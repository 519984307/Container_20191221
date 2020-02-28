#ifndef INFRAREDLOGIC_INTERFACE_H
#define INFRAREDLOGIC_INTERFACE_H

#include <QObject>

class InfraredlogicInterface:public QObject
{
    Q_OBJECT

public:
    virtual ~InfraredlogicInterface(){}

signals:

    ///
    /// \brief message 日志
    /// \param msg 信息体
    ///
     void messageSignal(const QString &msg);

     ///
     /// \brief logicStatus 红外信号状态
     /// \param status 状态码
     ///
     void logicStatusSignal(int* status);

     ///
     /// \brief setLogicPutImage 逻辑抓图
     /// \param putCommnd 逻辑
     ///
     void logicPutImageSignal(const int &putCommnd);

public slots://槽

   ///
   /// \brief startSlave 初始化串口
   /// \param portName1 串口1
   /// \param portName2 串口2
   ///
   virtual void startSlaveSlot(const QString &portName1, const QString &portName2)=0;

   ///
   /// \brief setAlarmModeSlot 设置红外模式
   /// \param mode 模式(敞开|常闭)
   ///
   virtual void setAlarmModeSlot(bool model)=0;

     ///
     /// \brief exitWhile 退出循环
     /// \param exit
     ///
   virtual void exitWhileSlot(bool exit)=0;
};

#define InfraredlogicInterfaceIID "ZBY.ContainerServer.InfraredlogicInterface/1.0"
Q_DECLARE_INTERFACE(InfraredlogicInterface,InfraredlogicInterfaceIID);

#endif // INFRAREDLOGIC_INTERFACE_H
