#ifndef SYSTEMSETTING_H
#define SYSTEMSETTING_H

#include "settingvalues.h"
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
#include <QFileDialog>
#include <QDateTime>
#include <QMessageBox>
#include <QTextStream>
#include <QtDebug>

namespace Ui {
class SystemSettingWidget;
}

class SystemSettingWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SystemSettingWidget(QWidget *parent = nullptr);
    ~SystemSettingWidget();

public:

    ///
    /// \brief pSettingValues 配置参数表
    ///
    SettingValues* pSettingValues;

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

    ///
    /// \brief J sonWriteToUI 反写配置到UI
    /// \return
    ///
    void jsonWritetoUI();

    ///
    /// \brief createImgPath 创建图片保存路径
    /// \param path 图片路径
    /// \param currentindex 保存格式
    ///
    void createImgPath(const QString &path, int currentindex);

private slots:

    ///
    /// \brief on_buttonBox_clicked 保存参数
    /// \param button
    ///
    void on_buttonBox_clicked(QAbstractButton *button);

    ///
    /// \brief conditionsOfButton_clicked 字头条件按钮
    ///
    void conditionsOfButton_clicked();

    ///
    /// \brief checkPathPushButton_clicked 图片路径设置按钮
    ///
    void checkPathPushButton_clicked();

    ///
    /// \brief socketModel_clicked 网络模式设定
    /// \param checked 选取状态
    ///
    void socketModel_clicked(bool checked);

signals:

    ///
    /// \brief messageSignal 日志信息
    /// \param type 日志类型
    /// \param msg 信息体
    ///
    void messageSignal(const QString &type,const QString &msg);

    ///
    /// \brief setSaveImgFormatOneSignal 设置图片保存路径1
    /// \param path 图片路径
    /// \param format 保存协议
    ///
    void setSaveImgFormatOneSignal(const QString &path,int format);

    ///
    /// \brief setSaveImgFormatTowSignal 设置图片保存路径2
    /// \param path 图片路径
    /// \param format 保存协议
    ///
    void setSaveImgFormatTowSignal(const QString &path,int format);

    ///
    /// \brief setCheckTheResultsSlot 是否校验识别结果
    /// \param correct 校验标志
    ///
    void setCheckTheResultsSignal(bool correct=false);
};

#endif // SYSTEMSETTING_H
