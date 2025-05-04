/********************************************************************************
** Form generated from reading UI file 'displayUser.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DISPLAYUSER_H
#define UI_DISPLAYUSER_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DisplayUser
{
public:
    QPushButton *pushButton_3;
    QLineEdit *lineEdit_10;
    QPushButton *pdfButton;
    QLabel *photoLabel;
    QTableView *tableView_3;
    QLabel *label_4;
    QPushButton *ModifyUser;
    QLabel *label;
    QLabel *label_5;
    QWidget *widget;
    QGridLayout *gridLayout_3;

    void setupUi(QWidget *Form)
    {
        if (Form->objectName().isEmpty())
            Form->setObjectName("Form");
        Form->resize(1047, 721);
        Form->setStyleSheet(QString::fromUtf8("background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 #1b1f2a, stop:1 #10131a);"));
        pushButton_3 = new QPushButton(Form);
        pushButton_3->setObjectName("pushButton_3");
        pushButton_3->setGeometry(QRect(660, 580, 50, 50));
        pushButton_3->setStyleSheet(QString::fromUtf8("/* Style for the Delete button */\n"
"QPushButton#pushButton_3 {\n"
"    background-color: #FF1414; /* Muted dark red */\n"
"    color: #E0E6ED; /* Light gray text */\n"
"\n"
"}\n"
"QPushButton#pushButton_3:hover {\n"
"    background-color: #ff5d5d; /* Lighter red on hover */\n"
"}\n"
"QPushButton#pushButton_3:pressed {\n"
"    background-color: #6A3A3A; /* Darker red when pressed */\n"
"}\n"
"    border: 1px solid white; /* Subtle blue-gray border */\n"
"    border-radius: 1px;"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/img/deleteIcon.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButton_3->setIcon(icon);
        pushButton_3->setIconSize(QSize(25, 25));
        lineEdit_10 = new QLineEdit(Form);
        lineEdit_10->setObjectName("lineEdit_10");
        lineEdit_10->setGeometry(QRect(50, 100, 251, 31));
        lineEdit_10->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"    border: 1px solid white; /* Subtle blue-gray border */\n"
