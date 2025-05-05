/********************************************************************************
** Form generated from reading UI file 'tableau.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TABLEAU_H
#define UI_TABLEAU_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Tableau
{
public:
    QTableWidget *tableWidget;
    QLineEdit *searchBar;
    QLabel *label;
    QPushButton *downloadButton;
    QPushButton *modifyButton;
    QPushButton *deleteButton;
    QWidget *widget;
    QLabel *label_2;
    QLabel *label_3;

    void setupUi(QWidget *Tableau)
    {
        if (Tableau->objectName().isEmpty())
            Tableau->setObjectName("Tableau");
        Tableau->resize(725, 644);
        Tableau->setStyleSheet(QString::fromUtf8("background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 #1b1f2a, stop:1 #10131a);"));
        tableWidget = new QTableWidget(Tableau);
        tableWidget->setObjectName("tableWidget");
        tableWidget->setGeometry(QRect(10, 160, 701, 391));
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
        searchBar = new QLineEdit(Tableau);
        searchBar->setObjectName("searchBar");
        searchBar->setGeometry(QRect(440, 110, 251, 31));
        searchBar->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"    border: 1px solid white; /* Subtle blue-gray border */\n"
"    border-radius: 15px;\n"
"color: rgb(24, 24, 24);\n"
""));
        label = new QLabel(Tableau);
        label->setObjectName("label");
        label->setGeometry(QRect(660, 100, 44, 44));
        label->setStyleSheet(QString::fromUtf8("background-color: transparent;\n"
""));
        label->setPixmap(QPixmap(QString::fromUtf8(":/img/search.png")));
        label->setScaledContents(true);
        label->setIndent(-1);
        downloadButton = new QPushButton(Tableau);
        downloadButton->setObjectName("downloadButton");
        downloadButton->setGeometry(QRect(550, 570, 50, 50));
        downloadButton->setStyleSheet(QString::fromUtf8("/* Style for the Modify button */\n"
"QPushButton#downloadButton {\n"
"	background-color: #2B2F37;\n"
"}\n"
"QPushButton#downloadButton:hover {\n"
"    background-color:#343842 ; /* Darker green on hover */\n"
"}\n"
"QPushButton#downloadButton:pressed {\n"
"    background-color: #1e2127; /* Even darker green when pressed */\n"
"}\n"
"    border: 1px solid white; /* Subtle blue-gray border */\n"
"    border-radius: 1px;"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/img/pdfIcon.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        downloadButton->setIcon(icon);
        downloadButton->setIconSize(QSize(30, 30));
        modifyButton = new QPushButton(Tableau);
        modifyButton->setObjectName("modifyButton");
        modifyButton->setGeometry(QRect(600, 570, 50, 50));
        modifyButton->setStyleSheet(QString::fromUtf8("/* Style for the Modify button */\n"
"QPushButton#modifyButton {\n"
"    background-color:#D8A353 ; /* Green to match the accent */\n"
"    color: #1A2633; /* Dark blue text */\n"
"\n"
"}\n"
"QPushButton#modifyButton:hover {\n"
"    background-color: #eeb35b; /* Darker green on hover */\n"
"}\n"
"QPushButton#modifyButton:pressed {\n"
"    background-color:#a37b3f ; /* Even darker green when pressed */\n"
"}\n"
"    border: 1px solid white; /* Subtle blue-gray border */\n"
"    border-radius: 1px;"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/img/editIcon.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        modifyButton->setIcon(icon1);
        modifyButton->setIconSize(QSize(20, 20));
        deleteButton = new QPushButton(Tableau);
        deleteButton->setObjectName("deleteButton");
        deleteButton->setGeometry(QRect(650, 570, 50, 50));
        deleteButton->setStyleSheet(QString::fromUtf8("/* Style for the Delete button */\n"
"QPushButton#deleteButton {\n"
"    background-color: #FF1414; /* Muted dark red */\n"
"    color: #E0E6ED; /* Light gray text */\n"
"\n"
"}\n"
"QPushButton#deleteButton:hover {\n"
"    background-color: #ff5d5d; /* Lighter red on hover */\n"
"}\n"
"QPushButton#deleteButton:pressed {\n"
"    background-color: #6A3A3A; /* Darker red when pressed */\n"
"}\n"
"    border: 1px solid white; /* Subtle blue-gray border */\n"
"    border-radius: 1px;"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/img/deleteIcon.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        deleteButton->setIcon(icon2);
        deleteButton->setIconSize(QSize(25, 25));
        widget = new QWidget(Tableau);
        widget->setObjectName("widget");
        widget->setGeometry(QRect(440, 570, 109, 50));
        widget->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        label_2 = new QLabel(widget);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(20, 20, 81, 16));
        label_2->setStyleSheet(QString::fromUtf8("color: rgb(184, 184, 184);"));
        label_3 = new QLabel(Tableau);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(280, 20, 171, 41));
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
        searchBar->raise();
        tableWidget->raise();
        label->raise();
        downloadButton->raise();
        modifyButton->raise();
        deleteButton->raise();
        widget->raise();
        label_3->raise();

        retranslateUi(Tableau);

        QMetaObject::connectSlotsByName(Tableau);
    } // setupUi

    void retranslateUi(QWidget *Tableau)
    {
        Tableau->setWindowTitle(QCoreApplication::translate("Tableau", "Form", nullptr));
        label->setText(QString());
        downloadButton->setText(QString());
        modifyButton->setText(QString());
        deleteButton->setText(QString());
        label_2->setText(QCoreApplication::translate("Tableau", "You can also ..", nullptr));
        label_3->setText(QCoreApplication::translate("Tableau", "Adjust Team", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Tableau: public Ui_Tableau {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TABLEAU_H
