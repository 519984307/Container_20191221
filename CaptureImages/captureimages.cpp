#include "captureimages.h"

 CaptureImages* CaptureImages::pThis=nullptr;

CaptureImages::CaptureImages(QObject *parent)
{
    this->setParent(parent);

    CaptureImages::pThis=this;;

    lUserID=-1;dwResult=0;streamID=-1;

    pDLL=nullptr;
    pTimerState=nullptr;
    NetSDKInit=false;

    NET_DVR_SetExceptionCallBack_V30_L=nullptr;
    NET_DVR_SetSDKInitCfg_L=nullptr;
    NET_DVR_Cleanup_L=nullptr;
    NET_DVR_Init_L=nullptr;
    NET_DVR_Login_V40_L=nullptr;
    NET_DVR_Logout_L=nullptr;
    NET_DVR_ChangeWndResolution_L=nullptr;
    NET_DVR_CaptureJPEGPicture_NEW_L=nullptr;
    NET_DVR_RealPlay_V40_L=nullptr;
    NET_DVR_GetLastError_L=nullptr;
    NET_DVR_SetLogToFile_L=nullptr;
    NET_DVR_GetLocalIP_L=nullptr;
    NET_DVR_SetValidIP_L=nullptr;
    NET_DVR_StopRealPlay_L=nullptr;
    NET_DVR_RemoteControl_L=nullptr;
    NET_DVR_GetRealPlayerIndex_L=nullptr;
    NET_DVR_SetConnectTime_L=nullptr;
    NET_DVR_SetRecvTimeOut_L=nullptr;
}

CaptureImages::~CaptureImages()
{
    CaptureImages::pThis=nullptr;

    delete  pTimerState;
    pTimerState=nullptr;

    if(NET_DVR_Cleanup_L!=nullptr){
        NET_DVR_Cleanup_L();
    }

    if(pDLL!=nullptr && pDLL->isLoaded()){
        qDebug()<<pDLL->unload();
    }
    delete pDLL;
    pDLL=nullptr;
}


bool CaptureImages::InitializationSlot()
{
    //pDLL=new QLibrary("HCNetSDK.dll",this);/* windows下不支持设置动态库路径 */
    pDLL=new QLibrary (QDir::toNativeSeparators(QString("%1/%2").arg(QCoreApplication::applicationDirPath()).arg("Plugins/HCNetSDK/libhcnetsdk")),this) ;

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
        NET_DVR_GetRealPlayerIndex_L=reinterpret_cast<NET_DVR_GetRealPlayerIndexFUN>(pDLL->resolve("NET_DVR_GetRealPlayerIndex"));
        NET_DVR_SetConnectTime_L=reinterpret_cast<NET_DVR_SetConnectTimeFUN>(pDLL->resolve("NET_DVR_SetConnectTime"));
        NET_DVR_SetReconnect_L=reinterpret_cast<NET_DVR_SetReconnectFUN>(pDLL->resolve("NET_DVR_SetReconnect"));
        NET_DVR_SetRecvTimeOut_L=reinterpret_cast<NET_DVR_SetRecvTimeOutFUN>(pDLL->resolve("NET_DVR_SetRecvTimeOut"));

        if(pTimerState==nullptr){
            pTimerState=new QTimer (this);
            connect(pTimerState,SIGNAL(timeout()),this,SLOT(getDeviceStatusSlot()));
            pTimerState->start(15000);/* 10秒检测一次相机状态 */
        }

        return  true;
    }
    else {
        emit messageSignal(ZBY_LOG("ERROR"),tr("Load The Dynamic Error<errorCode=%1>").arg(pDLL->errorString()));
    }
    return false;
}

