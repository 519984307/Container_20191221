#ifndef ELECTRONICLICENSEPLATE_GLOBAL_H
#define ELECTRONICLICENSEPLATE_GLOBAL_H

#include <QtCore/qglobal.h>
#include <QLibrary>
#include <QDir>
#include <QDateTime>
#include <QMutexLocker>
#include <QMutex>
#include <QDebug>
#include <QPixmap>
#include <QCoreApplication>
#include <QThread>
#include <QTimer>

#if defined(ELECTRONICLICENSEPLATE_LIBRARY)
#  define ELECTRONICLICENSEPLATESHARED_EXPORT Q_DECL_EXPORT
#else
#  define ELECTRONICLICENSEPLATESHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // ELECTRONICLICENSEPLATE_GLOBAL_H
