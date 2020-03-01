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

private slots:
    void on_buttonBox_clicked(QAbstractButton *button);

private:
    Ui::SystemSettingWidget *ui;

    ///
    /// \brief jsonWrite 写入参数到配置文件
    ///
    void jsonWrite();

    ///
    /// \brief jsonRead 读取参数到配置文件
    ///
    void jsonRead();

signals:

    ///
    /// \brief messageSignal 日志信息信号
    /// \param msg 信息
    ///
    void messageSignal(const QString &msg);
};

#endif // SYSTEMSETTING_H
