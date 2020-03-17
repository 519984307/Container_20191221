#include "infraredlogic.h"
#include<QTime>

InfraredLogic::InfraredLogic(QObject *parent)
{
    this-> setParent(parent);

    memset(status,0,sizeof (int));
    memset(tmpStatus,0,sizeof (int));

    exit=false;
    model=false;

    one=0;    two=1;
    /* 常开(false) |常闭(true) */
    if(!model) {
        one=1;two=0;
    }
}

InfraredLogic::~InfraredLogic()
{   
    /*
     * free(status);
     * free(tmpStatus);
     */
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
        if(status[0]==one){
            if(status[1]==two){
                if(status[3]==two){
                    if(status[4]==two)
                    {
                        emit logicPutImageSignal(-1);
                    }
                }
            }
        }

        /*
         * 45G1
        */
        if(status[0]==one){
            if(status[1]==one){
                if(status[3]==one){
                    if(status[4]==one){
                        emit logicPutImageSignal(0);
                        _22G1=false;
                        _45G1=true;
                    }
                }
            }
        }
        if(_45G1){
            if(status[0]==two){
                if(status[1]==two){
                    if(status[3]==one){
                        if(status[4]==one){
                            emit logicPutImageSignal(1);
                            _45G1=false;
                        }
                    }
                }
            }
        }

        /*
         * 22G1
        */
        if(status[0]==one){
            if(status[1]==one){
                if(status[3]==one){
                    if(status[4]==two){
                        _22G1=true;
                    }
                }
            }
        }
        if(_22G1){
            if(status[0]==two){
                if(status[1]==two){
                    if(status[3]==one){
                        if(status[4]==one){
                            emit logicPutImageSignal(2);
                            _22G1=false;
                        }
                    }
                }
            }
        }

        /*
         * 22G1_22G1
        */
        if(status[0]==one){
            if(status[1]==two){
                if(status[3]==one){
                    if(status[4]==one){
                        emit logicPutImageSignal(3);
                        _22G1_22G1=true;
                    }
                }
            }
        }
        if(_22G1_22G1){
            if(status[0]==two){
                if(status[1]==two){
                    if(status[3]==one){
                        if(status[4]==one){
                            emit logicPutImageSignal(4);
                            _22G1_22G1=false;
                        }
                    }
                }
            }
        }
    }

    memcpy(tmpStatus,status,sizeof (tmpStatus));
}

void InfraredLogic::setAlarmModeSlot(bool model)
{
    this->model=model;
}

void InfraredLogic::exitWhileSlot(bool EXIT)
{
    this->exit=EXIT;
}

