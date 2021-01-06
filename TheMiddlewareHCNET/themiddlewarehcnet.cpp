#include "themiddlewarehcnet.h"

TheMiddlewareHCNET* TheMiddlewareHCNET::pThis=nullptr;

TheMiddlewareHCNET::TheMiddlewareHCNET(QObject *parent)
{
    this->setParent(parent);
    TheMiddlewareHCNET::pThis=this;;

    streamID=-1;

    pDLL=nullptr;
    pTimerState=nullptr;
    isSDKInit=false;

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
    NET_DVR_CaptureJPEGPicture_L=nullptr;
    NET_DVR_SetupAlarmChan_V41_L=nullptr;
    NET_DVR_CloseAlarmChan_V30_L=nullptr;
    NET_DVR_SetDVRMessageCallBack_V31_L=nullptr;
    NET_DVR_ContinuousShoot_L=nullptr;
    NET_DVR_ManualSnap_L=nullptr;

    charLen=IMG_BYTE;

    pJpegFile.wPicSize=0xff;
    pJpegFile.wPicQuality=0;

    snapcfg.dwSize=sizeof (NET_DVR_SNAPCFG);
    snapcfg.byRelatedDriveWay=1;
    snapcfg.bySnapTimes=1;
    snapcfg.wSnapWaitTime =0;
    snapcfg.struJpegPara=pJpegFile;

    manualsnap.byOSDEnable=1;
    manualsnap.byLaneNo=1;

    imgBuff=nullptr;
}

TheMiddlewareHCNET::~TheMiddlewareHCNET()
{
    free(imgBuff);
    delete imgBuff;
    imgBuff=nullptr;

    TheMiddlewareHCNET::pThis=nullptr;

    delete  pTimerState;
    pTimerState=nullptr;

    if(NET_DVR_Cleanup_L!=nullptr){
        NET_DVR_Cleanup_L();
    }

    if(pDLL!=nullptr && pDLL->isLoaded()){
        pDLL->unload();
    }

    delete pDLL;
    pDLL=nullptr;
}

