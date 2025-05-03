/********************************************************************************
** Form generated from reading UI file 'Main.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAIN_H
#define UI_MAIN_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QListWidget *menu;
    QListWidget *azer;
    QListWidget *aymen;
    QLabel *dashboard_2;
    QListWidget *listWidget;
    QListWidget *menu_2;
    QLabel *dashboard_6;
    QFrame *line;
    QFrame *line_2;
    QFrame *line_3;
    QLabel *label_2;
    QLabel *dashboard_7;
    QLabel *dashboard_3;
    QLabel *dashboard_4;
    QLabel *label_3;
    QLabel *label_4;
    QLineEdit *lineEdit;
    QLabel *label;
    QPushButton *pushButton;
    QListWidget *aymen_2;
    QListWidget *aymen_3;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1200, 800);
        MainWindow->setStyleSheet(QString::fromUtf8("background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 #1b1f2a, stop:1 #10131a);\n"
""));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        menu = new QListWidget(centralwidget);
        menu->setObjectName("menu");
        menu->setGeometry(QRect(20, 10, 1151, 71));
        menu->setStyleSheet(QString::fromUtf8("background: #192231;\n"
"color: #D3D3D3;\n"
"border-bottom: 2px solid #4C5C75;\n"
"\n"
"border-radius: 30px;\n"
"\n"
""));
        azer = new QListWidget(centralwidget);
        azer->setObjectName("azer");
        azer->setGeometry(QRect(20, 170, 261, 351));
        azer->setStyleSheet(QString::fromUtf8("background: #2E3B4E;\n"
"border: 1px solid #4C5C75;\n"
"\n"
"border-radius: 30px;\n"
"\n"
""));
        aymen = new QListWidget(centralwidget);
        aymen->setObjectName("aymen");
        aymen->setGeometry(QRect(890, 170, 291, 341));
        aymen->setStyleSheet(QString::fromUtf8("background: #2E3B4E;\n"
"border: 1px solid #4C5C75;\n"
"\n"
"border-radius: 30px;\n"
"\n"
""));
        dashboard_2 = new QLabel(centralwidget);
        dashboard_2->setObjectName("dashboard_2");
        dashboard_2->setGeometry(QRect(210, 30, 71, 31));
        QFont font;
        font.setFamilies({QString::fromUtf8("Franklin Gothic Book")});
        font.setPointSize(12);
        font.setWeight(QFont::Thin);
        dashboard_2->setFont(font);
        dashboard_2->setStyleSheet(QString::fromUtf8("background-color: transparent;\n"
"color: rgb(158, 158, 158);"));
        listWidget = new QListWidget(centralwidget);
        listWidget->setObjectName("listWidget");
        listWidget->setGeometry(QRect(60, 220, 181, 181));
        listWidget->setStyleSheet(QString::fromUtf8("border-radius: 90px;\n"
"background-color: qradialgradient(spread:pad, cx:0.5, cy:0.5, radius:0.5, fx:0.5, fy:0.5, stop:0 rgba(13, 27, 42, 255), stop:1 rgba(27, 38, 59, 255));"));
        menu_2 = new QListWidget(centralwidget);
        menu_2->setObjectName("menu_2");
        menu_2->setGeometry(QRect(20, 10, 111, 71));
        menu_2->setStyleSheet(QString::fromUtf8("background: #0A1628;\n"
"color: #FFFFFF;\n"
"border-bottom: 3px solid #00FF7F;\n"
"\n"
"border-radius: 30px;\n"
"\n"
""));
        dashboard_6 = new QLabel(centralwidget);
        dashboard_6->setObjectName("dashboard_6");
        dashboard_6->setGeometry(QRect(50, 410, 201, 31));
        QFont font1;
        font1.setFamilies({QString::fromUtf8("Sans Serif Collection")});
        font1.setPointSize(12);
        font1.setBold(true);
        dashboard_6->setFont(font1);
        dashboard_6->setStyleSheet(QString::fromUtf8("background-color: transparent;\n"
"    color: red;\n"
"    font-weight: bold;\n"
"    text-shadow: 0px 0px 8px rgba(255, 215, 0, 0.8); /* Gold glow */\n"
""));
        line = new QFrame(centralwidget);
        line->setObjectName("line");
        line->setGeometry(QRect(360, 10, 3, 61));
        line->setStyleSheet(QString::fromUtf8("color: rgb(40, 40, 40);\n"
"border: 2px solid #4C5C75;"));
        line->setFrameShape(QFrame::Shape::VLine);
        line->setFrameShadow(QFrame::Shadow::Sunken);
        line_2 = new QFrame(centralwidget);
        line_2->setObjectName("line_2");
        line_2->setGeometry(QRect(640, 10, 3, 61));
        line_2->setStyleSheet(QString::fromUtf8("border: 2px solid #4C5C75;"));
        line_2->setFrameShape(QFrame::Shape::VLine);
        line_2->setFrameShadow(QFrame::Shadow::Sunken);
        line_3 = new QFrame(centralwidget);
        line_3->setObjectName("line_3");
        line_3->setGeometry(QRect(880, 10, 3, 61));
        line_3->setStyleSheet(QString::fromUtf8("border: 2px solid #4C5C75;"));
        line_3->setFrameShape(QFrame::Shape::VLine);
        line_3->setFrameShadow(QFrame::Shadow::Sunken);
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(-50, 130, 441, 281));
        label_2->setStyleSheet(QString::fromUtf8("background-color: transparent;"));
        label_2->setPixmap(QPixmap(QString::fromUtf8("../../../../../../Downloads/Unazeaztitled-1.png")));
        label_2->setScaledContents(true);
        dashboard_7 = new QLabel(centralwidget);
        dashboard_7->setObjectName("dashboard_7");
        dashboard_7->setGeometry(QRect(460, 30, 131, 31));
        dashboard_7->setFont(font);
        dashboard_7->setStyleSheet(QString::fromUtf8("background-color: transparent;\n"
"color: rgb(158, 158, 158);"));
        dashboard_3 = new QLabel(centralwidget);
        dashboard_3->setObjectName("dashboard_3");
        dashboard_3->setGeometry(QRect(740, 30, 71, 31));
        dashboard_3->setFont(font);
        dashboard_3->setStyleSheet(QString::fromUtf8("background-color: transparent;\n"
"color: rgb(158, 158, 158);"));
        dashboard_4 = new QLabel(centralwidget);
        dashboard_4->setObjectName("dashboard_4");
        dashboard_4->setGeometry(QRect(960, 30, 61, 31));
        dashboard_4->setFont(font);
        dashboard_4->setStyleSheet(QString::fromUtf8("background-color: transparent;\n"
"color: rgb(158, 158, 158);"));
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(1110, 30, 40, 40));
        label_3->setStyleSheet(QString::fromUtf8("background-color: transparent;"));
        label_3->setPixmap(QPixmap(QString::fromUtf8("../../../../../Pictures/icons/user.png")));
        label_3->setScaledContents(true);
        label_4 = new QLabel(centralwidget);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(1120, 30, 40, 40));
        label_4->setStyleSheet(QString::fromUtf8("background-color:transparent;"));
        label_4->setPixmap(QPixmap(QString::fromUtf8("user.png")));
        label_4->setScaledContents(true);
        lineEdit = new QLineEdit(centralwidget);
        lineEdit->setObjectName("lineEdit");
        lineEdit->setGeometry(QRect(30, 410, 241, 31));
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setGeometry(QRect(50, 20, 50, 50));
        label->setPixmap(QPixmap(QString::fromUtf8("../../../../../Pictures/proj QT/logo football.png")));
        label->setScaledContents(true);
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(1110, 20, 51, 51));
        QFont font2;
        font2.setPointSize(11);
        pushButton->setFont(font2);
        pushButton->setStyleSheet(QString::fromUtf8("background-color: transparent;\n"
"border-radius: 5px;\n"
""));
        QIcon icon;
        icon.addFile(QString::fromUtf8("../../../../../Pictures/proj QT/Userr.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButton->setIcon(icon);
        pushButton->setIconSize(QSize(16, 16));
        aymen_2 = new QListWidget(centralwidget);
        aymen_2->setObjectName("aymen_2");
        aymen_2->setGeometry(QRect(330, 140, 521, 341));
        aymen_2->setStyleSheet(QString::fromUtf8("background: #2E3B4E;\n"
"border: 1px solid #4C5C75;\n"
"\n"
"border-radius: 30px;\n"
"\n"
""));
        aymen_3 = new QListWidget(centralwidget);
        aymen_3->setObjectName("aymen_3");
        aymen_3->setGeometry(QRect(290, 530, 591, 211));
        aymen_3->setStyleSheet(QString::fromUtf8("background: #2E3B4E;\n"
"border: 1px solid #4C5C75;\n"
"\n"
"border-radius: 30px;\n"
"\n"
""));
        MainWindow->setCentralWidget(centralwidget);
        menu->raise();
        azer->raise();
        aymen->raise();
        dashboard_2->raise();
        listWidget->raise();
        menu_2->raise();
        line->raise();
        line_2->raise();
        line_3->raise();
        label_2->raise();
        dashboard_7->raise();
        dashboard_3->raise();
        dashboard_4->raise();
        label_3->raise();
        label_4->raise();
        lineEdit->raise();
        dashboard_6->raise();
        label->raise();
        pushButton->raise();
        aymen_2->raise();
        aymen_3->raise();
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
        dashboard_6->setText(QCoreApplication::translate("MainWindow", "Player Of The Week", nullptr));
        label_2->setText(QString());
        dashboard_7->setText(QCoreApplication::translate("MainWindow", "Competition", nullptr));
        dashboard_3->setText(QCoreApplication::translate("MainWindow", "Match", nullptr));
        dashboard_4->setText(QCoreApplication::translate("MainWindow", "Team", nullptr));
        label_3->setText(QString());
        label_4->setText(QString());
        label->setText(QString());
        pushButton->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAIN_H
