QT += core
QT -= gui
QT +=network
QT += sql
TARGET = untitled1
CONFIG += console
CONFIG -= app_bundle
TEMPLATE = app

SOURCES += main.cpp \
    myserver.cpp \
    mythread.cpp

HEADERS += \
    mythread.h \
    myserver.h

