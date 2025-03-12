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
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
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
    QTabWidget *tabWidget;
    QWidget *tab;
    QWidget *widget;
    QGridLayout *gridLayout_3;
    QPushButton *button1;
    QComboBox *cb;
    QLabel *label_10;
    QLineEdit *l1;
    QLabel *label_9;
    QLabel *label_11;
    QLabel *label_7;
    QLabel *label_8;
    QLineEdit *l2;
    QWidget *widget1;
    QHBoxLayout *horizontalLayout;
    QToolButton *toolButton;
    QLabel *label_2;
    QLineEdit *l2_2;
    QLabel *label_4;
    QLabel *label_19;
    QLabel *label_27;
    QLabel *label_28;
    QLabel *label_29;
    QLabel *label_30;
    QPushButton *resetButton;
    QWidget *tab_2;
    QTableWidget *tableWidget;
    QFrame *frame_5;
    QLineEdit *searchBar;
    QFrame *frame_7;
    QLabel *label_21;
    QPushButton *deleteButton;
    QPushButton *modifyButton;
    QPushButton *downloadButton;
    QWidget *tab_5;
    QLabel *label_5;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1200, 800);
        QFont font;
        font.setPointSize(10);
        MainWindow->setFont(font);
        MainWindow->setStyleSheet(QString::fromUtf8("background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 #212A3C, stop:1 #121824);"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        menu = new QListWidget(centralwidget);
        menu->setObjectName("menu");
        menu->setGeometry(QRect(20, 20, 1151, 71));
        menu->setStyleSheet(QString::fromUtf8("background-color: rgb(13, 29, 53);\n"
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
        label->setPixmap(QPixmap(QString::fromUtf8(":/img/logo football.png")));
        label->setScaledContents(true);
        dashboard_2 = new QLabel(centralwidget);
        dashboard_2->setObjectName("dashboard_2");
        dashboard_2->setGeometry(QRect(210, 40, 71, 31));
        QFont font1;
        font1.setFamilies({QString::fromUtf8("Franklin Gothic Book")});
        font1.setPointSize(12);
        dashboard_2->setFont(font1);
        dashboard_2->setStyleSheet(QString::fromUtf8("background-color: transparent;\n"
"color: rgb(158, 158, 158);"));
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
        QFont font2;
        font2.setFamilies({QString::fromUtf8("Franklin Gothic Book")});
        font2.setPointSize(12);
        font2.setBold(true);
        dashboard_4->setFont(font2);
        dashboard_4->setStyleSheet(QString::fromUtf8("background-color: transparent;\n"
"color: white;"));
        label_17 = new QLabel(centralwidget);
        label_17->setObjectName("label_17");
        label_17->setGeometry(QRect(1120, 50, 21, 21));
        label_17->setStyleSheet(QString::fromUtf8("background-color:transparent;"));
        label_17->setPixmap(QPixmap(QString::fromUtf8(":/img/Userr.png")));
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
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName("tabWidget");
        tabWidget->setGeometry(QRect(110, 120, 971, 621));
        tabWidget->setLayoutDirection(Qt::LayoutDirection::LeftToRight);
        tabWidget->setStyleSheet(QString::fromUtf8("/* Style for the QTabWidget pane (content area) */\n"
"QTabWidget#tabWidget::pane {\n"
"    background-color: #1E2633; /* Match the form widget background */\n"
"    border: 2px solid #2A3A4A; /* Subtle blue-gray border */\n"
"    border-radius: 5px;\n"
"}\n"
"\n"
"/* Style for the tab bar (tabs) */\n"
"QTabBar::tab {\n"
"    background-color: #252A38; /* Slightly lighter than the pane */\n"
"    color: #B0C0D0; /* Light grayish-blue for inactive tab text */\n"
"    padding: 10px 20px; /* Increased padding for better spacing */\n"
"    border: 1px solid #2A3A4A; /* Subtle border */\n"
"    border-top-left-radius: 5px;\n"
"    border-top-right-radius: 5px;\n"
"    margin-right: 2px; /* Space between tabs */\n"
"    font-size: 12px;\n"
"    font-weight: 500;\n"
"}\n"
"\n"
"/* Style for the selected tab */\n"
"QTabBar::tab:selected {\n"
"    background-color: #2E3440; /* Darker shade for the active tab */\n"
"    color: #E0E6ED; /* Brighter text for the active tab */\n"
"    font-weight: bold;\n"
"    border-bott"
                        "om: 2px solid #00FF7F; /* Green underline to match the accent */\n"
"}\n"
"\n"
"/* Style for tab on hover */\n"
"QTabBar::tab:hover {\n"
"    background-color: #353F4D; /* Lighter blue-gray on hover */\n"
"    color: #E0E6ED;\n"
"}\n"
"\n"
"/* Style for non-selected tabs */\n"
"QTabBar::tab:!selected {\n"
"    margin-top: 2px; /* Slightly lower non-selected tabs */\n"
"    color: #A0A8B7; /* Dimmer text for non-selected tabs */\n"
"}\n"
"\n"
"/* Style for the tab bar's corner button (if any) */\n"
"QTabWidget#tabWidget QTableCornerButton::section {\n"
"    background-color: #252A38;\n"
"    border: 1px solid #2A3A4A;\n"
"}"));
        tab = new QWidget();
        tab->setObjectName("tab");
        widget = new QWidget(tab);
        widget->setObjectName("widget");
        widget->setGeometry(QRect(220, 60, 541, 491));
        widget->setStyleSheet(QString::fromUtf8("background-color: rgb(25, 31, 42);\n"
"    color: #FFFFFF;\n"
"    font-family: 'Segoe UI', Arial, sans-serif;\n"
"    font-size: 12px;\n"
"    border-radius: 15px;\n"
"    padding: 15px;\n"
"    spacing: 2px;\n"
""));
        gridLayout_3 = new QGridLayout(widget);
        gridLayout_3->setObjectName("gridLayout_3");
        button1 = new QPushButton(widget);
        button1->setObjectName("button1");
        button1->setStyleSheet(QString::fromUtf8("background-color: #00FF7F; /* Green to match the accent */\n"
"    color: #1A2633; /* Dark blue text for contrast */\n"
"    font-size: 12px;\n"
"    font-weight: bold;\n"
"    border-radius: 5px;\n"
"    padding: 6px 12px;\n"
"    margin-left: 350px;\n"
"    margin-right: 20px;\n"
"    margin-bottom: 5px;"));

        gridLayout_3->addWidget(button1, 10, 0, 1, 1);

        cb = new QComboBox(widget);
        cb->addItem(QString());
        cb->addItem(QString());
        cb->addItem(QString());
        cb->addItem(QString());
        cb->addItem(QString());
        cb->setObjectName("cb");
        cb->setStyleSheet(QString::fromUtf8("background-color: #2A3240;\n"
"  border: 1px solid #3A4A5A;\n"
"    border-radius: 5px;\n"
"    padding: 5px;\n"
"    color: #E0E6ED;\n"
"    margin-left: 15px;\n"
"    margin-right: 15px;\n"
"\n"
"Qcb::drop-down {\n"
"    border-left: 1px solid #3A4A5A;\n"
"    width: 20px;\n"
"}\n"
"Qcb:focus {\n"
"    border: 1px solid #00FF7F;\n"
"    background-color: #323A48;\n"
"}"));

        gridLayout_3->addWidget(cb, 3, 0, 1, 1);

        label_10 = new QLabel(widget);
        label_10->setObjectName("label_10");
        label_10->setStyleSheet(QString::fromUtf8("color: #A0A8B7;\n"
"font-weight: bold;\n"
"padding-bottom: 5px;background-color:transparent;"));

        gridLayout_3->addWidget(label_10, 6, 0, 1, 1);

        l1 = new QLineEdit(widget);
        l1->setObjectName("l1");
        l1->setStyleSheet(QString::fromUtf8("background-color: #2A3240; /* Darker blue-gray for input fields */\n"
"    border: 1px solid #3A4A5A; /* Subtle blue-gray border */\n"
"    border-radius: 5px;\n"
"    padding: 5px;\n"
"    color: #E0E6ED; /* Light gray text for readability */\n"
"    margin-left: 15px;\n"
"    margin-right: 15px;\n"
""));

        gridLayout_3->addWidget(l1, 1, 0, 1, 1);

        label_9 = new QLabel(widget);
        label_9->setObjectName("label_9");
        label_9->setStyleSheet(QString::fromUtf8("color: #A0A8B7;\n"
"font-weight: bold;\n"
"padding-bottom: 5px;background-color:transparent;"));

        gridLayout_3->addWidget(label_9, 4, 0, 1, 1);

        label_11 = new QLabel(widget);
        label_11->setObjectName("label_11");
        label_11->setStyleSheet(QString::fromUtf8("color: #A0A8B7;\n"
"font-weight: bold;\n"
"padding-bottom: 5px;background-color:transparent;"));

        gridLayout_3->addWidget(label_11, 8, 0, 1, 1);

        label_7 = new QLabel(widget);
        label_7->setObjectName("label_7");
        label_7->setStyleSheet(QString::fromUtf8("color: #A0A8B7;\n"
"font-weight: bold;\n"
"padding-bottom: 5px;background-color:transparent;"));

        gridLayout_3->addWidget(label_7, 0, 0, 1, 1);

        label_8 = new QLabel(widget);
        label_8->setObjectName("label_8");
        label_8->setStyleSheet(QString::fromUtf8("color: #A0A8B7;\n"
"font-weight: bold;\n"
"padding-bottom: 5px;background-color:transparent;"));

        gridLayout_3->addWidget(label_8, 2, 0, 1, 1);

        l2 = new QLineEdit(widget);
        l2->setObjectName("l2");
        l2->setStyleSheet(QString::fromUtf8("background-color: #2A3240; /* Darker blue-gray for input fields */\n"
"    border: 1px solid #3A4A5A; /* Subtle blue-gray border */\n"
"    border-radius: 5px;\n"
"    padding: 5px;\n"
"    color: #E0E6ED; /* Light gray text for readability */\n"
"    margin-left: 15px;\n"
"    margin-right: 15px;"));

        gridLayout_3->addWidget(l2, 5, 0, 1, 1);

        widget1 = new QWidget(widget);
        widget1->setObjectName("widget1");
        widget1->setStyleSheet(QString::fromUtf8("background-color: #2A3240;\n"
"    border: 1px solid #3A4A5A;\n"
"    border-radius: 5px;\n"
"    padding: 3px;\n"
"    color: #E0E6ED;\n"
"    margin-left: 15px;\n"
"    margin-right: 15px;\n"
"    margin-bottom: 15px;"));
        horizontalLayout = new QHBoxLayout(widget1);
        horizontalLayout->setObjectName("horizontalLayout");
        toolButton = new QToolButton(widget1);
        toolButton->setObjectName("toolButton");
        toolButton->setStyleSheet(QString::fromUtf8("background-color: #1C1F2A;\n"
"border: 1px solid #2A2D3A;\n"
"border-radius: 5px;\n"
"padding: 3px;\n"
"color: white;\n"
"margin-left: 15px;\n"
"margin-right:15px;\n"
"margin-bottom:15px;"));

        horizontalLayout->addWidget(toolButton);

        label_2 = new QLabel(widget1);
        label_2->setObjectName("label_2");
        label_2->setStyleSheet(QString::fromUtf8("color: #A0A8B7;\n"
"padding-left: 10px;\n"
"background-color: transparent;"));

        horizontalLayout->addWidget(label_2);


        gridLayout_3->addWidget(widget1, 7, 0, 1, 1);

        l2_2 = new QLineEdit(widget);
        l2_2->setObjectName("l2_2");
        l2_2->setStyleSheet(QString::fromUtf8("background-color: #2A3240; /* Darker blue-gray for input fields */\n"
"    border: 1px solid #3A4A5A; /* Subtle blue-gray border */\n"
"    border-radius: 5px;\n"
"    padding: 5px;\n"
"    color: #E0E6ED; /* Light gray text for readability */\n"
"    margin-left: 15px;\n"
"    margin-right: 15px;"));

        gridLayout_3->addWidget(l2_2, 9, 0, 1, 1);

        label_4 = new QLabel(tab);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(310, 25, 361, 21));
        QFont font3;
        font3.setFamilies({QString::fromUtf8("PT Dusky")});
        font3.setPointSize(12);
        font3.setBold(true);
        label_4->setFont(font3);
        label_4->setStyleSheet(QString::fromUtf8("background-color: transparent\n"
";"));
        label_19 = new QLabel(tab);
        label_19->setObjectName("label_19");
        label_19->setGeometry(QRect(250, 170, 17, 17));
        label_19->setStyleSheet(QString::fromUtf8("background-color:transparent;"));
        label_19->setPixmap(QPixmap(QString::fromUtf8(":/img/terrain.png")));
        label_19->setScaledContents(true);
        label_27 = new QLabel(tab);
        label_27->setObjectName("label_27");
        label_27->setGeometry(QRect(250, 250, 12, 18));
        label_27->setStyleSheet(QString::fromUtf8("background-color:transparent;"));
        label_27->setPixmap(QPixmap(QString::fromUtf8(":/img/money.png")));
        label_27->setScaledContents(true);
        label_28 = new QLabel(tab);
        label_28->setObjectName("label_28");
        label_28->setGeometry(QRect(250, 90, 17, 17));
        label_28->setStyleSheet(QString::fromUtf8("color: #B0C0D0;background-color:transparent;"));
        label_28->setPixmap(QPixmap(QString::fromUtf8(":/img/Userr.png")));
        label_28->setScaledContents(true);
        label_29 = new QLabel(tab);
        label_29->setObjectName("label_29");
        label_29->setGeometry(QRect(250, 326, 21, 21));
        label_29->setStyleSheet(QString::fromUtf8("background-color:transparent;"));
        label_29->setPixmap(QPixmap(QString::fromUtf8(":/img/logo.png")));
        label_29->setScaledContents(true);
        label_30 = new QLabel(tab);
        label_30->setObjectName("label_30");
        label_30->setGeometry(QRect(250, 450, 18, 16));
        label_30->setStyleSheet(QString::fromUtf8("background-color:transparent;"));
        label_30->setPixmap(QPixmap(QString::fromUtf8(":/img/abv.png")));
        label_30->setScaledContents(true);
        resetButton = new QPushButton(tab);
        resetButton->setObjectName("resetButton");
        resetButton->setGeometry(QRect(780, 510, 31, 24));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/img/reset.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        resetButton->setIcon(icon);
        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName("tab_2");
        tableWidget = new QTableWidget(tab_2);
        tableWidget->setObjectName("tableWidget");
        tableWidget->setGeometry(QRect(230, 110, 521, 371));
        tableWidget->setStyleSheet(QString::fromUtf8("/* Style for the QTableWidget */\n"
"QTableWidget#tableWidget {\n"
"    background-color: #1E2633; /* Match tab pane and form widget */\n"
"    border: 2px solid #2A3A4A; /* Subtle blue-gray border */\n"
"    gridline-color: #3A4A5A; /* Light grid lines */\n"
"    alternate-background-color: #252A38; /* Alternating row color */\n"
"    color: #E0E6ED; /* Light gray text */\n"
"    selection-background-color: #00FF7F; /* Green selection */\n"
"    selection-color: #1A2633; /* Dark blue text on selection */\n"
"    border-radius: 5px;\n"
"}\n"
"QTableWidget#tableWidget::item {\n"
"    padding: 5px;\n"
"    border: none; /* Remove individual cell borders */\n"
"}\n"
"QTableWidget#tableWidget::item:focus {\n"
"    outline: none; /* Remove focus outline */\n"
"}\n"
"\n"
"/* Style for the table header */\n"
"QHeaderView::section {\n"
"    background-color: #252A38; /* Match alternating row color */\n"
"    color: #E0E6ED;\n"
"    border: 1px solid #2A3A4A;\n"
"    padding: 4px;\n"
"    font-weight: bold;\n"
"    bor"
                        "der-radius: 0;\n"
"}\n"
"QTableWidget#tableWidget QTableCornerButton::section {\n"
"    background-color: #252A38;\n"
"    border: 1px solid #2A3A4A;\n"
"}"));
        frame_5 = new QFrame(tab_2);
        frame_5->setObjectName("frame_5");
        frame_5->setGeometry(QRect(410, 40, 341, 51));
        frame_5->setStyleSheet(QString::fromUtf8("background-color: rgb(21, 26, 35);\n"
"border-radius:15px ;\n"
"border: 1px solid #2A2D3A;\n"
"\n"
" \n"
"\n"
""));
        frame_5->setFrameShape(QFrame::Shape::StyledPanel);
        frame_5->setFrameShadow(QFrame::Shadow::Raised);
        searchBar = new QLineEdit(frame_5);
        searchBar->setObjectName("searchBar");
        searchBar->setGeometry(QRect(70, 10, 251, 32));
        searchBar->setStyleSheet(QString::fromUtf8("    background-color: #141821;  /* Slightly lighter for contrast */\n"
"    border: 2px solid #cccccc;  /* Keep borders subtle */\n"
"    border-radius: 6px;\n"
"    padding: 6px 10px;\n"
"    font-size: 14px;\n"
"    color: white;"));
        frame_7 = new QFrame(frame_5);
        frame_7->setObjectName("frame_7");
        frame_7->setGeometry(QRect(20, 10, 31, 31));
        frame_7->setFrameShape(QFrame::Shape::StyledPanel);
        frame_7->setFrameShadow(QFrame::Shadow::Raised);
        label_21 = new QLabel(frame_7);
        label_21->setObjectName("label_21");
        label_21->setGeometry(QRect(10, 10, 11, 11));
        label_21->setPixmap(QPixmap(QString::fromUtf8(":/img/search.png")));
        label_21->setScaledContents(true);
        deleteButton = new QPushButton(tab_2);
        deleteButton->setObjectName("deleteButton");
        deleteButton->setGeometry(QRect(651, 500, 101, 24));
        deleteButton->setStyleSheet(QString::fromUtf8("/* Style for the Delete button */\n"
"QPushButton#deleteButton {\n"
"    background-color: #4A1A1A; /* Muted dark red */\n"
"    color: #E0E6ED; /* Light gray text */\n"
"    font-size: 12px;\n"
"    font-weight: bold;\n"
"    border-radius: 5px;\n"
"    padding: 6px 12px;\n"
"}\n"
"QPushButton#deleteButton:hover {\n"
"    background-color: #5A2A2A; /* Lighter red on hover */\n"
"}\n"
"QPushButton#deleteButton:pressed {\n"
"    background-color: #6A3A3A; /* Darker red when pressed */\n"
"}"));
        modifyButton = new QPushButton(tab_2);
        modifyButton->setObjectName("modifyButton");
        modifyButton->setGeometry(QRect(540, 500, 101, 24));
        modifyButton->setStyleSheet(QString::fromUtf8("/* Style for the Modify button */\n"
"QPushButton#modifyButton {\n"
"    background-color: #00FF7F; /* Green to match the accent */\n"
"    color: #1A2633; /* Dark blue text */\n"
"    font-size: 12px;\n"
"    font-weight: bold;\n"
"    border-radius: 5px;\n"
"    padding: 6px 12px;\n"
"    margin-right: 10px;\n"
"}\n"
"QPushButton#modifyButton:hover {\n"
"    background-color: #00CC66; /* Darker green on hover */\n"
"}\n"
"QPushButton#modifyButton:pressed {\n"
"    background-color: #00994D; /* Even darker green when pressed */\n"
"}"));
        downloadButton = new QPushButton(tab_2);
        downloadButton->setObjectName("downloadButton");
        downloadButton->setGeometry(QRect(230, 500, 151, 24));
        downloadButton->setStyleSheet(QString::fromUtf8("/* Style for the Modify button */\n"
"QPushButton#downloadButton {\n"
"	background-color: rgb(120, 120, 120);\n"
"    color: #1A2633; /* Dark blue text */\n"
"    font-size: 12px;\n"
"    font-weight: bold;\n"
"    border-radius: 5px;\n"
"    padding: 6px 12px;\n"
"    margin-right: 10px;\n"
"}\n"
"QPushButton#downloadButton:hover {\n"
"    background-color: #00CC66; /* Darker green on hover */\n"
"}\n"
"QPushButton#downloadButton:pressed {\n"
"    background-color: #00994D; /* Even darker green when pressed */\n"
"}"));
        tabWidget->addTab(tab_2, QString());
        tab_5 = new QWidget();
        tab_5->setObjectName("tab_5");
        tabWidget->addTab(tab_5, QString());
        label_5 = new QLabel(centralwidget);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(0, 0, 1200, 800));
        label_5->setPixmap(QPixmap(QString::fromUtf8(":/img/BACK.png")));
        label_5->setScaledContents(true);
        MainWindow->setCentralWidget(centralwidget);
        label_5->raise();
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
        tabWidget->raise();
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(1);


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
        button1->setText(QCoreApplication::translate("MainWindow", "Confirm", nullptr));
        cb->setItemText(0, QCoreApplication::translate("MainWindow", "bernabeu", nullptr));
        cb->setItemText(1, QCoreApplication::translate("MainWindow", "Santiago Bernab\303\251u", nullptr));
        cb->setItemText(2, QCoreApplication::translate("MainWindow", "Camp Nou", nullptr));
        cb->setItemText(3, QCoreApplication::translate("MainWindow", "Old Trafford", nullptr));
        cb->setItemText(4, QCoreApplication::translate("MainWindow", "Wembley Stadium", nullptr));

        label_10->setText(QCoreApplication::translate("MainWindow", "         Team_Logo :", nullptr));
        l1->setText(QString());
        label_9->setText(QCoreApplication::translate("MainWindow", "         Budget :", nullptr));
        label_11->setText(QCoreApplication::translate("MainWindow", "        Team_ABV :", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "          Team_Name :", nullptr));
        label_8->setText(QCoreApplication::translate("MainWindow", "         Home_Stadium :", nullptr));
        toolButton->setText(QCoreApplication::translate("MainWindow", "...", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "insert logo here", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "FILL IN THIS FORM TO ADD A TEAM", nullptr));
        label_19->setText(QString());
        label_27->setText(QString());
        label_28->setText(QString());
        label_29->setText(QString());
        label_30->setText(QString());
        resetButton->setText(QString());
        tabWidget->setTabText(tabWidget->indexOf(tab), QCoreApplication::translate("MainWindow", "     Add Team     ", nullptr));
        label_21->setText(QString());
        deleteButton->setText(QCoreApplication::translate("MainWindow", "Delete", nullptr));
        modifyButton->setText(QCoreApplication::translate("MainWindow", "Modify", nullptr));
        downloadButton->setText(QCoreApplication::translate("MainWindow", "Download PDF", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QCoreApplication::translate("MainWindow", "     Display Team    ", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_5), QCoreApplication::translate("MainWindow", "   To-Do-List   ", nullptr));
        label_5->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
