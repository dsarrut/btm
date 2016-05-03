#-------------------------------------------------
#
# Project created by QtCreator 2016-05-03T19:27:29
#
#-------------------------------------------------

QT       -= core gui

TARGET = libbtm
TEMPLATE = lib
CONFIG += staticlib

SOURCES += libbtm.cpp \
    btmDD.cpp \
    btmMatch.cpp \
    btmPlayer.cpp \
    btmRound.cpp \
    btmTournament.cpp \
    btmUtils.cpp

HEADERS += libbtm.h \
    btmDD.h \
    btmMatch.h \
    btmPlayer.h \
    btmRound.h \
    btmTournament.h \
    btmUtils.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
