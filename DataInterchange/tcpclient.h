#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#define ZBY_LOG(type)  tr("[%1][%2][%3]").arg(type).arg(Q_FUNC_INFO).arg(__LINE__)

#include "datainterchange_global.h"

class TcpClient : public QTcpSocket
{
    Q_OBJECT

public:
    explicit TcpClient(QObject *parent=nullptr);

private:

    ///
    /// \brief channel_number 通道号
    ///
    int channel_number;

signals:

    ///
    /// \brief getLastResultSignal 获取最后一次结果
    /// \param socktID
    ///
    void getLastResultSignal(qintptr socktID);

    ///
    /// \brief setClientChannelNumberSignal 设置通道号
    /// \param channel_number 通道号
    /// \param socktID 客户端ID
    ///
    void setClientChannelNumberSignal(int channel_number,qintptr socktID);

public slots:

    ///
    /// \brief receiveClientDataSlot 接收数据
    ///
    void receiveDataSlot();
};

#endif // TCPCLIENT_H
