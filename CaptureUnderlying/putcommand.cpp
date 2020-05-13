#include "putcommand.h"

PutCommand::PutCommand(QObject *parent) : QObject(parent)
{
    tcpSocket=new  QTcpSocket (this);
}

PutCommand::~PutCommand()
{
    if(tcpSocket!=nullptr){
        tcpSocket->abort();
    }
    delete  tcpSocket;
    tcpSocket=nullptr;
}

void PutCommand::linktoServerSlot(QString addr, quint16 port)
{
    if(!tcpSocket->isValid()){
            tcpSocket->connectToHost(addr,port);
    }
}

bool PutCommand::putCommandSlot()
{
    emit messageSignal(ZBY_LOG("INFO"),"Put Camera Command");

    if(tcpSocket->isValid()){
        const char * str_data="capture 01\n";
        if(tcpSocket->write(str_data)!=-1){
            return tcpSocket->flush();
        }
    }
    return false;
}
