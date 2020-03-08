#ifndef CAPTUREIMAGES_H
#define CAPTUREIMAGES_H

#include "HCNetSDK.h"
#include "captureimages_global.h"
#include "getimagesinterface.h"

class CAPTUREIMAGESSHARED_EXPORT CaptureImages:public GetImagesInterface
{
    Q_OBJECT
    Q_INTERFACES(GetImagesInterface)
    Q_PLUGIN_METADATA(IID  GetImagesInterfaceIID)

public:
    CaptureImages(QObject *parent = nullptr);
    ~CaptureImages()Q_DECL_OVERRIDE;

private:

    ///端口
    int port;

    ///地址,用户名,密码
    QString  ip,name ,pow;

    ///登录用户ID,视频流ID
    LONG lUserID,streamID;

    ///登录结果
    DWORD dwResult;

    QLibrary *pDLLHCNet;

    static CaptureImages* pThis;

private:

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
    /// \brief NET_DVR_Cleanup_L 清楚内存
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

private:

    ///
    /// \brief getDeviceStatus 获取设备运行状态
    /// \param lUserID 登录ID
    /// \return
    ///
    bool getDeviceStatus(LONG lUserID);

    ///
    /// \brief loginCamer 登录相机
    ///
    void loginCamer();

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
    void initCamerSlot(const QString &camerIP, quint16 camerPort, const QString &CamerUser, const QString &CamerPow) Q_DECL_OVERRIDE;

    ///
    /// \brief putCommandSlot 抓取图片
    /// \param imgNumber 编号
    /// \return
    ///
    bool putCommandSlot(const int &imgNumber) Q_DECL_OVERRIDE;

    ///
    /// \brief playStreamSlot 重写播放视频流函数
    /// \param winID 窗口句柄
    /// \param play 播放状态
    ///
    void playStreamSlot(uint winID, bool play) Q_DECL_OVERRIDE;

    ///
    /// \brief resizeEventSlot 通知动态库调整窗口
    ///
    void resizeEventSlot()Q_DECL_OVERRIDE;

    ///
    /// \brief closeStream 关闭视频流
    ///
    void closeStreamSlot()Q_DECL_OVERRIDE;
};

#endif // CAPTUREIMAGES_H
