#include "captureimages.h"

//CaptureImages* CaptureImages::pThis=nullptr;

CaptureImages::CaptureImages(QObject *parent)
{
    this->setParent(parent);

    /*****************************
    * @brief:海康相机其它实现
    ******************************/
    alias="";
    imgNumber=-1;
    camerID=-1;
    put=false;
    imgTimeOut=new QTimer(this);
    imgTimeOut->setSingleShot(true);
    connect(imgTimeOut,SIGNAL(timeout()),this,SLOT(imgTimeOutSlot()));





//    CaptureImages::pThis=this;;

//    lUserID=-1;dwResult=0;streamID=-1;lHandle=-1;

//    pDLL=nullptr;
//    pTimerState=nullptr;
//    isSDKInit=false;

//    NET_DVR_SetExceptionCallBack_V30_L=nullptr;
//    NET_DVR_SetSDKInitCfg_L=nullptr;
//    NET_DVR_Cleanup_L=nullptr;
//    NET_DVR_Init_L=nullptr;
//    NET_DVR_Login_V40_L=nullptr;
//    NET_DVR_Logout_L=nullptr;
//    NET_DVR_ChangeWndResolution_L=nullptr;
//    NET_DVR_CaptureJPEGPicture_NEW_L=nullptr;
//    NET_DVR_RealPlay_V40_L=nullptr;
//    NET_DVR_GetLastError_L=nullptr;
//    NET_DVR_SetLogToFile_L=nullptr;
//    NET_DVR_GetLocalIP_L=nullptr;
//    NET_DVR_SetValidIP_L=nullptr;
//    NET_DVR_StopRealPlay_L=nullptr;
//    NET_DVR_RemoteControl_L=nullptr;
//    NET_DVR_GetRealPlayerIndex_L=nullptr;
//    NET_DVR_SetConnectTime_L=nullptr;
//    NET_DVR_SetRecvTimeOut_L=nullptr;
//    NET_DVR_CaptureJPEGPicture_L=nullptr;
//    NET_DVR_SetupAlarmChan_V41_L=nullptr;
//    NET_DVR_CloseAlarmChan_V30_L=nullptr;
//    NET_DVR_SetDVRMessageCallBack_V31_L=nullptr;
//    NET_DVR_ContinuousShoot_L=nullptr;
//    NET_DVR_ManualSnap_L=nullptr;

//    charLen=IMG_BYTE;

//    pJpegFile.wPicSize=0xff;
//    pJpegFile.wPicQuality=0;

//    snapcfg.dwSize=sizeof (NET_DVR_SNAPCFG);
//    snapcfg.byRelatedDriveWay=1;
//    snapcfg.bySnapTimes=1;
//    snapcfg.wSnapWaitTime =0;
//    snapcfg.struJpegPara=pJpegFile;

//    manualsnap.byOSDEnable=1;
//    manualsnap.byLaneNo=1;

//    imgT="";
//    imgN=-1;

//    imgBuff=nullptr;
}

CaptureImages::~CaptureImages()
{
//    free(imgBuff);
//    delete imgBuff;
//    imgBuff=nullptr;

//    CaptureImages::pThis=nullptr;

//    delete  pTimerState;
//    pTimerState=nullptr;

//    if(NET_DVR_Cleanup_L!=nullptr){
//        NET_DVR_Cleanup_L();
//    }

//    if(pDLL!=nullptr && pDLL->isLoaded()){
//        pDLL->unload();
//    }

//    delete pDLL;
//    pDLL=nullptr;
}

