#ifndef LOGICALPROCESSING_H
#define LOGICALPROCESSING_H

#include <QObject>

class LogicalProcessing : public QObject
{
    Q_OBJECT
public:
    explicit LogicalProcessing(QObject *parent = nullptr);

signals:

    ///------------------------------------------------------------------------------------------------------------Infraredlogic
    /// \brief startSlave 初始化串口
    /// \param portName1 串口1
    /// \param portName2 串口2
    ///
    void startSlaveSignal(const QString &portName1, const QString &portName2);

    ///------------------------------------------------------------------------------------------------------------Infraredlogic
    /// \brief setAlarmModeSlot 设置红外模式
    /// \param mode 模式(敞开|常闭)
    ///
    void setAlarmModeSignal(bool model);

    ///------------------------------------------------------------------------------------------------------------Infraredlogic
    /// \brief exitWhile 退出循环
    /// \param exit 条件
    ///
    void exitWhileSignal(bool exit);

public slots:

    ///------------------------------------------------------------------------------------------------------------Infraredlogic
    /// \brief logicStatus 红外状态
    /// \param status 状态
    ///
    void logicStatusSlot(int* status);

    ///------------------------------------------------------------------------------------------------------------Infraredlogic
    /// \brief setLogicPutImage 逻辑抓图
    /// \param putCommnd 逻辑
    ///
    void logicPutImageSlot(int putCommnd);
};

#endif // LOGICALPROCESSING_H
