/********************************************************************************
** Form generated from reading UI file 'statsMatch.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STATSMATCH_H
#define UI_STATSMATCH_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QTableView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_statsMatch
{
public:
    QWidget *weather_impact;
    QTableView *Matches_sum;
    QTableView *refrees;
    QLabel *label_3;

    void setupUi(QWidget *statsMatch)
    {
        if (statsMatch->objectName().isEmpty())
            statsMatch->setObjectName("statsMatch");
        statsMatch->resize(942, 660);
        statsMatch->setStyleSheet(QString::fromUtf8("background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 #1b1f2a, stop:1 #10131a);"));
        weather_impact = new QWidget(statsMatch);
        weather_impact->setObjectName("weather_impact");
        weather_impact->setGeometry(QRect(10, 350, 921, 291));
        weather_impact->setStyleSheet(QString::fromUtf8("QWidget#customWidget {\n"
"    background-color: #1E2633;\n"
"    border: 2px solid #2A3A4A;\n"
"    color: #E0E6ED;\n"
"    border-radius: 5px;\n"
"}\n"
"QWidget#customWidget QLabel {\n"
"    color: #E0E6ED;\n"
"    background-color: transparent;\n"
"}"));
        Matches_sum = new QTableView(statsMatch);
        Matches_sum->setObjectName("Matches_sum");
        Matches_sum->setGeometry(QRect(10, 90, 921, 101));
        Matches_sum->setStyleSheet(QString::fromUtf8("/* Style for the QTableWidget */\n"
"QTableView#allmatches {\n"
"    background-color: #1E2633; /* Match tab pane and form widget */\n"
"    border: 2px solid #2A3A4A; /* Subtle blue-gray border */\n"
"    gridline-color: #3A4A5A; /* Light grid lines */\n"
"    alternate-background-color: #252A38; /* Alternating row color */\n"
"    color: #E0E6ED; /* Light gray text */\n"
"    selection-background-color: #00FF7F; /* Green selection */\n"
"    selection-color: #1A2633; /* Dark blue text on selection */\n"
"    border-radius: 5px;\n"
"}\n"
"QTableView#allmatches::item {\n"
"    padding: 5px;\n"
"    border: none; /* Remove individual cell borders */\n"
"}\n"
"QTableView#allmatches::item:focus {\n"
"    outline: none; /* Remove focus outline */\n"
"}\n"
"\n"
"/* Style for the table header */\n"
"QHeaderView::section {\n"
"    background-color: #252A38; /* Match alternating row color */\n"
"    color: #E0E6ED;\n"
"    border: 1px solid #2A3A4A;\n"
"    padding: 4px;\n"
"    font-weight: bold;\n"
"    border-radiu"
                        "s: 0;\n"
"}\n"
"QTableView#allmatches QTableCornerButton::section {\n"
"    background-color: #252A38;\n"
"    border: 1px solid #2A3A4A;\n"
"}"));
        refrees = new QTableView(statsMatch);
        refrees->setObjectName("refrees");
        refrees->setGeometry(QRect(10, 210, 921, 121));
        refrees->setStyleSheet(QString::fromUtf8("/* Style for the QTableWidget */\n"
"QTableView#allmatches {\n"
"    background-color: #1E2633; /* Match tab pane and form widget */\n"
"    border: 2px solid #2A3A4A; /* Subtle blue-gray border */\n"
"    gridline-color: #3A4A5A; /* Light grid lines */\n"
"    alternate-background-color: #252A38; /* Alternating row color */\n"
"    color: #E0E6ED; /* Light gray text */\n"
"    selection-background-color: #00FF7F; /* Green selection */\n"
"    selection-color: #1A2633; /* Dark blue text on selection */\n"
"    border-radius: 5px;\n"
"}\n"
"QTableView#allmatches::item {\n"
"    padding: 5px;\n"
"    border: none; /* Remove individual cell borders */\n"
"}\n"
"QTableView#allmatches::item:focus {\n"
"    outline: none; /* Remove focus outline */\n"
"}\n"
"\n"
"/* Style for the table header */\n"
"QHeaderView::section {\n"
"    background-color: #252A38; /* Match alternating row color */\n"
"    color: #E0E6ED;\n"
"    border: 1px solid #2A3A4A;\n"
"    padding: 4px;\n"
"    font-weight: bold;\n"
"    border-radiu"
                        "s: 0;\n"
"}\n"
"QTableView#allmatches QTableCornerButton::section {\n"
"    background-color: #252A38;\n"
"    border: 1px solid #2A3A4A;\n"
"}"));
        label_3 = new QLabel(statsMatch);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(320, 20, 241, 41));
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

        retranslateUi(statsMatch);

        QMetaObject::connectSlotsByName(statsMatch);
    } // setupUi

    void retranslateUi(QWidget *statsMatch)
    {
        statsMatch->setWindowTitle(QCoreApplication::translate("statsMatch", "Form", nullptr));
        label_3->setText(QCoreApplication::translate("statsMatch", "Match Statistique", nullptr));
    } // retranslateUi

};

namespace Ui {
    class statsMatch: public Ui_statsMatch {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STATSMATCH_H
