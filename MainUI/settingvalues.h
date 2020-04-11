#ifndef SETTINGVALUES_H
#define SETTINGVALUES_H

#include <QObject>

class SettingValues
{
public:
    SettingValues() {}

    ///
    /// \brief CameraVersion 相机协议
    ///
    int CameraVersion;

    ///
    /// \brief ProtocolVersion 通讯协议
    ///
    int ProtocolVersion;

    ///
    /// \brief ChannelNumber 通道数量
    ///
    int ChannelNumber;

    ///
    /// \brief ImageFormatOne 保存图片格式1
    ///
    int ImageFormatOne;

    ///
    /// \brief ImageFormatTow 保存图片格式12
    ///
    int ImageFormatTow;

    ///
    /// \brief SaveImageOne 图片保存状态1
    ///
    int SaveImageOne;

    ///
    /// \brief SaveImageTow 图片保存状态2
    ///
    int SaveImageTow;

    ///
    /// \brief FTP 是否启动上传图片
    ///
    int FTP;

    ///
    /// \brief FtpAddress FTP地址
    ///
    QString FtpAddress;

    ///
    /// \brief FtpLocalImgPath FTP本地图片路径
    ///
    QString FtpLocalImgPath;

    ///
    /// \brief FtpPassword FTP密码
    ///
    QString FtpPassword;

    ///
    /// \brief FtpPort FTP端口
    ///
    QString FtpPort;

    ///
    /// \brief FtpRemoteImgPath FTP远端图片地址
    ///
    QString FtpRemoteImgPath;

    ///
    /// \brief FtpUser FTP用户名
    ///
    QString FtpUser;

    ///
    /// \brief Language 语言版本
    ///
    int Language;

    ///
    /// \brief Minimization 启动最小化状态
    ///
    int Minimization;

    ///
    /// \brief Automatic 开机自动启动
    ///
    int Automatic;

    ///
    /// \brief SaveLog 保持日志状态
    ///
    int SaveLog;

    ///
    /// \brief SaveLogVersion 日志版本
    ///
    int SaveLogVersion;

    ///
    /// \brief InfoLog 运行日志
    ///
    int InfoLog;

    ///
    /// \brief ErrorLog 错误日志
    ///
    int ErrorLog;

    ///
    /// \brief WarningLog 警告日志
    ///
    int WarningLog;

    ///
    /// \brief AutomaticCorrection 自动校验结果
    ///
    int AutomaticCorrection;

    ///
    /// \brief ClientModel 客户端模式
    ///
    int ClientModel;

    ///
    /// \brief ServerModel 服务器模式
    ///
    int ServerModel;

    ///
    /// \brief ClientIP 客户端地址
    ///
    QString ClientIP;

    ///
    /// \brief ServerIP 服务器地址
    ///
    QString ServerIP;

    ///
    /// \brief ColorDisplay 颜色显示识别结果
    ///
    int ColorDisplay;

    ///
    /// \brief ImgPathOne 图片路径1
    ///
    QString ImgPathOne;

    ///
    /// \brief ImgPathTow 图片路径2
    ///
    QString ImgPathTow;

    ///
    /// \brief HcSDKPath 海康SDK路径
    ///
    QString HcSDKPath;

    ///
    /// \brief DataBaseVersion 数据库版本
    ///
    int DataBaseVersion;

    ///
    /// \brief DataBaseUser 数据库用户名
    ///
    QString DataBaseUser;

    ///
    /// \brief DataBasePassword 数据库密码
    ///
    QString DataBasePwd;

    ///
    /// \brief DataBaseAddr 数据库地址
    ///
    QString DataBaseAddr;

    ///
    /// \brief DataBasePort 数据库端口
    ///
    int DataBasePort;

    ///
    /// \brief TextFormat 数据保存文本
    ///
    int TextFormat;

    ///
    /// \brief TextFormatVersion 数据保存文本版本
    ///
    int TextFormatVersion;
};

#endif // SETTINGVALUES_H
