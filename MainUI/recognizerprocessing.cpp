#include "recognizerprocessing.h"

RecognizerProcessing::RecognizerProcessing(QObject *parent) : QObject(parent)
{
    this->imgPath1="";
    //this->imgPath2="";
}

void RecognizerProcessing::setChannelSlot(int channel)
{
    this->channel=channel;
}

void RecognizerProcessing::setSaveImgFormatOneSlot(const QString &path, int format)
{
    this->imgPath1=path;
    this->format1=format;  
}

//void RecognizerProcessing::setSaveImgFormatTowSlot(const QString &path, int format)
//{
//    this->imgPath2=path;
//    this->format2=format;
//}

void RecognizerProcessing::pictureStreamSlot(const QByteArray &jpgStream, const int &imgNumber, const QString &imgTime)
{
    QMutexLocker locket(&mutex);
    if(imgPath1!=""){/* 保存路径不存在,图片不保存,不识别 */
        QDir dir(imgPath1);
        QString suffixPath="";        
        bool isRoot=false;/* 如果是保存在根目录就不用CD */
        switch (format1) {
        case 0:
            suffixPath=QDir::toNativeSeparators(tr("%1/%2").arg(channel).arg(QDateTime::currentDateTime().toString("yyyy/MM/dd")));
            break;
        case 1:
            suffixPath=QDir::toNativeSeparators(tr("%1/%2").arg(channel).arg(QDateTime::currentDateTime().toString("yyyy/MM")));
            break;
        case 2:
            suffixPath=QDir::toNativeSeparators(tr("%1/%2").arg(channel).arg(QDateTime::currentDateTime().toString("yyyy")));
            break;
        case 3:
            suffixPath=QDir::toNativeSeparators(tr("%1").arg(channel));
            break;
        case 4:
            suffixPath=QDir::toNativeSeparators(tr("%1").arg(QDateTime::currentDateTime().toString("yyyy/MM/dd")));
            break;
        case 5:
            suffixPath=QDir::toNativeSeparators(tr("%1").arg(QDateTime::currentDateTime().toString("yyyy/MM")));
            break;
        case 6:
            suffixPath=QDir::toNativeSeparators(tr("%1").arg(QDateTime::currentDateTime().toString("yyyy")));
            break;
        case 7:
            isRoot=true;
            break;
        }
        if(!isRoot){
            dir.mkpath(suffixPath);
            dir.cd(suffixPath);
        }

        if(imgTime!="" && jpgStream!=nullptr){
            QPixmap *labelPix = new QPixmap(QSize(576,768));
            labelPix->loadFromData(jpgStream);

            QString image=QDir::toNativeSeparators(tr("%1/%2%3%4.jpg").arg(dir.path()).arg(channel).arg(imgTime.split('-').join("").split(':').join("").split(" ").join("")).arg(imgNumber));
            labelPix->save(image);
            delete labelPix;
            labelPix=nullptr;

            emit recognizerImageSignal(image);/* 识别图片 */
        }
    }
}
