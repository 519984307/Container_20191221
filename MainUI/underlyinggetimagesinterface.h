#ifndef UNDERLYINGGETIMAGESINTERFACE_H
#define UNDERLYINGGETIMAGESINTERFACE_H

#define ZBY_LOG(type)  tr("[%1][%2][%3]").arg(type).arg(Q_FUNC_INFO).arg(__LINE__)
#include <QObject>

class UnderlyingGetimagesInterface:public QObject
{
    Q_OBJECT

public:
    virtual ~UnderlyingGetimagesInterface(){}

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
    void pictureStreamSignal(const QByteArray &jpgStream,const int &imgNumber,const QString &imgTime="");

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
    /// \brief playViedoStreamSlot 预览实时视频
    /// \param winID 窗口句柄
    /// \param play 播放状态
    /// 多次实时预览,在LINUX下会出现内存不释放
    ///
    virtual void playStreamSlot(quint64 winID,bool play)=0;

    ///
    /// \brief resizeEventSlot 调整窗口通知动态库刷新窗口
    ///
    virtual void resizeEventSlot()=0;

    ///
    /// \brief releaseResourcesSlot 释放动态库资源
    ///
    virtual void releaseResourcesSlot()=0;

    ///
    /// \brief InitializationSlot 初始化参数
    ///
    virtual void InitializationSlot()=0;
};

#define UnderlyingGetimagesInterfaceIID  "ZBY.ContainerServer.UnderlyingGetimagesInterface/1.0"
Q_DECLARE_INTERFACE(UnderlyingGetimagesInterface,UnderlyingGetimagesInterfaceIID);

#endif // UNDERLYINGGETIMAGESINTERFACE_H
