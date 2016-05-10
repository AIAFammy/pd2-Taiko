#-------------------------------------------------
#
# Project created by QtCreator 2016-04-13T23:30:36
#
#-------------------------------------------------

QT       += core gui
QT       += multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MyFirstQT
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    newwindow.cpp

HEADERS  += mainwindow.h \
    newwindow.h

FORMS    += mainwindow.ui \
    newwindow.ui

RESOURCES += \
    pics.qrc
