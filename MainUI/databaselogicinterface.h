#ifndef DATABASELOGICINTERFACE_H
#define DATABASELOGICINTERFACE_H

#define ZBY_LOG(type)  tr("ZBY_LOG_%1(Func[%2](Line[%3]))").arg(type).arg(Q_FUNC_INFO).arg(__LINE__)

#include <QObject>
#include <QMap>
#include <QtSql/QSqlDatabase>

class DataBaseLogicInterface : public QObject
{
    Q_OBJECT
public:
    virtual ~DataBaseLogicInterface() {}

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
    /// \param user 用户名
    /// \param pass密码
    /// \param ip 地址
    ///
    virtual void initDataBaseSlot(const QString &user,const QString &pass,const QString &ip)=0;

    ///
    /// \brief insertDataBaseSlot 插入数据库
    /// \param data 数据字典
    ///
    virtual void insertDataBaseSlot(QMap<QString, QString> data)=0;

    ///
    /// \brief readDataBaseSlot 读取数据库
    /// \return 数据库操作对象
    ///
    virtual QSqlDatabase readDataBaseSlot()=0;

    ///
    /// \brief updateDataBaseSlot 更新数据
    /// \param data 数据字典
    ///
    virtual void updateDataBaseSlot(QMap<QString, QString> data)=0;
};

#define DataBaseLogicInterfaceIID "ZBY.ContainerServer.DataBaseLogicInterface/1.0"
Q_DECLARE_INTERFACE(DataBaseLogicInterface,DataBaseLogicInterfaceIID);

#endif // DATABASELOGICINTERFACE_H
