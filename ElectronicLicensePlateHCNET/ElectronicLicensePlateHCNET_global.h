#ifndef ELECTRONICLICENSEPLATEHCNET_GLOBAL_H
#define ELECTRONICLICENSEPLATEHCNET_GLOBAL_H

#include <QtCore/qglobal.h>
#include <QCoreApplication>
#include <QLibrary>
#include <QSysInfo>
#include <QDir>
#include <QTimer>
#include <QDebug>
#include <QPixmap>
#include <QCoreApplication>
#include <QThread>
#include <QDateTime>
#include <QMutexLocker>
#include <QMutex>

#if defined(ELECTRONICLICENSEPLATEHCNET_LIBRARY)
#  define ELECTRONICLICENSEPLATEHCNET_EXPORT Q_DECL_EXPORT
#else
#  define ELECTRONICLICENSEPLATEHCNET_EXPORT Q_DECL_IMPORT
#endif

#endif // ELECTRONICLICENSEPLATEHCNET_GLOBAL_H
