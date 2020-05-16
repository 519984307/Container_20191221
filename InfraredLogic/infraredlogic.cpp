#include "infraredlogic.h"

InfraredLogic::InfraredLogic(QObject *parent)
{
    this-> setParent(parent);

    pSerial1=new QSerialPort(this);
    pSerial2=new QSerialPort(this);

    pDetectionTimer=new QTimer  (this);
    connect(pDetectionTimer,SIGNAL(timeout()),this,SLOT(detectionLogicSlot()));

    pTimerFront=new QTimer (this) ;
    pTimerFront->setSingleShot(true);/* 单次定时器 */
    connect(pTimerFront,SIGNAL(timeout()),this,SLOT(delayFrontCaptureSlot()));

    pTimerAfter=new QTimer (this);
    pTimerAfter->setSingleShot(true);/* 单次定时器 */
    connect(pTimerAfter,SIGNAL(timeout()),this,SLOT(delayAfterCaptureSlot()));

    memset(status,0,sizeof (status));
    memset(tmpStatus,0,sizeof (tmpStatus));

    type=0;
    exit=false;
    health=false;
    doubleFrontPut=false;

    _45G1=false;_22G1=false;_22G1_MID_22G1=false;_22G1_22G1=false;_22G1_22G1_STATE=false;
}

InfraredLogic::~InfraredLogic()
{
    pDetectionTimer->stop();
    delete  pDetectionTimer;
    pDetectionTimer=nullptr;

    pTimerFront->stop();
    pTimerAfter->stop();
    delete pTimerFront;
    pTimerFront=nullptr;
    delete pTimerAfter;
    pTimerAfter=nullptr;
    /*
     * free(status);
     * free(tmpStatus);
     */
}

void InfraredLogic::setAlarmModeSlot(bool model)
{
    qDebug()<<model;
    valueOne=0;    valueTwo=1;
    /* 常开(false) |常闭(true) */
    if(!model) {
        valueOne=1;valueTwo=0;
    }
}

void InfraredLogic::exitWhileSlot(bool EXIT)
{
    pDetectionTimer->stop();
    pTimerFront->stop();
    pTimerAfter->stop();
    this->exit=EXIT;
    pSerial1->close();
    pSerial2->close();
    delete pSerial1;
    pSerial1=nullptr;
    delete pSerial2;
    pSerial2=nullptr;
}

bool InfraredLogic::compareStatus(int *before, int *after)
{
    for (int i=0;i<6;i++) {
        if(before[i]!=after[i]) {
            return true;
        }
    }
    return  false;
}

