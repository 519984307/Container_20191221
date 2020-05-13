#ifndef CAPTUREUNDERLYING_H
#define CAPTUREUNDERLYING_H

#include "captureunderlying_global.h"
#include "ICaptureUnderlying.h"
#include "putcommand.h"

class CAPTUREUNDERLYINGSHARED_EXPORT CaptureUnderlying:public ICaptureUnderlying
{
    Q_OBJECT
    Q_INTERFACES(ICaptureUnderlying)
    Q_PLUGIN_METADATA(IID  ICaptureUnderlyingIID)

public:
    CaptureUnderlying(QObject* parent=nullptr);
    ~CaptureUnderlying()Q_DECL_OVERRIDE;

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
    /// \brief startLinkCamer 连接相机
    ///
    void startLinkCamer();

private:

    PutCommand* pPutCommand;

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
    int camerPort;

    ///
    /// \brief alias 相机名
    ///
    QString alias;

    ///
    /// \brief jpgStream 图片流
    ///
    QByteArray jpgStream;

    ///
    /// \brief imgNumber 图片编号
    ///
    int imgNumber;

    ///
    /// \brief imgTime 抓图时间戳
    ///
    QString imgTime;

public:

    ///
    /// \brief initCamerSlot 初始化相机参数
    /// \param camerIP 地址
    /// \param camerPort 端口
    /// \param CamerUser 用户名
    /// \param CamerPow 密码
    ///
    void initCamerSlot(const QString &camerIP,const int &camerPort,const QString &CamerUser,const QString &CamerPow,const QString& alias) Q_DECL_OVERRIDE;

    ///
    /// \brief putCommandSlots 抓取图片
    /// \param command 图片编号
    ///
    bool putCommandSlot(const int &imgNumber,const QString &imgTime)Q_DECL_OVERRIDE;

    ///
    /// \brief closeStream 释放动态库资源
    ///
    void releaseResourcesSlot()Q_DECL_OVERRIDE;

    ///
    /// \brief InitializationSlot 初始化参数
    ///
    void InitializationSlot()Q_DECL_OVERRIDE;
};

#endif // CAPTUREUNDERLYING_H
