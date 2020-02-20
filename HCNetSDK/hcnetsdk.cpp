#include "hcnetsdk.h"

#if defined(Q_OS_WIN32)
    #define OS 0
#elif defined(Q_OS_LINUX)
    #define OS 1
#endif

HCNetSDK* HCNetSDK::pThis=nullptr;

HCNetSDK::HCNetSDK(QObject *parent)
{
    this->setParent(parent);

    HCNetSDK::pThis=this;

    lUserID=-1;dwResult=0;streamID=-1;

    if(OS){
        pDLL= new QLibrary("./plugins/HCNetSDK/libhcnetsdk.so");
    }
    else {
        pDLL = new QLibrary("./plugins/HCNetSDK/libhcnetsdk.dll");
    }

    if(pDLL->load()){
        NET_DVR_SetExceptionCallBack_V30_L=reinterpret_cast<NET_DVR_SetExceptionCallBack_V30FUN>(pDLL->resolve("NET_DVR_SetExceptionCallBack_V30"));
        NET_DVR_SetSDKInitCfg_L=reinterpret_cast<NET_DVR_SetSDKInitCfgFUN>(pDLL->resolve("NET_DVR_SetSDKInitCfg"));
        NET_DVR_Cleanup_L=reinterpret_cast<NET_DVR_CleanupFUN>(pDLL->resolve("NET_DVR_Cleanup"));
        NET_DVR_Init_L=reinterpret_cast<NET_DVR_InitFUN>(pDLL->resolve("NET_DVR_Init"));
        NET_DVR_Login_V40_L=reinterpret_cast<NET_DVR_Login_V40FUN>(pDLL->resolve("NET_DVR_Login_V40"));
        NET_DVR_Logout_L=reinterpret_cast<NET_DVR_LogoutFUN>(pDLL->resolve("NET_DVR_Logout"));
        NET_DVR_ChangeWndResolution_L=reinterpret_cast<NET_DVR_ChangeWndResolutionFUN>(pDLL->resolve("NET_DVR_ChangeWndResolution"));
        NET_DVR_CaptureJPEGPicture_NEW_L=reinterpret_cast<NET_DVR_CaptureJPEGPicture_NEWFUN>(pDLL->resolve("NET_DVR_CaptureJPEGPicture_NEW"));
        NET_DVR_RealPlay_V40_L=reinterpret_cast<NET_DVR_RealPlay_V40FUN>(pDLL->resolve("NET_DVR_RealPlay_V40"));
        NET_DVR_GetLastError_L=reinterpret_cast<NET_DVR_GetLastErrorFUN>(pDLL->resolve("NET_DVR_GetLastError"));
        NET_DVR_SetLogToFile_L=reinterpret_cast<NET_DVR_SetLogToFileFUN>(pDLL->resolve("NET_DVR_SetLogToFile"));
        NET_DVR_GetLocalIP_L=reinterpret_cast<NET_DVR_GetLocalIPFUN>(pDLL->resolve("NET_DVR_GetLocalIP"));
        NET_DVR_SetValidIP_L=reinterpret_cast<NET_DVR_SetValidIPFUN>(pDLL->resolve("NET_DVR_SetValidIP"));
        NET_DVR_StopRealPlay_L=reinterpret_cast<NET_DVR_StopRealPlayFUN>(pDLL->resolve("NET_DVR_StopRealPlay"));
        NET_DVR_RemoteControl_L=reinterpret_cast<NET_DVR_RemoteControlFUN>(pDLL->resolve("NET_DVR_RemoteControl"));
    }
}

HCNetSDK::~HCNetSDK()
{
    pDLL->unload();
    delete pDLL;
}

bool HCNetSDK::getDeviceStatus(LONG lUserID)
{
    if(NET_DVR_RemoteControl_L(lUserID,NET_DVR_CHECK_USER_STATUS,nullptr,4)){
        return true;
    }
    else {
        return false;
    }
}

