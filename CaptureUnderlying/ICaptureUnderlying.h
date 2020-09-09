#ifndef ICAPTUREUNDERLYING_H
#define ICAPTUREUNDERLYING_H

#define ZBY_LOG(type)  tr("[%1][%2][%3]").arg(type).arg(Q_FUNC_INFO).arg(__LINE__)

#include <QObject>

class ICaptureUnderlying : public QObject
{
    Q_OBJECT
public:
    virtual ~ICaptureUnderlying(){}

signals:

    ///
    /// \brief camerStateSingals 相机连接状态信号
    /// \param camerIP 相机地址
    /// \param state 相机连接状态
    ///
    void camerStateSingal(const QString &camerIP,bool state,const QString& alias);

    ///
    /// \brief pictureStreamSignals 图片流信号
    /// \param jpgStream 图片流
    /// \param imgNumber 图片编号
    /// \param imgTime 图片时间戳
    ///
    void pictureStreamSignal(const QByteArray &jpgStream,const int &imgNumber=0,const QString &imgTime="");

    ///
    /// \brief messageSignal 日志信息
    /// \param type 日志类型
    /// \param msg 信息体
    ///
    void messageSignal(const QString &type,const QString &msg);

public slots:

    ///
    /// \brief initCamerSlots 初始化相机
    /// \param camerIP 相机地址
    /// \param camerPort 相机端口
    /// \param 用户名
    /// \param 密码
    ///
    virtual void initCamerSlot(const QString &camerIP,const int &camerPort,const QString &CamerUser,const QString &CamerPow,const QString& alias)=0;

    ///
    /// \brief putCommandSlots 抓取图片
    /// \param command 图片编号
    /// \param imgTime 时间戳
    ///
    virtual bool putCommandSlot(const int &imgNumber,const QString &imgTime)=0;

    ///
    /// \brief releaseResourcesSlot 释放动态库资源
    ///
    virtual void releaseResourcesSlot()=0;

    ///
    /// \brief InitializationSlot 初始化参数
    ///
    virtual void InitializationSlot()=0;
};

#define ICaptureUnderlyingIID  "ZBY.ContainerServer.ICaptureUnderlying/1.0"
Q_DECLARE_INTERFACE(ICaptureUnderlying,ICaptureUnderlyingIID);

#endif // ICAPTUREUNDERLYING_H
