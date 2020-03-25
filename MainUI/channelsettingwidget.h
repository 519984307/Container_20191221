#ifndef CAMERSETTING_H
#define CAMERSETTING_H

#include "defineobj.h"

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
class ChannelSettingWidget;
}

class ChannelSettingWidget : public QWidget
{
    Q_OBJECT

public:

    /* 构造函数传递通道编号 */
    explicit ChannelSettingWidget(int number,QWidget *parent = nullptr);
    ~ChannelSettingWidget();

public:

    ///
    /// \brief Alias 通道别名
    ///
    QString Alias;

    ///
    /// \brief LicensePlate 车牌协议
    ///
    int LicensePlate;

    ///
    /// \brief AfterCamer 后相机
    ///
    QString AfterCamer;

    ///
    /// \brief BeforeCamer 前相机
    ///
    QString BeforeCamer;

    ///
    /// \brief LeftCamer 左相机
    ///
    QString LeftCamer;

    ///
    /// \brief RgihtCamer 右相机
    ///
    QString RgihtCamer;

    ///
    /// \brief PlateCamer 车牌相机
    ///
    QString PlateCamer;

    ///
    /// \brief PortOne 串口端口1
    ///
    int PortOne;

    ///
    /// \brief PortTow 串口端口2
    ///
    int PortTow;

    ///
    /// \brief SerialAddrOne 串口服务地址1
    ///
    QString SerialAddrOne;

    ///
    /// \brief SerialAddrTow 串口服务地址2
    ///
    QString SerialAddrTow;

    ///
    /// \brief SerialPortCloseState 串口常闭
    ///
    int SerialPortCloseState;

    ///
    /// \brief SerialPortMode 串口模式
    ///
    int SerialPortMode;

    ///
    /// \brief SerialPortOpenState 串口常开
    ///
    int SerialPortOpenState;

    ///
    /// \brief SerialPortTow 串口2
    ///
    int SerialPortTow;

    ///
    /// \brief SerialPortOne 串口1
    ///
    int SerialPortOne;

private:
    Ui::ChannelSettingWidget *ui;

    ///
    /// \brief channel 通道编号
    ///
    int channelNumber;

    ///
    /// \brief getJsonValue 获取配置项
    /// \param child 配置项子名称
    /// \param key 配置项值
    /// \param obj JSON对象
    /// \return
    ///
    QVariant  getJsonValue(const QString &child,const QString &key,QJsonObject obj);

    ///
    /// \brief jsonWrite 写入配置文件
    /// \return
    ///
    bool jsonWrite();

    ///
    /// \brief jsonRead 读取配置文件
    /// \return
    ///
    bool jsonRead();

    ///
    /// \brief jsonWritetoUI 回写配置到UI
    ///
    void jsonWritetoUI();

signals:

    ///
    /// \brief messageSignal 日志信号
    /// ]param type 信息类型
    /// \param msg 信息体
    ///
    void messageSignal(const QString &type,const QString &msg);

private slots:

    ///
    /// \brief on_buttonBox_clicked 保存参数
    /// \param button
    ///
    void on_buttonBox_clicked(QAbstractButton *button);

};

#endif // CAMERSETTING_H
