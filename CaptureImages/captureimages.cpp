#include "captureimages.h"

CaptureImages::CaptureImages(QObject *parent)
{
    this->setParent(parent);

    /* 登录ID,登录状态,视频流状态 */
    lUserID=-1;dwResult=0;streamID=-1;
}

CaptureImages::~CaptureImages()
{
}

void CaptureImages::initCamerSlot(const QString &camerIP, quint16 camerPort,const QString &CamerUser,const QString &CamerPow)
{
    this->ip=camerIP;
    this->port=camerPort;
    this->name=CamerUser;
    this->pow=CamerPow;

    DLL.setFileName("./Plugins/HCNetSDK/libhcnetsdk");

    if(DLL.load()){
        NET_DVR_SetExceptionCallBack_V30_L=reinterpret_cast<NET_DVR_SetExceptionCallBack_V30FUN>(DLL.resolve("NET_DVR_SetExceptionCallBack_V30"));
        NET_DVR_SetSDKInitCfg_L=reinterpret_cast<NET_DVR_SetSDKInitCfgFUN>(DLL.resolve("NET_DVR_SetSDKInitCfg"));
        NET_DVR_Cleanup_L=reinterpret_cast<NET_DVR_CleanupFUN>(DLL.resolve("NET_DVR_Cleanup"));
        NET_DVR_Init_L=reinterpret_cast<NET_DVR_InitFUN>(DLL.resolve("NET_DVR_Init"));
        NET_DVR_Login_V40_L=reinterpret_cast<NET_DVR_Login_V40FUN>(DLL.resolve("NET_DVR_Login_V40"));
        NET_DVR_Logout_L=reinterpret_cast<NET_DVR_LogoutFUN>(DLL.resolve("NET_DVR_Logout"));
        NET_DVR_ChangeWndResolution_L=reinterpret_cast<NET_DVR_ChangeWndResolutionFUN>(DLL.resolve("NET_DVR_ChangeWndResolution"));
        NET_DVR_CaptureJPEGPicture_NEW_L=reinterpret_cast<NET_DVR_CaptureJPEGPicture_NEWFUN>(DLL.resolve("NET_DVR_CaptureJPEGPicture_NEW"));
        NET_DVR_RealPlay_V40_L=reinterpret_cast<NET_DVR_RealPlay_V40FUN>(DLL.resolve("NET_DVR_RealPlay_V40"));
        NET_DVR_GetLastError_L=reinterpret_cast<NET_DVR_GetLastErrorFUN>(DLL.resolve("NET_DVR_GetLastError"));
        NET_DVR_SetLogToFile_L=reinterpret_cast<NET_DVR_SetLogToFileFUN>(DLL.resolve("NET_DVR_SetLogToFile"));
        NET_DVR_GetLocalIP_L=reinterpret_cast<NET_DVR_GetLocalIPFUN>(DLL.resolve("NET_DVR_GetLocalIP"));
        NET_DVR_SetValidIP_L=reinterpret_cast<NET_DVR_SetValidIPFUN>(DLL.resolve("NET_DVR_SetValidIP"));
        NET_DVR_StopRealPlay_L=reinterpret_cast<NET_DVR_StopRealPlayFUN>(DLL.resolve("NET_DVR_StopRealPlay"));
        NET_DVR_RemoteControl_L=reinterpret_cast<NET_DVR_RemoteControlFUN>(DLL.resolve("NET_DVR_RemoteControl"));
        NET_DVR_GetRealPlayerIndex_L=reinterpret_cast<NET_DVR_GetRealPlayerIndexFUN>(DLL.resolve("NET_DVR_GetRealPlayerIndex"));
        NET_DVR_SetConnectTime_L=reinterpret_cast<NET_DVR_SetConnectTimeFUN>(DLL.resolve("NET_DVR_SetConnectTime"));

        loginCamer();
    }
    else {
        emit messageSignal(ZBY_LOG("ERROR"),tr("Failed to load the dynamic DLL"));
    }
}

bool CaptureImages::getDeviceStatus(LONG lUserID)
{   
    if(NET_DVR_RemoteControl_L(lUserID,NET_DVR_CHECK_USER_STATUS,nullptr,4)){
        emit camerStateSingal(ip,true);
        return true;
    }
    else {
        emit camerStateSingal(ip,false);
        return false;
    }
}

void CaptureImages::loginCamer()
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
    LoginInfo.cbLoginResult=CaptureImages::loginResultCallBack;
    LoginInfo.pUser=this;

    if(NET_DVR_Init_L()){
        NET_DVR_SetExceptionCallBack_V30_L(0,nullptr,CaptureImages::exceptionCallBack_V30,nullptr);
        //NET_DVR_SetLogToFile_L(3, QString(".\\sdkLog").toLatin1().data(), false);
        NET_DVR_SetConnectTime_L(20000,10);
        NET_DVR_Login_V40_L(&LoginInfo,&DeviceInfo);

        emit messageSignal(ZBY_LOG("INFO"),tr("IP=%1 camera init sucess").arg(ip));
    }
    else {
        emit messageSignal(ZBY_LOG("ERROR"),tr("IP=%1 camera init error<errorCode=%2>").arg(ip).arg(NET_DVR_GetLastError_L()));
    }
}

