#include "infraredprocessing.h"

InfraredProcessing::InfraredProcessing(QObject *parent) : QObject(parent)
{
    this->setParent(parent);

    /* 创建日志文件夹 */
    QDir mkPath(QCoreApplication::applicationDirPath());
    mkPath.mkdir("Log");
    mkPath.cd("Log");
    logPath=mkPath.path();
}

void InfraredProcessing::setCamerMultiMap(QList<QObject *> camerList,int channel)
{
    this->channel=channel;
    if(camerList.count()==4)
    {
        /* 相机顺序  前,后,左,右 */
        pPictureWidgetFRONT=qobject_cast<PictureWidget*>(camerList[3]);
        pPictureWidgetAFTER=qobject_cast<PictureWidget*>(camerList[2]);
        pPictureWidgetLEFT=qobject_cast<PictureWidget*>(camerList[1]);
        pPictureWidgetRIGHT=qobject_cast<PictureWidget*>(camerList[0]);
    }
}

void InfraredProcessing::logicStatusSlot(int* status)
{
    /* 红外状态写入日志 */
    QFile file(QDir::toNativeSeparators(tr("%1/%2_%3_Logic_log.txt").arg(logPath).arg(QDateTime::currentDateTime().toString("yyyyMMdd")).arg(channel)));
    if(!file.open(QIODevice::WriteOnly | QIODevice::Append)){
        return;
    }
    QTextStream stream(&file);
    stream<<tr("[%1]").arg(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss:zzz"));
    stream<<tr("A1(%1)  A2(%2)  B1(%3)  B2(%4)  D1(%5)  D2(%6)").arg(status[0]).arg(status[1]).arg(status[3]).arg(status[4]).arg(status[2]).arg(status[5]);
    stream<<QDir::toNativeSeparators("\n");
    file.close();
}

void InfraredProcessing::logicPutImageSlot(const int &putCommnd)
{
    /* putCommnd
     * -1:来车
     *0:45G1前面
     *1:45G1后面
     *2:22G1
     *3:双22G1前面
     *4:双22G1后面*/
    /* Type
      * 0没有箱
      * 1:22G1
      * 2:45G1
      * 3:双22G1*/
    switch (putCommnd) {
    case -1:
        emit InfraredLogicStartSignal();/* 通知识别器来车,清除遗留图片数据 */
        emit clearnPictureSignal(nullptr,-1);/* 通知来车,清除数据界面图片 */
        break;
    case 0:
        timer=QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");/* 来车时间 */
        name=QDateTime::fromString(timer,"yyyy-MM-dd hh:mm:ss").toString("yyyyMMddhhmmss");/* 图片名时间部分 */

        emit pPictureWidgetFRONT->putCommandSignal(1,timer);
        emit pPictureWidgetLEFT->putCommandSignal(3,timer);
        emit pPictureWidgetRIGHT->putCommandSignal(2,timer);

        emit putCommantStateSignal(channel,tr("ImgTime:%1,ImgId:%2").arg(name).arg("1,2,3,4,5,6"));/* 抓拍信息写入日志 */

        break;
    case 1:
        emit pPictureWidgetLEFT->putCommandSignal(5,timer);
        emit pPictureWidgetRIGHT->putCommandSignal(4,timer);
        emit pPictureWidgetAFTER->putCommandSignal(6,timer);

        data["Timer"]=timer;
        data["Channel"]=QString::number(channel);/* 通道号 */
        data["Type"]=QString::number(2);

        data["ImgFront"]=tr("%1%2%3.jpg").arg(name).arg(1).arg(channel);
        data["ImgLeftFront"]=tr("%1%2%3.jpg").arg(name).arg(3).arg(channel);
        data["ImgRightFront"]=tr("%1%2%3.jpg").arg(name).arg(2).arg(channel);
        data["ImgLeftAfter"]=tr("%1%2%3.jpg").arg(name).arg(5).arg(channel);
        data["ImgRightAfter"]=tr("%1%2%3.jpg").arg(name).arg(4).arg(channel);
        data["ImgAfter"]=tr("%1%2%3.jpg").arg(name).arg(6).arg(channel);

        emit infraredCompleteSignal(2);
        emit insertDataBaseSignal(data);
        data.clear();

        break;
    case 2:
        timer=QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");/* 来车时间 */
        name=QDateTime::fromString(timer,"yyyy-MM-dd hh:mm:ss").toString("yyyyMMddhhmmss");/* 图片名时间部分 */

        emit pPictureWidgetFRONT->putCommandSignal(1,timer);
        emit pPictureWidgetLEFT->putCommandSignal(2,timer);
        emit pPictureWidgetRIGHT->putCommandSignal(3,timer);
        emit pPictureWidgetAFTER->putCommandSignal(6,timer);

        data["Channel"]=QString::number(channel);/* 通道号 */
        data["Timer"]=timer;
        data["Type"]=QString::number(1);

        data["ImgFront"]=tr("%1%2%3.jpg").arg(name).arg(1).arg(channel);
        data["ImgLeftFront"]=tr("%1%2%3.jpg").arg(name).arg(2).arg(channel);
        data["ImgRightFront"]=tr("%1%2%3.jpg").arg(name).arg(3).arg(channel);
        data["ImgAfter"]=tr("%1%2%3.jpg").arg(name).arg(6).arg(channel);

        emit infraredCompleteSignal(1);
        emit insertDataBaseSignal(data);
        data.clear();

        emit putCommantStateSignal(channel,tr("ImgTime:%1,ImgId:%2").arg(name).arg("1,2,3,6"));/* 抓拍信息写入日志 */

        break;
    case 3:

        timer=QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");/* 来车时间 */
        name=QDateTime::fromString(timer,"yyyy-MM-dd hh:mm:ss").toString("yyyyMMddhhmmss");/* 图片名时间部分 */

        emit pPictureWidgetFRONT->putCommandSignal(1,timer);
        emit pPictureWidgetLEFT->putCommandSignal(3,timer);
        emit pPictureWidgetRIGHT->putCommandSignal(2,timer);

        emit putCommantStateSignal(channel,tr("ImgTime:%1,ImgId:%2").arg(name).arg("1,2,3,4,5,6"));/* 抓拍信息写入日志 */

        break;
    case 4:
        emit pPictureWidgetLEFT->putCommandSignal(5,timer);
        emit pPictureWidgetRIGHT->putCommandSignal(4,timer);
        emit pPictureWidgetAFTER->putCommandSignal(6,timer);

        data["Channel"]=QString::number(channel);/* 通道号 */
        data["Timer"]=timer;
        data["Type"]=QString::number(3);

        data["ImgFront"]=tr("%1%2%3.jpg").arg(name).arg(1).arg(channel);
        data["ImgLeftFront"]=tr("%1%2%3.jpg").arg(name).arg(3).arg(channel);
        data["ImgRightFront"]=tr("%1%2%3.jpg").arg(name).arg(2).arg(channel);
        data["ImgLeftAfter"]=tr("%1%2%3.jpg").arg(name).arg(5).arg(channel);
        data["ImgRightAfter"]=tr("%1%2%3.jpg").arg(name).arg(4).arg(channel);
        data["ImgAfter"]=tr("%1%2%3.jpg").arg(name).arg(6).arg(channel);

        emit infraredCompleteSignal(3);
        emit insertDataBaseSignal(data);
        data.clear();

        break;
    }
}
