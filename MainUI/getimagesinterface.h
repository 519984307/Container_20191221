#ifndef GETIMAGESINTERFACE_H
#define GETIMAGESINTERFACE_H

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
    /// \param camerIP 相机地址
    ///
    void pictureStreamSignal(const QByteArray &jpgStream,const QString &camerIP);

    ///
    /// \brief message 日志信号
    /// \param msg 信息体
    ///
    void messageSignal(const QString &msg);

public slots:

    ///
    /// \brief initCamerSlots 初始化相机
    /// \param camerIP 相机地址
    /// \param camerPort 相机端口
    ///
    virtual void initCamerSlot(const QString &camerIP, quint16 camerPort,const QString &CamerUser,const QString &CamerPow)=0;

    ///
    /// \brief putCommandSlots 抓拍指令
    /// \param command 抓拍命令
    ///
    virtual bool putCommandSlot(const QString &command)=0;

    ///
    /// \brief playViedoStreamSlot 预览实时视频
    /// \param winID 窗口句柄
    /// \param play 播放状态
    ///
    virtual void playStreamSlot(uint winID,bool play)=0;

    ///
    /// \brief resizeEventSlot 调整窗口通知动态库
    ///
    virtual void resizeEventSlot()=0;

};

#define GetImagesInterfaceIID "ZBY.ContainerServer.GetImagesInterface/1.0"
Q_DECLARE_INTERFACE(GetImagesInterface,GetImagesInterfaceIID);

#endif // GETIMAGESINTERFACE_H
