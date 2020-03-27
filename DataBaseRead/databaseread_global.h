#ifndef DATABASEREAD_GLOBAL_H
#define DATABASEREAD_GLOBAL_H

#include <QtCore/qglobal.h>
#include <QSqlTableModel>
#include <QSqlDatabase>
#include <QSqlError>
#include <QReadWriteLock>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QDir>
#include <QCoreApplication>

#if defined(DATABASEREAD_LIBRARY)
#  define DATABASEREADSHARED_EXPORT Q_DECL_EXPORT
#else
#  define DATABASEREADSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // DATABASEREAD_GLOBAL_H
