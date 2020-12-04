#ifndef CAPTUREIMAGES_H
#define CAPTUREIMAGES_H

#include "HCNetSDK.h"
#include "captureimages_global.h"
#include "ICaptureImages.h"

#define CAMERA_TYPE 2

class CAPTUREIMAGESSHARED_EXPORT CaptureImages:public ICaptureImages
{
    Q_OBJECT
    Q_INTERFACES(ICaptureImages)
    Q_PLUGIN_METADATA(IID  ICaptureImagesIID)

public:
    CaptureImages(QObject *parent = nullptr);
    ~CaptureImages()Q_DECL_OVERRIDE;

//    static CaptureImages* pThis;

//private:/* 参数  */

//    ///
//    /// \brief isSDKInit 动态库初始化状态
//    ///
//    bool isSDKInit;

//    ///
//    /// \brief port 端口
//    ///
//    int port;

//    ///
//    /// \brief camerIp  地址,用户名,密码,别名
//    ///
//    QString camerIp,camerName,camerPow,alias;

//    ///登录用户ID,视频流ID
//    LONG lUserID,streamID;

//    ///
//    /// \brief dwResult 登录结果
//    ///
//    DWORD dwResult;

//    ///
//    /// \brief lHandle 布防结果
//    ///
//    LONG lHandle;

//    ///
//    /// \brief imgNumber 抓拍图片编号
//    ///
//    int imgN;

//    ///
//    /// \brief imgTime 抓拍图片时间戳
//    ///
//    QString imgT;

//    ///
//    /// \brief imgBuff 图片流内存(主动申请和释放)
//    ///
//    char* imgBuff;

//    ///
//    /// \brief charLen 图片缓冲区大小
//    ///
//    uint32_t charLen;

//    ///
//    /// \brief DLL 加载动态库
//    ///
//    QLibrary* pDLL;

//    ///
//    /// \brief pTimerState 相机状态定时器
//    ///
//    QTimer* pTimerState;

//    ///
//    /// \brief LoginInfo 相机登录参数
//    ///
//    NET_DVR_USER_LOGIN_INFO LoginInfo={};

//    ///
//    /// \brief DeviceInfo 相机参数
//    ///
//    NET_DVR_DEVICEINFO_V40 DeviceInfo={};

//    ///
//    /// \brief SDKPath 动态库路径
//    ///
//    NET_DVR_LOCAL_SDK_PATH SDKPath={};

//    ///
//    /// \brief pJpegFile 图像信息
//    ///
//    NET_DVR_JPEGPARA   pJpegFile={};

//    ///
//    /// \brief snapcfg 触发参数结构体
//    ///
//    NET_DVR_SNAPCFG snapcfg={};

//    ///
//    /// \brief manualsnap 手动抓拍参数
//    ///
//    NET_DVR_MANUALSNAP manualsnap={};

//private:

    /*****************************
    * @brief:交通系列（2CD9），抓图需要布防
    ******************************/
    ///
    /// \brief exceptionMSGCallBack_V31  注册回调函数，接收设备报警消息等。
    /// \param lCommand 上传的消息类型，不同的报警信息对应不同的类型，通过类型区分是什么报警信息，详见“Remarks”中列表
    /// \param pAlarmer 报警设备信息，包括设备序列号、IP地址、登录IUserID句柄等
    /// \param pAlarmInfo 报警信息，通过lCommand值判断pAlarmer对应的结构体，详见“Remarks”中列表
    /// \param dwBufLen 报警信息缓存大小
    /// \param pUser 用户数据
    /// \return TRUE表示成功，FALSE表示失败。接口返回失败请调用NET_DVR_GetLastError获取错误码，通过错误码判断出错原因
    ///
    static BOOL CALLBACK exceptionMSGCallBack_V31(LONG lCommand,NET_DVR_ALARMER *pAlarmer,char *pAlarmInfo,DWORD dwBufLen,void *pUser);

//    typedef   LONG (*NET_DVR_SetupAlarmChan_V41FUN)(LONG lUserID,LPNET_DVR_SETUPALARM_PARAM   lpSetupParam);
//    ///
//    /// \brief NET_DVR_SetupAlarmChan_V41_L 建立报警上传通道，获取报警等信息
//    ///
//    NET_DVR_SetupAlarmChan_V41FUN NET_DVR_SetupAlarmChan_V41_L;

//    typedef   BOOL (*NET_DVR_CloseAlarmChan_V30FUN)(LONG lAlarmHandle);
//    ///
//    /// \brief NET_DVR_CloseAlarmChan_V30_L 撤销报警上传通道
//    ///
//    NET_DVR_CloseAlarmChan_V30FUN NET_DVR_CloseAlarmChan_V30_L;

//    typedef   BOOL (*NET_DVR_SetDVRMessageCallBack_V31FUN)(MSGCallBack_V31 fMessageCallBack,void *pUser);
//    ///
//    /// \brief NET_DVR_SetDVRMessageCallBack_V31_L 设置回调函数
//    ///
//    NET_DVR_SetDVRMessageCallBack_V31FUN NET_DVR_SetDVRMessageCallBack_V31_L;

//    typedef   BOOL (*NET_DVR_ContinuousShootFUN)(LONG lUserID,LPNET_DVR_SNAPCFG    lpInter);
//    ///
//    /// \brief NET_DVR_ContinuousShoot_L 网络触发抓拍
//    ///
//    NET_DVR_ContinuousShootFUN NET_DVR_ContinuousShoot_L;

//    typedef   BOOL (*NET_DVR_ManualSnapFUN)(  LONG  lUserID,LPNET_DVR_MANUALSNAP      lpInter,  LPNET_DVR_PLATE_RESULT    lpOuter);
//    ///
//    /// \brief NET_DVR_ManualSnap_L 手动触发抓拍
//    ///
//    NET_DVR_ManualSnapFUN NET_DVR_ManualSnap_L;

//    /*****************************
//    * @brief:网络相机系列（2CD7）
//    ******************************/
//    typedef   BOOL  (*NET_DVR_SetExceptionCallBack_V30FUN)(UINT reserved1, void* reserved2, void (CALLBACK* fExceptionCallBack)(DWORD dwType, LONG lUserID, LONG lHandle, void *pUser), void *pUser);
//    ///
//    /// \brief NET_DVR_SetExceptionCallBack_V30_L 设置异常回调函数
//    ///
//    NET_DVR_SetExceptionCallBack_V30FUN NET_DVR_SetExceptionCallBack_V30_L;

//    typedef bool (*NET_DVR_SetSDKInitCfgFUN)(NET_SDK_INIT_CFG_TYPE enumType, void* const lpInBuff);
//    ///
//    /// \brief NET_DVR_SetSDKInitCfg_L 设置动态库路径
//    ///
//    NET_DVR_SetSDKInitCfgFUN NET_DVR_SetSDKInitCfg_L;

//    typedef bool (*NET_DVR_CleanupFUN)();
//    ///
//    /// \brief NET_DVR_Cleanup_L 清除内存
//    ///
//    NET_DVR_CleanupFUN NET_DVR_Cleanup_L;

//    typedef bool (*NET_DVR_InitFUN)();
//    ///
//    /// \brief NET_DVR_Init_L 初始化动态库
//    ///
//    NET_DVR_InitFUN NET_DVR_Init_L;

//    typedef LONG (*NET_DVR_Login_V40FUN)(LPNET_DVR_USER_LOGIN_INFO pLoginInfo,LPNET_DVR_DEVICEINFO_V40 lpDeviceInfo);
//    ///
//    /// \brief NET_DVR_Login_V40_L 登录相机
//    ///
//    NET_DVR_Login_V40FUN NET_DVR_Login_V40_L;

//    typedef   BOOL (*NET_DVR_LogoutFUN)(LONG lUserID);
//    ///
//    /// \brief NET_DVR_Logout_L 登出相机
//    ///
//    NET_DVR_LogoutFUN NET_DVR_Logout_L;

//    typedef BOOL (*NET_DVR_ChangeWndResolutionFUN)(LONG iRealHandle);
//    ///
//    /// \brief NET_DVR_ChangeWndResolution_L 通知窗口重画图像
//    ///
//    NET_DVR_ChangeWndResolutionFUN NET_DVR_ChangeWndResolution_L;

//    typedef BOOL (*NET_DVR_CaptureJPEGPicture_NEWFUN)(LONG lUserID, LONG lChannel, LPNET_DVR_JPEGPARA lpJpegPara, char *sJpegPicBuffer, DWORD dwPicSize,  LPDWORD lpSizeReturned);
//    ///
//    /// \brief NET_DVR_CaptureJPEGPicture_NEW_L 抓图保存到内存
//    ///
//    NET_DVR_CaptureJPEGPicture_NEWFUN NET_DVR_CaptureJPEGPicture_NEW_L;

//    typedef BOOL (*NET_DVR_CaptureJPEGPictureFUN)(LONG lUserID,LONG lChannel,  LPNET_DVR_JPEGPARA   lpJpegPara,char *sPicFileName);
//    ///
//    /// \brief NET_DVR_CaptureJPEGPicture_L  抓图保存到文件
//    ///
//    NET_DVR_CaptureJPEGPictureFUN NET_DVR_CaptureJPEGPicture_L;

//    typedef LONG (*NET_DVR_RealPlay_V40FUN)(LONG lUserID, LPNET_DVR_PREVIEWINFO lpPreviewInfo, REALDATACALLBACK fRealDataCallBack_V30 , void* pUser);
//    ///
//    /// \brief NET_DVR_RealPlay_V40_L 实时预览
//    ///
//    NET_DVR_RealPlay_V40FUN NET_DVR_RealPlay_V40_L;

//    typedef DWORD (*NET_DVR_GetLastErrorFUN)();
//    ///
//    /// \brief NET_DVR_GetLastError_L 获取错误
//    ///
//    NET_DVR_GetLastErrorFUN NET_DVR_GetLastError_L;

//    typedef   BOOL  (*NET_DVR_SetLogToFileFUN)(DWORD nLogLevel, char * strLogDir , BOOL bAutoDel );
//    ///
//    /// \brief NET_DVR_SetLogToFile_L 设置日志
//    ///
//    NET_DVR_SetLogToFileFUN NET_DVR_SetLogToFile_L;

//    typedef   BOOL  (*NET_DVR_GetLocalIPFUN)(char strIP[16][16], DWORD *pValidNum, BOOL *pEnableBind);
//    ///
//    /// \brief NET_DVR_GetLocalIP_L 获取所有网卡IP
//    ///
//    NET_DVR_GetLocalIPFUN NET_DVR_GetLocalIP_L;

//    typedef   BOOL   (*NET_DVR_SetValidIPFUN)(DWORD dwIPIndex, BOOL bEnableBind);
//    ///
//    /// \brief NET_DVR_SetValidIP_L 绑定网卡
//    ///
//    NET_DVR_SetValidIPFUN NET_DVR_SetValidIP_L;

//    typedef   BOOL (*NET_DVR_StopRealPlayFUN)(LONG lRealHandle);
//    ///
//    /// \brief NET_DVR_StopRealPlay_L 停止预览
//    ///
//    ///
//    NET_DVR_StopRealPlayFUN NET_DVR_StopRealPlay_L;

//    typedef   BOOL  (*NET_DVR_RemoteControlFUN)(LONG lUserID, DWORD dwCommand, LPVOID lpInBuffer, DWORD dwInBufferSize);
//    ///
//    /// \brief NET_DVR_RemoteControl_L 远程控制,设备运行状态
//    ///
//    NET_DVR_RemoteControlFUN NET_DVR_RemoteControl_L;

//    typedef  int (*NET_DVR_GetRealPlayerIndexFUN)(LONG    lRealHandle);
//    ///
//    /// \brief NET_DVR_GetRealPlayerIndex_L 获取预览时用来解码和显示的播放器句柄。
//    ///
//    NET_DVR_GetRealPlayerIndexFUN NET_DVR_GetRealPlayerIndex_L;

//    typedef  BOOL (*NET_DVR_SetConnectTimeFUN)( DWORD   dwWaitTime,DWORD   dwTryTimes);
//    ///
//    /// \brief NET_DVR_SetConnectTime_L 设置网络连接超时时间和连接尝试次数。
//    ///
//    NET_DVR_SetConnectTimeFUN NET_DVR_SetConnectTime_L;

//    typedef   BOOL (*NET_DVR_SetReconnectFUN)(DWORD   dwInterval,BOOL    bEnableRecon    );
//    ///
//    /// \brief NET_DVR_SetReconnect_L 设置重连功能。
//    ///
//    NET_DVR_SetReconnectFUN NET_DVR_SetReconnect_L;

//    typedef   BOOL (*NET_DVR_SetRecvTimeOutFUN)(DWORD   nRecvTimeOut);
//    ///
//    /// \brief NET_DVR_SetRecvTimeOut_L 设置接收超时时间
//    ///
//    NET_DVR_SetRecvTimeOutFUN NET_DVR_SetRecvTimeOut_L;

private:

