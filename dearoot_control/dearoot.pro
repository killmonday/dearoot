#-------------------------------------------------
#
# Project created by QtCreator 2022-10-01T18:04:01
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = dearoot_control
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    fun.c \
    addconfig.cpp

HEADERS  += mainwindow.h \
    fun.h \
    addconfig.h

FORMS    += mainwindow.ui \
    addconfig.ui

LIBS += -lm

#QMAKE_LFLAGS += -Wl,-rpath=./lib

#CONFIG += static
#QMAKE_LFLAGS += -static
