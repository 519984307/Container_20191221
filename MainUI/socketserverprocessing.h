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
    /// \param heartBeat 心跳包
    ///
    void  InitializationParameterSignal(const QString& address,const quint16& port,const int& serviceType,const int& heartBeat);

    ///
    /// \brief socketSendDataSlot 发送数据
    /// \param data 数据体
    ///
    void socketSendDataSignal(const QString& data);

public slots:
};

#endif // SOCKETSERVERPROCESSING_H
