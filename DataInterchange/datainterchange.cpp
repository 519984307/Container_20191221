#include "datainterchange.h"

DataInterchange::DataInterchange(QObject *parent)
{
    this->setParent(parent);
    isHeartBeat=false;
    isConnected=false;
    pTcpServer=nullptr;
    pTcpClient=nullptr;
    pTimerLinkState=nullptr;
}

DataInterchange::~DataInterchange()
{
    if(pTcpClient != nullptr){
         pTcpClient->abort();
         delete  pTcpClient;
         pTcpClient=nullptr;
    }

    if(pTcpServer!=nullptr){
         pTcpServer->close();
         delete pTcpServer;
         pTcpServer=nullptr;
    }

    if(pTimerLinkState!=nullptr){
        pTimerLinkState->stop();
        delete pTimerLinkState;
        pTimerLinkState=nullptr;
    }
}

void DataInterchange::InitializationParameterSlot(const QString &address, const quint16 &port, const int &serviceType, const int &serviceMode)
{
    this->address=address;
    this->port=port;

    if(serviceMode==1){/* 服务器模式 */
        pTcpServer=new TcpServer (this);
        pTcpServer->setServiceType(serviceType);/* 设置服务模式 */
        /* 日志信息 */
        connect(pTcpServer,&TcpServer::messageSignal,this,&DataInterchange::messageSignal);
        /* 心跳包状态设置 */
        connect(this,&DataInterchange::setHeartbeatPackStateSignal,pTcpServer,&TcpServer::setHeartPacketStateSlot);
        /* 绑定客户端数量 */
        connect(pTcpServer,&TcpServer::connectCountSignal,this,&DataInterchange::connectCountSignal);
        /* 发送识别结果 */
        connect(this,&DataInterchange::toSendDataSignal,pTcpServer,&TcpServer::toSendDataSlot);

        startListenSlot();
    }
    else if (serviceMode==0) {/* 客户端模式 */
        pTcpClient=new QTcpSocket(this);
        pTimerLinkState=new QTimer (this);

        /* 发送识别结果 */
        connect(this,&DataInterchange::toSendDataSignal,this,&DataInterchange::toSendDataSlot);
        /* 心跳包状态设置 */
        connect(this,&DataInterchange::setHeartbeatPackStateSignal,this,&DataInterchange::setHeartPacketStateSlot);

        connect(pTcpClient,&QIODevice::readyRead,this,&DataInterchange::receiveDataSlot);
        connect(pTcpClient,&QAbstractSocket::connected,this,&DataInterchange::connectedSlot);
        connect(pTcpClient,&QAbstractSocket::disconnected,this,&DataInterchange::disconnectedSlot);
        connect(pTcpClient,QOverload<QAbstractSocket::SocketError>::of(&QAbstractSocket::error),this,&DataInterchange::displayErrorSlot);
        connect(pTimerLinkState,&QTimer::timeout,this,&DataInterchange::heartbeatSlot);

        startLinkSlot();
    }
}

void DataInterchange::startLinkSlot()
{
    if(!isConnected){
        pTcpClient->abort();
        pTcpClient->connectToHost(address,port);
    }
}

void DataInterchange::startListenSlot()
{
    if(!pTcpServer->listen(QHostAddress::AnyIPv4,port)){/* 服务器使用本机地址 */
        emit messageSignal(ZBY_LOG("ERROR"),tr("IP:%1 Listen error<errocCode=%2>").arg(QHostAddress::AnyIPv4).arg(pTcpServer->errorString()));
    }
    else {
        emit messageSignal(ZBY_LOG("INFO"),tr("IP:%1 Start listen.").arg(QHostAddress::AnyIPv4));
    }
}

void DataInterchange::heartbeatSlot()
{
    if(isHeartBeat && pTcpClient->isOpen()){
        pTcpClient->write("[H]");/* 心跳包数据 */
    }
}

void DataInterchange::connectedSlot()
{
    isConnected=true;

    if(!pTimerLinkState->isActive()){
        pTimerLinkState->start(15000);
    }

    emit connectCountSignal(1);
    emit messageSignal(ZBY_LOG("INFO"), tr("IP:%1:%2 link successful").arg(address).arg(port));
}

void DataInterchange::receiveDataSlot()
{
    QByteArray buf=pTcpClient->readAll();
}

void DataInterchange::disconnectedSlot()
{
    isConnected=false;
    emit connectCountSignal(-1);
}

void DataInterchange::displayErrorSlot(QAbstractSocket::SocketError socketError)
{
    isConnected=false;

    QTimer::singleShot(15000, this, SLOT(startLinkSlot()));
    emit messageSignal(ZBY_LOG("ERROR"), tr("IP:%1:%3  link error<errorCode=%2>").arg(address).arg(socketError).arg(port));
}

void DataInterchange::setHeartPacketStateSlot(bool state)
{
    isHeartBeat=state;
}

void DataInterchange::toSendDataSlot(int channel_number,const QString &data)
{
    if(pTcpClient->isOpen()){
        pTcpClient->write(data.toLocal8Bit());
    }
}

void DataInterchange::releaseResourcesSlot()
{
    isConnected=false;

    if(pTcpServer!=nullptr){
        pTcpServer->releaseResourcesSlot();
    }
}
