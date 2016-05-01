#-------------------------------------------------
#
# Project created by QtCreator 2016-04-30T17:41:02
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = btm
TEMPLATE = app

CONFIG += static
QMAKE_LFLAGS += -static-libgcc -static-libstdc++ -Wl,--enable-auto-image-base -Wl,--add-stdcall-alias -Wl,--enable-auto-import

SOURCES += main.cpp\
        mainwindow.cpp \
    btmRound.cpp \
    btmPlayer.cpp \
    btmTournament.cpp \
    btmMatch.cpp \
    btmUtils.cpp \
    btmQPlayersTable.cpp \
    btmQTableWidgetItemWithPlayer.cpp \
    btmQPlayerTableRow.cpp

HEADERS  += mainwindow.h \
    btmRound.h \
    btmPlayer.h \
    btmDD.h \
    btmUtils.h \
    btmTournament.h \
    btmMatch.h \
    btmQPlayersTable.h \
    btmQTableWidgetItemWithPlayer.h \
    btmQPlayerTableRow.h

FORMS    += mainwindow.ui
