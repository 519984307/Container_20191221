#ifndef GETIMAGESINTERFACE_H
#define GETIMAGESINTERFACE_H

#define ZBY_LOG(type)  tr("ZBY_LOG_%1(Func[%2](Line[%3]))").arg(type).arg(Q_FUNC_INFO).arg(__LINE__)

#include <QObject>

class GetImagesInterface:public QObject
{
    Q_OBJECT

public:
    virtual ~GetImagesInterface(){}

signals:

    ///
    /// \brief camerStateSingals 相机连接状态信号
    /// \param camerIP 相机地址
    /// \param state 相机连接状态
    ///
    void camerStateSingal(const QString &camerIP,bool state);

    ///
    /// \brief pictureStreamSignals 图片流信号
    /// \param jpgStream 图片流
    /// \param imgNumber 图片编号
    ///
    void pictureStreamSignal(const QByteArray &jpgStream,const int &imgNumber);

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
    virtual void initCamerSlot(const QString &camerIP, quint16 camerPort,const QString &CamerUser,const QString &CamerPow)=0;

    ///
    /// \brief putCommandSlots 抓取图片
    /// \param command 图片编号
    ///
    virtual bool putCommandSlot(const int &imgNumber)=0;

    ///
    /// \brief playViedoStreamSlot 预览实时视频
    /// \param winID 窗口句柄
    /// \param play 播放状态
    /// 多次实时预览,在LINUX下会出现内存不释放
    ///
    virtual void playStreamSlot(uint winID,bool play)=0;

    ///
    /// \brief resizeEventSlot 调整窗口通知动态库刷新窗口
    ///
    virtual void resizeEventSlot()=0;

    ///
    /// \brief releaseResourcesSlot 释放动态库资源
    ///
    virtual void releaseResourcesSlot()=0;
};

#define GetImagesInterfaceIID "ZBY.ContainerServer.GetImagesInterface/1.0"
Q_DECLARE_INTERFACE(GetImagesInterface,GetImagesInterfaceIID);

#endif // GETIMAGESINTERFACE_H
