#include "recognizerprocessing.h"

RecognizerProcessing::RecognizerProcessing(QObject *parent) : QObject(parent)
{
}

void RecognizerProcessing::settingValues(int channel)
{
    this->channel=channel;
}

void RecognizerProcessing::pictureStreamSlot(const QByteArray &jpgStream, const int &imgNumber, const QString &imgTime)
{
    QMutexLocker locket(&mutex);
    QString tmp=imgTime;
    QString name=tmp.split('-').join("").split(':').join("").split(" ").join("");
    if(imgTime!="" && jpgStream!=nullptr){
        QPixmap *labelPix = new QPixmap();
        labelPix->loadFromData(jpgStream);
        labelPix->save((tr("./Images/%1%2%3.jpg").arg(QString::number(channel)).arg(name).arg(imgNumber)));
        delete labelPix;
        labelPix=nullptr;
    }
}
