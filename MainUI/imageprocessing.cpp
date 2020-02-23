#include "imageprocessing.h"

ImageProcessing::ImageProcessing(QObject *parent) : QObject(parent)
{
    this->setParent(parent);
}

void ImageProcessing::camerIDstatesSlot(const QString &camerIP, bool state)
{

}

void ImageProcessing::pictureStreamSlot(const QByteArray &jpgStream, const QString &camerIP)
{

}
