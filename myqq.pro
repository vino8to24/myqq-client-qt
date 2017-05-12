#-------------------------------------------------
#
# Project created by QtCreator 2017-05-10T15:49:57
#
#-------------------------------------------------

QT       += core gui
QT  += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = myqq
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    toolbox1.cpp \
    login.cpp

HEADERS  += widget.h \
    toolbox1.h \
    login.h

RESOURCES += \
    myqq.qrc
