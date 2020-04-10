#include "recognizerprocessing.h"

RecognizerProcessing::RecognizerProcessing(QObject *parent) : QObject(parent)
{
    this->imgPath1="";
    this->imgPath2="";
    containerNum=0;
    containertType=0;
}

RecognizerProcessing::~RecognizerProcessing()
{
    resulList.clear();
    queue.clear();
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

void RecognizerProcessing::setSaveImgFormatTowSlot(const QString &path, int format)
{
    this->imgPath2=path;
    this->format2=format;
}

void RecognizerProcessing::pictureStreamSlot(const QByteArray &jpgStream, const int &imgNumber, const QString &imgTime)
{
    if(imgNumber==0){/* 测试抓图,不保存,不识别 */
        return;
    }
    QMutexLocker locket(&mutex);
    if(imgPath1!=""){/* 保存路径不存在,图片不保存,不识别 */
        QDir dir(imgPath1);
        bool isRoot=false;/* 如果是保存在根目录就不用CD */
        QString suffixPath="";
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

        QString image="";
        if(imgTime!="" && jpgStream!=nullptr){
            QPixmap *labelPix = new QPixmap();
            labelPix->loadFromData(jpgStream);
            /* 缩放图片 */
            QPixmap labelPixFit=  labelPix->scaled(1280,720, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
            image=QDir::toNativeSeparators(tr("%1/%2%3%4.jpg").arg(dir.path()).arg(QDateTime::fromString(imgTime,"yyyy-MM-dd hh:mm:ss").toString("yyyyMMddhhmmss")).arg(imgNumber).arg(channel));
            labelPixFit.save(image);
            //labelPix->save(image);
            delete labelPix;
            labelPix=nullptr;

            //emit identifyImagesSignal(image);/* 识别图片 */
        }
        emit identifyImagesSignal(image);/* 识别图片 */
    }
}

void RecognizerProcessing::infraredCompleteSlot(const int &type)
{
    /* 1:22G1 */
    /* 2:45G1 */
    /* 3:双22G1 */
    queue.enqueue(type);
}

void RecognizerProcessing::recognitionResultSlot(const QString &result, const QString &image)
{
    resulList<<result;

    if(containerNum==0&&queue.count()!=0){
        containertType=queue.dequeue();
        switch (containertType) {
        case 1:
            containerNum=4;
            break;
        case 2:
            containerNum=6;
            break;
        case 3:
            containerNum=6;
            break;
        }
        imageName=image;
    }

    if(resulList.count()==containerNum){
        for(int i=0;i<containerNum;i++){
            chanResulList.append(resulList[0]);
            qDebug()<<resulList[0];
            resulList.removeAt(0);
        }
        emit resultsOfAnalysisSignal(chanResulList,containertType,imageName);/* 分析结果 */

        containerNum=0;
        containertType=0;
        chanResulList.clear();
        imageName="";
    }
}