bool CaptureImages::InitializationSlot()
{
//    pDLL=new QLibrary("HCNetSDK",this);/* windows下不支持设置动态库路径 */
//    //pDLL=new QLibrary (QDir::toNativeSeparators(QString("%1/%2").arg(QCoreApplication::applicationDirPath()).arg("Plugins/HCNetSDK/libhcnetsdk")),this) ;

//    if(pDLL->load()){
//        NET_DVR_SetExceptionCallBack_V30_L=reinterpret_cast<NET_DVR_SetExceptionCallBack_V30FUN>(pDLL->resolve("NET_DVR_SetExceptionCallBack_V30"));
//        NET_DVR_SetSDKInitCfg_L=reinterpret_cast<NET_DVR_SetSDKInitCfgFUN>(pDLL->resolve("NET_DVR_SetSDKInitCfg"));
//        NET_DVR_Cleanup_L=reinterpret_cast<NET_DVR_CleanupFUN>(pDLL->resolve("NET_DVR_Cleanup"));
//        NET_DVR_Init_L=reinterpret_cast<NET_DVR_InitFUN>(pDLL->resolve("NET_DVR_Init"));
//        NET_DVR_Login_V40_L=reinterpret_cast<NET_DVR_Login_V40FUN>(pDLL->resolve("NET_DVR_Login_V40"));
//        NET_DVR_Logout_L=reinterpret_cast<NET_DVR_LogoutFUN>(pDLL->resolve("NET_DVR_Logout"));
//        NET_DVR_ChangeWndResolution_L=reinterpret_cast<NET_DVR_ChangeWndResolutionFUN>(pDLL->resolve("NET_DVR_ChangeWndResolution"));
//        NET_DVR_CaptureJPEGPicture_NEW_L=reinterpret_cast<NET_DVR_CaptureJPEGPicture_NEWFUN>(pDLL->resolve("NET_DVR_CaptureJPEGPicture_NEW"));
//        NET_DVR_CaptureJPEGPicture_L=reinterpret_cast<NET_DVR_CaptureJPEGPictureFUN>(pDLL->resolve("NET_DVR_CaptureJPEGPicture"));
//        NET_DVR_RealPlay_V40_L=reinterpret_cast<NET_DVR_RealPlay_V40FUN>(pDLL->resolve("NET_DVR_RealPlay_V40"));
//        NET_DVR_GetLastError_L=reinterpret_cast<NET_DVR_GetLastErrorFUN>(pDLL->resolve("NET_DVR_GetLastError"));
//        NET_DVR_SetLogToFile_L=reinterpret_cast<NET_DVR_SetLogToFileFUN>(pDLL->resolve("NET_DVR_SetLogToFile"));
//        NET_DVR_GetLocalIP_L=reinterpret_cast<NET_DVR_GetLocalIPFUN>(pDLL->resolve("NET_DVR_GetLocalIP"));
//        NET_DVR_SetValidIP_L=reinterpret_cast<NET_DVR_SetValidIPFUN>(pDLL->resolve("NET_DVR_SetValidIP"));
//        NET_DVR_StopRealPlay_L=reinterpret_cast<NET_DVR_StopRealPlayFUN>(pDLL->resolve("NET_DVR_StopRealPlay"));
//        NET_DVR_RemoteControl_L=reinterpret_cast<NET_DVR_RemoteControlFUN>(pDLL->resolve("NET_DVR_RemoteControl"));
//        NET_DVR_GetRealPlayerIndex_L=reinterpret_cast<NET_DVR_GetRealPlayerIndexFUN>(pDLL->resolve("NET_DVR_GetRealPlayerIndex"));
//        NET_DVR_SetConnectTime_L=reinterpret_cast<NET_DVR_SetConnectTimeFUN>(pDLL->resolve("NET_DVR_SetConnectTime"));
//        NET_DVR_SetReconnect_L=reinterpret_cast<NET_DVR_SetReconnectFUN>(pDLL->resolve("NET_DVR_SetReconnect"));
//        NET_DVR_SetRecvTimeOut_L=reinterpret_cast<NET_DVR_SetRecvTimeOutFUN>(pDLL->resolve("NET_DVR_SetRecvTimeOut"));
//        NET_DVR_CloseAlarmChan_V30_L=reinterpret_cast<NET_DVR_CloseAlarmChan_V30FUN>(pDLL->resolve("NET_DVR_CloseAlarmChan_V30"));
//        NET_DVR_SetupAlarmChan_V41_L=reinterpret_cast<NET_DVR_SetupAlarmChan_V41FUN>(pDLL->resolve("NET_DVR_SetupAlarmChan_V41"));
//        NET_DVR_SetDVRMessageCallBack_V31_L=reinterpret_cast<NET_DVR_SetDVRMessageCallBack_V31FUN>(pDLL->resolve("NET_DVR_SetDVRMessageCallBack_V31"));
//        NET_DVR_ContinuousShoot_L=reinterpret_cast<NET_DVR_ContinuousShootFUN>(pDLL->resolve("NET_DVR_ContinuousShoot"));
//        NET_DVR_ManualSnap_L=reinterpret_cast<NET_DVR_ManualSnapFUN>(pDLL->resolve("NET_DVR_ManualSnap"));

//        if(pTimerState==nullptr){
//            pTimerState=new QTimer (this);
//            connect(pTimerState,SIGNAL(timeout()),this,SLOT(getDeviceStatusSlot()));
//            pTimerState->start(10000);/* 10秒检测一次相机状态 */
//        }
//        return  true;
//    }
//    else {
//        emit messageSignal(ZBY_LOG("ERROR"),tr("Load The Dynamic Error<errorCode=%1>").arg(pDLL->errorString()));
//    }
//    return false;
}

