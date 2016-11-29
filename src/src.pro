#-------------------------------------------------
#
# Project created by QtCreator 2016-11-20T15:59:49
#
#-------------------------------------------------

QT       -= gui

TARGET = CMakeClient
TEMPLATE = lib
CONFIG += staticlib

SOURCES += \
    cmakeclient.cpp \
    request.cpp \
    reply.cpp

HEADERS += \
    cmakeclient.h \
    request.h \
    reply.h
unix {
    target.path = /usr/lib
    INSTALLS += target
}
