#ifndef TOUPLOADDATA_GLOBAL_H
#define TOUPLOADDATA_GLOBAL_H

#include <QtCore/qglobal.h>
#include <QFile>
#include <QUrl>
#include <QNetworkRequest>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QDebug>
#include <QRegExp>

#if defined(TOUPLOADDATA_LIBRARY)
#  define TOUPLOADDATASHARED_EXPORT Q_DECL_EXPORT
#else
#  define TOUPLOADDATASHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // TOUPLOADDATA_GLOBAL_H
