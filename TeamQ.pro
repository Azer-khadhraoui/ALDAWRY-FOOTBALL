QT += core gui sql charts multimedia multimediawidgets network
QT += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17
CONFIG += console

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    chatdialog.cpp \
    connection.cpp \
    formadd.cpp \
    main.cpp \
    mainwindow.cpp \
    modifyteam.cpp \
    tableau.cpp \
    team.cpp
    chatdialog.cpp

HEADERS += \
    chatdialog.h \
    connection.h \
    formadd.h \
    mainwindow.h \
    modifyteam.h \
    tableau.h \
    team.h
    chatdialog.h

FORMS += \
    chatdialog.ui \
    formadd.ui \
    mainwindow.ui \
    modifyTeam.ui \
    tableau.ui \
    trash.ui
    chatdialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    images.qrc
