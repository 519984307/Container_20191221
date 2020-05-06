#include "socketservice.h"

SocketService::SocketService(QObject *parent)
{
    this->setParent(parent);

    isConnected=false;
    pTcpServer=nullptr;
    pTcpSocket=nullptr;
    pTimerLink=nullptr;
}

SocketService::~SocketService()
{
    if(pTcpSocket!=nullptr){
         pTcpSocket->abort();
    }
    if(pTcpServer!=nullptr){
         pTcpServer->close();
    }

    delete pTcpServer;
    delete pTcpSocket;
    delete pTimerLink;

    pTcpServer=nullptr;
    pTcpSocket=nullptr;
    pTimerLink=nullptr;
}

void SocketService::InitializationParameterSlot(const QString &address, const quint16 &port, const int &serviceType,const int& serviceMode,const int& heartBeat)
{
    this->heartBeat=heartBeat;
    this->address=address;
    this->port=port;

    if(serviceType==1){/* 服务器模式 */
        pTcpServer=new SocketServer (this);

        connect(pTcpServer,&SocketServer::messageSignal,this,&SocketService::messageSignal);

        startListen();
    }
    else if (serviceType==0) {/* 客户端模式 */
        pTcpSocket=new QTcpSocket(this);
        pTimerLink=new QTimer (this);

        connect(pTcpSocket,&QIODevice::readyRead,this,&SocketService::readFortune);
        connect(pTcpSocket,&QAbstractSocket::connected,this,&SocketService::connected);
        connect(pTcpSocket,&QAbstractSocket::disconnected,this,&SocketService::disconnected);
        connect(pTcpSocket,QOverload<QAbstractSocket::SocketError>::of(&QAbstractSocket::error),this,&SocketService::displayError);
        connect(pTimerLink,&QTimer::timeout,this,&SocketService::heartbeatSlot);

        startLink();
    }
}

void SocketService::startLink()
{
    if(!isConnected){
        pTcpSocket->abort();
        pTcpSocket->connectToHost(address,port);

        if(!pTcpSocket->waitForConnected(1000)){
            pTcpSocket->error();
        }
    }
}

void SocketService::startListen()
{
    if(!pTcpServer->listen(QHostAddress::Any,port)){/* 服务器使用本机地址 */
        emit messageSignal(ZBY_LOG("ERROR"),tr("IP:%1 Listen Error<errocCode=%2>").arg(QHostAddress::Any).arg(pTcpServer->errorString()));
    }
    else {
        emit messageSignal(ZBY_LOG("INFO"),tr("IP:%1 Start Listen.").arg(QHostAddress::Any));
        /* 绑定客户端数量 */
        connect(pTcpServer,&SocketServer::socketConnectCountSignal,this,&SocketService::socketConnectCountSignal);
        /* 发送识别结果 */
        connect(this,&SocketService::sendResultSignal,pTcpServer,&SocketServer::sendResultSlot);
    }
}

void SocketService::heartbeatSlot()
{
    if(pTcpSocket->isOpen()){
        pTcpSocket->write("[H]");/* 心跳包数据 */
    }
}

void SocketService::connected()
{
    if(pTimerLink->isActive()){
        pTimerLink->stop();
    }

    if(heartBeat){
         pTimerLink->start(5000);
    }

    isConnected=true;

    emit messageSignal(ZBY_LOG("INFO"), tr("IP:%1 Socket  Link Successful").arg(address));
    emit socketLinkStateSingal(address,true);
}

void SocketService::readFortune()
{
    /* 读取客户端数据 */
    QByteArray buf=pTcpSocket->readAll();
    qDebug()<<buf;
    //emit soc    isConnected=true;ketReadDataSignal();
}

void SocketService::socketSendDataSlot(const QString &data)
{
    if(pTcpSocket->isOpen()){
        pTcpSocket->write(data.toLocal8Bit());
    }
}

void SocketService::disconnected()
{
    emit socketLinkStateSingal(address,false);
    isConnected=false;
}

void SocketService::displayError(QAbstractSocket::SocketError socketError)
{
    emit socketLinkStateSingal(address,false);
    isConnected=false;
    emit messageSignal(ZBY_LOG("ERROR"), tr("IP:%1  Socket Error<errorCode=%2>").arg(address).arg(socketError));
    QTimer::singleShot(10000, this, SLOT(startLink()));
}

void SocketService::releaseResourcesSlot()
{
    if(pTimerLink!=nullptr && pTimerLink->isActive()){
        pTimerLink->stop();
    }
}
