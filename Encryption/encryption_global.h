#ifndef ENCRYPTION_GLOBAL_H
#define ENCRYPTION_GLOBAL_H

#include <QtCore/qglobal.h>
#include <QLibrary>
#include <QTimer>
#include <QDebug>

#if defined(ENCRYPTION_LIBRARY)
#  define ENCRYPTIONSHARED_EXPORT Q_DECL_EXPORT
#else
#  define ENCRYPTIONSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // ENCRYPTION_GLOBAL_H
