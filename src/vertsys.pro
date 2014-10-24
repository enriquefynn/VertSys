#-------------------------------------------------
#
# Project created by QtCreator 2014-09-27T10:38:26
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = vertsys
TEMPLATE = app


SOURCES += main.cpp \
        mainwindow.cpp \
    registeruser.cpp \
    dbmanager.cpp \
    tabwidget.cpp \
    climber.cpp \
    phonevalidator.cpp \
    emailvalidator.cpp \
    climbermodel.cpp \
    paymentmodel.cpp \
    paymentwindow.cpp \
    payment.cpp

HEADERS  += mainwindow.h \
    registeruser.h \
    dbmanager.h \
    tabwidget.h \
    phonevalidator.h \
    emailvalidator.h \
    climber.h \
    climbermodel.h \
    paymentmodel.h \
    paymentwindow.h \
    payment.h \
    vertsys.h

TRANSLATIONS += vertSys_pt.ts

FORMS    += mainwindow.ui \
    registeruser.ui \
    payment.ui

RESOURCES += \
    icons.qrc\

QMAKE_EXTRA_COMPILERS += lrelease-qt4
lrelease-qt4.input         = TRANSLATIONS
lrelease-qt4.output        = ${QMAKE_FILE_BASE}.qm
lrelease-qt4.commands      = $$[QT_INSTALL_BINS]/lrelease-qt4 ${QMAKE_FILE_IN} -qm ${QMAKE_FILE_BASE}.qm
lrelease-qt4.CONFIG       += no_link target_predeps