bool HCNetSDK::initSDk()
{
    NET_DVR_LOCAL_SDK_PATH SDKPath={};
    NET_SDK_INIT_CFG_TYPE cfgType=NET_SDK_INIT_CFG_SDK_PATH;
    QString path= QDir::toNativeSeparators(tr("%1/%2").arg(QCoreApplication::applicationDirPath()).arg("plugins/HCNetSDK"));
    strcpy(SDKPath.sPath,path.toLocal8Bit().data());
    NET_DVR_SetSDKInitCfg_L(cfgType,&SDKPath);

    NET_DVR_USER_LOGIN_INFO LoginInfo={};
    NET_DVR_DEVICEINFO_V40 DeviceInfo={};
    strcpy(LoginInfo.sDeviceAddress,this->ip.toLatin1().data());
    strcpy(LoginInfo.sUserName,this->name.toLatin1().data());
    strcpy(LoginInfo.sPassword,this->pow.toLatin1().data());
    LoginInfo.wPort=static_cast<uint16_t>(this->port);
    LoginInfo.bUseAsynLogin=1;
    LoginInfo.cbLoginResult=HCNetSDK::loginResultCallBack;
    LoginInfo.pUser=nullptr;

    if(NET_DVR_Init_L()){
        NET_DVR_SetExceptionCallBack_V30_L(0,nullptr,HCNetSDK::exceptionCallBack_V30,nullptr);
        NET_DVR_SetLogToFile_L(3, QString(".\\sdkLog").toLatin1().data(), true);
        NET_DVR_Login_V40_L(&LoginInfo,&DeviceInfo);
        return  true;
    }
     return false;
}

void HCNetSDK::exceptionCallBack_V30(DWORD dwType, LONG lUserID, LONG lHandle, void *pUser)
{
    //HCNetSDK* pThis=reinterpret_cast<HCNetSDK*>(pUser);
    emit pThis->messageSignal(tr("ID:%1,ERROR:%2,HANDLE:%3").arg(lUserID).arg(dwType).arg(lHandle));
}

void HCNetSDK::loginResultCallBack(LONG lUserID, DWORD dwResult, LPNET_DVR_DEVICEINFO_V30 lpDeviceInfo, void *pUser)
{   
    //HCNetSDK* pThis=static_cast<HCNetSDK*>(pUser);
    pThis->lUserID=lUserID;
    pThis->dwResult=dwResult;
    emit pThis->messageSignal(tr("ID:%1,STATUS:%2").arg(lUserID).arg(dwResult));
}

void HCNetSDK::initCamerSlot(const QString &camerIP, quint16 camerPort,const QString &CamerUser,const QString &CamerPow)
{
    this->ip=camerIP;
    this->port=camerPort;
    this->name=CamerUser;
    this->pow=CamerPow;

    initSDk();
}

bool HCNetSDK::putCommandSlot(const QString &command)
{
    NET_DVR_JPEGPARA   pJpegFile={};

    uint charLen=200000;
    uint dataLen=0;
    char* buff=static_cast<char*>(malloc( charLen* sizeof(char)));
    pJpegFile.wPicSize=2;
    pJpegFile.wPicQuality=184;

    if(dwResult){
        if(!NET_DVR_CaptureJPEGPicture_NEW_L(lUserID,1,&pJpegFile,buff,charLen,&dataLen)){
            emit messageSignal(tr("put command Error:%1").arg(NET_DVR_GetLastError_L()));
            return false;
        }
        else {
            QByteArray bye(buff,200000);
            emit pictureStreamSignal(bye,this->ip);
        }
    }
    free(buff);
    return true;
}

void HCNetSDK::playStreamSlot(uint winID,bool play)
{
    NET_DVR_PREVIEWINFO struPlayInfo = {};
    struPlayInfo.hPlayWnd    =winID;//static_cast<uint>(winID);        //需要SDK解码时句柄设为有效值，仅取流不解码时可设为空
    struPlayInfo.lChannel     = 1;       //预览通道号
    struPlayInfo.dwStreamType = 0;       //0-主码流，1-子码流，2-码流3，3-码流4，以此类推
    struPlayInfo.dwLinkMode   = 1;       //0- TCP方式，1- UDP方式，2- 多播方式，3- RTP方式，4-RTP/RTSP，5-RSTP/HTTP
    struPlayInfo.bBlocked     = 0;       //0- 非阻塞取流，1- 阻塞取流

    if(dwResult){
        if(play){
            streamID =NET_DVR_RealPlay_V40_L(lUserID,&struPlayInfo,nullptr,nullptr);
            if(streamID==-1){
                 emit messageSignal(tr("open stream Error:%1").arg(NET_DVR_GetLastError_L()));
            }
        }
        else {
            NET_DVR_StopRealPlay_L(streamID);
        }
    }
}

void HCNetSDK::resizeEventSlot()
{
    NET_DVR_ChangeWndResolution_L(this->streamID);
}

void HCNetSDK::closeStreamSlot()
{
    if(streamID!=-1||lUserID!=-1){
        NET_DVR_StopRealPlay_L(streamID);
        NET_DVR_Logout_L(lUserID);
    }
    NET_DVR_Cleanup_L();
}
