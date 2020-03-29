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
    /// \brief SaveLog 保持日志状态
    ///
    int SaveLog;

    ///
    /// \brief AutomaticCorrection 自动校验结果
    ///
    int AutomaticCorrection;

    ///
    /// \brief Client SOCKET服务状态
    ///
    int Client;

    ///
    /// \brief ClientIP SOCKET客户地址
    ///
    QString ClientIP;

    ///
    /// \brief ClientPort SOCKET客户端口
    ///
    int ClientPort;

    ///
    /// \brief Server SOCKET服务状态
    ///
    int Server;

    ///
    /// \brief ServerIP SOCKET服务地址
    ///
    QString ServerIP;

    ///
    /// \brief ServerPort SOCKET服务端口
    ///
    int ServerPort;

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
};

#endif // SETTINGVALUES_H
