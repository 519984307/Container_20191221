#include "tcpserver.h"

TcpServer::TcpServer(QObject *parent):QTcpServer (parent)
{    
    this->setParent(parent);
}

void TcpServer::InitializationParameter()
{
    pClient=nullptr;
    isHeartPack=false;
    pTimerSendHeartPack=new QTimer (this);
    connect(pTimerSendHeartPack,&QTimer::timeout,this,&TcpServer::heartbeatSlot);

    if(!pTimerSendHeartPack->isActive()){
        pTimerSendHeartPack->start(15000);
    }
}

void TcpServer::setServiceType(int serviceType)
{
    this->serviceType=serviceType;
}

void TcpServer::incomingConnection(qintptr socketID)
{
    TcpClient *pClient=new TcpClient (this);
    pClient->setSocketDescriptor(socketID);
    clientSocketIdMap.insert(socketID,pClient);

    emit connectCountSignal(1);
    emit messageSignal(ZBY_LOG("INFO"),tr("New client in join<IP:%1 PORT:%2>").arg(pClient->peerAddress().toString()).arg(pClient->peerPort()));

    connect(pClient,&TcpClient::disconnected,this,&TcpServer::disconnectedSlot);
    connect(pClient,&TcpClient::setClientChannelNumberSignal,this,&TcpServer::setClientChannelNumberSlot);
    connect(pClient,&TcpClient::getLastResultSignal,this,&TcpServer::getLastResultSlot);
}

void TcpServer::disconnectedSlot()
{
    TcpClient *pClient=qobject_cast<TcpClient*>(sender());

    emit connectCountSignal(-1);
    emit messageSignal(ZBY_LOG("INFO"),tr("Client offline <IP:%1 PORT:%2>").arg(pClient->peerAddress().toString()).arg(pClient->peerPort()));

    qintptr socketID= clientSocketIdMap.key(pClient);
    clientSocketIdMap.remove(socketID);
    clientChannelMap.remove(clientChannelMap.key(socketID));

    delete pClient;
    pClient=nullptr;
}

void TcpServer::setClientChannelNumberSlot(int channel_number, qintptr socketID)
{
    clientChannelMap.insert(channel_number,socketID);
}

void TcpServer::getLastResultSlot(qintptr socktID)
{
    emit messageSignal(ZBY_LOG("INFO"),tr("Get the last result"));
}

void TcpServer::toSendDataSlot(int channel_number, const QString &result)
{
    if(serviceType==1){/* 多模发送到所有链接的客户端 */
        foreach (auto tcp, clientSocketIdMap.values()) {
            tcp->write(result.toLocal8Bit());
        }
    }
    else if (serviceType==0) {/* 单模只发送对应通道客户端 */
        foreach (auto tcp, clientChannelMap.values(channel_number)) {
            pClient=clientSocketIdMap.value(tcp,nullptr);
            if(pClient!=nullptr){
                pClient->write(result.toLocal8Bit());
                messageSignal(ZBY_LOG("INFO"),tr("Send Data %1:%2:%3").arg(pClient->peerAddress().toString()).arg(pClient->peerPort()).arg(result));
            }
            pClient=nullptr;
        }
    }
}

void TcpServer::heartbeatSlot()
{
    if(isHeartPack){
        foreach (auto client, clientSocketIdMap.values()) {
            client->write("[H]");
            messageSignal(ZBY_LOG("INFO"),tr("Send HeartPackets"));
        }
    }
}

void TcpServer::setHeartPacketStateSlot(bool state)
{
    isHeartPack=state;
}

void TcpServer::releaseResourcesSlot()
{
    this->close();

    if(pTimerSendHeartPack!=nullptr){
        pTimerSendHeartPack->stop();
        delete pTimerSendHeartPack;
        pTimerSendHeartPack=nullptr;
    }

    foreach (auto tcp, clientSocketIdMap.values()) {
        tcp->disconnected();
        delete tcp;
        tcp=nullptr;
    }

    clientChannelMap.clear();
    clientSocketIdMap.clear();

    delete pClient;
    pClient=nullptr;
}
