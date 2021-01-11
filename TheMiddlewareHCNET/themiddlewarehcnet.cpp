#if _MSC_VER >=1600    // MSVC2015>1899,对于MSVC2010以上版本都可以使用
#pragma execution_character_set("utf-8")
#endif

#include "themiddlewarehcnet.h"

TheMiddlewareHCNET* TheMiddlewareHCNET::pThis=nullptr;


TheMiddlewareHCNET::TheMiddlewareHCNET(QObject *parent)
{
    this->setParent(parent);

    streamID=-1;
    putID=-1;

    pDLL=nullptr;
    pDLLplay=nullptr;
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

    PlayM4_GetPort_L=nullptr;
    PlayM4_OpenStream_L=nullptr;
    PlayM4_SetDecCallBack_L=nullptr;
    PlayM4_Play_L=nullptr;
    PlayM4_InputData_L=nullptr;
    PlayM4_Stop_L=nullptr;
    PlayM4_CloseStream_L=nullptr;
    PlayM4_FreePort_L=nullptr;
    PlayM4_GetLastError_L=nullptr;

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
    qDebug()<<"~TheMiddlewareHCNET()";
    free(imgBuff);
    playMap.clear();
}

QString TheMiddlewareHCNET::InterfaceType()
{
    return "HCNET";
}

bool TheMiddlewareHCNET::initializationParameter()
{
    TheMiddlewareHCNET::pThis=this;;

    pDLLplay=new QLibrary("PlayCtrl",this);
    if(pDLLplay->load()){
        qDebug()<<"pDLLplay=new QLibrary(PlayCtrl,this)";
        PlayM4_GetPort_L=reinterpret_cast<PlayM4_GetPortFUN>(pDLLplay->resolve("PlayM4_GetPort"));
        PlayM4_OpenStream_L=reinterpret_cast<PlayM4_OpenStreamFUN>(pDLLplay->resolve("PlayM4_OpenStream"));
        PlayM4_Play_L=reinterpret_cast<PlayM4_PlayFUN>(pDLLplay->resolve("PlayM4_Play"));
        PlayM4_InputData_L=reinterpret_cast<PlayM4_InputDataFUN>(pDLLplay->resolve("PlayM4_InputData"));
        PlayM4_Stop_L=reinterpret_cast<PlayM4_StopFUN>(pDLLplay->resolve("PlayM4_Stop"));
        PlayM4_CloseStream_L=reinterpret_cast<PlayM4_CloseStreamFUN>(pDLLplay->resolve("PlayM4_CloseStream"));
        PlayM4_FreePort_L=reinterpret_cast<PlayM4_FreePortFUN>(pDLLplay->resolve("PlayM4_FreePort"));
        PlayM4_GetLastError_L=reinterpret_cast<PlayM4_GetLastErrorFUN>(pDLLplay->resolve("PlayM4_GetLastError"));
        PlayM4_SetDecCallBack_L=reinterpret_cast<PlayM4_SetDecCallBackFUN>(pDLLplay->resolve("PlayM4_SetDecCallBack"));
    }

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
             qInfo().noquote()<<"The dynamic library path was set successfully";
        }

        if(nullptr!= NET_DVR_Init_L && NET_DVR_Init_L()){
            emit messageSignal(ZBY_LOG("INFO"),tr("Dynamic library initialization succeeded"));
            qInfo().noquote()<<"Dynamic library initialization succeeded";

            if(imgBuff==nullptr){
                imgBuff=static_cast<char*>(malloc(charLen* sizeof(char)));
            }

            if(NET_DVR_SetExceptionCallBack_V30_L!=nullptr && NET_DVR_SetExceptionCallBack_V30_L(0,nullptr,TheMiddlewareHCNET::exceptionCallBack_V30,this)){
                emit messageSignal(ZBY_LOG("INFO"),tr("Set exception callback successful"));
                qInfo().noquote()<<"Set exception callback successful";
                NET_DVR_SetLogToFile_L(3, QString(".\\Log\\sdkLog").toLatin1().data(), true);
                NET_DVR_SetConnectTime_L(10000,0);
                NET_DVR_SetReconnect_L(10000,0);
                NET_DVR_SetRecvTimeOut_L(1000);
            }

            /*****************************
            * @brief:交通系列布防信息回调
            ******************************/
            if(NET_DVR_SetDVRMessageCallBack_V31_L!=nullptr && NET_DVR_SetDVRMessageCallBack_V31_L(TheMiddlewareHCNET::exceptionMSGCallBack_V31,this) && 3==CAMERA_TYPE){
                emit messageSignal(ZBY_LOG("INFO"),tr("Setup defense callback successful"));
                qInfo().noquote()<<"Setup defense callback successful";
            }

            if(pTimerState==nullptr){
                pTimerState=new QTimer (this);
                connect(pTimerState,SIGNAL(timeout()),this,SLOT(getDeviceStatusSlot()));
                pTimerState->start(15000);/* 15秒检测一次相机状态 */
            }
            return  true;
        }
        else if(nullptr!=NET_DVR_Cleanup_L && NET_DVR_Cleanup_L()){
            emit messageSignal(ZBY_LOG("ERROR"),tr("Dynamic library initialization failed"));
            qWarning().noquote()<<"Dynamic library initialization failed";
        }
        else {
            emit messageSignal(ZBY_LOG("ERROR"),tr("Dynamic library cleanup failed"));
            qWarning().noquote()<<"Dynamic library cleanup failed";
        }
        if(NET_DVR_GetLastError_L!=nullptr){
            emit messageSignal(ZBY_LOG("ERROR"),tr("Dynamic library cleanup failed <errorCode=%1>").arg(NET_DVR_GetLastError_L()));
            qWarning().noquote()<<QString("Dynamic library cleanup failed <errorCode=%1>").arg(NET_DVR_GetLastError_L());
        }
    }
    else {
        emit messageSignal(ZBY_LOG("ERROR"),tr("Load The Dynamic Error<errorCode=%1>").arg(pDLL->errorString()));
        qWarning().noquote()<<QString("Load The Dynamic Error<errorCode=%1>").arg(pDLL->errorString());
    }
    return false;
}


