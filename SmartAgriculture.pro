QT       += core gui
QT       += sql
QT       += concurrent
QT       += charts
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    adminwindow.cpp \
    changeinfowindow.cpp \
    databasemanager.cpp \
    expertadviceform.cpp \
    expertwindow.cpp \
    farmerwindow.cpp \
    main.cpp \
    mainwindow.cpp \
    registerwindow.cpp \
    systemadviceform.cpp \
    systemwindow.cpp \
    gauge_widget.cpp \
    fertilizerprediction.cpp

HEADERS += \
    adminwindow.h \
    changeinfowindow.h \
    databasemanager.h \
    expertadviceform.h \
    expertwindow.h \
    farmerwindow.h \
    gauge_widget.h \
    mainwindow.h \
    registerwindow.h \
    systemadviceform.h \
    systemwindow.h

FORMS += \
    adminwindow.ui \
    changeinfowindow.ui \
    expertadviceform.ui \
    expertwindow.ui \
    farmerwindow.ui \
    mainwindow.ui \
    registerwindow.ui \
    systemadviceform.ui \
    systemwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    icon.qrc

RC_FILE = appicon.rc