void CaptureImages::initCamerSlot(const QString &camerIP, const int &camerPort,const QString &CamerUser,const QString &CamerPow,const QString& alias)
{
    if(!NetSDKInit){
        if(!InitializationSlot()){/* 动态库初始化失败就不登录相机 */
            return;
        }

        this->camerIp=camerIP;
        this->port=camerPort;
        this->camerName=CamerUser;
        this->camerPow=CamerPow;
        this->alias=alias;

        /* 设置动态库路径 */
        NET_SDK_INIT_CFG_TYPE cfgType=NET_SDK_INIT_CFG_SDK_PATH;
        QString path= QDir::toNativeSeparators(QString("%1/%2").arg(QCoreApplication::applicationDirPath()).arg("Plugins/HCNetSDK"));
        strcpy(SDKPath.sPath,path.toLocal8Bit().data());
        if(NET_DVR_SetSDKInitCfg_L){
             NET_DVR_SetSDKInitCfg_L(cfgType,&SDKPath);
        }

        strcpy(LoginInfo.sDeviceAddress,camerIP.toLatin1().data());
        strcpy(LoginInfo.sUserName,CamerUser.toLatin1().data());
        strcpy(LoginInfo.sPassword,CamerPow.toLatin1().data());
        LoginInfo.wPort=static_cast<quint16>(camerPort);
        LoginInfo.bUseAsynLogin=1;
        LoginInfo.cbLoginResult=CaptureImages::loginResultCallBack;
        LoginInfo.pUser=this;

        if(NET_DVR_Init_L !=nullptr){
            if(NET_DVR_Init_L()){
                NetSDKInit=true;
                qDebug()<<"realy init";
                if(NET_DVR_SetExceptionCallBack_V30_L){
                    NET_DVR_SetExceptionCallBack_V30_L(0,nullptr,CaptureImages::exceptionCallBack_V30,this);
                    // NET_DVR_SetLogToFile_L(3, QString(".\\Log\\sdkLog").toLatin1().data(), true);
                    NET_DVR_SetConnectTime_L(15000,0);
                    NET_DVR_SetReconnect_L(15000,1);
                    NET_DVR_SetRecvTimeOut_L(1000);
                }
                NET_DVR_Login_V40_L(&LoginInfo,&DeviceInfo);
                emit messageSignal(ZBY_LOG("INFO"),tr("IP=%1 Camera Init Sucess").arg(this->camerIp));
            }
            else {
                emit messageSignal(ZBY_LOG("ERROR"),tr("IP=%1 Camera Init Error<errorCode=%2>").arg(this->camerIp).arg(NET_DVR_GetLastError_L()));
            }
        }
        else {
            emit messageSignal(ZBY_LOG("ERROR"),tr("Init The Dynamic Error<errorCode=%1>").arg(pDLL->errorString()));
            if(pDLL!=nullptr && pDLL->isLoaded()){
                pDLL->unload();
                pDLL=nullptr;
            }
            initCamerSlot(camerIP, camerPort,CamerUser,CamerPow,alias);
        }
    }
    else {
        qDebug()<<"realy login";
        NET_DVR_Login_V40_L(&LoginInfo,&DeviceInfo);
    }
}

void CaptureImages::getDeviceStatusSlot()
{   
    if(NET_DVR_RemoteControl_L !=nullptr){
        if(camerIp==""){
            return;
        }
        if(NET_DVR_RemoteControl_L(lUserID,NET_DVR_CHECK_USER_STATUS,nullptr,4)){
            emit camerStateSingal(camerIp,true,alias);
            dwResult=1;
        }
        else {
            emit camerStateSingal(camerIp,false,alias);
            dwResult=0;
        }
    }
}

void CaptureImages::exceptionCallBack_V30(DWORD dwType, LONG lUserID, LONG lHandle, void *pUser)
{
    //pThis=static_cast<CaptureImages*>(pUser);
    //CaptureImages* pThis=static_cast<CaptureImages*>(pUser);
    emit pThis->messageSignal(ZBY_LOG("ERROR"),tr("IP=%1 Camrea Exception<errorCode=%2>").arg(pThis->camerIp).arg(QString::number(pThis->NET_DVR_GetLastError_L())));
    //pThis=nullptr;
}

void CaptureImages::loginResultCallBack(LONG lUserID, DWORD dwResult, LPNET_DVR_DEVICEINFO_V30 lpDeviceInfo, void *pUser)
{      
    //pThis=static_cast<CaptureImages*>(pUser);;
    //CaptureImages* pThis=static_cast<CaptureImages*>(pUser);
    pThis->lUserID=lUserID;
    pThis->dwResult=dwResult;

    if(dwResult==0){
        emit pThis->messageSignal(ZBY_LOG("ERROR"),tr("IP=%1 Camera Login Error<errorCode=%2>").arg(pThis->camerIp).arg(pThis->NET_DVR_GetLastError_L()));
        if(pThis->NET_DVR_GetLastError_L()==7){
            pThis->initCamerSlot(pThis->camerIp,pThis->port,pThis->camerName,pThis->camerPow,pThis->alias);/* 重新登录 */
        }
    }
    if(dwResult==1){
        emit pThis->messageSignal(ZBY_LOG("INFO"),tr("IP=%1 Camera Login Sucess").arg(pThis->camerIp));
    }
    //pThis=nullptr;
}