void CaptureImages::exceptionCallBack_V30(DWORD dwType, LONG lUserID, LONG lHandle, void *pUser)
{
    CaptureImages* pThis=reinterpret_cast<CaptureImages*>(pUser);
    emit pThis->messageSignal(ZBY_LOG("ERROR"),tr("IP=%1 camrea exception<errorCode=%2>").arg(pThis->ip).arg(dwType));
}


void CaptureImages::loginResultCallBack(LONG lUserID, DWORD dwResult, LPNET_DVR_DEVICEINFO_V30 lpDeviceInfo, void *pUser)
{      
    CaptureImages* pThis=static_cast<CaptureImages*>(pUser);
    pThis->lUserID=lUserID;
    pThis->dwResult=dwResult;
    if(dwResult==0){
        pThis->loginCamer();/*第一次登录失败,重新登录*/
        emit pThis->messageSignal(ZBY_LOG("ERROR"),tr("IP=%1 camera login error<errorCOde=%2>").arg(pThis->ip).arg(pThis->NET_DVR_GetLastError_L()));
    }
    if(dwResult==1){
        emit pThis->messageSignal(ZBY_LOG("INFO"),tr("IP=%1 camera loginsucess").arg(pThis->ip));
    }
}

bool CaptureImages::putCommandSlot(const int &imgNumber)
{
    NET_DVR_JPEGPARA   pJpegFile={};

    uint32_t charLen=200000;
    LPDWORD dataLen=nullptr;
    char* buff=static_cast<char*>(malloc( charLen* sizeof(char)));
    pJpegFile.wPicSize=0xff;
    pJpegFile.wPicQuality=0;

    if(dwResult){
        if(!NET_DVR_CaptureJPEGPicture_NEW_L(lUserID,1,&pJpegFile,buff,charLen,dataLen)){

            emit messageSignal(ZBY_LOG("ERROR"),tr("IP=%1 Put command error<errorCode=%2>").arg(ip).arg(NET_DVR_GetLastError_L()));

            dataLen=nullptr;    delete  dataLen;
            free(buff);    buff=nullptr;    delete buff;
            return false;
        }
        else {
            QByteArray arrayJpg(buff,200000);
            emit pictureStreamSignal(arrayJpg,imgNumber);
            arrayJpg.clear();

            emit messageSignal(ZBY_LOG("INFO"), tr("IP=%1 Put command sucess").arg(ip));
        }
    }

    dataLen=nullptr; delete  dataLen;
    free(buff);  buff=nullptr; delete buff;
    return true;
}

void CaptureImages::playStreamSlot(uint winID,bool play)
{
    if(dwResult){
        if(play){
            NET_DVR_PREVIEWINFO struPlayInfo = {};
            struPlayInfo.hPlayWnd    =reinterpret_cast<HWND>(winID);        //需要SDK解码时句柄设为有效值，仅取流不解码时可设为空
            struPlayInfo.lChannel     = 1;       //预览通道号
            struPlayInfo.dwStreamType = 0;       //0-主码流，1-子码流，2-码流3，3-码流4，以此类推
            struPlayInfo.dwLinkMode   = 1;       //0- TCP方式，1- UDP方式，2- 多播方式，3- RTP方式，4-RTP/RTSP，5-RSTP/HTTP
            struPlayInfo.bBlocked     = 0;       //0- 非阻塞取流，1- 阻塞取流

            streamID =NET_DVR_RealPlay_V40_L(lUserID,&struPlayInfo,nullptr,nullptr);

            if(streamID==-1){
                 emit messageSignal(ZBY_LOG("ERROR"), tr("IP=%1 Open stream error<errorCode=%2>").arg(ip).arg(NET_DVR_GetLastError_L()));
            }
            else {
                emit messageSignal(ZBY_LOG("INFO"),tr("IP=%1 Open stream sucess").arg(ip));
            }
        }
        else {
            if(!NET_DVR_StopRealPlay_L(streamID)){
                emit messageSignal(ZBY_LOG("ERROR"), tr("IP=%1 Stop stream error<errorCode=%2>").arg(ip).arg(NET_DVR_GetLastError_L()));
            }
            else {
                emit messageSignal(ZBY_LOG("INFO"), tr("IP=%1 Stop stream sucess").arg(ip));
            }
        }
    }
}

void CaptureImages::resizeEventSlot()
{
    if(dwResult){
         NET_DVR_ChangeWndResolution_L(this->streamID);
    }
}

void CaptureImages::releaseResourcesSlot()
{
    if(lUserID!=-1){
        if(streamID!=-1){
            NET_DVR_StopRealPlay_L(streamID);
        }
        NET_DVR_Logout_L(lUserID);
        NET_DVR_Cleanup_L();
    }

    if(DLL.isLoaded()){
         DLL.unload();
    }
}
