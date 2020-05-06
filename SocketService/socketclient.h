#ifndef SOCKETCLIENT_H
#define SOCKETCLIENT_H

#include "socketservice_global.h"

class SocketClient : public QTcpSocket
{
    Q_OBJECT

public:
    explicit SocketClient(QObject *parent = nullptr);

private:

    ///
    /// \brief land 通道号
    ///
    int land;

signals:

    ///
    /// \brief getLastResultSignal 获取最后一次结果
    /// \param socktID TCPID
    ///
    void getLastResultSignal(qintptr socktID);

    ///
    /// \brief setClientLandSignal 设置通道号
    /// \param land 通道号
    /// \param socktID 客户端ID
    ///
    void setClientLandSignal(int land,qintptr socktID);

public slots:

    ///
    /// \brief readClientSlot 读取客户端数据
    ///
    void readClientSlot();
};

#endif // SOCKETCLIENT_H
