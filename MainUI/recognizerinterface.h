#ifndef RECOGNIZERINTERFACE_H
#define RECOGNIZERINTERFACE_H

#define ZBY_LOG(type)  tr("[%1][%2][%3]").arg(type).arg(Q_FUNC_INFO).arg(__LINE__)

#include <QObject>

class RecognizerInterface : public QObject
{
    Q_OBJECT

public:
    virtual ~RecognizerInterface() {}

signals:

    ///
    /// \brief messageSignal 日志信息
    /// \param type 日志类型
    /// \param msg 信息体
    ///
    void messageSignal(const QString &type,const QString &msg);

    ///
    /// \brief recognitionResult 识别结果
    /// \param result 识别结果
    /// \param imgNumber 图片编号
    ///
    void recognitionResultSignal(const QString &result,int imgNumber);

public slots:

    ///
    /// \brief pictureStreamSlot 图片流
    /// \param jpgStream 图片流
    /// \param imgNumber 图片编号
    ///
    virtual void pictureStreamSlot(const QByteArray &jpgStream,const int &imgNumber)=0;

    ///
    /// \brief identifyResults 识别图片
    /// \param image  图片名
    /// \param imgNumber 图片编号
    ///
    virtual void identifyImagesSlot(const QString &image,int imgNumber)=0;
};

#define RecognizerInterfaceIID "ZBY.ContainerServer.RecognizerInterface/1.0"
Q_DECLARE_INTERFACE(RecognizerInterface,RecognizerInterfaceIID);

#endif // RECOGNIZERINTERFACE_H
