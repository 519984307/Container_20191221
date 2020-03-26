#include "infraredprocessing.h"

InfraredProcessing::InfraredProcessing(QObject *parent) : QObject(parent)
{
    this->setParent(parent);
}

void InfraredProcessing::setCamerMultiMap(QList<QObject *> camerList,int channel)
{
    this->channel=channel;
    if(camerList.count()==4)
    {
        /* 相机顺序 右,左,后,前 */
        pPictureWidgetBEFORE=qobject_cast<PictureWidget*>(camerList[0]);
        pPictureWidgetAFTER=qobject_cast<PictureWidget*>(camerList[1]);
        pPictureWidgetLEFT=qobject_cast<PictureWidget*>(camerList[2]);
        pPictureWidgetRIGHT=qobject_cast<PictureWidget*>(camerList[3]);
    }
}

void InfraredProcessing::logicStatusSlot(int *status)
{
    /* 后续写入日志 */
}

void InfraredProcessing::logicPutImageSlot(const int &putCommnd)
{
    /*
     * -1:来车
     *0:45G1前面
     *1:45G1后面
     *2:22G1
     *3:双22G1前面
     *4:双22G1后面
    */
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

        timer=QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");/* 来车时间 */
        name=timer.split('-').join("").split(':').join("").split(" ").join("");

        data["Timer"]=timer;
        data["Channel"]=QString::number(channel);/* 通道号 */
        data["Type"]=QString::number(2);
        data["ImgFront"]=tr("%1%2%3.jpg").arg(channel).arg(name).arg(1);
        data["ImgLeftFront"]=tr("%1%2%3.jpg").arg(channel).arg(name).arg(2);
        data["ImgRightFront"]=tr("%1%2%3.jpg").arg(channel).arg(name).arg(3);
        data["ImgLeftAfter"]=tr("%1%2%3.jpg").arg(channel).arg(name).arg(4);
        data["ImgRightAfter"]=tr("%1%2%3.jpg").arg(channel).arg(name).arg(5);
        data["ImgAfter"]=tr("%1%2%3.jpg").arg(channel).arg(name).arg(6);
        emit insertDataBaseSignal(data);
        data.clear();

        break;
    case 2:
        emit pPictureWidgetBEFORE->putCommandSignal(1);
        emit pPictureWidgetLEFT->putCommandSignal(2);
        emit pPictureWidgetRIGHT->putCommandSignal(3);
        emit pPictureWidgetAFTER->putCommandSignal(6);

        timer=QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");/* 来车时间 */
        name=timer.split('-').join("").split(':').join("").split(" ").join("");
        data["Channel"]=QString::number(channel);/* 通道号 */
        data["Timer"]=timer;
        data["Type"]=QString::number(1);
        data["ImgFront"]=tr("%1%2%3.jpg").arg(channel).arg(name).arg(1);
        data["ImgLeftFront"]=tr("%1%2%3.jpg").arg(channel).arg(name).arg(2);
        data["ImgRightFront"]=tr("%1%2%3.jpg").arg(channel).arg(name).arg(3);
        data["ImgAfter"]=tr("%1%2%3.jpg").arg(channel).arg(name).arg(6);
        emit insertDataBaseSignal(data);
        data.clear();

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

        timer=QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");/* 来车时间 */
        name=timer.split('-').join("").split(':').join("").split(" ").join("");
        data["Channel"]=QString::number(channel);/* 通道号 */
        data["Timer"]=timer;
        data["Type"]=QString::number(3);
        data["ImgFront"]=tr("%1%2%3.jpg").arg(channel).arg(name).arg(1);
        data["ImgLeftFront"]=tr("%1%2%3.jpg").arg(channel).arg(name).arg(2);
        data["ImgRightFront"]=tr("%1%2%3.jpg").arg(channel).arg(name).arg(3);
        data["ImgLeftAfter"]=tr("%1%2%3.jpg").arg(channel).arg(name).arg(4);
        data["ImgRightAfter"]=tr("%1%2%3.jpg").arg(channel).arg(name).arg(5);
        data["ImgAfter"]=tr("%1%2%3.jpg").arg(channel).arg(name).arg(6);
        emit insertDataBaseSignal(data);
        data.clear();

        break;
    }
}
