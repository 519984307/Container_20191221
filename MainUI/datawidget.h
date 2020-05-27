#ifndef DATAWIDGET_H
#define DATAWIDGET_H

#include <QWidget>
#include <QMutex>
#include <QMutexLocker>
#include <QResizeEvent>
#include <QHideEvent>
#include <QPainter>
#include <QtDebug>

namespace Ui {
class DataWidget;
}

class DataWidget : public QWidget
{
    Q_OBJECT

public:
    explicit DataWidget(QWidget *parent = nullptr);
    ~DataWidget()Q_DECL_OVERRIDE;

    ///
    /// \brief resizeEvent 重写窗口调整事件
    /// \param size
    ///
    void resizeEvent(QResizeEvent* size)Q_DECL_OVERRIDE;

    ///
    /// \brief hideEvent 重写窗口隐藏事件
    /// \param event
    ///
    void hideEvent(QHideEvent *event)Q_DECL_OVERRIDE;

private:

    Ui::DataWidget *ui;

    QMutex mutex;

public slots:

    ///
    /// \brief logicStatusSlot 红外状态
    /// \param status 状态值
    ///
    void logicStatusSlot(int* status);

    ///
    /// \brief pictureStreamSlot 图片流数据
    /// \param jpgStream 图片流
    /// \param imgNumber 编号
    ///
    void pictureStreamSlot(const QByteArray &jpgStream,const int &imgNumber);

    ///
    /// \brief containerSlot 箱号结果
    /// \param result1 前箱
    /// \param iso1 箱型
    /// \param result2 后箱
    /// \param iso2 箱型
    ///
    void containerSlot(const int& type,const QString &result1, const int &resultCheck1, const QString &iso1, const QString &result2, const int &resultCheck2, const QString &iso2);

    ///
    /// \brief camerIDstatesSlot 相机状态
    /// \param camerIP 相机地址
    /// \param state 相机状态
    ///
    void camerIDstatesSlot(const QString &camerIP,bool state,const QString& alisa);

    ///车牌
    ///
    /// \brief imageFlowSlot 图片流
    /// \param img
    ///
    void imageFlowSlot(QByteArray img);

    ///
    /// \brief theVideoStreamSlot 视频流
    /// \param stream
    ///
    void theVideoStreamSlot(QByteArray arrImg);

    ///
    /// \brief resultsTheLicensePlateSlot 车牌结果
    /// \param plate
    ///
    void resultsTheLicensePlateSlot(const QString &plate,const QString &color,const QString &time,QByteArray arrImg);

    ///
    /// \brief equipmentStateSlot  设备额在线状态
    /// \param state
    ///
    void equipmentStateSlot( bool state);

signals:

    ///
    /// \brief simulateTriggerSignal 模拟抓拍
    /// \param type 逻辑类型
    ///
    void simulateTriggerSignal(int type);

//    ///
//    /// \brief initCameraSlot 初始化相机
//    /// \param localAddr 本机地址(用户绑定网卡)
//    /// \param addr 相机地址
//    /// \param port 端口
//    /// \param imgPath 图片地址
//    /// \param channel 通道号
//    ///
//    void initCameraSignal(const QString &localAddr,const QString &addr, const int &port, const QString &imgPath, int imgFormat,const int &channel);

    ///
    /// \brief simulationCaptureSlot 模拟抓拍
    ///
    void simulationCaptureSignal();

    ///
    /// \brief openTheVideoSlot 打开视频/关闭视频
    /// \param play
    ///
    void openTheVideoSignal(bool play);

private slots:

    ///
    /// \brief on_while_cycle_capture_checkBox_stateChanged 循环模拟抓拍
    /// \param arg1
    ///
    void on_while_cycle_capture_checkBox_stateChanged(int arg1);

    ///
    /// \brief on_Capture_pushButton_clicked 模拟抓图
    ///
    void on_Capture_pushButton_clicked();
    void on_pushButton_clicked();
    void on_pushButton_2_clicked(bool checked);
};

#endif // DATAWIDGET_H