void InfraredLogic::serialLogic(int *status)
{
    /*
     * 红外逻辑(一定要判断状态),1)如果A2无信号,过车释放A1,会导致后3张图偏移.(处理完成)
     * 常开[false|0,0,0,0]|常闭[true|1,1,1,1]
    */
    //if(compareStatus(status,tmpStatus)){
        /*
         * clearn
        */
        if(status[0]==valueOne){
            if(status[1]==valueTwo){
                if(status[3]==valueTwo){
                    if(status[4]==valueTwo)
                    {
                        emit logicPutImageSignal(-1);
                        health=true;
                        return;
                    }
                }
            }
        }

        if(health){
            /*
             * 45G1 front
            */
            if(status[0]==valueOne){
                if(status[1]==valueOne){
                    if(status[3]==valueOne){
                        if(status[4]==valueOne){
                            if(!_22G1_22G1 && !_22G1_22G1_STATE){/* 过滤双箱重复抓图 */
                                emit logicPutImageSignal(-1);/* 过滤高车头抓拍的无效图片 */
                                emit logicPutImageSignal(0);
                                _45G1=true;
                                _22G1_MID_22G1=true;/* 双22尺箱和45尺箱前3张图片触发逻辑一样 */
                            }
                            else {
                                _45G1=false;
                                _22G1_22G1=true;/* 双箱 */
                            }
                            _22G1=false;
                        }
                    }
                }
            }

            //_45G1_CAR=false;
            _22G1_22G1_STATE=false;

            /*
             *  45G1 after
            */
            if(_45G1){
                if(status[0]==valueTwo){
                    if(status[1]==valueTwo){
                        if(status[3]==valueOne){
                            if(status[4]==valueOne){
                                emit logicPutImageSignal(1);
                                _22G1_22G1=false;
                                _22G1_MID_22G1=false;
                                _22G1_22G1_STATE=false;
                                _45G1=false;
                                health=false;
                                return;
                            }
                        }
                    }
                }
            }
            /*
             * 22G1 front
            */
            if(status[0]==valueOne){
                if(status[1]==valueOne){
                    if(status[3]==valueOne){
                        if(status[4]==valueTwo){
                            _22G1=true;
                            _45G1=false;/* 防止高车头小箱放后面,误认为是45G1 */
                            //return;//防止跳过长箱加高车头
                        }
                    }
                }
            }
            /*
             * 22G1 after
            */
            if(_22G1){
                if(status[0]==valueTwo){
                    if(status[1]==valueTwo){
                        if(status[3]==valueOne){
                            if(status[4]==valueOne){
                                emit logicPutImageSignal(2);
                                _22G1=false;
                                _22G1_22G1=false;
                                _22G1_MID_22G1=false;
                                _22G1_22G1_STATE=false;
                                _45G1=false;
                                health=false;
                                return;
                            }
                        }
                    }
                }
            }

            /*
             * 22G1_22G1 检测双箱状态
            */
            if(_22G1_MID_22G1){
                if(status[0]==valueOne){
                    if(status[1]==valueTwo){
                        if(status[3]==valueOne){
                            if(status[4]==valueOne){
                                _22G1_22G1=true;
                                _45G1=false;/* 判断是双箱,双箱和长箱前3张逻辑一样 */
                                return;
                            }
                        }
                    }
                }
            }

            /*
             *  长箱加高车头
            */
            if(_22G1_MID_22G1){
                if(status[0]==valueOne){
                    if(status[1]==valueOne){
                        if(status[3]==valueOne){
                            if(status[4]==valueTwo){
                                _22G1_22G1=false;
                                return;
                            }
                        }
                    }
                }
            }

            /*
             * 双箱加高车头
            */
            if(_22G1_MID_22G1){
                if(status[0]==valueOne){
                    if(status[1]==valueOne){
                        if(status[3]==valueTwo){
                            if(status[4]==valueOne){
                                _22G1_22G1_STATE=true;
                                return;
                            }
                        }
                    }
                }
            }

            if(_22G1_22G1){
                if(status[0]==valueTwo){
                    if(status[1]==valueTwo){
                        if(status[3]==valueOne){
                            if(status[4]==valueOne){
                                emit logicPutImageSignal(4);
                                _22G1_22G1=false;
                                _22G1_MID_22G1=false;
                                _22G1_22G1_STATE=false;
                                _45G1=false;
                                health=false;
                                return;
                            }
                        }
                    }
                }
            }
        }
    //}
    //memcpy(tmpStatus,status,sizeof (tmpStatus));
}

void InfraredLogic::startSlaveSlot(const QString &portName1, const QString &portName2)
{
    pSerial1->close();
    pSerial1->setPortName(portName1);
    pSerial2->close();
    pSerial2->setPortName(portName2);

    /*
     * COM1
    */
    if(!pSerial1->open(QIODevice::ReadOnly)){
        emit messageSignal(ZBY_LOG("ERROR"), tr("portName1:%1 Open error<errorCode=%2>").arg(portName1).arg(pSerial1->error()));
    }
    else{
        /*
         * 设置DTR电平高
        */
        if(pSerial1->setDataTerminalReady(true)){
            emit messageSignal(ZBY_LOG("INFO"), tr("portName1:%1 Set DataTerminalReady successful").arg(portName1));
            com1=true;
        }
        else {
            emit messageSignal(ZBY_LOG("ERROR"), tr("portName1:%1 Set DataTerminalReady  error<errorCode=%2>").arg(portName1).arg(pSerial1->error()));
        }
        /*
         * 设置RTS电平高,可以不设置
        */
        if(pSerial1->setRequestToSend(true))
        {
            emit messageSignal(ZBY_LOG("INFO"),tr("portName1:%1 Set RequestToSend successful").arg(portName1));
        }
        else{
            emit messageSignal(ZBY_LOG("ERROR"),tr("portName1:%1 Set RequestToSend error<errorCode=%2>").arg(portName1).arg(pSerial1->error()));
        }
    }

    /*
     * COM2
    */
    if(!pSerial2->open(QIODevice::ReadOnly)){
        emit messageSignal(ZBY_LOG("ERROR"),tr("portName2:%1 Open error<errorCode=%2>").arg(portName2).arg(pSerial2->error()));
    }
    else{
        /*
         * 设置DTR电平高
        */
        if(pSerial2->setDataTerminalReady(true)){
            emit messageSignal(ZBY_LOG("INFO"),tr("portName2:%1 Set DataTerminalReady successful").arg(portName2));
            com2=true;
        }
        else {
            emit messageSignal(ZBY_LOG("ERROR"),tr("portName2:%1 Set DataTerminalReady error<errorCode=%2>").arg(portName2).arg(pSerial2->error()));
        }
        /*
         * 设置RTS电平高,可以不设置
        */
        if(pSerial2->setRequestToSend(true))
        {
            emit messageSignal(ZBY_LOG("INFO"),tr("portName2:%1 Set RequestToSend successful").arg(portName2));
        }
        else{
            emit messageSignal(ZBY_LOG("ERROR"),tr("portName2:%1 Set RequestToSend error<errorCode=%2>").arg(portName2).arg(pSerial2->error()));
        }
    }

    if(!com1 && !com2){/* com1和com2都未打开,不做后续处理 */
        emit messageSignal(ZBY_LOG("INFO"),tr("Channel serial port exception"));
        return;
    }

    pDetectionTimer->start(1);
}

