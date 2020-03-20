#ifndef INFRAREDLOGIC_GLOBAL_H
#define INFRAREDLOGIC_GLOBAL_H

#include <QtCore/qglobal.h>
#include <QTimer>
#include <QThread>
#include <QtSerialPort/QSerialPort>
#include <QCoreApplication>

#if defined(INFRAREDLOGIC_LIBRARY)
#  define INFRAREDLOGICSHARED_EXPORT Q_DECL_EXPORT
#else
#  define INFRAREDLOGICSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // INFRAREDLOGIC_GLOBAL_H
