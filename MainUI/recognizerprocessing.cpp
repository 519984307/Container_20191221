#include "recognizerprocessing.h"

RecognizerProcessing::RecognizerProcessing(QObject *parent) : QObject(parent)
{
    this->imgPath1="";
    //this->imgPath2="";
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

//void RecognizerProcessing::setSaveImgFormatTowSlot(const QString &path, int format)
//{
//    this->imgPath2=path;
//    this->format2=format;
//}

void RecognizerProcessing::pictureStreamSlot(const QByteArray &jpgStream, const int &imgNumber, const QString &imgTime)
{
    if(imgNumber==0){
        return;
    }
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

        QString image="";
        if(imgTime!="" && jpgStream!=nullptr){
            QPixmap *labelPix = new QPixmap();
            labelPix->loadFromData(jpgStream);
            /* 缩放图片 */
            QPixmap labelPixFit=  labelPix->scaled(1280,960, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

            image=QDir::toNativeSeparators(tr("%1/%2%3%4.jpg").arg(dir.path()).arg(imgTime.split('-').join("").split(':').join("").split(" ").join("")).arg(imgNumber).arg(channel));

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
    }

    if(resulList.count()==containerNum){
        for(int i=0;i<containerNum;i++){
            chanResulList.append(resulList[0]);
            resulList.removeAt(0);
        }
        resultsOfAnalysis(containertType);
        containerNum=0;
        containertType=0;
    }
}

void RecognizerProcessing::resultsOfAnalysis(int type)
{
    /* 双箱，分前3个结果和后3个结果独立处理 */
    QStringList conTemp,isoTemp;/* 箱号,箱型 */
    QList<uint32_t> probabilityTemp;/* 置信度 */

    for (auto var:chanResulList) {
        if(var.split(":")[1].indexOf("|")==-1){/* 没有识别到结果 */
            conTemp.append("");
            isoTemp.append("");
            probabilityTemp.append(0);
        }
        else {
            QStringList tmp=var.split(":")[1].split("|");
            conTemp.append(tmp[0]);
            isoTemp.append(tmp[1]);
            probabilityTemp.append(tmp[2].toUInt());
        }
    }

    if(type==3){

        int index1=0;
        int index2=0;
        uint32_t probability=0;

        for (int var = 0; var < 3; ++var) {
            if(probabilityTemp[var]>probability){
                probability=probabilityTemp[var];
                index1=var;
            }
        }
        probability=0;
        for (int var = 3; var < 6; ++var) {
            if(probabilityTemp[var]>probability){
                probability=probabilityTemp[var];
                index2=var;
            }
        }
        emit containerSignal(conTemp[index1],isoTemp[1],conTemp[index2],isoTemp[index2]);
    }
    else {
        uint32_t probability=0;
        int index1=0;

        for (int var = 0; var < probabilityTemp.count(); ++var) {
            if(probabilityTemp[var]>probability){
                probability=probabilityTemp[var];
                index1=var;
            }
        }
        emit containerSignal(conTemp[index1],isoTemp[1],"","");
    }

    chanResulList.clear();
    conTemp.clear();
    isoTemp.clear();
    probabilityTemp.clear();
}
