/********************************************************************************
** Form generated from reading UI file 'tableau1.ui'
**
** Created by: Qt User Interface Compiler version 6.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TABLEAU1_H
#define UI_TABLEAU1_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TableauDialog
{
public:
    QLabel *label_3;
    QLabel *label_2;
    QLineEdit *lineEdit;
    QComboBox *comboBox;
    QComboBox *comboBox_2;
    QTableView *test;
    QPushButton *pushButton_2;
    QPushButton *pushButton;
    QPushButton *pushButton_5;
    QWidget *monthCalendarWidget;
    QVBoxLayout *monthCalendarLayout;
    QWidget *widget;
    QGridLayout *monthGridLayout;
    QPushButton *decemberButton;
    QPushButton *mayButton;
    QPushButton *septemberButton;
    QPushButton *januaryButton;
    QPushButton *aprilButton;
    QPushButton *juneButton;
    QPushButton *augustButton;
    QPushButton *novemberButton;
    QPushButton *marchButton;
    QPushButton *octoberButton;
    QPushButton *februaryButton;
    QPushButton *julyButton;
    QFrame *line;
    QWidget *widget_2;
    QComboBox *yearComboBox;
    QLabel *label;
    QListWidget *listWidget_2;
    QLabel *comp_name;
    QLabel *team_name;
    QLabel *label_15;
    QLabel *label_16;
    QLabel *team_logo;
    QLabel *label_4;

    void setupUi(QDialog *TableauDialog)
    {
        if (TableauDialog->objectName().isEmpty())
            TableauDialog->setObjectName("TableauDialog");
        TableauDialog->resize(1187, 714);
        TableauDialog->setStyleSheet(QString::fromUtf8("background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 #1b1f2a, stop:1 #10131a);"));
        label_3 = new QLabel(TableauDialog);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(510, 30, 271, 41));
        QFont font;
        font.setBold(true);
        label_3->setFont(font);
        label_3->setStyleSheet(QString::fromUtf8("/* Style for the Adjust Team title label */\n"
"QLabel#label_3 {\n"
"    background-color: transparent; /* Dark background matching the app */\n"
"    color: #FFFFFF; /* White text for contrast */\n"
"    font-size: 25px; /* Larger font for title emphasis */\n"
"    font-weight: bold; /* Bold for a strong title appearance */\n"
"    padding: 5px 10px; /* Padding for a balanced look */\n"
"}"));
        label_2 = new QLabel(TableauDialog);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(20, 130, 44, 44));
        label_2->setStyleSheet(QString::fromUtf8("background-color: transparent;"));
        label_2->setPixmap(QPixmap(QString::fromUtf8(":/images/search.png")));
        label_2->setScaledContents(true);
        lineEdit = new QLineEdit(TableauDialog);
        lineEdit->setObjectName("lineEdit");
        lineEdit->setGeometry(QRect(50, 140, 411, 31));
        lineEdit->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"    border: 1px solid white; /* Subtle blue-gray border */\n"
