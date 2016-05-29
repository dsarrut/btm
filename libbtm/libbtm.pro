#-------------------------------------------------
#
# Project created by QtCreator 2016-05-03T19:27:29
#
#-------------------------------------------------

QT       += core

TARGET = libbtm
TEMPLATE = lib
#CONFIG += staticlib

SOURCES += \
    btmDD.cpp \
    btmMatch.cpp \
    btmPlayer.cpp \
    btmRound.cpp \
    btmTournament.cpp \
    btmUtils.cpp \
    btmSet.cpp

HEADERS += \
    btmDD.h \
    btmMatch.h \
    btmPlayer.h \
    btmRound.h \
    btmTournament.h \
    btmUtils.h \
    btmSet.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
