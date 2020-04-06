#include "identifyimages.h"

IdentifyImages::IdentifyImages(QObject *parent)
{
    this->setParent(parent);
    pPool=new QThreadPool (this);
    pPool->setMaxThreadCount(QThread::idealThreadCount());
}

IdentifyImages::~IdentifyImages()
{
    delete  pPool;
    pPool=nullptr;
}

void IdentifyImages::pictureStreamSlot(const QByteArray &jpgStream, const int &imgNumber)
{
    /* Subsequent processing */
}

void IdentifyImages::identifyImagesSlot(const QString &image)
{
    Recognition* pRecognition=new Recognition(nullptr,image);
    connect(pRecognition,&Recognition::recognitionResultSignal,this,&IdentifyImages::recognitionResultSignal);
    connect(pRecognition,&Recognition::messageSignal,this,&IdentifyImages::messageSignal);
    pPool->start(pRecognition);
}
