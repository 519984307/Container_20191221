#-------------------------------------------------
#
# Project created by QtCreator 2019-12-22T17:35:53
#
#-------------------------------------------------

QT       += core gui
QT       += widgets
QT       +=sql
QT       +=network
QT       +=serialport

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
    imageprocessing.cpp \
    databaseprocessing.cpp \
    infraredprocessing.cpp \
    recognizerprocessing.cpp \
    resultsanalysisprocessing.cpp \
    socketserverprocessing.cpp \
    encryptionprocessing.cpp \
    logwidget.cpp \
    underlyinggetimagesprocessing.cpp \
    PROCESSING/uploaddataprocessing.cpp \
    PROCESSING/electroniclicenseplateprocessing.cpp

HEADERS += \
        mainwidget.h\
    middlewareinterface.h \
    picturewidget.h \
    datawidget.h \
    systemsettingwidget.h \
    servicewidget.h \
    databasewidget.h \
    channelsettingwidget.h \
    imageprocessing.h \
    databaseprocessing.h \
    infraredprocessing.h \
    databaselogicinterface.h \
    infraredlogicinterface.h \
    databasereadinterface.h\
    databaseinsertinterface.h \
    defineobj.h \
    recognizerinterface.h \
    recognizerprocessing.h \
    settingvalues.h \
    resultsanalysisinterface.h \
    resultsanalysisprocessing.h \
    socketserverinterface.h \
    socketserverprocessing.h \
    encryptionprocessing.h \
    encryptioninterface.h \
    logwidget.h \
    underlyinggetimagesprocessing.h \
    ICaptureUnderlying.h \
    getimagesinterface.h \
    INTERFACE/touploaddatainterface.h \
    PROCESSING/uploaddataprocessing.h \
    INTERFACE/licenseplateinterface.h \
    PROCESSING/electroniclicenseplateprocessing.h

FORMS += \
        mainwidget.ui \
    picturewidget.ui \
    datawidget.ui \
    systemsettingwidget.ui \
    servicewidget.ui \
    databasewidget.ui \
    channelsettingwidget.ui \
    logwidget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

MOC_DIR=tmp/moc
RCC_DIR=tmp/rcc
UI_DIR=tmp/ui
OBJECTS_DIR=tmp/obj

RESOURCES += \
    ico.qrc

TRANSLATIONS = zh_hans.ts

DISTFILES += \
    ico.rc

RC_FILE = \
    ico.rc

#QMAKE_LFLAGS+="-Wl,-rpath=./Plugins/,-rpath=./Plugins/smartX"
