TEMPLATE = app
CONFIG += console
CONFIG -= qt

SOURCES += main.cpp \
    goBackN.cpp \
    repetSeletiva.cpp
LIBS += -pthread
HEADERS += \
    communication.h

