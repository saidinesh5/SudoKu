#-------------------------------------------------
#
# Project created by QtCreator 2013-01-04T08:35:06
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SudoKu
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    sudokumodel.cpp \
    sudokudelegate.cpp

HEADERS  += mainwindow.h \
    sudokumodel.h \
    sudokudelegate.h

FORMS    += mainwindow.ui
