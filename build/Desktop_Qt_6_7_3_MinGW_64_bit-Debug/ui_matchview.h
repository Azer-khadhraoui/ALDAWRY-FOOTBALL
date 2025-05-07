/********************************************************************************
** Form generated from reading UI file 'matchview.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MATCHVIEW_H
#define UI_MATCHVIEW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_matchview
{
public:
    QWidget *centralwidget;
    QWidget *widget_2;
    QLabel *dashboard_7;
    QLabel *dashboard_3;
    QLabel *label_5;
    QLabel *dashboard_2;
    QLabel *dashboard_4;
    QLabel *label_6;
    QLabel *label;
    QLabel *label_13;
    QLabel *label_14;
    QFrame *line_2;
    QLabel *label_3;
    QLabel *label_20;
    QLabel *dashboard_6;
    QFrame *line;
    QLabel *dashboard_5;
    QPushButton *addmatch;
    QLabel *label_18;
    QLabel *label_21;
    QLabel *label_4;
    QPushButton *chartbutton;
    QPushButton *displaymatch;
    QPushButton *statsbutton;
    QLabel *label_15;
    QLabel *label_16;
    QLabel *label_17;
    QPushButton *watchmatch;
    QPushButton *viewallmatches;
    QLabel *label_22;
    QLabel *label_23;
    QLabel *currentUserPhotoLabel;
    QLabel *dashboard_9;
    QLabel *dashboard_8;
    QLabel *label_24;
    QPushButton *userbutton;
    QPushButton *compButton;
    QPushButton *playerButton;
    QPushButton *teamButton;
    QPushButton *logout;

    void setupUi(QMainWindow *matchview)
    {
        if (matchview->objectName().isEmpty())
            matchview->setObjectName("matchview");
        matchview->resize(1920, 1080);
        QFont font;
        font.setPointSize(10);
        matchview->setFont(font);
        matchview->setStyleSheet(QString::fromUtf8("background-color: #161A22;"));
        centralwidget = new QWidget(matchview);
        centralwidget->setObjectName("centralwidget");
        widget_2 = new QWidget(centralwidget);
        widget_2->setObjectName("widget_2");
        widget_2->setGeometry(QRect(200, 120, 1851, 971));
        widget_2->setStyleSheet(QString::fromUtf8("background-color: #22252D;\n"
"border-radius:40px;\n"
"border: 1px solid #FFFFFF; /* Subtle blue-gray border */\n"
""));
        dashboard_7 = new QLabel(centralwidget);
        dashboard_7->setObjectName("dashboard_7");
        dashboard_7->setGeometry(QRect(80, 420, 131, 31));
        QFont font1;
        font1.setFamilies({QString::fromUtf8("Franklin Gothic Book")});
        font1.setPointSize(12);
        dashboard_7->setFont(font1);
        dashboard_7->setStyleSheet(QString::fromUtf8("background-color: transparent;\n"
"color:#393C44;"));
        dashboard_3 = new QLabel(centralwidget);
        dashboard_3->setObjectName("dashboard_3");
        dashboard_3->setGeometry(QRect(80, 520, 71, 31));
        dashboard_3->setFont(font1);
        dashboard_3->setStyleSheet(QString::fromUtf8("background-color: transparent;\n"
"color:white;"));
        label_5 = new QLabel(centralwidget);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(30, 420, 27, 27));
        label_5->setStyleSheet(QString::fromUtf8("background-color: transparent;"));
        label_5->setPixmap(QPixmap(QString::fromUtf8(":/matchimg/Vector.png")));
        label_5->setScaledContents(true);
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
        label_6 = new QLabel(centralwidget);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(30, 620, 28, 29));
        label_6->setStyleSheet(QString::fromUtf8("background-color: transparent;"));
        label_6->setPixmap(QPixmap(QString::fromUtf8(":/compimg/Group 2.png")));
        label_6->setScaledContents(true);
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setGeometry(QRect(50, 30, 85, 85));
        label->setPixmap(QPixmap(QString::fromUtf8(":/compimg/logo football.png")));
        label->setScaledContents(true);
        label_13 = new QLabel(centralwidget);
        label_13->setObjectName("label_13");
        label_13->setGeometry(QRect(30, 320, 28, 29));
        label_13->setStyleSheet(QString::fromUtf8("background-color: transparent;"));
        label_13->setPixmap(QPixmap(QString::fromUtf8(":/compimg/Group 1.png")));
        label_13->setScaledContents(true);
        label_14 = new QLabel(centralwidget);
        label_14->setObjectName("label_14");
        label_14->setGeometry(QRect(30, 520, 28, 29));
        label_14->setStyleSheet(QString::fromUtf8("background-color: transparent;"));
        label_14->setPixmap(QPixmap(QString::fromUtf8(":/matchimg/Vectorora.png")));
        label_14->setScaledContents(true);
        line_2 = new QFrame(centralwidget);
        line_2->setObjectName("line_2");
        line_2->setGeometry(QRect(-10, 510, 15, 54));
        line_2->setStyleSheet(QString::fromUtf8("QFrame#line_2 {\n"
"    background-color: #D8A353; /* Match the exact background color */\n"
"    border: 2px solid #2D3748; /* Darker border to contrast with background */\n"
"    border-radius: 3px;\n"
"}"));
        line_2->setFrameShape(QFrame::Shape::VLine);
        line_2->setFrameShadow(QFrame::Shadow::Sunken);
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(190, 130, 1260, 399));
        label_3->setStyleSheet(QString::fromUtf8("background-color: transparent;"));
        label_3->setPixmap(QPixmap(QString::fromUtf8(":/matchimg/DESIGN2.png")));
        label_3->setScaledContents(true);
        label_20 = new QLabel(centralwidget);
        label_20->setObjectName("label_20");
        label_20->setGeometry(QRect(30, 920, 28, 29));
        label_20->setStyleSheet(QString::fromUtf8("background-color: transparent;"));
        label_20->setPixmap(QPixmap(QString::fromUtf8(":/img/logout.png")));
        label_20->setScaledContents(true);
        dashboard_6 = new QLabel(centralwidget);
        dashboard_6->setObjectName("dashboard_6");
        dashboard_6->setGeometry(QRect(80, 920, 71, 31));
        dashboard_6->setFont(font1);
        dashboard_6->setStyleSheet(QString::fromUtf8("background-color: transparent;\n"
"color:#393C44;"));
        line = new QFrame(centralwidget);
        line->setObjectName("line");
        line->setGeometry(QRect(30, 790, 135, 1));
        line->setStyleSheet(QString::fromUtf8("background-color: #393C44;"));
        line->setFrameShape(QFrame::Shape::HLine);
        line->setFrameShadow(QFrame::Shadow::Sunken);
        dashboard_5 = new QLabel(centralwidget);
        dashboard_5->setObjectName("dashboard_5");
        dashboard_5->setGeometry(QRect(80, 850, 71, 31));
        dashboard_5->setFont(font1);
        dashboard_5->setStyleSheet(QString::fromUtf8("background-color: transparent;\n"
"color:#393C44;"));
        addmatch = new QPushButton(centralwidget);
        addmatch->setObjectName("addmatch");
        addmatch->setGeometry(QRect(740, 280, 181, 41));
        QFont font3;
        font3.setFamilies({QString::fromUtf8("HP Simplified Jpan")});
        font3.setPointSize(14);
        addmatch->setFont(font3);
        addmatch->setStyleSheet(QString::fromUtf8("\n"
"QPushButton#addmatch {\n"
"border: 2px solid orange; /* Subtle white border */\n"
"border-radius: 10px;\n"
"background-color: rgb(255, 255, 255);\n"
"color: rgb(255, 184, 19);\n"
"}\n"
"QPushButton#addmatch:hover {\n"
"    background-color: #ebebeb; /* Lighter shade on hover */\n"
"\n"
"}\n"
"\n"
"QPushButton#addmatch:pressed {\n"
"    background-color: #ffe9c6; /* Darker shade when pressed */\n"
"\n"
"}"));
        label_18 = new QLabel(centralwidget);
        label_18->setObjectName("label_18");
        label_18->setGeometry(QRect(640, 180, 391, 31));
        QFont font4;
        font4.setFamilies({QString::fromUtf8("Speedo")});
        font4.setPointSize(25);
        font4.setBold(false);
        label_18->setFont(font4);
        label_18->setStyleSheet(QString::fromUtf8("background-color: transparent;"));
        label_21 = new QLabel(centralwidget);
        label_21->setObjectName("label_21");
        label_21->setGeometry(QRect(640, 220, 181, 31));
        QFont font5;
        font5.setFamilies({QString::fromUtf8("Arial Nova")});
        font5.setPointSize(13);
        font5.setBold(false);
        label_21->setFont(font5);
        label_21->setStyleSheet(QString::fromUtf8("background-color: transparent;"));
        label_4 = new QLabel(centralwidget);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(1500, 164, 389, 335));
        label_4->setStyleSheet(QString::fromUtf8("background-color: transparent;"));
        label_4->setPixmap(QPixmap(QString::fromUtf8(":/matchimg/DESIGN3.png")));
        label_4->setScaledContents(true);
        chartbutton = new QPushButton(centralwidget);
        chartbutton->setObjectName("chartbutton");
        chartbutton->setGeometry(QRect(1660, 220, 44, 44));
        chartbutton->setStyleSheet(QString::fromUtf8("/* Style for the pushButton_6 */\n"
"QPushButton#chartbutton {\n"
"    background-color: #B4B4B4; /* Original background color */\n"
"    color: #1A2633; /* Dark blue text for contrast */\n"
"    border: 1px solid white; /* Subtle white border */\n"
"    border-radius: 10px;\n"
"    min-width: 42px;\n"
"    min-height: 42px;\n"
"  \n"
"}\n"
"\n"
"QPushButton#chartbutton:hover {\n"
"    background-color: #C5C5C5; /* Lighter shade on hover */\n"
"    min-width: 48px; /* Slight size increase */\n"
"    min-height: 48px;\n"
"}\n"
"\n"
"QPushButton#chartbutton:pressed {\n"
"    background-color: #A3A3A3; /* Darker shade when pressed */\n"
"    min-width: 42px; /* Original size */\n"
"    min-height: 42px;\n"
"\n"
"}"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/matchimg/chart.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        chartbutton->setIcon(icon);
        chartbutton->setIconSize(QSize(25, 25));
        displaymatch = new QPushButton(centralwidget);
        displaymatch->setObjectName("displaymatch");
        displaymatch->setGeometry(QRect(1530, 200, 64, 64));
        displaymatch->setStyleSheet(QString::fromUtf8("/* Style for the pushButton_4 */\n"
"QPushButton#displaymatch {\n"
"    background-color: #F5A623; /* Original background color */\n"
"    color: #1A2633; /* Dark blue text */\n"
"    border: 1px solid white; /* Subtle white border */\n"
"    border-radius: 20px;\n"
"    min-width: 62px;\n"
"    min-height: 62px;\n"
"    \n"
"}\n"
"\n"
"QPushButton#displaymatch:hover {\n"
"    background-color: #ffdba2; /* Lighter shade on hover */\n"
"    min-width: 70px; /* Slight size increase */\n"
"    min-height: 70px;\n"
"    \n"
"}\n"
"\n"
"QPushButton#displaymatch:pressed {\n"
"    background-color: #d68f1e; /* Darker shade when pressed */\n"
"    min-width: 62px; /* Original size */\n"
"    min-height: 62px;\n"
"   \n"
"}"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/compimg/pencil.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        displaymatch->setIcon(icon1);
        displaymatch->setIconSize(QSize(42, 42));
        statsbutton = new QPushButton(centralwidget);
        statsbutton->setObjectName("statsbutton");
        statsbutton->setGeometry(QRect(1600, 210, 54, 54));
        statsbutton->setStyleSheet(QString::fromUtf8("/* Style for the pushButton_5 */\n"
"QPushButton#statsbutton {\n"
"    background-color: #393C44; /* Original background color */\n"
"    color: #FFFFFF; /* White text for contrast */\n"
"    border: 1px solid #2c2f35; /* Subtle white border */\n"
"    border-radius: 15px;\n"
"    min-width: 52px;\n"
"    min-height: 52px;\n"
"   \n"
"}\n"
"\n"
"QPushButton#statsbutton:hover {\n"
"    background-color: #4A4E58; /* Lighter shade on hover */\n"
"    min-width: 60px; /* Slight size increase */\n"
"    min-height: 60px;\n"
"    \n"
"}\n"
"\n"
"QPushButton#statsbutton:pressed {\n"
"    background-color: #2D3037; /* Darker shade when pressed */\n"
"    min-width: 52px; /* Original size */\n"
"    min-height: 52px;\n"
"    \n"
"}"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/matchimg/statsIcon.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        statsbutton->setIcon(icon2);
        statsbutton->setIconSize(QSize(27, 27));
        label_15 = new QLabel(centralwidget);
        label_15->setObjectName("label_15");
        label_15->setGeometry(QRect(201, 520, 1721, 561));
        label_15->setStyleSheet(QString::fromUtf8("background-color: #2B2F38;"));
        label_16 = new QLabel(centralwidget);
        label_16->setObjectName("label_16");
        label_16->setGeometry(QRect(480, 560, 1161, 432));
        label_16->setStyleSheet(QString::fromUtf8("background-color: transparent;"));
        label_16->setPixmap(QPixmap(QString::fromUtf8(":/matchimg/DESIGN1.png")));
        label_16->setScaledContents(true);
        label_17 = new QLabel(centralwidget);
        label_17->setObjectName("label_17");
        label_17->setGeometry(QRect(530, 584, 80, 27));
        label_17->setStyleSheet(QString::fromUtf8("background-color: #D2A9A9;\n"
"border-radius:5px;"));
        watchmatch = new QPushButton(centralwidget);
        watchmatch->setObjectName("watchmatch");
        watchmatch->setGeometry(QRect(1490, 584, 105, 27));
        watchmatch->setStyleSheet(QString::fromUtf8("background-color: white;\n"
"color:black;\n"
"border-radius:5px;"));
        viewallmatches = new QPushButton(centralwidget);
        viewallmatches->setObjectName("viewallmatches");
        viewallmatches->setGeometry(QRect(980, 960, 208, 54));
        QFont font6;
        font6.setPointSize(14);
        viewallmatches->setFont(font6);
        viewallmatches->setStyleSheet(QString::fromUtf8("background-color: #D8A353;\n"
"color:white;\n"
"border-radius:20px;"));
        label_22 = new QLabel(centralwidget);
        label_22->setObjectName("label_22");
        label_22->setGeometry(QRect(1530, 280, 531, 31));
        QFont font7;
        font7.setFamilies({QString::fromUtf8("Impact")});
        font7.setPointSize(21);
        font7.setBold(false);
        label_22->setFont(font7);
        label_22->setStyleSheet(QString::fromUtf8("background-color: transparent;"));
        label_23 = new QLabel(centralwidget);
        label_23->setObjectName("label_23");
        label_23->setGeometry(QRect(1530, 320, 321, 31));
        QFont font8;
        font8.setFamilies({QString::fromUtf8("Arial Nova")});
        font8.setPointSize(11);
        font8.setBold(false);
        label_23->setFont(font8);
        label_23->setStyleSheet(QString::fromUtf8("background-color: transparent;"));
        currentUserPhotoLabel = new QLabel(centralwidget);
        currentUserPhotoLabel->setObjectName("currentUserPhotoLabel");
        currentUserPhotoLabel->setGeometry(QRect(1800, 30, 60, 60));
        currentUserPhotoLabel->setStyleSheet(QString::fromUtf8("background: #1E1F2D;\n"
"border: 1px solid #3A3D4A;\n"
"border-radius: 	30px;\n"
"box-shadow: 0 4px 10px rgba(0, 0, 0, 0.2);"));
        currentUserPhotoLabel->setScaledContents(true);
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
        label_24 = new QLabel(centralwidget);
        label_24->setObjectName("label_24");
        label_24->setGeometry(QRect(1870, 60, 16, 10));
        label_24->setStyleSheet(QString::fromUtf8("background-color: transparent;"));
        label_24->setPixmap(QPixmap(QString::fromUtf8(":/img/Vectorrrr.png")));
        label_24->setScaledContents(true);
        userbutton = new QPushButton(centralwidget);
        userbutton->setObjectName("userbutton");
        userbutton->setGeometry(QRect(1870, 50, 21, 27));
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
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/images/logout.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        userbutton->setIcon(icon3);
        userbutton->setIconSize(QSize(40, 40));
        compButton = new QPushButton(centralwidget);
        compButton->setObjectName("compButton");
        compButton->setGeometry(QRect(20, 400, 141, 61));
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
        compButton->setIcon(icon3);
        compButton->setIconSize(QSize(40, 40));
        playerButton = new QPushButton(centralwidget);
        playerButton->setObjectName("playerButton");
        playerButton->setGeometry(QRect(20, 300, 141, 61));
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
        playerButton->setIcon(icon3);
        playerButton->setIconSize(QSize(40, 40));
        teamButton = new QPushButton(centralwidget);
        teamButton->setObjectName("teamButton");
        teamButton->setGeometry(QRect(10, 610, 141, 61));
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
        teamButton->setIcon(icon3);
        teamButton->setIconSize(QSize(40, 40));
        logout = new QPushButton(centralwidget);
        logout->setObjectName("logout");
        logout->setGeometry(QRect(10, 900, 141, 61));
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
        logout->setIcon(icon3);
        logout->setIconSize(QSize(40, 40));
        matchview->setCentralWidget(centralwidget);
        widget_2->raise();
        label_4->raise();
        label_3->raise();
        dashboard_7->raise();
        dashboard_3->raise();
        label_5->raise();
        dashboard_2->raise();
        dashboard_4->raise();
        label_6->raise();
        label->raise();
        label_13->raise();
        label_14->raise();
        line_2->raise();
        label_20->raise();
        dashboard_6->raise();
        line->raise();
        dashboard_5->raise();
        addmatch->raise();
        label_18->raise();
        label_21->raise();
        chartbutton->raise();
        displaymatch->raise();
        statsbutton->raise();
        label_15->raise();
        label_16->raise();
        label_17->raise();
        watchmatch->raise();
        viewallmatches->raise();
        label_22->raise();
        label_23->raise();
        currentUserPhotoLabel->raise();
        dashboard_9->raise();
        dashboard_8->raise();
        label_24->raise();
        userbutton->raise();
        compButton->raise();
        playerButton->raise();
        teamButton->raise();
        logout->raise();

        retranslateUi(matchview);

        QMetaObject::connectSlotsByName(matchview);
    } // setupUi

    void retranslateUi(QMainWindow *matchview)
    {
        matchview->setWindowTitle(QCoreApplication::translate("matchview", "MainWindow", nullptr));
        dashboard_7->setText(QCoreApplication::translate("matchview", "Competition", nullptr));
        dashboard_3->setText(QCoreApplication::translate("matchview", "Match", nullptr));
        label_5->setText(QString());
        dashboard_2->setText(QCoreApplication::translate("matchview", "Player", nullptr));
        dashboard_4->setText(QCoreApplication::translate("matchview", "Team", nullptr));
        label_6->setText(QString());
        label->setText(QString());
        label_13->setText(QString());
        label_14->setText(QString());
        label_3->setText(QString());
        label_20->setText(QString());
        dashboard_6->setText(QCoreApplication::translate("matchview", "Log Out", nullptr));
        dashboard_5->setText(QCoreApplication::translate("matchview", "About", nullptr));
        addmatch->setText(QCoreApplication::translate("matchview", "HERE", nullptr));
        label_18->setText(QCoreApplication::translate("matchview", "ADD A MATCH", nullptr));
        label_21->setText(QCoreApplication::translate("matchview", "by filling this form", nullptr));
        label_4->setText(QString());
        chartbutton->setText(QString());
        displaymatch->setText(QString());
        statsbutton->setText(QString());
        label_15->setText(QString());
        label_16->setText(QString());
        label_17->setText(QString());
        watchmatch->setText(QCoreApplication::translate("matchview", "Watch Match", nullptr));
        viewallmatches->setText(QCoreApplication::translate("matchview", "View All Matches", nullptr));
        label_22->setText(QCoreApplication::translate("matchview", "Edit  |  Stats |  Chart", nullptr));
        label_23->setText(QCoreApplication::translate("matchview", " You can download Match details as a PDF.", nullptr));
        currentUserPhotoLabel->setText(QString());
        dashboard_9->setText(QCoreApplication::translate("matchview", "User name", nullptr));
        dashboard_8->setText(QCoreApplication::translate("matchview", "Role", nullptr));
        label_24->setText(QString());
        userbutton->setText(QString());
        compButton->setText(QString());
        playerButton->setText(QString());
        teamButton->setText(QString());
        logout->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class matchview: public Ui_matchview {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MATCHVIEW_H
