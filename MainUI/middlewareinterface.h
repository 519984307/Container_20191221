#ifndef IMIDDLEWARE_H
#define IMIDDLEWARE_H

#include <QObject>

class IMiddleware : public QObject
{
    Q_OBJECT
public:
    ~ IMiddleware(){}

    ///
    /// \brief InterfaceType 插件类型，多插件调用统一接口
    /// \return
    ///
    virtual QString InterfaceType()=0;

signals:

    ///
    /// \brief messageSignal 日志信息
    /// \param type 日志类型
    /// \param msg 信息体
    ///
    void messageSignal(const QString &type,const QString &msg);

    ///
    /// \brief signal_message 分发日志信息
    /// \param ID
    /// \param meg
    ///
    void signal_message(int ID,QString meg);

    ///
    /// \brief signal_pictureStream 分发图片数据
    /// \param ID
    /// \param arrJpg
    ///
    void signal_pictureStream(int ID,QByteArray arrJpg);

    ///
    /// \brief signal_setCameraID 设置通道登录相机ID
    /// \param ID 登录ID
    /// \param cameraIP 相机地址
    ///
    void signal_setCameraID(int ID,QString cameraIP);

    ///
    /// \brief resultsTheLicensePlateSignal 车牌结果
    /// \param plate
    ///
    void resultsTheLicensePlateSignal(int ID,const QString &plate,const QString &color,const QString &time,QByteArray arrImg);

    ///
    /// \brief equipmentState  设备额在线状态
    /// \param state
    ///
    void equipmentStateSignal(int ID, bool state);

public slots:

    ///
    /// \brief initCameraSlot 初始化相机
    /// \param localAddr 本机地址(用户绑定网卡)
    /// \param addr 地址
    /// \param port 端口
    /// \param user 用户
    /// \param pow  密码
    ///
    virtual void initCameraSlot(const QString &localAddr, const QString &addr, const int &port, const QString &user, const QString &pow)=0;

    ///
    /// \brief openTheVideoSlot 打开视频/关闭视频
    /// \param play
    ///
    virtual void openTheVideoSlot(int ID, bool play,quint64 winID)=0;

    ///
    /// \brief simulationCaptureSlot 模拟抓拍
    ///
    virtual void simulationCaptureSlot(int ID)=0;

    ///
    /// \brief liftingElectronicRailingSlot 抬杆/落杆
    ///
    virtual void liftingElectronicRailingSlot(bool gate)=0;

    ///
    /// \brief transparentTransmission485Slot 透明传输
    /// \param dmsg
    ///
    virtual void transparentTransmission485Slot(const QString &msg)=0;

    ///
    /// \brief releaseResourcesSlot 释放动态库资源
    ///
    virtual void releaseResourcesSlot()=0;
};

#define IMiddlewareIID "ZBY.ContainerServer.IMiddleware/1.2.1"
Q_DECLARE_INTERFACE(IMiddleware,IMiddlewareIID);

#endif // IMIDDLEWARE_H
