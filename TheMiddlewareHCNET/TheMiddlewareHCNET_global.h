#ifndef THEMIDDLEWAREHCNET_GLOBAL_H
#define THEMIDDLEWAREHCNET_GLOBAL_H

#include <QtCore/qglobal.h>
#include <QCoreApplication>
#include <QLibrary>
#include <QSysInfo>
#include <QDir>
#include <QTimer>
#include <QDebug>
#include <QCoreApplication>
#include <QThread>
#include <QDateTime>
#include <QMutexLocker>
#include <QMutex>
#include <QImage>
#include <QBuffer>
#include <QScopedPointer>
#include <QtConcurrent>

#if defined(THEMIDDLEWAREHCNET_LIBRARY)
#  define THEMIDDLEWAREHCNET_EXPORT Q_DECL_EXPORT
#else
#  define THEMIDDLEWAREHCNET_EXPORT Q_DECL_IMPORT
#endif

#endif // THEMIDDLEWAREHCNET_GLOBAL_H
