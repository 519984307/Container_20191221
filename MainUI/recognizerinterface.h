#ifndef RECOGNIZERINTERFACE_H
#define RECOGNIZERINTERFACE_H

#define ZBY_LOG(type)  tr("ZBY_LOG_%1(Func[%2](Line[%3]))").arg(type).arg(Q_FUNC_INFO).arg(__LINE__)

#include <QObject>

class RecognizerInterface : public QObject
{
    Q_OBJECT

public:
    virtual ~RecognizerInterface() {}

public slots:

    virtual void pictureStreamSlot(const QByteArray &jpgStream,const QString &imgName)=0;
};

#define RecognizerInterfaceIID "ZBY.ContainerServer.RecognizerInterface/1.0"
Q_DECLARE_INTERFACE(RecognizerInterface,RecognizerInterfaceIID);
#endif // RECOGNIZERINTERFACE_H
