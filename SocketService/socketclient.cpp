#include "socketclient.h"

SocketClient::SocketClient(QObject *parent)
{
    this->setParent(parent);

    connect(this,SIGNAL(readyRead()),this,SLOT(readClientSlot()));
    connect(this,SIGNAL(disconnected()),this,SLOT(deleteLater()));
}

void SocketClient::readClientSlot()
{
    /* 读取客户端数据 */
    QByteArray buf=readAll();
    qDebug()<<buf;
}
