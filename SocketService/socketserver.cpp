#include "socketserver.h"

SocketServer::SocketServer(QObject* parent):QTcpServer (parent)
{
}

void SocketServer::incomingConnection(qintptr socketID)
{
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
    qintptr key= clientSocketIDMap.key(socket);
    clientSocketIDMap.remove(key);
    clientChannelMap.remove(clientChannelMap.key(key));

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
    qintptr key=clientChannelMap.value(channel,-1);
    SocketClient* pClient=clientSocketIDMap.value(key,nullptr);
    QString ret=QString("%1\n").arg(result);
    if(pClient!=nullptr){
        pClient->write(ret.toLatin1());
    }

    pClient=nullptr;
}