bool CaptureImages::putCommandSlot(const int &imgNumber,const QString &imgTime)
{    
    if(dwResult){
        NET_DVR_JPEGPARA   pJpegFile={};
        uint32_t charLen=250000;
        LPDWORD dataLen=nullptr;
        char* buff=static_cast<char*>(malloc( charLen* sizeof(char)));
        pJpegFile.wPicSize=0xff;
        pJpegFile.wPicQuality=0;

        if(NET_DVR_CaptureJPEGPicture_NEW_L!=nullptr && NET_DVR_CaptureJPEGPicture_NEW_L(lUserID,1,&pJpegFile,buff,charLen,dataLen)){
            QByteArray arrayJpg(buff,250000);
            emit pictureStreamSignal(arrayJpg,imgNumber,imgTime);
            emit messageSignal(ZBY_LOG("INFO"), tr("IP=%1 Put Command Sucess").arg(camerIp));
        }
        else {
            emit pictureStreamSignal(nullptr,imgNumber,imgTime);/* 保证识别流程完成(识别流程需要完整图片编号) */
        }
        delete  dataLen;
        dataLen=nullptr;
        free(buff);
        buff=nullptr;
        return true;
    }

    emit pictureStreamSignal(nullptr,imgNumber,imgTime);/* 保证识别流程完成(识别流程需要完整图片编号) */

    if(NET_DVR_GetLastError_L!=nullptr){
        emit messageSignal(ZBY_LOG("ERROR"),tr("IP=%1 Put Command Error<errorCode=%2>").arg(camerIp).arg(NET_DVR_GetLastError_L()));
    }
    return  false;
}

void CaptureImages::playStreamSlot(quint64 winID,bool play)
{
    if(dwResult){
        if(play){
            NET_DVR_PREVIEWINFO struPlayInfo = {};
            struPlayInfo.hPlayWnd    =static_cast<HWND>(winID); /* linux */
            //struPlayInfo.hPlayWnd= reinterpret_cast<HWND>(winID);/* windows */
            struPlayInfo.lChannel     = 1;       /* 预览通道号 */
            struPlayInfo.dwStreamType = 0;       /* 0-主码流，1-子码流，2-码流3，3-码流4，以此类推 */
            struPlayInfo.dwLinkMode   = 1;       /* 0- TCP方式，1- UDP方式，2- 多播方式，3- RTP方式，4-RTP/RTSP，5-RSTP/HTTP */
            struPlayInfo.bBlocked     = 0;       /* 0- 非阻塞取流，1- 阻塞取流 */

            if(NET_DVR_RealPlay_V40_L !=nullptr){
                streamID =NET_DVR_RealPlay_V40_L(lUserID,&struPlayInfo,nullptr,nullptr);
                if(streamID==-1){
                     emit messageSignal(ZBY_LOG("ERROR"), tr("IP=%1 Open Stream Error<errorCode=%2>").arg(camerIp).arg(NET_DVR_GetLastError_L()));
                }
                else {
                    emit messageSignal(ZBY_LOG("INFO"),tr("IP=%1 Open Stream Sucess").arg(camerIp));
                }
            }
        }
        else {
            if(NET_DVR_StopRealPlay_L !=nullptr && NET_DVR_StopRealPlay_L(streamID)){
                emit messageSignal(ZBY_LOG("INFO"), tr("IP=%1 Stop Stream sSucess").arg(camerIp));
            }
            else {
                emit messageSignal(ZBY_LOG("ERROR"), tr("IP=%1 Stop Stream Error<errorCode=%2>").arg(camerIp).arg(NET_DVR_GetLastError_L()));
            }
        }
    }
}

void CaptureImages::resizeEventSlot()
{
    if(dwResult){
        if(NET_DVR_ChangeWndResolution_L !=nullptr){
            NET_DVR_ChangeWndResolution_L(this->streamID);
        }
    }
}

void CaptureImages::releaseResourcesSlot()
{
    if(NET_DVR_SetConnectTime_L!=nullptr){
         NET_DVR_SetConnectTime_L(1,1);/* 设置网络连接超时时间和连接尝试次数 */
    }

    if(pTimerState!=nullptr && pTimerState->isActive()){
         pTimerState->stop();
    }

    if(lUserID!=-1){
        if(streamID!=-1){
            if(NET_DVR_StopRealPlay_L !=nullptr){
                NET_DVR_StopRealPlay_L(streamID);
            }
        }
        if(NET_DVR_Logout_L !=nullptr){
            NET_DVR_Logout_L(lUserID);
        }
    }
}