bool TheMiddlewareHCNET::initializationParameter()
{
    pDLL=new QLibrary("HCNetSDK",this);/* windows下不支持设置动态库路径 */
    //pDLL=new QLibrary (QDir::toNativeSeparators(QString("%1/%2").arg(QCoreApplication::applicationDirPath()).arg("Plugins/HCNetSDK/libhcnetsdk")),this) ;

    if(pDLL->load()){
        NET_DVR_SetExceptionCallBack_V30_L=reinterpret_cast<NET_DVR_SetExceptionCallBack_V30FUN>(pDLL->resolve("NET_DVR_SetExceptionCallBack_V30"));
        NET_DVR_SetSDKInitCfg_L=reinterpret_cast<NET_DVR_SetSDKInitCfgFUN>(pDLL->resolve("NET_DVR_SetSDKInitCfg"));
        NET_DVR_Cleanup_L=reinterpret_cast<NET_DVR_CleanupFUN>(pDLL->resolve("NET_DVR_Cleanup"));
        NET_DVR_Init_L=reinterpret_cast<NET_DVR_InitFUN>(pDLL->resolve("NET_DVR_Init"));
        NET_DVR_Login_V40_L=reinterpret_cast<NET_DVR_Login_V40FUN>(pDLL->resolve("NET_DVR_Login_V40"));
        NET_DVR_Logout_L=reinterpret_cast<NET_DVR_LogoutFUN>(pDLL->resolve("NET_DVR_Logout"));
        NET_DVR_ChangeWndResolution_L=reinterpret_cast<NET_DVR_ChangeWndResolutionFUN>(pDLL->resolve("NET_DVR_ChangeWndResolution"));
        NET_DVR_CaptureJPEGPicture_NEW_L=reinterpret_cast<NET_DVR_CaptureJPEGPicture_NEWFUN>(pDLL->resolve("NET_DVR_CaptureJPEGPicture_NEW"));
        NET_DVR_CaptureJPEGPicture_L=reinterpret_cast<NET_DVR_CaptureJPEGPictureFUN>(pDLL->resolve("NET_DVR_CaptureJPEGPicture"));
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
        NET_DVR_CloseAlarmChan_V30_L=reinterpret_cast<NET_DVR_CloseAlarmChan_V30FUN>(pDLL->resolve("NET_DVR_CloseAlarmChan_V30"));
        NET_DVR_SetupAlarmChan_V41_L=reinterpret_cast<NET_DVR_SetupAlarmChan_V41FUN>(pDLL->resolve("NET_DVR_SetupAlarmChan_V41"));
        NET_DVR_SetDVRMessageCallBack_V31_L=reinterpret_cast<NET_DVR_SetDVRMessageCallBack_V31FUN>(pDLL->resolve("NET_DVR_SetDVRMessageCallBack_V31"));
        NET_DVR_ContinuousShoot_L=reinterpret_cast<NET_DVR_ContinuousShootFUN>(pDLL->resolve("NET_DVR_ContinuousShoot"));
        NET_DVR_ManualSnap_L=reinterpret_cast<NET_DVR_ManualSnapFUN>(pDLL->resolve("NET_DVR_ManualSnap"));

        /* 设置动态库路径 */
        NET_SDK_INIT_CFG_TYPE cfgType=NET_SDK_INIT_CFG_SDK_PATH;
        QString path= QDir::toNativeSeparators(QString("%1/%2").arg(QCoreApplication::applicationDirPath()).arg("Plugins/HCNetSDK"));
        strcpy(SDKPath.sPath,path.toLocal8Bit().data());
        if(NET_DVR_SetSDKInitCfg_L!=nullptr && NET_DVR_SetSDKInitCfg_L(cfgType,&SDKPath)){
             NET_DVR_SetSDKInitCfg_L(cfgType,&SDKPath);
             emit messageSignal(ZBY_LOG("INFO"),tr("The dynamic library path was set successfully"));
        }

        if(nullptr!= NET_DVR_Init_L && NET_DVR_Init_L()){
            emit messageSignal(ZBY_LOG("INFO"),tr("Dynamic library initialization succeeded"));

            if(imgBuff==nullptr){
                imgBuff=static_cast<char*>(malloc(charLen* sizeof(char)));
            }

            if(NET_DVR_SetExceptionCallBack_V30_L!=nullptr && NET_DVR_SetExceptionCallBack_V30_L(0,nullptr,TheMiddlewareHCNET::exceptionCallBack_V30,this)){
                emit messageSignal(ZBY_LOG("INFO"),tr("Set exception callback successful"));
                // NET_DVR_SetLogToFile_L(3, QString(".\\Log\\sdkLog").toLatin1().data(), true);
                NET_DVR_SetConnectTime_L(10000,0);
                NET_DVR_SetReconnect_L(10000,1);
                NET_DVR_SetRecvTimeOut_L(1000);
            }

            /*****************************
            * @brief:交通系列布防信息回调
            ******************************/
            if(NET_DVR_SetDVRMessageCallBack_V31_L!=nullptr && NET_DVR_SetDVRMessageCallBack_V31_L(TheMiddlewareHCNET::exceptionMSGCallBack_V31,this)){
                emit messageSignal(ZBY_LOG("INFO"),tr("Setup defense callback successful"));
            }

            if(pTimerState==nullptr){
                pTimerState=new QTimer (this);
                connect(pTimerState,SIGNAL(timeout()),this,SLOT(getDeviceStatusSlot()));
                pTimerState->start(12000);/* 10秒检测一次相机状态 */
            }
            return  true;
        }
        else if(nullptr!=NET_DVR_Cleanup_L && NET_DVR_Cleanup_L()){
            emit messageSignal(ZBY_LOG("ERROR"),tr("Dynamic library initialization failed"));
        }
        else {
            emit messageSignal(ZBY_LOG("ERROR"),tr("Dynamic library cleanup failed"));
        }
        if(NET_DVR_GetLastError_L!=nullptr){
            emit messageSignal(ZBY_LOG("ERROR"),tr("Dynamic library cleanup failed <errorCode=%1>").arg(NET_DVR_GetLastError_L()));
        }
    }
    else {
        emit messageSignal(ZBY_LOG("ERROR"),tr("Load The Dynamic Error<errorCode=%1>").arg(pDLL->errorString()));
    }
    return false;
}


