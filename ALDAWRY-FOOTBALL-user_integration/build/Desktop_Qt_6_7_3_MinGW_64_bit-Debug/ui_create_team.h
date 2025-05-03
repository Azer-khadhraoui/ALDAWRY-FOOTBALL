/********************************************************************************
** Form generated from reading UI file 'create_team.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CREATE_TEAM_H
#define UI_CREATE_TEAM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CreateTeamWindow
{
public:
    QWidget *centralwidget;
    QWidget *widget;
    QGridLayout *gridLayout;
    QLabel *label_title;
    QLabel *label_team_name;
    QLineEdit *teamNameEdit;
    QLabel *label_home_stadium;
    QLineEdit *stadiumEdit;
    QLabel *label_goals;
    QLineEdit *goalsEdit;
    QLabel *label_budget;
    QLineEdit *budgetEdit;
    QLabel *label_team_logo;
    QLineEdit *teamLogoEdit;
    QPushButton *createButton;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *CreateTeamWindow)
    {
        if (CreateTeamWindow->objectName().isEmpty())
            CreateTeamWindow->setObjectName("CreateTeamWindow");
        CreateTeamWindow->resize(637, 667);
        CreateTeamWindow->setStyleSheet(QString::fromUtf8("background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 #1b1f2a, stop:1 #10131a);"));
        centralwidget = new QWidget(CreateTeamWindow);
        centralwidget->setObjectName("centralwidget");
        widget = new QWidget(centralwidget);
        widget->setObjectName("widget");
        widget->setGeometry(QRect(50, 20, 531, 591));
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

        teamNameEdit = new QLineEdit(widget);
        teamNameEdit->setObjectName("teamNameEdit");
        teamNameEdit->setStyleSheet(QString::fromUtf8("background-color: #1C1F2A; border: 1px solid #2A2D3A; border-radius: 5px; padding: 5px; color: white;"));

        gridLayout->addWidget(teamNameEdit, 2, 0, 1, 1);

        label_home_stadium = new QLabel(widget);
        label_home_stadium->setObjectName("label_home_stadium");
        label_home_stadium->setStyleSheet(QString::fromUtf8("color: #A0A8B7; font-weight: bold; padding-bottom: 5px; background-color: transparent;"));

        gridLayout->addWidget(label_home_stadium, 3, 0, 1, 1);

        stadiumEdit = new QLineEdit(widget);
        stadiumEdit->setObjectName("stadiumEdit");
        stadiumEdit->setStyleSheet(QString::fromUtf8("background-color: #1C1F2A; border: 1px solid #2A2D3A; border-radius: 5px; padding: 5px; color: white;"));

        gridLayout->addWidget(stadiumEdit, 4, 0, 1, 1);

        label_goals = new QLabel(widget);
        label_goals->setObjectName("label_goals");
        label_goals->setStyleSheet(QString::fromUtf8("color: #A0A8B7; font-weight: bold; padding-bottom: 5px; background-color: transparent;"));

        gridLayout->addWidget(label_goals, 5, 0, 1, 1);

        goalsEdit = new QLineEdit(widget);
        goalsEdit->setObjectName("goalsEdit");
        goalsEdit->setStyleSheet(QString::fromUtf8("background-color: #1C1F2A; border: 1px solid #2A2D3A; border-radius: 5px; padding: 5px; color: white;"));

        gridLayout->addWidget(goalsEdit, 6, 0, 1, 1);

        label_budget = new QLabel(widget);
        label_budget->setObjectName("label_budget");
        label_budget->setStyleSheet(QString::fromUtf8("color: #A0A8B7; font-weight: bold; padding-bottom: 5px; background-color: transparent;"));

        gridLayout->addWidget(label_budget, 7, 0, 1, 1);

        budgetEdit = new QLineEdit(widget);
        budgetEdit->setObjectName("budgetEdit");
        budgetEdit->setStyleSheet(QString::fromUtf8("background-color: #1C1F2A; border: 1px solid #2A2D3A; border-radius: 5px; padding: 5px; color: white;"));

        gridLayout->addWidget(budgetEdit, 8, 0, 1, 1);

        label_team_logo = new QLabel(widget);
        label_team_logo->setObjectName("label_team_logo");
        label_team_logo->setStyleSheet(QString::fromUtf8("color: #A0A8B7; font-weight: bold; padding-bottom: 5px; background-color: transparent;"));

        gridLayout->addWidget(label_team_logo, 9, 0, 1, 1);

        teamLogoEdit = new QLineEdit(widget);
        teamLogoEdit->setObjectName("teamLogoEdit");
        teamLogoEdit->setStyleSheet(QString::fromUtf8("background-color: #1C1F2A; border: 1px solid #2A2D3A; border-radius: 5px; padding: 5px; color: white;"));

        gridLayout->addWidget(teamLogoEdit, 10, 0, 1, 1);

        createButton = new QPushButton(widget);
        createButton->setObjectName("createButton");
        createButton->setStyleSheet(QString::fromUtf8("background-color: rgba(50, 150, 250, 0.8); color: white; font-size: 12px; border-radius: 5px; padding: 6px 12px;"));

        gridLayout->addWidget(createButton, 11, 0, 1, 1);

        CreateTeamWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(CreateTeamWindow);
        statusbar->setObjectName("statusbar");
        CreateTeamWindow->setStatusBar(statusbar);

        retranslateUi(CreateTeamWindow);

        QMetaObject::connectSlotsByName(CreateTeamWindow);
    } // setupUi

    void retranslateUi(QMainWindow *CreateTeamWindow)
    {
        CreateTeamWindow->setWindowTitle(QCoreApplication::translate("CreateTeamWindow", "Create Team", nullptr));
        label_title->setText(QCoreApplication::translate("CreateTeamWindow", "Create Your Team", nullptr));
        label_team_name->setText(QCoreApplication::translate("CreateTeamWindow", "Team Name", nullptr));
        label_home_stadium->setText(QCoreApplication::translate("CreateTeamWindow", "Home Stadium", nullptr));
        label_goals->setText(QCoreApplication::translate("CreateTeamWindow", "Goals", nullptr));
        label_budget->setText(QCoreApplication::translate("CreateTeamWindow", "Budget", nullptr));
        label_team_logo->setText(QCoreApplication::translate("CreateTeamWindow", "Team Logo (File Path)", nullptr));
        createButton->setText(QCoreApplication::translate("CreateTeamWindow", "Create Team", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CreateTeamWindow: public Ui_CreateTeamWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CREATE_TEAM_H
