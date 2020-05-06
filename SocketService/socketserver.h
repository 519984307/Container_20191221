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
    void incomingConnection(qintptr socketID);

public slots:

    ///
    /// \brief disconnectedSlot 客户端断开信号,从客户端列表删除断开的客户端
    ///
    void disconnectedSlot();

    ///
    /// \brief setClientLandSlot 设置通道号
    /// \param land 通道号
    /// \param socktID 客户端ID
    ///
    void setClientLandSlot(int land, qintptr socketID);

    ///
    /// \brief getLastResultSlot 获取最后一次结果
    /// \param socktID TCPID
    ///
    void getLastResultSlot(qintptr socktID);

    ///
    /// \brief sendResultSlot 发送识别结果
    /// \param channel 通道号
    /// \param result 识别结果
    ///
    void sendResultSlot(int channel,const QString& result);

private:

    ///
    /// \brief clientSocketIDMap 客户端字典
    ///
    QMap<qintptr,SocketClient*> clientSocketIDMap;

    ///
    /// \brief clientChannelMap 通道字典
    ///
    QMap<int,qintptr> clientChannelMap;


signals:

    ///
    /// \brief messageSignal 日志信息
    /// \param type 日志类型
    /// \param msg 信息体
    ///
    void messageSignal(const QString &type,const QString &msg);

    ///
    /// \brief socketConnectCount socket链接数量
    /// \param count
    ///
    void socketConnectCountSignal(int count);
};

#endif // SOCKETSERVER_H
