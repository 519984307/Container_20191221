#ifndef DATABASELOGIC_GLOBAL_H
#define DATABASELOGIC_GLOBAL_H

#include <QtCore/qglobal.h>
#include <QSqlTableModel>
#include <QSqlRecord>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>

#if defined(DATABASELOGIC_LIBRARY)
#  define DATABASELOGICSHARED_EXPORT Q_DECL_EXPORT
#else
#  define DATABASELOGICSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // DATABASELOGIC_GLOBAL_H
