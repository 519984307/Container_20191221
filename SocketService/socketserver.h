#ifndef SOCKETSERVER_H
#define SOCKETSERVER_H

#include "socketclient.h"
#include "socketservice_global.h"

class SocketServer : public QTcpServer
{
    Q_OBJECT

public:
    SocketServer(QObject* parent=nullptr);

private:

    ///
    /// \brief incomingConnection 重写客户端接入
    /// \param handle
    ///
    void incomingConnection(qintptr handle);

public slots:

    ///
    /// \brief disconnectedSlot 客户端断开信号
    ///
    void disconnectedSlot();

private:

    QMap<qintptr,SocketClient*> clientMap;
};

#endif // SOCKETSERVER_H