void TheMiddlewareHCNET::simulationCaptureSlot(int ID)
{
    bool cap=true;

    if(NET_DVR_RemoteControl_L !=nullptr && !NET_DVR_RemoteControl_L(ID,NET_DVR_CHECK_USER_STATUS,nullptr,4)){
        emit pThis->signal_pictureStream(ID,nullptr);/* 保证识别流程完成(识别流程需要完整图片编号) */
        emit messageSignal(ZBY_LOG("ERROR"),tr("IP=%1 Put Command Error<errorCode=%2>").arg(QString::fromLocal8Bit(logInfoMap.value(ID).sDeviceAddress)).arg(NET_DVR_GetLastError_L()));
        qWarning().noquote()<<QString("IP=%1 Put Command Error<errorCode=%2>").arg(QString::fromLocal8Bit(logInfoMap.value(ID).sDeviceAddress)).arg(NET_DVR_GetLastError_L());
        return;
    }

    switch (CAMERA_TYPE) {
    case 1:
        {
            LPDWORD dataLen=nullptr;
            /* 手动触发抓拍保存到内存 */
            if(NET_DVR_CaptureJPEGPicture_NEW_L!=nullptr && NET_DVR_CaptureJPEGPicture_NEW_L(ID,1,&pJpegFile,imgBuff,charLen,dataLen)){
                QByteArray arrayJpg(imgBuff,IMG_BYTE);
                emit signal_pictureStream(ID,arrayJpg);
                emit messageSignal(ZBY_LOG("INFO"), tr("IP=%1 Put Command Sucess").arg(QString::fromLocal8Bit(logInfoMap.value(ID).sDeviceAddress)));
                qInfo().noquote()<<QString("IP=%1 Put Command Sucess").arg(QString::fromLocal8Bit(logInfoMap.value(ID).sDeviceAddress));
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
                qInfo().noquote()<<QString("IP=%1 Put Command Sucess").arg(QString::fromLocal8Bit(logInfoMap.value(ID).sDeviceAddress));
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
                    qInfo().noquote()<<QString("IP=%1 Put Command Sucess").arg(QString::fromLocal8Bit(logInfoMap.value(ID).sDeviceAddress));
                }
                else {
                    cap=false;
                }
            }
        }
        break;
    case 4:
        putID=ID;
        qDebug().noquote()<<QString::fromLocal8Bit(logInfoMap.value(ID).sDeviceAddress)<<":"<<playMap.value(putID)<<"[stream]|[camID]"<<putID;
        qDebug().noquote()<<QString("IP=%1 Start Put Command ").arg(QString::fromLocal8Bit(logInfoMap.value(ID).sDeviceAddress));
        break;
    }

    if(!cap){
        emit pThis->signal_pictureStream(ID,nullptr);/* 保证识别流程完成(识别流程需要完整图片编号) */
        //emit pictureStreamSignal(nullptr,imgNumber,imgTime);/* 保证识别流程完成(识别流程需要完整图片编号) */
        if(NET_DVR_GetLastError_L!=nullptr){
            emit messageSignal(ZBY_LOG("ERROR"),tr("IP=%1 Put Command Error<errorCode=%2>").arg(QString::fromLocal8Bit(logInfoMap.value(ID).sDeviceAddress)).arg(NET_DVR_GetLastError_L()));
            qWarning().noquote()<<QString("IP=%1 Put Command Error<errorCode=%2>").arg(QString::fromLocal8Bit(logInfoMap.value(ID).sDeviceAddress)).arg(NET_DVR_GetLastError_L());
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
    if(4 == CAMERA_TYPE){
        return;
    }
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
                qWarning().noquote()<<QString("IP=%1 Open Stream Error<errorCode=%2>").arg(QString::fromLocal8Bit(logInfoMap.value(ID).sDeviceAddress)).arg(NET_DVR_GetLastError_L());
            }
            else {
                emit messageSignal(ZBY_LOG("INFO"),tr("IP=%1 Open Stream Sucess").arg(QString::fromLocal8Bit(logInfoMap.value(ID).sDeviceAddress)));
                qInfo().noquote()<<QString("IP=%1 Open Stream Sucess").arg(QString::fromLocal8Bit(logInfoMap.value(ID).sDeviceAddress));
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
    if(pTimerState!=nullptr){
         pTimerState->stop();
    }
//    if(NET_DVR_SetConnectTime_L!=nullptr){
//         NET_DVR_SetConnectTime_L(1,0);/* 设置网络连接超时时间和连接尝试次数 */
//    }
    foreach ( auto handID, alarmInfoMap.keys()) {
        if(NET_DVR_CloseAlarmChan_V30_L!=nullptr){
            NET_DVR_CloseAlarmChan_V30_L(handID);
        }
    }
    if(streamID!=-1 && NET_DVR_StopRealPlay_L !=nullptr){
        NET_DVR_StopRealPlay_L(streamID);
    }
    if(4==CAMERA_TYPE){
        foreach (auto nPort, playMap.values()) {
            if(-1!=nPort){
                if(NET_DVR_StopRealPlay_L !=nullptr){
                    NET_DVR_StopRealPlay_L(nPort);
                }
                /* 释放播放库资源 */
                if(nullptr!=PlayM4_Stop_L){
                    PlayM4_Stop_L(nPort);
                }
                if(nullptr!=PlayM4_CloseStream_L){
                    PlayM4_CloseStream_L(nPort);
                }
                if(nullptr!=PlayM4_FreePort_L){
                    PlayM4_FreePort_L(nPort);
                }
            }
        }
    }

    foreach ( auto userID, logInfoMap.keys()) {
        if(NET_DVR_Logout_L !=nullptr){
            NET_DVR_Logout_L(userID);
        }
    }
    if(NET_DVR_Cleanup_L!=nullptr){
        NET_DVR_Cleanup_L();
    }
//    if(pDLL!=nullptr && pDLL->isLoaded()){
//        pDLL->unload();
//    }

    qDebug().noquote()<<"releaseResourcesSlot()";
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
    qDebug().noquote()<<QString("IP=%1 Camera logging in").arg(addr);

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
            qInfo().noquote()<<QString("IP=%1 Camera login successful<Code=%2>").arg(addr).arg(ID);
            if(NET_DVR_SetupAlarmChan_V41_L!=nullptr && 3==CAMERA_TYPE){
                /*****************************
                * @brief:交通系列，布防。
                ******************************/
                NET_DVR_SETUPALARM_PARAM aram={};
                aram.dwSize=sizeof (NET_DVR_SETUPALARM_PARAM);
                aram.byAlarmInfoType=1;
                aram.byLevel=1;
                long lHandle= NET_DVR_SetupAlarmChan_V41_L(ID,&aram);
                if(lHandle<0 && NET_DVR_GetLastError_L!=nullptr){
                    emit messageSignal(ZBY_LOG("ERROR"),tr("IP=%1 Camera Aram Error<errorCode=%2>").arg(addr).arg(NET_DVR_GetLastError_L()));
                    qWarning().noquote()<<QString("IP=%1 Camera Aram Error<errorCode=%2>").arg(addr).arg(NET_DVR_GetLastError_L());
                }
                else{
                    emit messageSignal(ZBY_LOG("INFO"),tr("IP=%1 Camera Aram Success<Code=%2>").arg(addr).arg(lHandle));
                    qInfo().noquote()<<QString("IP=%1 Camera Aram Success<Code=%2>").arg(addr).arg(lHandle);
                }
            }
            if(4==CAMERA_TYPE){
                /*****************************
                * @brief: 登录成功,打开预览-------------------------取图使用
                ******************************/
                initVideoStream(ID,true);
            }
        }
        else {
            logfalList.append(LoginInfo);

            if(NET_DVR_GetLastError_L!=nullptr){
                emit messageSignal(ZBY_LOG("ERROR"),tr("IP=%1 Login failed <errorCode=%2>").arg(addr).arg(NET_DVR_GetLastError_L()));
                qWarning().noquote()<<QString("IP=%1 Login failed <errorCode=%2>").arg(addr).arg(NET_DVR_GetLastError_L());
            }
        }
    }
}

