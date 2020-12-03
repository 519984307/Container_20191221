#include "electroniclicenseplatehcnet.h"

//ElectronicLicensePlateHCNET* ElectronicLicensePlateHCNET::pThis=nullptr;

ElectronicLicensePlateHCNET::ElectronicLicensePlateHCNET(QObject *parent)
{
    this->setParent(parent);
//    ElectronicLicensePlateHCNET::pThis=this;;

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

//    imgTime="";
//    imgNumber=-1;

//    imgBuff=nullptr;
}

ElectronicLicensePlateHCNET::~ElectronicLicensePlateHCNET()
{
//    free(imgBuff);
//    delete imgBuff;
//    imgBuff=nullptr;

//    ElectronicLicensePlateHCNET::pThis=nullptr;

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

bool ElectronicLicensePlateHCNET::initializationParameter()
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

void ElectronicLicensePlateHCNET::saveImg(QByteArray arrImg, const QString &time)
{
    QMutexLocker locket(&mutex);
    if(imgPath!=""){/* 保存路径不存在,图片不保存,不识别 */
        QString suffixPath="";
        switch (imgFormat) {
        case 0:
            suffixPath=QDir::toNativeSeparators(tr("%1/%2").arg(channel).arg(QDateTime::currentDateTime().toString("yyyy/MM/dd")));
            break;
        case 1:
            suffixPath=QDir::toNativeSeparators(tr("%1/%2").arg(channel).arg(QDateTime::currentDateTime().toString("yyyy/MM")));
            break;
        case 2:
            suffixPath=QDir::toNativeSeparators(tr("%1/%2").arg(channel).arg(QDateTime::currentDateTime().toString("yyyy")));
            break;
        case 3:
            suffixPath=QDir::toNativeSeparators(tr("%1").arg(channel));
            break;
        case 4:
            suffixPath=QDir::toNativeSeparators(tr("%1").arg(QDateTime::currentDateTime().toString("yyyy/MM/dd")));
            break;
        case 5:
            suffixPath=QDir::toNativeSeparators(tr("%1").arg(QDateTime::currentDateTime().toString("yyyy/MM")));
            break;
        case 6:
            suffixPath=QDir::toNativeSeparators(tr("%1").arg(QDateTime::currentDateTime().toString("yyyy")));
            break;
        case 7:
            suffixPath=QDir::toNativeSeparators("./");
            break;
        }

        QDir dir(imgPath);
        dir.mkpath(suffixPath);
        dir.cd(suffixPath);

        QPixmap *labelPix = new QPixmap();
        labelPix->loadFromData(arrImg);
        QPixmap labelPixFit=  labelPix->scaled(1280,720, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);/* 缩放图片 */
        QString image=QString("%1/%2%3%4.jpg").arg(dir.path()).arg(QDateTime::fromString(time,"yyyy-M-d h:m:s").toString("yyyyMMddhhmmss")).arg(7).arg(channel);
        qDebug()<<image;
        labelPixFit.save(image);
        delete labelPix;
        labelPix=nullptr;
    }
}

void ElectronicLicensePlateHCNET::simulationCaptureSlot()
{
    /*****************************
    * @brief:海康相机其它实现
    ******************************/
    emit signal_simulationCapture(camerID);




//    bool cap=true;

//    if(dwResult){
//        switch (CAMERA_TYPE) {
//        case 1:
////            {
////                LPDWORD dataLen=nullptr;
////                /* 手动触发抓拍保存到内存 */
////                if(NET_DVR_CaptureJPEGPicture_NEW_L!=nullptr && NET_DVR_CaptureJPEGPicture_NEW_L(lUserID,1,&pJpegFile,imgBuff,charLen,dataLen)){
////                    QByteArray arrayJpg(imgBuff,*dataLen);
////                    emit pictureStreamSignal(arrayJpg,imgNumber,imgTime);
////                    emit messageSignal(ZBY_LOG("INFO"), tr("IP=%1 Put Command Sucess").arg(camerIp));

////                    arrayJpg.clear();
////                    delete  dataLen;
////                    dataLen=nullptr;
////                }
////                else {
////                    cap=false;
////                    }
////            }
//            break;
//        case 2:
////            {
////                NET_DVR_PLATE_RESULT result={};
////                result.dwSize=sizeof (result);
////                result.pBuffer1=reinterpret_cast<unsigned char*>(imgBuff);
////                /* 手动触发抓拍，SDK提示做测试使用 */
////                if(NET_DVR_ManualSnap_L!=nullptr && NET_DVR_ManualSnap_L(lUserID,&manualsnap,&result)){
////                    QByteArray arrayJpg(imgBuff,IMG_BYTE);
////                    emit pictureStreamSignal(arrayJpg,imgNumber,imgTime);
////                    emit messageSignal(ZBY_LOG("INFO"), tr("IP=%1 Put Command Sucess").arg(camerIp));

////                    arrayJpg.clear();
////                }
////                else {
////                    cap=false;
////                }
////            }
//            break;
//        case 3:
//            {
//                if(NET_DVR_ContinuousShoot_L!=nullptr){/* 网络触发抓拍 */
//                    int rul=NET_DVR_ContinuousShoot_L(lUserID,&snapcfg);
//                    if(rul){
//                        this->imgNumber=imgNumber;
//                        this->imgTime=imgTime;
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
//    if(!cap){
//        //emit pictureStreamSignal(nullptr,imgNumber,imgTime);/* 保证识别流程完成(识别流程需要完整图片编号) */
//        if(NET_DVR_GetLastError_L!=nullptr){
//            emit messageSignal(ZBY_LOG("ERROR"),tr("IP=%1 Put Command Error<errorCode=%2>").arg(camerIp).arg(NET_DVR_GetLastError_L()));
//        }
//        //return false;
//    }
//    //return true;
}

void ElectronicLicensePlateHCNET::liftingElectronicRailingSlot(bool gate)
{

}

void ElectronicLicensePlateHCNET::transparentTransmission485Slot(const QString &msg)
{

}

void ElectronicLicensePlateHCNET::openTheVideoSlot(bool play,quint64 winID)
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

void ElectronicLicensePlateHCNET::releaseResourcesSlot()
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
}

