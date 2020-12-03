#ifndef LICENSEPLATEINTERFACE_H
#define LICENSEPLATEINTERFACE_H

#include <QObject>

class LicensePlateInterface : public QObject
{
    Q_OBJECT
public:
    ~ LicensePlateInterface(){}

signals:

    ///
    /// \brief messageSignal 日志信息
    /// \param type 日志类型
    /// \param msg 信息体
    ///
    void messageSignal(const QString &type,const QString &msg);

    ///
    /// \brief imageFlowSignal 图片流
    /// \param img
    ///
    void imageFlowSignal(QByteArray img);

    ///
    /// \brief theVideoStreamSignal 视频流
    /// \param stream
    ///
    void theVideoStreamSignal(QByteArray arrImg);

    ///
    /// \brief resultsTheLicensePlateSignal 车牌结果
    /// \param plate
    ///
    void resultsTheLicensePlateSignal(const QString &plate,const QString &color,const QString &time,QByteArray arrImg);

    ///
    /// \brief equipmentState  设备额在线状态
    /// \param state
    ///
    void equipmentStateSignal( bool state);

public slots:

    ///
    /// \brief initCameraSlot 初始化相机
    /// \param localAddr 本机地址(用户绑定网卡)
    /// \param addr 相机地址
    /// \param port 端口
    /// \param imgPath 图片地址
    /// \param channel 通道号
    ///
    virtual void initCameraSlot(const QString &localAddr,const QString &addr, const int &port, const QString &imgPath, int imgFormat,const int &channel)=0;

    ///
    /// \brief simulationCaptureSlot 模拟抓拍
    ///
    virtual void simulationCaptureSlot()=0;

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
    /// \brief openTheVideoSlot 打开视频/关闭视频
    /// \param play
    ///
    virtual void openTheVideoSlot(bool play,quint64 winID=0)=0;

    ///
    /// \brief releaseResourcesSlot 释放动态库资源
    ///
    virtual void releaseResourcesSlot()=0;


    /*****************************
    * @brief:海康相机其它实现
    ******************************/
public slots:
    ///
    /// \brief slot_pictureStream 分发图片数据
    /// \param ID
    /// \param arrJpg
    ///
    virtual void slot_pictureStream(int ID,QByteArray arrJpg)=0;

    ///
    /// \brief slot_setCameraID 设置通道登录相机ID
    /// \param ID 登录ID
    /// \param cameraIP 相机地址
    ///
    virtual void slot_setCameraID(int ID,QString cameraIP)=0;

    ///
    /// \brief slot_resultsTheLicensePlate 车牌结果
    /// \param plate
    ///
    virtual void slot_resultsTheLicensePlate(int ID,const QString &plate,const QString &color,const QString &time,QByteArray arrImg)=0;

    ///
    /// \brief slot_equipmentState  设备额在线状态
    /// \param state
    ///
    virtual void slot_equipmentState(int ID, bool state)=0;

signals:

    ///
    /// \brief signal_initCamera 初始化相机
    /// \param localAddr 本机地址(用户绑定网卡)
    /// \param addr 地址
    /// \param port 端口
    /// \param user 用户
    /// \param pow  密码
    ///
    void signal_initCamera(const QString &localAddr, const QString &addr, const int &port, const QString &user, const QString &pow);

    ///
    /// \brief signal_openTheVideo 打开视频/关闭视频
    /// \param play
    ///
    void signal_openTheVideo(int ID, bool play,quint64 winID);

    ///
    /// \brief signal_simulationCapture 模拟抓拍
    ///
    void signal_simulationCapture(int ID);


    ///
    /// \brief signal_liftingElectronicRailing 抬杆/落杆
    ///
    void signal_liftingElectronicRailing(bool gate);

    ///
    /// \brief signal_transparentTransmission485 透明传输
    /// \param dmsg
    ///
    void signal_transparentTransmission485(const QString &msg);
    /*****************************
    * @brief:海康相机其它实现
    ******************************/
};

#define LicensePlateInterfaceIID "ZBY.ContainerServer.LicensePlateInterface/1.0"
Q_DECLARE_INTERFACE(LicensePlateInterface,LicensePlateInterfaceIID);

#endif // LICENSEPLATEINTERFACE_H
