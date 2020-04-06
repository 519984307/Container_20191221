#ifndef RESULTSANALYSISINTERFACE_H
#define RESULTSANALYSISINTERFACE_H

#define ZBY_LOG(type)  tr("ZBY_LOG_%1(Func[%2](Line[%3]))").arg(type).arg(Q_FUNC_INFO).arg(__LINE__)
#include <QObject>

class ResultsAnalysisInterface : public QObject
{
    Q_OBJECT

public:
    virtual ~ResultsAnalysisInterface() {}

signals:

    ///
    /// \brief messageSignal 日志信息
    /// \param type 日志类型
    /// \param msg 信息体
    ///
    void messageSignal(const QString &type,const QString &msg);

public slots:

    ///
    /// \brief numberCheck 集装箱号码校验
    /// \param number 集装箱号码
    /// \param correct 是否矫正
    /// \return  校验结果
    ///
    virtual bool numberCheck(QString &number,bool correct=false)=0;
};

#define ResultsAnalysisInterfaceIID "ZBY.ContainerServer.ResultsAnalysisInterface/1.0"
Q_DECLARE_INTERFACE(ResultsAnalysisInterface,ResultsAnalysisInterfaceIID);

#endif // RESULTSANALYSISINTERFACE_H
