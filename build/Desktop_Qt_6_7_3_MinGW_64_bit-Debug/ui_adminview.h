/********************************************************************************
** Form generated from reading UI file 'adminview.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADMINVIEW_H
#define UI_ADMINVIEW_H

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

class Ui_AdminWindow
{
public:
    QWidget *centralwidget;
    QTabWidget *tabWidget;
    QWidget *tab_5;
    QWidget *statsWidget;
    QLabel *currentUserPhotoLabel;
    QWidget *widget_3;
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
    QPushButton *adminButton;
    QPushButton *coachButton;
    QPushButton *employeeButton;
    QFrame *line_2;
    QPushButton *logout;
    QPushButton *profileButton;
    QPushButton *teamButton;
    QLabel *dashboard_9;
    QLabel *dashboard_8;
    QPushButton *playerButton;
    QPushButton *compButton;
    QPushButton *matchButton;
    QLabel *label_13;
    QLabel *dashboard_5;
    QPushButton *aboutButton;

    void setupUi(QMainWindow *AdminWindow)
    {
        if (AdminWindow->objectName().isEmpty())
            AdminWindow->setObjectName("AdminWindow");
        AdminWindow->resize(1920, 1080);
        AdminWindow->setStyleSheet(QString::fromUtf8("background-color: #161A22;"));
        centralwidget = new QWidget(AdminWindow);
        centralwidget->setObjectName("centralwidget");
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName("tabWidget");
        tabWidget->setGeometry(QRect(230, 576, 1671, 441));
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
        currentUserPhotoLabel->setGeometry(QRect(1800, 36, 60, 60));
        currentUserPhotoLabel->setStyleSheet(QString::fromUtf8("background: #1E1F2D;\n"
"border: 1px solid #3A3D4A;\n"
"border-radius: 	30px;\n"
"box-shadow: 0 4px 10px rgba(0, 0, 0, 0.2);"));
        currentUserPhotoLabel->setScaledContents(true);
        widget_3 = new QWidget(centralwidget);
        widget_3->setObjectName("widget_3");
        widget_3->setGeometry(QRect(200, 125, 1851, 971));
        widget_3->setStyleSheet(QString::fromUtf8("background-color: #22252D;\n"
"border-radius:40px;\n"
"border: 1px solid #FFFFFF; /* Subtle blue-gray border */\n"
""));
        dashboard_7 = new QLabel(centralwidget);
        dashboard_7->setObjectName("dashboard_7");
        dashboard_7->setGeometry(QRect(80, 426, 131, 31));
        QFont font;
        font.setFamilies({QString::fromUtf8("Franklin Gothic Book")});
        font.setPointSize(12);
        dashboard_7->setFont(font);
        dashboard_7->setStyleSheet(QString::fromUtf8("background-color: transparent;\n"
"color:#393C44;"));
        dashboard_3 = new QLabel(centralwidget);
        dashboard_3->setObjectName("dashboard_3");
        dashboard_3->setGeometry(QRect(80, 526, 71, 31));
        dashboard_3->setFont(font);
        dashboard_3->setStyleSheet(QString::fromUtf8("background-color: transparent;\n"
"color:#393C44;"));
        label_17 = new QLabel(centralwidget);
        label_17->setObjectName("label_17");
        label_17->setGeometry(QRect(30, 426, 27, 27));
        label_17->setStyleSheet(QString::fromUtf8("background-color: transparent;"));
        label_17->setPixmap(QPixmap(QString::fromUtf8(":/img/Vector.png")));
        label_17->setScaledContents(true);
        dashboard_2 = new QLabel(centralwidget);
        dashboard_2->setObjectName("dashboard_2");
        dashboard_2->setGeometry(QRect(80, 326, 71, 31));
        dashboard_2->setFont(font);
        dashboard_2->setStyleSheet(QString::fromUtf8("background-color: transparent;\n"
"color:#393C44;"));
        label_18 = new QLabel(centralwidget);
        label_18->setObjectName("label_18");
        label_18->setGeometry(QRect(30, 326, 35, 35));
        label_18->setStyleSheet(QString::fromUtf8("background-color: transparent;"));
        label_18->setPixmap(QPixmap(QString::fromUtf8(":/img/Group 1.png")));
        label_18->setScaledContents(true);
        label_19 = new QLabel(centralwidget);
        label_19->setObjectName("label_19");
        label_19->setGeometry(QRect(30, 526, 34, 32));
        label_19->setStyleSheet(QString::fromUtf8("background-color: transparent;"));
        label_19->setPixmap(QPixmap(QString::fromUtf8(":/img/Group 3.png")));
        label_19->setScaledContents(true);
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setGeometry(QRect(50, 36, 85, 85));
        label->setPixmap(QPixmap(QString::fromUtf8(":/img/logo_football.png")));
        label->setScaledContents(true);
        dashboard_4 = new QLabel(centralwidget);
        dashboard_4->setObjectName("dashboard_4");
        dashboard_4->setGeometry(QRect(80, 626, 71, 31));
        dashboard_4->setFont(font);
        dashboard_4->setStyleSheet(QString::fromUtf8("background-color: transparent;\n"
"color:#393C44;"));
        label_21 = new QLabel(centralwidget);
        label_21->setObjectName("label_21");
        label_21->setGeometry(QRect(30, 626, 28, 29));
        label_21->setStyleSheet(QString::fromUtf8("background-color: transparent;"));
        label_21->setPixmap(QPixmap(QString::fromUtf8(":/teamimg/Group 2.png")));
        label_21->setScaledContents(true);
        dashboard_6 = new QLabel(centralwidget);
        dashboard_6->setObjectName("dashboard_6");
        dashboard_6->setGeometry(QRect(80, 926, 71, 31));
        dashboard_6->setFont(font);
        dashboard_6->setStyleSheet(QString::fromUtf8("background-color: transparent;\n"
"color: rgb(158, 158, 158);"));
        label_22 = new QLabel(centralwidget);
        label_22->setObjectName("label_22");
        label_22->setGeometry(QRect(30, 926, 28, 29));
        label_22->setStyleSheet(QString::fromUtf8("background-color: transparent;"));
        label_22->setPixmap(QPixmap(QString::fromUtf8(":/img/logout.png")));
        label_22->setScaledContents(true);
        line = new QFrame(centralwidget);
        line->setObjectName("line");
        line->setGeometry(QRect(30, 796, 135, 1));
        line->setStyleSheet(QString::fromUtf8("background-color: #393C44;"));
        line->setFrameShape(QFrame::Shape::HLine);
        line->setFrameShadow(QFrame::Shadow::Sunken);
        pushButton_4 = new QPushButton(centralwidget);
        pushButton_4->setObjectName("pushButton_4");
        pushButton_4->setGeometry(QRect(1870, 66, 16, 10));
        pushButton_4->setStyleSheet(QString::fromUtf8("background-color: transparent;\n"
"border: 1px solid transparent ; /* Subtle border matching chart borders */\n"
""));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/img/Vectorrrr.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButton_4->setIcon(icon);
        label_20 = new QLabel(centralwidget);
        label_20->setObjectName("label_20");
        label_20->setGeometry(QRect(300, 236, 471, 121));
        QFont font1;
        font1.setFamilies({QString::fromUtf8("Speedo")});
        font1.setPointSize(29);
        font1.setBold(true);
        label_20->setFont(font1);
        label_20->setStyleSheet(QString::fromUtf8("background-color: transparent;"));
        label_23 = new QLabel(centralwidget);
        label_23->setObjectName("label_23");
        label_23->setGeometry(QRect(300, 376, 561, 121));
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
        label_2->setGeometry(QRect(1030, 206, 140, 350));
        label_2->setStyleSheet(QString::fromUtf8("background-color: transparent;"));
        label_2->setPixmap(QPixmap(QString::fromUtf8(":/img/ADDBACKG.png")));
        label_2->setScaledContents(true);
        add_user = new QPushButton(centralwidget);
        add_user->setObjectName("add_user");
        add_user->setGeometry(QRect(1030, 206, 141, 341));
        add_user->setStyleSheet(QString::fromUtf8("background-color: transparent;\n"
"border-radius: 5px; /* Slightly rounded corners for a modern look */"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/img/ADDICON.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        add_user->setIcon(icon1);
        adminButton = new QPushButton(centralwidget);
        adminButton->setObjectName("adminButton");
        adminButton->setGeometry(QRect(1280, 216, 200, 341));
        adminButton->setStyleSheet(QString::fromUtf8("background-color: transparent;\n"
"border-radius: 5px; /* Slightly rounded corners for a modern look */"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/img/ADMIN.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        adminButton->setIcon(icon2);
        adminButton->setIconSize(QSize(500, 700));
        coachButton = new QPushButton(centralwidget);
        coachButton->setObjectName("coachButton");
        coachButton->setGeometry(QRect(1490, 216, 200, 341));
        coachButton->setStyleSheet(QString::fromUtf8("background-color: transparent;\n"
"border-radius: 5px; /* Slightly rounded corners for a modern look */"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/img/COACH.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        coachButton->setIcon(icon3);
        coachButton->setIconSize(QSize(500, 700));
        employeeButton = new QPushButton(centralwidget);
        employeeButton->setObjectName("employeeButton");
        employeeButton->setGeometry(QRect(1700, 216, 200, 341));
        employeeButton->setStyleSheet(QString::fromUtf8("background-color: transparent;\n"
"border-radius: 5px; /* Slightly rounded corners for a modern look */"));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/img/employee.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        employeeButton->setIcon(icon4);
        employeeButton->setIconSize(QSize(500, 700));
        line_2 = new QFrame(centralwidget);
        line_2->setObjectName("line_2");
        line_2->setGeometry(QRect(1220, 206, 1, 351));
        line_2->setStyleSheet(QString::fromUtf8("background-color: rgb(168, 168, 168);"));
        line_2->setFrameShape(QFrame::Shape::VLine);
        line_2->setFrameShadow(QFrame::Shadow::Sunken);
        logout = new QPushButton(centralwidget);
        logout->setObjectName("logout");
        logout->setGeometry(QRect(20, 906, 121, 61));
        logout->setStyleSheet(QString::fromUtf8("background: linear-gradient(45deg, #0288D1 0%, #03A9F4 100%);\n"
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
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/images/logout.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        logout->setIcon(icon5);
        logout->setIconSize(QSize(40, 40));
        profileButton = new QPushButton(centralwidget);
        profileButton->setObjectName("profileButton");
        profileButton->setGeometry(QRect(1800, 36, 61, 81));
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
        profileButton->setIcon(icon5);
        profileButton->setIconSize(QSize(40, 40));
        teamButton = new QPushButton(centralwidget);
        teamButton->setObjectName("teamButton");
        teamButton->setGeometry(QRect(20, 616, 121, 61));
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
        teamButton->setIcon(icon5);
        teamButton->setIconSize(QSize(40, 40));
        dashboard_9 = new QLabel(centralwidget);
        dashboard_9->setObjectName("dashboard_9");
        dashboard_9->setGeometry(QRect(1720, 66, 81, 31));
        QFont font3;
        font3.setFamilies({QString::fromUtf8("Franklin Gothic Book")});
        font3.setPointSize(12);
        font3.setBold(false);
        dashboard_9->setFont(font3);
        dashboard_9->setStyleSheet(QString::fromUtf8("background-color: transparent;\n"
"color:white;"));
        dashboard_8 = new QLabel(centralwidget);
        dashboard_8->setObjectName("dashboard_8");
        dashboard_8->setGeometry(QRect(1710, 46, 71, 31));
        dashboard_8->setFont(font);
        dashboard_8->setStyleSheet(QString::fromUtf8("background-color: transparent;\n"
"color:#393C44;"));
        playerButton = new QPushButton(centralwidget);
        playerButton->setObjectName("playerButton");
        playerButton->setGeometry(QRect(20, 316, 121, 61));
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
        playerButton->setIcon(icon5);
        playerButton->setIconSize(QSize(40, 40));
        compButton = new QPushButton(centralwidget);
        compButton->setObjectName("compButton");
        compButton->setGeometry(QRect(30, 416, 141, 61));
        compButton->setStyleSheet(QString::fromUtf8("background: linear-gradient(45deg, #0288D1 0%, #03A9F4 100%);\n"
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
        compButton->setIcon(icon5);
        compButton->setIconSize(QSize(40, 40));
        matchButton = new QPushButton(centralwidget);
        matchButton->setObjectName("matchButton");
        matchButton->setGeometry(QRect(10, 510, 141, 61));
        matchButton->setStyleSheet(QString::fromUtf8("background: linear-gradient(45deg, #0288D1 0%, #03A9F4 100%);\n"
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
        matchButton->setIcon(icon5);
        matchButton->setIconSize(QSize(40, 40));
        label_13 = new QLabel(centralwidget);
        label_13->setObjectName("label_13");
        label_13->setGeometry(QRect(30, 850, 28, 29));
        label_13->setStyleSheet(QString::fromUtf8("background-color: transparent;"));
        label_13->setPixmap(QPixmap(QString::fromUtf8(":/compimg/language.png")));
        label_13->setScaledContents(true);
        dashboard_5 = new QLabel(centralwidget);
        dashboard_5->setObjectName("dashboard_5");
        dashboard_5->setGeometry(QRect(80, 850, 71, 31));
        dashboard_5->setFont(font);
        dashboard_5->setStyleSheet(QString::fromUtf8("background-color: transparent;\n"
"color: rgb(158, 158, 158);"));
        aboutButton = new QPushButton(centralwidget);
        aboutButton->setObjectName("aboutButton");
        aboutButton->setGeometry(QRect(20, 830, 121, 61));
        aboutButton->setStyleSheet(QString::fromUtf8("background: linear-gradient(45deg, #0288D1 0%, #03A9F4 100%);\n"
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
        aboutButton->setIcon(icon5);
        aboutButton->setIconSize(QSize(40, 40));
        AdminWindow->setCentralWidget(centralwidget);
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
        adminButton->raise();
        coachButton->raise();
        employeeButton->raise();
        line_2->raise();
        logout->raise();
        profileButton->raise();
        teamButton->raise();
        dashboard_9->raise();
        dashboard_8->raise();
        playerButton->raise();
        compButton->raise();
        matchButton->raise();
        label_13->raise();
        dashboard_5->raise();
        aboutButton->raise();

        retranslateUi(AdminWindow);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(AdminWindow);
    } // setupUi

    void retranslateUi(QMainWindow *AdminWindow)
    {
        AdminWindow->setWindowTitle(QCoreApplication::translate("AdminWindow", "MainWindow", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_5), QCoreApplication::translate("AdminWindow", "Stats", nullptr));
        currentUserPhotoLabel->setText(QString());
        dashboard_7->setText(QCoreApplication::translate("AdminWindow", "Competition", nullptr));
        dashboard_3->setText(QCoreApplication::translate("AdminWindow", "Match", nullptr));
        label_17->setText(QString());
        dashboard_2->setText(QCoreApplication::translate("AdminWindow", "Player", nullptr));
        label_18->setText(QString());
        label_19->setText(QString());
        label->setText(QString());
        dashboard_4->setText(QCoreApplication::translate("AdminWindow", "Team", nullptr));
        label_21->setText(QString());
        dashboard_6->setText(QCoreApplication::translate("AdminWindow", "Log Out", nullptr));
        label_22->setText(QString());
        pushButton_4->setText(QString());
        label_20->setText(QCoreApplication::translate("AdminWindow", "Manage your\n"
"\n"
"users", nullptr));
        label_23->setText(QCoreApplication::translate("AdminWindow", "Add new users easily and assign roles : \n"
"Admin, Coach, or Employee.", nullptr));
        label_2->setText(QString());
        add_user->setText(QString());
        adminButton->setText(QString());
        coachButton->setText(QString());
        employeeButton->setText(QString());
        logout->setText(QString());
        profileButton->setText(QString());
        teamButton->setText(QString());
        dashboard_9->setText(QCoreApplication::translate("AdminWindow", "User name", nullptr));
        dashboard_8->setText(QCoreApplication::translate("AdminWindow", "Role", nullptr));
        playerButton->setText(QString());
        compButton->setText(QString());
        matchButton->setText(QString());
        label_13->setText(QString());
        dashboard_5->setText(QCoreApplication::translate("AdminWindow", "About", nullptr));
        aboutButton->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class AdminWindow: public Ui_AdminWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADMINVIEW_H