"    border-radius: 15px;\n"
"color: rgb(24, 24, 24);\n"
""));
        pdfButton = new QPushButton(Form);
        pdfButton->setObjectName("pdfButton");
        pdfButton->setGeometry(QRect(560, 580, 50, 50));
        pdfButton->setStyleSheet(QString::fromUtf8("/* Style for the Modify button */\n"
"QPushButton#pdfButton {\n"
"	background-color: #2B2F37;\n"
"}\n"
"QPushButton#pdfButton:hover {\n"
"    background-color:#343842 ; /* Darker green on hover */\n"
"}\n"
"QPushButton#pdfButton:pressed {\n"
"    background-color: #1e2127; /* Even darker green when pressed */\n"
"}\n"
"    border: 1px solid white; /* Subtle blue-gray border */\n"
"    border-radius: 1px;"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/img/pdfIcon.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pdfButton->setIcon(icon1);
        pdfButton->setIconSize(QSize(25, 25));
        photoLabel = new QLabel(Form);
        photoLabel->setObjectName("photoLabel");
        photoLabel->setGeometry(QRect(730, 370, 200, 200));
        photoLabel->setStyleSheet(QString::fromUtf8("background-color: transparent;\n"
"border: 1px solid #3A3D4A;\n"
"border-radius: 12px;\n"
"box-shadow: 0 4px 10px rgba(0, 0, 0, 0.2);"));
        photoLabel->setScaledContents(true);
        tableView_3 = new QTableView(Form);
        tableView_3->setObjectName("tableView_3");
        tableView_3->setGeometry(QRect(10, 150, 701, 421));
        tableView_3->setStyleSheet(QString::fromUtf8("/* Style for the tableWidget */\n"
"QTableView {\n"
"    background-color: #2D3748; /* Dark background matching the app */\n"
"    color: #FFFFFF; /* White text for readability */\n"
"    border: 1px solid #4A4E58; /* Subtle border matching button hover color */\n"
"    gridline-color: #4A4E58; /* Subtle grid lines */\n"
"}\n"
"\n"
"/* Style for table items */\n"
"QTableView::item {\n"
"    border: 1px solid #4A4E58; /* Subtle cell borders */\n"
"    padding: 5px; /* Spacing inside cells */\n"
"}\n"
"\n"
"/* Alternating row colors */\n"
"QTableView::item:nth-child(even) {\n"
"    background-color: #2D3748; /* Darker shade for even rows */\n"
"}\n"
"\n"
"QTableView::item:nth-child(odd) {\n"
"    background-color: #394252; /* Slightly lighter shade for odd rows */\n"
"}\n"
"\n"
"/* Hover effect for rows */\n"
"QTableView::item:hover {\n"
"    background-color: #4A4E58; /* Lighter shade on hover */\n"
"}\n"
"\n"
"/* Style for the header */\n"
"QHeaderView::section {\n"
"    background-color: #F5A623; /* Accent co"
                        "lor for header */\n"
"    color: #1A2633; /* Dark text for contrast */\n"
"    font-weight: bold; /* Bold header text */\n"
"    border: 1px solid #4A4E58; /* Border to match table */\n"
"    padding: 5px; /* Spacing inside header */\n"
"}\n"
"\n"
"/* Remove selection background */\n"
"QTableView::item:selected {\n"
"    background-color: #4A4E58; /* Same as hover to avoid clashing */\n"
"    color: #FFFFFF; /* Keep text white */\n"
"}"));
        label_4 = new QLabel(Form);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(370, 10, 171, 51));
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
        ModifyUser = new QPushButton(Form);
        ModifyUser->setObjectName("ModifyUser");
        ModifyUser->setGeometry(QRect(610, 580, 50, 50));
        ModifyUser->setStyleSheet(QString::fromUtf8("/* Style for the Modify button */\n"
"QPushButton#ModifyUser {\n"
"    background-color:#D8A353 ; /* Green to match the accent */\n"
"    color: #1A2633; /* Dark blue text */\n"
"\n"
"}\n"
"QPushButton#ModifyUser:hover {\n"
"    background-color: #eeb35b; /* Darker green on hover */\n"
"}\n"
"QPushButton#ModifyUser:pressed {\n"
"    background-color:#a37b3f ; /* Even darker green when pressed */\n"
"}\n"
"    border: 1px solid white; /* Subtle blue-gray border */\n"
"    border-radius: 1px;"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/img/editIcon.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ModifyUser->setIcon(icon2);
        ModifyUser->setIconSize(QSize(25, 25));
        label = new QLabel(Form);
        label->setObjectName("label");
        label->setGeometry(QRect(260, 90, 44, 44));
        label->setStyleSheet(QString::fromUtf8("background-color: transparent;"));
        label->setPixmap(QPixmap(QString::fromUtf8(":/img/search.png")));
        label->setScaledContents(true);
        label_5 = new QLabel(Form);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(770, 320, 111, 51));
        QFont font1;
        font1.setBold(false);
        label_5->setFont(font1);
        label_5->setStyleSheet(QString::fromUtf8("/* Style for the Adjust Team title label */\n"
"QLabel#label_5 {\n"
"    background-color: transparent; /* Dark background matching the app */\n"
"    color: #FFFFFF; /* White text for contrast */\n"
"    font-size: 15px; /* Larger font for title emphasis */\n"
"    padding: 5px 10px; /* Padding for a balanced look */\n"
"}"));
        widget = new QWidget(Form);
        widget->setObjectName("widget");
        widget->setGeometry(QRect(0, 0, 1051, 741));
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
        widget->raise();
        pushButton_3->raise();
        lineEdit_10->raise();
        pdfButton->raise();
        photoLabel->raise();
        tableView_3->raise();
        label_4->raise();
        ModifyUser->raise();
        label->raise();
        label_5->raise();

        retranslateUi(Form);

        QMetaObject::connectSlotsByName(Form);
    } // setupUi

    void retranslateUi(QWidget *Form)
    {
        Form->setWindowTitle(QCoreApplication::translate("DisplayUser", "Form", nullptr));
        pushButton_3->setText(QString());
        lineEdit_10->setPlaceholderText(QCoreApplication::translate("DisplayUser", "      Search by user's name", nullptr));
        pdfButton->setText(QString());
        photoLabel->setText(QString());
        label_4->setText(QCoreApplication::translate("DisplayUser", "Display User", nullptr));
        ModifyUser->setText(QString());
        label->setText(QString());
        label_5->setText(QCoreApplication::translate("DisplayUser", "User's Picture", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DisplayUser: public Ui_DisplayUser {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DISPLAYUSER_H
