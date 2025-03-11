/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCalendarWidget>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QListWidget *menu;
    QListWidget *menu_2;
    QFrame *line;
    QFrame *line_2;
    QFrame *line_3;
    QLabel *dashboard_2;
    QLabel *dashboard_7;
    QLabel *dashboard_3;
    QLabel *dashboard_4;
    QLabel *label_4;
    QFrame *frame;
    QLabel *label_2;
    QLineEdit *lineEdit;
    QComboBox *comboBox;
    QComboBox *comboBox_2;
    QCalendarWidget *calendarWidget;
    QListWidget *listWidget_2;
    QLabel *label_6;
    QLabel *label_7;
    QLabel *label_8;
    QLabel *label_3;
    QLabel *label_5;
    QPushButton *pushButton_3;
    QTableView *test;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1200, 800);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        centralwidget->setStyleSheet(QString::fromUtf8("background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 #1b1f2a, stop:1 #10131a);"));
        menu = new QListWidget(centralwidget);
        menu->setObjectName("menu");
        menu->setGeometry(QRect(20, 30, 1151, 71));
        menu->setStyleSheet(QString::fromUtf8("background: #192231;\n"
"color: #D3D3D3;\n"
"border-bottom: 2px solid #4C5C75;\n"
"border-radius: 30px;"));
        menu_2 = new QListWidget(centralwidget);
        menu_2->setObjectName("menu_2");
        menu_2->setGeometry(QRect(20, 30, 111, 71));
        menu_2->setStyleSheet(QString::fromUtf8("background: #0A1628;\n"
"color: #FFFFFF;\n"
"border-bottom: 3px solid #00FF7F;\n"
"border-radius: 30px;"));
        line = new QFrame(centralwidget);
        line->setObjectName("line");
        line->setGeometry(QRect(360, 30, 3, 61));
        line->setStyleSheet(QString::fromUtf8("border: 2px solid #4C5C75;"));
        line->setFrameShape(QFrame::Shape::VLine);
        line->setFrameShadow(QFrame::Shadow::Sunken);
        line_2 = new QFrame(centralwidget);
        line_2->setObjectName("line_2");
        line_2->setGeometry(QRect(640, 30, 3, 61));
        line_2->setStyleSheet(QString::fromUtf8("border: 2px solid #4C5C75;"));
        line_2->setFrameShape(QFrame::Shape::VLine);
        line_2->setFrameShadow(QFrame::Shadow::Sunken);
        line_3 = new QFrame(centralwidget);
        line_3->setObjectName("line_3");
        line_3->setGeometry(QRect(880, 30, 3, 61));
        line_3->setStyleSheet(QString::fromUtf8("border: 2px solid #4C5C75;"));
        line_3->setFrameShape(QFrame::Shape::VLine);
        line_3->setFrameShadow(QFrame::Shadow::Sunken);
        dashboard_2 = new QLabel(centralwidget);
        dashboard_2->setObjectName("dashboard_2");
        dashboard_2->setGeometry(QRect(210, 50, 71, 31));
        QFont font;
        font.setFamilies({QString::fromUtf8("Franklin Gothic Book")});
        font.setPointSize(15);
        dashboard_2->setFont(font);
        dashboard_2->setStyleSheet(QString::fromUtf8("background-color: transparent;\n"
"color: rgb(158, 158, 158);"));
        dashboard_7 = new QLabel(centralwidget);
        dashboard_7->setObjectName("dashboard_7");
        dashboard_7->setGeometry(QRect(460, 50, 131, 31));
        dashboard_7->setFont(font);
        dashboard_7->setStyleSheet(QString::fromUtf8("background-color: transparent;\n"
"color: rgb(158, 158, 158);"));
        dashboard_3 = new QLabel(centralwidget);
        dashboard_3->setObjectName("dashboard_3");
        dashboard_3->setGeometry(QRect(740, 50, 71, 31));
        dashboard_3->setFont(font);
        dashboard_3->setStyleSheet(QString::fromUtf8("background-color: transparent;\n"
"color: rgb(158, 158, 158);"));
        dashboard_4 = new QLabel(centralwidget);
        dashboard_4->setObjectName("dashboard_4");
        dashboard_4->setGeometry(QRect(960, 50, 61, 31));
        dashboard_4->setFont(font);
        dashboard_4->setStyleSheet(QString::fromUtf8("background-color: transparent;\n"
"color: rgb(158, 158, 158);"));
        label_4 = new QLabel(centralwidget);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(1120, 50, 40, 40));
        label_4->setStyleSheet(QString::fromUtf8("background-color: transparent;"));
        label_4->setPixmap(QPixmap(QString::fromUtf8("user.png")));
        label_4->setScaledContents(true);
        frame = new QFrame(centralwidget);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(40, 140, 591, 51));
        frame->setFrameShape(QFrame::Shape::StyledPanel);
        frame->setFrameShadow(QFrame::Shadow::Raised);
        label_2 = new QLabel(frame);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(10, 10, 41, 30));
        label_2->setStyleSheet(QString::fromUtf8("background-color: transparent;\n"
"border: 1px solid #aaaaaa;\n"
"border-radius: 5px;\n"
"padding: 6px 12px;"));
        label_2->setPixmap(QPixmap(QString::fromUtf8(":/images/search.png")));
        label_2->setScaledContents(true);
        lineEdit = new QLineEdit(frame);
        lineEdit->setObjectName("lineEdit");
        lineEdit->setGeometry(QRect(60, 10, 341, 31));
        lineEdit->setStyleSheet(QString::fromUtf8("background-color: #141821;\n"
"border: 2px solid #cccccc;\n"
"border-radius: 6px;\n"
"padding: 6px 10px;\n"
"font-size: 14px;\n"
"color: white;"));
        comboBox = new QComboBox(frame);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName("comboBox");
        comboBox->setGeometry(QRect(410, 10, 82, 28));
        comboBox_2 = new QComboBox(frame);
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->setObjectName("comboBox_2");
        comboBox_2->setGeometry(QRect(500, 10, 82, 28));
        calendarWidget = new QCalendarWidget(centralwidget);
        calendarWidget->setObjectName("calendarWidget");
        calendarWidget->setGeometry(QRect(760, 160, 400, 261));
        calendarWidget->setStyleSheet(QString::fromUtf8("background-color: #141821;\n"
"border-radius: 6px;\n"
"border: 1px solid #444444;\n"
"color: white;"));
        listWidget_2 = new QListWidget(centralwidget);
        listWidget_2->setObjectName("listWidget_2");
        listWidget_2->setGeometry(QRect(760, 470, 401, 261));
        listWidget_2->setStyleSheet(QString::fromUtf8("background-color: #141821;\n"
"border-radius: 6px;\n"
"padding: 10px;\n"
"border: 1px solid #666666;\n"
"font-size: 16px;\n"
"color: rgb(0, 216, 0);"));
        label_6 = new QLabel(centralwidget);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(870, 550, 191, 161));
        label_6->setPixmap(QPixmap(QString::fromUtf8(":/images/Downloads/BAR.png")));
        label_6->setScaledContents(true);
        label_7 = new QLabel(centralwidget);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(940, 500, 63, 20));
        QFont font1;
        font1.setPointSize(14);
        font1.setBold(true);
        label_7->setFont(font1);
        label_7->setStyleSheet(QString::fromUtf8("color: rgb(0, 193, 0);"));
        label_8 = new QLabel(centralwidget);
        label_8->setObjectName("label_8");
        label_8->setGeometry(QRect(780, 490, 91, 41));
        QFont font2;
        font2.setPointSize(16);
        font2.setBold(true);
        label_8->setFont(font2);
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(872, 549, 181, 161));
        label_3->setPixmap(QPixmap(QString::fromUtf8(":/images/BAR.png")));
        label_3->setScaledContents(true);
        label_5 = new QLabel(centralwidget);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(50, 40, 51, 51));
        label_5->setAutoFillBackground(false);
        label_5->setPixmap(QPixmap(QString::fromUtf8(":/images/logo football.png")));
        label_5->setScaledContents(true);
        pushButton_3 = new QPushButton(centralwidget);
        pushButton_3->setObjectName("pushButton_3");
        pushButton_3->setGeometry(QRect(40, 680, 80, 31));
        pushButton_3->setStyleSheet(QString::fromUtf8("background-color: #20242e;\n"
"color: white;\n"
"border-radius: 5px;\n"
"padding: 6px 12px;\n"
"border: 1px solid #666666;"));
        test = new QTableView(centralwidget);
        test->setObjectName("test");
        test->setGeometry(QRect(40, 210, 591, 451));
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(550, 680, 83, 29));
        pushButton_2 = new QPushButton(centralwidget);
        pushButton_2->setObjectName("pushButton_2");
        pushButton_2->setGeometry(QRect(450, 680, 83, 29));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1200, 25));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        dashboard_2->setText(QCoreApplication::translate("MainWindow", "Player", nullptr));
        dashboard_7->setText(QCoreApplication::translate("MainWindow", "Competition", nullptr));
        dashboard_3->setText(QCoreApplication::translate("MainWindow", "Match", nullptr));
        dashboard_4->setText(QCoreApplication::translate("MainWindow", "Team", nullptr));
        comboBox->setItemText(0, QCoreApplication::translate("MainWindow", "NULL", nullptr));
        comboBox->setItemText(1, QCoreApplication::translate("MainWindow", "By date", nullptr));
        comboBox->setItemText(2, QCoreApplication::translate("MainWindow", "By nb teams", nullptr));

        comboBox_2->setItemText(0, QCoreApplication::translate("MainWindow", "NULL", nullptr));
        comboBox_2->setItemText(1, QCoreApplication::translate("MainWindow", "League", nullptr));
        comboBox_2->setItemText(2, QCoreApplication::translate("MainWindow", "Tournement", nullptr));

        label_7->setText(QCoreApplication::translate("MainWindow", "86%", nullptr));
        label_8->setText(QCoreApplication::translate("MainWindow", "LaLiga", nullptr));
        label_3->setText(QString());
        label_5->setText(QString());
        pushButton_3->setText(QCoreApplication::translate("MainWindow", "Add", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "Delete", nullptr));
        pushButton_2->setText(QCoreApplication::translate("MainWindow", "Update", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
