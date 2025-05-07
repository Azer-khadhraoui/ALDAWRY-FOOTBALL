/********************************************************************************
** Form generated from reading UI file 'displayMatch.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DISPLAYMATCH_H
#define UI_DISPLAYMATCH_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_displayMatch
{
public:
    QTableView *allmatches;
    QLineEdit *search;
    QLabel *label_3;
    QPushButton *Modify;
    QPushButton *Delete;
    QPushButton *pdf;

    void setupUi(QWidget *displayMatch)
    {
        if (displayMatch->objectName().isEmpty())
            displayMatch->setObjectName("displayMatch");
        displayMatch->resize(725, 644);
        displayMatch->setStyleSheet(QString::fromUtf8("background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 #1b1f2a, stop:1 #10131a);"));
        allmatches = new QTableView(displayMatch);
        allmatches->setObjectName("allmatches");
        allmatches->setGeometry(QRect(10, 160, 701, 381));
        allmatches->setStyleSheet(QString::fromUtf8("/* Style for the tableWidget */\n"
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
        search = new QLineEdit(displayMatch);
        search->setObjectName("search");
        search->setGeometry(QRect(50, 110, 251, 31));
        search->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"    border: 1px solid white; /* Subtle blue-gray border */\n"
"    border-radius: 15px;\n"
"color: rgb(24, 24, 24);\n"
""));
        label_3 = new QLabel(displayMatch);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(280, 20, 191, 41));
        QFont font;
        font.setBold(true);
        label_3->setFont(font);
        label_3->setStyleSheet(QString::fromUtf8("/* Style for the Adjust Team title label */\n"
"QLabel#label_3 {\n"
"    background-color: transparent; /* Dark background matching the app */\n"
"    color: #FFFFFF; /* White text for contrast */\n"
"    font-size: 25px; /* Larger font for title emphasis */\n"
"    font-weight: bold; /* Bold for a strong title appearance */\n"
"\n"
"\n"
"    padding: 5px 10px; /* Padding for a balanced look */\n"
"}"));
        Modify = new QPushButton(displayMatch);
        Modify->setObjectName("Modify");
        Modify->setGeometry(QRect(610, 560, 50, 50));
        Modify->setStyleSheet(QString::fromUtf8("/* Style for the Modify button */\n"
"QPushButton#Modify {\n"
"    background-color:#D8A353 ; /* Green to match the accent */\n"
"    color: #1A2633; /* Dark blue text */\n"
"\n"
"}\n"
"QPushButton#Modify:hover {\n"
"    background-color: #eeb35b; /* Darker green on hover */\n"
"}\n"
"QPushButton#Modify:pressed {\n"
"    background-color:#a37b3f ; /* Even darker green when pressed */\n"
"}\n"
"    border: 1px solid white; /* Subtle blue-gray border */\n"
"    border-radius: 1px;"));
        Delete = new QPushButton(displayMatch);
        Delete->setObjectName("Delete");
        Delete->setGeometry(QRect(660, 560, 50, 50));
        Delete->setStyleSheet(QString::fromUtf8("/* Style for the Delete button */\n"
"QPushButton#Delete {\n"
"    background-color: #FF1414; /* Muted dark red */\n"
"    color: #E0E6ED; /* Light gray text */\n"
"\n"
"}\n"
"QPushButton#Delete:hover {\n"
"    background-color: #ff5d5d; /* Lighter red on hover */\n"
"}\n"
"QPushButton#Delete:pressed {\n"
"    background-color: #6A3A3A; /* Darker red when pressed */\n"
"}\n"
"    border: 1px solid white; /* Subtle blue-gray border */\n"
"    border-radius: 1px;"));
        pdf = new QPushButton(displayMatch);
        pdf->setObjectName("pdf");
        pdf->setGeometry(QRect(560, 560, 50, 50));
        pdf->setStyleSheet(QString::fromUtf8("/* Style for the Modify button */\n"
"QPushButton#pdf {\n"
"	background-color: #2B2F37;\n"
"}\n"
"QPushButton#pdf:hover {\n"
"    background-color:#343842 ; /* Darker green on hover */\n"
"}\n"
"QPushButton#pdf:pressed {\n"
"    background-color: #1e2127; /* Even darker green when pressed */\n"
"}\n"
"    border: 1px solid white; /* Subtle blue-gray border */\n"
"    border-radius: 1px;"));

        retranslateUi(displayMatch);

        QMetaObject::connectSlotsByName(displayMatch);
    } // setupUi

    void retranslateUi(QWidget *displayMatch)
    {
        displayMatch->setWindowTitle(QCoreApplication::translate("displayMatch", "Form", nullptr));
        label_3->setText(QCoreApplication::translate("displayMatch", "Adjust Match", nullptr));
        Modify->setText(QCoreApplication::translate("displayMatch", "Modify", nullptr));
        Delete->setText(QCoreApplication::translate("displayMatch", "Delete", nullptr));
        pdf->setText(QCoreApplication::translate("displayMatch", "PDF", nullptr));
    } // retranslateUi

};

namespace Ui {
    class displayMatch: public Ui_displayMatch {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DISPLAYMATCH_H
