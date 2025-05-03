/********************************************************************************
** Form generated from reading UI file 'display_team.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DISPLAY_TEAM_H
#define UI_DISPLAY_TEAM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DisplayTeamWindow
{
public:
    QWidget *centralwidget;
    QWidget *widget;
    QGridLayout *gridLayout;
    QLabel *label_title;
    QLabel *label_team_name;
    QLabel *teamNameDisplay;
    QLabel *label_home_stadium;
    QLabel *stadiumDisplay;
    QLabel *label_goals;
    QLabel *goalsDisplay;
    QLabel *label_budget;
    QLabel *budgetDisplay;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *DisplayTeamWindow)
    {
        if (DisplayTeamWindow->objectName().isEmpty())
            DisplayTeamWindow->setObjectName("DisplayTeamWindow");
        DisplayTeamWindow->resize(777, 564);
        DisplayTeamWindow->setStyleSheet(QString::fromUtf8("background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 #1b1f2a, stop:1 #10131a);"));
        centralwidget = new QWidget(DisplayTeamWindow);
        centralwidget->setObjectName("centralwidget");
        widget = new QWidget(centralwidget);
        widget->setObjectName("widget");
        widget->setGeometry(QRect(50, 20, 631, 491));
        widget->setStyleSheet(QString::fromUtf8("background-color: #0F111A;\n"
"color: #FFFFFF;\n"
"font-family: 'Segoe UI', Arial, sans-serif;\n"
"font-size: 12px;\n"
"border-radius: 15px;\n"
"padding: 15px;"));
        gridLayout = new QGridLayout(widget);
        gridLayout->setObjectName("gridLayout");
        label_title = new QLabel(widget);
        label_title->setObjectName("label_title");
        label_title->setStyleSheet(QString::fromUtf8("color: #FFFFFF; font-size: 18px; font-weight: bold; background-color: transparent;"));

        gridLayout->addWidget(label_title, 0, 0, 1, 1);

        label_team_name = new QLabel(widget);
        label_team_name->setObjectName("label_team_name");
        label_team_name->setStyleSheet(QString::fromUtf8("color: #A0A8B7; font-weight: bold; padding-bottom: 5px; background-color: transparent;"));

        gridLayout->addWidget(label_team_name, 1, 0, 1, 1);

        teamNameDisplay = new QLabel(widget);
        teamNameDisplay->setObjectName("teamNameDisplay");
        teamNameDisplay->setStyleSheet(QString::fromUtf8("color: #FFFFFF; background-color: transparent;"));

        gridLayout->addWidget(teamNameDisplay, 2, 0, 1, 1);

        label_home_stadium = new QLabel(widget);
        label_home_stadium->setObjectName("label_home_stadium");
        label_home_stadium->setStyleSheet(QString::fromUtf8("color: #A0A8B7; font-weight: bold; padding-bottom: 5px; background-color: transparent;"));

        gridLayout->addWidget(label_home_stadium, 3, 0, 1, 1);

        stadiumDisplay = new QLabel(widget);
        stadiumDisplay->setObjectName("stadiumDisplay");
        stadiumDisplay->setStyleSheet(QString::fromUtf8("color: #FFFFFF; background-color: transparent;"));

        gridLayout->addWidget(stadiumDisplay, 4, 0, 1, 1);

        label_goals = new QLabel(widget);
        label_goals->setObjectName("label_goals");
        label_goals->setStyleSheet(QString::fromUtf8("color: #A0A8B7; font-weight: bold; padding-bottom: 5px; background-color: transparent;"));

        gridLayout->addWidget(label_goals, 5, 0, 1, 1);

        goalsDisplay = new QLabel(widget);
        goalsDisplay->setObjectName("goalsDisplay");
        goalsDisplay->setStyleSheet(QString::fromUtf8("color: #FFFFFF; background-color: transparent;"));

        gridLayout->addWidget(goalsDisplay, 6, 0, 1, 1);

        label_budget = new QLabel(widget);
        label_budget->setObjectName("label_budget");
        label_budget->setStyleSheet(QString::fromUtf8("color: #A0A8B7; font-weight: bold; padding-bottom: 5px; background-color: transparent;"));

        gridLayout->addWidget(label_budget, 7, 0, 1, 1);

        budgetDisplay = new QLabel(widget);
        budgetDisplay->setObjectName("budgetDisplay");
        budgetDisplay->setStyleSheet(QString::fromUtf8("color: #FFFFFF; background-color: transparent;"));

        gridLayout->addWidget(budgetDisplay, 8, 0, 1, 1);

        DisplayTeamWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(DisplayTeamWindow);
        statusbar->setObjectName("statusbar");
        DisplayTeamWindow->setStatusBar(statusbar);

        retranslateUi(DisplayTeamWindow);

        QMetaObject::connectSlotsByName(DisplayTeamWindow);
    } // setupUi

    void retranslateUi(QMainWindow *DisplayTeamWindow)
    {
        DisplayTeamWindow->setWindowTitle(QCoreApplication::translate("DisplayTeamWindow", "Your Team", nullptr));
        label_title->setText(QCoreApplication::translate("DisplayTeamWindow", "Your Team Details", nullptr));
        label_team_name->setText(QCoreApplication::translate("DisplayTeamWindow", "Team Name:", nullptr));
        teamNameDisplay->setText(QCoreApplication::translate("DisplayTeamWindow", "-", nullptr));
        label_home_stadium->setText(QCoreApplication::translate("DisplayTeamWindow", "Home Stadium:", nullptr));
        stadiumDisplay->setText(QCoreApplication::translate("DisplayTeamWindow", "-", nullptr));
        label_goals->setText(QCoreApplication::translate("DisplayTeamWindow", "Goals:", nullptr));
        goalsDisplay->setText(QCoreApplication::translate("DisplayTeamWindow", "-", nullptr));
        label_budget->setText(QCoreApplication::translate("DisplayTeamWindow", "Budget:", nullptr));
        budgetDisplay->setText(QCoreApplication::translate("DisplayTeamWindow", "-", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DisplayTeamWindow: public Ui_DisplayTeamWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DISPLAY_TEAM_H