void TheMiddlewareHCNET::simulationCaptureSlot(int ID)
{
    bool cap=true;

    if(NET_DVR_RemoteControl_L !=nullptr && !NET_DVR_RemoteControl_L(ID,NET_DVR_CHECK_USER_STATUS,nullptr,4)){
        emit pThis->signal_pictureStream(ID,nullptr);/* 保证识别流程完成(识别流程需要完整图片编号) */
        emit messageSignal(ZBY_LOG("ERROR"),tr("IP=%1 Put Command Error<errorCode=%2>").arg(QString::fromLocal8Bit(logInfoMap.value(ID).sDeviceAddress)).arg(NET_DVR_GetLastError_L()));

        return;
    }

    switch (CAMERA_TYPE) {
    case 1:
        {
            LPDWORD dataLen=nullptr;
            /* 手动触发抓拍保存到内存 */
            if(NET_DVR_CaptureJPEGPicture_NEW_L!=nullptr && NET_DVR_CaptureJPEGPicture_NEW_L(ID,1,&pJpegFile,imgBuff,charLen,dataLen)){
                QByteArray arrayJpg(imgBuff,*dataLen);
                emit signal_pictureStream(ID,arrayJpg);
                emit messageSignal(ZBY_LOG("INFO"), tr("IP=%1 Put Command Sucess").arg(QString::fromLocal8Bit(logInfoMap.value(ID).sDeviceAddress)));

                arrayJpg.clear();
                delete  dataLen;
                dataLen=nullptr;
            }
            else {
                cap=false;
                }
        }
        break;
    case 2:
        {
            NET_DVR_PLATE_RESULT result={};
            result.dwSize=sizeof (result);
            result.pBuffer1=reinterpret_cast<unsigned char*>(imgBuff);
            /* 手动触发抓拍，SDK提示做测试使用 */
            if(NET_DVR_ManualSnap_L!=nullptr && NET_DVR_ManualSnap_L(ID,&manualsnap,&result)){
                QByteArray arrayJpg(imgBuff,IMG_BYTE);
                emit signal_pictureStream(ID,arrayJpg);
                emit messageSignal(ZBY_LOG("INFO"), tr("IP=%1 Put Command Sucess").arg(QString::fromLocal8Bit(logInfoMap.value(ID).sDeviceAddress)));

                arrayJpg.clear();
            }
            else {
                cap=false;
            }
        }
        break;
    case 3:
        {
            if(NET_DVR_ContinuousShoot_L!=nullptr){/* 网络触发抓拍 */
                int rul=NET_DVR_ContinuousShoot_L(ID,&snapcfg);
                if(rul){
                    emit messageSignal(ZBY_LOG("INFO"), tr("IP=%1 Put Command Sucess").arg(QString::fromLocal8Bit(logInfoMap.value(ID).sDeviceAddress)));
                }
                else {
                    cap=false;
                }
            }
        }
        break;
    }

    if(!cap){
        emit pThis->signal_pictureStream(ID,nullptr);/* 保证识别流程完成(识别流程需要完整图片编号) */
        //emit pictureStreamSignal(nullptr,imgNumber,imgTime);/* 保证识别流程完成(识别流程需要完整图片编号) */
        if(NET_DVR_GetLastError_L!=nullptr){
            emit messageSignal(ZBY_LOG("ERROR"),tr("IP=%1 Put Command Error<errorCode=%2>").arg(QString::fromLocal8Bit(logInfoMap.value(ID).sDeviceAddress)).arg(NET_DVR_GetLastError_L()));
        }
    }
}

void TheMiddlewareHCNET::liftingElectronicRailingSlot(bool gate)
{
    Q_UNUSED(gate);
}

void TheMiddlewareHCNET::transparentTransmission485Slot(const QString &msg)
{
    Q_UNUSED(msg);
}