void CaptureImages::initCamerSlot(const QString &camerIP, const int &camerPort,const QString &CamerUser,const QString &CamerPow,const QString& alias)
{
    /*****************************
    * @brief:海康相机其它实现
    ******************************/
    this->camerIP=camerIP;
    this->alias=alias;
    if(camerIP.isEmpty()){
        return;
    }
    emit signal_initCamera("",camerIP,camerPort,CamerUser,CamerPow);




//    if(!isSDKInit){
//        if(!InitializationSlot()){/* 动态库初始化失败就不登录相机 */
//            return;
//        }

//        this->camerIp=camerIP;
//        this->port=camerPort;
//        this->camerName=CamerUser;
//        this->camerPow=CamerPow;
//        this->alias=alias;

//        /* 设置动态库路径 */
//        NET_SDK_INIT_CFG_TYPE cfgType=NET_SDK_INIT_CFG_SDK_PATH;
//        QString path= QDir::toNativeSeparators(QString("%1/%2").arg(QCoreApplication::applicationDirPath()).arg("Plugins/HCNetSDK"));
//        strcpy(SDKPath.sPath,path.toLocal8Bit().data());
//        if(NET_DVR_SetSDKInitCfg_L!=nullptr){
//             NET_DVR_SetSDKInitCfg_L(cfgType,&SDKPath);
//        }

//        strcpy(LoginInfo.sDeviceAddress,camerIP.toLatin1().data());
//        strcpy(LoginInfo.sUserName,CamerUser.toLatin1().data());
//        strcpy(LoginInfo.sPassword,CamerPow.toLatin1().data());
//        LoginInfo.wPort=static_cast<quint16>(camerPort);
//        LoginInfo.bUseAsynLogin=1;
//        LoginInfo.cbLoginResult=CaptureImages::loginResultCallBack;
//        LoginInfo.pUser=nullptr;

//        if(NET_DVR_Init_L !=nullptr){
//            if(NET_DVR_Init_L()){

//                if(imgBuff==nullptr){
//                    imgBuff=static_cast<char*>(malloc(charLen* sizeof(char)));
//                }
//                if(imgBuff==nullptr){
//                    emit messageSignal(ZBY_LOG("INFO"),tr("IP=%1 Image memory allocation failed").arg(this->camerIp));
//                }

//                isSDKInit=true;
//                qDebug()<<"realy init";
//                if(NET_DVR_SetExceptionCallBack_V30_L!=nullptr){
//                    NET_DVR_SetExceptionCallBack_V30_L(0,nullptr,CaptureImages::exceptionCallBack_V30,this);
//                    // NET_DVR_SetLogToFile_L(3, QString(".\\Log\\sdkLog").toLatin1().data(), true);
//                    NET_DVR_SetConnectTime_L(10000,0);
//                    NET_DVR_SetReconnect_L(10000,0);
//                    NET_DVR_SetRecvTimeOut_L(1000);
//                }

//                if(NET_DVR_Login_V40_L !=nullptr){
//                    NET_DVR_Login_V40_L(&LoginInfo,&DeviceInfo);
//                }

//                /*****************************
//                * @brief:交通系列产品
//                ******************************/
////                if(NET_DVR_SetDVRMessageCallBack_V31_L!=nullptr){
////                    if(NET_DVR_SetDVRMessageCallBack_V31_L(CaptureImages::exceptionMSGCallBack_V31,this)){
////                        emit messageSignal(ZBY_LOG("INFO"),tr("IP=%1 Camera NET_DVR_SetDVRMessageCallBack_V31_L Sucess").arg(this->camerIp));
////                    }
////                }
//                emit messageSignal(ZBY_LOG("INFO"),tr("IP=%1 Camera Init Sucess").arg(this->camerIp));
//            }
//            else {
////                if(nullptr!= NET_DVR_Cleanup_L)
////                {
////                    NET_DVR_Cleanup_L();/* 不能调用其他接口 */
////                }
//                emit messageSignal(ZBY_LOG("ERROR"),tr("IP=%1 Camera Init Error<errorCode=%2>").arg(this->camerIp).arg(NET_DVR_GetLastError_L()));
//            }
//        }
//        else {
//            emit messageSignal(ZBY_LOG("ERROR"),tr("Init The Dynamic Error<errorCode=%1>").arg(pDLL->errorString()));
//            if(pDLL!=nullptr && pDLL->isLoaded()){
//                pDLL->unload();
//                pDLL=nullptr;
//            }
//            initCamerSlot(camerIP, camerPort,CamerUser,CamerPow,alias);
//        }
//    }
//    else {
//        qDebug()<<"realy login";
//        NET_DVR_Login_V40_L(&LoginInfo,&DeviceInfo);
//    }
}

