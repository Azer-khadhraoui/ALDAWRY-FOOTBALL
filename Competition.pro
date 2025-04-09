#-------------------------------------------------
#
# Project created by QtCreator 2018-10-26T21:45:23
#
#-------------------------------------------------

QT       += core gui sql
QT += sql
QT += core gui widgets
QT += widgets
QT += charts
QT       += core gui charts
QT += network
QT += core gui sql network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = competition
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
    addcompetitionwindow.cpp \
    competition.cpp \
    deletewindow.cpp \
        main.cpp \
        mainwindow.cpp \
    connection.cpp \
    statistics.cpp \
    statistics2.cpp \
    updateform.cpp

HEADERS += \
    addcompetitionwindow.h \
    competition.h \
    deletewindow.h \
        mainwindow.h \
    connection.h \
    statistics.h \
    statistics2.h \
    updateform.h

FORMS += \
	addcompetitionwindow.ui \
	deletewindow.ui \
	mainwindow.ui \
	statistics.ui \
	statistics2.ui \
	updateform.ui
RESOURCES += \
	resources.qrc

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
