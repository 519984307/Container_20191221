#include "socketservice.h"

SocketService::SocketService(QObject *parent)
{
    this->setParent(parent);

    tcpSocket=new QTcpSocket(this);
    pTimerLinkCamer=new QTimer (this);

    connect(tcpSocket,&QIODevice::readyRead,this,&SocketService::readFortune);
    connect(tcpSocket,&QAbstractSocket::connected,this,&SocketService::connected);
    connect(tcpSocket,&QAbstractSocket::disconnected,this,&SocketService::disconnected);
    connect(tcpSocket,&QAbstractSocket::stateChanged,this,&SocketService::stateChanged);
    connect(tcpSocket,QOverload<QAbstractSocket::SocketError>::of(&QAbstractSocket::error),this,&SocketService::displayError);    connect(pTimerLinkCamer,&QTimer::timeout,this,&SocketService::startLinkCamer);
}

SocketService::~SocketService()
{
    tcpSocket->abort();
    delete tcpSocket;
    tcpSocket=nullptr;
}

void SocketService::InitializationParameterSlot(const QString &address, const int &port, bool reconnection)
{
    this->address=address;
    this->port=port;
    startLinkCamer();
}

void SocketService::startLinkCamer()
{
    tcpSocket->abort();
    tcpSocket->connectToHost(address,port);
}

void SocketService::connected()
{
    emit messageSignal(ZBY_LOG("INFO"), tr("IP:%1  link successful").arg(address));
    emit socketLinkStateSingal(address,true);

    /* 防止出现链接完成后,物理线路断开 */
    if(pTimerLinkCamer->isActive())
    {
        pTimerLinkCamer->stop();
    }
    pTimerLinkCamer->start(20000);
}

void SocketService::readFortune()
{

}

void SocketService::socketSendDataSlot(const QString &data)
{

}

void SocketService::disconnected()
{
    emit socketLinkStateSingal(address,false);
}

void SocketService::displayError(QAbstractSocket::SocketError socketError)
{
    emit messageSignal(ZBY_LOG("ERROR"), tr("IP:%1  link error<errorCode=%2>").arg(address).arg(socketError));

    if(pTimerLinkCamer->isActive())
    {
        pTimerLinkCamer->stop();
    }
    pTimerLinkCamer->start(10000);
}

void SocketService::stateChanged(QAbstractSocket::SocketState socketState)
{
    emit messageSignal(ZBY_LOG("INFO"), tr("IP:%1 link state is %2").arg(address).arg(socketState));
}
