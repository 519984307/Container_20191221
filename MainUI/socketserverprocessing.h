#ifndef SOCKETSERVERPROCESSING_H
#define SOCKETSERVERPROCESSING_H

#include <QObject>

class SocketServerProcessing : public QObject
{
    Q_OBJECT
public:
    explicit SocketServerProcessing(QObject *parent = nullptr);

signals:

    ///
    /// \brief InitializationParameterSignal 初始化参数
    /// \param address 地址
    /// \param port 端口
    /// \param serviceType 服务类型
    /// \param heartBeat 心跳包状态
    /// \param serviceMode 服务模式
    ///
    void  InitializationParameterSignal(const QString& address,const quint16& port,const int& serviceType,const int& serviceMode,const int& heartBeat);

    ///
    /// \brief socketSendDataSlot 发送数据
    /// \param data 数据体
    ///
    void socketSendDataSignal(const QString& data);

    ///
    /// \brief socketConnectCount socket链接数量
    /// \param count
    ///
    void socketConnectCountSignal(int count);

    ///
    /// \brief sendResultSlot 发送识别结果
    /// \param channel 通道号
    /// \param result 识别结果
    ///
    void sendResultSignal(int channel,const QString& result);

    ///
    /// \brief sendHeartPacketSignal 心跳包状态
    /// \param state
    ///
    void sendHeartPacketSignal(bool state);

public slots:
};

#endif // SOCKETSERVERPROCESSING_H
