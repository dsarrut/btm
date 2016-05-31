#-------------------------------------------------
#
# Project created by QtCreator 2016-04-30T17:41:02
#
#-------------------------------------------------

TEMPLATE  = subdirs
CONFIG   += ordered
CONFIG += static
#QMAKE_LFLAGS += -static-libgcc -static-libstdc++ -Wl,--enable-auto-image-base -Wl,--add-stdcall-alias -Wl,--enable-auto-import
SUBDIRS = libbtm mainwindow
mainwindow.depends = libbtm


