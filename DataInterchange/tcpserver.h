#ifndef TCPSERVER_H
#define TCPSERVER_H

#define ZBY_LOG(type)  tr("[%1][%2][%3]").arg(type).arg(Q_FUNC_INFO).arg(__LINE__)

#include "datainterchange_global.h"
#include "tcpclient.h"

class TcpServer : public QTcpServer
{
    Q_OBJECT

public:
    explicit TcpServer(QObject *parent=nullptr);

    ///
    /// \brief InitializationParameter 初始化参数
    ///
    void InitializationParameter();

    ///
    /// \brief setServiceType 设置TCP模式
    /// \param serviceType
    ///
    void setServiceType(int serviceType);

    ///
    /// \brief incomingConnection 重写客户端接入
    /// \param handle
    ///
    void incomingConnection(qintptr socketID);

private:

    ///
    /// \brief serviceType TCP模式
    ///
    int serviceType;

    ///
    /// \brief clientSocketIdMap 客户端字典
    ///
    QMap<qintptr,TcpClient*> clientSocketIdMap;

    ///
    /// \brief clientChannelMap 通道字典
    ///
    QMultiMap<int,qintptr> clientChannelMap;

    ///
    /// \brief pTimerSendHeartPack 定时发送心跳包
    ///
    QTimer *pTimerSendHeartPack;

    ///
    /// \brief isHeartPack 发送心跳包状态
    ///
    bool isHeartPack;

    ///
    /// \brief pClient 客户端对象
    ///
    TcpClient *pClient;

public slots:

    ///
    /// \brief disconnectedSlot 客户端断开信号(从客户端列表删除断开的客户端)
    ///
    void disconnectedSlot();

    ///
    /// \brief setClientChannelNumberSlot 设置通道号
    /// \param channel_number 通道号
    /// \param socktID 客户端ID
    ///
    void setClientChannelNumberSlot(int channel_number, qintptr socketID);

    ///
    /// \brief getLastResultSlot 获取最后一次结果
    /// \param socktID
    ///
    void getLastResultSlot(qintptr socktID);

    ///
    /// \brief toSendDataSlot 发送识别结果
    /// \param channel_number 通道号
    /// \param result 识别结果
    ///
    void toSendDataSlot(int channel_number,const QString& result);

    ///
    /// \brief heartbeatSlot 心跳检测
    ///
    void heartbeatSlot();

    ///
    /// \brief setHeartPacketStateSlot 设置心跳包状态
    /// \param state
    ///
    void setHeartPacketStateSlot(bool state);

    ///
    /// \brief releaseResourcesSlot 释放动资源
    ///
    void releaseResourcesSlot();

signals:

    ///
    /// \brief messageSignal 日志信息
    /// \param type 日志类型
    /// \param msg 信息体
    ///
    void messageSignal(const QString &type,const QString &msg);

    ///
    /// \brief connectCountSignal 链接数量
    /// \param count
    ///
    void connectCountSignal(int count);
};

#endif // TCPSERVER_H
