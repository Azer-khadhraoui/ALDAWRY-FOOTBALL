/********************************************************************************
** Form generated from reading UI file 'viewMatch.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VIEWMATCH_H
#define UI_VIEWMATCH_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QTableView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_viewMatch
{
public:
    QTableView *allmatches;
    QLineEdit *search;
    QLabel *label_3;

    void setupUi(QWidget *viewMatch)
    {
        if (viewMatch->objectName().isEmpty())
            viewMatch->setObjectName("viewMatch");
        viewMatch->resize(725, 644);
        viewMatch->setStyleSheet(QString::fromUtf8("background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 #1b1f2a, stop:1 #10131a);"));
        allmatches = new QTableView(viewMatch);
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
        search = new QLineEdit(viewMatch);
        search->setObjectName("search");
        search->setGeometry(QRect(50, 110, 251, 31));
        search->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"    border: 1px solid white; /* Subtle blue-gray border */\n"
"    border-radius: 15px;\n"
"color: rgb(24, 24, 24);\n"
""));
        label_3 = new QLabel(viewMatch);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(280, 20, 181, 41));
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

        retranslateUi(viewMatch);

        QMetaObject::connectSlotsByName(viewMatch);
    } // setupUi

    void retranslateUi(QWidget *viewMatch)
    {
        viewMatch->setWindowTitle(QCoreApplication::translate("viewMatch", "Form", nullptr));
        label_3->setText(QCoreApplication::translate("viewMatch", "View Match", nullptr));
    } // retranslateUi

};

namespace Ui {
    class viewMatch: public Ui_viewMatch {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VIEWMATCH_H
