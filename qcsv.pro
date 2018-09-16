#-------------------------------------------------
#
# Project created by QtCreator 2015-09-16T08:47:40
#
#-------------------------------------------------

QT       += core gui multimedia concurrent printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qcsv
TEMPLATE = app
CONFIG += debug
CONFIG += c++11
QT += concurrent


SOURCES += main.cpp\
        mainwindow.cpp \
    qxtcsvmodel.cpp \
    qxtglobal.cpp \
    configuredialog.cpp \
    about.cpp \
    technicalsupport.cpp \
    simpleqtcryptor.cpp

HEADERS  += mainwindow.h \
    qxtcsvmodel.h \
    qxtglobal.h \
    configuredialog.h \
    technicalsupport.h \
    about.h \
    simpleqtcryptor.h \
    serpent_sbox.h

FORMS    += mainwindow.ui \
    configuredialog.ui \
    about.ui \
    technicalsupport.ui

RESOURCES += \
    pictures.qrc

RC_ICONS = pictures\logo.ico
