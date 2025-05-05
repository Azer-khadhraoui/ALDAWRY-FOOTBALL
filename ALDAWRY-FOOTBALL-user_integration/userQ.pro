#-------------------------------------------------
#
# Project created by QtCreator 2018-10-26T21:45:23
#
#-------------------------------------------------

QT       += core gui sql
Qt += sql
QT += printsupport
QT += charts multimedia multimediawidgets
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
    teamcpp/chatdialog.cpp \
    teamcpp/modifyteam.cpp \
    teamcpp/tableau.cpp \
    teamcpp/teamwindow.cpp \
    teamcpp/tododialog.cpp \
    usercpp/displayplayers_coach.cpp \
    teamcpp/formadd.cpp \
    teamcpp/team.cpp \
    usercpp/StatsWidget.cpp \
    usercpp/adduser.cpp \
    usercpp/admin.cpp \
    usercpp/coach.cpp \
    usercpp/connection.cpp \
    usercpp/displayuser.cpp \
    usercpp/emailsent.cpp \
    usercpp/employeview.cpp \
    usercpp/main.cpp \
    usercpp/mainwindow.cpp \
    usercpp/modifyuser.cpp \
    usercpp/newpassword.cpp \
    usercpp/profile.cpp \
    usercpp/qrcodegen.cpp \
    usercpp/recoverpassword.cpp \
    usercpp/sessionmanager.cpp \
    usercpp/stats.cpp \
    usercpp/user.cpp

HEADERS += \
    teamheaders/chatdialog.h \
    teamheaders/modifyteam.h \
    teamheaders/tableau.h \
    teamheaders/teamwindow.h \
    teamheaders/tododialog.h \
    userheaders/displayplayers_coach.h \
    teamheaders/formadd.h \
    teamheaders/team.h \
    teamheaders/team.h \
    userheaders/StatsWidget.h \
    userheaders/adduser.h \
    userheaders/admin.h \
    userheaders/coach.h \
    userheaders/connection.h \
    userheaders/displayuser.h \
    userheaders/emailsent.h \
    userheaders/employeview.h \
    userheaders/mainwindow.h \
    userheaders/modifyuser.h \
    userheaders/newpassword.h \
    userheaders/profile.h \
    userheaders/qrcodegen.hpp \
    userheaders/recoverpassword.h \
    userheaders/sessionmanager.h \
    userheaders/stats.h \
    userheaders/user.h

FORMS += \
    teamui/chatdialog.ui \
    teamui/modifyTeam.ui \
    teamui/tableau.ui \
    teamui/teamwindow.ui \
    teamui/tododialog.ui \
    teamui/trash.ui \
    userui/displayplayers_coach.ui \
    teamui/formadd.ui \
    userui/EmailSent.ui \
    userui/NewPassword.ui \
    userui/addUser.ui \
    userui/adminview.ui \
    userui/coach.ui \
    userui/displayUser.ui \
    userui/employeview.ui \
    userui/mainwindow.ui \
    userui/modifyUser.ui \
    userui/profile.ui \
    userui/recoverpassword.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    images.qrc

