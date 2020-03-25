#ifndef DATABASEINSERT_GLOBAL_H
#define DATABASEINSERT_GLOBAL_H

#include <QtCore/qglobal.h>
#include <QSqlTableModel>
#include <QSqlRecord>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QMutexLocker>
#include <QMutex>
#include <QMap>
#include <QDir>
#include <QCoreApplication>

#if defined(DATABASEINSERT_LIBRARY)
#  define DATABASEINSERTSHARED_EXPORT Q_DECL_EXPORT
#else
#  define DATABASEINSERTSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // DATABASEINSERT_GLOBAL_H
