#include "infraredlogic.h"

InfraredLogic::InfraredLogic(QObject *parent)
{
    this-> setParent(parent);

    memset(status,0,sizeof (int));
    memset(tmpStatus,0,sizeof (int));
    exit=false;
}

InfraredLogic::~InfraredLogic()
{
    exit=true;
    free(status);
}

bool InfraredLogic::compareStatus(int *before, int *after)
{
    for (int i=0;i<6;i++) {
        if(before[i]!=after[i]) {
            return false;
        }
    }
    return  true;
}

void InfraredLogic::serialLogic(int *status)
{
    /*
     * 红外逻辑(一定要判断状态),1)如果A2无信号,过车释放A1,会导致后3张图偏移.
     * 常开[false|0,0,0,0]|常闭[true|1,1,1,1]
    */
    int one=0,two=1;
    if(!model) {
        one=1;two=0;
    }
    if(!compareStatus(status,tmpStatus)){
        //clearn
        if(status[0]==one){
            if(status[1]==two){
                if(status[3]==two){
                    if(status[4]==two)
                    {
                        emit logicPutImage(-1);
                    }
                }
            }
        }

        //45G1
        if(status[0]==one){
            if(status[1]==one){
                if(status[3]==one){
                    if(status[4]==one){
                        emit logicPutImage(0);
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
                            emit logicPutImage(1);
                            _45G1=false;
                        }
                    }
                }
            }
        }

        //22G1
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
                            emit logicPutImage(2);
                            _22G1=false;
                        }
                    }
                }
            }
        }

        //22G1_22G1
        if(status[0]==one){
            if(status[1]==two){
                if(status[3]==one){
                    if(status[4]==one){
                        emit logicPutImage(3);
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
                            emit logicPutImage(4);
                            _22G1_22G1=false;
                        }
                    }
                }
            }
        }
    }

    memcpy(tmpStatus,status,sizeof (tmpStatus));
}

void InfraredLogic::setAlarmMode(bool model)
{
    this->model=model;
}

void InfraredLogic::startSlave(const QString &portName1, const QString &portName2)
{
    QSerialPort serial1,serial2;
    bool com1=false;
    bool com2=false;

    serial1.close();
    serial1.setPortName(portName1);
    serial2.close();
    serial2.setPortName(portName2);

    //COM1
    if(!serial1.open(QIODevice::ReadOnly)){
        emit message(tr("Can't open %1, error code %2").arg(portName1).arg(serial1.error()));
    }
    else{
        //设置DTR电平高
        if(serial1.setDataTerminalReady(true)){
            emit message(tr("set 1% DataTerminalReady successful").arg(portName1));
            com1=true;
        }
        else {
            emit message(tr("Can't set DTR  %1, error code %2").arg(portName1).arg(serial1.error()));
        }
        //设置RTS电平高,可以不设置
        if(serial1.setRequestToSend(true))
        {
            emit message(tr("set 1% RequestToSend successful").arg(portName1));
        }
        else
        {
            emit message(tr("Can't set RTS  %1, error code %2").arg(portName1).arg(serial1.error()));
        }
    }

    //COM2
    if(!serial2.open(QIODevice::ReadOnly)){
        emit message(tr("Can't open %1, error code %2").arg(portName2).arg(serial2.error()));
    }
    else{
        //设置DTR电平高
        if(serial2.setDataTerminalReady(true)){
            emit message(tr("set %1 DataTerminalReady successful").arg(portName2));
            com2=true;
        }
        else {
            emit message(tr("Can't set DTR  %1, error code %2").arg(portName2).arg(serial2.error()));
        }
        //设置RTS电平高,可以不设置
        if(serial2.setRequestToSend(true))
        {
            emit message(tr("set %1 RequestToSend successful").arg(portName2));
        }
        else
        {
            emit message(tr("Can't set RTS  %1, error code %2").arg(portName2).arg(serial2.error()));
        }
    }

    int one=1,zero=0;
    //循环逻辑判断
    while (!this->exit)
    {
        QThread::usleep(1);

        if(com1){
            //COM1
            //A1
            status[0]= (serial1.pinoutSignals()&QSerialPort::ClearToSendSignal)?one:zero;
            //A2
            status[1]= (serial1.pinoutSignals()&QSerialPort::DataSetReadySignal)?one:zero;
            //D1
            status[2]= (serial1.pinoutSignals()&QSerialPort::DataCarrierDetectSignal)?one:zero;
        }

        if(com2){
            //COM2
            //B1
            status[3]= (serial2.pinoutSignals()&QSerialPort::ClearToSendSignal)?one:zero;
            //B2
            status[4]= (serial2.pinoutSignals()&QSerialPort::DataSetReadySignal)?one:zero;
            //D2
            status[5]= (serial2.pinoutSignals()&QSerialPort::DataCarrierDetectSignal)?one:zero;
        }

        if(compareStatus(status,tmpStatus)){//比对红外状态有没有变化,有变化才做相应处理.
            serialLogic(status);//逻辑判断
            emit logicStatus(status);//传递状态
        }
        memcpy(tmpStatus,status,sizeof (status));
    }
}
