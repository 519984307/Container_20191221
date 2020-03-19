#ifndef DATABASELOGIC_H
#define DATABASELOGIC_H

#include "databaselogic_global.h"
#include "databaselogicinterface.h"

class DATABASELOGICSHARED_EXPORT DataBaseLogic:public DataBaseLogicInterface
{
    Q_OBJECT
    Q_INTERFACES(DataBaseLogicInterface)
    Q_PLUGIN_METADATA(IID DataBaseLogicInterfaceIID)

public:
    DataBaseLogic();
    ~DataBaseLogic()Q_DECL_OVERRIDE;

public:

    ///
    /// \brief initDataBaseSlot 初始化数据库.如果不存在,就创建.
    /// \param user 用户名
    /// \param pass密码
    /// \param ip 地址
    ///
    void initDataBaseSlot(const QString &user,const QString &pass,const QString &ip="127.0.0.1")Q_DECL_OVERRIDE;

    ///
    /// \brief insertDataBaseSlot 写入数据
    /// \param dataHash 数据字典
    ///
    void insertDataBaseSlot(QMap<QString, QString> data)Q_DECL_OVERRIDE;

    ///
    /// \brief readDataBaseSlot 读取数据库
    /// \return 数据库操作对象
    ///
    QSqlDatabase readDataBaseSlot()Q_DECL_OVERRIDE;

    ///
    /// \brief updateDataBaseSlot 更新数据库
    /// \param data 数据字典
    ///
    void updateDataBaseSlot(QMap<QString, QString> data)Q_DECL_OVERRIDE;
};

#endif // DATABASELOGIC_H
