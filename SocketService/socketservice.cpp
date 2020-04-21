#include "socketservice.h"

SocketService::SocketService(QObject *parent)
{
    this->setParent(parent);
    pTcpServer=nullptr;

    pTcpSocket=new QTcpSocket(this);
    //pTcpServer=new QTcpServer(this);
    pTimerLink=new QTimer (this);

    connect(pTcpSocket,&QIODevice::readyRead,this,&SocketService::readFortune);
    connect(pTcpSocket,&QAbstractSocket::connected,this,&SocketService::connected);
    connect(pTcpSocket,&QAbstractSocket::disconnected,this,&SocketService::disconnected);
    connect(pTcpSocket,QOverload<QAbstractSocket::SocketError>::of(&QAbstractSocket::error),this,&SocketService::displayError);
    connect(pTimerLink,&QTimer::timeout,this,&SocketService::startLink);
}

SocketService::~SocketService()
{
    pTcpSocket->abort();
    if(pTcpServer!=nullptr){
         pTcpServer->close();
    }
    pTimerLink->stop();

    delete pTcpServer;
    delete pTcpSocket;
    delete pTimerLink;

    pTcpServer=nullptr;
    pTcpSocket=nullptr;
    pTimerLink=nullptr;
}

void SocketService::InitializationParameterSlot(const QString &address, const int &port, const int& channel, const int &serviceType)
{
    qDebug()<<"init";
    this->address=address;
    this->port=port;
    this->channel=channel;

    if(serviceType==0){/* 服务器模式 */
        startListen();
    }
    if(serviceType==1){/* 客户端模式 */
         startLink();
    }
}

void SocketService::startLink()
{
    pTcpSocket->abort();
    pTcpSocket->connectToHost(address,static_cast<quint16>(port));
}

void SocketService::startListen()
{
    pTcpServer=new SocketServer (this);
    if(!pTcpServer->listen(QHostAddress(address),static_cast<quint16>(port))){
        emit messageSignal(ZBY_LOG("ERROR"),tr("IP:%1 listen error<errocCode=%2>").arg(address).arg(pTcpServer->errorString()));
        qDebug()<<pTcpServer->errorString();
    }
    else {
        emit messageSignal(ZBY_LOG("INFO"),tr("IP:%1 start listen.").arg(address));
        qDebug()<<"sucess";
    }
}

void SocketService::newClientConnectSlot()
{
//    SocketClient* pClient=new SocketClient (this);
//    auto tmp=pTcpServer->nextPendingConnection();
//    pClient->setSocketDescriptor(tmp->socketDescriptor());

//    connect(pClient,&QTcpSocket::readyRead,this,&SocketService::readFortune);
//    connect(pClient,&QTcpSocket::disconnected,this,&SocketService::disconnected);

    //emit messageSignal(ZBY_LOG("INFO"),tr("IP:%1 There is new client access").arg(pClient->peerAddress().toString()));
    //clientList.append(pClient);
}

void SocketService::connected()
{
    emit messageSignal(ZBY_LOG("INFO"), tr("IP:%1  link successful").arg(address));
    emit socketLinkStateSingal(address,true);

    /* 防止出现链接完成后,物理线路断开 */
    if(pTimerLink->isActive())
    {
        pTimerLink->stop();
    }
    pTimerLink->start(20000);
}

void SocketService::readFortune()
{
    //emit socketReadDataSignal();
}

void SocketService::socketSendDataSlot(const QString &data)
{
//    if(pTcpSocket->isOpen()){
//        tcpSocket->write();
//    }
}

void SocketService::disconnected()
{
    //emit socketLinkStateSingal(address,false);
}

void SocketService::displayError(QAbstractSocket::SocketError socketError)
{
    emit messageSignal(ZBY_LOG("ERROR"), tr("IP:%1  link error<errorCode=%2>").arg(address).arg(socketError));

    if(pTimerLink->isActive())
    {
        pTimerLink->stop();
    }
    pTimerLink->start(10000);
}