void InfraredLogic::simulateTriggerSlot(int type)
{
    this->type=type;

    switch (type) {
    case 0:/* 清除图片 */
        emit logicPutImageSignal(-1);
        break;
    case 1:/* 22G1 */
        emit logicPutImageSignal(-1);
        emit logicPutImageSignal(2);
        break;
    case 2:/* 45G1,后3张图片延时抓拍 */
        emit logicPutImageSignal(-1);
        emit logicPutImageSignal(0);
        QTimer::singleShot(3000,this,SLOT(delayAfterCaptureSlot()));
        break;
    case 3:/* Double 22G1 Front */
        emit logicPutImageSignal(-1);
        emit logicPutImageSignal(3);
        doubleFrontPut=true;
        break;
    case 4:/* Double 22G1 Front */
        if(doubleFrontPut){
            emit logicPutImageSignal(4);
        }
        doubleFrontPut=false;
        break;
    case 5:/* 循环抓拍45G1,后3张图片延时抓拍 */
        if(pTimerFront->isActive()){
            pTimerFront->stop();
        }
        else {
            if(!pTimerAfter->isActive()){
                pTimerFront->start(5000);
            }
        }
        if(pTimerAfter->isActive()){
            pTimerAfter->stop();
        }
        break;
    }
}

void InfraredLogic::delayAfterCaptureSlot()
{
    emit logicPutImageSignal(1);
    if(type==5){
        pTimerFront->start(10000);
    }
}

void InfraredLogic::delayFrontCaptureSlot()
{
    emit logicPutImageSignal(-1);
    emit logicPutImageSignal(0);

    if(pTimerAfter->isActive()){/* 延时抓拍后面图片 */
        pTimerAfter->stop();
    }
    pTimerAfter->start(5000);
}

void InfraredLogic::detectionLogicSlot()
{
    detectionLogicStatus(com1,com2);
}

void InfraredLogic::detectionLogicStatus(bool com1, bool com2)
{
    if(com1){
        /*A1*/
        status[0]= (pSerial1->pinoutSignals()&QSerialPort::ClearToSendSignal)?1:0;
        //A2
        status[1]= (pSerial1->pinoutSignals()&QSerialPort::DataSetReadySignal)?1:0;
        /*D1*/
        status[2]= (pSerial1->pinoutSignals()&QSerialPort::DataCarrierDetectSignal)?1:0;
    }

    if(com2){
        /*B1*/
        status[3]= (pSerial2->pinoutSignals()&QSerialPort::ClearToSendSignal)?1:0;
        /*B2*/
        status[4]= (pSerial2->pinoutSignals()&QSerialPort::DataSetReadySignal)?1:0;
        /*D2*/
        status[5]= (pSerial2->pinoutSignals()&QSerialPort::DataCarrierDetectSignal)?1:0;
    }

    if(com1&&com2){
        /* 比对红外状态有没有变化 有变化才做相应处理 */
        if(compareStatus(status,tmpStatus)){
            serialLogic(status); /* 逻辑判断 */
            memcpy(tmpStatus,status,sizeof (status));
        }
    }

    /* 传递状态 */
    if(compareStatus(status,tmpStatus)){
        emit logicStatusSignal(status);
        memcpy(tmpStatus,status,sizeof (status));
    }
}
