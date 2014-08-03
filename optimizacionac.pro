#-------------------------------------------------
#
# Project created by QtCreator 2014-07-29T09:56:55
#
#-------------------------------------------------

QT       += core gui

#CONFIG += qwt

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets #printsupport

TARGET = optimizacionac
TEMPLATE = app

QMAKE_CXXFLAGS += -std=c++11


#INCLUDEPATH += /usr/include/qwt

#LIBS += -lqwt

SOURCES += main.cpp\
        mainwindow.cpp \
    individual.cpp \
    situationalknowledge.cpp \
    normativeknowledge.cpp \
    normativeknowledgevariable.cpp \
    populationvariation.cpp \
    populationselection.cpp

HEADERS  += mainwindow.h \
    individual.h \
    situationalknowledge.h \
    normativeknowledge.h \
    normativeknowledgevariable.h \
    populationvariation.h \
    populationselection.h

FORMS    += mainwindow.ui
