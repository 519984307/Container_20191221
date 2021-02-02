#ifndef THEMIDDLEWAREHCNET_H
#define THEMIDDLEWAREHCNET_H

#define ZBY_LOG(type)  tr("[%1][%2][%3]").arg(type).arg(Q_FUNC_INFO).arg(__LINE__)

#define IMG_BYTE 1920*1080+1
#define CAMERA_TYPE 1


#include "TheMiddlewareHCNET_global.h"
#include "middlewareinterface.h"
#include "HCNetSDK.h"
#include "plaympeg4.h"

class THEMIDDLEWAREHCNET_EXPORT TheMiddlewareHCNET:public IMiddleware
{
    Q_OBJECT
    Q_INTERFACES(IMiddleware)
    Q_PLUGIN_METADATA(IID IMiddlewareIID)

public:
    TheMiddlewareHCNET(QObject *parent=nullptr);
    ~TheMiddlewareHCNET()Q_DECL_OVERRIDE;

    QString InterfaceType()Q_DECL_OVERRIDE;

    static TheMiddlewareHCNET *pThis;

    ///
    /// \brief liftingElectronicRailingSlot 抬杆/落杆
    ///
    void liftingElectronicRailingSlot(bool gate)Q_DECL_OVERRIDE;

    ///
    /// \brief transparentTransmission485Slot 透明传输
    /// \param dmsg
    ///
    void transparentTransmission485Slot(const QString &msg)Q_DECL_OVERRIDE;

    ///
    /// \brief releaseResourcesSlot 释放动态库资源
    ///
    void releaseResourcesSlot()Q_DECL_OVERRIDE;

    ///
    /// \brief simulationCaptureSlot 模拟抓拍
    ///
    void simulationCaptureSlot(int ID)Q_DECL_OVERRIDE;

    ///
    /// \brief openTheVideoSlot 打开视频/关闭视频
    /// \param play
    ///
    void openTheVideoSlot(int ID,bool play,quint64 winID=0)Q_DECL_OVERRIDE;

    ///
    /// \brief initCameraSlot 初始化相机
    /// \param localAddr 本机地址(用户绑定网卡)
    /// \param addr 地址
    /// \param port 端口
    /// \param user 用户
    /// \param pow  密码
    ///
    void initCameraSlot(const QString &localAddr, const QString &addr, const int &port, const QString &user, const QString &pow)Q_DECL_OVERRIDE;

    ///
    /// \brief initializationParameter 初始化参数
    /// \param addr 地址
    /// \param port 端口
    /// \param imgPath 图片路径
    /// \param channel 通道号
    ///
    bool initializationParameter();

private:/* 参数  */

    QString localAddr;
    long streamID;

    QList<NET_DVR_USER_LOGIN_INFO> logfalList;
    QMap<int,NET_DVR_USER_LOGIN_INFO> logInfoMap;
    QMap<int,NET_DVR_SETUPALARM_PARAM> alarmInfoMap;

    ///
    /// \brief isSDKInit 动态库初始化状态
    ///
    bool isSDKInit;

    ///
    /// \brief imgBuff 图片流内存(主动申请和释放)
    ///
    char* imgBuff;

    ///
    /// \brief charLen 图片缓冲区大小
    ///
    uint32_t charLen;

    ///
    /// \brief DLL 加载动态库
    ///
    QLibrary* pDLL;

    ///
    /// \brief pDLLplay 加载播放动态库
    ///
    QLibrary* pDLLplay;

    ///
    /// \brief pTimerState 相机状态定时器
    ///
    QTimer* pTimerState;

    ///
    /// \brief DeviceInfo 相机参数
    ///
    NET_DVR_DEVICEINFO_V40 DeviceInfo={};

    ///
    /// \brief SDKPath 动态库路径
    ///
    NET_DVR_LOCAL_SDK_PATH SDKPath={};

    ///
    /// \brief pJpegFile 图像信息
    ///
    NET_DVR_JPEGPARA   pJpegFile={};

    ///
    /// \brief snapcfg 触发参数结构体
    ///
    NET_DVR_SNAPCFG snapcfg={};

    ///
    /// \brief manualsnap 手动抓拍参数
    ///
    NET_DVR_MANUALSNAP manualsnap={};

    ///
    /// \brief playMap 视频流绑定ID
    ///
    QMap<int,LONG> playMap;

    ///
    /// \brief putID 当前抓图ID
    ///
    int putID;

private:

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