int TheMiddlewareHCNET::exceptionMSGCallBack_V31(LONG lCommand, NET_DVR_ALARMER *pAlarmer, char *pAlarmInfo, DWORD dwBufLen, void *pUser)
{
    Q_UNUSED((dwBufLen);
    Q_UNUSED(pUser);)
    /* 系统时间 */
    QString dateTime=QDateTime::currentDateTime().toString("yyyy-M-d h:m:s");

    if(lCommand == COMM_UPLOAD_PLATE_RESULT){
        NET_DVR_PLATE_RESULT struPlateResult={};
        memcpy(&struPlateResult, pAlarmInfo, sizeof(struPlateResult));

        QString plate=QString::fromLocal8Bit(struPlateResult.struPlateInfo.sLicense);
        if(plate!="无车牌" && !plate.isEmpty()){
            plate=plate.mid(1);
        }

        //emit pThis->messageSignal(ZBY_LOG("INFO"),QString("Plate: %1").arg(plate));/* 车牌号 */

        /* 场景图 */
        if (struPlateResult.dwPicLen != 0 && struPlateResult.byResultType == 1 )
        {
            pThis->imgBuff=reinterpret_cast<char*>(struPlateResult.pBuffer1);
            QByteArray arrayJpg(pThis->imgBuff,struPlateResult.dwPicLen);

            QString color="";
            switch(struPlateResult.struPlateInfo.byColor)/* 车牌颜色 */
            {
            case VCA_BLUE_PLATE:
                color=QString::fromLocal8Bit("蓝");
                break;
            case VCA_YELLOW_PLATE:
                color=QString::fromLocal8Bit("黄");
                break;
            case VCA_WHITE_PLATE:
                color=QString::fromLocal8Bit("白");
                break;
            case VCA_BLACK_PLATE:
                color=QString::fromLocal8Bit("黑");
                break;
            default:
                break;
            }
            emit pThis->resultsTheLicensePlateSignal(pAlarmer->lUserID, plate,color,dateTime,arrayJpg);
            emit pThis->signal_pictureStream(pAlarmer->lUserID,arrayJpg);
            //emit pThis->messageSignal(ZBY_LOG("INFO"),tr("License Plate recognition results:%1 %2").arg(plate).arg(dateTime));
            arrayJpg.clear();
        }
        /* 车牌图 */
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
        //emit pThis->messageSignal(ZBY_LOG("INFO"),QString("Plate: %1").arg(plate));/* 车牌号 */

        /* 场景图 */
        if (((struITSPlateResult.struPicInfo[0].dwDataLen != 0)&&(struITSPlateResult.struPicInfo[0].byType== 1))||(struITSPlateResult.struPicInfo[0].byType == 2))
        {
            pThis->imgBuff=reinterpret_cast<char*>(struITSPlateResult.struPicInfo[0].pBuffer);
            QByteArray arrayJpg(pThis->imgBuff,struITSPlateResult.struPicInfo[0].dwDataLen);

            QString color="";
            switch(struITSPlateResult.struPlateInfo.byColor)/* 车牌颜色 */
            {
            case VCA_BLUE_PLATE:
                color=QString::fromLocal8Bit("蓝");
                break;
            case VCA_YELLOW_PLATE:
                color=QString::fromLocal8Bit("黄");
                break;
            case VCA_WHITE_PLATE:
                color=QString::fromLocal8Bit("白");
                break;
            case VCA_BLACK_PLATE:
                color=QString::fromLocal8Bit("黑");
                break;
            default:
                break;
            }

            emit pThis->resultsTheLicensePlateSignal(pAlarmer->lUserID,plate,color,dateTime,arrayJpg);
            emit pThis->signal_pictureStream(pAlarmer->lUserID,arrayJpg);
            //emit pThis->messageSignal(ZBY_LOG("INFO"),tr("License Plate recognition results:%1 %2").arg(plate).arg(dateTime));
            arrayJpg.clear();
        }
        /* 车牌图 */
//        if (((struITSPlateResult.struPicInfo[0].dwDataLen != 0)&&(struITSPlateResult.struPicInfo[0].byType== 0)))
//        {
//            pThis->imgBuff=reinterpret_cast<char*>(struITSPlateResult.struPicInfo[0].pBuffer);
//            QByteArray arrayJpg(pThis->imgBuff,struITSPlateResult.struPicInfo[0].dwDataLen);
//        }
    }

    return true;
}

