#ifndef SOCKETCLIENT_H
#define SOCKETCLIENT_H

#include "socketservice_global.h"

class SocketClient : public QTcpSocket
{
    Q_OBJECT

public:
    explicit SocketClient(QObject *parent = nullptr);

signals:

    ///
    /// \brief sendClientSignal 发送数据
    /// \param msg
    ///
    void sendClientSignal(const  QString&  msg);

public slots:

    ///
    /// \brief readClientSlot 读取客户端数据
    ///
    void readClientSlot();
};

#endif // SOCKETCLIENT_H
