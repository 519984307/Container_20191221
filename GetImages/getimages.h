#ifndef GETIMAGES_H
#define GETIMAGES_H

#include "getimages_interface.h"
#include "getimages_global.h"

class GETIMAGESSHARED_EXPORT GetImages:public GetImagesInterface
{
    Q_OBJECT
    Q_INTERFACES(GetImagesInterface)
    Q_PLUGIN_METADATA(IID  GetImagesInterfaceIID)

public:
    GetImages(QObject *parent = nullptr);
    ~GetImages()Q_DECL_OVERRIDE;

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

private:

    ///
    /// \brief tcpSocket Socket
    ///
    QTcpSocket *tcpSocket;

    ///
    /// \brief pTimerLinkCamer 定时检测
    ///
    QTimer *pTimerLinkCamer;

    ///
    /// \brief camerIP 相机地址
    ///
    QString camerIP;

    ///
    /// \brief camerPort 相机端口
    ///
    quint16 camerPort;

    ///
    /// \brief jpgStream 图片流
    ///
    QByteArray jpgStream;

private:

    ///
    /// \brief startLinkCamer 连接相机
    ///
    void startLinkCamer();

public:

    void initCamerSlot(const QString &camerIP, quint16 camerPort) Q_DECL_OVERRIDE;

    bool putCommandSlot(const QString &command) Q_DECL_OVERRIDE;
};

#endif // GETIMAGES_H
