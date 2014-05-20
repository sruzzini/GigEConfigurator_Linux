#-------------------------------------------------
#
# Project created by QtCreator 2014-05-13T10:06:14
#
#-------------------------------------------------

QT       += core gui
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GigEConfigurator
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

unix:!macx: LIBS += -L$$PWD/../../../../usr/lib/ -lflycapture
unix:!macx: INCLUDEPATH += $$PWD/../../../../usr/include/flycapture
unix:!macx: DEPENDPATH += $$PWD/../../../../usr/include/flycapture

win32: INCLUDEPATH += "C:\Program Files\Point Grey Research\FlyCapture2\include"
win32: LIBS += -L"C:\Program Files\Point Grey Research\FlyCapture2\lib64" -lFlyCapture2
