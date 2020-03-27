#-------------------------------------------------
#
# Project created by QtCreator 2019-12-22T17:35:53
#
#-------------------------------------------------

QT       += core gui
QT       += widgets
QT       +=sql

greaterThan(QT_MAJOR_VERSION, 4):

TARGET = Container
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
        mainwidget.cpp \
    picturewidget.cpp \
    datawidget.cpp \
    systemsettingwidget.cpp \
    servicewidget.cpp \
    databasewidget.cpp \
    channelsettingwidget.cpp \
    imagewidget.cpp \
    imageprocessing.cpp \
    databaseprocessing.cpp \
    infraredprocessing.cpp

HEADERS += \
        mainwidget.h\
    picturewidget.h \
    datawidget.h \
    systemsettingwidget.h \
    servicewidget.h \
    databasewidget.h \
    channelsettingwidget.h \
    imagewidget.h \
    imageprocessing.h \
    databaseprocessing.h \
    infraredprocessing.h \
    getimagesinterface.h \
    databaselogicinterface.h \
    infraredlogicinterface.h \
    databasereadinterface.h\
    databaseinsertinterface.h \
    defineobj.h \
    recognizerinterface.h

FORMS += \
        mainwidget.ui \
    picturewidget.ui \
    datawidget.ui \
    systemsettingwidget.ui \
    servicewidget.ui \
    databasewidget.ui \
    channelsettingwidget.ui \
    imagewidget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

MOC_DIR=tmp/moc
RCC_DIR=tmp/rcc
UI_DIR=tmp/ui
OBJECTS_DIR=tmp/obj

#QMAKE_LFLAGS+="-Wl,-rpath=./plugins/,-rpath=./plugins/HCNetSDK"

RESOURCES += \
    ico.qrc

#DISTFILES += \
#    libAudioRender.so \
#    libSuperRender.so \
#    libPlayCtrl.so
