#ifndef ELECTRONICLICENSEPLATE_H
#define ELECTRONICLICENSEPLATE_H

#define ZBY_LOG(type)  tr("[%1][%2][%3]").arg(type).arg(Q_FUNC_INFO).arg(__LINE__)

#include "electroniclicenseplate_global.h"
#include "licenseplateinterface.h"
#include "LPRCClientSDK.h"

class ELECTRONICLICENSEPLATESHARED_EXPORT ElectronicLicensePlate:public LicensePlateInterface
{

    Q_OBJECT
    Q_INTERFACES(LicensePlateInterface)
    Q_PLUGIN_METADATA(IID LicensePlateInterfaceIID)

public:
    ElectronicLicensePlate(QObject *parent=nullptr);
    ~ElectronicLicensePlate()Q_DECL_OVERRIDE;

    ///
    /// \brief initializationParameter 初始化参数
    /// \param addr 地址
    /// \param port 端口
    /// \param imgPath 图片路径
    /// \param channel 通道号
    ///
    bool initializationParameter();

    ///
    /// \brief saveImg 保存图片
    /// \param arrImg
    ///
    void saveImg(QByteArray arrImg,const QString &time);

    ///
    /// \brief simulationCaptureSlot 模拟抓拍
    ///
    void simulationCaptureSlot()Q_DECL_OVERRIDE;

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
    /// \brief openTheVideoSlot 打开视频/关闭视频
    /// \param play
    ///
    void openTheVideoSlot(bool play,quint64 winID=0)Q_DECL_OVERRIDE;

    ///
    /// \brief releaseResourcesSlot 释放动态库资源
    ///
    void releaseResourcesSlot()Q_DECL_OVERRIDE;

    ///
    /// \brief initCameraSlot 初始化相机
    /// \param localAddr 本机地址(用户绑定网卡)
    /// \param addr 相机地址
    /// \param port 端口
    /// \param imgPath 图片地址
    /// \param channel 通道号
    ///
    void initCameraSlot(const QString &localAddr,const QString &addr, const int &port, const QString &imgPath, int imgFormat,const int &channel)Q_DECL_OVERRIDE;

private:

    static void connectCallback(char *chWTYIP,UINT nStatus,LDWORD dwUser);
    typedef   void (*CLIENT_LPRC_RegCLIENTConnEventFUN)(CLIENT_LPRC_ConnectCallback CLIENTConnect);
    ///
    /// \brief CLIENT_LPRC_RegCLIENTConnEvent 注册连接状态回调函数的函数
    ///
    CLIENT_LPRC_RegCLIENTConnEventFUN CLIENT_LPRC_RegCLIENTConnEvent;

    static void dataEx2Callback(CLIENT_LPRC_PLATE_RESULTEX *recResultEx,LDWORD dwUser);
    typedef   void (*CLIENT_LPRC_RegDataEx2EventFUN)(CLIENT_LPRC_DataEx2Callback CLIENTDataEx2);
    ///
    /// \brief CLIENT_LPRC_RegDataEx2Event 注册获取识别结果的回调函数
    ///
    CLIENT_LPRC_RegDataEx2EventFUN CLIENT_LPRC_RegDataEx2Event;

    static void jpegCallback(CLIENT_LPRC_DEVDATA_INFO *JpegInfo,LDWORD dwUser);
    typedef   void (*CLIENT_LPRC_RegJpegEventFUN)(CLIENT_LPRC_JpegCallback  JpegInfo);
    ///
    /// \brief CLIENT_LPRC_RegJpegEvent 注册获取Jpeg流的回调函数
    ///
    CLIENT_LPRC_RegJpegEventFUN CLIENT_LPRC_RegJpegEvent;

    static void getGpioStateCallback(char *chWTYIP,CLIENT_LPRC_GPIO_In_Statue *pGpioState);
    typedef   void  (*CLIENT_LPRC_RegWTYGetGpioStateFUN) (CLIENT_LPRC_GetGpioStateCallback   CLIENTGpioState);
    ///
    /// \brief CLIENT_LPRC_RegWTYGetGpioState 注册获取相机GPIO状态回调函数
    ///
    CLIENT_LPRC_RegWTYGetGpioStateFUN CLIENT_LPRC_RegWTYGetGpioState;

    static void serialDataCallback(char *chCLIENTIP,CLIENT_LPRC_DEVSERIAL_DATA *pSerialData,LDWORD dwUser);
    typedef   void (*CLIENT_LPRC_RegSerialDataEventFUN)(CLIENT_LPRC_SerialDataCallback CLIENTSerialData);
    ///
    /// \brief CLIENT_LPRC_RegSerialDataEvent 注册获取RS485串口回传数据的回调函数
    ///
    CLIENT_LPRC_RegSerialDataEventFUN CLIENT_LPRC_RegSerialDataEvent;

