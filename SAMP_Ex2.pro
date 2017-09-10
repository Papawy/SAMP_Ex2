#-------------------------------------------------
#
# Project created by QtCreator 2017-04-13T17:56:21
#
#-------------------------------------------------

QT += core gui
QT += network
QT += xml
QT += widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SAMP_Ex2
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

DEFINES += UNICODE

win32:LIBS += -lKernel32
win32:LIBS += -lAdvapi32

SOURCES += src/main.cpp \
        src/mainwindow.cpp \
    src/gtautils.cpp \
    src/cconfigfile.cpp \
    src/cserverlist.cpp \
    src/cserver.cpp

HEADERS  += headers/mainwindow.h \
    headers/gtautils.hpp \
    headers/cserverlist.hpp \
    headers/cserver.hpp \
    headers/cconfigfile.h

FORMS    += ui/mainwindow.ui

RESOURCES += \
    rsc/iconsrsc.qrc
