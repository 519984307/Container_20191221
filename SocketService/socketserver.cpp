#include "socketserver.h"

SocketServer::SocketServer(QObject* parent):QTcpServer (parent)
{
    sendHeart=false;
    pTimerLink=new QTimer (this);
    connect(pTimerLink,&QTimer::timeout,this,&SocketServer::heartbeatSlot);
}

void SocketServer::incomingConnection(qintptr socketID)
{
    if(!pTimerLink->isActive()){
         pTimerLink->start(5000);
    }

    SocketClient* pClient=new SocketClient (this);
    pClient->setSocketDescriptor(socketID);
    clientSocketIDMap.insert(socketID,pClient);

    emit messageSignal(ZBY_LOG("INFO"),tr("New Client in join"));
    emit socketConnectCountSignal(clientSocketIDMap.count());

    connect(pClient,&SocketClient::disconnected,this,&SocketServer::disconnectedSlot);
    connect(pClient,&SocketClient::setClientLandSignal,this,&SocketServer::setClientLandSlot);
    connect(pClient,&SocketClient::getLastResultSignal,this,&SocketServer::getLastResultSlot);
}

void SocketServer::disconnectedSlot()
{
    SocketClient* socket=qobject_cast<SocketClient*>(sender());
    qintptr key1= clientSocketIDMap.key(socket);
    clientSocketIDMap.remove(key1);

    int key2=clientChannelMap.key(key1);
    clientChannelMap.remove(key2,key1);

    emit socketConnectCountSignal(clientSocketIDMap.count());
}

void SocketServer::setClientLandSlot(int land, qintptr socketID)
{
    clientChannelMap.insert(land,socketID);
}

void SocketServer::getLastResultSlot(qintptr socktID)
{
    qDebug()<<socktID;
}

void SocketServer::sendResultSlot(int channel, const QString &result)
{
    //(auto obj:channelCamerMultiMap.values(key)){

    //qintptr key=clientChannelMap.value(channel);
    foreach (auto obj, clientChannelMap.values(channel)) {
        SocketClient* pClient=clientSocketIDMap.value(obj);
        //QString ret=QString("%1\n").arg(result);
        if(pClient!=nullptr){
            pClient->write(result.toLatin1());

            messageSignal(ZBY_LOG("INFO"),tr("Send Data %1:%2:%3").arg(pClient->peerAddress().toString()).arg(pClient->peerPort()).arg(result));
        }
        pClient=nullptr;
    }
}

void SocketServer::heartbeatSlot()
{
    if(sendHeart){
        foreach (auto client, clientSocketIDMap.values()) {
            client->write("[H]");
            messageSignal(ZBY_LOG("INFO"),tr("Send HeartPackets"));
        }
    }
}

void SocketServer::sendHeartPacketSlot(bool state)
{
    sendHeart=state;
}

void SocketServer::releaseResourcesSlot()
{
    if(pTimerLink!=nullptr){
        pTimerLink->stop();
    }
    delete pTimerLink;
    pTimerLink=nullptr;

    foreach (auto client, clientSocketIDMap.values()) {
        client->disconnect();
    }
    this->close();
}

