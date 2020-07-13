#include "mainwidget.h"
#include "systemsettingwidget.h"

#include <QApplication>
#include <QTranslator>
#include <QCoreApplication>
#include <QDir>
#include <QTextCodec>
#include <QDebug>
#include <QMessageBox>

#include <QLocalSocket>
#include <QLocalServer>

int main(int argc, char *argv[])
{
    QTextCodec *codec = QTextCodec::codecForName("gbk");
    QTextCodec::setCodecForLocale(codec);

    QApplication::addLibraryPath(QDir::toNativeSeparators("./Plugins"));
    QApplication::addLibraryPath(QDir::toNativeSeparators("./translations"));

    QApplication a(argc, argv);

    //连接LocalServer
    QString serverName = "localserver";
    QLocalSocket socket;
    socket.connectToServer(serverName);
    if(socket.waitForConnected(1000)){
        QMessageBox::critical(nullptr,"Container","Startup error, the program is already running.");
        return(-1);
    }

    //创建LocalServer
    QLocalServer server;
    if (server.listen(serverName)){
        if(server.serverError()== QAbstractSocket::AddressInUseError &&
                QFile::exists(server.serverName())){
            QFile::remove(server.serverName());
            server.listen(serverName);
        }
    }

    QTranslator *translator = new QTranslator(&a);
    translator->load("zh_hans.qm", QDir::toNativeSeparators("./translations"));
    SystemSettingWidget  SystemSettingWidget;
    if(SystemSettingWidget.pSettingValues->Language==1){
        a.installTranslator(translator);
    }

    MainWidget w;
    w.show();

    return a.exec();
}

