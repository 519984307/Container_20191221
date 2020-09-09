#include "encryption.h"

#include <QCryptographicHash>
#include <QProcess>

Encryption::Encryption(QObject *parent)
{
    this->setParent(parent);

    //key1=QByteArray("cheng870888").toHex()+"5e8d317e83c2f7ace3584a929961fcb4";

    key1=QByteArray("cheng870888").toHex()+"0451031075c8f4a1a81913cad8c8593f";
    ind=5;

    dogState=false;

    pDLL=nullptr;
    SmartX3Find=nullptr;
    SmartX3GetUid=nullptr;
    SmartX3CheckExist=nullptr;

    pTimer=new QTimer(this);
    //connect(pTimer,SIGNAL(timeout()),this,SLOT(SmartXCheckExistSlot()));
    connect(pTimer,SIGNAL(timeout()),this,SLOT(checkTheKeyFunc()));

    InitializationSlot();
}

Encryption::~Encryption()
{
    if(pDLL!=nullptr && pDLL->isLoaded()){
        pDLL->unload();
    }

    delete  pTimer;
    pTimer=nullptr;

    delete pDLL;
    pDLL=nullptr;
}

void Encryption::InitializationSlot()
{
    pDLL=new QLibrary ("libsmart-x3",this);

    if(pDLL->load()){
        SmartX3Find=reinterpret_cast<SmartX3FindFUN>(pDLL->resolve("SmartX3Find"));
        SmartX3GetUid=reinterpret_cast<SmartX3GetUidFUN>(pDLL->resolve("SmartX3GetUid"));
        SmartX3CheckExist=reinterpret_cast<SmartX3CheckExistFUN>(pDLL->resolve("SmartX3CheckExist"));

        /*****************************
        * @brief: 加密狗
        ******************************/
        //smartXGetUidFunc();
        //pTimer->start(10000);

        /*****************************
        * @brief: KEY
        ******************************/
        pTimer->start(10000);
    }
    else {
        emit messageSignal(ZBY_LOG("ERROR"),"Smart DLL  not load");
    }

    //pTimer->start(10000);
}

void Encryption::releaseResourcesSlot()
{
    pTimer->stop();
}

void Encryption::smartXGetUidFunc()
{
    /* 福建达远
     * ed302361196401966c72f116402e9297
     * ae68c66368a8e943bc260ae97003747f
    */
    /* 辽宁锦州
     * 2895743a6f3c423adfc444d16076e085
    */
    /* 惠州key
     * 5e8d317e83c2f7ace3584a929961fcb4
    */
    if(SmartX3Find!=nullptr && SmartX3Find(appID,keyHandles,&keyNumber)==0){
        if(SmartX3GetUid!=nullptr && SmartX3GetUid(keyHandles[0],UID)==0){
            qDebug()<<"UID:"<<UID;
            if(strncmp(UID,"2895743a6f3c423adfc444d16076e085",33)==0){
                dogState=true;
            }
            else {
                dogState=false;
            }
        }
    }
}

void Encryption::SmartXCheckExistSlot()
{
    if(dogState && SmartX3CheckExist!=nullptr && SmartX3CheckExist(keyHandles[0])==0){
        emit GetTheEncryptedStateSignal(true);
        qDebug()<<"find lock";
    }
    else {
        emit GetTheEncryptedStateSignal(false);
        smartXGetUidFunc();
        qDebug()<<"not find";
    }
}

void Encryption::checkTheKeyFunc()
{
    /*****************************
    * @brief: 15c70d2b4d36be659ce989f394170677
    *         0edc4d55539cd86b7e85b54b076d16b5
    ******************************/
    QByteArray key;
    key.append(getKey(runPro("wmic",QStringList()<<"CPU"<<"get"<<"ProcessorID")));/* CPU */
    //key.append(getKey(runPro("wmic",QStringList()<<"diskdrive"<<"get"<<"serialnumber")));/* 硬盘 */
    key.append(getKey(runPro("wmic",QStringList()<<"baseboard"<<"get"<<"serialnumber")));/* 主板 */
    key.append(getKey(runPro("wmic",QStringList()<<"csproduct"<<"get"<<"UUID")));/* UUID */

    if(QByteArray("cheng870888").toHex()+QCryptographicHash::hash(key.insert(3,"Cheng870888"),QCryptographicHash::Md5).toHex()==key1){
        emit GetTheEncryptedStateSignal(true);
        qDebug()<<"emit GetTheEncryptedStateSignal(true);";
    }
    else {
        emit GetTheEncryptedStateSignal(false);
        qDebug()<<"emit GetTheEncryptedStateSignal(false);";
    }

    if(ind==0){
        pTimer->stop();
    }
    else {
        ind--;
    }
}

QString Encryption::getKey(QByteArray arr)
{
    QString str=arr.data();
    QStringList tmp=str.simplified().split(" ");
    if(tmp.count()==2){
        return tmp[1];
    }
    return "E";
}

QByteArray Encryption::runPro(QString cmd, QStringList arg)
{
    QProcess process;
    process.setProgram(cmd);
    process.setArguments(arg);
    process.start();

    process.closeWriteChannel();
    if(process.waitForFinished()){
        return  process.readAll();
    }

    process.close();
    return "";
}