void ElectronicLicensePlateHCNET::initCameraSlot(const QString &localAddr, const QString &addr, const int &port, const QString &imgPath, int imgFormat, const int &channel)
{
    /*****************************
    * @brief:海康相机其它实现
    ******************************/
    //addr="192.168.1.100;admin;admin123457"
    QStringList addList=addr.trimmed().split(";");
    if(addList.count()<=2){
        emit messageSignal(ZBY_LOG("ERROR"),tr("IP=%1 The camera requires a user and password").arg(addr));
        return;
    }
    this->camerIP=addList[0];
    this->imgPath=imgPath;
    this->imgFormat=imgFormat;
    this->channel=channel;
    emit signal_initCamera(localAddr,addList[0],port,addList[1],addList[2]);



//    if(!isSDKInit){
//        if(!initializationParameter()){/* 动态库初始化失败就不登录相机 */
//            return;
//        }

//        //addr="192.168.1.100;admin;admin123457"
//        QStringList addList=addr.trimmed().split(";");
//        if(addList.count()<3){
//            emit messageSignal(ZBY_LOG("INFO"),tr("IP=%1 The camera requires a user and password").arg(this->camerIp));
//            return;
//        }
//        this->camerIp=addList[0];
//        this->camerName=addList[1];
//        this->camerPow=addList[2];

//        this->addr=addr;
//        this->localAddr=localAddr;
//        this->port=port;
//        this->imgFormat=imgFormat;
//        this->imgPath=imgPath;
//        this->channel=channel;

//        this->arrAddr=localAddr.toLatin1();

//        /* 设置动态库路径 */
//        NET_SDK_INIT_CFG_TYPE cfgType=NET_SDK_INIT_CFG_SDK_PATH;
//        QString path= QDir::toNativeSeparators(QString("%1/%2").arg(QCoreApplication::applicationDirPath()).arg("Plugins/HCNetSDK"));
//        strcpy(SDKPath.sPath,path.toLocal8Bit().data());
//        if(NET_DVR_SetSDKInitCfg_L!=nullptr){
//             NET_DVR_SetSDKInitCfg_L(cfgType,&SDKPath);
//        }

//        strcpy(LoginInfo.sDeviceAddress,camerIp.toLatin1().data());
//        strcpy(LoginInfo.sUserName,camerName.toLatin1().data());
//        strcpy(LoginInfo.sPassword,camerPow.toLatin1().data());
//        LoginInfo.wPort=static_cast<quint16>(port);
//        LoginInfo.bUseAsynLogin=1;
//        LoginInfo.cbLoginResult=ElectronicLicensePlateHCNET::loginResultCallBack;
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
//                    NET_DVR_SetExceptionCallBack_V30_L(0,nullptr,ElectronicLicensePlateHCNET::exceptionCallBack_V30,this);
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
//                if(NET_DVR_SetDVRMessageCallBack_V31_L!=nullptr){
//                    if(NET_DVR_SetDVRMessageCallBack_V31_L(ElectronicLicensePlateHCNET::exceptionMSGCallBack_V31,this)){
//                        emit messageSignal(ZBY_LOG("INFO"),tr("IP=%1 Camera NET_DVR_SetDVRMessageCallBack_V31_L Sucess").arg(this->camerIp));
//                    }
//                }
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
//            initCameraSlot(localAddr, addr, port, imgPath, imgFormat,channel);
//        }
//    }
//    else {
//        qDebug()<<"realy login";
//        NET_DVR_Login_V40_L(&LoginInfo,&DeviceInfo);
//    }
}

