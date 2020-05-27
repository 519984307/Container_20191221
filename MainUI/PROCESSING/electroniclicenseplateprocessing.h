#ifndef ELECTRONICLICENSEPLATEPROCESSING_H
#define ELECTRONICLICENSEPLATEPROCESSING_H

#include <QObject>

class ElectronicLicensePlateProcessing : public QObject
{
    Q_OBJECT
public:
    explicit ElectronicLicensePlateProcessing(QObject *parent = nullptr);

signals:

//    ///
//    /// \brief imageFlowSignal 图片流
//    /// \param img
//    ///
//    void imageFlowSignal(const QString &img);

//    ///
//    /// \brief theVideoStreamSignal 视频流
//    /// \param stream
//    ///
//    void theVideoStreamSignal(QByteArray arrImg);

    ///
    /// \brief resultsTheLicensePlateSignal 车牌结果
    /// \param plate
    ///
    void resultsTheLicensePlateSignal(const QString &plate,const QString &color,const QString &time,QByteArray arrImg);

    ///
    /// \brief initCameraSignal 初始化相机
    /// \param localAddr
    /// \param addr
    /// \param port
    /// \param imgPath
    /// \param imgFormat
    /// \param channel
    ///
    void initCameraSignal(const QString &localAddr,const QString &addr, const int &port, const QString &imgPath, int imgFormat,const int &channel);

//    ///
//    /// \brief equipmentState  设备额在线状态
//    /// \param state
//    ///
//    void equipmentStateSignal( bool state);

//    ///
//    /// \brief simulationCaptureSlot 模拟抓拍
//    ///
//    void simulationCaptureSignal();

//    ///
//    /// \brief openTheVideoSlot 打开视频/关闭视频
//    /// \param play
//    ///
//    void openTheVideoSignal(bool play);

//    ///
//    /// \brief releaseResourcesSlot 释放动态库资源
//    ///
//    void releaseResourcesSignal();
public slots:
};

#endif // ELECTRONICLICENSEPLATEPROCESSING_H
