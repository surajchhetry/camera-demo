#-------------------------------------------------
#
# Project created by QtCreator 2013-11-17T13:49:01
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = camera-demo
TEMPLATE = app

QMAKE_CXXFLAGS +=

INCLUDEPATH += ../libv4l2/include

LIBS += -L../libv4l2/lib -lv4l2

SOURCES += main.cpp camerademo.cpp ccvt.cpp utils.cpp

HEADERS  += camerademo.h ccvt.h utils.h

FORMS    += camerademo.ui

