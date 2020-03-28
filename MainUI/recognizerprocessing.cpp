#include "recognizerprocessing.h"

RecognizerProcessing::RecognizerProcessing(QObject *parent) : QObject(parent)
{
}

void RecognizerProcessing::pictureStreamSlot(const QByteArray &jpgStream, const int &imgNumber, const QString &imgTime)
{
    QMutexLocker locket(&mutex);
    if(imgTime!="" && jpgStream!=nullptr){
        QPixmap *labelPix = new QPixmap();
        labelPix->loadFromData(jpgStream);
        labelPix->save((tr("%1%2.jpg").arg(imgTime).arg(imgNumber)));
        delete labelPix;
        labelPix=nullptr;
    }
}