    /*
    * nPort[in]:              请求连接的设备端口，默认8080
    * hWndHandle [in]: 接收消息的窗体句柄，当为NULL时，表示无窗体
    * uMsg[in]:         用户自定义消息，当hWnd不为NULL时，此为窗口消息标识
    * chServerIP[in]: 相机的IP地址
    * dwUser[in]:      用户自定义字段，主要用来传给回调函数
    */
    typedef   int (*CLIENT_LPRC_InitSDKFUN)(UINT nPort,HWND hWndHandle,UINT uMsg,char *chServerIP,LDWORD dwUser);
    ///
    /// \brief CLIENT_LPRC_InitSDK 连接相机设备
    ///
    CLIENT_LPRC_InitSDKFUN CLIENT_LPRC_InitSDK;

    /*
     * chSavePath[in]: 文件存储路径，以"\\"结束，如："D:\\Image\\"
     */
    typedef  void (*CLIENT_LPRC_SetSavePathFUN) (char *chSavePath);
    ///
    /// \brief CLIENT_LPRC_SetSavePath 设置保存识别图片的路径
    ///
    CLIENT_LPRC_SetSavePathFUN CLIENT_LPRC_SetSavePath;

    /*
     * pCameraIP[in]：      已连接设备 IP 地址
     * nCameraPort[in]：   已连接设备端口,默认 8080
     */
    typedef   int (*CLIENT_LPRC_SetTriggerFUN)(char *pCameraIP, int nCameraPort);
    ///
    /// \brief CLIENT_LPRC_SetTrigger 模拟地感触发信号
    ///
    CLIENT_LPRC_SetTriggerFUN CLIENT_LPRC_SetTrigger;

    /*
     * pCameraIP[in]  相机设备的ip地址
     * onoff[in]             流开关项，0表示关闭流，1表示打开jpeg流 2打开H264
     */
    typedef   int (*CLIENT_LPRC_SetJpegStreamPlayOrStopFUN)(char *pCameraIP,int onoff);
    ///
    /// \brief CLIENT_LPRC_SetJpegStreamPlayOrStop 设置流模式切换
    ///
    CLIENT_LPRC_SetJpegStreamPlayOrStopFUN CLIENT_LPRC_SetJpegStreamPlayOrStop;

    /*
     * pCameraIP[in]:        已连接设备IP地址
     * nCameraPort[in]:     已连接设备端口，默认9110
     */
    typedef   int (*CLIENT_LPRC_SetRelayCloseFUN)(char *pCameraIP, int nCameraPort);
    ///
    /// \brief CLIENT_LPRC_SetRelayClose 通过继电器抬杆
    ///
    CLIENT_LPRC_SetRelayCloseFUN CLIENT_LPRC_SetRelayClose;

    /*
     * pCameraIP[in]:         已连接设备IP地址
     * nCameraPort[in]:     已连接设备端口，默认9110
     */
    typedef   int  (*CLIENT_LPRC_DropRodFUN)(char *pCameraIP, int nCameraPort);
    ///
    /// \brief CLIENT_LPRC_DropRod 通过继电器控制落杆
    ///
    CLIENT_LPRC_DropRodFUN CLIENT_LPRC_DropRod;

    /*
     * pCameraIP[in]: 要绑定的网卡IP地址
     */
    typedef   int (*CLIENT_LPRC_SetNetworkCardBindFUN)(char *pCameraIP);
    ///
    /// \brief CLIENT_LPRC_SetNetworkCardBind 手动绑定指定网卡IP
    ///
    CLIENT_LPRC_SetNetworkCardBindFUN CLIENT_LPRC_SetNetworkCardBind;

    /*
     * pCameraIP[in]:  相机设备IP地址
     * nCameraPort:   端口,默认9110
     * CLIENT_LPRC_RS485_Transparent_t nRs485:   传输485数据的结构体
     */
    typedef   int (*CLIENT_LPRC_RS485SendFUN)(char *pCameraIP, int nCameraPort, char *chData,int   nSendLen);
    ///
    /// \brief CLIENT_LPRC_RS485SendFUN RS485透明传输扩展接口，可以一次性发送最大5条数据
    ///
    CLIENT_LPRC_RS485SendFUN CLIENT_LPRC_RS485Send;

    typedef int (*CLIENT_LPRC_QuitDeviceFUN)(char *pCameraIP) ;
    ///
    /// \brief CLIENT_LPRC_QuitDevice 断开链接
    ///
    CLIENT_LPRC_QuitDeviceFUN CLIENT_LPRC_QuitDevice;

    QString address;
    QString imgPath;
    int imgFormat;
    int channel;
    int port; 

    bool isSDKinit;
    QLibrary* pDLL;

    QByteArray arrAddr;
    QMutex mutex; 

    static ElectronicLicensePlate *pThis;
    static bool complate;


private slots:

    ///
    /// \brief autoLinkCamer 链接事变自动重连
    ///
    void autoLinkCamer();




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

    /*****************************
    * @brief:海康相机其它实现
    ******************************/
};

#endif // ELECTRONICLICENSEPLATE_H
