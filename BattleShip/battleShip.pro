#-------------------------------------------------
#
# Project created by QtCreator 2014-12-02T20:59:21
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = battleShip
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    campo.cpp

HEADERS  += mainwindow.h \
    communication.h \
    campo.h

FORMS    += mainwindow.ui
