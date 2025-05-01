#-------------------------------------------------
#
# Project created by QtCreator 2018-10-26T21:45:23
#
#-------------------------------------------------

QT       += core gui sql
Qt += sql
QT += printsupport
QT += charts
QT += core gui sql printsupport charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = userQ
TEMPLATE = app

LIBS += -lbcrypt

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

QT += network

SOURCES += \
    adduser.cpp \
    admin.cpp \
    createteamwindow.cpp \
    displayteamwindow.cpp \
    displayuser.cpp \
    emailsent.cpp \
    employeview.cpp \
        main.cpp \
        mainwindow.cpp \
    connection.cpp \
    modifyuser.cpp \
    newpassword.cpp \
    profile.cpp \
    recoverpassword.cpp \
    stats.cpp \
    team.cpp \
    user.cpp \
    sessionmanager.cpp

HEADERS += \
    adduser.h \
    admin.h \
    createteamwindow.h \
    displayteamwindow.h \
    displayuser.h \
    emailsent.h \
    employeview.h \
    mainwindow.h \
    connection.h \
    modifyuser.h \
    newpassword.h \
    profile.h \
    recoverpassword.h \
    stats.h \
    team.h \
    user.h \
    sessionmanager.h

FORMS += \
    EmailSent.ui \
    NewPassword.ui \
    adminview.ui \
    create_team.ui \
    displayUser.ui \
    display_team.ui \
    employeview.ui \
    main.ui \
    mainwindow.ui \
    modifyUser.ui \
    profile.ui \
    recoverpassword.ui  \
    adduser.ui \

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    images.qrc