WINBOOL ElectronicLicensePlateHCNET::exceptionMSGCallBack_V31(LONG lCommand, NET_DVR_ALARMER *pAlarmer, char *pAlarmInfo, DWORD dwBufLen, void *pUser)
{
//    //struPlateResult.struPlateInfo.byColor)//车牌颜色
//    //(struPlateResult.struPlateInfo.sLicense));// 车牌号
//    //emit pThis->messageSignal(ZBY_LOG("INFO"),QString("lUserID: %1").arg(pAlarmer->lUserID));


////    if(pThis->imgNumber==-1){
////        return false;
////    }

//    /* 系统时间 */
//    QString dateTime=QDateTime::currentDateTime().toString("yyyy-M-d h:m:s");

//    if(lCommand == COMM_UPLOAD_PLATE_RESULT){
//        NET_DVR_PLATE_RESULT struPlateResult={};
//        memcpy(&struPlateResult, pAlarmInfo, sizeof(struPlateResult));

//        QString plate=QString::fromLocal8Bit(struPlateResult.struPlateInfo.sLicense);
//        if(plate!="无车牌" && !plate.isEmpty()){
//            plate=plate.mid(1);
//        }

//        emit pThis->messageSignal(ZBY_LOG("INFO"),QString("Plate: %1").arg(plate));// 车牌号

//        // 场景图
//        if (struPlateResult.dwPicLen != 0 && struPlateResult.byResultType == 1 )
//        {
//            pThis->imgBuff=reinterpret_cast<char*>(struPlateResult.pBuffer1);
//            QByteArray arrayJpg(pThis->imgBuff,struPlateResult.dwPicLen);

//            QString color="";
//            switch(struPlateResult.struPlateInfo.byColor)//车牌颜色
//            {
//            case VCA_BLUE_PLATE:
//                color="蓝";
//                break;
//            case VCA_YELLOW_PLATE:
//                color="黄";
//                break;
//            case VCA_WHITE_PLATE:
//                color="白";
//                break;
//            case VCA_BLACK_PLATE:
//                color="黑";
//                break;
//            default:
//                break;
//            }

//            emit pThis->resultsTheLicensePlateSignal(plate,color,dateTime,arrayJpg);
//            emit pThis->messageSignal(ZBY_LOG("INFO"),tr("License Plate recognition results:%1 %2").arg(plate).arg(dateTime));

//            pThis->saveImg(arrayJpg,dateTime);

//            arrayJpg.clear();
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

//        QString plate=QString::fromLocal8Bit(struITSPlateResult.struPlateInfo.sLicense);
//        if(plate!="无车牌" && !plate.isEmpty()){
//            plate=plate.mid(1);
//        }
//        emit pThis->messageSignal(ZBY_LOG("INFO"),QString("Plate: %1").arg(plate));// 车牌号

//        // 场景图
//        if (((struITSPlateResult.struPicInfo[0].dwDataLen != 0)&&(struITSPlateResult.struPicInfo[0].byType== 1))||(struITSPlateResult.struPicInfo[0].byType == 2))
//        {
//            pThis->imgBuff=reinterpret_cast<char*>(struITSPlateResult.struPicInfo[0].pBuffer);
//            QByteArray arrayJpg(pThis->imgBuff,struITSPlateResult.struPicInfo[0].dwDataLen);

//            QString color="";
//            switch(struITSPlateResult.struPlateInfo.byColor)//车牌颜色
//            {
//            case VCA_BLUE_PLATE:
//                color="蓝";
//                break;
//            case VCA_YELLOW_PLATE:
//                color="黄";
//                break;
//            case VCA_WHITE_PLATE:
//                color="白";
//                break;
//            case VCA_BLACK_PLATE:
//                color="黑";
//                break;
//            default:
//                break;
//            }

//            emit pThis->resultsTheLicensePlateSignal(plate,color,dateTime,arrayJpg);
//            emit pThis->messageSignal(ZBY_LOG("INFO"),tr("License Plate recognition results:%1 %2").arg(plate).arg(dateTime));

//            pThis->saveImg(arrayJpg,dateTime);

//            arrayJpg.clear();
//        }
//        // 车牌图
//        if (((struITSPlateResult.struPicInfo[0].dwDataLen != 0)&&(struITSPlateResult.struPicInfo[0].byType== 0)))
//        {
////            pThis->imgBuff=reinterpret_cast<char*>(struITSPlateResult.struPicInfo[0].pBuffer);
////            QByteArray arrayJpg(pThis->imgBuff,struITSPlateResult.struPicInfo[0].dwDataLen);
//        }
//    }
//    //emit pThis->messageSignal(ZBY_LOG("INFO"),QString("exceptionMSGCallBack_V31:%1,imgNumber:%2").arg(QString::number(lCommand)).arg(pThis->imgNumber));

////    pThis->imgNumber=-1;
////    pThis->imgTime="";

//    return true;
}