void TheMiddlewareHCNET::openTheVideoSlot(int ID,bool play,quint64 winID)
{
    if(play){
        NET_DVR_PREVIEWINFO struPlayInfo = {};
        //struPlayInfo.hPlayWnd    =static_cast<HWND>(winID); /* linux */
        struPlayInfo.hPlayWnd= reinterpret_cast<HWND>(winID);/* windows */
        struPlayInfo.lChannel     = 1;       /* 预览通道号 */
        struPlayInfo.dwStreamType = 0;       /* 0-主码流，1-子码流，2-码流3，3-码流4，以此类推 */
        struPlayInfo.dwLinkMode   = 1;       /* 0- TCP方式，1- UDP方式，2- 多播方式，3- RTP方式，4-RTP/RTSP，5-RSTP/HTTP */
        struPlayInfo.bBlocked     = 0;       /* 0- 非阻塞取流，1- 阻塞取流 */

        if(NET_DVR_RealPlay_V40_L !=nullptr){
            streamID =NET_DVR_RealPlay_V40_L(ID,&struPlayInfo,nullptr,nullptr);
            if(streamID==-1){
                 emit messageSignal(ZBY_LOG("ERROR"), tr("IP=%1 Open Stream Error<errorCode=%2>").arg(QString::fromLocal8Bit(logInfoMap.value(ID).sDeviceAddress)).arg(NET_DVR_GetLastError_L()));
            }
            else {
                emit messageSignal(ZBY_LOG("INFO"),tr("IP=%1 Open Stream Sucess").arg(QString::fromLocal8Bit(logInfoMap.value(ID).sDeviceAddress)));
            }
        }
    }
    else {
        if(NET_DVR_StopRealPlay_L !=nullptr && streamID!=-1 && NET_DVR_StopRealPlay_L(streamID)){
            emit messageSignal(ZBY_LOG("INFO"), tr("IP=%1 Stop Stream sSucess").arg(QString::fromLocal8Bit(logInfoMap.value(ID).sDeviceAddress)));
        }
//            else {
//                emit messageSignal(ZBY_LOG("ERROR"), tr("IP=%1 Stop Stream Error<errorCode=%2>").arg(camerIp).arg(NET_DVR_GetLastError_L()));
//            }
    }
}

void TheMiddlewareHCNET::releaseResourcesSlot()
{
    if(pTimerState!=nullptr && pTimerState->isActive()){
         pTimerState->stop();
    }
    if(NET_DVR_SetConnectTime_L!=nullptr){
         NET_DVR_SetConnectTime_L(1,0);/* 设置网络连接超时时间和连接尝试次数 */
    }
    foreach ( auto handID, alarmInfoMap.keys()) {
        if(NET_DVR_CloseAlarmChan_V30_L!=nullptr){
            NET_DVR_CloseAlarmChan_V30_L(handID);
        }
    }
    if(streamID!=-1 && NET_DVR_StopRealPlay_L !=nullptr){
        NET_DVR_StopRealPlay_L(streamID);
    }
    foreach ( auto userID, logInfoMap.keys()) {
        if(NET_DVR_Logout_L !=nullptr){
            NET_DVR_Logout_L(userID);
        }
    }
}

