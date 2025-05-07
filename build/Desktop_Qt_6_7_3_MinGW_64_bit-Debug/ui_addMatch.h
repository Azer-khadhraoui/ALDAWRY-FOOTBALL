/********************************************************************************
** Form generated from reading UI file 'addMatch.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDMATCH_H
#define UI_ADDMATCH_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateTimeEdit>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_addMatch
{
public:
    QWidget *widget;
    QGridLayout *gridLayout_3;
    QLabel *label_7;
    QComboBox *team2;
    QPushButton *Confirm;
    QLabel *label_8;
    QLineEdit *Stadium;
    QLabel *label_10;
    QComboBox *Comp;
    QLabel *label_12;
    QLineEdit *Referee_name;
    QDateTimeEdit *Date;
    QLabel *label_11;
    QLabel *label_9;
    QComboBox *team1;
    QLabel *label_4;

    void setupUi(QWidget *addMatch)
    {
        if (addMatch->objectName().isEmpty())
            addMatch->setObjectName("addMatch");
        addMatch->resize(605, 635);
        addMatch->setStyleSheet(QString::fromUtf8("background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 #1b1f2a, stop:1 #10131a);"));
        widget = new QWidget(addMatch);
        widget->setObjectName("widget");
        widget->setGeometry(QRect(30, 80, 541, 521));
        widget->setStyleSheet(QString::fromUtf8("background-color: rgb(25, 31, 42);\n"
"    color: #FFFFFF;\n"
"    font-family: 'Segoe UI', Arial, sans-serif;\n"
"    font-size: 12px;\n"
"    border-radius: 15px;\n"
"    padding: 15px;\n"
"    spacing: 2px;\n"
""));
        gridLayout_3 = new QGridLayout(widget);
        gridLayout_3->setObjectName("gridLayout_3");
        label_7 = new QLabel(widget);
        label_7->setObjectName("label_7");
        label_7->setStyleSheet(QString::fromUtf8("color: #A0A8B7;\n"
"font-weight: bold;\n"
"padding-bottom: 5px;background-color:transparent;"));

        gridLayout_3->addWidget(label_7, 0, 0, 1, 1);

        team2 = new QComboBox(widget);
        team2->setObjectName("team2");
        team2->setStyleSheet(QString::fromUtf8("background-color: #2A3240;\n"
"  border: 1px solid #3A4A5A;\n"
"    border-radius: 5px;\n"
"    padding: 5px;\n"
"    color: #E0E6ED;\n"
"    margin-left: 15px;\n"
"    margin-right: 15px;\n"
"\n"
"Qcb::drop-down {\n"
"    border-left: 1px solid #3A4A5A;\n"
"    width: 20px;\n"
"}\n"
"Qcb:focus {\n"
"    border: 1px solid #00FF7F;\n"
"    background-color: #323A48;\n"
"}"));

        gridLayout_3->addWidget(team2, 4, 0, 1, 1);

        Confirm = new QPushButton(widget);
        Confirm->setObjectName("Confirm");
        Confirm->setEnabled(true);
        Confirm->setStyleSheet(QString::fromUtf8("background-color: #00FF7F; /* Green to match the accent */\n"
