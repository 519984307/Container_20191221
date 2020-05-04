#include "socketserver.h"

SocketServer::SocketServer(QObject* parent):QTcpServer (parent)
{

}

void SocketServer::incomingConnection(qintptr handle)
{
    qDebug()<<"newCon";
    SocketClient* pClient=new SocketClient (this);
    pClient->setSocketDescriptor(handle);
    clientMap.insert(handle,pClient);
    qDebug()<<handle;

    emit messageSignal(ZBY_LOG("INFO"),"new client join");
    connect(pClient,&SocketClient::disconnected,this,&SocketServer::disconnectedSlot);
}

void SocketServer::disconnectedSlot()
{
    SocketClient* socket=qobject_cast<SocketClient*>(sender());
    int k= static_cast<int>(clientMap.key(socket));
    qDebug()<<k;
    clientMap.remove(k);
    qDebug()<<clientMap.count();
}