    typedef   LONG (*NET_DVR_SetupAlarmChan_V41FUN)(LONG lUserID,LPNET_DVR_SETUPALARM_PARAM   lpSetupParam);
    ///
    /// \brief NET_DVR_SetupAlarmChan_V41_L 建立报警上传通道，获取报警等信息
    ///
    NET_DVR_SetupAlarmChan_V41FUN NET_DVR_SetupAlarmChan_V41_L;

    typedef   BOOL (*NET_DVR_CloseAlarmChan_V30FUN)(LONG lAlarmHandle);
    ///
    /// \brief NET_DVR_CloseAlarmChan_V30_L 撤销报警上传通道
    ///
    NET_DVR_CloseAlarmChan_V30FUN NET_DVR_CloseAlarmChan_V30_L;

    typedef   BOOL (*NET_DVR_SetDVRMessageCallBack_V31FUN)(MSGCallBack_V31 fMessageCallBack,void *pUser);
    ///
    /// \brief NET_DVR_SetDVRMessageCallBack_V31_L 设置回调函数
    ///
    NET_DVR_SetDVRMessageCallBack_V31FUN NET_DVR_SetDVRMessageCallBack_V31_L;

    typedef   BOOL (*NET_DVR_ContinuousShootFUN)(LONG lUserID,LPNET_DVR_SNAPCFG    lpInter);
    ///
    /// \brief NET_DVR_ContinuousShoot_L 网络触发抓拍
    ///
    NET_DVR_ContinuousShootFUN NET_DVR_ContinuousShoot_L;

    typedef   BOOL (*NET_DVR_ManualSnapFUN)(  LONG  lUserID,LPNET_DVR_MANUALSNAP      lpInter,  LPNET_DVR_PLATE_RESULT    lpOuter);
    ///
    /// \brief NET_DVR_ManualSnap_L 手动触发抓拍
    ///
    NET_DVR_ManualSnapFUN NET_DVR_ManualSnap_L;

    /*****************************
    * @brief:网络相机系列（2CD7）
    ******************************/
    typedef   BOOL  (*NET_DVR_SetExceptionCallBack_V30FUN)(UINT reserved1, void* reserved2, void (CALLBACK* fExceptionCallBack)(DWORD dwType, LONG lUserID, LONG lHandle, void *pUser), void *pUser);
    ///
    /// \brief NET_DVR_SetExceptionCallBack_V30_L 设置异常回调函数
    ///
    NET_DVR_SetExceptionCallBack_V30FUN NET_DVR_SetExceptionCallBack_V30_L;

    typedef bool (*NET_DVR_SetSDKInitCfgFUN)(NET_SDK_INIT_CFG_TYPE enumType, void* const lpInBuff);
    ///
    /// \brief NET_DVR_SetSDKInitCfg_L 设置动态库路径
    ///
    NET_DVR_SetSDKInitCfgFUN NET_DVR_SetSDKInitCfg_L;

    typedef bool (*NET_DVR_CleanupFUN)();
    ///
    /// \brief NET_DVR_Cleanup_L 清除内存
    ///
    NET_DVR_CleanupFUN NET_DVR_Cleanup_L;

    typedef bool (*NET_DVR_InitFUN)();
    ///
    /// \brief NET_DVR_Init_L 初始化动态库
    ///
    NET_DVR_InitFUN NET_DVR_Init_L;

    typedef LONG (*NET_DVR_Login_V40FUN)(LPNET_DVR_USER_LOGIN_INFO pLoginInfo,LPNET_DVR_DEVICEINFO_V40 lpDeviceInfo);
    ///
    /// \brief NET_DVR_Login_V40_L 登录相机
    ///
    NET_DVR_Login_V40FUN NET_DVR_Login_V40_L;

    typedef   BOOL (*NET_DVR_LogoutFUN)(LONG lUserID);
    ///
    /// \brief NET_DVR_Logout_L 登出相机
    ///
    NET_DVR_LogoutFUN NET_DVR_Logout_L;

    typedef BOOL (*NET_DVR_ChangeWndResolutionFUN)(LONG iRealHandle);
    ///
    /// \brief NET_DVR_ChangeWndResolution_L 通知窗口重画图像
    ///
    NET_DVR_ChangeWndResolutionFUN NET_DVR_ChangeWndResolution_L;

    typedef BOOL (*NET_DVR_CaptureJPEGPicture_NEWFUN)(LONG lUserID, LONG lChannel, LPNET_DVR_JPEGPARA lpJpegPara, char *sJpegPicBuffer, DWORD dwPicSize,  LPDWORD lpSizeReturned);
    ///
    /// \brief NET_DVR_CaptureJPEGPicture_NEW_L 抓图保存到内存
    ///
    NET_DVR_CaptureJPEGPicture_NEWFUN NET_DVR_CaptureJPEGPicture_NEW_L;

