#ifndef RECOGNITION_H
#define RECOGNITION_H

#define ZBY_LOG(type)  tr("[%1][%2][%3]").arg(type).arg(Q_FUNC_INFO).arg(__LINE__)

#include <QObject>
#include <QRunnable>
#include <QProcess>
#include <QCoreApplication>
#include <QDir>
#include <QDebug>

class Recognition : public QObject,public QRunnable
{
    Q_OBJECT

public:
    explicit Recognition(QObject *parent = nullptr,const QString &image="",int imgNumber=-1);

private:
    QString image;
    int imgNumber;

private:

    ///
    /// \brief run 识别线程
    ///
    void run()Q_DECL_OVERRIDE;

signals:

    ///
    /// \brief recognitionResult 识别结果
    /// \param result 识别结果
    /// \param imgNumber 图片编号
    ///
    void recognitionResultSignal(const QString &result,int imgNumber);

    ///
    /// \brief messageSignal 日志信息
    /// \param type 日志类型
    /// \param msg 信息体
    ///
    void messageSignal(const QString &type,const QString &msg);

};

#endif // RECOGNITION_H
