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
QT += serialport network

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
    matchcpp/addmatch.cpp \
    matchcpp/arduino.cpp \
    matchcpp/chartmatch.cpp \
    matchcpp/displaymatch.cpp \
    matchcpp/fieldwidget.cpp \
    matchcpp/match.cpp \
    compcpp/addcompetitionwindow.cpp \
    compcpp/calendardialog.cpp \
    compcpp/competition.cpp \
    compcpp/competitionview.cpp \
    compcpp/deletewindow.cpp \
    compcpp/matchesdialog.cpp \
    compcpp/statistics.cpp \
    compcpp/statistics2.cpp \
    compcpp/tableau1.cpp \
    compcpp/updateform.cpp \
    matchcpp/matchview.cpp \
    matchcpp/statsmatch.cpp \
    matchcpp/viewmatch.cpp \
    matchcpp/watchmatchdialog.cpp \
    playercpp/addplayer.cpp \
    playercpp/deletejoueur.cpp \
    playercpp/formationpopup.cpp \
    playercpp/joueur.cpp \
    playercpp/modifyjoueur.cpp \
    playercpp/playerwindow.cpp \
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
    usercpp/user.cpp \
    usercpp/displaymatch_coach.cpp

HEADERS += \
    matchheaders/addmatch.h \
    matchheaders/arduino.h \
    matchheaders/chartmatch.h \
    matchheaders/displaymatch.h \
    matchheaders/fieldwidget.h \
    matchheaders/match.h \
    compheaders/addcompetitionwindow.h \
    compheaders/calendardialog.h \
    compheaders/competition.h \
    compheaders/competitionview.h \
    compheaders/deletewindow.h \
    compheaders/matchesdialog.h \
    compheaders/statistics.h \
    compheaders/statistics2.h \
    compheaders/tableau1.h \
    compheaders/updateform.h \
    matchheaders/matchview.h \
    matchheaders/statsmatch.h \
    matchheaders/viewmatch.h \
    matchheaders/watchmatchdialog.h \
    playerheaders/addplayer.h \
    playerheaders/deletejoueur.h \
    playerheaders/formationpopup.h \
    playerheaders/joueur.h \
    playerheaders/modifyjoueur.h \
    playerheaders/playerwindow.h \
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
    userheaders/user.h \
    userheaders/displaymatch_coach.h

FORMS += \
    compui/addcompetitionwindow.ui \
    compui/calendardialog.ui \
    compui/competitionview.ui \
    compui/deletewindow.ui \
    compui/matchesdialog.ui \
    compui/statistics.ui \
    compui/statistics2.ui \
    compui/tableau1.ui \
    compui/updateform.ui \
    matchui/addMatch.ui \
    matchui/chartMatch.ui \
    matchui/displayMatch.ui \
    matchui/fieldwidget.ui \
    matchui/matchview.ui \
    matchui/statsMatch.ui \
    matchui/viewMatch.ui \
    playerui/addPlayer.ui \
    playerui/playerwindow.ui \
    teamui/chatdialog.ui \
    teamui/modifyTeam.ui \
    teamui/tableau.ui \
    teamui/teamwindow.ui \
    teamui/tododialog.ui \
    teamui/trash.ui \
    userui/displaymatch_coach.ui \
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



