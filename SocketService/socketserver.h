#ifndef SOCKETSERVER_H
#define SOCKETSERVER_H

#include "socketclient.h"
#include "socketservice_global.h"

#define ZBY_LOG(type)  tr("[%1][%2][%3]").arg(type).arg(Q_FUNC_INFO).arg(__LINE__)

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

    ///
    /// \brief clientMap 客户端列表
    ///
    QMap<qintptr,SocketClient*> clientMap;


signals:

    ///
    /// \brief messageSignal 日志信息
    /// \param type 日志类型
    /// \param msg 信息体
    ///
    void messageSignal(const QString &type,const QString &msg);
};

#endif // SOCKETSERVER_H
