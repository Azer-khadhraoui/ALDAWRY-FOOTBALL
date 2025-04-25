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
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateTimeEdit>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableView>
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
    QLabel *label_10;
    QLabel *label_7;
    QDateTimeEdit *Date;
    QLabel *label_11;
    QComboBox *team1;
    QLabel *label_8;
    QLabel *label_12;
    QLineEdit *Referee_name;
    QLabel *label_9;
    QComboBox *Comp;
    QPushButton *Confirm;
    QComboBox *team2;
    QLineEdit *Stadium;
    QWidget *tab_4;
    QTableView *allmatches;
    QFrame *frame_5;
    QLineEdit *lineEdit_9;
    QLabel *label_13;
    QFrame *frame_6;
    QLabel *label_19;
    QPushButton *Delete;
    QPushButton *Modify;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1200, 800);
        QFont font;
        font.setPointSize(10);
        MainWindow->setFont(font);
        MainWindow->setStyleSheet(QString::fromUtf8("background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 #1b1f2a, stop:1 #10131a);"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        menu = new QListWidget(centralwidget);
        menu->setObjectName("menu");
        menu->setGeometry(QRect(20, 20, 1151, 71));
        menu->setStyleSheet(QString::fromUtf8("background: #192231;\n"
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
        label->setPixmap(QPixmap(QString::fromUtf8(":/logo football.png")));
        label->setScaledContents(true);
        dashboard_2 = new QLabel(centralwidget);
        dashboard_2->setObjectName("dashboard_2");
        dashboard_2->setGeometry(QRect(210, 40, 71, 31));
        QFont font1;
        font1.setFamilies({QString::fromUtf8("Franklin Gothic Book")});
        font1.setPointSize(12);
        font1.setWeight(QFont::Thin);
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
"color: rgb(255, 255, 255);"));
        dashboard_4 = new QLabel(centralwidget);
        dashboard_4->setObjectName("dashboard_4");
        dashboard_4->setGeometry(QRect(960, 40, 61, 31));
        dashboard_4->setFont(font1);
        dashboard_4->setStyleSheet(QString::fromUtf8("background-color: transparent;\n"
"color: rgb(158, 158, 158);"));
        label_17 = new QLabel(centralwidget);
        label_17->setObjectName("label_17");
        label_17->setGeometry(QRect(1110, 40, 30, 30));
        label_17->setStyleSheet(QString::fromUtf8("background-color:transparent;"));
        label_17->setPixmap(QPixmap(QString::fromUtf8(":/user.png")));
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
        tabWidget->setGeometry(QRect(110, 130, 971, 621));
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
        tab = new QWidget();
        tab->setObjectName("tab");
        widget = new QWidget(tab);
        widget->setObjectName("widget");
        widget->setGeometry(QRect(90, 20, 761, 541));
        widget->setStyleSheet(QString::fromUtf8("background-color: #0F111A;\n"
"color: #FFFFFF;\n"
"font-family: 'Segoe UI', Arial, sans-serif;\n"
"font-size: 12px;\n"
"border-radius: 15px;\n"
"padding: 15px;\n"
"spacing: 2px;"));
        gridLayout_3 = new QGridLayout(widget);
        gridLayout_3->setObjectName("gridLayout_3");
        label_10 = new QLabel(widget);
        label_10->setObjectName("label_10");
        label_10->setStyleSheet(QString::fromUtf8("color: #A0A8B7;\n"
"font-weight: bold;\n"
"padding-bottom: 5px;background-color:transparent;"));

        gridLayout_3->addWidget(label_10, 10, 0, 1, 1);

        label_7 = new QLabel(widget);
        label_7->setObjectName("label_7");
        label_7->setStyleSheet(QString::fromUtf8("color: #A0A8B7;\n"
"font-weight: bold;\n"
"padding-bottom: 5px;background-color:transparent;"));

        gridLayout_3->addWidget(label_7, 0, 0, 1, 1);

        Date = new QDateTimeEdit(widget);
        Date->setObjectName("Date");
        Date->setStyleSheet(QString::fromUtf8("background-color: #1C1F2A;\n"
"border: 1px solid #2A2D3A;\n"
"border-radius: 5px;\n"
"padding: 5px;\n"
"color: white;\n"
"margin-left: 15px;\n"
"margin-right:15px;"));

        gridLayout_3->addWidget(Date, 11, 0, 1, 1);

        label_11 = new QLabel(widget);
        label_11->setObjectName("label_11");
        label_11->setStyleSheet(QString::fromUtf8("color: #A0A8B7;\n"
"font-weight: bold;\n"
"padding-bottom: 5px;background-color:transparent;"));

        gridLayout_3->addWidget(label_11, 4, 0, 1, 1);

        team1 = new QComboBox(widget);
        team1->setObjectName("team1");
        team1->setStyleSheet(QString::fromUtf8("background-color: #1C1F2A;\n"
"border: 1px solid #2A2D3A;\n"
"border-radius: 5px;\n"
"padding: 5px;\n"
"color: white;\n"
"margin-left: 15px;\n"
"margin-right:15px;"));

        gridLayout_3->addWidget(team1, 1, 0, 1, 1);

        label_8 = new QLabel(widget);
        label_8->setObjectName("label_8");
        label_8->setStyleSheet(QString::fromUtf8("color: #A0A8B7;\n"
"font-weight: bold;\n"
"padding-bottom: 5px;background-color:transparent;"));

        gridLayout_3->addWidget(label_8, 2, 0, 1, 1);

        label_12 = new QLabel(widget);
        label_12->setObjectName("label_12");
        label_12->setStyleSheet(QString::fromUtf8("color: #A0A8B7;\n"
"font-weight: bold;\n"
"padding-bottom: 5px;\n"
"background-color:transparent;\n"
""));

        gridLayout_3->addWidget(label_12, 6, 0, 1, 1);

        Referee_name = new QLineEdit(widget);
        Referee_name->setObjectName("Referee_name");
        Referee_name->setStyleSheet(QString::fromUtf8("background-color: #1C1F2A;\n"
"border: 1px solid #2A2D3A;\n"
"border-radius: 5px;\n"
"padding: 5px;\n"
"color: white;\n"
"margin-left: 15px;\n"
"margin-right:15px;"));

        gridLayout_3->addWidget(Referee_name, 7, 0, 1, 1);

        label_9 = new QLabel(widget);
        label_9->setObjectName("label_9");
        label_9->setStyleSheet(QString::fromUtf8("color: #A0A8B7;\n"
"font-weight: bold;\n"
"padding-bottom: 5px;background-color:transparent;"));

        gridLayout_3->addWidget(label_9, 8, 0, 1, 1);

        Comp = new QComboBox(widget);
        Comp->setObjectName("Comp");
        Comp->setStyleSheet(QString::fromUtf8("background-color: #1C1F2A;\n"
"border: 1px solid #2A2D3A;\n"
"border-radius: 5px;\n"
"padding: 5px;\n"
"color: white;\n"
"margin-left: 15px;\n"
"margin-right:15px;"));

        gridLayout_3->addWidget(Comp, 9, 0, 1, 1);

        Confirm = new QPushButton(widget);
        Confirm->setObjectName("Confirm");
        Confirm->setEnabled(true);
        Confirm->setStyleSheet(QString::fromUtf8("background-color: rgba(50, 150, 250, 0.8);\n"
"color: white;\n"
"font-size: 12px;\n"
"border-radius: 5px;\n"
"padding: 6px 12px;\n"
"margin-left:500px;\n"
"margin-right:20px;\n"
"margin-bottom:10px;"));

        gridLayout_3->addWidget(Confirm, 13, 0, 1, 1);

        team2 = new QComboBox(widget);
        team2->setObjectName("team2");
        team2->setStyleSheet(QString::fromUtf8("background-color: #1C1F2A;\n"
"border: 1px solid #2A2D3A;\n"
"border-radius: 5px;\n"
"padding: 5px;\n"
"color: white;\n"
"margin-left: 15px;\n"
"margin-right:15px;"));

        gridLayout_3->addWidget(team2, 3, 0, 1, 1);

        Stadium = new QLineEdit(widget);
        Stadium->setObjectName("Stadium");
        Stadium->setStyleSheet(QString::fromUtf8("background-color: #1C1F2A;\n"
"border: 1px solid #2A2D3A;\n"
"border-radius: 5px;\n"
"padding: 5px;\n"
"color: white;\n"
"margin-left: 15px;\n"
"margin-right:15px;"));

        gridLayout_3->addWidget(Stadium, 5, 0, 1, 1);

        tabWidget->addTab(tab, QString());
        tab_4 = new QWidget();
        tab_4->setObjectName("tab_4");
        allmatches = new QTableView(tab_4);
        allmatches->setObjectName("allmatches");
        allmatches->setGeometry(QRect(100, 100, 741, 381));
        frame_5 = new QFrame(tab_4);
        frame_5->setObjectName("frame_5");
        frame_5->setGeometry(QRect(500, 40, 341, 51));
        frame_5->setStyleSheet(QString::fromUtf8("    background-color: #1E1E2D;  /* Dark matte background */\n"
"\n"
"\n"
" \n"
"\n"
""));
        frame_5->setFrameShape(QFrame::Shape::StyledPanel);
        frame_5->setFrameShadow(QFrame::Shadow::Raised);
        lineEdit_9 = new QLineEdit(frame_5);
        lineEdit_9->setObjectName("lineEdit_9");
        lineEdit_9->setGeometry(QRect(70, 10, 211, 31));
        lineEdit_9->setStyleSheet(QString::fromUtf8("    background-color: #141821;  /* Slightly lighter for contrast */\n"
"    border: 2px solid #cccccc;  /* Keep borders subtle */\n"
"    border-radius: 6px;\n"
"    padding: 6px 10px;\n"
"    font-size: 14px;\n"
"    color: white;"));
        label_13 = new QLabel(frame_5);
        label_13->setObjectName("label_13");
        label_13->setGeometry(QRect(300, 20, 18, 18));
        label_13->setPixmap(QPixmap(QString::fromUtf8(":/trier.png")));
        label_13->setScaledContents(true);
        frame_6 = new QFrame(frame_5);
        frame_6->setObjectName("frame_6");
        frame_6->setGeometry(QRect(20, 10, 31, 31));
        frame_6->setFrameShape(QFrame::Shape::StyledPanel);
        frame_6->setFrameShadow(QFrame::Shadow::Raised);
        label_19 = new QLabel(frame_6);
        label_19->setObjectName("label_19");
        label_19->setGeometry(QRect(10, 10, 11, 11));
        label_19->setPixmap(QPixmap(QString::fromUtf8(":/search.png")));
        label_19->setScaledContents(true);
        Delete = new QPushButton(tab_4);
        Delete->setObjectName("Delete");
        Delete->setGeometry(QRect(760, 500, 83, 29));
        Delete->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 0, 0);\n"
"border-radius: 5px ;"));
        Modify = new QPushButton(tab_4);
        Modify->setObjectName("Modify");
        Modify->setGeometry(QRect(660, 500, 83, 29));
        Modify->setStyleSheet(QString::fromUtf8("background-color: #192231;\n"
"border-radius: 5px ;"));
        tabWidget->addTab(tab_4, QString());
        MainWindow->setCentralWidget(centralwidget);
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
        label->setText(QString());
        dashboard_2->setText(QCoreApplication::translate("MainWindow", "Player", nullptr));
        dashboard_7->setText(QCoreApplication::translate("MainWindow", "Competition", nullptr));
        dashboard_3->setText(QCoreApplication::translate("MainWindow", "Match", nullptr));
        dashboard_4->setText(QCoreApplication::translate("MainWindow", "Team", nullptr));
        label_17->setText(QString());
        label_10->setText(QCoreApplication::translate("MainWindow", "Date", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "Team_1", nullptr));
        label_11->setText(QCoreApplication::translate("MainWindow", "Stadium", nullptr));
        label_8->setText(QCoreApplication::translate("MainWindow", "Team_2", nullptr));
        label_12->setText(QCoreApplication::translate("MainWindow", "Referee's FullName", nullptr));
        label_9->setText(QCoreApplication::translate("MainWindow", "Competiton", nullptr));
        Confirm->setText(QCoreApplication::translate("MainWindow", "Confirm", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QCoreApplication::translate("MainWindow", "Add Match", nullptr));
        label_13->setText(QString());
        label_19->setText(QString());
        Delete->setText(QCoreApplication::translate("MainWindow", "Delete", nullptr));
        Modify->setText(QCoreApplication::translate("MainWindow", "Modify", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_4), QCoreApplication::translate("MainWindow", "Display Match", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