void InfraredLogic::startSlaveSlot(const QString &portName1, const QString &portName2)
{
    //    QSerialPort serial1,serial2;
    //    bool com1=false;
    //    bool com2=false;

    //    serial1.close();
    //    serial1.setPortName(portName1);
    //    serial2.close();
    //    serial2.setPortName(portName2);

    //    /*
    //     * COM1
    //    */
    //    if(!serial1.open(QIODevice::ReadOnly)){
    //        emit messageSignal(tr("Can't open %1, error code %2").arg(portName1).arg(serial1.error()));
    //    }
    //    else{
    //        /*
    //         * 设置DTR电平高
    //        */
    //        if(serial1.setDataTerminalReady(true)){
    //            emit messageSignal(tr("set %1 DataTerminalReady successful").arg(portName1));
    //            com1=true;
    //        }
    //        else {
    //            emit messageSignal(tr("Can't set DTR  %1, error code %2").arg(portName1).arg(serial1.error()));
    //        }
    //        /*
    //         * 设置RTS电平高,可以不设置
    //        */
    //        if(serial1.setRequestToSend(true))
    //        {
    //            emit messageSignal(tr("set %1 RequestToSend successful").arg(portName1));
    //        }
    //        else{
    //            emit messageSignal(tr("Can't set RTS  %1, error code %2").arg(portName1).arg(serial1.error()));
    //        }
    //    }

    //    /*
    //     * COM2
    //    */
    //    if(!serial2.open(QIODevice::ReadOnly)){
    //        emit messageSignal(tr("Can't open %1, error code %2").arg(portName2).arg(serial2.error()));
    //    }
    //    else{
    //        /*
    //         * 设置DTR电平高
    //        */
    //        if(serial2.setDataTerminalReady(true)){
    //            emit messageSignal(tr("set %1 DataTerminalReady successful").arg(portName2));
    //            com2=true;
    //        }
    //        else {
    //            emit messageSignal(tr("Can't set DTR  %1, error code %2").arg(portName2).arg(serial2.error()));
    //        }
    //        /*
    //         * 设置RTS电平高,可以不设置
    //        */
    //        if(serial2.setRequestToSend(true))
    //        {
    //            emit messageSignal(tr("set %1 RequestToSend successful").arg(portName2));
    //        }
    //        else{
    //            emit messageSignal(tr("Can't set RTS  %1, error code %2").arg(portName2).arg(serial2.error()));
    //        }
    //    }

    //    /*
    //     * int one=1 int zero=0;
    //     * 循环逻辑判断
    //    */
    //    while (!this->exit)
    //    {
    //        QCoreApplication::processEvents();
    //        QThread::usleep(1);

    //        if(com1){
    //            /*A1*/
    //            status[0]= (serial1.pinoutSignals()&QSerialPort::ClearToSendSignal)?1:0;
    //            //A2
    //            status[1]= (serial1.pinoutSignals()&QSerialPort::DataSetReadySignal)?1:0;
    //            /*D1*/
    //            status[2]= (serial1.pinoutSignals()&QSerialPort::DataCarrierDetectSignal)?1:0;
    //        }

    //        if(com2){
    //            /*B1*/
    //            status[3]= (serial2.pinoutSignals()&QSerialPort::ClearToSendSignal)?1:0;
    //            /*B2*/
    //            status[4]= (serial2.pinoutSignals()&QSerialPort::DataSetReadySignal)?1:0;
    //            /*D2*/
    //            status[5]= (serial2.pinoutSignals()&QSerialPort::DataCarrierDetectSignal)?1:0;
    //        }

    //        /* 比对红外状态有没有变化 有变化才做相应处理 */
    //        if(compareStatus(status,tmpStatus)){
    //            serialLogic(status); /* 逻辑判断 */
    //            emit logicStatusSignal(status);/* 传递状态 */
    //        }
    //        memcpy(tmpStatus,status,sizeof (status));
    //    }

//    while (1)
//    {
//                QCoreApplication::processEvents();
//                QThread::msleep(10);

//        if(this->exit){
//            break;
//        }

//        qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
//        /*A1*/
//        status[0]= qrand()%2;
//        //A2
//        status[1]= qrand()%2;
//        /*D1*/
//        status[2]= qrand()%2;

//        status[3]=qrand()%2;
//        /*B2*/
//        status[4]= qrand()%2;
//        /*D2*/
//        status[5]= qrand()%2;
//                if(compareStatus(status,tmpStatus)){
//                    //serialLogic(status); /* 逻辑判断 */
//                    emit logicStatusSignal(status);/* 传递状态 */
//                }
//        //emit logicStatusSignal(status);/* 传递状态 */

//    }
    while (1)
    {
        memcpy(tmpStatus,status,sizeof (status));

        QCoreApplication::processEvents();

        if(this->exit){
            break;
        }

        QCoreApplication::processEvents();

        /*A1*/
        status[0]= 1;
        serialLogic(status); /* 逻辑判断 */
        emit logicStatusSignal(status);/* 传递状态 */
        QThread::sleep(1);

        QCoreApplication::processEvents();

        /* A2 */
        status[1]= 1;
        serialLogic(status); /* 逻辑判断 */
        emit logicStatusSignal(status);/* 传递状态 */
        QThread::sleep(1);

        QCoreApplication::processEvents();

        /*B1*/
        status[3]=1;
        serialLogic(status); /* 逻辑判断 */
        emit logicStatusSignal(status);/* 传递状态 */
        QThread::sleep(1);

        QCoreApplication::processEvents();

         /*B2*/
        status[4]= 1;
        serialLogic(status); /* 逻辑判断 */
        emit logicStatusSignal(status);/* 传递状态 */
        QThread::sleep(10);

        QCoreApplication::processEvents();

        /* A1*/
        status[0]= 0;
        serialLogic(status); /* 逻辑判断 */
        emit logicStatusSignal(status);/* 传递状态 */
        QThread::sleep(1);

        QCoreApplication::processEvents();

        /* A2 */
        status[1]=0;
        serialLogic(status); /* 逻辑判断 */
        emit logicStatusSignal(status);/* 传递状态 */
        QThread::sleep(1);

        QCoreApplication::processEvents();

        /*B1*/
        status[3]= 0;
        serialLogic(status); /* 逻辑判断 */
        emit logicStatusSignal(status);/* 传递状态 */
        QThread::sleep(1);

        QCoreApplication::processEvents();

        /*B2*/
        status[4]= 0;
        serialLogic(status); /* 逻辑判断 */
        emit logicStatusSignal(status);/* 传递状态 */

        QThread::sleep(5);
        //memcpy(tmpStatus,status,sizeof (status));
    }

}
