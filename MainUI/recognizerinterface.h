#ifndef RECOGNIZERINTERFACE_H
#define RECOGNIZERINTERFACE_H

#define ZBY_LOG(type)  tr("ZBY_LOG_%1(Func[%2](Line[%3]))").arg(type).arg(Q_FUNC_INFO).arg(__LINE__)

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
    ///
    virtual void identifyResults(const QString &image)=0;

    ///
    /// \brief recognitionResultSlot 识别结果
    /// \param result
    ///
    virtual void recognitionResultSlot(const QString &result)=0;
};

#define RecognizerInterfaceIID "ZBY.ContainerServer.RecognizerInterface/1.0"
Q_DECLARE_INTERFACE(RecognizerInterface,RecognizerInterfaceIID);

#endif // RECOGNIZERINTERFACE_H