void ElectronicLicensePlateHCNET::exceptionCallBack_V30(DWORD dwType, LONG lUserID, LONG lHandle, void *pUser)
{
//    emit pThis->messageSignal(ZBY_LOG("ERROR"),tr("IP=%1 Camrea Exception<errorCode=%2>").arg(pThis->camerIp).arg(QString::number(pThis->NET_DVR_GetLastError_L())));
}

void ElectronicLicensePlateHCNET::loginResultCallBack(LONG lUserID, DWORD dwResult, LPNET_DVR_DEVICEINFO_V30 lpDeviceInfo, void *pUser)
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
//        if(pThis->NET_DVR_SetupAlarmChan_V41_L!=nullptr){
//            NET_DVR_SETUPALARM_PARAM aram={};
//            aram.dwSize=sizeof (NET_DVR_SETUPALARM_PARAM);
//            aram.byAlarmInfoType=1;
//            aram.byLevel=1;
//            pThis->lHandle= pThis->NET_DVR_SetupAlarmChan_V41_L(lUserID,&aram);
//            if(pThis->lHandle<0){
//                emit pThis->messageSignal(ZBY_LOG("ERROR"),tr("IP=%1 Camera Aram Error<errorCode=%2>").arg(pThis->camerIp).arg(pThis->NET_DVR_GetLastError_L()));
//            }
//            else{
//                emit pThis->messageSignal(ZBY_LOG("INFO"),tr("IP=%1 Camera Aram Success<Code=%2>").arg(pThis->camerIp).arg(pThis->lHandle));

//            }
//        }

//        pThis->lUserID=lUserID;
//        pThis->dwResult=dwResult;
//    }
}

void ElectronicLicensePlateHCNET::getDeviceStatusSlot()
{
//    if(NET_DVR_RemoteControl_L !=nullptr){
//        if(camerIp==""){
//            return;
//        }
//        if(NET_DVR_RemoteControl_L(lUserID,NET_DVR_CHECK_USER_STATUS,nullptr,4)){
//            emit equipmentStateSignal(true);
//            dwResult=1;
//        }
//        else {
//            emit equipmentStateSignal(false);
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
//            initCameraSlot(localAddr, addr, port, imgPath, imgFormat,channel);/* 重新登录 */
//        }
//    }
}

void ElectronicLicensePlateHCNET::resizeEventSlot()
{
//    if(dwResult){/* window不需要 */
//        if(NET_DVR_ChangeWndResolution_L !=nullptr){
//            NET_DVR_ChangeWndResolution_L(this->streamID);
//        }
//    }
}





/*****************************
* @brief:海康相机其它实现
******************************/

void ElectronicLicensePlateHCNET::slot_pictureStream(int ID, QByteArray arrJpg)
{
//    if(ID==camerID){
//        emit pictureStreamSignal(arrJpg,imgNumber,imgTime);
//        //emit messageSignal(ZBY_LOG("INFO"), tr("IP=%1 Put Command Sucess").arg(camerIP));
//    }
    /*****************************
    * @brief:车牌不处理箱号信息
    ******************************/
}

void ElectronicLicensePlateHCNET::slot_setCameraID(int ID, QString cameraIP)
{
    if(camerIP==cameraIP){
        camerID=ID;
        emit messageSignal(ZBY_LOG("INFO"), tr("IP=%1 Set the ID[%2]").arg(cameraIP).arg(ID));
    }
}

void ElectronicLicensePlateHCNET::slot_resultsTheLicensePlate(int ID, const QString &plate, const QString &color, const QString &time, QByteArray arrImg)
{
    if(camerID==ID){
        saveImg(arrImg,time);
        emit resultsTheLicensePlateSignal(plate,color,time,arrImg);
        emit messageSignal(ZBY_LOG("INFO"),tr("License Plate recognition results:%1 %2").arg(plate).arg(time));
    }
}

void ElectronicLicensePlateHCNET::slot_equipmentState(int ID, bool state)
{
    if(camerID==ID){
        emit equipmentStateSignal(state);
    }
}
