#ifndef GETIMAGES_INTERFACE_H
#define GETIMAGES_INTERFACE_H

#include <QObject>

class GetImagesInterface:public QObject
{
    Q_OBJECT

public:
    virtual ~GetImagesInterface();

public slots:

    ///
    /// \brief initCamerSlots 初始化相机
    /// \param camerIP 相机地址
    /// \param camerPort 相机端口
    ///
    virtual void initCamerSlot(const QString &camerIP, quint16 camerPort)=0;

    ///
    /// \brief putCommandSlots 抓拍指令
    /// \param command 抓拍命令
    ///
    virtual bool putCommandSlot(const QString &command)=0;

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

};

#define GetImagesInterfaceIID "ZBY.ContainerServer.GetImagesInterface/1.0"
Q_DECLARE_INTERFACE(GetImagesInterface,GetImagesInterfaceIID);


#endif // GETIMAGES_INTERFACE_H
