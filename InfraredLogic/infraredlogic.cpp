#include "infraredlogic.h"
#include<QTime>

InfraredLogic::InfraredLogic(QObject *parent)
{
    this-> setParent(parent);

    pTimerFront=new QTimer (this) ;
    pTimerFront->setSingleShot(true);/* 单次定时器 */
    pTimerAfter=new QTimer (this);
    pTimerAfter->setSingleShot(true);/* 单次定时器 */

    connect(pTimerFront,SIGNAL(timeout()),this,SLOT(delayFrontCaptureSlot()));
    connect(pTimerAfter,SIGNAL(timeout()),this,SLOT(delayAfterCaptureSlot()));

    memset(status,0,sizeof (status));
    memset(tmpStatus,0,sizeof (tmpStatus));

    type=0;
    exit=false;
    health=false;
}

InfraredLogic::~InfraredLogic()
{   
    pTimerFront->stop();
    pTimerAfter->stop();
    delete pTimerFront;
    delete pTimerAfter;
    /*
     * free(status);
     * free(tmpStatus);
     */
}

void InfraredLogic::setAlarmModeSlot(bool model)
{
    valueOne=0;    valueTwo=1;
    /* 常开(false) |常闭(true) */
    if(!model) {
        valueOne=1;valueTwo=0;
    }
}

void InfraredLogic::exitWhileSlot(bool EXIT)
{
    pTimerFront->stop();
    pTimerAfter->stop();
    this->exit=EXIT;
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
     * 红外逻辑(一定要判断状态),1)如果A2无信号,过车释放A1,会导致后3张图偏移.
     * 常开[false|0,0,0,0]|常闭[true|1,1,1,1]
    */
    if(compareStatus(status,tmpStatus)){
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
                    }
                }
            }
        }

        if(health){
            /*
             * 45G1
            */
            if(status[0]==valueOne){
                if(status[1]==valueOne){
                    if(status[3]==valueOne){
                        if(status[4]==valueOne){
                            emit logicPutImageSignal(0);
                            _22G1=false;
                            _45G1=true;
                        }
                    }
                }
            }
            if(_45G1){
                if(status[0]==valueTwo){
                    if(status[1]==valueTwo){
                        if(status[3]==valueOne){
                            if(status[4]==valueOne){
                                emit logicPutImageSignal(1);
                                _45G1=false;
                                health=false;
                            }
                        }
                    }
                }
            }

            /*
             * 22G1
            */
            if(status[0]==valueOne){
                if(status[1]==valueOne){
                    if(status[3]==valueOne){
                        if(status[4]==valueTwo){
                            _22G1=true;
                        }
                    }
                }
            }
            if(_22G1){
                if(status[0]==valueTwo){
                    if(status[1]==valueTwo){
                        if(status[3]==valueOne){
                            if(status[4]==valueOne){
                                emit logicPutImageSignal(2);
                                _22G1=false;
                                health=false;
                            }
                        }
                    }
                }
            }

            /*
             * 22G1_22G1
            */
            if(status[0]==valueOne){
                if(status[1]==valueTwo){
                    if(status[3]==valueOne){
                        if(status[4]==valueOne){
                            emit logicPutImageSignal(3);
                            _22G1_22G1=true;
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
                                health=false;
                            }
                        }
                    }
                }
            }
        }
    }
    //memcpy(tmpStatus,status,sizeof (tmpStatus));
}
#include <iostream>
void InfraredLogic::startSlaveSlot(const QString &portName1, const QString &portName2)
{
        QSerialPort serial1,serial2;
        bool com1=false;
        bool com2=false;

        serial1.close();
        serial1.setPortName(portName1);
        serial2.close();
        serial2.setPortName(portName2);

        /*
         * COM1
        */
        if(!serial1.open(QIODevice::ReadOnly)){
            emit messageSignal(ZBY_LOG("ERROR"), tr("portName1:%1 Open error<errorCode=%2>").arg(portName1).arg(serial1.error()));
        }
        else{
            /*
             * 设置DTR电平高
            */
            if(serial1.setDataTerminalReady(true)){
                emit messageSignal(ZBY_LOG("INFO"), tr("portName1:%1 Set DataTerminalReady successful").arg(portName1));
                com1=true;
            }
            else {
                emit messageSignal(ZBY_LOG("ERROR"), tr("portName1:%1 Set DataTerminalReady  error<errorCode=%2>").arg(portName1).arg(serial1.error()));
            }
            /*
             * 设置RTS电平高,可以不设置
            */
            if(serial1.setRequestToSend(true))
            {
                emit messageSignal(ZBY_LOG("INFO"),tr("portName1:%1 Set RequestToSend successful").arg(portName1));
            }
            else{
                emit messageSignal(ZBY_LOG("ERROR"),tr("portName1:%1 Set RequestToSend error<errorCode=%2>").arg(portName1).arg(serial1.error()));
            }
        }

        /*
         * COM2
        */
        if(!serial2.open(QIODevice::ReadOnly)){
            emit messageSignal(ZBY_LOG("ERROR"),tr("portName2:%1 Open error<errorCode=%2>").arg(portName2).arg(serial2.error()));
        }
        else{
            /*
             * 设置DTR电平高
            */
            if(serial2.setDataTerminalReady(true)){
                emit messageSignal(ZBY_LOG("INFO"),tr("portName2:%1 Set DataTerminalReady successful").arg(portName2));
                com2=true;
            }
            else {
                emit messageSignal(ZBY_LOG("ERROR"),tr("portName2:%1 Set DataTerminalReady error<errorCode=%2>").arg(portName2).arg(serial2.error()));
            }
            /*
             * 设置RTS电平高,可以不设置
            */
            if(serial2.setRequestToSend(true))
            {
                emit messageSignal(ZBY_LOG("INFO"),tr("portName2:%1 Set RequestToSend successful").arg(portName2));
            }
            else{
                emit messageSignal(ZBY_LOG("ERROR"),tr("portName2:%1 Set RequestToSend error<errorCode=%2>").arg(portName2).arg(serial2.error()));
            }
        }

        /*
         * 循环逻辑判断
         */
        while (!this->exit)
        {
            QCoreApplication::processEvents();
            QThread::msleep(1);

            if(com1){
                /*A1*/
                status[0]= (serial1.pinoutSignals()&QSerialPort::ClearToSendSignal)?1:0;
                //A2
                status[1]= (serial1.pinoutSignals()&QSerialPort::DataSetReadySignal)?1:0;
                /*D1*/
                status[2]= (serial1.pinoutSignals()&QSerialPort::DataCarrierDetectSignal)?1:0;
            }

            if(com2){
                /*B1*/
                status[3]= (serial2.pinoutSignals()&QSerialPort::ClearToSendSignal)?1:0;
                /*B2*/
                status[4]= (serial2.pinoutSignals()&QSerialPort::DataSetReadySignal)?1:0;
                /*D2*/
                status[5]= (serial2.pinoutSignals()&QSerialPort::DataCarrierDetectSignal)?1:0;
            }

            /* 比对红外状态有没有变化 有变化才做相应处理 */
            if(compareStatus(status,tmpStatus)){
                serialLogic(status); /* 逻辑判断 */
                emit logicStatusSignal(status);/* 传递状态 */
            }
            memcpy(tmpStatus,status,sizeof (status));
        }
}

void InfraredLogic::simulateTriggerSlot(int type)
{
    this->type=type;

    switch (type) {
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
        break;
    case 4:/* Double 22G1 Before */
        emit logicPutImageSignal(4);
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
