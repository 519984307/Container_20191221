#include "imageprocessing.h"

ImageProcessing::ImageProcessing(QObject *parent) : QObject(parent)
{
    this->setParent(nullptr);
}

void ImageProcessing::camerIDstates(const QString &camerIP, bool state)
{

}

void ImageProcessing::pictureStream(const QByteArray &jpgStream, const QString &camerIP)
{

}