void CaptureImages::getDeviceStatusSlot()
{   
//    if(NET_DVR_RemoteControl_L !=nullptr){
//        if(camerIp==""){
//            return;
//        }
//        if(NET_DVR_RemoteControl_L(lUserID,NET_DVR_CHECK_USER_STATUS,nullptr,4)){
//            emit camerStateSingal(camerIp,true,alias);
//            dwResult=1;
//        }
//        else {
//            emit camerStateSingal(camerIp,false,alias);
//            dwResult=0;

//            /*****************************
//            * @brief:断开重连
//            ******************************/
//            if(lUserID!=-1){
//                if(NET_DVR_Logout_L !=nullptr){
//                    NET_DVR_Logout_L(lUserID);
//                }
//            }
//            if(lHandle>0){
//                if(NET_DVR_CloseAlarmChan_V30_L!=nullptr){
//                    NET_DVR_CloseAlarmChan_V30_L(lHandle);
//                }
//            }
//            initCamerSlot(camerIp,port,camerName,camerPow,alias);/* 重新登录 */
//        }
    //    }
}


WINBOOL CaptureImages::exceptionMSGCallBack_V31(LONG lCommand, NET_DVR_ALARMER *pAlarmer, char *pAlarmInfo, DWORD dwBufLen, void *pUser)
{
//    //struPlateResult.struPlateInfo.byColor)//车牌颜色
//    //(struPlateResult.struPlateInfo.sLicense));// 车牌号
//    //emit pThis->messageSignal(ZBY_LOG("INFO"),QString("lUserID: %1").arg(pAlarmer->lUserID));


//    if(pThis->imgN==-1){
//        return false;
//    }

//    if(lCommand == COMM_UPLOAD_PLATE_RESULT){
//        NET_DVR_PLATE_RESULT struPlateResult={};
//        memcpy(&struPlateResult, pAlarmInfo, sizeof(struPlateResult));
//        emit pThis->messageSignal(ZBY_LOG("INFO"),QString("Plate: %1").arg(struPlateResult.struPlateInfo.sLicense).toLocal8Bit());// 车牌号

//        // 场景图
//        if (struPlateResult.dwPicLen != 0 && struPlateResult.byResultType == 1 )
//        {
//            pThis->imgBuff=reinterpret_cast<char*>(struPlateResult.pBuffer1);
//            QByteArray arrayJpg(pThis->imgBuff,struPlateResult.dwPicLen);
//            emit pThis->pictureStreamSignal(arrayJpg,pThis->imgN,pThis->imgT);
//        }
//        // 车牌图
//        if (struPlateResult.dwPicPlateLen != 0 && struPlateResult.byResultType == 1)
//        {
////            pThis->imgBuff=reinterpret_cast<char*>(struPlateResult.pBuffer2);
////            QByteArray arrayJpg(pThis->imgBuff,struPlateResult.dwPicPlateLen);
//        }

//    }
//    if(lCommand==COMM_ITS_PLATE_RESULT){
//        NET_ITS_PLATE_RESULT struITSPlateResult={};
//        memcpy(&struITSPlateResult, pAlarmInfo, sizeof(struITSPlateResult));
//        emit pThis->messageSignal(ZBY_LOG("INFO"),QString("Plate: %1").arg(struITSPlateResult.struPlateInfo.sLicense).toLocal8Bit());// 车牌号

//        // 场景图
//        if (((struITSPlateResult.struPicInfo[0].dwDataLen != 0)&&(struITSPlateResult.struPicInfo[0].byType== 1))||(struITSPlateResult.struPicInfo[0].byType == 2))
//        {
//            pThis->imgBuff=reinterpret_cast<char*>(struITSPlateResult.struPicInfo[0].pBuffer);
//            QByteArray arrayJpg(pThis->imgBuff,struITSPlateResult.struPicInfo[0].dwDataLen);
//            emit pThis->pictureStreamSignal(arrayJpg,pThis->imgN,pThis->imgT);
//        }
//        // 车牌图
//        if (((struITSPlateResult.struPicInfo[0].dwDataLen != 0)&&(struITSPlateResult.struPicInfo[0].byType== 0)))
//        {
////            pThis->imgBuff=reinterpret_cast<char*>(struITSPlateResult.struPicInfo[0].pBuffer);
////            QByteArray arrayJpg(pThis->imgBuff,struITSPlateResult.struPicInfo[0].dwDataLen);
//        }
//    }
//    emit pThis->messageSignal(ZBY_LOG("INFO"),QString("exceptionMSGCallBack_V31:%1,imgNumber:%2").arg(QString::number(lCommand)).arg(pThis->imgN));

//    pThis->imgN=-1;
//    pThis->imgT="";

//    return true;
}