    typedef BOOL (*NET_DVR_CaptureJPEGPictureFUN)(LONG lUserID,LONG lChannel,  LPNET_DVR_JPEGPARA   lpJpegPara,char *sPicFileName);
    ///
    /// \brief NET_DVR_CaptureJPEGPicture_L  抓图保存到文件
    ///
    NET_DVR_CaptureJPEGPictureFUN NET_DVR_CaptureJPEGPicture_L;

    typedef LONG (*NET_DVR_RealPlay_V40FUN)(LONG lUserID, LPNET_DVR_PREVIEWINFO lpPreviewInfo, REALDATACALLBACK fRealDataCallBack_V30 , void* pUser);
    ///
    /// \brief NET_DVR_RealPlay_V40_L 实时预览
    ///
    NET_DVR_RealPlay_V40FUN NET_DVR_RealPlay_V40_L;

    typedef DWORD (*NET_DVR_GetLastErrorFUN)();
    ///
    /// \brief NET_DVR_GetLastError_L 获取错误
    ///
    NET_DVR_GetLastErrorFUN NET_DVR_GetLastError_L;

    typedef   BOOL  (*NET_DVR_SetLogToFileFUN)(DWORD nLogLevel, char * strLogDir , BOOL bAutoDel );
    ///
    /// \brief NET_DVR_SetLogToFile_L 设置日志
    ///
    NET_DVR_SetLogToFileFUN NET_DVR_SetLogToFile_L;

    typedef   BOOL  (*NET_DVR_GetLocalIPFUN)(char strIP[16][16], DWORD *pValidNum, BOOL *pEnableBind);
    ///
    /// \brief NET_DVR_GetLocalIP_L 获取所有网卡IP
    ///
    NET_DVR_GetLocalIPFUN NET_DVR_GetLocalIP_L;

    typedef   BOOL   (*NET_DVR_SetValidIPFUN)(DWORD dwIPIndex, BOOL bEnableBind);
    ///
    /// \brief NET_DVR_SetValidIP_L 绑定网卡
    ///
    NET_DVR_SetValidIPFUN NET_DVR_SetValidIP_L;

    typedef   BOOL (*NET_DVR_StopRealPlayFUN)(LONG lRealHandle);
    ///
    /// \brief NET_DVR_StopRealPlay_L 停止预览
    ///
    ///
    NET_DVR_StopRealPlayFUN NET_DVR_StopRealPlay_L;

    typedef   BOOL  (*NET_DVR_RemoteControlFUN)(LONG lUserID, DWORD dwCommand, LPVOID lpInBuffer, DWORD dwInBufferSize);
    ///
    /// \brief NET_DVR_RemoteControl_L 远程控制,设备运行状态
    ///
    NET_DVR_RemoteControlFUN NET_DVR_RemoteControl_L;

    typedef  int (*NET_DVR_GetRealPlayerIndexFUN)(LONG    lRealHandle);
    ///
    /// \brief NET_DVR_GetRealPlayerIndex_L 获取预览时用来解码和显示的播放器句柄。
    ///
    NET_DVR_GetRealPlayerIndexFUN NET_DVR_GetRealPlayerIndex_L;

    typedef  BOOL (*NET_DVR_SetConnectTimeFUN)( DWORD   dwWaitTime,DWORD   dwTryTimes);
    ///
    /// \brief NET_DVR_SetConnectTime_L 设置网络连接超时时间和连接尝试次数。
    ///
    NET_DVR_SetConnectTimeFUN NET_DVR_SetConnectTime_L;

    typedef   BOOL (*NET_DVR_SetReconnectFUN)(DWORD   dwInterval,BOOL    bEnableRecon    );
    ///
    /// \brief NET_DVR_SetReconnect_L 设置重连功能。
    ///
    NET_DVR_SetReconnectFUN NET_DVR_SetReconnect_L;

    typedef   BOOL (*NET_DVR_SetRecvTimeOutFUN)(DWORD   nRecvTimeOut);
    ///
    /// \brief NET_DVR_SetRecvTimeOut_L 设置接收超时时间
    ///
    NET_DVR_SetRecvTimeOutFUN NET_DVR_SetRecvTimeOut_L;



    /*****************************
    * @brief:海康播放库
    ******************************/

    typedef   BOOL  (*PlayM4_GetPortFUN)(  LONG*    nPort);
    ///
    /// \brief PlayM4_GetPort 获取未使用的通道号。
    /// nport 播放通道号，指向用于获取端口号的LONG型变量指针
    ///
    PlayM4_GetPortFUN PlayM4_GetPort_L;

