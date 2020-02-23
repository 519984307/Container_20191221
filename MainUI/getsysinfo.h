#ifndef GETSYSINFO_H
#define GETSYSINFO_H

#include <QObject>
#include <QThread>
#include <QProcess>
#include <QCoreApplication>

class GetSysInfo : public QThread
{
    Q_OBJECT

public:
    GetSysInfo();

private:

    ///
    /// \brief status 退出线程信号
    ///
    bool status;

private:
    ///
    /// \brief run 重写线程函数
    ///
    void run();

public slots:

    ///
    /// \brief exitWhile 退出线程
    /// \param status 标志位
    ///
    void exitWhileSlot(bool status);

signals:

    ///
    /// \brief statusMsg 系统状态
    /// \param msg 信息体
    ///
    void statusMsgSignal(const QString &msg);
};

#endif // GETSYSINFO_H
