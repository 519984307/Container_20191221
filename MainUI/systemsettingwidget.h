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
#include <QXmlStreamWriter>

//#include<setting.h>

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
    /// \brief writeINI 写入参数到配置文件
    ///
    void writeINI();

    ///
    /// \brief readINI 读取参数到配置文件
    ///
    void readINI();

signals:

    ///
    /// \brief mesageSignal 日志信息信号
    /// \param msg 信息
    ///
    void mesageSignal(const QString &msg);
};

#endif // SYSTEMSETTING_H
