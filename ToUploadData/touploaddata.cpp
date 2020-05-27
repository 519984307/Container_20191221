#include "touploaddata.h"

ToUploadData::ToUploadData(QObject *parent)
{
    this->setParent(parent);

    pManager=nullptr;
}

ToUploadData::~ToUploadData()
{
    url.clear();

    if(pManager!=nullptr){
        delete  pManager;
        pManager=nullptr;
    }
}

void ToUploadData::InitializationParameterSlot(const QString &user, const QString &pass, const QString &path, const QString &host, const int &port)
{    
    remotePath=path;

    url.setScheme("ftp");
    url.setHost(host);
    url.setPort(port);
    url.setUserName(user);
    url.setPassword(pass);

    pManager=new QNetworkAccessManager (this);
    connect(pManager, SIGNAL(finished(QNetworkReply*)),this, SLOT(replyFinishedSlot(QNetworkReply*)));
}

void ToUploadData::uploadDataSlot(const QString &data)
{   
    dataName=data;

    QFile file(data);
    if(!file.open(QIODevice::ReadOnly)){
        return;
    }

    QStringList dataList=data.split("/");
    if(dataList.count()<1){
        return;
    }

    url.setPath(QString("%1%2").arg(remotePath).arg(dataList[dataList.count()-1]));

    pManager->put(QNetworkRequest(url),file.readAll());

    file.flush();
    file.close();
}

void ToUploadData::replyFinishedSlot(QNetworkReply *reply)
{
    if (reply && reply->error() == QNetworkReply::NoError) {
        emit messageSignal(ZBY_LOG("INFO"),QString("%1 upload finished").arg(dataName));
    }
    else {
        emit messageSignal(ZBY_LOG("ERROR"),QString("Data upload error<errorCode=%1>").arg(reply->errorString()));
    }
    reply->close();
    reply->deleteLater();
}
