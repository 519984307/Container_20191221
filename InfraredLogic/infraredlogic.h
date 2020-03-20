#ifndef INFRAREDLOGIC_H
#define INFRAREDLOGIC_H

#include "infraredlogic_global.h"
#include "infraredlogicinterface.h"

class INFRAREDLOGICSHARED_EXPORT InfraredLogic:public InfraredlogicInterface
{
    Q_OBJECT
    Q_INTERFACES(InfraredlogicInterface)
    Q_PLUGIN_METADATA(IID InfraredlogicInterfaceIID)

public:
    explicit InfraredLogic(QObject *parent = nullptr);
    ~InfraredLogic() Q_DECL_OVERRIDE;

private:

    ///
    /// \brief status 红外信号状态
    ///
    int status[6];

    ///
    /// \brief tmpStatus 临时红外信号
    ///
    int tmpStatus[6];

    /* 红外信号值 */
    int valueOne,valueTwo;

     /* 箱型逻辑条件 */
     bool _45G1,_22G1,_22G1_22G1;

     ///
     /// \brief type 模拟抓拍类型
     ///
     int type;

     ///
     /// \brief exit 退出循环状态
     ///
     bool exit;

     ///
     /// \brief health 红外健康状态
     ///
     bool health;

     ///
     /// \brief pTimerFront 前循环抓拍定时器
     ///
     QTimer* pTimerFront;

     ///
     /// \brief pTimerAfter 后循环抓拍定时器
     ///
     QTimer* pTimerAfter;

private:

     ///
     /// \brief compareStatus 比较红外状态
     /// \param before 前一次状态
     /// \param after 后一次状态
     /// \return
     ///
     bool compareStatus(int* before,int* after);

     ///
     /// \brief serialLogicStatus 逻辑判断
     /// \param status 状态
     ///
      void serialLogic(int *status);

private slots:

      ///
      /// \brief delayAfterCaptureSlot 延时抓拍后3张图片.
      ///
      void delayAfterCaptureSlot();

      ///
      /// \brief DelayFrontCaptureSlot 延时抓拍前3张图片.
      ///
      void delayFrontCaptureSlot();

public:

     ///
     /// \brief startSlave 设置参数,启动串口
     /// \param portName1 串口1
     /// \param portName2 串口2
     ///
     void startSlaveSlot(const QString &portName1, const QString &portName2) Q_DECL_OVERRIDE;

     ///
     /// \brief simulateTriggerSlot 模拟触发
     /// \param type 逻辑类型
     /// type=1 22G1
     /// type=2 45G1
     /// type=3 Double 22G1_F
     /// type=4 Double 22G1_b
     /// type=5 while
     ///
      void simulateTriggerSlot(int type)Q_DECL_OVERRIDE;

     ///
     /// \brief setAlarmModeSlot 设置红外模式
     /// \param mode 模式(敞开|常闭)
     ///
     void setAlarmModeSlot(bool model)Q_DECL_OVERRIDE;

     ///
     /// \brief exitWhile 退出循环
     /// \param exit 条件
     ///
     void exitWhileSlot(bool EXIT)Q_DECL_OVERRIDE;
};

#endif // INFRAREDLOGIC_H
