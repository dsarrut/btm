#-------------------------------------------------
#
# Project created by QtCreator 2016-04-30T16:48:50
#
#-------------------------------------------------

QT       -= gui

TARGET = btm
TEMPLATE = lib

DEFINES += BTM_LIBRARY

SOURCES += btmRound.cpp

HEADERS += btmRound.h\
        btm_global.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
