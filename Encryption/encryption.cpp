#include "encryption.h"


Encryption::Encryption(QObject *parent)
{
    this->setParent(parent);

    pTimer=new QTimer(this);

    pDLL=nullptr;
    SmartXFind=nullptr;
    SmartXGetUid=nullptr;
    SmartXCheckExist=nullptr;

    connect(pTimer,SIGNAL(timeout()),this,SLOT(SmartXCheckExistSlot()));
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
    pDLL=new QLibrary ("./Plugins/smartx/libsmart-xe",this);

    if(pDLL->load()){
        SmartXFind=reinterpret_cast<SmartXFindFUN>(pDLL->resolve("SmartXFind"));
        SmartXGetUid=reinterpret_cast<SmartXGetUidFUN>(pDLL->resolve("SmartXGetUid"));
        SmartXCheckExist=reinterpret_cast<SmartXCheckExistFUN>(pDLL->resolve("SmartXCheckExist"));

        pTimer->start(10000);
    }
}

void Encryption::smartXGetUidFunc()
{
    char appID[32]={"HCA5NT4DKKUE48ULHT"};
    long keyNumber=0;

    if(SmartXFind!=nullptr && SmartXFind(appID,keyHandles,&keyNumber)==0){
        if(SmartXGetUid(keyHandles[0],UID)==0){
            if(strncmp(UID,"ae68c66368a8e943bc260ae97003747f",32)==0){
                emit GetTheEncryptedStateSignal(true);
            }
            else {
                emit GetTheEncryptedStateSignal(false);
            }
        }
    }
    else {
        emit messageSignal(ZBY_LOG("ERROR"),"The encryption tool was not found");
    }
}

void Encryption::SmartXCheckExistSlot()
{
    if(SmartXCheckExist(keyHandles[0])==0){
        emit GetTheEncryptedStateSignal(true);
    }
    else {
        emit GetTheEncryptedStateSignal(false);
    }
}
