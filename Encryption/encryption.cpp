#include "encryption.h"


Encryption::Encryption(QObject *parent)
{
    this->setParent(parent);

    dogState=false;

    pDLL=nullptr;
    SmartX3Find=nullptr;
    SmartX3GetUid=nullptr;
    SmartX3CheckExist=nullptr;

    pTimer=new QTimer(this);
    connect(pTimer,SIGNAL(timeout()),this,SLOT(SmartXCheckExistSlot()));

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
    pDLL=new QLibrary ("libsmart-xe",this);

    if(pDLL->load()){
        SmartX3Find=reinterpret_cast<SmartX3FindFUN>(pDLL->resolve("SmartX3Find"));
        SmartX3GetUid=reinterpret_cast<SmartX3GetUidFUN>(pDLL->resolve("SmartX3GetUid"));
        SmartX3CheckExist=reinterpret_cast<SmartX3CheckExistFUN>(pDLL->resolve("SmartX3CheckExist"));

        smartXGetUidFunc();
        pTimer->start(5000);
    }
//    else {
//        emit messageSignal(ZBY_LOG("ERROR"),"DLL  not load");
//    }
}

void Encryption::releaseResourcesSlot()
{
    pTimer->stop();
}

void Encryption::smartXGetUidFunc()
{
    if(SmartX3Find!=nullptr && SmartX3Find(appID,keyHandles,&keyNumber)==0){
        if(SmartX3GetUid!=nullptr && SmartX3GetUid(keyHandles[0],UID)==0){
            qDebug()<<"UID:"<<UID;
            if(strncmp(UID,"ed302361196401966c72f116402e9297",33)==0){/* ae68c66368a8e943bc260ae97003747f */
                dogState=true;
            }
            else {
                dogState=false;
            }
        }
    }
//    else {
//        emit messageSignal(ZBY_LOG("ERROR"),"The encryption tool was not found");
//    }
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
