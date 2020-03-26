#ifndef INFRAREDPROCESSING_H
#define INFRAREDPROCESSING_H

#include "picturewidget.h"

#include <QObject>
#include <QDateTime>
#include <QMap>

class InfraredProcessing : public QObject
{
    Q_OBJECT

public:
    explicit InfraredProcessing(QObject *parent = nullptr);

    ///
    /// \brief CamerMultiMap 绑定相机到通道,前后左右4台相机.
    /// \param tmpHash
    ///
    void setCamerMultiMap(QList<QObject*> camerList, int channel);

private:

    ///
    /// \brief data  写入数据库数据
    ///
    QMap<QString,QString> data;

    ///
    /// \brief timer 时间戳
    ///
    QString  timer;

    ///
    /// \brief name 图片中间名
    ///
    QString name;

    ///
    /// \brief channel 通道号
    ///
    int  channel;

    ///
    /// \brief pPictureWidgetBEFORE 前相机
    ///
    PictureWidget* pPictureWidgetBEFORE;

    ///
    /// \brief pPictureWidgetAFTER 后相机
    ///
    PictureWidget* pPictureWidgetAFTER;

    ///
    /// \brief pPictureWidgetLEFT 左相机
    ///
    PictureWidget* pPictureWidgetLEFT;

    ///
    /// \brief pPictureWidgetRIGHT 右相机
    ///
    PictureWidget* pPictureWidgetRIGHT;


signals:

    ///
    /// \brief startSlave 初始化串口
    /// \param portName1 串口1
    /// \param portName2 串口2
    ///
    void startSlaveSignal(const QString &portName1, const QString &portName2);

    ///
    /// \brief setAlarmModeSlot 设置红外模式
    /// \param mode 模式(常开|常闭)
    ///
    void setAlarmModeSignal(bool model);

    ///
    /// \brief exitWhile 退出循环
    /// \param exit 条件
    ///
    void exitWhileSignal(bool exit);

    ///
    /// \brief pictureStreamSignal 图片流数据信号
    /// \param jpgStream 图片流
    /// \param command 编号
    ///
     void pictureStreamSignal(const QByteArray &jpgStream,const int &imgNumber);

     ///
     /// \brief insertDataBaseSignal 写入记录到数据库
     /// \param data
     ///
     void insertDataBaseSignal(QMap<QString,QString> data);

public slots:

    ///
    /// \brief logicStatus 红外状态
    /// \param status 状态
    ///
    void logicStatusSlot(int* status);

    ///
    /// \brief setLogicPutImage 红外逻辑抓图
    /// \param putCommnd 逻辑
    ///
    void logicPutImageSlot(const int &putCommnd);

};

#endif // INFRAREDPROCESSING_H