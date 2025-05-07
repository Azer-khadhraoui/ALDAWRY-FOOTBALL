/********************************************************************************
** Form generated from reading UI file 'displaymatch_coach.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DISPLAYMATCH_COACH_H
#define UI_DISPLAYMATCH_COACH_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_displaymatch_coach
{
public:
    QTabWidget *tabWidget;
    QWidget *tab;
    QTableView *allmatches;
    QLineEdit *search;
    QLabel *label_3;
    QWidget *line_up_widget;
    QComboBox *Line_up;
    QLabel *label_2;

    void setupUi(QWidget *displaymatch_coach)
    {
        if (displaymatch_coach->objectName().isEmpty())
            displaymatch_coach->setObjectName("displaymatch_coach");
        displaymatch_coach->resize(975, 667);
        displaymatch_coach->setStyleSheet(QString::fromUtf8("background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 #1b1f2a, stop:1 #10131a);"));
        tabWidget = new QTabWidget(displaymatch_coach);
        tabWidget->setObjectName("tabWidget");
        tabWidget->setGeometry(QRect(40, 20, 901, 621));
        tabWidget->setLayoutDirection(Qt::LayoutDirection::LeftToRight);
        tabWidget->setStyleSheet(QString::fromUtf8("QTabWidget::pane {\n"
"    border: 2px solid #2c2f3f;\n"
"    background: #1e1f29;\n"
"    border-radius: 5px;\n"
"}\n"
"\n"
"QTabBar::tab {\n"
"    background: #1e1f29;\n"
"    color: #ffffff;\n"
"    padding: 8px 16px;\n"
"    border: 1px solid #2c2f3f;\n"
"    border-top-left-radius: 5px;\n"
"    border-top-right-radius: 5px;\n"
"}\n"
"\n"
"QTabBar::tab:selected {\n"
"    background: #2c2f3f;\n"
"    color: #ffffff;\n"
"    font-weight: bold;\n"
"    border-bottom: 2px solid #0078d7;\n"
"}\n"
"\n"
"QTabBar::tab:hover {\n"
"    background: #323546;\n"
"    color: #ffffff;\n"
"}\n"
"\n"
"QTabBar::tab:!selected {\n"
"    margin-top: 2px;\n"
"}\n"
""));
        tab = new QWidget();
        tab->setObjectName("tab");
        allmatches = new QTableView(tab);
        allmatches->setObjectName("allmatches");
        allmatches->setGeometry(QRect(70, 70, 701, 381));
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
        search = new QLineEdit(tab);
        search->setObjectName("search");
        search->setGeometry(QRect(90, 30, 251, 31));
        search->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"    border: 1px solid white; /* Subtle blue-gray border */\n"
"    border-radius: 15px;\n"
"color: rgb(24, 24, 24);\n"
""));
        label_3 = new QLabel(tab);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(370, 10, 181, 41));
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
        tabWidget->addTab(tab, QString());
        line_up_widget = new QWidget();
        line_up_widget->setObjectName("line_up_widget");
        Line_up = new QComboBox(line_up_widget);
        Line_up->addItem(QString());
        Line_up->addItem(QString());
        Line_up->setObjectName("Line_up");
        Line_up->setGeometry(QRect(420, 120, 231, 28));
        Line_up->setMinimumSize(QSize(231, 28));
        Line_up->setStyleSheet(QString::fromUtf8("background-color: #1C1F2A;\n"
"border: 1px solid #2A2D3A;\n"
"border-radius: 5px;\n"
"padding: 5px;\n"
"color: white;\n"
"margin-left: 15px;\n"
"margin-right:15px;"));
        label_2 = new QLabel(line_up_widget);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(280, 10, 601, 551));
        label_2->setPixmap(QPixmap(QString::fromUtf8(":/matchimg/terrainnnn.png")));
        label_2->setScaledContents(true);
        tabWidget->addTab(line_up_widget, QString());

        retranslateUi(displaymatch_coach);

        tabWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(displaymatch_coach);
    } // setupUi

    void retranslateUi(QWidget *displaymatch_coach)
    {
        displaymatch_coach->setWindowTitle(QCoreApplication::translate("displaymatch_coach", "Form", nullptr));
        label_3->setText(QCoreApplication::translate("displaymatch_coach", "View Match", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QCoreApplication::translate("displaymatch_coach", "Page", nullptr));
        Line_up->setItemText(0, QCoreApplication::translate("displaymatch_coach", "4-3-3", nullptr));
        Line_up->setItemText(1, QCoreApplication::translate("displaymatch_coach", "4-4-2", nullptr));

        label_2->setText(QString());
        tabWidget->setTabText(tabWidget->indexOf(line_up_widget), QCoreApplication::translate("displaymatch_coach", "Line up", nullptr));
    } // retranslateUi

};

namespace Ui {
    class displaymatch_coach: public Ui_displaymatch_coach {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DISPLAYMATCH_COACH_H
