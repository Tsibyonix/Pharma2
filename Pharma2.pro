#-------------------------------------------------
#
# Project created by QtCreator 2015-12-18T20:51:57
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Pharma2
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    checkforupdate.cpp \
    loaddatabase.cpp \
    runquerydialog.cpp

HEADERS  += mainwindow.h \
    checkforupdate.h \
    loaddatabase.h \
    runquerydialog.h


FORMS    += mainwindow.ui \
    runquerydialog.ui

VERSION += 2.0
