QT += core gui sql charts multimedia multimediawidgets network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17
CONFIG += console

SOURCES += \
    chatdialog.cpp \
    connection.cpp \
    formadd.cpp \
    main.cpp \
    mainwindow.cpp \
    modifyteam.cpp \
    tableau.cpp \
    team.cpp \
    tododialog.cpp

HEADERS += \
    chatdialog.h \
    connection.h \
    formadd.h \
    mainwindow.h \
    modifyteam.h \
    tableau.h \
    team.h \
    tododialog.h

FORMS += \
    chatdialog.ui \
    formadd.ui \
    mainwindow.ui \
    modifyTeam.ui \
    tableau.ui \
    trash.ui \
    tododialog.ui

RESOURCES += \
    images.qrc
