#-------------------------------------------------
#
# Project created by QtCreator 2013-11-14T09:36:57
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SimpleASM
TEMPLATE = app

SOURCES += main.cpp\
        startpage.cpp \
    WorkingWindow.cpp \
    Highlighter.cpp \
    InfoDialog.cpp

HEADERS  += startpage.h \
    WorkingWindow.h \
    Highlighter.h \
    InfoDialog.h

FORMS    += startpage.ui \
    WorkingWindow.ui \
    InfoDialog.ui

RESOURCES += \
    icons.qrc

OTHER_FILES +=
