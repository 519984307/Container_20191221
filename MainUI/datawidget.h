#ifndef DATAWIDGET_H
#define DATAWIDGET_H

#include <QWidget>

namespace Ui {
class DataWidget;
}

class DataWidget : public QWidget
{
    Q_OBJECT

public:
    explicit DataWidget(QWidget *parent = nullptr);
    ~DataWidget();

private:
    Ui::DataWidget *ui;

public slots://槽

    ///------------------------------------------------------------------------------------------------------------Infraredlogic
    /// \brief logicStatus 红外状态
    /// \param status 状态
    ///
    void logicStatus(int* status);

    ///------------------------------------------------------------------------------------------------------------Infraredlogic
    /// \brief setLogicPutImage 逻辑抓图
    /// \param putCommnd 逻辑
    ///
    void logicPutImage(int putCommnd);

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

signals://信号

    ///------------------------------------------------------------------------------------------------------------GetImgaes
    /// \brief initCamer 初始化相机
    /// \param camerIP 相机地址
    /// \param camerPort 相机端口
    ///
    void initCamer(const QString &camerIP, quint16 camerPort,const QString &CamerUser,const QString &CamerPow);

    ///------------------------------------------------------------------------------------------------------------GetImgaes
    /// \brief putCommand 相机指令
    /// \param command 指令
    /// \return  返回执行状态
    ///
    bool putCommand(const QString &command);

    ///------------------------------------------------------------------------------------------------------------Infraredlogic
    /// \brief startSlave 初始化串口
    /// \param portName1 串口1
    /// \param portName2 串口2
    ///
    void startSlave(const QString &portName1, const QString &portName2);

    ///------------------------------------------------------------------------------------------------------------Infraredlogic
    /// \brief setAlarmModeSlot 设置红外模式
    /// \param mode 模式(敞开|常闭)
    ///
    void setAlarmMode(bool model);

    ///------------------------------------------------------------------------------------------------------------Infraredlogic
    /// \brief exitWhile 退出循环
    /// \param exit 条件
    ///
    void exitWhile(bool exit);

};

#endif // DATAWIDGET_H
