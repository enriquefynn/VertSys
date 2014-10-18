#-------------------------------------------------
#
# Project created by QtCreator 2014-09-27T10:38:26
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = vertsys
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    registeruser.cpp \
    dbmanager.cpp \
    model.cpp \
    tabwidget.cpp \
    climber.cpp

HEADERS  += mainwindow.h \
    registeruser.h \
    dbmanager.h \
    model.h \
    tabwidget.h \
    climber.h

FORMS    += mainwindow.ui \
    registeruser.ui

RESOURCES += \
    icons.qrc
