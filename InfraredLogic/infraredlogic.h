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

private://变量

    int status[6];   //红外信号状态
    int tmpStatus[6];//临时红外信号

     //箱型逻辑条件
     bool _45G1;
     bool _22G1;
     bool _22G1_22G1;

     bool exit;//退出循环状态
     bool model;//红外模式(常开|常闭)

private://函数

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
     /// \param model 红外模式
     ///
      void serialLogic(int *status);

     ///
     /// \brief startSlave 设置参数,启动串口
     /// \param portName1 串口1
     /// \param portName2 串口2
     ///
     void startSlave(const QString &portName1, const QString &portName2) Q_DECL_OVERRIDE;

     ///
     /// \brief setAlarmModeSlot 设置红外模式
     /// \param mode 模式(敞开|常闭)
     ///
     void setAlarmMode(bool model)Q_DECL_OVERRIDE;

     ///
     /// \brief exitWhile 退出循环
     /// \param exit 条件
     ///
     virtual void exitWhile(bool exit)Q_DECL_OVERRIDE;
};

#endif // INFRAREDLOGIC_H
