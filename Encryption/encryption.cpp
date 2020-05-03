#include "encryption.h"


Encryption::Encryption(QObject *parent)
{
    this->setParent(parent);

    pTimer=new QTimer(this);

    dogState=false;

    pDLL=nullptr;
    SmartXFind=nullptr;
    SmartXGetUid=nullptr;
    SmartXCheckExist=nullptr;

    connect(pTimer,SIGNAL(timeout()),this,SLOT(SmartXCheckExistSlot()));

    InitializationSlot();
}

Encryption::~Encryption()
{
    if(pDLL!=nullptr && pDLL->isLoaded()){
        pDLL->unload();
    }

    pTimer->stop();
    delete  pTimer;
    pTimer=nullptr;

    delete pDLL;
    pDLL=nullptr;
}

void Encryption::InitializationSlot()
{
    pDLL=new QLibrary ("./Plugins/smartX/libsmart-xe",this);

    if(pDLL->load()){
        SmartXFind=reinterpret_cast<SmartXFindFUN>(pDLL->resolve("SmartXFind"));
        SmartXGetUid=reinterpret_cast<SmartXGetUidFUN>(pDLL->resolve("SmartXGetUid"));
        SmartXCheckExist=reinterpret_cast<SmartXCheckExistFUN>(pDLL->resolve("SmartXCheckExist"));

        smartXGetUidFunc();
        pTimer->start(5000);
    }
}

void Encryption::smartXGetUidFunc()
{
    if(SmartXFind!=nullptr && SmartXFind(appID,keyHandles,&keyNumber)==0){
        if(SmartXGetUid(keyHandles[0],UID)==0){
            if(strncmp(UID,"ae68c66368a8e943bc260ae97003747f",33)==0){
                dogState=true;
            }
            else {
                dogState=false;
            }
        }
    }
    else {
        emit messageSignal(ZBY_LOG("ERROR"),"The encryption tool was not found");
    }
}

void Encryption::SmartXCheckExistSlot()
{
    if(dogState && SmartXCheckExist(keyHandles[0])==0){
        emit GetTheEncryptedStateSignal(true);
        qDebug()<<"find lock";
    }
    else {
        emit GetTheEncryptedStateSignal(false);
        smartXGetUidFunc();
        qDebug()<<"not find";
    }
}
