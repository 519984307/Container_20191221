#ifndef DATABASEREADINTERFACE_H
#define DATABASEREADINTERFACE_H

#define ZBY_LOG(type)  tr("ZBY_LOG_%1(Func[%2](Line[%3]))").arg(type).arg(Q_FUNC_INFO).arg(__LINE__)

#include <QObject>
#include <QMap>
#include <QSqlTableModel>

class DataBaseReadInterface : public QObject
{
    Q_OBJECT

public:
    virtual ~DataBaseReadInterface() {}

signals:

    ///
    /// \brief messageSignal 日志信息
    /// \param type 日志类型
    /// \param msg 信息体
    ///
    void messageSignal(const QString &type,const QString &msg);

    ///
    /// \brief returnModelSingal 返回数据模型
    /// \param model 数据模型
    ///
    void returnModelSingal( QSqlTableModel *model);

    ///
    /// \brief statisticalDataSignal
    /// \param total 总计
    /// \param correct 正确
    /// \param error 错误
    /// \param statistical 统计
    ///
    void statisticalDataSignal(int total,double correct,double error,double statistical);

public slots:

    ///
    /// \brief initDataBaseSlot 初始化数据库.如果不存在,就创建.
    /// \param connectName 链接名称
    /// \param user 用户名
    /// \param pass密码
    /// \param ip 地址
    ///
    virtual void initDataBaseSlot(const QString &connectName,const QString &user,const QString &pass,const QString &ip)=0;

    ///
    /// \brief setDataBaseFilterSlot 设置数据库筛选条件
    /// \param filter 筛选条件
    ///
    virtual void setDataBaseFilterSlot(const QString &filter)=0;
};

#define DataBaseReadInterfaceIID "ZBY.ContainerServer.DataBaseReadInterface/1.0"
Q_DECLARE_INTERFACE(DataBaseReadInterface,DataBaseReadInterfaceIID);

#endif // DATABASEREADINTERFACE_H
