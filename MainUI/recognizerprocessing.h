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

    QMutex mutex;

    int channel;

signals:

public slots:

    ///
    /// \brief settingValues 设定需求参数
    ///
    void settingValues(int channel);

    ///
    /// \brief pictureStreamSlot 图片流
    /// \param jpgStream 图片流
    /// \param imgNumber 图片编号
    ///
    void pictureStreamSlot(const QByteArray &jpgStream, const int &imgNumber,const QString &imgTime);
};

#endif // RECOGNIZERPROCESSING_H
