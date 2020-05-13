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
#include <QCloseEvent>
#include <QStatusBar>
#include <QLabel>
#include <QMap>
#include <QMetaType>
#include <QDebug>
#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include <QMessageBox>

//------------------------------------------------------------------------------------------------------------Interface
#include "getimagesinterface.h"
#include "infraredlogicinterface.h"
#include "databaseinsertinterface.h"
#include "databasereadinterface.h"
#include "recognizerinterface.h"
#include "resultsanalysisinterface.h"
#include "socketserverinterface.h"
#include "encryptioninterface.h"
#include "ICaptureUnderlying.h"

//------------------------------------------------------------------------------------------------------------UI
#include "picturewidget.h"
#include "datawidget.h"
#include "channelsettingwidget.h"
#include "systemsettingwidget.h"
#include "servicewidget.h"
#include "databasewidget.h"
#include "logwidget.h"

//------------------------------------------------------------------------------------------------------------Process
#include "imageprocessing.h"
#include "infraredprocessing.h"
#include "databaseprocessing.h"
#include "recognizerprocessing.h"
#include "resultsanalysisprocessing.h"
#include "socketserverprocessing.h"
#include "encryptionprocessing.h"
#include "underlyinggetimagesprocessing.h"

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

    ///
    /// \brief pMenBar 菜单栏
    ///
    QMenuBar* pMenBar;

    ///
    /// \brief statusBar 系统状态栏
    ///
    QStatusBar *pStatusBar;

    ///
    /// \brief pStatusBarLabel 状态栏临时文本框
    ///
    QLabel* pStatusBarLabel;

    ///
    /// \brief pStatusBarLabelPermanet 状态栏永久文本框
    ///
    QLabel* pStatusBarLabelPermanet;

    ///
    /// \brief pDataBaseWidget 数据库窗口对象
    ///
    DataBaseWidget* pDataBaseWidget;

    ///
    /// \brief pSystemSettingWidget 系统设置窗口对象
    ///
    SystemSettingWidget* pSystemSettingWidget;

    ///
    /// \brief pServiceWidget f服务窗口对象
    ///
    ServiceWidget* pServiceWidget;

    ///
    /// \brief pLogWidget 日志窗口
    ///
    LogWidget* pLogWidget;

private:

    Ui::MainWidget *ui;

    ///
    /// \brief pEncryptionProcessing 加密处理类
    ///
    EncryptionProcessing* pEncryptionProcessing;

    ///
    /// \brief QActionMap 菜单按钮集
    ///
    QMap<QAction*,QObject*> QActionMap;

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

    ///
    /// \brief logPath 日志文件夹路径
    ///
    QString logPath;

private:

    ///
    /// \brief CameraMenuMap 相机子菜单字典
    ///
    QMap<int,QMenu*> CameraMenuMap;

    ///
    /// \brief pictureWidgetMap 相机窗口字典
    ///
    QMap<int,QObject*>PictureWidgetMap;

    ///
    /// \brief DataWidgetMap 数据窗口字典
    ///
    QMap<int,QObject*>DataWidgetMap;

    ///
    /// \brief ChannelSettingWidgetMap 通道设定窗口字典
    ///
    QMap<int,QObject*>ChannelSettingWidgetMap;

    ///
    /// \brief channelCamerMultiMap 通道对应的相机.
    ///
    QMultiHash<int,QObject*>channelCamerMultiMap;

    /*
     * treeWidget根据item判断显示窗口
     */
    QMap<QTreeWidgetItem*,QObject*> ItemWidgetMap;

    ///
    /// \brief ImageProcessingMap 图片处理类
    ///
    QMap<int,QObject*> ImageProcessingMap;

    ///
    /// \brief underlyingGetimagesProcessingMap 底层图片处理类
    ///
    QMap<int,QObject*> underlyingGetimagesProcessingMap;

    ///
    /// \brief infraredProcessingMap 红外逻辑处理类
    ///
    QMap<int,QObject*> InfraredProcessingMap;

    ///
    /// \brief DataBaseProcessingMap 数据库逻辑处理类
    ///
    QMap<int,QObject*> DataBaseProcessingMap;

    ///
    /// \brief RecognizerProcessingMap 识别器处理类
    ///
    QMap<int,QObject*> RecognizerProcessingMap;

    ///
    /// \brief ResultsAnalysisProcessingMap 识别结果分析类
    ///
    QMap<int,QObject*> ResultsAnalysisProcessingMap;

    ///
    /// \brief SocketServiceProcessingMap TCP处理类
    ///
    QMap<int,QObject*> SocketServiceProcessingMap;