void CaptureImages::exceptionCallBack_V30(DWORD dwType, LONG lUserID, LONG lHandle, void *pUser)
{
//    emit pThis->messageSignal(ZBY_LOG("ERROR"),tr("IP=%1 Camrea Exception<errorCode=%2>").arg(pThis->camerIp).arg(QString::number(pThis->NET_DVR_GetLastError_L())));
}

void CaptureImages::loginResultCallBack(LONG lUserID, DWORD dwResult, LPNET_DVR_DEVICEINFO_V30 lpDeviceInfo, void *pUser)
{      
//    qDebug()<<"lUserID:"<<lUserID;

//    if(dwResult==0){
//        emit pThis->messageSignal(ZBY_LOG("ERROR"),tr("IP=%1 Camera Login Error<errorCode=%2>").arg(pThis->camerIp).arg(pThis->NET_DVR_GetLastError_L()));
//    }
//    if(dwResult==1){
//        emit pThis->messageSignal(ZBY_LOG("INFO"),tr("IP=%1 Camera Login Sucess").arg(pThis->camerIp));

//        /*****************************
//        * @brief:交通系列，布防。
//        ******************************/
////        if(pThis->NET_DVR_SetupAlarmChan_V41_L!=nullptr){
////            NET_DVR_SETUPALARM_PARAM aram={};
////            aram.dwSize=sizeof (NET_DVR_SETUPALARM_PARAM);
////            aram.byAlarmInfoType=1;
////            aram.byLevel=1;
////            pThis->lHandle= pThis->NET_DVR_SetupAlarmChan_V41_L(lUserID,&aram);
////            if(pThis->lHandle<0){
////                emit pThis->messageSignal(ZBY_LOG("ERROR"),tr("IP=%1 Camera Aram Error<errorCode=%2>").arg(pThis->camerIp).arg(pThis->NET_DVR_GetLastError_L()));
////            }
////            else{
////                emit pThis->messageSignal(ZBY_LOG("INFO"),tr("IP=%1 Camera Aram Success<Code=%2>").arg(pThis->camerIp).arg(pThis->lHandle));

////            }
////        }

//        pThis->lUserID=lUserID;
//        pThis->dwResult=dwResult;
//    }
}

void CaptureImages::imgTimeOutSlot()
{
    put=false;
    emit pictureStreamSignal(nullptr,imgNumber,imgTime);
}

