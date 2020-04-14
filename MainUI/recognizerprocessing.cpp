#include "recognizerprocessing.h"

RecognizerProcessing::RecognizerProcessing(QObject *parent) : QObject(parent)
{
    this->imgPath1="";
    this->imgPath2="";
    this->channel=-1;
    containerNum=0;
    containertType=0;
}

RecognizerProcessing::~RecognizerProcessing()
{
    resulList.clear();
    chanResulList.clear();
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
            suffixPath=QDir::toNativeSeparators("./");
            break;
        }

        QDir dir(imgPath1);
        dir.mkpath(suffixPath);
        dir.cd(suffixPath);

        QString image="";
        if(imgTime!="" && jpgStream!=nullptr){
            QPixmap *labelPix = new QPixmap();
            labelPix->loadFromData(jpgStream);            
            QPixmap labelPixFit=  labelPix->scaled(1280,720, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);/* 缩放图片 */
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

void RecognizerProcessing::saveImageTowSlot(const QByteArray &jpgStream, const int &imgNumber, const QString &imgTime)
{
    if(imgNumber==0){/* 测试抓图,不保存,不识别 */
        return;
    }
    QMutexLocker locket(&mutex);
    if(imgPath2!=""){/* 保存路径不存在,图片不保存 */
        QString suffixPath="";
        switch (format2) {
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
            suffixPath=QDir::toNativeSeparators("./");
            break;
        }

        QDir dir(imgPath2);
        dir.mkpath(suffixPath);
        dir.cd(suffixPath);

        QString image="";
        if(imgTime!="" && jpgStream!=nullptr){
            QPixmap *labelPix = new QPixmap();
            labelPix->loadFromData(jpgStream);
            //QPixmap labelPixFit=  labelPix->scaled(1920,1080, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);/* 缩放图片 */
            image=QDir::toNativeSeparators(tr("%1/%2%3%4.jpg").arg(dir.path()).arg(QDateTime::fromString(imgTime,"yyyy-MM-dd hh:mm:ss").toString("yyyyMMddhhmmss")).arg(imgNumber).arg(channel));
            //labelPixFit.save(image);
            labelPix->save(image);
            delete labelPix;
            labelPix=nullptr;
        }
    }
}

void RecognizerProcessing::InfraredLogicStartSlot()
{
    resulList.clear();
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
            resulList.removeAt(0);
        }
        emit resultsOfAnalysisSignal(chanResulList,containertType,imageName);/* 分析结果 */

        containerNum=0;
        containertType=0;
        chanResulList.clear();
        imageName="";
    }
}