void TheMiddlewareHCNET::initCameraSlot(const QString &localAddr, const QString &addr, const int &port,const QString &user,const QString &pow)
{
    if(!isSDKInit){
        if(!initializationParameter()){/* 动态库初始化失败就不登录相机 */
            return;
        }
        isSDKInit=true;
    }
    this->localAddr=localAddr;

    messageSignal(ZBY_LOG("INFO"),QString("IP=%1 Camera logging in").arg(addr));

    NET_DVR_USER_LOGIN_INFO LoginInfo={};
    strcpy(LoginInfo.sDeviceAddress,addr.toLatin1().data());
    strcpy(LoginInfo.sUserName,user.toLatin1().data());
    strcpy(LoginInfo.sPassword,pow.toLatin1().data());
    LoginInfo.wPort=static_cast<quint16>(port);
    LoginInfo.bUseAsynLogin=0;
    LoginInfo.cbLoginResult=TheMiddlewareHCNET::loginResultCallBack;
    LoginInfo.pUser=&LoginInfo;

    if(NET_DVR_Login_V40_L !=nullptr){/* 登录设备 */
        long ID = NET_DVR_Login_V40_L(&LoginInfo,&DeviceInfo);
        //Q_UNUSED(ID);
        if(ID>-1){
            logInfoMap.insert(ID,LoginInfo);
            emit signal_setCameraID(ID,addr);
            emit messageSignal(ZBY_LOG("INFO"),tr("IP=%1 Camera login successful<Code=%2>").arg(addr).arg(ID));
            /*****************************
            * @brief:交通系列，布防。
            ******************************/
            if(NET_DVR_SetupAlarmChan_V41_L!=nullptr){
                NET_DVR_SETUPALARM_PARAM aram={};
                aram.dwSize=sizeof (NET_DVR_SETUPALARM_PARAM);
                aram.byAlarmInfoType=1;
                aram.byLevel=1;
                long lHandle= NET_DVR_SetupAlarmChan_V41_L(ID,&aram);
                if(lHandle<0 && NET_DVR_GetLastError_L!=nullptr){
                    emit messageSignal(ZBY_LOG("ERROR"),tr("IP=%1 Camera Aram Error<errorCode=%2>").arg(addr).arg(NET_DVR_GetLastError_L()));
                }
                else{
                    emit messageSignal(ZBY_LOG("INFO"),tr("IP=%1 Camera Aram Success<Code=%2>").arg(addr).arg(lHandle));

                }
            }
        }
        else {
            logfalList.append(LoginInfo);

            if(NET_DVR_GetLastError_L!=nullptr){
                emit messageSignal(ZBY_LOG("ERROR"),tr("IP=%1 Login failed <errorCode=%2>").arg(addr).arg(NET_DVR_GetLastError_L()));
            }
        }
    }
}

WINBOOL TheMiddlewareHCNET::exceptionMSGCallBack_V31(LONG lCommand, NET_DVR_ALARMER *pAlarmer, char *pAlarmInfo, DWORD dwBufLen, void *pUser)
{
    Q_UNUSED((dwBufLen);
    Q_UNUSED(pUser);)
    /* 系统时间 */
    QString dateTime=QDateTime::currentDateTime().toString("yyyy-M-d h:m:s");

    if(lCommand == COMM_UPLOAD_PLATE_RESULT){
        NET_DVR_PLATE_RESULT struPlateResult={};
        memcpy(&struPlateResult, pAlarmInfo, sizeof(struPlateResult));

        QString plate=QString::fromLocal8Bit(struPlateResult.struPlateInfo.sLicense);
        if(plate!=QString::fromLocal8Bit("无车牌") && !plate.isEmpty()){
            plate=plate.mid(1);
        }

        //emit pThis->messageSignal(ZBY_LOG("INFO"),QString("Plate: %1").arg(plate));// 车牌号

        // 场景图
        if (struPlateResult.dwPicLen != 0 && struPlateResult.byResultType == 1 )
        {
            pThis->imgBuff=reinterpret_cast<char*>(struPlateResult.pBuffer1);
            QByteArray arrayJpg(pThis->imgBuff,struPlateResult.dwPicLen);

            QString color="";
            switch(struPlateResult.struPlateInfo.byColor)//车牌颜色
            {
            case VCA_BLUE_PLATE:
                color="蓝";
                break;
            case VCA_YELLOW_PLATE:
                color="黄";
                break;
            case VCA_WHITE_PLATE:
                color="白";
                break;
            case VCA_BLACK_PLATE:
                color="黑";
                break;
            default:
                break;
            }
            emit pThis->resultsTheLicensePlateSignal(pAlarmer->lUserID, plate,color,dateTime,arrayJpg);
            emit pThis->signal_pictureStream(pAlarmer->lUserID,arrayJpg);
            //emit pThis->messageSignal(ZBY_LOG("INFO"),tr("License Plate recognition results:%1 %2").arg(plate).arg(dateTime));
            arrayJpg.clear();
        }
        // 车牌图
//        if (struPlateResult.dwPicPlateLen != 0 && struPlateResult.byResultType == 1)
//        {
//            pThis->imgBuff=reinterpret_cast<char*>(struPlateResult.pBuffer2);
//            QByteArray arrayJpg(pThis->imgBuff,struPlateResult.dwPicPlateLen);
//        }

    }
    if(lCommand==COMM_ITS_PLATE_RESULT){
        NET_ITS_PLATE_RESULT struITSPlateResult={};
        memcpy(&struITSPlateResult, pAlarmInfo, sizeof(struITSPlateResult));

        QString plate=QString::fromLocal8Bit(struITSPlateResult.struPlateInfo.sLicense);
        if(plate!="无车牌" && !plate.isEmpty()){
            plate=plate.mid(1);
        }
        //emit pThis->messageSignal(ZBY_LOG("INFO"),QString("Plate: %1").arg(plate));// 车牌号

        // 场景图
        if (((struITSPlateResult.struPicInfo[0].dwDataLen != 0)&&(struITSPlateResult.struPicInfo[0].byType== 1))||(struITSPlateResult.struPicInfo[0].byType == 2))
        {
            pThis->imgBuff=reinterpret_cast<char*>(struITSPlateResult.struPicInfo[0].pBuffer);
            QByteArray arrayJpg(pThis->imgBuff,struITSPlateResult.struPicInfo[0].dwDataLen);

            QString color="";
            switch(struITSPlateResult.struPlateInfo.byColor)//车牌颜色
            {
            case VCA_BLUE_PLATE:
                color="蓝";
                break;
            case VCA_YELLOW_PLATE:
                color="黄";
                break;
            case VCA_WHITE_PLATE:
                color="白";
                break;
            case VCA_BLACK_PLATE:
                color="黑";
                break;
            default:
                break;
            }

            emit pThis->resultsTheLicensePlateSignal(pAlarmer->lUserID,plate,color,dateTime,arrayJpg);
            emit pThis->signal_pictureStream(pAlarmer->lUserID,arrayJpg);
            //emit pThis->messageSignal(ZBY_LOG("INFO"),tr("License Plate recognition results:%1 %2").arg(plate).arg(dateTime));
            arrayJpg.clear();
        }
        // 车牌图
//        if (((struITSPlateResult.struPicInfo[0].dwDataLen != 0)&&(struITSPlateResult.struPicInfo[0].byType== 0)))
//        {
//            pThis->imgBuff=reinterpret_cast<char*>(struITSPlateResult.struPicInfo[0].pBuffer);
//            QByteArray arrayJpg(pThis->imgBuff,struITSPlateResult.struPicInfo[0].dwDataLen);
//        }
    }

    return true;
}

void TheMiddlewareHCNET::exceptionCallBack_V30(DWORD dwType, LONG lUserID, LONG lHandle, void *pUser)
{
    Q_UNUSED(dwType);
    Q_UNUSED(pUser);
    Q_UNUSED(lHandle);
    if(pThis->NET_DVR_GetLastError_L()>0){
        emit pThis->messageSignal(ZBY_LOG("ERROR"),tr("IP=%1 Camrea Exception<errorCode=%2>").arg(QString::fromLocal8Bit(pThis->logInfoMap.value(lUserID).sDeviceAddress)).arg(QString::number(pThis->NET_DVR_GetLastError_L())));
    }
}

void TheMiddlewareHCNET::loginResultCallBack(LONG lUserID, DWORD dwResult, LPNET_DVR_DEVICEINFO_V30 lpDeviceInfo, void *pUser)
{
    Q_UNUSED(lpDeviceInfo);

    NET_DVR_USER_LOGIN_INFO LoginInfo=*((NET_DVR_USER_LOGIN_INFO*)pUser);

    if(dwResult==0){
        emit pThis->messageSignal(ZBY_LOG("ERROR"),tr("IP=%1 Camera Login Error<errorCode=%2>").arg(QString::fromLocal8Bit(LoginInfo.sDeviceAddress)).arg(pThis->NET_DVR_GetLastError_L()));
    }
    if(dwResult==1){
        emit pThis->messageSignal(ZBY_LOG("INFO"),tr("IP=%1 Camera Login Sucess").arg(QString::fromLocal8Bit(LoginInfo.sDeviceAddress)));
        emit pThis->signal_setCameraID(lUserID,QString::fromLocal8Bit(LoginInfo.sDeviceAddress));

        pThis->logInfoMap.insert(lUserID,LoginInfo);

        /*****************************
        * @brief:交通系列，布防。
        ******************************/
        if(pThis->NET_DVR_SetupAlarmChan_V41_L!=nullptr){
            NET_DVR_SETUPALARM_PARAM aram={};
            aram.dwSize=sizeof (NET_DVR_SETUPALARM_PARAM);
            aram.byAlarmInfoType=1;
            aram.byLevel=1;
            long lHandle= pThis->NET_DVR_SetupAlarmChan_V41_L(lUserID,&aram);
            if(lHandle<0){
                emit pThis->messageSignal(ZBY_LOG("ERROR"),tr("IP=%1 Camera Aram Error<errorCode=%2>").arg(QString::fromLocal8Bit(LoginInfo.sDeviceAddress)).arg(pThis->NET_DVR_GetLastError_L()));
            }
            else{
                emit pThis->messageSignal(ZBY_LOG("INFO"),tr("IP=%1 Camera Aram Success").arg(QString::fromLocal8Bit(LoginInfo.sDeviceAddress)));
                pThis-> alarmInfoMap.insert(lHandle,aram);
            }
        }
    }
}