"    color: #1A2633; /* Dark blue text for contrast */\n"
"    font-size: 12px;\n"
"    font-weight: bold;\n"
"    border-radius: 5px;\n"
"    padding: 6px 12px;\n"
"    margin-left: 350px;\n"
"    margin-right: 20px;\n"
"    margin-bottom: 5px;"));

        gridLayout_3->addWidget(Confirm, 14, 0, 1, 1);

        label_8 = new QLabel(widget);
        label_8->setObjectName("label_8");
        label_8->setStyleSheet(QString::fromUtf8("color: #A0A8B7;\n"
"font-weight: bold;\n"
"padding-bottom: 5px;background-color:transparent;"));

        gridLayout_3->addWidget(label_8, 3, 0, 1, 1);

        Stadium = new QLineEdit(widget);
        Stadium->setObjectName("Stadium");
        Stadium->setStyleSheet(QString::fromUtf8("background-color: #2A3240; /* Darker blue-gray for input fields */\n"
"    border: 1px solid #3A4A5A; /* Subtle blue-gray border */\n"
"    border-radius: 5px;\n"
"    padding: 5px;\n"
"    color: #E0E6ED; /* Light gray text for readability */\n"
"    margin-left: 15px;\n"
"    margin-right: 15px;\n"
""));

        gridLayout_3->addWidget(Stadium, 6, 0, 1, 1);

        label_10 = new QLabel(widget);
        label_10->setObjectName("label_10");
        label_10->setStyleSheet(QString::fromUtf8("color: #A0A8B7;\n"
"font-weight: bold;\n"
"padding-bottom: 5px;background-color:transparent;"));

        gridLayout_3->addWidget(label_10, 11, 0, 1, 1);

        Comp = new QComboBox(widget);
        Comp->setObjectName("Comp");
        Comp->setStyleSheet(QString::fromUtf8("background-color: #2A3240;\n"
"  border: 1px solid #3A4A5A;\n"
"    border-radius: 5px;\n"
"    padding: 5px;\n"
"    color: #E0E6ED;\n"
"    margin-left: 15px;\n"
"    margin-right: 15px;\n"
"\n"
"Qcb::drop-down {\n"
"    border-left: 1px solid #3A4A5A;\n"
"    width: 20px;\n"
"}\n"
"Qcb:focus {\n"
"    border: 1px solid #00FF7F;\n"
"    background-color: #323A48;\n"
"}"));

        gridLayout_3->addWidget(Comp, 10, 0, 1, 1);

        label_12 = new QLabel(widget);
        label_12->setObjectName("label_12");
        label_12->setStyleSheet(QString::fromUtf8("color: #A0A8B7;\n"
"font-weight: bold;\n"
"padding-bottom: 5px;\n"
"background-color:transparent;\n"
""));

        gridLayout_3->addWidget(label_12, 7, 0, 1, 1);

        Referee_name = new QLineEdit(widget);
        Referee_name->setObjectName("Referee_name");
        Referee_name->setStyleSheet(QString::fromUtf8("background-color: #2A3240; /* Darker blue-gray for input fields */\n"
"    border: 1px solid #3A4A5A; /* Subtle blue-gray border */\n"
"    border-radius: 5px;\n"
"    padding: 5px;\n"
"    color: #E0E6ED; /* Light gray text for readability */\n"
"    margin-left: 15px;\n"
"    margin-right: 15px;\n"
""));

        gridLayout_3->addWidget(Referee_name, 8, 0, 1, 1);

        Date = new QDateTimeEdit(widget);
        Date->setObjectName("Date");
        Date->setStyleSheet(QString::fromUtf8("background-color: #2A3240;\n"
"  border: 1px solid #3A4A5A;\n"
"    border-radius: 5px;\n"
"    padding: 5px;\n"
"    color: #E0E6ED;\n"
"    margin-left: 15px;\n"
"    margin-right: 15px;\n"
"\n"
"Qcb::drop-down {\n"
"    border-left: 1px solid #3A4A5A;\n"
"    width: 20px;\n"
"}\n"
"Qcb:focus {\n"
"    border: 1px solid #00FF7F;\n"
"    background-color: #323A48;\n"
"}"));

        gridLayout_3->addWidget(Date, 12, 0, 1, 1);

        label_11 = new QLabel(widget);
        label_11->setObjectName("label_11");
        label_11->setStyleSheet(QString::fromUtf8("color: #A0A8B7;\n"
"font-weight: bold;\n"
"padding-bottom: 5px;background-color:transparent;"));

        gridLayout_3->addWidget(label_11, 5, 0, 1, 1);

        label_9 = new QLabel(widget);
        label_9->setObjectName("label_9");
        label_9->setStyleSheet(QString::fromUtf8("color: #A0A8B7;\n"
"font-weight: bold;\n"
"padding-bottom: 5px;background-color:transparent;"));

        gridLayout_3->addWidget(label_9, 9, 0, 1, 1);

        team1 = new QComboBox(widget);
        team1->setObjectName("team1");
        team1->setStyleSheet(QString::fromUtf8("background-color: #2A3240;\n"
"  border: 1px solid #3A4A5A;\n"
"    border-radius: 5px;\n"
"    padding: 5px;\n"
"    color: #E0E6ED;\n"
"    margin-left: 15px;\n"
"    margin-right: 15px;\n"
"\n"
"Qcb::drop-down {\n"
"    border-left: 1px solid #3A4A5A;\n"
"    width: 20px;\n"
"}\n"
"Qcb:focus {\n"
"    border: 1px solid #00FF7F;\n"
"    background-color: #323A48;\n"
"}"));

        gridLayout_3->addWidget(team1, 2, 0, 1, 1);

        label_4 = new QLabel(addMatch);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(230, 20, 171, 41));
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

        retranslateUi(addMatch);

        QMetaObject::connectSlotsByName(addMatch);
    } // setupUi

    void retranslateUi(QWidget *addMatch)
    {
        addMatch->setWindowTitle(QCoreApplication::translate("addMatch", "Form", nullptr));
        label_7->setText(QCoreApplication::translate("addMatch", "               Team_1 :", nullptr));
        Confirm->setText(QCoreApplication::translate("addMatch", "Confirm", nullptr));
        label_8->setText(QCoreApplication::translate("addMatch", "               Team_2 :", nullptr));
        label_10->setText(QCoreApplication::translate("addMatch", "               Date :", nullptr));
        label_12->setText(QCoreApplication::translate("addMatch", "               Referee's_FullName :", nullptr));
        label_11->setText(QCoreApplication::translate("addMatch", "              Stadium :", nullptr));
        label_9->setText(QCoreApplication::translate("addMatch", "               Competiton :", nullptr));
        label_4->setText(QCoreApplication::translate("addMatch", "Add Match", nullptr));
    } // retranslateUi

};

namespace Ui {
    class addMatch: public Ui_addMatch {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDMATCH_H
