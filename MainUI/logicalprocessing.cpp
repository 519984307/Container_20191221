#include "logicalprocessing.h"

LogicalProcessing::LogicalProcessing(QObject *parent) : QObject(parent)
{
    this->setParent(parent);
}

void LogicalProcessing::setCamerMultiMap(QList<QObject *> camerList)
{
    /* 相机顺序 右,左,后,前 */
    pPictureWidgetBEFORE=qobject_cast<PictureWidget*>(camerList[0]);
    pPictureWidgetAFTER=qobject_cast<PictureWidget*>(camerList[1]);
    pPictureWidgetLEFT=qobject_cast<PictureWidget*>(camerList[2]);
    pPictureWidgetRIGHT=qobject_cast<PictureWidget*>(camerList[3]);
    connect(pPictureWidgetBEFORE,&PictureWidget::pictureStreamSignal,this,&LogicalProcessing::pictureStreamSlot);
    connect(pPictureWidgetAFTER,&PictureWidget::pictureStreamSignal,this,&LogicalProcessing::pictureStreamSlot);
    connect(pPictureWidgetLEFT,&PictureWidget::pictureStreamSignal,this,&LogicalProcessing::pictureStreamSlot);
    connect(pPictureWidgetRIGHT,&PictureWidget::pictureStreamSignal,this,&LogicalProcessing::pictureStreamSlot);
}

//void LogicalProcessing::logicStatusSlot(int *status)
//{
//    ;
//}

void LogicalProcessing::logicPutImageSlot(const int &putCommnd)
{
    switch (putCommnd) {
    case -1:
        emit pictureStreamSignal(nullptr,-1);
        break;
    case 0:
        emit pPictureWidgetBEFORE->putCommandSignal(1);
        emit pPictureWidgetLEFT->putCommandSignal(2);
        emit pPictureWidgetRIGHT->putCommandSignal(3);
        break;
    case 1:
        emit pPictureWidgetLEFT->putCommandSignal(4);
        emit pPictureWidgetRIGHT->putCommandSignal(5);
        emit pPictureWidgetAFTER->putCommandSignal(6);
        break;
    case 2:
        emit pPictureWidgetBEFORE->putCommandSignal(1);
        emit pPictureWidgetLEFT->putCommandSignal(2);
        emit pPictureWidgetRIGHT->putCommandSignal(3);
        emit pPictureWidgetAFTER->putCommandSignal(6);
        break;
    case 3:
        emit pPictureWidgetBEFORE->putCommandSignal(1);
        emit pPictureWidgetLEFT->putCommandSignal(2);
        emit pPictureWidgetRIGHT->putCommandSignal(3);
        break;
    case 4:
        emit pPictureWidgetLEFT->putCommandSignal(4);
        emit pPictureWidgetRIGHT->putCommandSignal(5);
        emit pPictureWidgetAFTER->putCommandSignal(6);
        break;
    }
}

void LogicalProcessing::pictureStreamSlot(const QByteArray &jpgStream, const int &imgNumber)
{
    QMutexLocker &locker();
    emit pictureStreamSignal(jpgStream,imgNumber);
}
