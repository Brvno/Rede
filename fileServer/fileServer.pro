TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    server.cpp \
    client.cpp

HEADERS += \
    communication.h \
    protocol.h \
    server.h \
    client.h