    ///
    /// \brief exceptionCallBack_V30 接收异常、重连等消息的窗口句柄或回调函数。
    /// \param dwType 异常或重连等消息的类型
    /// \param lUserID 登录ID
    /// \param lHandle 出现异常的相应类型的句柄
    /// \param pUser 用户数据
    ///
    static void CALLBACK exceptionCallBack_V30(DWORD dwType, LONG lUserID, LONG lHandle, void *pUser);

    ///
    /// \brief fLoginResultCallBack 登录状态回调函数
    /// \param lUserID 用户ID，NET_DVR_Login_V40的返回值
    /// \param dwResult 登录状态：0- 异步登录失败，1- 异步登录成功
    /// \param lpDeviceInfo 设备信息，设备序列号、通道、能力等参数
    /// \param pUser 用户数据
    ///
    static void CALLBACK loginResultCallBack(LONG lUserID,DWORD dwResult,LPNET_DVR_DEVICEINFO_V30 lpDeviceInfo,void *pUser);

public:

    ///
    /// \brief initCamerSlot 初始化相机
    /// \param camerIP 地址
    /// \param camerPort 端口
    /// \param user 用户名
    /// \param pow 密码
    ///
    void initCamerSlot(const QString &camerIP, const int & camerPort, const QString &CamerUser, const QString &CamerPow,const QString& alias) Q_DECL_OVERRIDE;

