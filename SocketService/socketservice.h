#ifndef SOCKETSERVICE_H
#define SOCKETSERVICE_H

#include "socketservice_global.h"
#include "socketserverinterface.h"
#include "socketserver.h"

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
    /// \brief channel 通道号
    ///
    int channel;

    ///
    /// \brief tcpSocket tcpSocket
    ///
    QTcpSocket *pTcpSocket;

    SocketServer* pTcpServer;

//    ///
//    /// \brief pTcpServer tcpServer
//    ///
//    QTcpServer *pTcpServer;

    ///
    /// \brief pTimerLink 定时检测
    ///
    QTimer *pTimerLink;

//    ///
//    /// \brief clientList 客户端列表
//    ///
//    QList<QTcpSocket*> clientList;

private:

    ///
    /// \brief startLink 链接到服务器,客户端模式
    ///
    void startLink();

    ///
    /// \brief startListen 开始监听,服务器模式
    ///
    void startListen();

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
    /// \brief newClientConnectSlot 客户端接入
    ///
    void newClientConnectSlot();

public:

    ///
    /// \brief InitializationParameterSlot 初始化参数
    /// \param address 地址
    /// \param port 端口
    /// \param channel 通道号
    /// \param serviceType 服务类型
    ///
    void  InitializationParameterSlot(const QString& address,const int& port,const int& channel,const int& serviceType)Q_DECL_OVERRIDE;

    ///
    /// \brief socketSendDataSlot 发送数据
    /// \param data 数据体
    ///
    void socketSendDataSlot(const QString& data)Q_DECL_OVERRIDE;  
};

#endif // SOCKETSERVICE_H