    typedef   BOOL  (*PlayM4_OpenStreamFUN)(  LONG nPort,  PBYTE pFileHeadBuf, DWORD nSize,  DWORD nBufPoolSize);
    ///
    /// \brief PlayM4_OpenStream 打开流。
    /// nPort  播放通道号
    /// pFileHeadBuf  文件头数据
    /// nSize  文件头长度
    ///nBufPoolSize 设置播放器中存放数据流的缓冲区大小。范围是SOURCE_BUF_MIN~ SOURCE_BUF_MAX。该值过小会导致无法解码。
    ///
    PlayM4_OpenStreamFUN PlayM4_OpenStream_L;

    typedef   BOOL (*PlayM4_SetDecCallBackFUN)(  LONG     nPort,  void (CALLBACK* CallBack)(long nPort, char *pBuf, long nSize, FRAME_INFO *pFrameInfo, long luser, long nReserved2));
    ///
    /// \brief PlayM4_SetDecCallBack 解码回调
    /// nPort 播放通道号
    /// DecCallBack 解码回调函数指针，若不需要调用回调函数则置为NULL，否则不能为NULL
    ///
    PlayM4_SetDecCallBackFUN PlayM4_SetDecCallBack_L;

    typedef BOOL (*PlayM4_PlayFUN)(LONG   nPort, HWND   hWnd);
    ///
    /// \brief PlayM4_Play 开启播放。
    /// nPort 播放通道号
    /// HWND 播放视频的窗口句柄
    ///
    PlayM4_PlayFUN PlayM4_Play_L;

    typedef BOOL (*PlayM4_InputDataFUN)(  LONG      nPort,  PBYTE     pBuf,  DWORD     nSize);
    ///
    /// \brief PlayM4_InputData 输入流数据。
    /// nPort  播放通道号
    /// pBuf 流数据缓冲区地址
    /// nSize 流数据缓冲区大小
    ///
    PlayM4_InputDataFUN PlayM4_InputData_L;

    typedef   BOOL (*PlayM4_StopFUN)(  LONG     nPort);
    ///
    /// \brief PlayM4_Stop 关闭播放。
    ///
    PlayM4_StopFUN PlayM4_Stop_L;

    typedef BOOL (*PlayM4_CloseStreamFUN)(  LONG  nPort);
    ///
    /// \brief PlayM4_CloseStream 关闭流。
    ///
    PlayM4_CloseStreamFUN PlayM4_CloseStream_L;

    typedef   BOOL  (*PlayM4_FreePortFUN)(  LONG      nPort);
    ///
    /// \brief PlayM4_FreePort 释放已使用的通道号
    ///
    PlayM4_FreePortFUN PlayM4_FreePort_L;

    typedef   DWORD  (*PlayM4_GetLastErrorFUN)(  LONG   nPort);
    PlayM4_GetLastErrorFUN PlayM4_GetLastError_L;


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

    ///
    /// \brief g_RealDataCallBack_V30 预览回调函数
    /// \param lRealHandle 当前的预览句柄，NET_DVR_RealPlay_V40的返回值
    /// \param dwDataType 数据类型 宏定义 宏定义值 含义
    /// \param pBuffer 存放数据的缓冲区指针
    /// \param dwBufSize 缓冲区大小
    /// \param dwUser 用户数据
    ///
    static void CALLBACK g_RealDataCallBack_V30(LONG lRealHandle, DWORD dwDataType, BYTE *pBuffer,DWORD dwBufSize,void* dwUser);

    ///
    /// \brief DecCallBack 解码流回调函数
    /// \param nPort
    /// \param pBuf
    /// \param nSize
    /// \param pFrameInfo
    /// \param luser
    /// \param nReserved2
    ///
    static void CALLBACK DecCallBack(long nPort, char *pBuf, long nSize, FRAME_INFO *pFrameInfo, long luser, long nReserved2);

    ///
    /// \brief yv12ToRGB888 yv12转RGB888
    /// \param yv12
    /// \param rgb888
    /// \param width
    /// \param height
    /// \return
    ///
    void yv12ToRGB888(int ID, int width, int height, unsigned char *yv12, long nPort);

    ///
    /// \brief initVideoStream 视频流抓图
    /// \param ID
    /// \param play
    ///
    void initVideoStream(int ID,bool play);

private slots:
    ///
    /// \brief getDeviceStatusSlot 获取设备运行状态
    /// \param lUserID 登录ID
    /// \return
    ///
    void getDeviceStatusSlot();

    ///
    /// \brief resizeEventSlot 通知动态库调整窗口
    ///
    void resizeEventSlot();//Q_DECL_OVERRIDE;
};

#endif // THEMIDDLEWAREHCNET_H
