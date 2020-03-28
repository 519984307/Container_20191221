#ifndef RECOGNIZERPROCESSING_H
#define RECOGNIZERPROCESSING_H

#include <QObject>
#include <QPixmap>
#include <QMap>
#include <QMutexLocker>
#include <QMutex>

class RecognizerProcessing : public QObject
{
    Q_OBJECT
public:
    explicit RecognizerProcessing(QObject *parent = nullptr);

private:

    QMap<int,QString> imgNameData;
    QMutex mutex;

signals:

public slots:

//    ///
//    /// \brief pictureNameSlot 传递图片名
//    /// \param name 图片名
//    /// \param imgNumber 图片编号
//    ///
//    void pictureNameSlot(const QString &name,const int &imgNumber);

    ///
    /// \brief pictureStreamSlot 图片流
    /// \param jpgStream 图片流
    /// \param imgNumber 图片编号
    ///
    void pictureStreamSlot(const QByteArray &jpgStream, const int &imgNumber,const QString &imgTime);
};

#endif // RECOGNIZERPROCESSING_H
