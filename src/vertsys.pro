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
    model.cpp

HEADERS  += mainwindow.h \
    registeruser.h \
    dbmanager.h \
    model.h

FORMS    += mainwindow.ui \
    registeruser.ui

RESOURCES += \
    icons.qrc
