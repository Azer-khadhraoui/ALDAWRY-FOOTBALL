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
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QLabel *label_17;
    QTabWidget *tabWidget;
    QWidget *tab_4;
    QPushButton *pushButton_3;
    QPushButton *buttonModify;
    QTableWidget *tableWidget;
    QPushButton *buttonViewDetails;
    QFrame *formFrame;
    QFormLayout *formLayout;
    QComboBox *comboBoxTri;
    QLineEdit *lineEdit_10;
    QLabel *label_25;
    QWidget *widget_2;
    QLabel *dashboard_4;
    QLabel *label_3;
    QLabel *label_15;
    QLabel *dashboard_3;
    QLabel *dashboard_2;
    QLabel *dashboard_7;
    QLabel *label_6;
    QFrame *line_2;
    QLabel *label;
    QLabel *label_5;
    QLabel *label_4;
    QLabel *label_16;
    QLabel *label_18;
    QLabel *label_20;
    QPushButton *pushButton_2;
    QFrame *line;
    QLabel *dashboard_5;
    QLabel *dashboard_6;
    QLabel *label_19;
    QLabel *label_21;
    QLabel *label_22;
    QLabel *dashboard_8;
    QLabel *dashboard_9;
    QLabel *label_23;
    QLabel *label_24;
    QPushButton *pushButton_4;
    QPushButton *pushButton_5;
    QLabel *label_26;
    QLabel *label_27;
    QLabel *label_28;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
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
        label_17 = new QLabel(centralwidget);
        label_17->setObjectName("label_17");
        label_17->setGeometry(QRect(1110, 40, 30, 30));
        label_17->setStyleSheet(QString::fromUtf8("background-color:transparent;"));
        label_17->setPixmap(QPixmap(QString::fromUtf8("../../../../../Pictures/proj QT/user.png")));
        label_17->setScaledContents(true);
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName("tabWidget");
        tabWidget->setGeometry(QRect(220, 450, 1681, 571));
        tabWidget->setLayoutDirection(Qt::LayoutDirection::LeftToRight);
        tabWidget->setStyleSheet(QString::fromUtf8("QTabWidget::pane {\n"
"    border: 2px solid #2c2f3f;\n"
"    background: #1e1f29;\n"
"    border-radius: 5px;\n"
"}\n"
"\n"
"QTabBar::tab {\n"
"    background: #1e1f29;\n"
"    color: #ffffff;\n"
"    padding: 8px 16px;\n"
"    border: 1px solid #2c2f3f;\n"
"    border-top-left-radius: 5px;\n"
"    border-top-right-radius: 5px;\n"
"}\n"
"\n"
"QTabBar::tab:selected {\n"
"    background: #2c2f3f;\n"
"    color: #ffffff;\n"
"    font-weight: bold;\n"
"    border-bottom: 2px solid #0078d7;\n"
"}\n"
"\n"
"QTabBar::tab:hover {\n"
"    background: #323546;\n"
"    color: #ffffff;\n"
"}\n"
"\n"
"QTabBar::tab:!selected {\n"
"    margin-top: 2px;\n"
"}\n"
""));
        tab_4 = new QWidget();
        tab_4->setObjectName("tab_4");
        pushButton_3 = new QPushButton(tab_4);
        pushButton_3->setObjectName("pushButton_3");
        pushButton_3->setGeometry(QRect(620, 320, 50, 50));
        pushButton_3->setStyleSheet(QString::fromUtf8("/* Style for the Delete button */\n"
"QPushButton#pushButton_3 {\n"
"    background-color: #FF1414; /* Muted dark red */\n"
"    color: #E0E6ED; /* Light gray text */\n"
"\n"
"}\n"
"QPushButton#pushButton_3:hover {\n"
"    background-color: #ff5d5d; /* Lighter red on hover */\n"
"}\n"
"QPushButton#pushButton_3:pressed {\n"
"    background-color: #6A3A3A; /* Darker red when pressed */\n"
"}\n"
"    border: 1px solid white; /* Subtle blue-gray border */\n"
"    border-radius: 1px;"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/img/deleteIcon.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButton_3->setIcon(icon);
        pushButton_3->setIconSize(QSize(25, 25));
        buttonModify = new QPushButton(tab_4);
        buttonModify->setObjectName("buttonModify");
        buttonModify->setGeometry(QRect(620, 380, 50, 50));
        buttonModify->setStyleSheet(QString::fromUtf8("/* Style for the Modify button */\n"
"QPushButton#buttonModify {\n"
"    background-color:#D8A353 ; /* Green to match the accent */\n"
"    color: #1A2633; /* Dark blue text */\n"
"\n"
"}\n"
"QPushButton#buttonModify:hover {\n"
"    background-color: #eeb35b; /* Darker green on hover */\n"
"}\n"
"QPushButton#buttonModify:pressed {\n"
"    background-color:#a37b3f ; /* Even darker green when pressed */\n"
"}\n"
"    border: 1px solid white; /* Subtle blue-gray border */\n"
"    border-radius: 1px;"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/img/editIcon.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        buttonModify->setIcon(icon1);
        buttonModify->setIconSize(QSize(25, 25));
        tableWidget = new QTableWidget(tab_4);
        tableWidget->setObjectName("tableWidget");
        tableWidget->setGeometry(QRect(30, 90, 541, 411));
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
        buttonViewDetails = new QPushButton(tab_4);
        buttonViewDetails->setObjectName("buttonViewDetails");
        buttonViewDetails->setGeometry(QRect(620, 440, 50, 50));
        buttonViewDetails->setStyleSheet(QString::fromUtf8("background-color: #192231;\n"
"border-radius: 5px ;"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/img/compType.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        buttonViewDetails->setIcon(icon2);
        buttonViewDetails->setIconSize(QSize(25, 25));
        formFrame = new QFrame(tab_4);
        formFrame->setObjectName("formFrame");
        formFrame->setGeometry(QRect(750, 30, 771, 471));
        formFrame->setFrameShape(QFrame::Shape::Box);
        formLayout = new QFormLayout(formFrame);
        formLayout->setObjectName("formLayout");
        comboBoxTri = new QComboBox(tab_4);
        comboBoxTri->setObjectName("comboBoxTri");
        comboBoxTri->setGeometry(QRect(440, 40, 111, 25));
        comboBoxTri->setStyleSheet(QString::fromUtf8("background-color: grey;\n"
"    border: 1px solid white; /* Subtle blue-gray border */\n"
"    border-radius: 15px;\n"
"color : black;\n"
""));
        lineEdit_10 = new QLineEdit(tab_4);
        lineEdit_10->setObjectName("lineEdit_10");
        lineEdit_10->setGeometry(QRect(70, 30, 361, 41));
        lineEdit_10->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"    border: 1px solid white; /* Subtle blue-gray border */\n"
"    border-radius: 15px;\n"
"color: rgb(24, 24, 24);\n"
""));
        label_25 = new QLabel(tab_4);
        label_25->setObjectName("label_25");
        label_25->setGeometry(QRect(40, 10, 44, 44));
        label_25->setStyleSheet(QString::fromUtf8("background-color: transparent;\n"
""));
        label_25->setPixmap(QPixmap(QString::fromUtf8(":/img/search.png")));
        label_25->setScaledContents(true);
        label_25->setIndent(-1);
        tabWidget->addTab(tab_4, QString());
        pushButton_3->raise();
        buttonModify->raise();
        tableWidget->raise();
        buttonViewDetails->raise();
        formFrame->raise();
        lineEdit_10->raise();
        comboBoxTri->raise();
        label_25->raise();
        widget_2 = new QWidget(centralwidget);
        widget_2->setObjectName("widget_2");
        widget_2->setGeometry(QRect(200, 120, 1851, 971));
        widget_2->setStyleSheet(QString::fromUtf8("background-color: #22252D;\n"
"border-radius:40px;\n"
"border: 1px solid #FFFFFF; /* Subtle blue-gray border */\n"
""));
        dashboard_4 = new QLabel(centralwidget);
        dashboard_4->setObjectName("dashboard_4");
        dashboard_4->setGeometry(QRect(80, 620, 61, 31));
        QFont font1;
        font1.setFamilies({QString::fromUtf8("Franklin Gothic Book")});
        font1.setPointSize(12);
        font1.setBold(false);
        dashboard_4->setFont(font1);
        dashboard_4->setStyleSheet(QString::fromUtf8("background-color: transparent;\n"
"color:#393C44;"));
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(30, 320, 35, 35));
        label_3->setStyleSheet(QString::fromUtf8("background-color: transparent;"));
        label_3->setPixmap(QPixmap(QString::fromUtf8(":/img/Group 1.png")));
        label_3->setScaledContents(true);
        label_15 = new QLabel(centralwidget);
        label_15->setObjectName("label_15");
        label_15->setGeometry(QRect(30, 520, 34, 32));
        label_15->setStyleSheet(QString::fromUtf8("background-color: transparent;"));
        label_15->setPixmap(QPixmap(QString::fromUtf8(":/img/Group 3.png")));
        label_15->setScaledContents(true);
        dashboard_3 = new QLabel(centralwidget);
        dashboard_3->setObjectName("dashboard_3");
        dashboard_3->setGeometry(QRect(80, 520, 71, 31));
        QFont font2;
        font2.setFamilies({QString::fromUtf8("Franklin Gothic Book")});
        font2.setPointSize(12);
        dashboard_3->setFont(font2);
        dashboard_3->setStyleSheet(QString::fromUtf8("background-color: transparent;\n"
"color:#393C44;"));
        dashboard_2 = new QLabel(centralwidget);
        dashboard_2->setObjectName("dashboard_2");
        dashboard_2->setGeometry(QRect(80, 320, 71, 31));
        dashboard_2->setFont(font2);
        dashboard_2->setStyleSheet(QString::fromUtf8("background-color: transparent;\n"
"color:white;"));
        dashboard_7 = new QLabel(centralwidget);
        dashboard_7->setObjectName("dashboard_7");
        dashboard_7->setGeometry(QRect(80, 420, 131, 31));
        dashboard_7->setFont(font2);
        dashboard_7->setStyleSheet(QString::fromUtf8("background-color: transparent;\n"
"color:#393C44;"));
        label_6 = new QLabel(centralwidget);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(30, 620, 28, 29));
        label_6->setStyleSheet(QString::fromUtf8("background-color: transparent;"));
        label_6->setPixmap(QPixmap(QString::fromUtf8(":/img/Group 2.png")));
        label_6->setScaledContents(true);
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
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setGeometry(QRect(50, 30, 85, 85));
        label->setPixmap(QPixmap(QString::fromUtf8(":/img/logo football.png")));
        label->setScaledContents(true);
        label_5 = new QLabel(centralwidget);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(30, 420, 27, 27));
        label_5->setStyleSheet(QString::fromUtf8("background-color: transparent;"));
        label_5->setPixmap(QPixmap(QString::fromUtf8(":/img/Vector.png")));
        label_5->setScaledContents(true);
        label_4 = new QLabel(centralwidget);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(220, 10, 1200, 521));
        label_4->setStyleSheet(QString::fromUtf8("background-color:transparent;"));
        label_4->setPixmap(QPixmap(QString::fromUtf8(":/img/addPIC.png")));
        label_4->setScaledContents(true);
        label_16 = new QLabel(centralwidget);
        label_16->setObjectName("label_16");
        label_16->setGeometry(QRect(660, 66, 480, 381));
        label_16->setStyleSheet(QString::fromUtf8("background-color:transparent;"));
        label_16->setPixmap(QPixmap(QString::fromUtf8(":/img/hannibal.png")));
        label_16->setScaledContents(true);
        label_18 = new QLabel(centralwidget);
        label_18->setObjectName("label_18");
        label_18->setGeometry(QRect(270, 200, 391, 31));
        QFont font3;
        font3.setFamilies({QString::fromUtf8("Speedo")});
        font3.setPointSize(25);
        font3.setBold(false);
        label_18->setFont(font3);
        label_20 = new QLabel(centralwidget);
        label_20->setObjectName("label_20");
        label_20->setGeometry(QRect(270, 250, 181, 31));
        QFont font4;
        font4.setFamilies({QString::fromUtf8("Arial Nova")});
        font4.setPointSize(13);
        font4.setBold(false);
        label_20->setFont(font4);
        pushButton_2 = new QPushButton(centralwidget);
        pushButton_2->setObjectName("pushButton_2");
        pushButton_2->setGeometry(QRect(270, 340, 141, 41));
        QFont font5;
        font5.setFamilies({QString::fromUtf8("HP Simplified Jpan")});
        font5.setPointSize(14);
        pushButton_2->setFont(font5);
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
        line = new QFrame(centralwidget);
        line->setObjectName("line");
        line->setGeometry(QRect(30, 790, 135, 1));
        line->setStyleSheet(QString::fromUtf8("background-color: #393C44;"));
        line->setFrameShape(QFrame::Shape::HLine);
        line->setFrameShadow(QFrame::Shadow::Sunken);
        dashboard_5 = new QLabel(centralwidget);
        dashboard_5->setObjectName("dashboard_5");
        dashboard_5->setGeometry(QRect(80, 850, 71, 31));
        dashboard_5->setFont(font2);
        dashboard_5->setStyleSheet(QString::fromUtf8("background-color: transparent;\n"
"color: rgb(158, 158, 158);"));
        dashboard_6 = new QLabel(centralwidget);
        dashboard_6->setObjectName("dashboard_6");
        dashboard_6->setGeometry(QRect(80, 920, 71, 31));
        dashboard_6->setFont(font2);
        dashboard_6->setStyleSheet(QString::fromUtf8("background-color: transparent;\n"
"color: rgb(158, 158, 158);"));
        label_19 = new QLabel(centralwidget);
        label_19->setObjectName("label_19");
        label_19->setGeometry(QRect(30, 920, 28, 29));
        label_19->setStyleSheet(QString::fromUtf8("background-color: transparent;"));
        label_19->setPixmap(QPixmap(QString::fromUtf8(":/img/logout.png")));
        label_19->setScaledContents(true);
        label_21 = new QLabel(centralwidget);
        label_21->setObjectName("label_21");
        label_21->setGeometry(QRect(30, 850, 28, 29));
        label_21->setStyleSheet(QString::fromUtf8("background-color: transparent;"));
        label_21->setPixmap(QPixmap(QString::fromUtf8(":/img/language.png")));
        label_21->setScaledContents(true);
        label_22 = new QLabel(centralwidget);
        label_22->setObjectName("label_22");
        label_22->setGeometry(QRect(1800, 30, 60, 60));
        label_22->setStyleSheet(QString::fromUtf8("background-color: transparent;"));
        label_22->setPixmap(QPixmap(QString::fromUtf8(":/img/Layer 2.png")));
        label_22->setScaledContents(true);
        dashboard_8 = new QLabel(centralwidget);
        dashboard_8->setObjectName("dashboard_8");
        dashboard_8->setGeometry(QRect(1710, 40, 71, 31));
        dashboard_8->setFont(font2);
        dashboard_8->setStyleSheet(QString::fromUtf8("background-color: transparent;\n"
"color:#393C44;"));
        dashboard_9 = new QLabel(centralwidget);
        dashboard_9->setObjectName("dashboard_9");
        dashboard_9->setGeometry(QRect(1720, 60, 81, 31));
        dashboard_9->setFont(font1);
        dashboard_9->setStyleSheet(QString::fromUtf8("background-color: transparent;\n"
"color:white;"));
        label_23 = new QLabel(centralwidget);
        label_23->setObjectName("label_23");
        label_23->setGeometry(QRect(1870, 60, 16, 10));
        label_23->setStyleSheet(QString::fromUtf8("background-color: transparent;"));
        label_23->setPixmap(QPixmap(QString::fromUtf8(":/img/Vectorrrr.png")));
        label_23->setScaledContents(true);
        label_24 = new QLabel(centralwidget);
        label_24->setObjectName("label_24");
        label_24->setGeometry(QRect(1510, 140, 391, 325));
        label_24->setStyleSheet(QString::fromUtf8("background-color:transparent;"));
        label_24->setPixmap(QPixmap(QString::fromUtf8(":/img/rectDD.png")));
        label_24->setScaledContents(true);
        pushButton_4 = new QPushButton(centralwidget);
        pushButton_4->setObjectName("pushButton_4");
        pushButton_4->setGeometry(QRect(1530, 180, 64, 64));
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
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/img/pencil.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButton_4->setIcon(icon3);
        pushButton_4->setIconSize(QSize(42, 42));
        pushButton_5 = new QPushButton(centralwidget);
        pushButton_5->setObjectName("pushButton_5");
        pushButton_5->setGeometry(QRect(1610, 190, 54, 54));
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
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/img/delete.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButton_5->setIcon(icon4);
        pushButton_5->setIconSize(QSize(27, 27));
        label_26 = new QLabel(centralwidget);
        label_26->setObjectName("label_26");
        label_26->setGeometry(QRect(1530, 270, 531, 31));
        QFont font6;
        font6.setFamilies({QString::fromUtf8("Impact")});
        font6.setPointSize(19);
        font6.setBold(false);
        label_26->setFont(font6);
        label_26->setStyleSheet(QString::fromUtf8("background-color: transparent;"));
        label_27 = new QLabel(centralwidget);
        label_27->setObjectName("label_27");
        label_27->setGeometry(QRect(1525, 310, 331, 31));
        QFont font7;
        font7.setFamilies({QString::fromUtf8("Arial Nova")});
        font7.setPointSize(11);
        font7.setBold(false);
        label_27->setFont(font7);
        label_27->setStyleSheet(QString::fromUtf8("background-color: transparent;"));
        label_28 = new QLabel(centralwidget);
        label_28->setObjectName("label_28");
        label_28->setGeometry(QRect(1530, 330, 331, 31));
        label_28->setFont(font7);
        label_28->setStyleSheet(QString::fromUtf8("background-color: transparent;"));
        MainWindow->setCentralWidget(centralwidget);
        label_17->raise();
        widget_2->raise();
        dashboard_4->raise();
        label_3->raise();
        label_15->raise();
        dashboard_3->raise();
        dashboard_2->raise();
        dashboard_7->raise();
        label_6->raise();
        line_2->raise();
        label->raise();
        label_5->raise();
        label_4->raise();
        label_16->raise();
        label_18->raise();
        label_20->raise();
        pushButton_2->raise();
        tabWidget->raise();
        line->raise();
        dashboard_5->raise();
        dashboard_6->raise();
        label_19->raise();
        label_21->raise();
        label_22->raise();
        dashboard_8->raise();
        dashboard_9->raise();
        label_23->raise();
        label_24->raise();
        pushButton_4->raise();
        pushButton_5->raise();
        label_26->raise();
        label_27->raise();
        label_28->raise();
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        label_17->setText(QString());
        pushButton_3->setText(QString());
        buttonModify->setText(QString());
        buttonViewDetails->setText(QString());
        label_25->setText(QString());
        tabWidget->setTabText(tabWidget->indexOf(tab_4), QCoreApplication::translate("MainWindow", "          Display Player           ", nullptr));
        dashboard_4->setText(QCoreApplication::translate("MainWindow", "Team", nullptr));
        label_3->setText(QString());
        label_15->setText(QString());
        dashboard_3->setText(QCoreApplication::translate("MainWindow", "Match", nullptr));
        dashboard_2->setText(QCoreApplication::translate("MainWindow", "Player", nullptr));
        dashboard_7->setText(QCoreApplication::translate("MainWindow", "Competition", nullptr));
        label_6->setText(QString());
        label->setText(QString());
        label_5->setText(QString());
        label_4->setText(QString());
        label_16->setText(QString());
        label_18->setText(QCoreApplication::translate("MainWindow", "ADD A PLAYER", nullptr));
        label_20->setText(QCoreApplication::translate("MainWindow", "by filling this form", nullptr));
        pushButton_2->setText(QCoreApplication::translate("MainWindow", "HERE", nullptr));
        dashboard_5->setText(QCoreApplication::translate("MainWindow", "About", nullptr));
        dashboard_6->setText(QCoreApplication::translate("MainWindow", "Log Out", nullptr));
        label_19->setText(QString());
        label_21->setText(QString());
        label_22->setText(QString());
        dashboard_8->setText(QCoreApplication::translate("MainWindow", "Role", nullptr));
        dashboard_9->setText(QCoreApplication::translate("MainWindow", "User name", nullptr));
        label_23->setText(QString());
        label_24->setText(QString());
        pushButton_4->setText(QString());
        pushButton_5->setText(QString());
        label_26->setText(QCoreApplication::translate("MainWindow", "Edit  |  Delete Players", nullptr));
        label_27->setText(QCoreApplication::translate("MainWindow", " You can view players", nullptr));
        label_28->setText(QCoreApplication::translate("MainWindow", "details .", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