"    border-radius: 10px;\n"
"color: rgb(24, 24, 24);"));
        comboBox = new QComboBox(TableauDialog);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName("comboBox");
        comboBox->setGeometry(QRect(360, 150, 16, 17));
        comboBox->setStyleSheet(QString::fromUtf8("background-color: #BC8D47;\n"
"color: #e0f7fa;\n"
"border-radius: 4px;"));
        comboBox->setEditable(false);
        comboBox->setIconSize(QSize(9, 9));
        comboBox_2 = new QComboBox(TableauDialog);
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->setObjectName("comboBox_2");
        comboBox_2->setGeometry(QRect(380, 150, 71, 17));
        comboBox_2->setStyleSheet(QString::fromUtf8("background-color: #BC8D47;\n"
"color: #e0f7fa;\n"
"border-radius: 4px;"));
        test = new QTableView(TableauDialog);
        test->setObjectName("test");
        test->setGeometry(QRect(20, 190, 641, 411));
        test->setStyleSheet(QString::fromUtf8("/* Style for the tableWidget */\n"
"QTableView {\n"
"    background-color: #2D3748; /* Dark background matching the app */\n"
"    color: #FFFFFF; /* White text for readability */\n"
"    border: 1px solid #4A4E58; /* Subtle border matching button hover color */\n"
"    gridline-color: #4A4E58; /* Subtle grid lines */\n"
"}\n"
"\n"
"/* Style for table items */\n"
"QTableView::item {\n"
"    border: 1px solid #4A4E58; /* Subtle cell borders */\n"
"    padding: 5px; /* Spacing inside cells */\n"
"}\n"
"\n"
"/* Alternating row colors */\n"
"QTableView::item:nth-child(even) {\n"
"    background-color: #2D3748; /* Darker shade for even rows */\n"
"}\n"
"\n"
"QTableView::item:nth-child(odd) {\n"
"    background-color: #394252; /* Slightly lighter shade for odd rows */\n"
"}\n"
"\n"
"/* Hover effect for rows */\n"
"QTableView::item:hover {\n"
"    background-color: #4A4E58; /* Lighter shade on hover */\n"
"}\n"
"\n"
"/* Style for the header */\n"
"QHeaderView::section {\n"
"    background-color: #F5A623; /* Accent co"
                        "lor for header */\n"
"    color: #1A2633; /* Dark text for contrast */\n"
"    font-weight: bold; /* Bold header text */\n"
"    border: 1px solid #4A4E58; /* Border to match table */\n"
"    padding: 5px; /* Spacing inside header */\n"
"}\n"
"\n"
"/* Remove selection background */\n"
"QTableView::item:selected {\n"
"    background-color: #4A4E58; /* Same as hover to avoid clashing */\n"
"    color: #FFFFFF; /* Keep text white */\n"
"}"));
        pushButton_2 = new QPushButton(TableauDialog);
        pushButton_2->setObjectName("pushButton_2");
        pushButton_2->setGeometry(QRect(560, 620, 50, 50));
        pushButton_2->setStyleSheet(QString::fromUtf8("/* Style for the Modify button */\n"
"QPushButton#pushButton_2 {\n"
"    background-color:#D8A353 ; /* Green to match the accent */\n"
"    color: #1A2633; /* Dark blue text */\n"
"}\n"
"QPushButton#pushButton_2:hover {\n"
"    background-color: #eeb35b; /* Darker green on hover */\n"
"}\n"
"QPushButton#pushButton_2:pressed {\n"
"    background-color:#a37b3f ; /* Even darker green when pressed */\n"
"}\n"
"    border: 1px solid white; /* Subtle blue-gray border */\n"
"    border-radius: 1px;"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/images/editIcon.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButton_2->setIcon(icon);
        pushButton_2->setIconSize(QSize(25, 25));
        pushButton = new QPushButton(TableauDialog);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(610, 620, 50, 50));
        pushButton->setStyleSheet(QString::fromUtf8("/* Style for the Delete button */\n"
"QPushButton#pushButton {\n"
"    background-color: #FF1414; /* Muted dark red */\n"
"    color: #E0E6ED; /* Light gray text */\n"
"}\n"
"QPushButton#pushButton:hover {\n"
"    background-color: #ff5d5d; /* Lighter red on hover */\n"
"}\n"
"QPushButton#pushButton:pressed {\n"
"    background-color: #6A3A3A; /* Darker red when pressed */\n"
"}\n"
"    border: 1px solid white; /* Subtle blue-gray border */\n"
"    border-radius: 1px;"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/images/deleteIcon.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButton->setIcon(icon1);
        pushButton->setIconSize(QSize(25, 25));
        pushButton_5 = new QPushButton(TableauDialog);
        pushButton_5->setObjectName("pushButton_5");
        pushButton_5->setGeometry(QRect(510, 620, 50, 50));
        QFont font1;
        font1.setFamilies({QString::fromUtf8("Arial")});
        font1.setPointSize(12);
        pushButton_5->setFont(font1);
        pushButton_5->setStyleSheet(QString::fromUtf8("/* Style for the Modify button */\n"
"QPushButton#pushButton_5 {\n"
"    background-color: #2B2F37;\n"
"}\n"
"QPushButton#pushButton_5:hover {\n"
"    background-color:#343842 ; /* Darker green on hover */\n"
"}\n"
"QPushButton#pushButton_5:pressed {\n"
"    background-color: #1e2127; /* Even darker green when pressed */\n"
"}\n"
"    border: 1px solid white; /* Subtle blue-gray border */\n"
"    border-radius: 1px;"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/images/generate.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButton_5->setIcon(icon2);
        pushButton_5->setIconSize(QSize(25, 25));
        monthCalendarWidget = new QWidget(TableauDialog);
        monthCalendarWidget->setObjectName("monthCalendarWidget");
        monthCalendarWidget->setGeometry(QRect(720, 140, 441, 241));
        monthCalendarWidget->setStyleSheet(QString::fromUtf8("\n"
"background-color: rgb(255, 255, 255);\n"
"    color: #FFFFFF;       /* White text for contrast */\n"
"    border: 1px solid #2E3A3B;  /* Slightly lighter border for definition */\n"
"    font-family: \"Arial\";\n"
"    font-size: 12px;\n"
"    border: 0px solid white; /* Subtle blue-gray border */\n"
"    border-radius: 20px;\n"
""));
        monthCalendarLayout = new QVBoxLayout(monthCalendarWidget);
        monthCalendarLayout->setSpacing(10);
        monthCalendarLayout->setObjectName("monthCalendarLayout");
        widget = new QWidget(monthCalendarWidget);
        widget->setObjectName("widget");
        widget->setStyleSheet(QString::fromUtf8("border:10px;\n"
"    margin-left: 10px;\n"
"    margin-right: 10px;\n"
"    margin-TOP: 10px;\n"
"    margin-BOTTOM: 10px;"));
        monthGridLayout = new QGridLayout(widget);
        monthGridLayout->setSpacing(10);
        monthGridLayout->setObjectName("monthGridLayout");
        decemberButton = new QPushButton(widget);
        decemberButton->setObjectName("decemberButton");
        decemberButton->setMinimumSize(QSize(90, 50));
        decemberButton->setStyleSheet(QString::fromUtf8("/* Style for the calendar buttons (januaryButton, februaryButton, etc.) */\n"
"QPushButton#decemberButton {\n"
"    background: #3e4d64;\n"
"    color: #FFFFFF; /* White text for contrast */\n"
"    border: 2px solid white; /* Teal/cyan border to match app theme */\n"
"    border-radius: 8px; /* Rounded corners */\n"
"    padding: 12px 20px;\n"
"    font-family: 'Arial', sans-serif;\n"
"    font-size: 16px;\n"
"    font-weight: 500;\n"
"    cursor: pointer;\n"
"    box-shadow: 0 2px 5px rgba(0, 0, 0, 0.3); /* Subtle shadow */\n"
"    transition: all 0.3s ease; /* Smooth transitions */\n"
"}"));

        monthGridLayout->addWidget(decemberButton, 2, 3, 1, 1);

        mayButton = new QPushButton(widget);
        mayButton->setObjectName("mayButton");
        mayButton->setMinimumSize(QSize(90, 50));
        mayButton->setStyleSheet(QString::fromUtf8("/* Style for the calendar buttons (januaryButton, februaryButton, etc.) */\n"
"QPushButton#mayButton {\n"
"     background: #3e4d64;\n"
"    color: #FFFFFF; /* White text for contrast */\n"
"    border: 2px solid white; /* Teal/cyan border to match app theme */\n"
"    border-radius: 8px; /* Rounded corners */\n"
"    padding: 12px 20px;\n"
"    font-family: 'Arial', sans-serif;\n"
"    font-size: 16px;\n"
"    font-weight: 500;\n"
"    cursor: pointer;\n"
"    box-shadow: 0 2px 5px rgba(0, 0, 0, 0.3); /* Subtle shadow */\n"
"    transition: all 0.3s ease; /* Smooth transitions */\n"
"}"));

        monthGridLayout->addWidget(mayButton, 1, 0, 1, 1);

        septemberButton = new QPushButton(widget);
        septemberButton->setObjectName("septemberButton");
        septemberButton->setMinimumSize(QSize(90, 50));
        septemberButton->setStyleSheet(QString::fromUtf8("/* Style for the calendar buttons (januaryButton, februaryButton, etc.) */\n"
"QPushButton#septemberButton {\n"
"     background: #3e4d64;\n"
"    color: #FFFFFF; /* White text for contrast */\n"
"    border: 2px solid white; /* Teal/cyan border to match app theme */\n"
"    border-radius: 8px; /* Rounded corners */\n"
"    padding: 12px 20px;\n"
"    font-family: 'Arial', sans-serif;\n"
"    font-size: 16px;\n"
"    font-weight: 500;\n"
"    cursor: pointer;\n"
"    box-shadow: 0 2px 5px rgba(0, 0, 0, 0.3); /* Subtle shadow */\n"
"    transition: all 0.3s ease; /* Smooth transitions */\n"
"}"));

        monthGridLayout->addWidget(septemberButton, 2, 0, 1, 1);

        januaryButton = new QPushButton(widget);
        januaryButton->setObjectName("januaryButton");
        januaryButton->setMinimumSize(QSize(90, 50));
        QFont font2;
        font2.setFamilies({QString::fromUtf8("Arial")});
        font2.setWeight(QFont::Medium);
        januaryButton->setFont(font2);
        januaryButton->setStyleSheet(QString::fromUtf8("/* Style for the calendar buttons (januaryButton, februaryButton, etc.) */\n"
"QPushButton#januaryButton {\n"
"   background-color: #3e4d64;\n"
"    color: #FFFFFF; /* White text for contrast */\n"
"    border: 2px solid white; /* Teal/cyan border to match app theme */\n"
"    border-radius: 8px; /* Rounded corners */\n"
"    padding: 12px 20px;\n"
"    font-family: 'Arial', sans-serif;\n"
"    font-size: 16px;\n"
"    font-weight: 500;\n"
"    cursor: pointer;\n"
"    box-shadow: 0 2px 5px rgba(0, 0, 0, 0.3); /* Subtle shadow */\n"
"    transition: all 0.3s ease; /* Smooth transitions */\n"
"}"));

        monthGridLayout->addWidget(januaryButton, 0, 0, 1, 1);

        aprilButton = new QPushButton(widget);
        aprilButton->setObjectName("aprilButton");
        aprilButton->setMinimumSize(QSize(90, 50));
        aprilButton->setStyleSheet(QString::fromUtf8("/* Style for the calendar buttons (januaryButton, februaryButton, etc.) */\n"
"QPushButton#aprilButton {\n"
"    background: #3e4d64;\n"
"    color: #FFFFFF; /* White text for contrast */\n"
"    border: 2px solid white; /* Teal/cyan border to match app theme */\n"
"    border-radius: 8px; /* Rounded corners */\n"
"    padding: 12px 20px;\n"
"    font-family: 'Arial', sans-serif;\n"
"    font-size: 16px;\n"
"    font-weight: 500;\n"
"    cursor: pointer;\n"
"    box-shadow: 0 2px 5px rgba(0, 0, 0, 0.3); /* Subtle shadow */\n"
"    transition: all 0.3s ease; /* Smooth transitions */\n"
"}"));

        monthGridLayout->addWidget(aprilButton, 0, 3, 1, 1);

        juneButton = new QPushButton(widget);
        juneButton->setObjectName("juneButton");
        juneButton->setMinimumSize(QSize(90, 50));
        juneButton->setStyleSheet(QString::fromUtf8("/* Style for the calendar buttons (januaryButton, februaryButton, etc.) */\n"
"QPushButton#juneButton {\n"
"       background: #3e4d64;\n"
"    color: #FFFFFF; /* White text for contrast */\n"
"    border: 2px solid white; /* Teal/cyan border to match app theme */\n"
"    border-radius: 8px; /* Rounded corners */\n"
"    padding: 12px 20px;\n"
"    font-family: 'Arial', sans-serif;\n"
"    font-size: 16px;\n"
"    font-weight: 500;\n"
"    cursor: pointer;\n"
"    box-shadow: 0 2px 5px rgba(0, 0, 0, 0.3); /* Subtle shadow */\n"
"    transition: all 0.3s ease; /* Smooth transitions */\n"
"}"));

        monthGridLayout->addWidget(juneButton, 1, 1, 1, 1);

        augustButton = new QPushButton(widget);
        augustButton->setObjectName("augustButton");
        augustButton->setMinimumSize(QSize(90, 50));
        augustButton->setStyleSheet(QString::fromUtf8("/* Style for the calendar buttons (januaryButton, februaryButton, etc.) */\n"
"QPushButton#augustButton {\n"
"       background: #3e4d64;\n"
"    color: #FFFFFF; /* White text for contrast */\n"
"    border: 2px solid white; /* Teal/cyan border to match app theme */\n"
"    border-radius: 8px; /* Rounded corners */\n"
"    padding: 12px 20px;\n"
"    font-family: 'Arial', sans-serif;\n"
"    font-size: 16px;\n"
"    font-weight: 500;\n"
"    cursor: pointer;\n"
"    box-shadow: 0 2px 5px rgba(0, 0, 0, 0.3); /* Subtle shadow */\n"
"    transition: all 0.3s ease; /* Smooth transitions */\n"
"}"));

        monthGridLayout->addWidget(augustButton, 1, 3, 1, 1);

        novemberButton = new QPushButton(widget);
        novemberButton->setObjectName("novemberButton");
        novemberButton->setMinimumSize(QSize(90, 50));
        novemberButton->setStyleSheet(QString::fromUtf8("/* Style for the calendar buttons (januaryButton, februaryButton, etc.) */\n"
"QPushButton#novemberButton {\n"
"      background: #5a7091;\n"
"    color: #FFFFFF; /* White text for contrast */\n"
"    border: 2px solid white; /* Teal/cyan border to match app theme */\n"
"    border-radius: 8px; /* Rounded corners */\n"
"    padding: 12px 20px;\n"
"    font-family: 'Arial', sans-serif;\n"
"    font-size: 16px;\n"
"    font-weight: 500;\n"
"    cursor: pointer;\n"
"    box-shadow: 0 2px 5px rgba(0, 0, 0, 0.3); /* Subtle shadow */\n"
"    transition: all 0.3s ease; /* Smooth transitions */\n"
"}"));

        monthGridLayout->addWidget(novemberButton, 2, 2, 1, 1);

        marchButton = new QPushButton(widget);
        marchButton->setObjectName("marchButton");
        marchButton->setMinimumSize(QSize(90, 50));
        marchButton->setStyleSheet(QString::fromUtf8("/* Style for the calendar buttons (januaryButton, februaryButton, etc.) */\n"
"QPushButton#marchButton {\n"
"       background-color:#3e4d64;\n"
"    color: #FFFFFF; /* White text for contrast */\n"
"    border: 2px solid white; /* Teal/cyan border to match app theme */\n"
"    border-radius: 8px; /* Rounded corners */\n"
"    padding: 12px 20px;\n"
"    font-family: 'Arial', sans-serif;\n"
"    font-size: 16px;\n"
"    font-weight: 500;\n"
"    cursor: pointer;\n"
"    box-shadow: 0 2px 5px rgba(0, 0, 0, 0.3); /* Subtle shadow */\n"
"    transition: all 0.3s ease; /* Smooth transitions */\n"
"}"));

        monthGridLayout->addWidget(marchButton, 0, 2, 1, 1);

        octoberButton = new QPushButton(widget);
        octoberButton->setObjectName("octoberButton");
        octoberButton->setMinimumSize(QSize(90, 50));
        octoberButton->setStyleSheet(QString::fromUtf8("/* Style for the calendar buttons (januaryButton, februaryButton, etc.) */\n"
"QPushButton#octoberButton {\n"
"     background: #5a7091;\n"
"    color: #FFFFFF; /* White text for contrast */\n"
"    border: 2px solid white; /* Teal/cyan border to match app theme */\n"
"    border-radius: 8px; /* Rounded corners */\n"
"    padding: 12px 20px;\n"
"    font-family: 'Arial', sans-serif;\n"
"    font-size: 16px;\n"
"    font-weight: 500;\n"
"    cursor: pointer;\n"
"    box-shadow: 0 2px 5px rgba(0, 0, 0, 0.3); /* Subtle shadow */\n"
"    transition: all 0.3s ease; /* Smooth transitions */\n"
"}"));

        monthGridLayout->addWidget(octoberButton, 2, 1, 1, 1);

        februaryButton = new QPushButton(widget);
        februaryButton->setObjectName("februaryButton");
        februaryButton->setMinimumSize(QSize(90, 50));
        februaryButton->setStyleSheet(QString::fromUtf8("/* Style for the calendar buttons (januaryButton, februaryButton, etc.) */\n"
"QPushButton#februaryButton {\n"
"       background-color:#3e4d64;\n"
"    color: #FFFFFF; /* White text for contrast */\n"
"    border: 2px solid white; /* Teal/cyan border to match app theme */\n"
"    border-radius: 8px; /* Rounded corners */\n"
"    padding: 12px 20px;\n"
"    font-family: 'Arial', sans-serif;\n"
"    font-size: 16px;\n"
"    font-weight: 500;\n"
"    cursor: pointer;\n"
"    box-shadow: 0 2px 5px rgba(0, 0, 0, 0.3); /* Subtle shadow */\n"
"    transition: all 0.3s ease; /* Smooth transitions */\n"
"}"));

        monthGridLayout->addWidget(februaryButton, 0, 1, 1, 1);

        julyButton = new QPushButton(widget);
        julyButton->setObjectName("julyButton");
        julyButton->setMinimumSize(QSize(90, 50));
        julyButton->setStyleSheet(QString::fromUtf8("/* Style for the calendar buttons (januaryButton, februaryButton, etc.) */\n"
"QPushButton#julyButton {\n"
"   background: #3e4d64;\n"
"    color: #FFFFFF; /* White text for contrast */\n"
"    border: 2px solid white; /* Teal/cyan border to match app theme */\n"
"    border-radius: 8px; /* Rounded corners */\n"
"    padding: 12px 20px;\n"
"    font-family: 'Arial', sans-serif;\n"
"    font-size: 16px;\n"
"    font-weight: 500;\n"
"    cursor: pointer;\n"
"    box-shadow: 0 2px 5px rgba(0, 0, 0, 0.3); /* Subtle shadow */\n"
"    transition: all 0.3s ease; /* Smooth transitions */\n"
"}"));

        monthGridLayout->addWidget(julyButton, 1, 2, 1, 1);


        monthCalendarLayout->addWidget(widget);

        line = new QFrame(TableauDialog);
        line->setObjectName("line");
        line->setGeometry(QRect(687, 150, 1, 529));
        line->setStyleSheet(QString::fromUtf8("background-color: grey;"));
        line->setFrameShape(QFrame::Shape::VLine);
        line->setFrameShadow(QFrame::Shadow::Sunken);
        widget_2 = new QWidget(TableauDialog);
        widget_2->setObjectName("widget_2");
        widget_2->setGeometry(QRect(750, 120, 381, 41));
        widget_2->setStyleSheet(QString::fromUtf8("background-color: #2D3748; \n"
"    border: 1px solid white; /* Subtle blue-gray border */\n"
"    border-radius: 10px;"));
        yearComboBox = new QComboBox(TableauDialog);
        yearComboBox->addItem(QString());
        yearComboBox->addItem(QString());
        yearComboBox->addItem(QString());
        yearComboBox->setObjectName("yearComboBox");
        yearComboBox->setGeometry(QRect(800, 120, 311, 31));
        QFont font3;
        font3.setPointSize(14);
        font3.setBold(true);
        yearComboBox->setFont(font3);
        yearComboBox->setStyleSheet(QString::fromUtf8("background-color: transparent;\n"
"    border: 0px solid white; /* Subtle blue-gray border */\n"
"    border-radius: 1px;"));
        label = new QLabel(TableauDialog);
        label->setObjectName("label");
        label->setGeometry(QRect(770, 130, 17, 17));
        label->setStyleSheet(QString::fromUtf8("background-color: TRANSPARENT;"));
        label->setPixmap(QPixmap(QString::fromUtf8(":/images/StartDate.png")));
        label->setScaledContents(true);
        listWidget_2 = new QListWidget(TableauDialog);
        listWidget_2->setObjectName("listWidget_2");
        listWidget_2->setGeometry(QRect(720, 430, 441, 241));
        listWidget_2->setStyleSheet(QString::fromUtf8("background-color: #D9D9D9;\n"
"border-radius: 30px;\n"
"padding: 10px;\n"
"border: 1px solid ;\n"
"font-size: 16px;\n"
"color: #00e676;"));
        comp_name = new QLabel(TableauDialog);
        comp_name->setObjectName("comp_name");
        comp_name->setGeometry(QRect(750, 440, 351, 41));
        QFont font4;
        font4.setPointSize(12);
        font4.setBold(true);
        comp_name->setFont(font4);
        comp_name->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);\n"
"background-color: transparent;"));
        team_name = new QLabel(TableauDialog);
        team_name->setObjectName("team_name");
        team_name->setGeometry(QRect(750, 490, 251, 51));
        QFont font5;
        font5.setPointSize(25);
        font5.setBold(true);
        team_name->setFont(font5);
        team_name->setStyleSheet(QString::fromUtf8("background-color: transparent;color:orange;"));
        label_15 = new QLabel(TableauDialog);
        label_15->setObjectName("label_15");
        label_15->setGeometry(QRect(850, 390, 211, 41));
        QFont font6;
        font6.setPointSize(13);
        label_15->setFont(font6);
        label_15->setStyleSheet(QString::fromUtf8("\n"
"background-color: transparent;\n"
"color:#B4B4B4;"));
        label_16 = new QLabel(TableauDialog);
        label_16->setObjectName("label_16");
        label_16->setGeometry(QRect(730, 390, 161, 41));
        QFont font7;
        font7.setPointSize(15);
        label_16->setFont(font7);
        label_16->setStyleSheet(QString::fromUtf8("letter-spacing:2px;\n"
"background-color: transparent;"));
        team_logo = new QLabel(TableauDialog);
        team_logo->setObjectName("team_logo");
        team_logo->setGeometry(QRect(890, 560, 121, 91));
        team_logo->setFont(font5);
        team_logo->setStyleSheet(QString::fromUtf8("background-color: transparent;color:orange;"));
        label_4 = new QLabel(TableauDialog);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(721, 430, 461, 271));
        label_4->setStyleSheet(QString::fromUtf8("background-color: transparent;"));
        label_4->setPixmap(QPixmap(QString::fromUtf8(":/images/PREDICTION.png")));
        label_4->setScaledContents(true);
        listWidget_2->raise();
        label_4->raise();
        label_3->raise();
        lineEdit->raise();
        comboBox->raise();
        comboBox_2->raise();
        label_2->raise();
        test->raise();
        pushButton_2->raise();
        pushButton->raise();
        pushButton_5->raise();
        monthCalendarWidget->raise();
        line->raise();
        widget_2->raise();
        yearComboBox->raise();
        label->raise();
        comp_name->raise();
        team_name->raise();
        label_15->raise();
        label_16->raise();
        team_logo->raise();

        retranslateUi(TableauDialog);

        QMetaObject::connectSlotsByName(TableauDialog);
    } // setupUi

    void retranslateUi(QDialog *TableauDialog)
    {
        TableauDialog->setWindowTitle(QCoreApplication::translate("TableauDialog", "Tableau Dialog", nullptr));
        label_3->setText(QCoreApplication::translate("TableauDialog", "Adjust Competitions", nullptr));
        lineEdit->setText(QString());
        comboBox->setItemText(0, QString());
        comboBox->setItemText(1, QCoreApplication::translate("TableauDialog", "By date", nullptr));
        comboBox->setItemText(2, QCoreApplication::translate("TableauDialog", "By nb teams", nullptr));

        comboBox->setCurrentText(QString());
        comboBox->setPlaceholderText(QString());
        comboBox_2->setItemText(0, QCoreApplication::translate("TableauDialog", "All", nullptr));
        comboBox_2->setItemText(1, QCoreApplication::translate("TableauDialog", "League", nullptr));
        comboBox_2->setItemText(2, QCoreApplication::translate("TableauDialog", "Tournament", nullptr));

        pushButton_2->setText(QString());
        pushButton->setText(QString());
        pushButton_5->setText(QString());
        decemberButton->setText(QCoreApplication::translate("TableauDialog", "Dec", nullptr));
        mayButton->setText(QCoreApplication::translate("TableauDialog", "May", nullptr));
        septemberButton->setText(QCoreApplication::translate("TableauDialog", "Sep", nullptr));
        januaryButton->setText(QCoreApplication::translate("TableauDialog", "Jan", nullptr));
        aprilButton->setText(QCoreApplication::translate("TableauDialog", "Apr", nullptr));
        juneButton->setText(QCoreApplication::translate("TableauDialog", "Jun", nullptr));
        augustButton->setText(QCoreApplication::translate("TableauDialog", "Aug", nullptr));
        novemberButton->setText(QCoreApplication::translate("TableauDialog", "Nov", nullptr));
        marchButton->setText(QCoreApplication::translate("TableauDialog", "Mar", nullptr));
        octoberButton->setText(QCoreApplication::translate("TableauDialog", "Oct", nullptr));
        februaryButton->setText(QCoreApplication::translate("TableauDialog", "Feb", nullptr));
        julyButton->setText(QCoreApplication::translate("TableauDialog", "Jul", nullptr));
        yearComboBox->setItemText(0, QCoreApplication::translate("TableauDialog", "2000", nullptr));
        yearComboBox->setItemText(1, QCoreApplication::translate("TableauDialog", "2025", nullptr));
        yearComboBox->setItemText(2, QCoreApplication::translate("TableauDialog", "2500", nullptr));

        label->setText(QString());
        comp_name->setText(QString());
        team_name->setText(QString());
        label_15->setText(QCoreApplication::translate("TableauDialog", "winner", nullptr));
        label_16->setText(QCoreApplication::translate("TableauDialog", "Prediciton", nullptr));
        team_logo->setText(QString());
        label_4->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class TableauDialog: public Ui_TableauDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TABLEAU1_H
