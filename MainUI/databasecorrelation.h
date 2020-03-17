#ifndef DATABASECORRELATION_H
#define DATABASECORRELATION_H

#include <QObject>
#include <QDateTime>
#include <QHash>
#include <QSqlTableModel>
#include <QSqlRecord>
#include <QtSql/QSql>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>
#include <QMutexLocker>

class DataBaseCorrelation:public QObject
{
    Q_OBJECT

public:
    DataBaseCorrelation(QObject *parent = nullptr);
    ~DataBaseCorrelation();

private:

    ///
    /// \brief initDataBase 初始化数据库,如果没有就创建
    ///
    void initDataBase();

signals:

    ///
    /// \brief messageSignal 日志信息
    /// \param msg 信息体
    ///
    void messageSignal(const QString &msg);

public slots:

    ///
    /// \brief insertDataBase 插入数据库
    /// \param data
    ///
    void insertDataBaseSlot(QHash<QString, QString> dataHash);
};

#endif // DATABASECORRELATION_H