private:

    ///
    /// \brief initalizeMenubar 初始化菜单
    ///
    void initalizeMenubar();

    ///
    /// \brief loadingParameters 加载参数
    ///
    void loadingParameters();

    ///
    /// \brief closeEvent 重写窗口关闭事件
    /// \param event
    ///
    void closeEvent(QCloseEvent *event)Q_DECL_OVERRIDE;

    ///------------------------------------------------------------------------------------------------------------MainUI
    /// \brief InitializeSystemSet 初始化系统设定
    ///
    void InitializeSystemSet();

    ///------------------------------------------------------------------------------------------------------------MainUI
    /// \brief InitializeChannelSet 初始化通道设定,设置通道别名
    ///
    void InitializeChannelSet();

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
    /// \param pGetimagesInterface 相机类
    /// \param num 通道号
    ///
    void getImagePlugin(GetImagesInterface* pGetimagesInterface,int num);

    ///
    /// \brief underlyingGetimagesPlugin 处理底层抓拍插件
    /// \param pUnderlyingGetimagesInterface  底层插件类
    /// \param num
    ///
    void captureUnderlyingPlugin(ICaptureUnderlying* pUnderlyingCapture,int num);

    ///------------------------------------------------------------------------------------------------------------MainUI
    /// \brief infraredLogicPlugin 处理串口插件
    /// \param pInfraredlogicInterface 串口类
    /// \param num 通道号
    ///
    void infraredLogicPlugin(InfraredlogicInterface* pInfraredlogicInterface,int num);

    ///
    /// \brief dataBaseInsertPlugin 数据库插入插件
    /// \param pDataBaseInsertInterface 插入接口类
    /// \param num 通道号
    ///
    void dataBaseInsertPlugin(DataBaseInsertInterface* pDataBaseInsertInterface,int num);

    ///
    /// \brief dataBaseReadPlugin 数据库读取插件
    /// \param pDataBaseReadInterface  接口类
    ///
    void dataBaseReadPlugin(DataBaseReadInterface* pDataBaseReadInterface);

    ///
    /// \brief recognizerPlugin 识别器插件
    /// \param pRecognizerInterface 接口类
    ///
    void recognizerPlugin(RecognizerInterface* pRecognizerInterface,int num);

    ///
    /// \brief resultsAnalysisPlugin 识别结果分析插件
    /// \param pResultsAnalysisInterface 分析结果口
    /// \param num 通道号
    ///
    void resultsAnalysisPlugin(ResultsAnalysisInterface* pResultsAnalysisInterface,int num);

    ///
    /// \brief socketServerPlugin TCP插件
    /// \param pSocketServerInterface
    /// \param num
    ///
    void socketServerPlugin(SocketServerInterface* pSocketServerInterface,int  num);

    ///
    /// \brief encryptionInterPlugin 加密工具类
    /// \param pEncryptionInterface
    ///
    void encryptionInterPlugin(EncryptionInterface* pEncryptionInterface);
    ///------------------------------------------------------------------------------------------------------------MainUI
    /// \brief hideWindows 隐藏所有窗口
    ///
    void hideWindows();

    ///------------------------------------------------------------------------------------------------------------MainUI
    /// \brief setStatusBar 设置状态栏
    ///
    void setStatusBar();

    ///
    /// \brief publicConnect 链接公共部分信号和槽
    ///
    void publicConnect();

private slots:

    ///------------------------------------------------------------------------------------------------------------MainUI
    /// \brief message 日志信息
    /// \param type 信息类型
    /// \param msg 信息体
    ///
    void messageSlot(const QString &type, const QString &msg);

    ///------------------------------------------------------------------------------------------------------------MainUI
    /// \brief resizeEvent 重写窗口改变大小事件
    /// \param size 窗口尺寸
    ///
    void resizeEvent(QResizeEvent *size)override;

    ///------------------------------------------------------------------------------------------------------------MainUI
    /// \brief on_Navigation_itemActivated 导航栏选取事件
    /// \param item 选取项
    /// \param column 列
    ///
    void on_Navigation_itemActivated(QTreeWidgetItem *item);

    ///
    /// \brief putCommantStateSlot 抓拍信息写入日志
    /// \param msg 信息体
    ///
    void putCommantStateSlot(const int &channel, const QString& msg);

    ///
    /// \brief resultsAnalysisStateSlot 识别结果写入日志
    /// \param msg 信息体
    ///
    void resultsAnalysisStateSlot(const int& channel, const QString& msg);

    ///
    /// \brief avtionMapTiggered 菜单栏按钮响应
    ///
    void avtionMapTiggered();

signals:

    ///
    /// \brief releaseResourcesSignal 释放动态库资源
    ///
    void releaseResourcesSignal();

    ///
    /// \brief exitWhileSignal 退出循环线程,系统资源使用状态,和串口逻辑循环.
    /// \param status 标志位
    ///
    void exitWhileSignal(bool status);

    ///
    /// \brief messageSignal 日志信息
    /// \param type 日志类型
    /// \param msg 信息体
    ///
    void messageSignal(const QString &type,const QString &msg);

};

#endif // MAINWIDGET_H