bool CaptureImages::putCommandSlot( int imgNumber, QString imgTime)
{
    /*****************************
    * @brief:海康相机其它实现
    ******************************/
    if(camerID==-1){
        emit pictureStreamSignal(nullptr,imgNumber,imgTime);
        return false;
    }
    if(imgTimeOut->isActive()){
        emit pictureStreamSignal(nullptr,this->imgNumber,this->imgTime);
        imgTimeOut->stop();
    }
    put=true;
    this->imgNumber=imgNumber;
    this->imgTime=imgTime;
    emit signal_simulationCapture(camerID);
    imgTimeOut->start(3000);





//    bool cap=true;

//    if(dwResult){
//        switch (CAMERA_TYPE) {
//        case 1:
//            {
//                LPDWORD dataLen=nullptr;
//                /* 手动触发抓拍保存到内存 */
//                if(NET_DVR_CaptureJPEGPicture_NEW_L!=nullptr && NET_DVR_CaptureJPEGPicture_NEW_L(lUserID,1,&pJpegFile,imgBuff,charLen,dataLen)){
//                    QByteArray arrayJpg(imgBuff,*dataLen);
//                    emit pictureStreamSignal(arrayJpg,imgNumber,imgTime);
//                    emit messageSignal(ZBY_LOG("INFO"), tr("IP=%1 Put Command Sucess").arg(camerIp));

//                    arrayJpg.clear();
//                    delete  dataLen;
//                    dataLen=nullptr;
//                }
//                else {
//                    cap=false;
//                    }
//            }
//            break;
//        case 2:
//            {
//                NET_DVR_PLATE_RESULT result={};
//                result.dwSize=sizeof (result);
//                result.pBuffer1=reinterpret_cast<unsigned char*>(imgBuff);
//                /* 手动触发抓拍，SDK提示做测试使用 */
//                if(NET_DVR_ManualSnap_L!=nullptr && NET_DVR_ManualSnap_L(lUserID,&manualsnap,&result)){
//                    QByteArray arrayJpg(imgBuff,IMG_BYTE);
//                    emit pictureStreamSignal(arrayJpg,imgNumber,imgTime);
//                    emit messageSignal(ZBY_LOG("INFO"), tr("IP=%1 Put Command Sucess").arg(camerIp));

//                    arrayJpg.clear();
//                }
//                else {
//                    cap=false;
//                }
//            }
//            break;
//        case 3:
//            {
//                if(NET_DVR_ContinuousShoot_L!=nullptr){/* 网络触发抓拍 */
//                    int rul=NET_DVR_ContinuousShoot_L(lUserID,&snapcfg);
//                    if(rul){
//                        this->imgN=imgNumber;
//                        this->imgT=imgTime;
//                        emit messageSignal(ZBY_LOG("INFO"), tr("IP=%1 Put Command Sucess").arg(camerIp));
//                    }
//                    else {
//                        cap=false;
//                    }
//                }
//            }
//            break;
//        }

//    }

//    emit messageSignal(ZBY_LOG("ERROR"),tr("IP=%1 Put Command=%2>").arg(camerIp).arg(imgNumber));
//    if(!cap){
//        emit pictureStreamSignal(nullptr,imgNumber,imgTime);/* 保证识别流程完成(识别流程需要完整图片编号) */
//        if(NET_DVR_GetLastError_L!=nullptr){
//            emit messageSignal(ZBY_LOG("ERROR"),tr("IP=%1 Put Command Error<errorCode=%2>").arg(camerIp).arg(NET_DVR_GetLastError_L()));
//        }
//        return false;
//    }
//    return true;
}

