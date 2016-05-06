#-------------------------------------------------
#
# Project created by QtCreator 2016-04-30T17:41:02
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TEMPLATE = app

CONFIG += static
#QMAKE_LFLAGS += -static-libgcc -static-libstdc++ -Wl,--enable-auto-image-base -Wl,--add-stdcall-alias -Wl,--enable-auto-import

INCLUDEPATH += ../libbtm
LIBS += -L../libbtm/release/ -llibbtm


SOURCES += main.cpp\
    mainwindow.cpp \
    btmQPlayersTable.cpp \
    btmQTableWidgetItemWithPlayer.cpp \
    btmQPlayerTableRow.cpp \
    btmQMatchWidget.cpp \
    btmQRoundWidget.cpp \
    btmQWaitingPlayersWidget.cpp

HEADERS  += mainwindow.h \
    btmQPlayersTable.h \
    btmQTableWidgetItemWithPlayer.h \
    btmQPlayerTableRow.h \
    btmQMatchWidget.h \
    btmQRoundWidget.h \
    btmQWaitingPlayersWidget.h
    btm_global.h

FORMS    += mainwindow.ui \
    btmQMatchWidget.ui \
    btmQRoundWidget.ui \
    btmQWaitingPlayersWidget.ui

RESOURCES += \
    resource.qrc
