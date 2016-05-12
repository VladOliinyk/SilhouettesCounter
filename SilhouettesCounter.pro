#-------------------------------------------------
#
# Project created by QtCreator 2016-04-18T18:28:09
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SilhouettesCounter
TEMPLATE = app


SOURCES += main.cpp\
        window.cpp

HEADERS  += window.h \
    logic.h

FORMS    += window.ui

QMAKE_LFLAGS_RELEASE += -static -static-libgcc
