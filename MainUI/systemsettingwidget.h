#ifndef SYSTEMSETTING_H
#define SYSTEMSETTING_H

#include <QWidget>
#include <QAbstractButton>
#include <QDir>
#include <QFile>
#include <QIODevice>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonParseError>
#include <QJsonValue>

namespace Ui {
class SystemSettingWidget;
}

class SystemSettingWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SystemSettingWidget(QWidget *parent = nullptr);
    ~SystemSettingWidget();

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

private:
    Ui::SystemSettingWidget *ui;

    ///
    /// \brief getJsonValue 获取配置项
    /// \param child 配置项子名称
    /// \param key 配置项值
    /// \param obj JSON对象
    /// \return
    ///
    QVariant  getJsonValue(const QString &child,const QString &key,QJsonObject obj);

    ///
    /// \brief jsonWrite 写入参数到配置文件
    ///
    bool jsonWrite();

    ///
    /// \brief jsonRead 读取参数到配置文件
    ///
    bool jsonRead();

private slots:

    void on_buttonBox_clicked(QAbstractButton *button);

signals:

    ///
    /// \brief messageSignal 日志信息信号
    /// \param msg 信息
    ///
    void messageSignal(const QString &msg);
};

#endif // SYSTEMSETTING_H
