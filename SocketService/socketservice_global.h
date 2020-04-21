#ifndef SOCKETSERVICE_GLOBAL_H
#define SOCKETSERVICE_GLOBAL_H

#include <QtCore/qglobal.h>
#include <QTcpServer>
#include <QTcpSocket>
#include <QTimer>
#include <QDebug>

#if defined(SOCKETSERVICE_LIBRARY)
#  define SOCKETSERVICESHARED_EXPORT Q_DECL_EXPORT
#else
#  define SOCKETSERVICESHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // SOCKETSERVICE_GLOBAL_H
