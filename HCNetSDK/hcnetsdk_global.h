#ifndef HCNETSDK_GLOBAL_H
#define HCNETSDK_GLOBAL_H

#include <QtCore/qglobal.h>
#include <QCoreApplication>
#include <QLibrary>
#include <QSysInfo>
#include <QObject>
#include<QDir>

#if defined(HCNETSDK_LIBRARY)
#  define HCNETSDKSHARED_EXPORT Q_DECL_EXPORT
#else
#  define HCNETSDKSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // HCNETSDK_GLOBAL_H