//bool TheMiddlewareHCNET::yv12ToRGB888(const unsigned char *yv12, unsigned char *rgb888, int width, int height)
//{
//    if ((width < 1) || (height < 1) || (yv12 == NULL) || (rgb888 == NULL)) {
//        return false;
//    }

//    int len = width * height;
//    unsigned char const *yData = yv12;
//    unsigned char const *vData = &yData[len];
//    unsigned char const *uData = &vData[len >> 2];

//    int rgb[3];
//    int yIdx, uIdx, vIdx, idx;

//    for (int i = 0; i < height; ++i) {
//        for (int j = 0; j < width; ++j) {
//            yIdx = i * width + j;
//            vIdx = (i / 2) * (width / 2) + (j / 2);
//            uIdx = vIdx;

//            rgb[0] = static_cast<int>(yData[yIdx] + 1.370705 * (vData[uIdx] - 128));
//            rgb[1] = static_cast<int>(yData[yIdx] - 0.698001 * (uData[uIdx] - 128) - 0.703125 * (vData[vIdx] - 128));
//            rgb[2] = static_cast<int>(yData[yIdx] + 1.732446 * (uData[vIdx] - 128));

//            for (int k = 0; k < 3; ++k) {
//                idx = (i * width + j) * 3 + k;
//                if ((rgb[k] >= 0) && (rgb[k] <= 255)) {
//                    rgb888[idx] = static_cast<unsigned char>(rgb[k]);
//                } else {
//                    rgb888[idx] = (rgb[k] < 0) ? (0) : (255);
//                }
//            }
//        }
//    }
//    return true;
//}

static int Table_fv1[256] = { -180, -179, -177, -176, -174, -173, -172, -170, -169, -167, -166, -165, -163, -162, -160, -159, -158, -156, -155, -153, -152, -151, -149, -148, -146, -145, -144, -142, -141, -139, -138, -137,  -135, -134, -132, -131, -130, -128, -127, -125, -124, -123, -121, -120, -118, -117, -115, -114, -113, -111, -110, -108, -107, -106, -104, -103, -101, -100, -99, -97, -96, -94, -93, -92, -90,  -89, -87, -86, -85, -83, -82, -80, -79, -78, -76, -75, -73, -72, -71, -69, -68, -66, -65, -64,-62, -61, -59, -58, -57, -55, -54, -52, -51, -50, -48, -47, -45, -44, -43, -41, -40, -38, -37,  -36, -34, -33, -31, -30, -29, -27, -26, -24, -23, -22, -20, -19, -17, -16, -15, -13, -12, -10, -9, -8, -6, -5, -3, -2, 0, 1, 2, 4, 5, 7, 8, 9, 11, 12, 14, 15, 16, 18, 19, 21, 22, 23, 25, 26, 28, 29, 30, 32, 33, 35, 36, 37, 39, 40, 42, 43, 44, 46, 47, 49, 50, 51, 53, 54, 56, 57, 58, 60, 61, 63, 64, 65, 67, 68, 70, 71, 72, 74, 75, 77, 78, 79, 81, 82, 84, 85, 86, 88, 89, 91, 92, 93, 95, 96, 98, 99, 100, 102, 103, 105, 106, 107, 109, 110, 112, 113, 114, 116, 117, 119, 120, 122, 123, 124, 126, 127, 129, 130, 131, 133, 134, 136, 137, 138, 140, 141, 143, 144, 145, 147, 148,  150, 151, 152, 154, 155, 157, 158, 159, 161, 162, 164, 165, 166, 168, 169, 171, 172, 173, 175, 176, 178 };
static int Table_fv2[256] = { -92, -91, -91, -90, -89, -88, -88, -87, -86, -86, -85, -84, -83, -83, -82, -81, -81, -80, -79, -78, -78, -77, -76, -76, -75, -74, -73, -73, -72, -71, -71, -70, -69, -68, -68, -67, -66, -66, -65, -64, -63, -63, -62, -61, -61, -60, -59, -58, -58, -57, -56, -56, -55, -54, -53, -53, -52, -51, -51, -50, -49, -48, -48, -47, -46, -46, -45, -44, -43, -43, -42, -41, -41, -40, -39, -38, -38, -37, -36, -36, -35, -34, -33, -33, -32, -31, -31, -30, -29, -28, -28, -27, -26, -26, -25, -24, -23, -23, -22, -21, -21, -20, -19, -18, -18, -17, -16, -16, -15, -14, -13, -13, -12, -11, -11, -10, -9, -8, -8, -7, -6, -6, -5, -4, -3, -3, -2, -1, 0, 0, 1, 2, 2, 3, 4, 5, 5, 6, 7, 7, 8, 9, 10, 10, 11, 12, 12, 13, 14, 15, 15, 16, 17, 17, 18, 19, 20, 20, 21, 22, 22, 23, 24, 25, 25, 26, 27, 27, 28, 29, 30, 30, 31, 32, 32, 33, 34, 35, 35, 36, 37, 37, 38, 39, 40, 40, 41, 42, 42, 43, 44, 45, 45, 46, 47, 47, 48, 49, 50, 50, 51, 52, 52, 53, 54, 55, 55, 56, 57, 57, 58, 59, 60, 60, 61, 62, 62, 63, 64, 65, 65, 66, 67, 67, 68, 69, 70, 70, 71, 72, 72, 73, 74, 75, 75, 76, 77, 77, 78, 79, 80, 80, 81, 82, 82, 83, 84, 85, 85, 86, 87, 87, 88, 89, 90, 90 };
static int Table_fu1[256] = { -44, -44, -44, -43, -43, -43, -42, -42, -42, -41, -41, -41, -40, -40, -40, -39, -39, -39, -38, -38, -38, -37, -37, -37, -36, -36, -36, -35, -35, -35, -34, -34, -33, -33, -33, -32, -32, -32, -31, -31, -31, -30, -30, -30, -29, -29, -29, -28, -28, -28, -27, -27, -27, -26, -26, -26, -25, -25, -25, -24, -24, -24, -23, -23, -22, -22, -22, -21, -21, -21, -20, -20, -20, -19, -19, -19, -18, -18, -18, -17, -17, -17, -16, -16, -16, -15, -15, -15, -14, -14, -14, -13, -13, -13, -12, -12, -11, -11, -11, -10, -10, -10, -9, -9, -9, -8, -8, -8, -7, -7, -7, -6, -6, -6, -5, -5, -5, -4, -4, -4, -3, -3, -3, -2, -2, -2, -1, -1, 0, 0, 0, 1, 1, 1, 2, 2, 2, 3, 3, 3, 4, 4, 4, 5, 5, 5, 6, 6, 6, 7, 7, 7, 8, 8, 8, 9, 9, 9, 10, 10, 11, 11, 11, 12, 12, 12, 13, 13, 13, 14, 14, 14, 15, 15, 15, 16, 16, 16, 17, 17, 17, 18, 18, 18, 19, 19, 19, 20, 20, 20, 21, 21, 22, 22, 22, 23, 23, 23, 24, 24, 24, 25, 25, 25, 26, 26, 26, 27, 27, 27, 28, 28, 28, 29, 29, 29, 30, 30, 30, 31, 31, 31, 32, 32, 33, 33, 33, 34, 34, 34, 35, 35, 35, 36, 36, 36, 37, 37, 37, 38, 38, 38, 39, 39, 39, 40, 40, 40, 41, 41, 41, 42, 42, 42, 43, 43 };
static int Table_fu2[256] = { -227, -226, -224, -222, -220, -219, -217, -215, -213, -212, -210, -208, -206, -204, -203, -201, -199, -197, -196, -194, -192, -190, -188, -187, -185, -183, -181, -180, -178, -176, -174, -173, -171, -169, -167, -165, -164, -162, -160, -158, -157, -155, -153, -151, -149, -148, -146, -144, -142, -141, -139, -137, -135, -134, -132, -130, -128, -126, -125, -123, -121, -119, -118, -116, -114, -112, -110, -109, -107, -105, -103, -102, -100, -98, -96, -94, -93, -91, -89, -87, -86, -84, -82, -80, -79, -77, -75, -73, -71, -70, -68, -66, -64, -63, -61, -59, -57, -55, -54, -52, -50, -48, -47, -45, -43, -41, -40, -38, -36, -34, -32, -31, -29, -27, -25, -24, -22, -20, -18, -16, -15, -13, -11, -9, -8, -6, -4, -2, 0, 1, 3, 5, 7, 8, 10, 12, 14, 15, 17, 19, 21, 23, 24, 26, 28, 30, 31, 33, 35, 37, 39, 40, 42, 44, 46, 47, 49, 51, 53, 54, 56, 58, 60, 62, 63, 65, 67, 69, 70, 72, 74, 76, 78, 79, 81, 83, 85, 86, 88, 90, 92, 93, 95, 97, 99, 101, 102, 104, 106, 108, 109, 111, 113, 115, 117, 118, 120, 122, 124, 125, 127, 129, 131, 133, 134, 136, 138, 140, 141, 143, 145, 147, 148, 150, 152, 154, 156, 157, 159, 161, 163, 164, 166, 168, 170, 172, 173, 175, 177, 179, 180, 182, 184, 186, 187, 189, 191, 193, 195, 196, 198, 200, 202, 203, 205, 207, 209, 211, 212, 214, 216, 218, 219, 221, 223, 225 };


