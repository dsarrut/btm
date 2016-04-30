#-------------------------------------------------
#
# Project created by QtCreator 2016-04-30T17:41:02
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = btm
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    btmRound.cpp \
    btmPlayer.cpp \
    btmutils.cpp

HEADERS  += mainwindow.h \
    btmRound.h \
    btmPlayer.h \
    btmDD.h \
    btmUtils.h

FORMS    += mainwindow.ui
