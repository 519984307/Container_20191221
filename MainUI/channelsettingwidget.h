#ifndef CAMERSETTING_H
#define CAMERSETTING_H

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

    void jsonWrite();
    void jsonRead();

signals:

    ///
    /// \brief messageSignal 日志信息信号
    /// \param msg 信息
    ///
    void messageSignal(const QString &msg);

private slots:
    void on_buttonBox_clicked(QAbstractButton *button);
};

#endif // CAMERSETTING_H