void TheMiddlewareHCNET::yv12ToRGB888(int ID,int width,int height,unsigned char* yv12,long nPort)
{
    QScopedPointer<QImage> image(new QImage(width, height, QImage::Format_RGB888));
    unsigned char* rgb888=image->bits();

    if ((width < 1) || (height < 1) || (yv12 == nullptr) || (rgb888 == nullptr)) {
        emit signal_pictureStream(ID,nullptr);
        emit messageSignal(ZBY_LOG("WARNING"), tr("IP=%1 Put Command Sucess").arg(QString::fromLocal8Bit(logInfoMap.value(ID).sDeviceAddress)));
        qWarning().noquote()<<QString("IP=%1 Put Command Sucess").arg(QString::fromLocal8Bit(logInfoMap.value(ID).sDeviceAddress));

        if(PlayM4_GetLastError_L!=nullptr){
            emit messageSignal(ZBY_LOG("ERROR"),tr("IP=%1 Put Command Error<errorCode=%2>").arg(QString::fromLocal8Bit(logInfoMap.value(ID).sDeviceAddress)).arg(PlayM4_GetLastError_L(nPort)));
            qWarning().noquote()<<QString("IP=%1 Put Command Error<errorCode=%2>").arg(QString::fromLocal8Bit(logInfoMap.value(ID).sDeviceAddress)).arg(PlayM4_GetLastError_L(nPort));
        }
        return;
    }

    long len = width * height;
    unsigned char const *yData = yv12;
    unsigned char const *vData = &yData[len];
    unsigned char const *uData = &vData[len >> 2];

    int rgb[3];
    int yIdx, uIdx, vIdx, idx;

    /*****************************
    * @brief:替换法
    ******************************/
//    for (int i = 0; i < height; ++i) {
//        for (int j = 0; j < width; ++j) {
//            yIdx = i * width + j;
//            vIdx = (i / 2) * (width / 2) + (j / 2);
//            uIdx = vIdx;

//            rgb[0] = static_cast<int>(yData[yIdx] + 1.370705 * (vData[uIdx] - 128));
//            rgb[1] = static_cast<int>(yData[yIdx] - 0.698001 * (uData[uIdx] - 128) - 0.703125 * (vData[vIdx] - 128));
//            rgb[2] = static_cast<int>(yData[yIdx] + 1.732446 * (uData[vIdx] - 128));

//            for (int k = 0; k < 3; ++k) {
//                idx = (i * width + j) * 3 + k;
//                if ((rgb[k] >= 0) && (rgb[k] <= 255)) {
//                    rgb888[idx] = static_cast<unsigned char>(rgb[k]);
//                } else {
//                    rgb888[idx] = (rgb[k] < 0) ? (0) : (255);
//                }
//            }
//        }
//    }

    /*****************************
    * @brief:查表法
    ******************************/
    int rdif,invgdif,bdif;
    for (int i = 0;i < height;i++){
        for (int j = 0;j < width;j++){
            yIdx = i * width + j;
            vIdx = (i/2) * (width/2) + (j/2);
            uIdx = vIdx;

            rdif = Table_fv1[vData[vIdx]];
            invgdif = Table_fu1[uData[uIdx]] + Table_fv2[vData[vIdx]];
            bdif = Table_fu2[uData[uIdx]];

            rgb[0] = yData[yIdx] + rdif;
            rgb[1] = yData[yIdx] - invgdif;
            rgb[2] = yData[yIdx] + bdif;

            for (int k = 0;k < 3;k++){
                idx = (i * width + j) * 3 + k;
                if(rgb[k] >= 0 && rgb[k] <= 255)
                    rgb888[idx] = rgb[k];
                else
                    rgb888[idx] = (rgb[k] < 0)?0:255;
            }
        }
    }

    QByteArray arrayJpg(imgBuff,IMG_BYTE);
    QScopedPointer<QBuffer> buffer(new QBuffer(&arrayJpg));
    buffer->open(QIODevice::WriteOnly);
    image->save(buffer.data(),"jpg");
    buffer->close();
    signal_pictureStream(ID,arrayJpg);
    messageSignal(ZBY_LOG("INFO"), tr("IP=%1 Put Command Sucess").arg(QString::fromLocal8Bit(logInfoMap.value(ID).sDeviceAddress)));
    qInfo().noquote()<<QString("IP=%1 Put Command Sucess").arg(QString::fromLocal8Bit(logInfoMap.value(ID).sDeviceAddress));
    arrayJpg.clear();
}

