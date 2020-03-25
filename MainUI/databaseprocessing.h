#ifndef DATABASEPROCESSING_H
#define DATABASEPROCESSING_H

#include <QObject>
#include <QSqlTableModel>

class DataBaseProcessing : public QObject
{
    Q_OBJECT
public:
    explicit DataBaseProcessing(QObject *parent = nullptr);

signals:

    ///
    /// \brief initDataBaseSignal 初始化数据库
    /// \param connectName 链接名称
    /// \param user 用户名
    /// \param pass 密码
    /// \param ip 地址
    ///
    void initDataBaseSignal(const QString &connectName,const QString &user,const QString &pass,const QString &ip);

    ///
    /// \brief insertDataBaseSignal 插入数据
    /// \param data 数据
    ///
    void insertDataBaseSignal(QMap<QString, QString> data);

    ///
    /// \brief readDataBaseSignal 设置数据库筛选条件
    /// \param filter 筛选条件
    ///
    void setDataBaseFilterSignal(const QString &filter);

    ///
    /// \brief updateDataBaseSignal 更新数据库
    /// \param data 数据
    ///
    void updateDataBaseSignal(QMap<QString, QString> data);
};

#endif // DATABASEPROCESSING_H
