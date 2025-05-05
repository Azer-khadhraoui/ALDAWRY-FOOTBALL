/********************************************************************************
** Form generated from reading UI file 'teamwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TEAMWINDOW_H
#define UI_TEAMWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_teamwindow
{
public:
    QWidget *centralwidget;
    QLabel *label;
    QLabel *dashboard_2;
    QLabel *dashboard_7;
    QLabel *dashboard_3;
    QLabel *dashboard_4;
    QPushButton *pushButton;
    QWidget *widget_2;
    QPushButton *pushButton_3;
    QWidget *widget;
    QLabel *label_3;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *label_12;
    QFrame *line;
    QLabel *dashboard_5;
    QLabel *dashboard_6;
    QLabel *label_13;
    QLabel *label_14;
    QFrame *line_2;
    QLabel *label_15;
    QLabel *label_16;
    QLabel *dashboard_8;
    QLabel *dashboard_9;
    QLabel *label_17;
    QLabel *label_18;
    QPushButton *pushButton_2;
    QLabel *label_20;
    QLabel *label_2;
    QPushButton *pushButton_4;
    QPushButton *pushButton_5;
    QPushButton *pushButton_6;
    QLabel *label_19;
    QLabel *label_22;
    QListView *listView;
    QLabel *label_4;
    QLabel *label_7;
    QPushButton *pushButton_7;
    QPushButton *pushButton_8;
    QStatusBar *statusbar;

    void setupUi(QWidget *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1920, 1080);
        QFont font;
        font.setPointSize(10);
        MainWindow->setFont(font);
        MainWindow->setStyleSheet(QString::fromUtf8("background-color: #161A22;"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        centralwidget->setGeometry(QRect(0, 0, 2041, 1121));
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setGeometry(QRect(50, 30, 85, 85));
        label->setPixmap(QPixmap(QString::fromUtf8(":/img/logo_football.png")));
        label->setScaledContents(true);
        dashboard_2 = new QLabel(centralwidget);
        dashboard_2->setObjectName("dashboard_2");
        dashboard_2->setGeometry(QRect(80, 320, 71, 31));
        QFont font1;
        font1.setFamilies({QString::fromUtf8("Franklin Gothic Book")});
        font1.setPointSize(12);
        dashboard_2->setFont(font1);
        dashboard_2->setStyleSheet(QString::fromUtf8("background-color: transparent;\n"
"color:#393C44;"));
        dashboard_7 = new QLabel(centralwidget);
        dashboard_7->setObjectName("dashboard_7");
        dashboard_7->setGeometry(QRect(80, 420, 131, 31));
        dashboard_7->setFont(font1);
        dashboard_7->setStyleSheet(QString::fromUtf8("background-color: transparent;\n"
"color:#393C44;"));
        dashboard_3 = new QLabel(centralwidget);
        dashboard_3->setObjectName("dashboard_3");
        dashboard_3->setGeometry(QRect(80, 520, 71, 31));
        dashboard_3->setFont(font1);
        dashboard_3->setStyleSheet(QString::fromUtf8("background-color: transparent;\n"
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
"color:white;"));
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(1840, 930, 50, 50));
        pushButton->setStyleSheet(QString::fromUtf8("QPushButton#pushButton {\n"
"background-image: url(:/img/BACK.png);\n"
"border: 1px solid #3A4A5A; /* Subtle blue-gray border */\n"
"border-radius: 15px;\n"
"}\n"
"QPushButton#pushButton:hover {\n"
"    background-color: #d3d3d3;  /* Light grey */\n"
"    min-width: 110px;          /* 10% wider */\n"
"    min-height: 33px;          /* 10% taller */\n"
"}"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/teamimg/ai.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButton->setIcon(icon);
        pushButton->setIconSize(QSize(100, 100));
        widget_2 = new QWidget(centralwidget);
        widget_2->setObjectName("widget_2");
        widget_2->setGeometry(QRect(200, 120, 1851, 971));
        widget_2->setStyleSheet(QString::fromUtf8("background-color: #22252D;\n"
"border-radius:40px;\n"
"border: 1px solid #364154; /* Subtle blue-gray border */\n"
""));
        pushButton_3 = new QPushButton(widget_2);
        pushButton_3->setObjectName("pushButton_3");
        pushButton_3->setGeometry(QRect(1660, 810, 50, 50));
        pushButton_3->setStyleSheet(QString::fromUtf8("QPushButton#pushButton_3 {\n"
"background-image: url(:/img/BACK.png);\n"
"border: 1px solid #3A4A5A; /* Subtle blue-gray border */\n"
"border-radius: 15px;\n"
"}\n"
"QPushButton#pushButton_3:hover {\n"
"    background-color: #d3d3d3;  /* Light grey */\n"
"    min-width: 110px;          /* 10% wider */\n"
"    min-height: 33px;          /* 10% taller */\n"
"}"));
        pushButton_3->setIcon(icon);
        pushButton_3->setIconSize(QSize(100, 100));
        widget = new QWidget(widget_2);
        widget->setObjectName("widget");
        widget->setGeometry(QRect(1240, 20, 461, 331));
        widget->setStyleSheet(QString::fromUtf8("border: 3px solid #D0953C; /* Subtle blue-gray border */\n"
"background-color: #D9CEBD;"));
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(30, 320, 35, 35));
        label_3->setStyleSheet(QString::fromUtf8("background-color: transparent;"));
        label_3->setPixmap(QPixmap(QString::fromUtf8(":/teamimg/Group 1.png")));
        label_3->setScaledContents(true);
        label_5 = new QLabel(centralwidget);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(30, 420, 27, 27));
        label_5->setStyleSheet(QString::fromUtf8("background-color: transparent;"));
        label_5->setPixmap(QPixmap(QString::fromUtf8(":/teamimg/Vector.png")));
        label_5->setScaledContents(true);
        label_6 = new QLabel(centralwidget);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(30, 620, 28, 29));
        label_6->setStyleSheet(QString::fromUtf8("background-color: transparent;"));
        label_6->setPixmap(QPixmap(QString::fromUtf8(":/teamimg/Vectoror.png")));
        label_6->setScaledContents(true);
        label_12 = new QLabel(centralwidget);
        label_12->setObjectName("label_12");
        label_12->setGeometry(QRect(30, 520, 34, 32));
        label_12->setStyleSheet(QString::fromUtf8("background-color: transparent;"));
        label_12->setPixmap(QPixmap(QString::fromUtf8(":/img/Group 3.png")));
        label_12->setScaledContents(true);
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
        label_13->setPixmap(QPixmap(QString::fromUtf8(":/img/language.png")));
        label_13->setScaledContents(true);
        label_14 = new QLabel(centralwidget);
        label_14->setObjectName("label_14");
        label_14->setGeometry(QRect(30, 920, 28, 29));
        label_14->setStyleSheet(QString::fromUtf8("background-color: transparent;"));
        label_14->setPixmap(QPixmap(QString::fromUtf8(":/img/logout.png")));
        label_14->setScaledContents(true);
        line_2 = new QFrame(centralwidget);
        line_2->setObjectName("line_2");
        line_2->setGeometry(QRect(-10, 610, 15, 54));
        line_2->setStyleSheet(QString::fromUtf8("QFrame#line_2 {\n"
"    background-color: #D8A353; /* Match the exact background color */\n"
"    border: 2px solid #2D3748; /* Darker border to contrast with background */\n"
"    border-radius: 3px;\n"
"}"));
        line_2->setFrameShape(QFrame::Shape::VLine);
        line_2->setFrameShadow(QFrame::Shadow::Sunken);
        label_15 = new QLabel(centralwidget);
        label_15->setObjectName("label_15");
        label_15->setGeometry(QRect(1800, 30, 60, 60));
        label_15->setStyleSheet(QString::fromUtf8("background-color: transparent;"));
        label_15->setPixmap(QPixmap(QString::fromUtf8(":/teamimg/Layer 2.png")));
        label_15->setScaledContents(true);
        label_16 = new QLabel(centralwidget);
        label_16->setObjectName("label_16");
        label_16->setGeometry(QRect(1870, 60, 16, 10));
        label_16->setStyleSheet(QString::fromUtf8("background-color: transparent;"));
        label_16->setPixmap(QPixmap(QString::fromUtf8(":/img/Vectorrrr.png")));
        label_16->setScaledContents(true);
        dashboard_8 = new QLabel(centralwidget);
        dashboard_8->setObjectName("dashboard_8");
        dashboard_8->setGeometry(QRect(1710, 40, 71, 31));
        dashboard_8->setFont(font1);
        dashboard_8->setStyleSheet(QString::fromUtf8("background-color: transparent;\n"
"color:#393C44;"));
        dashboard_9 = new QLabel(centralwidget);
        dashboard_9->setObjectName("dashboard_9");
        dashboard_9->setGeometry(QRect(1720, 60, 81, 31));
        dashboard_9->setFont(font2);
        dashboard_9->setStyleSheet(QString::fromUtf8("background-color: transparent;\n"
"color:white;"));
        label_17 = new QLabel(centralwidget);
        label_17->setObjectName("label_17");
        label_17->setGeometry(QRect(220, 60, 1368, 452));
        label_17->setStyleSheet(QString::fromUtf8("background-color: TRANSPARENT;"));
        label_17->setPixmap(QPixmap(QString::fromUtf8(":/teamimg/pic.png")));
        label_17->setScaledContents(true);
        label_18 = new QLabel(centralwidget);
        label_18->setObjectName("label_18");
        label_18->setGeometry(QRect(290, 240, 341, 31));
        QFont font3;
        font3.setFamilies({QString::fromUtf8("Speedo")});
        font3.setPointSize(25);
        font3.setBold(false);
        label_18->setFont(font3);
        pushButton_2 = new QPushButton(centralwidget);
        pushButton_2->setObjectName("pushButton_2");
        pushButton_2->setGeometry(QRect(290, 380, 141, 31));
        QFont font4;
        font4.setFamilies({QString::fromUtf8("HP Simplified Jpan")});
        font4.setPointSize(14);
        pushButton_2->setFont(font4);
        pushButton_2->setStyleSheet(QString::fromUtf8("\n"
"QPushButton#pushButton_2 {\n"
"border: 2px solid orange; /* Subtle white border */\n"
"border-radius: 10px;\n"
"background-color: rgb(255, 255, 255);\n"
"color: rgb(255, 184, 19);\n"
"}\n"
"QPushButton#pushButton_2:hover {\n"
"    background-color: #ebebeb; /* Lighter shade on hover */\n"
"\n"
"}\n"
"\n"
"QPushButton#pushButton_2:pressed {\n"
"    background-color: #ffe9c6; /* Darker shade when pressed */\n"
"\n"
"}"));
        label_20 = new QLabel(centralwidget);
        label_20->setObjectName("label_20");
        label_20->setGeometry(QRect(290, 290, 141, 31));
        QFont font5;
        font5.setFamilies({QString::fromUtf8("Arial Nova")});
        font5.setPointSize(13);
        font5.setBold(false);
        label_20->setFont(font5);
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(1510, 90, 443, 368));
        label_2->setStyleSheet(QString::fromUtf8("background-color: transparent;"));
        label_2->setPixmap(QPixmap(QString::fromUtf8(":/teamimg/BALL.png")));
        label_2->setScaledContents(true);
        pushButton_4 = new QPushButton(centralwidget);
        pushButton_4->setObjectName("pushButton_4");
        pushButton_4->setGeometry(QRect(1470, 200, 64, 64));
        pushButton_4->setStyleSheet(QString::fromUtf8("/* Style for the pushButton_4 */\n"
"QPushButton#pushButton_4 {\n"
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
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/teamimg/pencil.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButton_4->setIcon(icon1);
        pushButton_4->setIconSize(QSize(42, 42));
        pushButton_5 = new QPushButton(centralwidget);
        pushButton_5->setObjectName("pushButton_5");
        pushButton_5->setGeometry(QRect(1540, 210, 54, 54));
        pushButton_5->setStyleSheet(QString::fromUtf8("/* Style for the pushButton_5 */\n"
"QPushButton#pushButton_5 {\n"
"    background-color: #393C44; /* Original background color */\n"
"    color: #FFFFFF; /* White text for contrast */\n"
"    border: 1px solid #2c2f35; /* Subtle white border */\n"
"    border-radius: 15px;\n"
"    min-width: 52px;\n"
"    min-height: 52px;\n"
"   \n"
"}\n"
"\n"
"QPushButton#pushButton_5:hover {\n"
"    background-color: #4A4E58; /* Lighter shade on hover */\n"
"    min-width: 60px; /* Slight size increase */\n"
"    min-height: 60px;\n"
"    \n"
"}\n"
"\n"
"QPushButton#pushButton_5:pressed {\n"
"    background-color: #2D3037; /* Darker shade when pressed */\n"
"    min-width: 52px; /* Original size */\n"
"    min-height: 52px;\n"
"    \n"
"}"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/teamimg/List.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButton_5->setIcon(icon2);
        pushButton_5->setIconSize(QSize(27, 27));
        pushButton_6 = new QPushButton(centralwidget);
        pushButton_6->setObjectName("pushButton_6");
        pushButton_6->setGeometry(QRect(1600, 220, 44, 44));
        pushButton_6->setStyleSheet(QString::fromUtf8("/* Style for the pushButton_6 */\n"
"QPushButton#pushButton_6 {\n"
"    background-color: #B4B4B4; /* Original background color */\n"
"    color: #1A2633; /* Dark blue text for contrast */\n"
"    border: 1px solid white; /* Subtle white border */\n"
"    border-radius: 10px;\n"
"    min-width: 42px;\n"
"    min-height: 42px;\n"
"  \n"
"}\n"
"\n"
"QPushButton#pushButton_6:hover {\n"
"    background-color: #C5C5C5; /* Lighter shade on hover */\n"
"    min-width: 48px; /* Slight size increase */\n"
"    min-height: 48px;\n"
"}\n"
"\n"
"QPushButton#pushButton_6:pressed {\n"
"    background-color: #A3A3A3; /* Darker shade when pressed */\n"
"    min-width: 42px; /* Original size */\n"
"    min-height: 42px;\n"
"\n"
"}"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/teamimg/delete.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButton_6->setIcon(icon3);
        pushButton_6->setIconSize(QSize(25, 25));
        label_19 = new QLabel(centralwidget);
        label_19->setObjectName("label_19");
        label_19->setGeometry(QRect(1470, 310, 531, 31));
        QFont font6;
        font6.setFamilies({QString::fromUtf8("Impact")});
        font6.setPointSize(21);
        font6.setBold(false);
        label_19->setFont(font6);
        label_19->setStyleSheet(QString::fromUtf8("background-color: transparent;"));
        label_22 = new QLabel(centralwidget);
        label_22->setObjectName("label_22");
        label_22->setGeometry(QRect(1470, 350, 321, 31));
        QFont font7;
        font7.setFamilies({QString::fromUtf8("Arial Nova")});
        font7.setPointSize(11);
        font7.setBold(false);
        label_22->setFont(font7);
        label_22->setStyleSheet(QString::fromUtf8("background-color: transparent;"));
        listView = new QListView(centralwidget);
        listView->setObjectName("listView");
        listView->setGeometry(QRect(240, 540, 861, 371));
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
        label_4 = new QLabel(centralwidget);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(230, 490, 171, 41));
        QFont font8;
        font8.setBold(true);
        label_4->setFont(font8);
        label_4->setStyleSheet(QString::fromUtf8("/* Style for the Adjust Team title label */\n"
"QLabel#label_4 {\n"
"    background-color: transparent; /* Dark background matching the app */\n"
"    color: #FFFFFF; /* White text for contrast */\n"
"    font-size: 25px; /* Larger font for title emphasis */\n"
"    font-weight: bold; /* Bold for a strong title appearance */\n"
"    padding: 5px 10px; /* Padding for a balanced look */\n"
"}"));
        label_7 = new QLabel(centralwidget);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(380, 490, 171, 41));
        QFont font9;
        font9.setBold(false);
        label_7->setFont(font9);
        label_7->setStyleSheet(QString::fromUtf8("/* Style for the Adjust Team title label */\n"
"QLabel#label_7 {\n"
"    background-color: transparent; /* Dark background matching the app */\n"
"	color: rgb(186, 186, 186);\n"
"    font-size: 18px; /* Larger font for title emphasis */\n"
"\n"
"    padding: 5px 10px; /* Padding for a balanced look */\n"
"}"));
        pushButton_7 = new QPushButton(centralwidget);
        pushButton_7->setObjectName("pushButton_7");
        pushButton_7->setGeometry(QRect(1060, 920, 40, 40));
        pushButton_7->setStyleSheet(QString::fromUtf8("background-color: #22252D;"));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/teamimg/add.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButton_7->setIcon(icon4);
        pushButton_7->setIconSize(QSize(30, 30));
        pushButton_8 = new QPushButton(centralwidget);
        pushButton_8->setObjectName("pushButton_8");
        pushButton_8->setGeometry(QRect(1010, 920, 40, 40));
        pushButton_8->setStyleSheet(QString::fromUtf8("background-color: #22252D;"));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/teamimg/minus.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButton_8->setIcon(icon5);
        pushButton_8->setIconSize(QSize(30, 30));
        label->raise();
        dashboard_2->raise();
        dashboard_7->raise();
        dashboard_3->raise();
        dashboard_4->raise();
        pushButton->raise();
        label_3->raise();
        label_5->raise();
        label_6->raise();
        label_12->raise();
        line->raise();
        dashboard_5->raise();
        dashboard_6->raise();
        label_13->raise();
        label_14->raise();
        line_2->raise();
        label_15->raise();
        label_16->raise();
        dashboard_8->raise();
        dashboard_9->raise();
        widget_2->raise();
        label_17->raise();
        label_18->raise();
        pushButton_2->raise();
        label_20->raise();
        label_2->raise();
        pushButton_4->raise();
        pushButton_5->raise();
        pushButton_6->raise();
        label_19->raise();
        label_22->raise();
        listView->raise();
        label_4->raise();
        label_7->raise();
        pushButton_7->raise();
        pushButton_8->raise();
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        statusbar->setGeometry(QRect(0, 0, 3, 22));

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QWidget *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("teamwindow", "MainWindow", nullptr));
        label->setText(QString());
        dashboard_2->setText(QCoreApplication::translate("teamwindow", "Player", nullptr));
        dashboard_7->setText(QCoreApplication::translate("teamwindow", "Competition", nullptr));
        dashboard_3->setText(QCoreApplication::translate("teamwindow", "Match", nullptr));
        dashboard_4->setText(QCoreApplication::translate("teamwindow", "Team", nullptr));
        pushButton->setText(QString());
        pushButton_3->setText(QString());
        label_3->setText(QString());
        label_5->setText(QString());
        label_6->setText(QString());
        label_12->setText(QString());
        dashboard_5->setText(QCoreApplication::translate("teamwindow", "Language", nullptr));
        dashboard_6->setText(QCoreApplication::translate("teamwindow", "Log Out", nullptr));
        label_13->setText(QString());
        label_14->setText(QString());
        label_15->setText(QString());
        label_16->setText(QString());
        dashboard_8->setText(QCoreApplication::translate("teamwindow", "Role", nullptr));
        dashboard_9->setText(QCoreApplication::translate("teamwindow", "User name", nullptr));
        label_17->setText(QString());
        label_18->setText(QCoreApplication::translate("teamwindow", "ADD A TEAM NOW ", nullptr));
        pushButton_2->setText(QCoreApplication::translate("teamwindow", "HERE", nullptr));
        label_20->setText(QCoreApplication::translate("teamwindow", "by filling this form", nullptr));
        label_2->setText(QString());
        pushButton_4->setText(QString());
        pushButton_5->setText(QString());
        pushButton_6->setText(QString());
        label_19->setText(QCoreApplication::translate("teamwindow", "Edit  |  Adjust Team  |  Remove", nullptr));
        label_22->setText(QCoreApplication::translate("teamwindow", " You can download team details as a PDF.", nullptr));
        label_4->setText(QCoreApplication::translate("teamwindow", "To-Do-List", nullptr));
        label_7->setText(QCoreApplication::translate("teamwindow", "Training", nullptr));
        pushButton_7->setText(QString());
        pushButton_8->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class teamwindow: public Ui_teamwindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TEAMWINDOW_H
