#include "mainwidget.h"
#include "systemsettingwidget.h"

#include <QApplication>
#include <QTranslator>
#include <QCoreApplication>
#include <QDir>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication::addLibraryPath(QDir::toNativeSeparators("./Plugins"));
    QApplication::addLibraryPath(QDir::toNativeSeparators("./qm"));
    QApplication a(argc, argv);

    QTranslator *translator = new QTranslator(&a);
    translator->load("zh_hans.qm", QDir::toNativeSeparators("./qm"));
    SystemSettingWidget  SystemSettingWidget;
    if(SystemSettingWidget.pSettingValues->Language==1){
        a.installTranslator(translator);
    }

    MainWidget w;
    w.show();

    return a.exec();
}
