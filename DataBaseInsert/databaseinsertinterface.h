#ifndef DATABASELOGICINTERFACE_H
#define DATABASELOGICINTERFACE_H

#define ZBY_LOG(type)  tr("[%1][%2][%3]").arg(type).arg(Q_FUNC_INFO).arg(__LINE__)

#include <QObject>
#include <QMap>
#include <QSqlTableModel>

class DataBaseInsertInterface : public QObject
{
    Q_OBJECT

public:
    virtual ~DataBaseInsertInterface() {}

signals:

    ///
    /// \brief messageSignal 日志信息
    /// \param type 日志类型
    /// \param msg 信息体
    ///
    void messageSignal(const QString &type,const QString &msg);

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
    /// \brief insertDataBaseSlot 插入数据库
    /// \param data 数据字典
    ///
    virtual void insertDataBaseSlot(QMap<QString, QString> data)=0;

    ///
    /// \brief updateDataBaseSlot 更新数据
    /// \param data 数据字典
    ///
    virtual void updateDataBaseSlot(QMap<QString, QString> data)=0;
};

#define DataBaseInsertInterfaceIID "ZBY.ContainerServer.DataBaseInsertInterface/1.0"
Q_DECLARE_INTERFACE(DataBaseInsertInterface,DataBaseInsertInterfaceIID);

#endif // DATABASELOGICINTERFACE_H
