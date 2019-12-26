#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QDir>
#include <QPluginLoader>
#include <QPixmap>
#include <QDebug>

#include "getimages_interface.h"


namespace Ui {
class MainWidget;
}

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MainWidget(QWidget *parent = nullptr);
    ~MainWidget();

private://对象
    Ui::MainWidget *ui;

    GetImagesInterface *pGetimagesInterface;

private://函数

    ///------------------------------------------------------------------------------------------------------------
    /// \brief loadPlugin 加载插件
    ///------------------------------------------------------------------------------------------------------------
    void loadPlugin();

    ///------------------------------------------------------------------------------------------------------------
    /// \brief ProcessingPlug 处理插件
    /// \param plugin 插件对象
    ///------------------------------------------------------------------------------------------------------------
    void processingPlug(QObject *plugin);

private slots://槽

    ///------------------------------------------------------------------------------------------------------------
    /// \brief camerIDstates 相机状态
    /// \param camerIP 相机地址
    /// \param state 相机状态
    ///------------------------------------------------------------------------------------------------------------
    void camerIDstates(const QString &camerIP,bool state);

    ///------------------------------------------------------------------------------------------------------------
    /// \brief pictureStream 接受图片流
    /// \param jpgStream 图片流
    /// \param camerIP 相机地址
    ///------------------------------------------------------------------------------------------------------------
    void pictureStream(const QByteArray &jpgStream,const QString &camerIP);

    ///------------------------------------------------------------------------------------------------------------
    /// \brief message 日志
    /// \param msg 信息体
    ///------------------------------------------------------------------------------------------------------------
    void message(const QString &msg);

    void on_pushButton_clicked();

signals://信号

    ///------------------------------------------------------------------------------------------------------------
    /// \brief initCamer 初始化相机
    /// \param camerIP 相机地址
    /// \param camerPort 相机端口
    ///------------------------------------------------------------------------------------------------------------
    void initCamer(const QString &camerIP, quint16 camerPort);

    ///------------------------------------------------------------------------------------------------------------
    /// \brief putCommand 相机指令
    /// \param command 指令
    /// \return  返回执行状态
    ///------------------------------------------------------------------------------------------------------------
    bool putCommand(const QString &command);

};

#endif // MAINWIDGET_H
