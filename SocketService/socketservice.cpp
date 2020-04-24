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
    if(pTimerLink!=nullptr && pTimerLink->isActive()){
        pTimerLink->stop();
    }

    delete pTcpServer;
    delete pTcpSocket;
    delete pTimerLink;

    pTcpServer=nullptr;
    pTcpSocket=nullptr;
    pTimerLink=nullptr;
}

void SocketService::InitializationParameterSlot(const QString &address, const quint16 &port, const int &serviceType)
{
    this->address=address;
    this->port=port;

    if(serviceType==1){/* 服务器模式 */
        pTcpServer=new SocketServer (this);
        startListen();
    }
    if(serviceType==0){/* 客户端模式 */
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
    if(!pTcpServer->listen(QHostAddress(address),port)){
        emit messageSignal(ZBY_LOG("ERROR"),tr("IP:%1 listen error<errocCode=%2>").arg(address).arg(pTcpServer->errorString()));
        qDebug()<<pTcpServer->errorString();
    }
    else {
        emit messageSignal(ZBY_LOG("INFO"),tr("IP:%1 start listen.").arg(address));
        qDebug()<<"sucess";
    }
}

void SocketService::heartbeatSlot()
{
    if(pTcpSocket->isOpen()){
        pTcpSocket->write("");/* 心跳包空数据 */
    }
}

void SocketService::connected()
{
    if(pTimerLink->isActive()){
        pTimerLink->stop();
    }
    pTimerLink->start(5000);
    emit messageSignal(ZBY_LOG("INFO"), tr("IP:%1 Socket  Link Successful").arg(address));
    emit socketLinkStateSingal(address,true);
    isConnected=true;
}

void SocketService::readFortune()
{
    /* 读取客户端数据 */
    QByteArray buf=pTcpSocket->readAll();
    qDebug()<<buf;
    //emit socketReadDataSignal();
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
