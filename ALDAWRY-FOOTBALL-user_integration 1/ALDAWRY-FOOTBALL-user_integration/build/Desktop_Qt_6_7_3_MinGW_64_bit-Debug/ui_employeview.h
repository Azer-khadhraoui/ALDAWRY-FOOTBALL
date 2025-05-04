/********************************************************************************
** Form generated from reading UI file 'employeview.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EMPLOYEVIEW_H
#define UI_EMPLOYEVIEW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_EmployeeWindow
{
public:
    QWidget *centralwidget;
    QTabWidget *tabWidget;
    QWidget *tab_5;
    QWidget *statsWidget;
    QLabel *currentUserPhotoLabel;
    QWidget *widget_3;
    QPushButton *employeeButton;
    QPushButton *coachButton;
    QLabel *dashboard_7;
    QLabel *dashboard_3;
    QLabel *label_17;
    QLabel *dashboard_2;
    QLabel *label_18;
    QLabel *label_19;
    QLabel *label;
    QLabel *dashboard_4;
    QLabel *label_21;
    QLabel *dashboard_6;
    QLabel *label_22;
    QFrame *line;
    QPushButton *pushButton_4;
    QLabel *label_20;
    QLabel *label_23;
    QLabel *label_2;
    QPushButton *add_user;
    QFrame *line_2;
    QPushButton *pushButton;
    QPushButton *profileButton;
    QPushButton *teamButton;
    QLabel *dashboard_9;
    QLabel *dashboard_8;
    QPushButton *playerButton;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1920, 1080);
        MainWindow->setStyleSheet(QString::fromUtf8("background-color: #161A22;"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName("tabWidget");
        tabWidget->setGeometry(QRect(230, 570, 1671, 501));
        tabWidget->setStyleSheet(QString::fromUtf8("QTabWidget::pane {\n"
" background: linear-gradient(135deg, #0F111A 0%, #1A1C2A 100%);\n"
" border: 1px solid #2A2D3A;\n"
" border-radius: 10px;\n"
"}\n"
"QTabBar::tab {\n"
" background: #1E1F2D;\n"
" color: #B0BEC5;\n"
" padding: 10px 20px;\n"
" margin: 2px;\n"
" border-radius: 8px;\n"
" font-size: 14px;\n"
"}\n"
"QTabBar::tab:selected {\n"
" background: #0288D1;\n"
" color: #FFFFFF;\n"
"}\n"
"QTabBar::tab:hover {\n"
" background: #2A2D3A;\n"
"}"));
        tab_5 = new QWidget();
        tab_5->setObjectName("tab_5");
        statsWidget = new QWidget(tab_5);
        statsWidget->setObjectName("statsWidget");
        statsWidget->setGeometry(QRect(10, 10, 1621, 600));
        statsWidget->setStyleSheet(QString::fromUtf8("background: linear-gradient(135deg, #0F111A 0%, #1A1C2A 100%);\n"
"border-radius: 10px;"));
        tabWidget->addTab(tab_5, QString());
        currentUserPhotoLabel = new QLabel(centralwidget);
        currentUserPhotoLabel->setObjectName("currentUserPhotoLabel");
        currentUserPhotoLabel->setGeometry(QRect(1800, 30, 60, 60));
        currentUserPhotoLabel->setStyleSheet(QString::fromUtf8("background: #1E1F2D;\n"
"border: 1px solid #3A3D4A;\n"
"border-radius: 	30px;\n"
"box-shadow: 0 4px 10px rgba(0, 0, 0, 0.2);"));
        currentUserPhotoLabel->setScaledContents(true);
        widget_3 = new QWidget(centralwidget);
        widget_3->setObjectName("widget_3");
        widget_3->setGeometry(QRect(200, 120, 1851, 971));
        widget_3->setStyleSheet(QString::fromUtf8("background-color: #22252D;\n"
"border-radius:40px;\n"
"border: 1px solid #FFFFFF; /* Subtle blue-gray border */\n"
""));
        employeeButton = new QPushButton(widget_3);
        employeeButton->setObjectName("employeeButton");
        employeeButton->setGeometry(QRect(1130, 90, 200, 311));
        employeeButton->setStyleSheet(QString::fromUtf8("background-color: transparent;\n"
"border-radius: 5px; /* Slightly rounded corners for a modern look */"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/img/employee.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        employeeButton->setIcon(icon);
        employeeButton->setIconSize(QSize(500, 700));
        coachButton = new QPushButton(widget_3);
        coachButton->setObjectName("coachButton");
        coachButton->setGeometry(QRect(1470, 90, 200, 311));
        coachButton->setStyleSheet(QString::fromUtf8("background-color: transparent;\n"
"border-radius: 5px; /* Slightly rounded corners for a modern look */"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/img/COACH.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        coachButton->setIcon(icon1);
        coachButton->setIconSize(QSize(500, 700));
        dashboard_7 = new QLabel(centralwidget);
        dashboard_7->setObjectName("dashboard_7");
        dashboard_7->setGeometry(QRect(80, 420, 131, 31));
        QFont font;
        font.setFamilies({QString::fromUtf8("Franklin Gothic Book")});
        font.setPointSize(12);
        dashboard_7->setFont(font);
        dashboard_7->setStyleSheet(QString::fromUtf8("background-color: transparent;\n"
"color:#393C44;"));
        dashboard_3 = new QLabel(centralwidget);
        dashboard_3->setObjectName("dashboard_3");
        dashboard_3->setGeometry(QRect(80, 520, 71, 31));
        dashboard_3->setFont(font);
        dashboard_3->setStyleSheet(QString::fromUtf8("background-color: transparent;\n"
"color:#393C44;"));
        label_17 = new QLabel(centralwidget);
        label_17->setObjectName("label_17");
        label_17->setGeometry(QRect(30, 420, 27, 27));
        label_17->setStyleSheet(QString::fromUtf8("background-color: transparent;"));
        label_17->setPixmap(QPixmap(QString::fromUtf8(":/img/Vector.png")));
        label_17->setScaledContents(true);
        dashboard_2 = new QLabel(centralwidget);
        dashboard_2->setObjectName("dashboard_2");
        dashboard_2->setGeometry(QRect(80, 320, 71, 31));
        dashboard_2->setFont(font);
        dashboard_2->setStyleSheet(QString::fromUtf8("background-color: transparent;\n"
"color:#393C44;"));
        label_18 = new QLabel(centralwidget);
        label_18->setObjectName("label_18");
        label_18->setGeometry(QRect(30, 320, 35, 35));
        label_18->setStyleSheet(QString::fromUtf8("background-color: transparent;"));
        label_18->setPixmap(QPixmap(QString::fromUtf8(":/img/Group 1.png")));
        label_18->setScaledContents(true);
        label_19 = new QLabel(centralwidget);
        label_19->setObjectName("label_19");
        label_19->setGeometry(QRect(30, 520, 34, 32));
        label_19->setStyleSheet(QString::fromUtf8("background-color: transparent;"));
        label_19->setPixmap(QPixmap(QString::fromUtf8(":/img/Group 3.png")));
        label_19->setScaledContents(true);
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setGeometry(QRect(50, 30, 85, 85));
        label->setPixmap(QPixmap(QString::fromUtf8(":/img/logo_football.png")));
        label->setScaledContents(true);
        dashboard_4 = new QLabel(centralwidget);
        dashboard_4->setObjectName("dashboard_4");
        dashboard_4->setGeometry(QRect(80, 620, 71, 31));
        dashboard_4->setFont(font);
        dashboard_4->setStyleSheet(QString::fromUtf8("background-color: transparent;\n"
"color:#393C44;"));
        label_21 = new QLabel(centralwidget);
        label_21->setObjectName("label_21");
        label_21->setGeometry(QRect(30, 620, 28, 29));
        label_21->setStyleSheet(QString::fromUtf8("background-color: transparent;"));
        label_21->setPixmap(QPixmap(QString::fromUtf8(":/img/Group 2.png")));
        label_21->setScaledContents(true);
        dashboard_6 = new QLabel(centralwidget);
        dashboard_6->setObjectName("dashboard_6");
        dashboard_6->setGeometry(QRect(80, 920, 71, 31));
        dashboard_6->setFont(font);
        dashboard_6->setStyleSheet(QString::fromUtf8("background-color: transparent;\n"
"color:#393C44;"));
        label_22 = new QLabel(centralwidget);
        label_22->setObjectName("label_22");
        label_22->setGeometry(QRect(30, 920, 28, 29));
        label_22->setStyleSheet(QString::fromUtf8("background-color: transparent;"));
        label_22->setPixmap(QPixmap(QString::fromUtf8(":/img/logout.png")));
        label_22->setScaledContents(true);
        line = new QFrame(centralwidget);
        line->setObjectName("line");
        line->setGeometry(QRect(30, 790, 135, 1));
        line->setStyleSheet(QString::fromUtf8("background-color: #393C44;"));
        line->setFrameShape(QFrame::Shape::HLine);
        line->setFrameShadow(QFrame::Shadow::Sunken);
        pushButton_4 = new QPushButton(centralwidget);
        pushButton_4->setObjectName("pushButton_4");
        pushButton_4->setGeometry(QRect(1867, 60, 16, 10));
        pushButton_4->setStyleSheet(QString::fromUtf8("background-color: transparent;\n"
"border: 1px solid transparent ; /* Subtle border matching chart borders */\n"
""));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/img/Vectorrrr.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButton_4->setIcon(icon2);
        label_20 = new QLabel(centralwidget);
        label_20->setObjectName("label_20");
        label_20->setGeometry(QRect(300, 220, 471, 141));
        QFont font1;
        font1.setFamilies({QString::fromUtf8("Speedo")});
        font1.setPointSize(29);
        font1.setBold(true);
        label_20->setFont(font1);
        label_20->setStyleSheet(QString::fromUtf8("background-color: transparent;"));
        label_23 = new QLabel(centralwidget);
        label_23->setObjectName("label_23");
        label_23->setGeometry(QRect(300, 370, 561, 121));
        QFont font2;
        font2.setFamilies({QString::fromUtf8("Gill Sans Nova")});
        font2.setPointSize(21);
        font2.setBold(false);
        font2.setItalic(false);
        label_23->setFont(font2);
        label_23->setStyleSheet(QString::fromUtf8("background-color: transparent;\n"
"color: #B1B1B1;"));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(1030, 220, 140, 301));
        label_2->setStyleSheet(QString::fromUtf8("background-color: transparent;"));
        label_2->setPixmap(QPixmap(QString::fromUtf8(":/img/ADDBACKG.png")));
        label_2->setScaledContents(true);
        add_user = new QPushButton(centralwidget);
        add_user->setObjectName("add_user");
        add_user->setGeometry(QRect(1030, 230, 141, 281));
        add_user->setStyleSheet(QString::fromUtf8("background-color: transparent;\n"
"border-radius: 5px; /* Slightly rounded corners for a modern look */"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/img/ADDICON.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        add_user->setIcon(icon3);
        line_2 = new QFrame(centralwidget);
        line_2->setObjectName("line_2");
        line_2->setGeometry(QRect(1220, 200, 1, 351));
        line_2->setStyleSheet(QString::fromUtf8("background-color: rgb(168, 168, 168);"));
        line_2->setFrameShape(QFrame::Shape::VLine);
        line_2->setFrameShadow(QFrame::Shadow::Sunken);
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(20, 900, 121, 61));
        pushButton->setStyleSheet(QString::fromUtf8("background: linear-gradient(45deg, #0288D1 0%, #03A9F4 100%);\n"
"border-radius: 30px;\n"
"transition: background 0.3s, transform 0.2s;\n"
"}\n"
"QPushButton:hover {\n"
" background: linear-gradient(45deg, #03A9F4 0%, #4FC3F7 100%);\n"
" transform: scale(1.1);\n"
"}\n"
"QPushButton:pressed {\n"
" background: linear-gradient(45deg, #01579B 0%, #0288D1 100%);\n"
" transform: scale(0.9);\n"
"}"));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/images/logout.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButton->setIcon(icon4);
        pushButton->setIconSize(QSize(40, 40));
        profileButton = new QPushButton(centralwidget);
        profileButton->setObjectName("profileButton");
        profileButton->setGeometry(QRect(1800, 20, 71, 71));
        profileButton->setStyleSheet(QString::fromUtf8("background: linear-gradient(45deg, #0288D1 0%, #03A9F4 100%);\n"
"border-radius: 30px;\n"
"transition: background 0.3s, transform 0.2s;\n"
"}\n"
"QPushButton:hover {\n"
" background: linear-gradient(45deg, #03A9F4 0%, #4FC3F7 100%);\n"
" transform: scale(1.1);\n"
"}\n"
"QPushButton:pressed {\n"
" background: linear-gradient(45deg, #01579B 0%, #0288D1 100%);\n"
" transform: scale(0.9);\n"
"}"));
        profileButton->setIcon(icon4);
        profileButton->setIconSize(QSize(40, 40));
        teamButton = new QPushButton(centralwidget);
        teamButton->setObjectName("teamButton");
        teamButton->setGeometry(QRect(20, 610, 121, 61));
        teamButton->setStyleSheet(QString::fromUtf8("background: linear-gradient(45deg, #0288D1 0%, #03A9F4 100%);\n"
"border-radius: 30px;\n"
"transition: background 0.3s, transform 0.2s;\n"
"}\n"
"QPushButton:hover {\n"
" background: linear-gradient(45deg, #03A9F4 0%, #4FC3F7 100%);\n"
" transform: scale(1.1);\n"
"}\n"
"QPushButton:pressed {\n"
" background: linear-gradient(45deg, #01579B 0%, #0288D1 100%);\n"
" transform: scale(0.9);\n"
"}"));
        teamButton->setIcon(icon4);
        teamButton->setIconSize(QSize(40, 40));
        dashboard_9 = new QLabel(centralwidget);
        dashboard_9->setObjectName("dashboard_9");
        dashboard_9->setGeometry(QRect(1720, 60, 81, 31));
        QFont font3;
        font3.setFamilies({QString::fromUtf8("Franklin Gothic Book")});
        font3.setPointSize(12);
        font3.setBold(false);
        dashboard_9->setFont(font3);
        dashboard_9->setStyleSheet(QString::fromUtf8("background-color: transparent;\n"
"color:white;"));
        dashboard_8 = new QLabel(centralwidget);
        dashboard_8->setObjectName("dashboard_8");
        dashboard_8->setGeometry(QRect(1710, 40, 71, 31));
        dashboard_8->setFont(font);
        dashboard_8->setStyleSheet(QString::fromUtf8("background-color: transparent;\n"
"color:#393C44;"));
        playerButton = new QPushButton(centralwidget);
        playerButton->setObjectName("playerButton");
        playerButton->setGeometry(QRect(20, 300, 121, 61));
        playerButton->setStyleSheet(QString::fromUtf8("background: linear-gradient(45deg, #0288D1 0%, #03A9F4 100%);\n"
"border-radius: 30px;\n"
"transition: background 0.3s, transform 0.2s;\n"
"}\n"
"QPushButton:hover {\n"
" background: linear-gradient(45deg, #03A9F4 0%, #4FC3F7 100%);\n"
" transform: scale(1.1);\n"
"}\n"
"QPushButton:pressed {\n"
" background: linear-gradient(45deg, #01579B 0%, #0288D1 100%);\n"
" transform: scale(0.9);\n"
"}"));
        playerButton->setIcon(icon4);
        playerButton->setIconSize(QSize(40, 40));
        MainWindow->setCentralWidget(centralwidget);
        widget_3->raise();
        tabWidget->raise();
        currentUserPhotoLabel->raise();
        dashboard_7->raise();
        dashboard_3->raise();
        label_17->raise();
        dashboard_2->raise();
        label_18->raise();
        label_19->raise();
        label->raise();
        dashboard_4->raise();
        label_21->raise();
        dashboard_6->raise();
        label_22->raise();
        line->raise();
        pushButton_4->raise();
        label_20->raise();
        label_23->raise();
        label_2->raise();
        add_user->raise();
        line_2->raise();
        pushButton->raise();
        profileButton->raise();
        teamButton->raise();
        dashboard_9->raise();
        dashboard_8->raise();
        playerButton->raise();

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("EmployeeWindow", "MainWindow", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_5), QCoreApplication::translate("EmployeeWindow", "Stats", nullptr));
        currentUserPhotoLabel->setText(QString());
        employeeButton->setText(QString());
        coachButton->setText(QString());
        dashboard_7->setText(QCoreApplication::translate("EmployeeWindow", "Competition", nullptr));
        dashboard_3->setText(QCoreApplication::translate("EmployeeWindow", "Match", nullptr));
        label_17->setText(QString());
        dashboard_2->setText(QCoreApplication::translate("EmployeeWindow", "Player", nullptr));
        label_18->setText(QString());
        label_19->setText(QString());
        label->setText(QString());
        dashboard_4->setText(QCoreApplication::translate("EmployeeWindow", "Team", nullptr));
        label_21->setText(QString());
        dashboard_6->setText(QCoreApplication::translate("EmployeeWindow", "Log Out", nullptr));
        label_22->setText(QString());
        pushButton_4->setText(QString());
        label_20->setText(QCoreApplication::translate("EmployeeWindow", "Manage your\n"
"\n"
"users", nullptr));
        label_23->setText(QCoreApplication::translate("EmployeeWindow", "Add new users easily and assign roles : \n"
"Coach or Employee.", nullptr));
        label_2->setText(QString());
        add_user->setText(QString());
        pushButton->setText(QString());
        profileButton->setText(QString());
        teamButton->setText(QString());
        dashboard_9->setText(QCoreApplication::translate("EmployeeWindow", "User name", nullptr));
        dashboard_8->setText(QCoreApplication::translate("EmployeeWindow", "Role", nullptr));
        playerButton->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class EmployeeWindow: public Ui_EmployeeWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EMPLOYEVIEW_H