void TheMiddlewareHCNET::DecCallBack(long nPort, char *pBuf, long nSize, FRAME_INFO *pFrameInfo, long luser, long nReserved2)
{
    Q_UNUSED(luser);
    Q_UNUSED(nReserved2);
    Q_UNUSED(nSize);

//    if(-1 != pThis->putID){
//        foreach (auto var, pThis->playMap.keys()) {
//            qDebug()<<pThis<<"key:"<<var<<"|"<<"value:"<<pThis->playMap.value(var);
//        }
//        qDebug()<<pThis<<nPort<<" [stream]|[camerID] " <<pThis->putID<<"------------------------------";
//    }
    if(-1 != pThis->putID  && pThis->playMap.key(nPort)==pThis->putID){
        long frameType = pFrameInfo->nType;
        int width = pFrameInfo->nWidth;
        int height = pFrameInfo->nHeight;
//        char *arr = new char[nSize];
//        memcpy(arr, pBuf, nSize);
        if (frameType == T_YV12) {
            QtConcurrent::run(pThis,&TheMiddlewareHCNET::yv12ToRGB888,pThis->putID,width,height,(unsigned char *)pBuf,nPort);
        }
        pThis->putID=-1;


//        int width = pFrameInfo->nWidth;
//        int height = pFrameInfo->nHeight;
//        QByteArray arrayJpg(pThis->imgBuff,IMG_BYTE);
//        QScopedPointer<QImage> image(new QImage(width, height, QImage::Format_RGB888));
//        pThis->putID=-1;
//        //视频数据是 T_YV12 音频数据是 T_AUDIO16
//        if (frameType == T_YV12) {
//            int width = pFrameInfo->nWidth;
//            int height = pFrameInfo->nHeight;
//            if (TheMiddlewareHCNET::yv12ToRGB888((unsigned char *)pBuf, (unsigned char*)pThis->imgBuff, width, height)) {
//                QByteArray arrayJpg(pThis->imgBuff,IMG_BYTE);
//                emit pThis->signal_pictureStream(pThis->playMap.value(nPort),arrayJpg);
//                emit pThis->messageSignal(ZBY_LOG("INFO"), tr("IP=%1 Put Command Sucess").arg(QString::fromLocal8Bit(pThis->logInfoMap.value(pThis->playMap.value(nPort)).sDeviceAddress)));
//                qInfo().noquote()<<QString("IP=%1 Put Command Sucess").arg(QString::fromLocal8Bit(pThis->logInfoMap.value(pThis->playMap.value(nPort)).sDeviceAddress));
//                arrayJpg.clear();
//            }

//            int width = pFrameInfo->nWidth;
//            int height = pFrameInfo->nHeight;
//            QByteArray arrayJpg(pThis->imgBuff,IMG_BYTE);
//            QScopedPointer<QImage> image(new QImage(width, height, QImage::Format_RGB888));
//            if (yv12ToRGB888((unsigned char *)pBuf, image->bits(), width, height)) {
//                QScopedPointer<QBuffer> buffer(new QBuffer(&arrayJpg));
//                buffer->open(QIODevice::WriteOnly);
//                image->save(buffer.data(),"jpg");
//                buffer->close();
//                emit pThis->signal_pictureStream(pThis->playMap.value(nPort),arrayJpg);
//                emit pThis->messageSignal(ZBY_LOG("INFO"), tr("IP=%1 Put Command Sucess").arg(QString::fromLocal8Bit(pThis->logInfoMap.value(pThis->playMap.value(nPort)).sDeviceAddress)));
//                qInfo().noquote()<<QString("IP=%1 Put Command Sucess").arg(QString::fromLocal8Bit(pThis->logInfoMap.value(pThis->playMap.value(nPort)).sDeviceAddress));
//                arrayJpg.clear();
//            }
    }


}

void TheMiddlewareHCNET::g_RealDataCallBack_V30(LONG lRealHandle, DWORD dwDataType, BYTE *pBuffer, DWORD dwBufSize, void *dwUser)
{
     Q_UNUSED(dwUser);

     switch (dwDataType) {
     case NET_DVR_SYSHEAD:
         /* 获取播放库未使用的通道号 */
         if(nullptr!=pThis->PlayM4_GetPort_L){
//             if(pThis->streamID!=lRealHandle){
//                 /* 释放播放库资源 */
//                 if(nullptr!=pThis->PlayM4_Stop_L){
//                     pThis->PlayM4_Stop_L(lRealHandle);
//                 }
//                 if(nullptr!=pThis->PlayM4_CloseStream_L){
//                     pThis->PlayM4_CloseStream_L(lRealHandle);
//                 }
//                 if(nullptr!=pThis->PlayM4_FreePort_L){
//                     pThis->PlayM4_FreePort_L(lRealHandle);
//                 }
//             }
             if(pThis->streamID!=lRealHandle){
                 if (!pThis->PlayM4_GetPort_L(&lRealHandle)) {
                     break;
                 }
             }


         }

         if (dwBufSize > 0) {
             if(nullptr!=pThis-> PlayM4_OpenStream_L){
                 if (!pThis-> PlayM4_OpenStream_L(lRealHandle, pBuffer, dwBufSize, 1920*1080)) {
                     break;
                 }
             }

             /* 设置解码回调函数 只解码不显示 */
             if(nullptr!=pThis-> PlayM4_SetDecCallBack_L){
                 if (!pThis-> PlayM4_SetDecCallBack_L(lRealHandle, DecCallBack)) {
                     break;
                 }
             }

             /* 打开视频解码 */
             if(nullptr!=pThis-> PlayM4_Play_L){
                 if (!pThis-> PlayM4_Play_L(lRealHandle, nullptr)) {
                     break;
                 }
             }
         }
         break;
     case NET_DVR_STREAMDATA:
         /* 解码数据 */
         if (dwBufSize > 0 && lRealHandle != -1 ) {
             BOOL inData = pThis->PlayM4_InputData_L(lRealHandle, pBuffer, dwBufSize);
             while (!inData || lRealHandle!=pThis->streamID) {/* 防止解码库把多通道数据混淆 */
                 //QThread::msleep(5);
                 inData =pThis-> PlayM4_InputData_L(lRealHandle, pBuffer, dwBufSize);
             }
//             if(nullptr!=pThis-> PlayM4_InputData_L){
//                 if(!pThis-> PlayM4_InputData_L(lRealHandle, pBuffer, dwBufSize)){
//                     break;
//                 }
//             }
           }
           break;
//     default: /* 其他数据 */
//         if (dwBufSize > 0 && lRealHandle != -1)
//         {
//             if(nullptr!=pThis-> PlayM4_InputData_L){
//                 if (!pThis-> PlayM4_InputData_L(lRealHandle, pBuffer, dwBufSize))
//                 {
//                     break;
//                 }
//             }
//         }
//         break;
     }
}

void TheMiddlewareHCNET::exceptionCallBack_V30(DWORD dwType, LONG lUserID, LONG lHandle, void *pUser)
{
    Q_UNUSED(lUserID);
    Q_UNUSED(dwType);
    Q_UNUSED(lHandle);

    NET_DVR_USER_LOGIN_INFO LoginInfo=*((NET_DVR_USER_LOGIN_INFO*)pUser);
    if(pThis->NET_DVR_GetLastError_L()>0){
        emit pThis->messageSignal(ZBY_LOG("ERROR"),tr("IP=%1 Camrea Exception<errorCode=%2>").arg(QString::fromLocal8Bit(LoginInfo.sDeviceAddress)).arg(QString::number(pThis->NET_DVR_GetLastError_L())));
    }
}

void TheMiddlewareHCNET::loginResultCallBack(LONG lUserID, DWORD dwResult, LPNET_DVR_DEVICEINFO_V30 lpDeviceInfo, void *pUser)
{
    Q_UNUSED(lpDeviceInfo);

    NET_DVR_USER_LOGIN_INFO LoginInfo=*((NET_DVR_USER_LOGIN_INFO*)pUser);

    if(dwResult==0){
        emit pThis->messageSignal(ZBY_LOG("ERROR"),tr("IP=%1 Camera Login Error<errorCode=%2>").arg(QString::fromLocal8Bit(LoginInfo.sDeviceAddress)).arg(pThis->NET_DVR_GetLastError_L()));
        qWarning().noquote()<<QString("IP=%1 Camera Login Error<errorCode=%2>").arg(QString::fromLocal8Bit(LoginInfo.sDeviceAddress)).arg(pThis->NET_DVR_GetLastError_L());
    }
    if(dwResult==1){
        emit pThis->messageSignal(ZBY_LOG("INFO"),tr("IP=%1 Camera Login Sucess").arg(QString::fromLocal8Bit(LoginInfo.sDeviceAddress)));
        emit pThis->signal_setCameraID(lUserID,QString::fromLocal8Bit(LoginInfo.sDeviceAddress));
        qInfo().noquote()<<QString("IP=%1 Camera Login Sucess").arg(QString::fromLocal8Bit(LoginInfo.sDeviceAddress));
        pThis->logInfoMap.insert(lUserID,LoginInfo);
    }
}

void TheMiddlewareHCNET::initVideoStream(int ID, bool play)
{
    if(play){
        NET_DVR_PREVIEWINFO struPlayInfo = {};
        struPlayInfo.hPlayWnd= nullptr;
        struPlayInfo.lChannel     = 1;       /* 预览通道号 */
        struPlayInfo.dwStreamType = 0;       /* 0-主码流，1-子码流，2-码流3，3-码流4，以此类推 */
        struPlayInfo.dwLinkMode   = 0;       /* 0- TCP方式，1- UDP方式，2- 多播方式，3- RTP方式，4-RTP/RTSP，5-RSTP/HTTP */
        struPlayInfo.bBlocked     = 0;       /* 0- 非阻塞取流，1- 阻塞取流 */

        if(NET_DVR_RealPlay_V40_L !=nullptr){
            streamID =NET_DVR_RealPlay_V40_L(ID,&struPlayInfo,g_RealDataCallBack_V30,nullptr);
            if(streamID==-1){
                emit messageSignal(ZBY_LOG("ERROR"), tr("IP=%1 Open Stream Error<errorCode=%2>").arg(QString::fromLocal8Bit(logInfoMap.value(ID).sDeviceAddress)).arg(NET_DVR_GetLastError_L()));
                qWarning().noquote()<<QString("IP=%1 Open Stream Error<errorCode=%2>").arg(QString::fromLocal8Bit(logInfoMap.value(ID).sDeviceAddress)).arg(NET_DVR_GetLastError_L());
            }
            else {
                playMap.insert(ID,streamID);
                qDebug().noquote()<<QString::fromLocal8Bit(logInfoMap.value(ID).sDeviceAddress)<<":"<<streamID<<"[stream]|[camerID]"<<ID;
                emit messageSignal(ZBY_LOG("INFO"),tr("IP=%1 Open Stream Sucess <Code=%2>").arg(QString::fromLocal8Bit(logInfoMap.value(ID).sDeviceAddress)).arg(QString::number(streamID)));
                qInfo().noquote()<<QString("IP=%1 Open Stream Sucess <Code=%2>").arg(QString::fromLocal8Bit(logInfoMap.value(ID).sDeviceAddress)).arg(QString::number(streamID));
            }
        }
    }
    else {
        long stream=playMap.value(ID);
        //playMap.remove(streamID);
        if(NET_DVR_StopRealPlay_L !=nullptr && stream!=-1 && NET_DVR_StopRealPlay_L(stream)){
            emit messageSignal(ZBY_LOG("INFO"), tr("IP=%1 Stop Stream sSucess").arg(QString::fromLocal8Bit(logInfoMap.value(ID).sDeviceAddress)));
        }
    }
}

