#ifndef GETIMAGES_GLOBAL_H
#define GETIMAGES_GLOBAL_H

#include  <QtCore/qglobal.h>

#include  <QThread>
#include  <QTimer>
#include  <QtNetwork/QSctpSocket>

#if defined(GETIMAGE_LIBRARY)
#  define GETIMAGESSHARED_EXPORT Q_DECL_EXPORT
#else
#  define GETIMAGESSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // GETIMAGES_GLOBAL_H
