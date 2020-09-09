#ifndef TOUPLOADDATAINTERFACE_H
#define TOUPLOADDATAINTERFACE_H

#define ZBY_LOG(type)  tr("[%1][%2][%3]").arg(type).arg(Q_FUNC_INFO).arg(__LINE__)

#include <QObject>

class ToUploadDataInterface : public QObject
{
    Q_OBJECT
public:
    ~ ToUploadDataInterface(){}

signals:

    ///
    /// \brief theProgressOf 上传进度
    /// \param ind 进度值
    ///
    void theProgressOf(int ind);

    ///
    /// \brief messageSignal 日志信息
    /// \param type 日志类型
    /// \param msg 信息体
    ///
    void messageSignal(const QString &type,const QString &msg);

public slots:

    ///
    /// \brief InitializationParameterSlot 初始化参数
    /// \param host 地址
    /// \param port 端口
    /// \param path 路径
    /// \param user 用户名
    /// \param pass 密码
    ///
    virtual void InitializationParameterSlot(const QString &user,const QString &pass,const QString &path,const QString &host,const int &port=21)=0;

    ///
    /// \brief uploadDataSlot 上传数据
    /// \param data 数据
    ///
   virtual void uploadDataSlot(const QString &data)=0;
};

#define ToUploadDataInterfaceIID "ZBY.ContainerServer.ToUploadDataInterface/1.0"
Q_DECLARE_INTERFACE(ToUploadDataInterface,ToUploadDataInterfaceIID);

#endif // TOUPLOADDATAINTERFACE_H
