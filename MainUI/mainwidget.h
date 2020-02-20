#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QDir>
#include <QPluginLoader>
#include <QPixmap>
#include <QDebug>
#include <QThread>
#include <QTreeWidgetItem>
#include <QResizeEvent>
#include <QStatusBar>
#include <QCloseEvent>

//------------------------------------------------------------------------------------------------------------Interface
#include "getimagesinterface.h"
#include "infraredlogicinterface.h"

//------------------------------------------------------------------------------------------------------------Headers
#include "setting.h"

//------------------------------------------------------------------------------------------------------------UI
#include "picturewidget.h"
#include "datawidget.h"
#include "camersetting.h"
#include "systemsetting.h"
#include "servicewidget.h"
#include "databasewidget.h"

//------------------------------------------------------------------------------------------------------------Process
#include "imageprocessing.h"
#include "logicalprocessing.h"

namespace Ui {
class MainWidget;
}

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MainWidget(QWidget *parent = nullptr);
    ~MainWidget()override;

private:
    Ui::MainWidget *ui;

    ///
    /// \brief statusBar 系统状态栏
    ///
    QStatusBar *statusBar;

    ///
    /// \brief CamerNameList 通道相机列表
    ///
    QList<QString> CamerNameList;

    ///
    /// \brief ThreadList 插件线程池
    ///
    QList<QThread*> ThreadList;

    ///
    /// \brief Separators 路径分割符
    ///
    QString  separators;

    ///
    /// \brief channelCounnt 通道数
    ///
    int channelCounnt;

private:

    /*
     * 窗口字典
     */
    QHash<int,QObject*>CamerWidgetMap;
    QHash<int,QObject*>DataWidgetMap;

    /*
     * treeWidget判断显示窗口
     */
    QHash<QTreeWidgetItem*,QObject*> ItemWidgetMap;

    ///图片处理类
    QHash<int,QObject*> ImageProcessingMap;

private:

    ///
    /// \brief closeEvent 重新窗口关闭事件
    /// \param event
    ///
    void closeEvent(QCloseEvent *event)Q_DECL_OVERRIDE;

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
    void loadPlugins();

    ///------------------------------------------------------------------------------------------------------------MainUI
    /// \brief ProcessingPlug 分析插件
    ///
    void processingPlugins(QDir path,int num);

    ///------------------------------------------------------------------------------------------------------------MainUI
    /// \brief camerPlugin 处理相机插件
    /// \param Camer 相机类
    ///
    void getImagePlugin(GetImagesInterface* pGetimagesInterface,int num);

    ///------------------------------------------------------------------------------------------------------------MainUI
    /// \brief serialportPlugin 处理串口插件
    /// \param SerialPort 串口类
    ///
    void serialportPlugin(InfraredlogicInterface* pInfraredlogicInterface,int num);

    ///------------------------------------------------------------------------------------------------------------MainUI
    /// \brief hideWindows 隐藏所有窗口
    ///
    void hideWindows();

    ///------------------------------------------------------------------------------------------------------------MainUI
    /// \brief setStatusBar 设置状态栏
    ///
    void setStatusBar();

private slots:

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
    void on_treeWidget_itemActivated(QTreeWidgetItem *item);

signals:

    ///
    /// \brief closeStreamSignal 关闭视频流
    ///
    void closeStreamSignal();
};

#endif // MAINWIDGET_H
