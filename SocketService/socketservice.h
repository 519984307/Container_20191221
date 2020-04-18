#ifndef SOCKETSERVICE_H
#define SOCKETSERVICE_H

#include "socketservice_global.h"
#include "socketserverinterface.h"

class SOCKETSERVICESHARED_EXPORT SocketService:public SocketServerInterface
{
    Q_OBJECT
    Q_INTERFACES(SocketServerInterface)
    Q_PLUGIN_METADATA(IID SocketServerInterfaceIID)

public:
    SocketService(QObject* parent=nullptr);
    ~SocketService()Q_DECL_OVERRIDE;

private:

    ///
    /// \brief address 地址
    ///
    QString address;

    ///
    /// \brief port 端口
    ///
    int port;

    ///
    /// \brief tcpSocket Socket
    ///
    QTcpSocket *tcpSocket;

    ///
    /// \brief pTimerLinkCamer 定时检测
    ///
    QTimer *pTimerLinkCamer;

private:

    ///
    /// \brief startLinkCamer 链接tcp
    ///
    void startLinkCamer();

private slots:

    ///
    /// \brief connected 链接成功
    ///
    void connected();

    ///
    /// \brief readFortune 接收数据
    ///
    void readFortune();

    ///
    /// \brief disconnected 链接断开
    ///
    void disconnected();

    ///
    /// \brief displayError 链接错误
    /// \param socketError 链接状态码
    ///
    void displayError(QAbstractSocket::SocketError socketError);

    ///
    /// \brief stateChanged 链接状态
    /// \param socketState 状态码
    ///
    void stateChanged(QAbstractSocket::SocketState socketState);

public:

    ///
    /// \brief InitializationParameterSlot 初始化参数
    /// \param address 地址
    /// \param port 端口
    /// \param reconnection 是否自动重连
    ///
    void  InitializationParameterSlot(const QString& address,const int& port,bool reconnection)Q_DECL_OVERRIDE;

    ///
    /// \brief socketSendDataSlot 发送数据
    /// \param data 数据体
    ///
    void socketSendDataSlot(const QString& data)Q_DECL_OVERRIDE;
};

#endif // SOCKETSERVICE_H
