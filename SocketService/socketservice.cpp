#include "socketservice.h"

SocketService::SocketService(QObject *parent)
{
    this->setParent(parent);

    heartBeat=false;
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

void SocketService::InitializationParameterSlot(const QString &address, const quint16 &port, const int &serviceType,const int& serviceMode)
{
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
        /* 心跳包状态设置 */
        connect(this,&SocketService::sendHeartPacketSignal,this,&SocketService::sendHeartPacketSlot);

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

//        if(!pTcpSocket->waitForConnected(1000)){
//            displayError(pTcpSocket->error());
//        }
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
    if(heartBeat){
        if(pTcpSocket->isOpen()){
            pTcpSocket->write("[H]");/* 心跳包数据 */
        }
    }
}

void SocketService::connected()
{
    isConnected=true;

    if(!pTimerLink->isActive()){
        pTimerLink->start(15000);
    }

    emit socketConnectCountSignal(1);
    emit messageSignal(ZBY_LOG("INFO"), tr("IP:%1:%2 Socket  Link Successful").arg(address).arg(port));
    //emit socketLinkStateSingal(address,true);
}

void SocketService::readFortune()
{
    /* 读取服务器数据 */
    QByteArray buf=pTcpSocket->readAll();    
    if (buf.indexOf("[R")!=-1) {/* 找到取结果标志位 */
        if(pTcpSocket->isOpen()){
            pTcpSocket->write(resultOfMemory.toLocal8Bit());/* 重新发送 */
        }
    }
}

void SocketService::socketSendDataSlot(const QString &data)
{
    if(pTcpSocket->isOpen()){
        pTcpSocket->write(data.toLocal8Bit());
    }
}

void SocketService::disconnected()
{
    isConnected=false;
    emit socketConnectCountSignal(-1);
    //emit socketLinkStateSingal(address,false);
}

void SocketService::displayError(QAbstractSocket::SocketError socketError)
{
    //emit socketLinkStateSingal(address,false);
    isConnected=false;

    QTimer::singleShot(15000, this, SLOT(startLink()));
    emit messageSignal(ZBY_LOG("ERROR"), tr("IP:%1:%3  Socket Error<errorCode=%2>").arg(address).arg(socketError).arg(port));
}

void SocketService::sendHeartPacketSlot(bool state)
{
    heartBeat=state;
}

void SocketService::releaseResourcesSlot()
{
    if(pTcpSocket!=nullptr){
         pTcpSocket->abort();
    }

    isConnected=false;

    if(pTimerLink!=nullptr && pTimerLink->isActive()){
        pTimerLink->stop();
    }   
    if(pTcpServer!=nullptr){
        pTcpServer->releaseResourcesSlot();
    }
}

void SocketService::sendResultSlot(int channel, const QString &result)
{    
    //QString ret=QString("%1\n\r").arg(result);
    resultOfMemory=result;/* 存储结果，用于主动获取 */

    /*****************************
    * @brief:20210202软著需求改动，发送完结果断开，有结果再次链接
    ******************************/
    startLink();
    pTcpSocket->waitForConnected(3000);

    if(pTcpSocket->isOpen()){
        pTcpSocket->write(result.toLocal8Bit());

        /*****************************
        * @brief:发送完成主动断开        
        ******************************/
        pTcpSocket->waitForBytesWritten();
        pTcpSocket->abort();
        pTcpSocket->close();
        //QTimer::singleShot(10000,this,SLOT(startLink()));/* 20210202软著需求改动，发送完结果断开，有结果再次链接 */
    }
    else {
        emit messageSignal(ZBY_LOG("ERROR"), tr("IP:%1:%3  Socket Error<errorCode=%2>").arg(address).arg(-1).arg(port));/* 20210202软著需求改动，发送完结果断开，有结果再次链接 */
    }
}