void TheMiddlewareHCNET::getDeviceStatusSlot()
{
    //QMap<int, NET_DVR_USER_LOGIN_INFO>::iterator it;
    //for (it = logInfoMap.begin(); it != logInfoMap.end(); ++it){
    foreach (auto id,logInfoMap.keys()){
        if(NET_DVR_RemoteControl_L !=nullptr && NET_DVR_RemoteControl_L(id,NET_DVR_CHECK_USER_STATUS,nullptr,4)){
            emit equipmentStateSignal(id,true);
            qDebug()<<"logInfoMap:"<<logInfoMap.size();
        }
        else {
            logfalList.append(logInfoMap[id]);
            logInfoMap.remove(id);

            emit equipmentStateSignal(id,false);
//            if(NET_DVR_StopRealPlay_L){
//                NET_DVR_StopRealPlay_L(playMap.value(id));
//            }
            /* 释放播放库资源 */
            if(nullptr!=PlayM4_Stop_L){
                PlayM4_Stop_L(playMap.value(id));
            }
            if(nullptr!=PlayM4_CloseStream_L){
                PlayM4_CloseStream_L(playMap.value(id));
            }
            if(nullptr!=PlayM4_FreePort_L){
                PlayM4_FreePort_L(playMap.value(id));
            }
            if(NET_DVR_Logout_L !=nullptr){
                NET_DVR_Logout_L(id);
            }

//            if(-1==logfalList.indexOf(it[Va])){
//                logfalList.append(it.value());
//            }
            playMap.remove(id);
            //logInfoMap.erase(it);
        }
    }

    //QList<NET_DVR_USER_LOGIN_INFO>::iterator it_log;
    //for (it_log = logfalList.begin(); it_log != logfalList.end(); ++it_log){
    for(int var=0;var<logfalList.size();++var){

        qDebug()<<"logfalList:"<<logfalList.size();
        if(NET_DVR_Login_V40_L !=nullptr){/* 登录设备 */
            long ID = NET_DVR_Login_V40_L(&logfalList[var],&DeviceInfo);
            //Q_UNUSED(ID);
            if(ID>-1){
                logInfoMap.insert(ID,logfalList.at(var));
                emit signal_setCameraID(ID,QString::fromLocal8Bit(logfalList.at(var).sDeviceAddress));
                emit messageSignal(ZBY_LOG("INFO"),tr("IP=%1 Camera login successful<Code=%2>").arg(QString::fromLocal8Bit(logfalList.at(var).sDeviceAddress)).arg(ID));
                qInfo().noquote()<<QString("IP=%1 Camera login successful<Code=%2>").arg(QString::fromLocal8Bit(logfalList.at(var).sDeviceAddress)).arg(ID);
                if(NET_DVR_SetupAlarmChan_V41_L!=nullptr && 3==CAMERA_TYPE){
                    /*****************************
                    * @brief:交通系列，布防。
                    ******************************/
                    NET_DVR_SETUPALARM_PARAM aram={};
                    aram.dwSize=sizeof (NET_DVR_SETUPALARM_PARAM);
                    aram.byAlarmInfoType=1;
                    aram.byLevel=1;
                    long lHandle= NET_DVR_SetupAlarmChan_V41_L(ID,&aram);
                    if(lHandle<0 && NET_DVR_GetLastError_L!=nullptr){
                        emit messageSignal(ZBY_LOG("ERROR"),tr("IP=%1 Camera Aram Error<errorCode=%2>").arg(QString::fromLocal8Bit(logfalList.at(var).sDeviceAddress)).arg(NET_DVR_GetLastError_L()));
                        qWarning().noquote()<<QString("IP=%1 Camera Aram Error<errorCode=%2>").arg(QString::fromLocal8Bit(logfalList.at(var).sDeviceAddress)).arg(NET_DVR_GetLastError_L());
                    }
                    else{
                        emit messageSignal(ZBY_LOG("INFO"),tr("IP=%1 Camera Aram Success<Code=%2>").arg(QString::fromLocal8Bit(logfalList.at(var).sDeviceAddress)).arg(lHandle));
                        qInfo().noquote()<<QString("IP=%1 Camera Aram Success<Code=%2>").arg(QString::fromLocal8Bit(logfalList.at(var).sDeviceAddress)).arg(lHandle);
                    }
                }
                if(4==CAMERA_TYPE){
                    /*****************************
                    * @brief: 登录成功,打开预览-------------------------取图使用
                    ******************************/
                    //initVideoStream(ID,false);
                    initVideoStream(ID,true);
                }
                //logfalList.erase(it_log);/* 登录成功，删除列表项 */
                //logfalList.removeOne(logfalList.at(var));
                logfalList.removeAt(var);
                var-=1;
            }
            else {
                if(NET_DVR_GetLastError_L!=nullptr){
                    emit messageSignal(ZBY_LOG("ERROR"),tr("IP=%1 Login failed <errorCode=%2>").arg(QString::fromLocal8Bit(logfalList.at(var).sDeviceAddress)).arg(NET_DVR_GetLastError_L()));
                    qWarning().noquote()<<QString("IP=%1 Login failed <errorCode=%2>").arg(QString::fromLocal8Bit(logfalList.at(var).sDeviceAddress)).arg(NET_DVR_GetLastError_L());
                }
            }
        }
    }
    //logfalList.clear();
}

void TheMiddlewareHCNET::resizeEventSlot()
{
//    if(dwResult){/* window不需要 */
//        if(NET_DVR_ChangeWndResolution_L !=nullptr){
//            NET_DVR_ChangeWndResolution_L(this->streamID);
//        }
//    }
}