void CaptureImages::playStreamSlot(quint64 winID,bool play)
{
    /*****************************
    * @brief:海康相机其它实现
    ******************************/
    emit signal_openTheVideo(camerID,play,winID);





//    if(dwResult){
//        if(play){
//            NET_DVR_PREVIEWINFO struPlayInfo = {};
//            //struPlayInfo.hPlayWnd    =static_cast<HWND>(winID); /* linux */
//            struPlayInfo.hPlayWnd= reinterpret_cast<HWND>(winID);/* windows */
//            struPlayInfo.lChannel     = 1;       /* 预览通道号 */
//            struPlayInfo.dwStreamType = 0;       /* 0-主码流，1-子码流，2-码流3，3-码流4，以此类推 */
//            struPlayInfo.dwLinkMode   = 1;       /* 0- TCP方式，1- UDP方式，2- 多播方式，3- RTP方式，4-RTP/RTSP，5-RSTP/HTTP */
//            struPlayInfo.bBlocked     = 0;       /* 0- 非阻塞取流，1- 阻塞取流 */

//            if(NET_DVR_RealPlay_V40_L !=nullptr){
//                streamID =NET_DVR_RealPlay_V40_L(lUserID,&struPlayInfo,nullptr,nullptr);
//                if(streamID==-1){
//                     emit messageSignal(ZBY_LOG("ERROR"), tr("IP=%1 Open Stream Error<errorCode=%2>").arg(camerIp).arg(NET_DVR_GetLastError_L()));
//                }
//                else {
//                    emit messageSignal(ZBY_LOG("INFO"),tr("IP=%1 Open Stream Sucess").arg(camerIp));
//                }
//            }
//        }
//        else {
//            if(NET_DVR_StopRealPlay_L !=nullptr && NET_DVR_StopRealPlay_L(streamID)){
//                emit messageSignal(ZBY_LOG("INFO"), tr("IP=%1 Stop Stream sSucess").arg(camerIp));
//            }
////            else {
////                emit messageSignal(ZBY_LOG("ERROR"), tr("IP=%1 Stop Stream Error<errorCode=%2>").arg(camerIp).arg(NET_DVR_GetLastError_L()));
////            }
//        }
//    }
}

void CaptureImages::resizeEventSlot()
{
//    if(dwResult){
//        if(NET_DVR_ChangeWndResolution_L !=nullptr){
//            NET_DVR_ChangeWndResolution_L(this->streamID);
//        }
//    }
}

void CaptureImages::releaseResourcesSlot()
{
//    if(NET_DVR_SetConnectTime_L!=nullptr){
//         NET_DVR_SetConnectTime_L(1,1);/* 设置网络连接超时时间和连接尝试次数 */
//    }

//    if(pTimerState!=nullptr && pTimerState->isActive()){
//         pTimerState->stop();
//    }

//    if(lUserID!=-1){
//        if(streamID!=-1){
//            if(NET_DVR_StopRealPlay_L !=nullptr){
//                NET_DVR_StopRealPlay_L(streamID);
//            }
//        }
//        if(NET_DVR_Logout_L !=nullptr){
//            NET_DVR_Logout_L(lUserID);
//        }
//        if(lHandle!=-1){
//            if(NET_DVR_CloseAlarmChan_V30_L!=nullptr){
//                NET_DVR_CloseAlarmChan_V30_L(lHandle);
//            }
//        }
//    }
    if(imgTimeOut!=nullptr && imgTimeOut->isActive()){
        imgTimeOut->stop();
    }
}





/*****************************
* @brief:海康相机其它实现
******************************/

void CaptureImages::slot_pictureStream(int ID, QByteArray arrJpg)
{
    if(put && ID==camerID){
        imgTimeOut->stop();
        emit pictureStreamSignal(arrJpg,imgNumber,imgTime);
        //emit messageSignal(ZBY_LOG("INFO"), tr("IP=%1 Put Command Sucess").arg(camerIP));
        put=false;
    }
}

void CaptureImages::slot_setCameraID(int ID, QString cameraIP)
{
    if(camerIP==cameraIP){
        camerID=ID;
        emit messageSignal(ZBY_LOG("INFO"), tr("IP=%1 Set the ID[%2]").arg(cameraIP).arg(ID));
    }
}

void CaptureImages::slot_resultsTheLicensePlate(int ID, const QString &plate, const QString &color, const QString &time, QByteArray arrImg)
{
//    if(camerID==ID){
//        saveImg(arrImg,time);
//        emit resultsTheLicensePlateSignal(plate,color,time,arrImg);
//        emit messageSignal(ZBY_LOG("INFO"),tr("License Plate recognition results:%1 %2").arg(plate).arg(time));
//    }
    /*****************************
    * @brief:集装箱不接受车牌信息
    ******************************/
}

void CaptureImages::slot_equipmentState(int ID, bool state)
{
    if(camerID==ID){
         emit camerStateSingal(camerIP,state,alias);
    }
}
