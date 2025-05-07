/********************************************************************************
** Form generated from reading UI file 'competitionview.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_COMPETITIONVIEW_H
#define UI_COMPETITIONVIEW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_competitionview
{
public:
    QWidget *centralwidget;
    QPushButton *pushButton_3;
    QWidget *widget_2;
    QLabel *label_6;
    QFrame *line_2;
    QLabel *label_5;
    QLabel *label_4;
    QLabel *dashboard_3;
    QLabel *dashboard_2;
    QLabel *dashboard_4;
    QLabel *dashboard_7;
    QLabel *label_12;
    QLabel *label_7;
    QLabel *label_14;
    QLabel *dashboard_5;
    QLabel *dashboard_6;
    QLabel *label_13;
    QFrame *line;
    QLabel *label_8;
    QLabel *label_18;
    QLabel *label_20;
    QLabel *label_9;
    QPushButton *pushButton_6;
    QPushButton *pushButton_4;
    QLabel *label_19;
    QLabel *label_22;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_15;
    QLabel *label_16;
    QLabel *currentUserPhotoLabel;
    QPushButton *userbutton;
    QLabel *dashboard_9;
    QLabel *dashboard_8;
    QLabel *label_17;
    QPushButton *playerButton;
    QPushButton *teamButton;
    QPushButton *logout;
    QPushButton *matchButton;
    QPushButton *aboutButton;

    void setupUi(QWidget *competitionview)
    {
        if (competitionview->objectName().isEmpty())
            competitionview->setObjectName("competitionview");
        competitionview->resize(1920, 1080);
        competitionview->setStyleSheet(QString::fromUtf8("background-color: #161A22;"));
        centralwidget = new QWidget(competitionview);
        centralwidget->setObjectName("centralwidget");
        centralwidget->setGeometry(QRect(0, 0, 2041, 1121));
        centralwidget->setStyleSheet(QString::fromUtf8("background-color: #161A22;"));
        pushButton_3 = new QPushButton(centralwidget);
        pushButton_3->setObjectName("pushButton_3");
        pushButton_3->setGeometry(QRect(480, 380, 111, 41));
        QFont font;
        font.setFamilies({QString::fromUtf8("HP Simplified Jpan")});
        font.setPointSize(14);
        pushButton_3->setFont(font);
        pushButton_3->setStyleSheet(QString::fromUtf8("\n"
"QPushButton#pushButton_3 {\n"
"border: 2px solid orange; /* Subtle white border */\n"
"border-radius: 10px;\n"
"background-color: rgb(255, 255, 255);\n"
"color: rgb(255, 184, 19);\n"
"}\n"
"QPushButton#pushButton_3:hover {\n"
"    background-color: #ebebeb; /* Lighter shade on hover */\n"
"\n"
"}\n"
"\n"
"QPushButton#pushButton_3:pressed {\n"
"    background-color: #ffe9c6; /* Darker shade when pressed */\n"
"\n"
"}"));
        pushButton_3->setIconSize(QSize(16, 16));
        widget_2 = new QWidget(centralwidget);
        widget_2->setObjectName("widget_2");
        widget_2->setGeometry(QRect(200, 120, 1851, 971));
        widget_2->setStyleSheet(QString::fromUtf8("background-color: #22252D;\n"
"border-radius:40px;\n"
"border: 1px solid #FFFFFF; /* Subtle blue-gray border */\n"
""));
        label_6 = new QLabel(centralwidget);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(30, 620, 28, 29));
        label_6->setStyleSheet(QString::fromUtf8("background-color: transparent;"));
        label_6->setPixmap(QPixmap(QString::fromUtf8(":/compimg/Group 2.png")));
        label_6->setScaledContents(true);
        line_2 = new QFrame(centralwidget);
        line_2->setObjectName("line_2");
        line_2->setGeometry(QRect(-10, 410, 15, 54));
        line_2->setStyleSheet(QString::fromUtf8("QFrame#line_2 {\n"
"    background-color: #D8A353; /* Match the exact background color */\n"
"    border: 2px solid #2D3748; /* Darker border to contrast with background */\n"
"    border-radius: 3px;\n"
"}"));
        line_2->setFrameShape(QFrame::Shape::VLine);
        line_2->setFrameShadow(QFrame::Shadow::Sunken);
        label_5 = new QLabel(centralwidget);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(30, 420, 27, 27));
        label_5->setStyleSheet(QString::fromUtf8("background-color: transparent;"));
        label_5->setPixmap(QPixmap(QString::fromUtf8(":/compimg/Vectoror.png")));
        label_5->setScaledContents(true);
        label_4 = new QLabel(centralwidget);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(30, 320, 35, 35));
        label_4->setStyleSheet(QString::fromUtf8("background-color: transparent;"));
        label_4->setPixmap(QPixmap(QString::fromUtf8(":/matchimg/Group 1.png")));
        label_4->setScaledContents(true);
        dashboard_3 = new QLabel(centralwidget);
        dashboard_3->setObjectName("dashboard_3");
        dashboard_3->setGeometry(QRect(80, 520, 71, 31));
        QFont font1;
        font1.setFamilies({QString::fromUtf8("Franklin Gothic Book")});
        font1.setPointSize(12);
        dashboard_3->setFont(font1);
        dashboard_3->setStyleSheet(QString::fromUtf8("background-color: transparent;\n"
"color:#393C44;"));
        dashboard_2 = new QLabel(centralwidget);
        dashboard_2->setObjectName("dashboard_2");
        dashboard_2->setGeometry(QRect(80, 320, 71, 31));
        dashboard_2->setFont(font1);
        dashboard_2->setStyleSheet(QString::fromUtf8("background-color: transparent;\n"
"color:#393C44;"));
        dashboard_4 = new QLabel(centralwidget);
        dashboard_4->setObjectName("dashboard_4");
        dashboard_4->setGeometry(QRect(80, 620, 61, 31));
        QFont font2;
        font2.setFamilies({QString::fromUtf8("Franklin Gothic Book")});
        font2.setPointSize(12);
        font2.setBold(false);
        dashboard_4->setFont(font2);
        dashboard_4->setStyleSheet(QString::fromUtf8("background-color: transparent;\n"
"color:#393C44;"));
        dashboard_7 = new QLabel(centralwidget);
        dashboard_7->setObjectName("dashboard_7");
        dashboard_7->setGeometry(QRect(80, 420, 131, 31));
        dashboard_7->setFont(font1);
        dashboard_7->setStyleSheet(QString::fromUtf8("background-color: transparent;\n"
"color:white;"));
        label_12 = new QLabel(centralwidget);
        label_12->setObjectName("label_12");
        label_12->setGeometry(QRect(30, 520, 34, 32));
        label_12->setStyleSheet(QString::fromUtf8("background-color: transparent;"));
        label_12->setPixmap(QPixmap(QString::fromUtf8(":/compimg/Group 3.png")));
        label_12->setScaledContents(true);
        label_7 = new QLabel(centralwidget);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(50, 30, 85, 85));
        label_7->setPixmap(QPixmap(QString::fromUtf8(":/compimg/logo football.png")));
        label_7->setScaledContents(true);
        label_14 = new QLabel(centralwidget);
        label_14->setObjectName("label_14");
        label_14->setGeometry(QRect(30, 920, 28, 29));
        label_14->setStyleSheet(QString::fromUtf8("background-color: transparent;"));
        label_14->setPixmap(QPixmap(QString::fromUtf8(":/compimg/logout.png")));
        label_14->setScaledContents(true);
        dashboard_5 = new QLabel(centralwidget);
        dashboard_5->setObjectName("dashboard_5");
        dashboard_5->setGeometry(QRect(80, 850, 71, 31));
        dashboard_5->setFont(font1);
        dashboard_5->setStyleSheet(QString::fromUtf8("background-color: transparent;\n"
"color: rgb(158, 158, 158);"));
        dashboard_6 = new QLabel(centralwidget);
        dashboard_6->setObjectName("dashboard_6");
        dashboard_6->setGeometry(QRect(80, 920, 71, 31));
        dashboard_6->setFont(font1);
        dashboard_6->setStyleSheet(QString::fromUtf8("background-color: transparent;\n"
"color: rgb(158, 158, 158);"));
        label_13 = new QLabel(centralwidget);
        label_13->setObjectName("label_13");
        label_13->setGeometry(QRect(30, 850, 28, 29));
        label_13->setStyleSheet(QString::fromUtf8("background-color: transparent;"));
        label_13->setPixmap(QPixmap(QString::fromUtf8(":/compimg/language.png")));
        label_13->setScaledContents(true);
        line = new QFrame(centralwidget);
        line->setObjectName("line");
        line->setGeometry(QRect(30, 790, 135, 1));
        line->setStyleSheet(QString::fromUtf8("background-color: #393C44;"));
        line->setFrameShape(QFrame::Shape::HLine);
        line->setFrameShadow(QFrame::Shadow::Sunken);
        label_8 = new QLabel(centralwidget);
        label_8->setObjectName("label_8");
        label_8->setGeometry(QRect(120, 90, 1411, 411));
        label_8->setStyleSheet(QString::fromUtf8("background-color: transparent;"));
        label_8->setPixmap(QPixmap(QString::fromUtf8(":/compimg/Group 12.png")));
        label_8->setScaledContents(true);
        label_18 = new QLabel(centralwidget);
        label_18->setObjectName("label_18");
        label_18->setGeometry(QRect(480, 220, 531, 31));
        QFont font3;
        font3.setFamilies({QString::fromUtf8("Speedo")});
        font3.setPointSize(25);
        font3.setBold(false);
        label_18->setFont(font3);
        label_18->setStyleSheet(QString::fromUtf8("background-color: transparent;"));
        label_20 = new QLabel(centralwidget);
        label_20->setObjectName("label_20");
        label_20->setGeometry(QRect(480, 270, 141, 31));
        QFont font4;
        font4.setFamilies({QString::fromUtf8("Arial Nova")});
        font4.setPointSize(13);
        font4.setBold(false);
        label_20->setFont(font4);
        label_20->setStyleSheet(QString::fromUtf8("background-color: transparent;"));
        label_9 = new QLabel(centralwidget);
        label_9->setObjectName("label_9");
        label_9->setGeometry(QRect(1450, 140, 449, 335));
        label_9->setStyleSheet(QString::fromUtf8("background-color: transparent;"));
        label_9->setPixmap(QPixmap(QString::fromUtf8(":/compimg/Group 13.png")));
        label_9->setScaledContents(true);
        pushButton_6 = new QPushButton(centralwidget);
        pushButton_6->setObjectName("pushButton_6");
        pushButton_6->setGeometry(QRect(1480, 170, 64, 64));
        pushButton_6->setStyleSheet(QString::fromUtf8("/* Style for the pushButton_4 */\n"
"QPushButton#pushButton_6 {\n"
"    background-color: #F5A623; /* Original background color */\n"
"    color: #1A2633; /* Dark blue text */\n"
"    border: 1px solid white; /* Subtle white border */\n"
"    border-radius: 20px;\n"
"    min-width: 62px;\n"
"    min-height: 62px;\n"
"    \n"
"}\n"
"\n"
"QPushButton#pushButton_4:hover {\n"
"    background-color: #ffdba2; /* Lighter shade on hover */\n"
"    min-width: 70px; /* Slight size increase */\n"
"    min-height: 70px;\n"
"    \n"
"}\n"
"\n"
"QPushButton#pushButton_4:pressed {\n"
"    background-color: #d68f1e; /* Darker shade when pressed */\n"
"    min-width: 62px; /* Original size */\n"
"    min-height: 62px;\n"
"   \n"
"}"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/compimg/pencil.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButton_6->setIcon(icon);
        pushButton_6->setIconSize(QSize(42, 42));
        pushButton_4 = new QPushButton(centralwidget);
        pushButton_4->setObjectName("pushButton_4");
        pushButton_4->setGeometry(QRect(1560, 180, 46, 46));
        pushButton_4->setStyleSheet(QString::fromUtf8("/* Style for the pushButton_5 */\n"
"QPushButton#pushButton_4 {\n"
"    background-color: #393C44; /* Original background color */\n"
"    color: #FFFFFF; /* White text for contrast */\n"
"	    border: 1px solid white; /* Subtle white border */\n"
"    border-radius: 15px;\n"
"    min-width: 44px;\n"
"    min-height: 44px;\n"
"   \n"
"}\n"
"\n"
"QPushButton#pushButton_4:hover {\n"
"    background-color: #4A4E58; /* Lighter shade on hover */\n"
"    min-width: 60px; /* Slight size increase */\n"
"    min-height: 60px;\n"
"    \n"
"}\n"
"\n"
"QPushButton#pushButton_4:pressed {\n"
"    background-color: #2D3037; /* Darker shade when pressed */\n"
"    min-width: 52px; /* Original size */\n"
"    min-height: 52px;\n"
"    \n"
"}"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/compimg/statsIcon.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButton_4->setIcon(icon1);
        pushButton_4->setIconSize(QSize(22, 22));
        label_19 = new QLabel(centralwidget);
        label_19->setObjectName("label_19");
        label_19->setGeometry(QRect(1480, 260, 531, 31));
        QFont font5;
        font5.setFamilies({QString::fromUtf8("Impact")});
        font5.setPointSize(21);
        font5.setBold(false);
        label_19->setFont(font5);
        label_19->setStyleSheet(QString::fromUtf8("background-color: transparent;"));
        label_22 = new QLabel(centralwidget);
        label_22->setObjectName("label_22");
        label_22->setGeometry(QRect(1480, 300, 331, 31));
        QFont font6;
        font6.setFamilies({QString::fromUtf8("Arial Nova")});
        font6.setPointSize(11);
        font6.setBold(false);
        label_22->setFont(font6);
        label_22->setStyleSheet(QString::fromUtf8("background-color: transparent;"));
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setGeometry(QRect(240, 560, 558, 417));
        label->setStyleSheet(QString::fromUtf8("background-color:transparent;"));
        label->setPixmap(QPixmap(QString::fromUtf8(":/compimg/genPic.png")));
        label->setScaledContents(true);
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(410, 580, 381, 151));
        QFont font7;
        font7.setFamilies({QString::fromUtf8("Arial Nova")});
        font7.setPointSize(25);
        font7.setBold(true);
        label_2->setFont(font7);
        label_2->setStyleSheet(QString::fromUtf8("letter-spacing:2px;\n"
"background-color: transparent;"));
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(910, 560, 988, 417));
        label_3->setStyleSheet(QString::fromUtf8("background-color: transparent;"));
        label_3->setPixmap(QPixmap(QString::fromUtf8(":/compimg/CHP.png")));
        label_3->setScaledContents(true);
        label_15 = new QLabel(centralwidget);
        label_15->setObjectName("label_15");
        label_15->setGeometry(QRect(950, 600, 421, 61));
        QFont font8;
        font8.setPointSize(35);
        font8.setBold(true);
        label_15->setFont(font8);
        label_15->setStyleSheet(QString::fromUtf8("background-color: transparent;"));
        label_16 = new QLabel(centralwidget);
        label_16->setObjectName("label_16");
        label_16->setGeometry(QRect(1040, 700, 401, 121));
        QFont font9;
        font9.setFamilies({QString::fromUtf8("Segoe Print")});
        font9.setPointSize(24);
        font9.setBold(false);
        label_16->setFont(font9);
        label_16->setStyleSheet(QString::fromUtf8("background-color: transparent;"));
        currentUserPhotoLabel = new QLabel(centralwidget);
        currentUserPhotoLabel->setObjectName("currentUserPhotoLabel");
        currentUserPhotoLabel->setGeometry(QRect(1800, 30, 60, 60));
        currentUserPhotoLabel->setStyleSheet(QString::fromUtf8("background: #1E1F2D;\n"
"border: 1px solid #3A3D4A;\n"
"border-radius: 	30px;\n"
"box-shadow: 0 4px 10px rgba(0, 0, 0, 0.2);"));
        currentUserPhotoLabel->setScaledContents(true);
        userbutton = new QPushButton(centralwidget);
        userbutton->setObjectName("userbutton");
        userbutton->setGeometry(QRect(1864, 42, 34, 43));
        userbutton->setStyleSheet(QString::fromUtf8("background: linear-gradient(45deg, #0288D1 0%, #03A9F4 100%);\n"
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
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/images/logout.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        userbutton->setIcon(icon2);
        userbutton->setIconSize(QSize(40, 40));
        dashboard_9 = new QLabel(centralwidget);
        dashboard_9->setObjectName("dashboard_9");
        dashboard_9->setGeometry(QRect(1720, 60, 81, 31));
        dashboard_9->setFont(font2);
        dashboard_9->setStyleSheet(QString::fromUtf8("background-color: transparent;\n"
"color:white;"));
        dashboard_8 = new QLabel(centralwidget);
        dashboard_8->setObjectName("dashboard_8");
        dashboard_8->setGeometry(QRect(1710, 40, 71, 31));
        dashboard_8->setFont(font1);
        dashboard_8->setStyleSheet(QString::fromUtf8("background-color: transparent;\n"
"color:#393C44;"));
        label_17 = new QLabel(centralwidget);
        label_17->setObjectName("label_17");
        label_17->setGeometry(QRect(1873, 60, 16, 10));
        label_17->setStyleSheet(QString::fromUtf8("background-color: transparent;"));
        label_17->setPixmap(QPixmap(QString::fromUtf8(":/img/Vectorrrr.png")));
        label_17->setScaledContents(true);
        playerButton = new QPushButton(centralwidget);
        playerButton->setObjectName("playerButton");
        playerButton->setGeometry(QRect(20, 300, 121, 71));
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
        playerButton->setIcon(icon2);
        playerButton->setIconSize(QSize(40, 40));
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
        teamButton->setIcon(icon2);
        teamButton->setIconSize(QSize(40, 40));
        logout = new QPushButton(centralwidget);
        logout->setObjectName("logout");
        logout->setGeometry(QRect(20, 910, 121, 61));
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
        logout->setIcon(icon2);
        logout->setIconSize(QSize(40, 40));
        matchButton = new QPushButton(centralwidget);
        matchButton->setObjectName("matchButton");
        matchButton->setGeometry(QRect(20, 510, 121, 61));
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
        matchButton->setIcon(icon2);
        matchButton->setIconSize(QSize(40, 40));
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
        aboutButton->setIcon(icon2);
        aboutButton->setIconSize(QSize(40, 40));
        widget_2->raise();
        label->raise();
        label_8->raise();
        label_9->raise();
        label_6->raise();
        line_2->raise();
        label_5->raise();
        label_4->raise();
        dashboard_3->raise();
        dashboard_2->raise();
        dashboard_4->raise();
        dashboard_7->raise();
        label_12->raise();
        label_7->raise();
        label_14->raise();
        dashboard_5->raise();
        dashboard_6->raise();
        label_13->raise();
        line->raise();
        pushButton_6->raise();
        pushButton_4->raise();
        label_19->raise();
        label_22->raise();
        label_18->raise();
        label_20->raise();
        pushButton_3->raise();
        label_2->raise();
        label_3->raise();
        label_15->raise();
        label_16->raise();
        currentUserPhotoLabel->raise();
        userbutton->raise();
        dashboard_9->raise();
        dashboard_8->raise();
        label_17->raise();
        playerButton->raise();
        teamButton->raise();
        logout->raise();
        matchButton->raise();
        aboutButton->raise();

        retranslateUi(competitionview);

        QMetaObject::connectSlotsByName(competitionview);
    } // setupUi

    void retranslateUi(QWidget *competitionview)
    {
        competitionview->setWindowTitle(QCoreApplication::translate("competitionview", "MainWindow", nullptr));
        pushButton_3->setText(QCoreApplication::translate("competitionview", "HERE", nullptr));
        label_6->setText(QString());
        label_5->setText(QString());
        label_4->setText(QString());
        dashboard_3->setText(QCoreApplication::translate("competitionview", "Match", nullptr));
        dashboard_2->setText(QCoreApplication::translate("competitionview", "Player", nullptr));
        dashboard_4->setText(QCoreApplication::translate("competitionview", "Team", nullptr));
        dashboard_7->setText(QCoreApplication::translate("competitionview", "Competition", nullptr));
        label_12->setText(QString());
        label_7->setText(QString());
        label_14->setText(QString());
        dashboard_5->setText(QCoreApplication::translate("competitionview", "About", nullptr));
        dashboard_6->setText(QCoreApplication::translate("competitionview", "Log Out", nullptr));
        label_13->setText(QString());
        label_8->setText(QString());
        label_18->setText(QCoreApplication::translate("competitionview", "ADD A COMPETITON", nullptr));
        label_20->setText(QCoreApplication::translate("competitionview", "by filling this form", nullptr));
        label_9->setText(QString());
        pushButton_6->setText(QString());
        pushButton_4->setText(QString());
        label_19->setText(QCoreApplication::translate("competitionview", "Adjust Team  |  Statistiques", nullptr));
        label_22->setText(QCoreApplication::translate("competitionview", " You can choose the type of the Statistiques .", nullptr));
        label->setText(QString());
#if QT_CONFIG(whatsthis)
        label_2->setWhatsThis(QCoreApplication::translate("competitionview", "<html><head/><body><p align=\"center\">You can Generate a \\n random match \\n by selecting </p></body></html>", nullptr));
#endif // QT_CONFIG(whatsthis)
        label_2->setText(QCoreApplication::translate("competitionview", "  You can Generate a \n"
"        random match ! \n"
"      ", nullptr));
        label_3->setText(QString());
        label_15->setText(QCoreApplication::translate("competitionview", "Competition Types", nullptr));
        label_16->setText(QCoreApplication::translate("competitionview", "\342\200\242 League\n"
"\342\200\242 Tournament", nullptr));
        currentUserPhotoLabel->setText(QString());
        userbutton->setText(QString());
        dashboard_9->setText(QCoreApplication::translate("competitionview", "User name", nullptr));
        dashboard_8->setText(QCoreApplication::translate("competitionview", "Role", nullptr));
        label_17->setText(QString());
        playerButton->setText(QString());
        teamButton->setText(QString());
        logout->setText(QString());
        matchButton->setText(QString());
        aboutButton->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class competitionview: public Ui_competitionview {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_COMPETITIONVIEW_H
