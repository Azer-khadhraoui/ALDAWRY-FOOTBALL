/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QListWidget *menu;
    QListWidget *menu_2;
    QLabel *label;
    QLabel *dashboard_2;
    QLabel *dashboard_7;
    QLabel *dashboard_3;
    QLabel *dashboard_4;
    QLabel *label_17;
    QFrame *line;
    QFrame *line_2;
    QFrame *line_3;
    QPushButton *pushButton_5;
    QPushButton *pushButton_9;
    QPushButton *pushButton_8;
    QPushButton *pushButton_7;
    QPushButton *pushButton_6;
    QFrame *frame_6;
    QWidget *widget;
    QGridLayout *gridLayout_3;
    QLineEdit *lineEdit_3;
    QLabel *label_14;
    QLabel *label_9;
    QLabel *label_7;
    QLineEdit *lineEdit_9;
    QLabel *label_8;
    QLineEdit *lineEdit_5;
    QComboBox *comboBoxTeam;
    QToolButton *toolButton;
    QLabel *label_13;
    QDateEdit *dateEdit;
    QLabel *label_10;
    QPushButton *button1;
    QLineEdit *lineEdit_8;
    QLineEdit *lineEdit_4;
    QLabel *label_12;
    QLabel *label_11;
    QLabel *label_2;
    QTableWidget *tableWidget;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1200, 800);
        QFont font;
        font.setPointSize(10);
        MainWindow->setFont(font);
        MainWindow->setStyleSheet(QString::fromUtf8("background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 #1b1f2a, stop:1 #10131a);"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        menu = new QListWidget(centralwidget);
        menu->setObjectName("menu");
        menu->setGeometry(QRect(20, 20, 1151, 71));
        menu->setStyleSheet(QString::fromUtf8("background: #192231;\n"
"color: #D3D3D3;\n"
"border-bottom: 2px solid #4C5C75;\n"
"border-radius: 30px;"));
        menu_2 = new QListWidget(centralwidget);
        menu_2->setObjectName("menu_2");
        menu_2->setGeometry(QRect(20, 20, 111, 71));
        menu_2->setStyleSheet(QString::fromUtf8("background: #0A1628;\n"
"color: #FFFFFF;\n"
"border-bottom: 3px solid #00FF7F;\n"
"border-radius: 30px;"));
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setGeometry(QRect(50, 30, 50, 50));
        label->setPixmap(QPixmap(QString::fromUtf8("../../../../../Pictures/proj QT/logo football.png")));
        label->setScaledContents(true);
        dashboard_2 = new QLabel(centralwidget);
        dashboard_2->setObjectName("dashboard_2");
        dashboard_2->setGeometry(QRect(210, 40, 71, 31));
        QFont font1;
        font1.setFamilies({QString::fromUtf8("Franklin Gothic Book")});
        font1.setPointSize(12);
        font1.setWeight(QFont::Thin);
        dashboard_2->setFont(font1);
        dashboard_2->setStyleSheet(QString::fromUtf8("background-color: transparent;\n"
"color: rgb(255, 255, 255);"));
        dashboard_7 = new QLabel(centralwidget);
        dashboard_7->setObjectName("dashboard_7");
        dashboard_7->setGeometry(QRect(460, 40, 131, 31));
        dashboard_7->setFont(font1);
        dashboard_7->setStyleSheet(QString::fromUtf8("background-color: transparent;\n"
"color: rgb(158, 158, 158);"));
        dashboard_3 = new QLabel(centralwidget);
        dashboard_3->setObjectName("dashboard_3");
        dashboard_3->setGeometry(QRect(740, 40, 71, 31));
        dashboard_3->setFont(font1);
        dashboard_3->setStyleSheet(QString::fromUtf8("background-color: transparent;\n"
"color: rgb(158, 158, 158);"));
        dashboard_4 = new QLabel(centralwidget);
        dashboard_4->setObjectName("dashboard_4");
        dashboard_4->setGeometry(QRect(960, 40, 61, 31));
        dashboard_4->setFont(font1);
        dashboard_4->setStyleSheet(QString::fromUtf8("background-color: transparent;\n"
"color: rgb(158, 158, 158);"));
        label_17 = new QLabel(centralwidget);
        label_17->setObjectName("label_17");
        label_17->setGeometry(QRect(1110, 40, 30, 30));
        label_17->setStyleSheet(QString::fromUtf8("background-color:transparent;"));
        label_17->setPixmap(QPixmap(QString::fromUtf8("../../../../../Pictures/proj QT/user.png")));
        label_17->setScaledContents(true);
        line = new QFrame(centralwidget);
        line->setObjectName("line");
        line->setGeometry(QRect(360, 20, 3, 61));
        line->setStyleSheet(QString::fromUtf8("color: rgb(40, 40, 40);\n"
"border: 2px solid #4C5C75;"));
        line->setFrameShape(QFrame::Shape::VLine);
        line->setFrameShadow(QFrame::Shadow::Sunken);
        line_2 = new QFrame(centralwidget);
        line_2->setObjectName("line_2");
        line_2->setGeometry(QRect(640, 20, 3, 61));
        line_2->setStyleSheet(QString::fromUtf8("border: 2px solid #4C5C75;"));
        line_2->setFrameShape(QFrame::Shape::VLine);
        line_2->setFrameShadow(QFrame::Shadow::Sunken);
        line_3 = new QFrame(centralwidget);
        line_3->setObjectName("line_3");
        line_3->setGeometry(QRect(880, 20, 3, 61));
        line_3->setStyleSheet(QString::fromUtf8("border: 2px solid #4C5C75;"));
        line_3->setFrameShape(QFrame::Shape::VLine);
        line_3->setFrameShadow(QFrame::Shadow::Sunken);
        pushButton_5 = new QPushButton(centralwidget);
        pushButton_5->setObjectName("pushButton_5");
        pushButton_5->setGeometry(QRect(40, 120, 122, 34));
        pushButton_5->setStyleSheet(QString::fromUtf8("background-color: #2C2F3F;\n"
"color: white;\n"
"font-size: 14px;\n"
"font-weight: bold;\n"
"border: 1px solid #5A5F69;\n"
"border-radius: 6px;\n"
"padding: 8px 15px;\n"
"min-width: 90px;\n"
"transition: all 0.3s ease-in-out;"));
        pushButton_9 = new QPushButton(centralwidget);
        pushButton_9->setObjectName("pushButton_9");
        pushButton_9->setGeometry(QRect(160, 120, 122, 34));
        pushButton_9->setStyleSheet(QString::fromUtf8("background-color: #2C2F3F;\n"
"color: white;\n"
"font-size: 14px;\n"
"font-weight: bold;\n"
"border: 1px solid #5A5F69;\n"
"border-radius: 6px;\n"
"padding: 8px 15px;\n"
"min-width: 90px;\n"
"transition: all 0.3s ease-in-out;"));
        pushButton_8 = new QPushButton(centralwidget);
        pushButton_8->setObjectName("pushButton_8");
        pushButton_8->setGeometry(QRect(280, 120, 122, 34));
        pushButton_8->setStyleSheet(QString::fromUtf8("background-color: #2C2F3F;\n"
"color: white;\n"
"font-size: 14px;\n"
"font-weight: bold;\n"
"border: 1px solid #5A5F69;\n"
"border-radius: 6px;\n"
"padding: 8px 15px;\n"
"min-width: 90px;\n"
"transition: all 0.3s ease-in-out;"));
        pushButton_7 = new QPushButton(centralwidget);
        pushButton_7->setObjectName("pushButton_7");
        pushButton_7->setGeometry(QRect(400, 120, 122, 34));
        pushButton_7->setStyleSheet(QString::fromUtf8("background-color: #2C2F3F;\n"
"color: white;\n"
"font-size: 14px;\n"
"font-weight: bold;\n"
"border: 1px solid #5A5F69;\n"
"border-radius: 6px;\n"
"padding: 8px 15px;\n"
"min-width: 90px;\n"
"transition: all 0.3s ease-in-out;"));
        pushButton_6 = new QPushButton(centralwidget);
        pushButton_6->setObjectName("pushButton_6");
        pushButton_6->setGeometry(QRect(520, 120, 122, 34));
        pushButton_6->setStyleSheet(QString::fromUtf8("background-color: #2C2F3F;\n"
"color: white;\n"
"font-size: 14px;\n"
"font-weight: bold;\n"
"border: 1px solid #5A5F69;\n"
"border-radius: 6px;\n"
"padding: 8px 15px;\n"
"min-width: 90px;\n"
"transition: all 0.3s ease-in-out;"));
        frame_6 = new QFrame(centralwidget);
        frame_6->setObjectName("frame_6");
        frame_6->setGeometry(QRect(20, 140, 631, 641));
        frame_6->setFrameShape(QFrame::Shape::StyledPanel);
        frame_6->setFrameShadow(QFrame::Shadow::Raised);
        widget = new QWidget(frame_6);
        widget->setObjectName("widget");
        widget->setGeometry(QRect(0, 10, 631, 641));
        widget->setStyleSheet(QString::fromUtf8("background-color: #0F111A;\n"
"color: #FFFFFF;\n"
"font-family: 'Segoe UI', Arial, sans-serif;\n"
"font-size: 12px;\n"
"border-radius: 15px;\n"
"padding: 15px;"));
        gridLayout_3 = new QGridLayout(widget);
        gridLayout_3->setObjectName("gridLayout_3");
        lineEdit_3 = new QLineEdit(widget);
        lineEdit_3->setObjectName("lineEdit_3");
        lineEdit_3->setStyleSheet(QString::fromUtf8("background-color: #1C1F2A;\n"
"border: 1px solid #2A2D3A;\n"
"border-radius: 5px;\n"
"padding: 5px;\n"
"color: white;\n"
"margin-left: 15px;\n"
"margin-right:15px;"));

        gridLayout_3->addWidget(lineEdit_3, 1, 0, 1, 1);

        label_14 = new QLabel(widget);
        label_14->setObjectName("label_14");
        label_14->setStyleSheet(QString::fromUtf8("color: #A0A8B7;\n"
"font-weight: bold;\n"
"padding-bottom: 5px;background-color:transparent;"));

        gridLayout_3->addWidget(label_14, 15, 0, 1, 1);

        label_9 = new QLabel(widget);
        label_9->setObjectName("label_9");
        label_9->setStyleSheet(QString::fromUtf8("color: #A0A8B7;\n"
"font-weight: bold;\n"
"padding-bottom: 5px;background-color:transparent;"));

        gridLayout_3->addWidget(label_9, 6, 0, 1, 1);

        label_7 = new QLabel(widget);
        label_7->setObjectName("label_7");
        label_7->setStyleSheet(QString::fromUtf8("color: #A0A8B7;\n"
"font-weight: bold;\n"
"padding-bottom: 5px;background-color:transparent;"));

        gridLayout_3->addWidget(label_7, 0, 0, 1, 1);

        lineEdit_9 = new QLineEdit(widget);
        lineEdit_9->setObjectName("lineEdit_9");
        lineEdit_9->setStyleSheet(QString::fromUtf8("background-color: #1C1F2A;\n"
"border: 1px solid #2A2D3A;\n"
"border-radius: 5px;\n"
"padding: 5px;\n"
"color: white;\n"
"margin-left: 15px;\n"
"margin-right:15px;"));

        gridLayout_3->addWidget(lineEdit_9, 14, 0, 1, 1);

        label_8 = new QLabel(widget);
        label_8->setObjectName("label_8");
        label_8->setStyleSheet(QString::fromUtf8("color: #A0A8B7;\n"
"font-weight: bold;\n"
"padding-bottom: 5px;background-color:transparent;"));

        gridLayout_3->addWidget(label_8, 2, 0, 1, 1);

        lineEdit_5 = new QLineEdit(widget);
        lineEdit_5->setObjectName("lineEdit_5");
        lineEdit_5->setStyleSheet(QString::fromUtf8("background-color: #1C1F2A;\n"
"border: 1px solid #2A2D3A;\n"
"border-radius: 5px;\n"
"padding: 5px;\n"
"color: white;\n"
"margin-left: 15px;\n"
"margin-right:15px;"));

        gridLayout_3->addWidget(lineEdit_5, 10, 0, 1, 1);

        comboBoxTeam = new QComboBox(widget);
        comboBoxTeam->setObjectName("comboBoxTeam");

        gridLayout_3->addWidget(comboBoxTeam, 8, 0, 1, 1);

        toolButton = new QToolButton(widget);
        toolButton->setObjectName("toolButton");
        toolButton->setStyleSheet(QString::fromUtf8("background-color: #1C1F2A;\n"
"border: 1px solid #2A2D3A;\n"
"border-radius: 5px;\n"
"padding: 3px;\n"
"color: white;\n"
"margin-left: 15px;\n"
"margin-right:15px;\n"
"margin-bottom:15px;"));

        gridLayout_3->addWidget(toolButton, 18, 0, 1, 1);

        label_13 = new QLabel(widget);
        label_13->setObjectName("label_13");
        label_13->setStyleSheet(QString::fromUtf8("color: #A0A8B7;\n"
"font-weight: bold;\n"
"padding-bottom: 5px;background-color:transparent;"));

        gridLayout_3->addWidget(label_13, 13, 0, 1, 1);

        dateEdit = new QDateEdit(widget);
        dateEdit->setObjectName("dateEdit");
        dateEdit->setStyleSheet(QString::fromUtf8("background-color: #1C1F2A;\n"
"border: 1px solid #2A2D3A;\n"
"border-radius: 5px;\n"
"padding: 5px;\n"
"color: white;\n"
"margin-left: 15px;\n"
"margin-right:15px;"));

        gridLayout_3->addWidget(dateEdit, 5, 0, 1, 1);

        label_10 = new QLabel(widget);
        label_10->setObjectName("label_10");
        label_10->setStyleSheet(QString::fromUtf8("color: #A0A8B7;\n"
"font-weight: bold;\n"
"padding-bottom: 5px;background-color:transparent;"));

        gridLayout_3->addWidget(label_10, 9, 0, 1, 1);

        button1 = new QPushButton(widget);
        button1->setObjectName("button1");
        button1->setStyleSheet(QString::fromUtf8("background-color: rgba(50, 150, 250, 0.8);\n"
"color: white;\n"
"font-size: 12px;\n"
"border-radius: 5px;\n"
"padding: 6px 12px;\n"
"margin-left:500px;\n"
"margin-right:20px;\n"
"margin-bottom:10px;"));

        gridLayout_3->addWidget(button1, 19, 0, 1, 1);

        lineEdit_8 = new QLineEdit(widget);
        lineEdit_8->setObjectName("lineEdit_8");
        lineEdit_8->setStyleSheet(QString::fromUtf8("background-color: #1C1F2A;\n"
"border: 1px solid #2A2D3A;\n"
"border-radius: 5px;\n"
"padding: 5px;\n"
"color: white;\n"
"margin-left: 15px;\n"
"margin-right:15px;"));

        gridLayout_3->addWidget(lineEdit_8, 12, 0, 1, 1);

        lineEdit_4 = new QLineEdit(widget);
        lineEdit_4->setObjectName("lineEdit_4");
        lineEdit_4->setStyleSheet(QString::fromUtf8("background-color: #1C1F2A;\n"
"border: 1px solid #2A2D3A;\n"
"border-radius: 5px;\n"
"padding: 5px;\n"
"color: white;\n"
"margin-left: 15px;\n"
"margin-right:15px;"));

        gridLayout_3->addWidget(lineEdit_4, 3, 0, 1, 1);

        label_12 = new QLabel(widget);
        label_12->setObjectName("label_12");
        label_12->setStyleSheet(QString::fromUtf8("color: #A0A8B7;\n"
"font-weight: bold;\n"
"padding-bottom: 5px;background-color:transparent;"));

        gridLayout_3->addWidget(label_12, 4, 0, 1, 1);

        label_11 = new QLabel(widget);
        label_11->setObjectName("label_11");
        label_11->setStyleSheet(QString::fromUtf8("color: #A0A8B7;\n"
"font-weight: bold;\n"
"padding-bottom: 5px;background-color:transparent;"));

        gridLayout_3->addWidget(label_11, 11, 0, 1, 1);

        label_2 = new QLabel(centralwidget);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(740, 100, 341, 161));
        tableWidget = new QTableWidget(centralwidget);
        tableWidget->setObjectName("tableWidget");
        tableWidget->setGeometry(QRect(660, 290, 531, 451));
        MainWindow->setCentralWidget(centralwidget);
        menu->raise();
        menu_2->raise();
        label->raise();
        dashboard_2->raise();
        dashboard_7->raise();
        dashboard_3->raise();
        dashboard_4->raise();
        label_17->raise();
        line->raise();
        line_2->raise();
        line_3->raise();
        frame_6->raise();
        pushButton_5->raise();
        pushButton_9->raise();
        pushButton_6->raise();
        pushButton_8->raise();
        pushButton_7->raise();
        label_2->raise();
        tableWidget->raise();
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        label->setText(QString());
        dashboard_2->setText(QCoreApplication::translate("MainWindow", "Player", nullptr));
        dashboard_7->setText(QCoreApplication::translate("MainWindow", "Competition", nullptr));
        dashboard_3->setText(QCoreApplication::translate("MainWindow", "Match", nullptr));
        dashboard_4->setText(QCoreApplication::translate("MainWindow", "Team", nullptr));
        label_17->setText(QString());
        pushButton_5->setText(QCoreApplication::translate("MainWindow", "Add", nullptr));
        pushButton_9->setText(QCoreApplication::translate("MainWindow", "Display", nullptr));
        pushButton_8->setText(QCoreApplication::translate("MainWindow", "Modify", nullptr));
        pushButton_7->setText(QCoreApplication::translate("MainWindow", "Delete", nullptr));
        pushButton_6->setText(QCoreApplication::translate("MainWindow", "Stats", nullptr));
        label_14->setText(QCoreApplication::translate("MainWindow", "Insert player photo", nullptr));
        label_9->setText(QCoreApplication::translate("MainWindow", "Team", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "First_Name", nullptr));
        label_8->setText(QCoreApplication::translate("MainWindow", "Last_Name", nullptr));
        toolButton->setText(QCoreApplication::translate("MainWindow", "...", nullptr));
        label_13->setText(QCoreApplication::translate("MainWindow", "Nationality", nullptr));
        label_10->setText(QCoreApplication::translate("MainWindow", "Position", nullptr));
        button1->setText(QCoreApplication::translate("MainWindow", "Confirm", nullptr));
        label_12->setText(QCoreApplication::translate("MainWindow", "Date_Of_Birth", nullptr));
        label_11->setText(QCoreApplication::translate("MainWindow", "Jersey_Nb", nullptr));
        label_2->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
