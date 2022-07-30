QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Yocotpuce/yapi/yapi.c \
    Yocotpuce/yapi/yfifo.c \
    Yocotpuce/yapi/yhash.c \
    Yocotpuce/yapi/yjni.c \
    Yocotpuce/yapi/yjson.c \
    Yocotpuce/yapi/ykey.c \
    Yocotpuce/yapi/ymemory.c \
    Yocotpuce/yapi/ypkt_lin.c \
    Yocotpuce/yapi/ypkt_osx.c \
    Yocotpuce/yapi/ypkt_win.c \
    Yocotpuce/yapi/yprog.c \
    Yocotpuce/yapi/ystream.c \
    Yocotpuce/yapi/ytcp.c \
    Yocotpuce/yapi/ythread.c \
    Yocotpuce/yocto_api.cpp \
    Yocotpuce/yocto_colorled.cpp \
    Yocotpuce/yocto_colorledcluster.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    Yocotpuce/yapi/yapi.h \
    Yocotpuce/yapi/yapiresource.rc \
    Yocotpuce/yapi/yapiresource64.rc \
    Yocotpuce/yapi/ydef.h \
    Yocotpuce/yapi/yfifo.h \
    Yocotpuce/yapi/yhash.h \
    Yocotpuce/yapi/yjni.h \
    Yocotpuce/yapi/yjson.h \
    Yocotpuce/yapi/ykey.h \
    Yocotpuce/yapi/ymemory.h \
    Yocotpuce/yapi/yprog.h \
    Yocotpuce/yapi/yproto.h \
    Yocotpuce/yapi/ytcp.h \
    Yocotpuce/yapi/ythread.h \
    Yocotpuce/yapi/yversion.h \
    Yocotpuce/yocto_api.h \
    Yocotpuce/yocto_colorled.h \
    Yocotpuce/yocto_colorledcluster.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

win32: LIBS += -lws2_32
win32: LIBS += -lSetupApi

DISTFILES += \
    Yocotpuce/yapi/yapi.def
