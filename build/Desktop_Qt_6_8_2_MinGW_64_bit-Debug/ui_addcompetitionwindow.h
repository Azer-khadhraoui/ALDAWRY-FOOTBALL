/********************************************************************************
** Form generated from reading UI file 'addcompetitionwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDCOMPETITIONWINDOW_H
#define UI_ADDCOMPETITIONWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AddCompetitionForm
{
public:
    QWidget *widget;
    QVBoxLayout *verticalLayout_2;
    QWidget *widget1;
    QVBoxLayout *verticalLayout;
    QLabel *label_comp_name;
    QLineEdit *lineEdit_comp_name;
    QLabel *label_comp_type;
    QComboBox *comboBox_comp_type;
    QLabel *label_start_date;
    QDateEdit *dateEdit_start_date;
    QLabel *label_end_date;
    QDateEdit *dateEdit_end_date;
    QLabel *label_numbers_teams;
    QSpinBox *spinBox_numbers_teams;
    QLabel *label_reward;
    QLineEdit *lineEdit_reward;
    QPushButton *pushButton_submit;
    QLabel *label_4;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *label_7;

    void setupUi(QWidget *AddCompetitionForm)
    {
        if (AddCompetitionForm->objectName().isEmpty())
            AddCompetitionForm->setObjectName("AddCompetitionForm");
        AddCompetitionForm->resize(588, 677);
        AddCompetitionForm->setStyleSheet(QString::fromUtf8("background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 #1b1f2a, stop:1 #10131a);"));
        widget = new QWidget(AddCompetitionForm);
        widget->setObjectName("widget");
        widget->setGeometry(QRect(20, 90, 541, 561));
        widget->setStyleSheet(QString::fromUtf8("background-color: rgb(25, 31, 42);\n"
"    color: #FFFFFF;\n"
"    font-family: 'Segoe UI', Arial, sans-serif;\n"
"    font-size: 12px;\n"
"    border-radius: 15px;\n"
"    padding: 15px;\n"
"    spacing: 2px;\n"
""));
        verticalLayout_2 = new QVBoxLayout(widget);
        verticalLayout_2->setObjectName("verticalLayout_2");
        widget1 = new QWidget(widget);
        widget1->setObjectName("widget1");
        verticalLayout = new QVBoxLayout(widget1);
        verticalLayout->setObjectName("verticalLayout");
        label_comp_name = new QLabel(widget1);
        label_comp_name->setObjectName("label_comp_name");
        label_comp_name->setStyleSheet(QString::fromUtf8("color: #A0A8B7;\n"
"font-weight: bold;\n"
"padding-bottom: 5px;background-color:transparent;"));

        verticalLayout->addWidget(label_comp_name);

        lineEdit_comp_name = new QLineEdit(widget1);
        lineEdit_comp_name->setObjectName("lineEdit_comp_name");
        lineEdit_comp_name->setStyleSheet(QString::fromUtf8("background-color: #2A3240; /* Darker blue-gray for input fields */\n"
