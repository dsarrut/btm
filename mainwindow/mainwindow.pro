#-------------------------------------------------
#
# Project created by QtCreator 2016-04-30T17:41:02
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TEMPLATE = app

CONFIG += static
QMAKE_LFLAGS += -static-libgcc -static-libstdc++ -Wl,--enable-auto-image-base -Wl,--add-stdcall-alias -Wl,--enable-auto-import

INCLUDEPATH += ../libbtm
LIBS += -L../libbtm/release/   -L../libbtm/debug/ -llibbtm

SOURCES += main.cpp\
    mainwindow.cpp \
    btmQPlayersTable.cpp \
    btmQTableWidgetItemWithPlayer.cpp \
    btmQPlayerTableRow.cpp \
    btmQWaitingPlayersWidget.cpp \
    btmQPlayerWidget.cpp \
    btmQRemoteDisplayDialog.cpp \
    btmQRoundWidget2.cpp \
    btmQMatchWidget2.cpp

HEADERS  += mainwindow.h \
    btmQPlayersTable.h \
    btmQTableWidgetItemWithPlayer.h \
    btmQPlayerTableRow.h \
    btmQWaitingPlayersWidget.h \
    btmQPlayerWidget.h \
    btmQRemoteDisplayDialog.h \
    btmQRoundWidget2.h \
    btmQMatchWidget2.h
    btm_global.h

FORMS    += mainwindow.ui \
    btmQWaitingPlayersWidget.ui \
    btmQPlayerWidget.ui \
    btmQRemoteDisplay.ui \
    btmQRemoteDisplayDialog.ui \
    btmQRoundWidget2.ui \
    btmQMatchWidget2.ui

RESOURCES += \
    resource.qrc
