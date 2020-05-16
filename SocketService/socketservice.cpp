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

    if(serviceMode==1){/* 服务器模式 */
        pTcpServer=new SocketServer (this);

        pTcpServer->setServiceType(serviceType);/* 设置服务模式 */
        /* 日志信息 */
        connect(pTcpServer,&SocketServer::messageSignal,this,&SocketService::messageSignal);
        /* 心跳包状态设置 */
        connect(this,&SocketService::sendHeartPacketSignal,pTcpServer,&SocketServer::sendHeartPacketSlot);
        /* 绑定客户端数量 */
        connect(pTcpServer,&SocketServer::socketConnectCountSignal,this,&SocketService::socketConnectCountSignal);
        /* 发送识别结果 */
        connect(this,&SocketService::sendResultSignal,pTcpServer,&SocketServer::sendResultSlot);

        startListen();
    }
    else if (serviceMode==0) {/* 客户端模式 */
        pTcpSocket=new QTcpSocket(this);
        pTimerLink=new QTimer (this);

        /* 发送识别结果 */
        connect(this,&SocketService::sendResultSignal,this,&SocketService::sendResultSlot);

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
            displayError(pTcpSocket->error());
        }
    }
}


void SocketService::startListen()
{
    if(!pTcpServer->listen(QHostAddress::AnyIPv4,port)){/* 服务器使用本机地址 */
        emit messageSignal(ZBY_LOG("ERROR"),tr("IP:%1 Listen Error<errocCode=%2>").arg(QHostAddress::AnyIPv4).arg(pTcpServer->errorString()));
    }
    else {
        emit messageSignal(ZBY_LOG("INFO"),tr("IP:%1 Start Listen.").arg(QHostAddress::AnyIPv4));
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
    isConnected=true;
    emit socketConnectCountSignal(1);

    if(heartBeat){
        if(pTimerLink->isActive()){
            pTimerLink->stop();
        }
         pTimerLink->start(15000);
    }

    emit messageSignal(ZBY_LOG("INFO"), tr("IP:%1:%2 Socket  Link Successful").arg(address).arg(port));
    //emit socketLinkStateSingal(address,true);
}

void SocketService::readFortune()
{
    /* 读取服务器数据 */
    QByteArray buf=pTcpSocket->readAll();
    qDebug()<<buf;
    //emit    isConnected=true;ketReadDataSignal();
}

void SocketService::socketSendDataSlot(const QString &data)
{
    if(pTcpSocket->isOpen()){
        pTcpSocket->write(data.toLocal8Bit());
    }
}

void SocketService::disconnected()
{
   emit socketConnectCountSignal(-1);
    //emit socketLinkStateSingal(address,false);
    isConnected=false;
}

void SocketService::displayError(QAbstractSocket::SocketError socketError)
{
    //emit socketLinkStateSingal(address,false);
    isConnected=false;
    emit messageSignal(ZBY_LOG("ERROR"), tr("IP:%1:%3  Socket Error<errorCode=%2>").arg(address).arg(socketError).arg(port));
    QTimer::singleShot(10000, this, SLOT(startLink()));
    if(pTimerLink->isActive()){
        pTimerLink->stop();
    }
}

void SocketService::releaseResourcesSlot()
{
    if(pTimerLink!=nullptr && pTimerLink->isActive()){
        pTimerLink->stop();
    }   
    if(pTcpServer!=nullptr){
        pTcpServer->releaseResourcesSlot();
    }
}

void SocketService::sendResultSlot(int channel, const QString &result)
{
    if(pTcpSocket->isOpen()){
        pTcpSocket->write(result.toLocal8Bit());
    }
}
