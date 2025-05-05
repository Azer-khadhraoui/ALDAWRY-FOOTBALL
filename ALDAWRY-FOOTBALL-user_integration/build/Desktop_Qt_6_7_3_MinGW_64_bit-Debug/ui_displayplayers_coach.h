/********************************************************************************
** Form generated from reading UI file 'displayplayers_coach.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DISPLAYPLAYERS_COACH_H
#define UI_DISPLAYPLAYERS_COACH_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_displayplayers_coach
{
public:
    QTabWidget *tabWidget;
    QWidget *tab_4;
    QTableWidget *tableWidget;
    QFrame *formFrame;
    QFormLayout *formLayout;
    QComboBox *comboBoxTri;
    QLineEdit *lineEdit_10;
    QLabel *label_25;

    void setupUi(QWidget *displayplayers_coach)
    {
        if (displayplayers_coach->objectName().isEmpty())
            displayplayers_coach->setObjectName("displayplayers_coach");
        displayplayers_coach->resize(1683, 573);
        tabWidget = new QTabWidget(displayplayers_coach);
        tabWidget->setObjectName("tabWidget");
        tabWidget->setGeometry(QRect(0, 0, 1681, 571));
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
        tab_4 = new QWidget();
        tab_4->setObjectName("tab_4");
        tableWidget = new QTableWidget(tab_4);
        tableWidget->setObjectName("tableWidget");
        tableWidget->setGeometry(QRect(30, 90, 541, 411));
        tableWidget->setStyleSheet(QString::fromUtf8("/* Style for the tableWidget */\n"
"QTableWidget {\n"
"    background-color: #2D3748; /* Dark background matching the app */\n"
"    color: #FFFFFF; /* White text for readability */\n"
"    border: 1px solid #4A4E58; /* Subtle border matching button hover color */\n"
"    gridline-color: #4A4E58; /* Subtle grid lines */\n"
"}\n"
"\n"
"/* Style for table items */\n"
"QTableWidget::item {\n"
"    border: 1px solid #4A4E58; /* Subtle cell borders */\n"
"    padding: 5px; /* Spacing inside cells */\n"
"}\n"
"\n"
"/* Alternating row colors */\n"
"QTableWidget::item:nth-child(even) {\n"
"    background-color: #2D3748; /* Darker shade for even rows */\n"
"}\n"
"\n"
"QTableWidget::item:nth-child(odd) {\n"
"    background-color: #394252; /* Slightly lighter shade for odd rows */\n"
"}\n"
"\n"
"/* Hover effect for rows */\n"
"QTableWidget::item:hover {\n"
"    background-color: #4A4E58; /* Lighter shade on hover */\n"
"}\n"
"\n"
"/* Style for the header */\n"
"QHeaderView::section {\n"
"    background-color: #F5A623; /*"
                        " Accent color for header */\n"
"    color: #1A2633; /* Dark text for contrast */\n"
"    font-weight: bold; /* Bold header text */\n"
"    border: 1px solid #4A4E58; /* Border to match table */\n"
"    padding: 5px; /* Spacing inside header */\n"
"}\n"
"\n"
"/* Remove selection background */\n"
"QTableWidget::item:selected {\n"
"    background-color: #4A4E58; /* Same as hover to avoid clashing */\n"
"    color: #FFFFFF; /* Keep text white */\n"
"}"));
        formFrame = new QFrame(tab_4);
        formFrame->setObjectName("formFrame");
        formFrame->setGeometry(QRect(750, 30, 771, 471));
        formFrame->setFrameShape(QFrame::Shape::Box);
        formLayout = new QFormLayout(formFrame);
        formLayout->setObjectName("formLayout");
        comboBoxTri = new QComboBox(tab_4);
        comboBoxTri->setObjectName("comboBoxTri");
        comboBoxTri->setGeometry(QRect(440, 40, 111, 25));
        comboBoxTri->setStyleSheet(QString::fromUtf8("background-color: grey;\n"
"    border: 1px solid white; /* Subtle blue-gray border */\n"
"    border-radius: 15px;\n"
"color : black;\n"
""));
        lineEdit_10 = new QLineEdit(tab_4);
        lineEdit_10->setObjectName("lineEdit_10");
        lineEdit_10->setGeometry(QRect(70, 30, 361, 41));
        lineEdit_10->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"    border: 1px solid white; /* Subtle blue-gray border */\n"
"    border-radius: 15px;\n"
"color: rgb(24, 24, 24);\n"
""));
        label_25 = new QLabel(tab_4);
        label_25->setObjectName("label_25");
        label_25->setGeometry(QRect(40, 10, 44, 44));
        label_25->setStyleSheet(QString::fromUtf8("background-color: transparent;\n"
""));
        label_25->setPixmap(QPixmap(QString::fromUtf8(":/img/search.png")));
        label_25->setScaledContents(true);
        label_25->setIndent(-1);
        tabWidget->addTab(tab_4, QString());
        tableWidget->raise();
        formFrame->raise();
        lineEdit_10->raise();
        comboBoxTri->raise();
        label_25->raise();

        retranslateUi(displayplayers_coach);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(displayplayers_coach);
    } // setupUi

    void retranslateUi(QWidget *displayplayers_coach)
    {
        displayplayers_coach->setWindowTitle(QCoreApplication::translate("displayplayers_coach", "Form", nullptr));
        label_25->setText(QString());
        tabWidget->setTabText(tabWidget->indexOf(tab_4), QCoreApplication::translate("displayplayers_coach", "          Display Player           ", nullptr));
    } // retranslateUi

};

namespace Ui {
    class displayplayers_coach: public Ui_displayplayers_coach {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DISPLAYPLAYERS_COACH_H
