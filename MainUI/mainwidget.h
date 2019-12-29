#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QDir>
#include <QPluginLoader>
#include <QPixmap>
#include <QDebug>
#include <QTreeWidgetItem>
#include<QResizeEvent>

//------------------------------------------------------------------------------------------------------------Interface
#include "getimages_interface.h"
//------------------------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------------------------UI
#include "picturewidget.h"
#include "datawidget.h"
#include "camersetting.h"
#include "systemsetting.h"
//------------------------------------------------------------------------------------------------------------

namespace Ui {
class MainWidget;
}

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MainWidget(QWidget *parent = nullptr);
    ~MainWidget()override;

private://变量
     int channelCounnt;

private://对象
    Ui::MainWidget *ui;
    GetImagesInterface *pGetimagesInterface;   
    QList<QString> camerName;
    QMap< QTreeWidgetItem*,QObject*> widgetMap;

private://函数

    ///------------------------------------------------------------------------------------------------------------MainUI
    /// \brief InitializeObject 初始化对象
    ///
    void InitializeObject();

    ///------------------------------------------------------------------------------------------------------------MainUI
    /// \brief InitializeOtherWindow 初始化其他窗口
    ///
    void InitializeOtherWindow();

    ///------------------------------------------------------------------------------------------------------------MainUI
    /// \brief InitializeDataWindow 初始化数据窗口
    ///
    void InitializeDataWindow();

    ///------------------------------------------------------------------------------------------------------------MainUI
    /// \brief InitializeCamerWindow 初始化相机窗口
    ///
    void InitializeCamerWindow();

    ///------------------------------------------------------------------------------------------------------------MainUI
    /// \brief loadPlugin 加载插件
    ///
    void loadPlugin();

    ///------------------------------------------------------------------------------------------------------------MainUI
    /// \brief ProcessingPlug 处理插件
    /// \param plugin 插件对象
    ///
    void processingPlug(QObject *plugin);

    ///------------------------------------------------------------------------------------------------------------MainUI
    /// \brief hideWindows 隐藏所有窗口
    ///
    void hideWindows();

private slots://槽

    ///------------------------------------------------------------------------------------------------------------GetImgaes
    /// \brief camerIDstates 相机状态
    /// \param camerIP 相机地址
    /// \param state 相机状态
    ///
    void camerIDstates(const QString &camerIP,bool state);

    ///------------------------------------------------------------------------------------------------------------GetImgaes
    /// \brief pictureStream 接受图片流
    /// \param jpgStream 图片流
    /// \param camerIP 相机地址
    ///
    void pictureStream(const QByteArray &jpgStream,const QString &camerIP);

    ///------------------------------------------------------------------------------------------------------------MainUI
    /// \brief message 日志
    /// \param msg 信息体
    ///
    void message(const QString &msg);

    ///------------------------------------------------------------------------------------------------------------MainUI
    /// \brief resizeEvent 重写窗口改变大小事件
    /// \param size 窗口尺寸
    ///
    void resizeEvent(QResizeEvent *size)override;

    ///------------------------------------------------------------------------------------------------------------MainUI
    /// \brief on_treeWidget_itemActivated 导航栏选取事件
    /// \param item 选取项
    /// \param column 列
    ///
    void on_treeWidget_itemActivated(QTreeWidgetItem *item, int column);

signals://信号

    ///------------------------------------------------------------------------------------------------------------GetImgaes
    /// \brief initCamer 初始化相机
    /// \param camerIP 相机地址
    /// \param camerPort 相机端口
    ///
    void initCamer(const QString &camerIP, quint16 camerPort);

    ///------------------------------------------------------------------------------------------------------------GetImgaes
    /// \brief putCommand 相机指令
    /// \param command 指令
    /// \return  返回执行状态
    ///
    bool putCommand(const QString &command);

};

#endif // MAINWIDGET_H
