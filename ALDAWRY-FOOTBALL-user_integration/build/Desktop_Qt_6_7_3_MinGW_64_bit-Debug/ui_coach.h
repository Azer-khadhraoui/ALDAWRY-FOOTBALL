/********************************************************************************
** Form generated from reading UI file 'coach.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_COACH_H
#define UI_COACH_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CoachWindow
{
public:
    QWidget *centralwidget;
    QWidget *widget_2;
    QLabel *label;
    QFrame *line_2;
    QLabel *label_3;
    QPushButton *coachButton;
    QFrame *line;
    QLabel *label_13;
    QLabel *label_14;
    QPushButton *LogOutButton;
    QPushButton *LogOutButton_2;
    QLabel *label_2;
    QLabel *label_4;
    QListView *listView;
    QLabel *label_5;
    QPushButton *Viewplayers;
    QLabel *label_6;
    QLabel *label_7;
    QLabel *label_8;
    QLabel *label_9;
    QPushButton *MatchesButton;
    QLabel *label_10;
    QLabel *label_16;
    QPushButton *logout;
    QPushButton *profileButton;
    QLabel *dashboard_8;
    QLabel *dashboard_9;
    QLabel *currentUserPhotoLabel;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1920, 1080);
        MainWindow->setStyleSheet(QString::fromUtf8("background-color: #161A22;"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        widget_2 = new QWidget(centralwidget);
        widget_2->setObjectName("widget_2");
        widget_2->setGeometry(QRect(200, 120, 1851, 971));
        widget_2->setStyleSheet(QString::fromUtf8("background-color: #22252D;\n"
"border-radius:40px;\n"
"border: 1px solid #FFFFFF; /* Subtle blue-gray border */\n"
""));
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setGeometry(QRect(50, 30, 85, 85));
        label->setPixmap(QPixmap(QString::fromUtf8(":/img/logo football.png")));
        label->setScaledContents(true);
        line_2 = new QFrame(centralwidget);
        line_2->setObjectName("line_2");
        line_2->setGeometry(QRect(-10, 310, 15, 54));
        line_2->setStyleSheet(QString::fromUtf8("QFrame#line_2 {\n"
"    background-color: #D8A353; /* Match the exact background color */\n"
"    border: 2px solid #2D3748; /* Darker border to contrast with background */\n"
"    border-radius: 3px;\n"
"}"));
        line_2->setFrameShape(QFrame::Shape::VLine);
        line_2->setFrameShadow(QFrame::Shadow::Sunken);
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(30, 320, 35, 35));
        label_3->setStyleSheet(QString::fromUtf8("background-color: transparent;"));
        label_3->setPixmap(QPixmap(QString::fromUtf8(":/img/coach.png")));
        label_3->setScaledContents(true);
        coachButton = new QPushButton(centralwidget);
        coachButton->setObjectName("coachButton");
        coachButton->setGeometry(QRect(74, 327, 80, 24));
        QFont font;
        font.setPointSize(12);
        coachButton->setFont(font);
        coachButton->setStyleSheet(QString::fromUtf8("background-color: transparent;\n"
"color:white;\n"
"border:0px;"));
        coachButton->setIconSize(QSize(20, 20));
        line = new QFrame(centralwidget);
        line->setObjectName("line");
        line->setGeometry(QRect(30, 790, 135, 1));
        line->setStyleSheet(QString::fromUtf8("background-color: #393C44;"));
        line->setFrameShape(QFrame::Shape::HLine);
        line->setFrameShadow(QFrame::Shadow::Sunken);
        label_13 = new QLabel(centralwidget);
        label_13->setObjectName("label_13");
        label_13->setGeometry(QRect(30, 850, 28, 29));
        label_13->setStyleSheet(QString::fromUtf8("background-color: transparent;"));
        label_13->setPixmap(QPixmap(QString::fromUtf8(":/img/language.png")));
        label_13->setScaledContents(true);
        label_14 = new QLabel(centralwidget);
        label_14->setObjectName("label_14");
        label_14->setGeometry(QRect(30, 920, 28, 29));
        label_14->setStyleSheet(QString::fromUtf8("background-color: transparent;"));
        label_14->setPixmap(QPixmap(QString::fromUtf8(":/img/logout.png")));
        label_14->setScaledContents(true);
        LogOutButton = new QPushButton(centralwidget);
        LogOutButton->setObjectName("LogOutButton");
        LogOutButton->setGeometry(QRect(80, 920, 80, 24));
        LogOutButton->setFont(font);
        LogOutButton->setStyleSheet(QString::fromUtf8("background-color: transparent;\n"
"color:#393C44;\n"
"border:0px;"));
        LogOutButton->setIconSize(QSize(20, 20));
        LogOutButton_2 = new QPushButton(centralwidget);
        LogOutButton_2->setObjectName("LogOutButton_2");
        LogOutButton_2->setGeometry(QRect(73, 850, 80, 24));
        LogOutButton_2->setFont(font);
        LogOutButton_2->setStyleSheet(QString::fromUtf8("background-color: transparent;\n"
"color:#393C44;\n"
"border:0px;"));
        LogOutButton_2->setIconSize(QSize(20, 20));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(200, 0, 1672, 515));
        label_2->setStyleSheet(QString::fromUtf8("background-color: transparent;"));
        label_2->setPixmap(QPixmap(QString::fromUtf8(":/img/HEADER.png")));
        label_2->setScaledContents(true);
        label_4 = new QLabel(centralwidget);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(270, 530, 141, 51));
        QFont font1;
        font1.setPointSize(20);
        label_4->setFont(font1);
        label_4->setStyleSheet(QString::fromUtf8("background-color: transparent;"));
        listView = new QListView(centralwidget);
        listView->setObjectName("listView");
        listView->setGeometry(QRect(270, 580, 701, 411));
        listView->setStyleSheet(QString::fromUtf8("QListView#listView {\n"
"    background-color: #2D3748; /* Matches the sidebar background */\n"
"    border: 1px solid #4A4E58; /* Subtle border matching chart borders */\n"
"    border-radius: 5px; /* Slightly rounded corners for a modern look */\n"
"    color: #FFFFFF; /* White text for contrast */\n"
"    font: 12pt \"Arial\"; /* Matches the font style used elsewhere */\n"
"}\n"
"\n"
"QListView#listView::item {\n"
"    background-color: #2D3748; /* Item background matches the list background */\n"
"    padding: 10px; /* Spacing for better readability */\n"
"    color: #FFFFFF; /* White text for items */\n"
"}\n"
"\n"
"QListView#listView::item:hover {\n"
"    background-color: #F5A623; /* Golden highlight on hover to match accents */\n"
"    color: #1A2526; /* Dark text for contrast on hover */\n"
"}\n"
"\n"
"QListView#listView::item:selected {\n"
"    background-color: #D8A353; /* Slightly lighter gold for selected items */\n"
"    color: #1A2526; /* Dark text for contrast when selected */\n"
"    border: n"
                        "one; /* Remove any default border */\n"
"}"));
        label_5 = new QLabel(centralwidget);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(1480, 590, 389, 400));
        label_5->setStyleSheet(QString::fromUtf8("background-color: transparent;"));
        label_5->setPixmap(QPixmap(QString::fromUtf8(":/img/viewLabel.png")));
        label_5->setScaledContents(true);
        Viewplayers = new QPushButton(centralwidget);
        Viewplayers->setObjectName("Viewplayers");
        Viewplayers->setGeometry(QRect(1510, 620, 64, 64));
        Viewplayers->setStyleSheet(QString::fromUtf8("/* Style for the pushButton_4 */\n"
"QPushButton#ViewButton {\n"
"    background-color: #F5A623; /* Original background color */\n"
"    color: #1A2633; /* Dark blue text */\n"
"    border: 1px solid white; /* Subtle white border */\n"
"    border-radius: 20px;\n"
"    min-width: 62px;\n"
"    min-height: 62px;\n"
"    \n"
"}\n"
"\n"
"QPushButton#ViewButton:hover {\n"
"    background-color: #ffdba2; /* Lighter shade on hover */\n"
"    min-width: 70px; /* Slight size increase */\n"
"    min-height: 70px;\n"
"    \n"
"}\n"
"\n"
"QPushButton#ViewButton:pressed {\n"
"    background-color: #d68f1e; /* Darker shade when pressed */\n"
"    min-width: 62px; /* Original size */\n"
"    min-height: 62px;\n"
"   \n"
"}"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/img/view.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        Viewplayers->setIcon(icon);
        Viewplayers->setIconSize(QSize(42, 42));
        label_6 = new QLabel(centralwidget);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(1520, 710, 321, 41));
        label_6->setFont(font);
        label_6->setStyleSheet(QString::fromUtf8("background-color: transparent;"));
        label_7 = new QLabel(centralwidget);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(1060, 580, 401, 420));
        label_7->setStyleSheet(QString::fromUtf8("background-color: transparent;"));
        label_7->setPixmap(QPixmap(QString::fromUtf8(":/img/matches.png")));
        label_7->setScaledContents(true);
        label_8 = new QLabel(centralwidget);
        label_8->setObjectName("label_8");
        label_8->setGeometry(QRect(1170, 620, 191, 51));
        QFont font2;
        font2.setPointSize(30);
        font2.setBold(true);
        label_8->setFont(font2);
        label_8->setStyleSheet(QString::fromUtf8("background-color: transparent;"));
        label_9 = new QLabel(centralwidget);
        label_9->setObjectName("label_9");
        label_9->setGeometry(QRect(1110, 690, 301, 91));
        QFont font3;
        font3.setPointSize(16);
        font3.setBold(false);
        label_9->setFont(font3);
        label_9->setStyleSheet(QString::fromUtf8("background-color: transparent;"));
        MatchesButton = new QPushButton(centralwidget);
        MatchesButton->setObjectName("MatchesButton");
        MatchesButton->setGeometry(QRect(1180, 850, 171, 41));
        QFont font4;
        font4.setPointSize(12);
        font4.setBold(true);
        MatchesButton->setFont(font4);
        MatchesButton->setStyleSheet(QString::fromUtf8("  border: 1px solid #4A4E58; /* Subtle border matching chart borders */\n"
"    border-radius: 15px; /* Slightly rounded corners for a modern look */\n"
"background-color: #BEF8B6;\n"
"color:black;"));
        label_10 = new QLabel(centralwidget);
        label_10->setObjectName("label_10");
        label_10->setGeometry(QRect(1190, 858, 21, 25));
        label_10->setStyleSheet(QString::fromUtf8("background-color:transparent;"));
        label_10->setPixmap(QPixmap(QString::fromUtf8(":/img/here.png")));
        label_10->setScaledContents(true);
        label_16 = new QLabel(centralwidget);
        label_16->setObjectName("label_16");
        label_16->setGeometry(QRect(1870, 50, 16, 10));
        label_16->setStyleSheet(QString::fromUtf8("background-color: transparent;"));
        label_16->setPixmap(QPixmap(QString::fromUtf8(":/img/Vectorrrr.png")));
        label_16->setScaledContents(true);
        logout = new QPushButton(centralwidget);
        logout->setObjectName("logout");
        logout->setGeometry(QRect(50, 910, 121, 61));
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
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/images/logout.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        logout->setIcon(icon1);
        logout->setIconSize(QSize(40, 40));
        profileButton = new QPushButton(centralwidget);
        profileButton->setObjectName("profileButton");
        profileButton->setGeometry(QRect(1790, 20, 71, 71));
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
        profileButton->setIcon(icon1);
        profileButton->setIconSize(QSize(40, 40));
        dashboard_8 = new QLabel(centralwidget);
        dashboard_8->setObjectName("dashboard_8");
        dashboard_8->setGeometry(QRect(1670, 40, 71, 31));
        QFont font5;
        font5.setFamilies({QString::fromUtf8("Franklin Gothic Book")});
        font5.setPointSize(12);
        dashboard_8->setFont(font5);
        dashboard_8->setStyleSheet(QString::fromUtf8("background-color: transparent;\n"
"color:#393C44;"));
        dashboard_9 = new QLabel(centralwidget);
        dashboard_9->setObjectName("dashboard_9");
        dashboard_9->setGeometry(QRect(1670, 60, 81, 31));
        QFont font6;
        font6.setFamilies({QString::fromUtf8("Franklin Gothic Book")});
        font6.setPointSize(12);
        font6.setBold(false);
        dashboard_9->setFont(font6);
        dashboard_9->setStyleSheet(QString::fromUtf8("background-color: transparent;\n"
"color:#393C44;"));
        currentUserPhotoLabel = new QLabel(centralwidget);
        currentUserPhotoLabel->setObjectName("currentUserPhotoLabel");
        currentUserPhotoLabel->setGeometry(QRect(1790, 20, 60, 60));
        currentUserPhotoLabel->setStyleSheet(QString::fromUtf8("background: #1E1F2D;\n"
"border: 1px solid #3A3D4A;\n"
"border-radius: 	30px;\n"
"box-shadow: 0 4px 10px rgba(0, 0, 0, 0.2);"));
        currentUserPhotoLabel->setScaledContents(true);
        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("CoachWindow", "MainWindow", nullptr));
        label->setText(QString());
        label_3->setText(QString());
        coachButton->setText(QCoreApplication::translate("CoachWindow", "Coach", nullptr));
        label_13->setText(QString());
        label_14->setText(QString());
        LogOutButton->setText(QCoreApplication::translate("CoachWindow", "Log Out", nullptr));
        LogOutButton_2->setText(QCoreApplication::translate("CoachWindow", "About", nullptr));
        label_2->setText(QString());
        label_4->setText(QCoreApplication::translate("CoachWindow", "Tasks :", nullptr));
        label_5->setText(QString());
        Viewplayers->setText(QString());
        label_6->setText(QCoreApplication::translate("CoachWindow", "Browse the complete list of registered players.\n"
"View details", nullptr));
        label_7->setText(QString());
        label_8->setText(QCoreApplication::translate("CoachWindow", "MATCHES", nullptr));
        label_9->setText(QCoreApplication::translate("CoachWindow", "<html><head/><body><p align=\"center\">View matches and set player </p><p align=\"center\">lineups.</p></body></html>", nullptr));
        MatchesButton->setText(QCoreApplication::translate("CoachWindow", "                   HERE", nullptr));
        label_10->setText(QString());
        label_16->setText(QString());
        logout->setText(QString());
        profileButton->setText(QString());
        dashboard_8->setText(QCoreApplication::translate("CoachWindow", "Role", nullptr));
        dashboard_9->setText(QCoreApplication::translate("CoachWindow", "User name", nullptr));
        currentUserPhotoLabel->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class CoachWindow: public Ui_CoachWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_COACH_H
