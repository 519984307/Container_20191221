#ifndef RECOGNIZERPROCESSING_H
#define RECOGNIZERPROCESSING_H

#include <QObject>
#include <QPixmap>
#include <QMap>
#include <QMutexLocker>
#include <QMutex>
#include <QDir>
#include <QDateTime>

class RecognizerProcessing : public QObject
{
    Q_OBJECT
public:
    explicit RecognizerProcessing(QObject *parent = nullptr);

private:

    QDir  dir;

    QMutex mutex;    

    ///
    /// \brief channel 通道号
    ///
    int channel;

    ///
    /// \brief imgPath1 图片路径1
    ///
    QString imgPath1;

//    ///
//    /// \brief imgPath2 图片路径2
//    ///
//    QString imgPath2;

    ///
    /// \brief format1 保存协议1
    ///
    int format1;

//    ///
//    /// \brief format2 保存协议2
//    ///
//    int format2;

signals:

public slots:

    ///
    /// \brief setChannelSlot 设定通道号
    ///
    void setChannelSlot(int channel);

    ///
    /// \brief setSaveImgFormatOneSlot 设置图片保存路径1
    /// \param path
    /// \param format
    ///
    void setSaveImgFormatOneSlot(const QString &path,int format);

//    ///
//    /// \brief setSaveImgFormatTowSlot 设置图片保存路径2
//    /// \param path
//    /// \param format
//    ///
//    void setSaveImgFormatTowSlot(const QString &path,int format);
    ///
    /// \brief pictureStreamSlot 图片流
    /// \param jpgStream 图片流
    /// \param imgNumber 图片编号
    ///
    void pictureStreamSlot(const QByteArray &jpgStream, const int &imgNumber,const QString &imgTime);
};

#endif // RECOGNIZERPROCESSING_H