"    border: 1px solid #3A4A5A; /* Subtle blue-gray border */\n"
"    border-radius: 5px;\n"
"    padding: 5px;\n"
"    color: #E0E6ED; /* Light gray text for readability */\n"
"    margin-left: 15px;\n"
"    margin-right: 15px;\n"
""));

        verticalLayout->addWidget(lineEdit_comp_name);

        label_comp_type = new QLabel(widget1);
        label_comp_type->setObjectName("label_comp_type");
        label_comp_type->setStyleSheet(QString::fromUtf8("color: #A0A8B7;\n"
"font-weight: bold;\n"
"padding-bottom: 5px;background-color:transparent;"));

        verticalLayout->addWidget(label_comp_type);

        comboBox_comp_type = new QComboBox(widget1);
        comboBox_comp_type->addItem(QString());
        comboBox_comp_type->addItem(QString());
        comboBox_comp_type->addItem(QString());
        comboBox_comp_type->setObjectName("comboBox_comp_type");
        comboBox_comp_type->setStyleSheet(QString::fromUtf8("background-color: #2A3240;\n"
"  border: 1px solid #3A4A5A;\n"
"    border-radius: 5px;\n"
"    padding: 5px;\n"
"    color: #E0E6ED;\n"
"    margin-left: 15px;\n"
"    margin-right: 15px;\n"
"\n"
"comboBox_comp_type::drop-down {\n"
"    border-left: 1px solid #3A4A5A;\n"
"    width: 20px;\n"
"}\n"
"comboBox_comp_type::focus {\n"
"    border: 1px solid #00FF7F;\n"
"    background-color: #323A48;\n"
"}"));

        verticalLayout->addWidget(comboBox_comp_type);

        label_start_date = new QLabel(widget1);
        label_start_date->setObjectName("label_start_date");
        label_start_date->setStyleSheet(QString::fromUtf8("color: #A0A8B7;\n"
"font-weight: bold;\n"
"padding-bottom: 5px;background-color:transparent;"));

        verticalLayout->addWidget(label_start_date);

        dateEdit_start_date = new QDateEdit(widget1);
        dateEdit_start_date->setObjectName("dateEdit_start_date");
        dateEdit_start_date->setStyleSheet(QString::fromUtf8("background-color: #2A3240;\n"
"  border: 1px solid #3A4A5A;\n"
"    border-radius: 5px;\n"
"    padding: 5px;\n"
"    color: #E0E6ED;\n"
"    margin-left: 15px;\n"
"    margin-right: 15px;\n"
"\n"
"comboBox_comp_type::drop-down {\n"
"    border-left: 1px solid #3A4A5A;\n"
"    width: 20px;\n"
"}\n"
"comboBox_comp_type::focus {\n"
"    border: 1px solid #00FF7F;\n"
"    background-color: #323A48;\n"
"}"));
        dateEdit_start_date->setCalendarPopup(true);

        verticalLayout->addWidget(dateEdit_start_date);

        label_end_date = new QLabel(widget1);
        label_end_date->setObjectName("label_end_date");
        label_end_date->setStyleSheet(QString::fromUtf8("color: #A0A8B7;\n"
"font-weight: bold;\n"
"padding-bottom: 5px;background-color:transparent;"));

        verticalLayout->addWidget(label_end_date);

        dateEdit_end_date = new QDateEdit(widget1);
        dateEdit_end_date->setObjectName("dateEdit_end_date");
        dateEdit_end_date->setStyleSheet(QString::fromUtf8("background-color: #2A3240;\n"
"  border: 1px solid #3A4A5A;\n"
"    border-radius: 5px;\n"
"    padding: 5px;\n"
"    color: #E0E6ED;\n"
"    margin-left: 15px;\n"
"    margin-right: 15px;\n"
"\n"
"comboBox_comp_type::drop-down {\n"
"    border-left: 1px solid #3A4A5A;\n"
"    width: 20px;\n"
"}\n"
"comboBox_comp_type::focus {\n"
"    border: 1px solid #00FF7F;\n"
"    background-color: #323A48;\n"
"}"));
        dateEdit_end_date->setCalendarPopup(true);

        verticalLayout->addWidget(dateEdit_end_date);

        label_numbers_teams = new QLabel(widget1);
        label_numbers_teams->setObjectName("label_numbers_teams");
        label_numbers_teams->setStyleSheet(QString::fromUtf8("color: #A0A8B7;\n"
"font-weight: bold;\n"
"padding-bottom: 5px;background-color:transparent;"));

        verticalLayout->addWidget(label_numbers_teams);

        spinBox_numbers_teams = new QSpinBox(widget1);
        spinBox_numbers_teams->setObjectName("spinBox_numbers_teams");
        spinBox_numbers_teams->setStyleSheet(QString::fromUtf8("background-color: #2A3240; /* Darker blue-gray for input fields */\n"
"    border: 1px solid #3A4A5A; /* Subtle blue-gray border */\n"
"    border-radius: 5px;\n"
"    padding: 5px;\n"
"    color: #E0E6ED; /* Light gray text for readability */\n"
"    margin-left: 15px;\n"
"    margin-right: 15px;\n"
"    padding-top: 1px;\n"
""));
        spinBox_numbers_teams->setMinimum(2);
        spinBox_numbers_teams->setMaximum(100);

        verticalLayout->addWidget(spinBox_numbers_teams);

        label_reward = new QLabel(widget1);
        label_reward->setObjectName("label_reward");
        label_reward->setStyleSheet(QString::fromUtf8("color: #A0A8B7;\n"
"font-weight: bold;\n"
"padding-bottom: 5px;background-color:transparent;"));

        verticalLayout->addWidget(label_reward);

        lineEdit_reward = new QLineEdit(widget1);
        lineEdit_reward->setObjectName("lineEdit_reward");
        lineEdit_reward->setStyleSheet(QString::fromUtf8("background-color: #2A3240; /* Darker blue-gray for input fields */\n"
"    border: 1px solid #3A4A5A; /* Subtle blue-gray border */\n"
"    border-radius: 5px;\n"
"    padding: 5px;\n"
"    color: #E0E6ED; /* Light gray text for readability */\n"
"    margin-left: 15px;\n"
"    margin-right: 15px;\n"
""));

        verticalLayout->addWidget(lineEdit_reward);

        pushButton_submit = new QPushButton(widget1);
        pushButton_submit->setObjectName("pushButton_submit");
        pushButton_submit->setStyleSheet(QString::fromUtf8("background-color: #00FF7F; /* Green to match the accent */\n"
"    color: #1A2633; /* Dark blue text for contrast */\n"
"    font-size: 12px;\n"
"    font-weight: bold;\n"
"    border-radius: 5px;\n"
"    padding: 6px 12px;\n"
"    margin-left: 350px;\n"
"    margin-right: 20px;\n"
"    margin-bottom: 5px;"));

        verticalLayout->addWidget(pushButton_submit);


        verticalLayout_2->addWidget(widget1);

        label_4 = new QLabel(AddCompetitionForm);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(180, 30, 231, 41));
        QFont font;
        font.setBold(true);
        label_4->setFont(font);
        label_4->setStyleSheet(QString::fromUtf8("/* Style for the Adjust Team title label */\n"
"QLabel#label_4 {\n"
"    background-color: transparent; /* Dark background matching the app */\n"
"    color: #FFFFFF; /* White text for contrast */\n"
"    font-size: 25px; /* Larger font for title emphasis */\n"
"    font-weight: bold; /* Bold for a strong title appearance */\n"
"\n"
"\n"
"    padding: 5px 10px; /* Padding for a balanced look */\n"
"}"));
        label = new QLabel(AddCompetitionForm);
        label->setObjectName("label");
        label->setGeometry(QRect(56, 123, 41, 19));
        label->setPixmap(QPixmap(QString::fromUtf8(":/images/compName.png")));
        label->setScaledContents(true);
        label_2 = new QLabel(AddCompetitionForm);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(60, 207, 20, 14));
        label_2->setStyleSheet(QString::fromUtf8("background-color: TRANSPARENT;"));
        label_2->setPixmap(QPixmap(QString::fromUtf8(":/images/compType.png")));
        label_2->setScaledContents(true);
        label_3 = new QLabel(AddCompetitionForm);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(57, 286, 20, 20));
        label_3->setStyleSheet(QString::fromUtf8("background-color: TRANSPARENT;"));
        label_3->setPixmap(QPixmap(QString::fromUtf8(":/images/StartDate.png")));
        label_3->setScaledContents(true);
        label_5 = new QLabel(AddCompetitionForm);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(53, 365, 30, 30));
        label_5->setStyleSheet(QString::fromUtf8("background-color: TRANSPARENT;"));
        label_5->setPixmap(QPixmap(QString::fromUtf8(":/images/ExpDate.png")));
        label_5->setScaledContents(true);
        label_6 = new QLabel(AddCompetitionForm);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(60, 455, 20, 20));
        label_6->setStyleSheet(QString::fromUtf8("background-color: TRANSPARENT;"));
        label_6->setPixmap(QPixmap(QString::fromUtf8(":/images/numbers.png")));
        label_6->setScaledContents(true);
        label_7 = new QLabel(AddCompetitionForm);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(60, 526, 20, 24));
        label_7->setStyleSheet(QString::fromUtf8("background-color: TRANSPARENT;"));
        label_7->setPixmap(QPixmap(QString::fromUtf8(":/images/reward.png")));
        label_7->setScaledContents(true);

        retranslateUi(AddCompetitionForm);

        QMetaObject::connectSlotsByName(AddCompetitionForm);
    } // setupUi

    void retranslateUi(QWidget *AddCompetitionForm)
    {
        AddCompetitionForm->setWindowTitle(QCoreApplication::translate("AddCompetitionForm", "Add New Competition", nullptr));
        label_comp_name->setText(QCoreApplication::translate("AddCompetitionForm", "                   Competition Name:", nullptr));
        label_comp_type->setText(QCoreApplication::translate("AddCompetitionForm", "                  Competition Type:", nullptr));
        comboBox_comp_type->setItemText(0, QCoreApplication::translate("AddCompetitionForm", "League", nullptr));
        comboBox_comp_type->setItemText(1, QCoreApplication::translate("AddCompetitionForm", "Tournament", nullptr));
        comboBox_comp_type->setItemText(2, QCoreApplication::translate("AddCompetitionForm", "Cup", nullptr));

        label_start_date->setText(QCoreApplication::translate("AddCompetitionForm", "                  Start Date:", nullptr));
        label_end_date->setText(QCoreApplication::translate("AddCompetitionForm", "                  End Date:", nullptr));
        label_numbers_teams->setText(QCoreApplication::translate("AddCompetitionForm", "                  Number of Teams:", nullptr));
        label_reward->setText(QCoreApplication::translate("AddCompetitionForm", "                  Reward:", nullptr));
        pushButton_submit->setText(QCoreApplication::translate("AddCompetitionForm", "Submit", nullptr));
        label_4->setText(QCoreApplication::translate("AddCompetitionForm", "Add Competiton", nullptr));
        label->setText(QString());
        label_2->setText(QString());
        label_3->setText(QString());
        label_5->setText(QString());
        label_6->setText(QString());
        label_7->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class AddCompetitionForm: public Ui_AddCompetitionForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDCOMPETITIONWINDOW_H
