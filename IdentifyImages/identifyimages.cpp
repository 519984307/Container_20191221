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

void IdentifyImages::identifyResults(const QString &image)
{
    Recognition* pRecognition=new Recognition(nullptr,image);
    connect(pRecognition,&Recognition::recognitionResultSignal,this,&IdentifyImages::recognitionResultSlot);
    pPool->start(pRecognition);
}
#include <iostream>
void IdentifyImages::recognitionResultSlot(const QString &result)
{
    std::cout<<result.toStdString()<<std::endl;
}
