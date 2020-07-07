#include "socketserver.h"

SocketServer::SocketServer(QObject* parent):QTcpServer (parent)
{
    sendHeart=false;
    pTimerLink=new QTimer (this);
    connect(pTimerLink,&QTimer::timeout,this,&SocketServer::heartbeatSlot);
}

void SocketServer::setServiceType(int serviceType)
{
    this->serviceType=serviceType;
}

void SocketServer::incomingConnection(qintptr socketID)
{
    if(!pTimerLink->isActive()){
         pTimerLink->start(15000);
    }

    SocketClient* pClient=new SocketClient (this);
    pClient->setSocketDescriptor(socketID);
    clientSocketIDMap.insert(socketID,pClient);

    emit messageSignal(ZBY_LOG("INFO"),tr("New Client in join IP:%1 PORT:%2").arg(pClient->peerAddress().toString()).arg(pClient->peerPort()));
    //emit socketConnectCountSignal(clientSocketIDMap.count());
    emit socketConnectCountSignal(1);

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

    emit messageSignal(ZBY_LOG("INFO"),tr("Client offline IP:%1 PORT:%2").arg(socket->peerAddress().toString()).arg(socket->peerPort()));
    //emit socketConnectCountSignal(clientSocketIDMap.count());
    emit socketConnectCountSignal(-1);
}

void SocketServer::setClientLandSlot(int land, qintptr socketID)
{
    clientChannelMap.insert(land,socketID);
}

void SocketServer::getLastResultSlot(qintptr socktID)
{
    SocketClient* pClient= clientSocketIDMap.value(socktID);
    //QString ret=QString("%1\n").arg(result);
    if(pClient!=nullptr){
        pClient ->write(resultOfMemory.toLocal8Bit());
        messageSignal(ZBY_LOG("INFO"),tr("Send Data %1:%2:%3").arg(pClient->peerAddress().toString()).arg(pClient->peerPort()).arg(resultOfMemory));
    }
    pClient=nullptr;
}

void SocketServer::sendResultSlot(int channel, const QString &result)
{
    //QString ret=QString("%1\n\r").arg(result);
    resultOfMemory=result;/* 存储结果，用于主动获取 */

    if(serviceType==1){/* 多模发送到所有链接的客户端 */
        foreach (auto obj, clientSocketIDMap.values()) {
            obj->write(result.toLocal8Bit());
        }
    }
    else if (serviceType==0) {/* 单模只发送对应通道客户端 */
        foreach (auto obj, clientChannelMap.values(channel)) {
            SocketClient* pClient=clientSocketIDMap.value(obj);
            //QString ret=QString("%1\n").arg(result);
            if(pClient!=nullptr){
                pClient->write(result.toLocal8Bit());
                messageSignal(ZBY_LOG("INFO"),tr("Send Data %1:%2:%3").arg(pClient->peerAddress().toString()).arg(pClient->peerPort()).arg(result));
            }
            pClient=nullptr;
        }
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

    clientChannelMap.clear();
    clientSocketIDMap.clear();

    this->close();
}

