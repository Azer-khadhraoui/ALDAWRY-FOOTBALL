/********************************************************************************
** Form generated from reading UI file 'chartMatch.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHARTMATCH_H
#define UI_CHARTMATCH_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_chartMatch
{
public:
    QComboBox *chartOptionComboBox;
    QWidget *goals_chart;

    void setupUi(QWidget *chartMatch)
    {
        if (chartMatch->objectName().isEmpty())
            chartMatch->setObjectName("chartMatch");
        chartMatch->resize(885, 590);
        chartMatch->setStyleSheet(QString::fromUtf8("background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 #1b1f2a, stop:1 #10131a);"));
        chartOptionComboBox = new QComboBox(chartMatch);
        chartOptionComboBox->addItem(QString());
        chartOptionComboBox->addItem(QString());
        chartOptionComboBox->setObjectName("chartOptionComboBox");
        chartOptionComboBox->setGeometry(QRect(12, 50, 231, 28));
        chartOptionComboBox->setStyleSheet(QString::fromUtf8("background-color: #1C1F2A;\n"
"border: 1px solid #2A2D3A;\n"
"border-radius: 5px;\n"
"padding: 5px;\n"
"color: white;\n"
"margin-left: 15px;\n"
"margin-right:15px;"));
        goals_chart = new QWidget(chartMatch);
        goals_chart->setObjectName("goals_chart");
        goals_chart->setGeometry(QRect(20, 90, 851, 481));
        goals_chart->setStyleSheet(QString::fromUtf8("/* Style for the QTableWidget */\n"
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

        retranslateUi(chartMatch);

        QMetaObject::connectSlotsByName(chartMatch);
    } // setupUi

    void retranslateUi(QWidget *chartMatch)
    {
        chartMatch->setWindowTitle(QCoreApplication::translate("chartMatch", "Form", nullptr));
        chartOptionComboBox->setItemText(0, QCoreApplication::translate("chartMatch", "Goals per Competition", nullptr));
        chartOptionComboBox->setItemText(1, QCoreApplication::translate("chartMatch", "Goals per Team", nullptr));

    } // retranslateUi

};

namespace Ui {
    class chartMatch: public Ui_chartMatch {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHARTMATCH_H