void TheMiddlewareHCNET::getDeviceStatusSlot()
{
    foreach (auto id, logInfoMap.keys()) {
        if(NET_DVR_RemoteControl_L !=nullptr && NET_DVR_RemoteControl_L(id,NET_DVR_CHECK_USER_STATUS,nullptr,4)){
            emit equipmentStateSignal(id,true);
        }
        else {
            emit equipmentStateSignal(id,false);
//            initCameraSlot();/* 重新登录 */
//            NET_DVR_Login_V40_L(&LoginInfo,&DeviceInfo);
        }
    }
    if(logfalList.size()>0){/* 登录失败重新登录 */
        for(int i=0;i<logfalList.size();++i){
            if(NET_DVR_Login_V40_L !=nullptr){/* 登录设备 */
                long ID = NET_DVR_Login_V40_L(&logfalList[i],&DeviceInfo);
                //Q_UNUSED(ID);
                if(ID>-1){
                    logInfoMap.insert(ID,logfalList[i]);
                    emit signal_setCameraID(ID,QString::fromLocal8Bit(logfalList[i].sDeviceAddress));
                    emit messageSignal(ZBY_LOG("INFO"),tr("IP=%1 Camera login successful<Code=%2>").arg(QString::fromLocal8Bit(logfalList[i].sDeviceAddress)).arg(ID));
                    /*****************************
                    * @brief:交通系列，布防。
                    ******************************/
                    if(NET_DVR_SetupAlarmChan_V41_L!=nullptr){
                        NET_DVR_SETUPALARM_PARAM aram={};
                        aram.dwSize=sizeof (NET_DVR_SETUPALARM_PARAM);
                        aram.byAlarmInfoType=1;
                        aram.byLevel=1;
                        long lHandle= NET_DVR_SetupAlarmChan_V41_L(ID,&aram);
                        if(lHandle<0 && NET_DVR_GetLastError_L!=nullptr){
                            emit messageSignal(ZBY_LOG("ERROR"),tr("IP=%1 Camera Aram Error<errorCode=%2>").arg(QString::fromLocal8Bit(logfalList[i].sDeviceAddress)).arg(NET_DVR_GetLastError_L()));
                        }
                        else{
                            emit messageSignal(ZBY_LOG("INFO"),tr("IP=%1 Camera Aram Success<Code=%2>").arg(QString::fromLocal8Bit(logfalList[i].sDeviceAddress)).arg(lHandle));

                        }
                    }
                    logfalList.removeAt(i);/* 登录成功，删除列表项 */
                }
                else {
                    if(NET_DVR_GetLastError_L!=nullptr){
                        emit messageSignal(ZBY_LOG("ERROR"),tr("IP=%1 Login failed <errorCode=%2>").arg(QString::fromLocal8Bit(logfalList[i].sDeviceAddress)).arg(NET_DVR_GetLastError_L()));
                    }
                }
            }
        }
    }
}

void TheMiddlewareHCNET::resizeEventSlot()
{
//    if(dwResult){/* window不需要 */
//        if(NET_DVR_ChangeWndResolution_L !=nullptr){
//            NET_DVR_ChangeWndResolution_L(this->streamID);
//        }
//    }
}
