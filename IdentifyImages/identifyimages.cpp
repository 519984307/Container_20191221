#include "identifyimages.h"

IdentifyImages::IdentifyImages(QObject *parent)
{
    this->setParent(parent);
}

IdentifyImages::~IdentifyImages()
{

}

void IdentifyImages::pictureNameSlot(const QString &name, const int &imgNumber)
{

}

void IdentifyImages::pictureStreamSlot(const QByteArray &jpgStream, const int &imgNumber)
{

}

//void IdentifyImages::pictureStreamSlot(const QByteArray &jpgStream, const int &imgNumber, const QString &imgName)
//{
//    QPixmap *labelPix = new QPixmap();
//    if(jpgStream!=nullptr){
//        labelPix->loadFromData(jpgStream);
//    }
//    labelPix->save(imgName);

//    delete labelPix;
//    labelPix=nullptr;
//}
