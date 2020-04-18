#ifndef SOCKETSERVERINTERFACE_H
#define SOCKETSERVERINTERFACE_H

#define ZBY_LOG(type)  tr("[%1][%2][%3]").arg(type).arg(Q_FUNC_INFO).arg(__LINE__)

#include <QObject>

class SocketServerInterface : public QObject
{
    Q_OBJECT

public:
    virtual ~SocketServerInterface(){}

signals:

    ///
    /// \brief messageSignal 日志信息
    /// \param type 日志类型
    /// \param msg 信息体
    ///
    void messageSignal(const QString &type,const QString &msg);

    ///
    /// \brief socketLinkStateSingal TCP链接状态
    /// \param address 地址
    /// \param state 状态
    ///
    void socketLinkStateSingal(const QString& address,bool state);

public slots:

    ///
    /// \brief InitializationParameterSlot 初始化参数
    /// \param address 地址
    /// \param port 端口
    /// \param reconnection 是否自动重连
    ///
    virtual void  InitializationParameterSlot(const QString& address,const int& port,bool reconnection)=0;

    ///
    /// \brief socketSendDataSlot 发送数据
    /// \param data 数据体
    ///
    virtual void socketSendDataSlot(const QString& data)=0;
};

#define SocketServerInterfaceIID "ZBY.ContainerServer.SocketServerInterface/1.0"
Q_DECLARE_INTERFACE(SocketServerInterface,SocketServerInterfaceIID);

#endif // SOCKETSERVERINTERFACE_H
