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
    /// \param channel 通道号
    /// \param serviceType 服务类型
    ///
    void  InitializationParameterSignal(const QString& address,const int& port,const int& channel,const int& serviceType);

    ///
    /// \brief socketSendDataSlot 发送数据
    /// \param data 数据体
    ///
    void socketSendDataSignal(const QString& data);

public slots:
};

#endif // SOCKETSERVERPROCESSING_H