    ///
    /// \brief putCommandSlot 抓取图片
    /// \param imgNumber 图片编号
    /// \return
    ///
    bool putCommandSlot(const int &imgNumber,const QString &imgTime) Q_DECL_OVERRIDE;

    ///
    /// \brief playStreamSlot 播放视频流
    /// \param winID 窗口句柄
    /// \param play 播放状态
    ///
    void playStreamSlot(quint64 winID, bool play) Q_DECL_OVERRIDE;

    ///
    /// \brief releaseResourcesSlot 释放资源
    ///
    void releaseResourcesSlot()Q_DECL_OVERRIDE;

    ///
    /// \brief resizeEventSlot 通知动态库调整窗口
    ///
    void resizeEventSlot()Q_DECL_OVERRIDE;

    ///
    /// \brief InitializationSlot 初始化参数
    ///
    bool InitializationSlot()Q_DECL_OVERRIDE;

private slots:
    ///
    /// \brief getDeviceStatusSlot 获取设备运行状态
    /// \param lUserID 登录ID
    /// \return
    ///
    void getDeviceStatusSlot();




    /*****************************
    * @brief:海康相机其它实现
    ******************************/
public:
    ///
    /// \brief slot_pictureStream 分发图片数据
    /// \param ID
    /// \param arrJpg
    ///
    void slot_pictureStream(int ID,QByteArray arrJpg)Q_DECL_OVERRIDE;

    ///
    /// \brief slot_setCameraID 设置通道登录相机ID
    /// \param ID 登录ID
    /// \param cameraIP 相机地址
    ///
    void slot_setCameraID(int ID,QString cameraIP)Q_DECL_OVERRIDE;

    ///
    /// \brief slot_resultsTheLicensePlate 车牌结果
    /// \param plate
    ///
    void slot_resultsTheLicensePlate(int ID,const QString &plate,const QString &color,const QString &time,QByteArray arrImg)Q_DECL_OVERRIDE;

    ///
    /// \brief slot_equipmentState  设备额在线状态
    /// \param state
    ///
    void slot_equipmentState(int ID, bool state)Q_DECL_OVERRIDE;

    int camerID;
    QString camerIP,alias;
    int imgNumber;
    QString imgTime;
    bool put;
    /*****************************
    * @brief:海康相机其它实现
    ******************************/
};

#endif // CAPTUREIMAGES_H
