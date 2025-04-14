/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.8.2
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
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QListWidget *menu;
    QListWidget *menu_2;
    QFrame *line;
    QFrame *line_2;
    QFrame *line_3;
    QLabel *dashboard_2;
    QLabel *dashboard_7;
    QLabel *dashboard_3;
    QLabel *dashboard_4;
    QLabel *label_4;
    QFrame *frame;
    QLabel *label_2;
    QLineEdit *lineEdit;
    QComboBox *comboBox;
    QComboBox *comboBox_2;
    QWidget *monthCalendarWidget;
    QVBoxLayout *monthCalendarLayout;
    QComboBox *yearComboBox;
    QGridLayout *monthGridLayout;
    QPushButton *januaryButton;
    QPushButton *februaryButton;
    QPushButton *marchButton;
    QPushButton *aprilButton;
    QPushButton *mayButton;
    QPushButton *juneButton;
    QPushButton *julyButton;
    QPushButton *augustButton;
    QPushButton *septemberButton;
    QPushButton *octoberButton;
    QPushButton *novemberButton;
    QPushButton *decemberButton;
    QListWidget *listWidget_2;
    QLabel *label_5;
    QPushButton *pushButton_3;
    QTableView *test;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QPushButton *pushButton_4;
    QLabel *comp_name;
    QLabel *team_name;
    QPushButton *pushButton_5;
    QLabel *label;
    QLabel *label_3;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1200, 800);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        centralwidget->setStyleSheet(QString::fromUtf8("background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 #1a3c34, stop:1 #0d1f2d);"));
        menu = new QListWidget(centralwidget);
        menu->setObjectName("menu");
        menu->setGeometry(QRect(20, 30, 1151, 71));
        menu->setStyleSheet(QString::fromUtf8("background: #1e4d4a;\n"
"color: #e0f7fa;\n"
"border-bottom: 2px solid #4dd0e1;\n"
"border-radius: 30px;"));
        menu_2 = new QListWidget(centralwidget);
        menu_2->setObjectName("menu_2");
        menu_2->setGeometry(QRect(20, 30, 111, 71));
        menu_2->setStyleSheet(QString::fromUtf8("background: #0a2f2d;\n"
"color: #ffffff;\n"
"border-bottom: 3px solid #00e676;\n"
"border-radius: 30px;"));
        line = new QFrame(centralwidget);
        line->setObjectName("line");
        line->setGeometry(QRect(360, 30, 3, 61));
        line->setStyleSheet(QString::fromUtf8("border: 2px solid #4dd0e1;"));
        line->setFrameShape(QFrame::Shape::VLine);
        line->setFrameShadow(QFrame::Shadow::Sunken);
        line_2 = new QFrame(centralwidget);
        line_2->setObjectName("line_2");
        line_2->setGeometry(QRect(640, 30, 3, 61));
        line_2->setStyleSheet(QString::fromUtf8("border: 2px solid #4dd0e1;"));
        line_2->setFrameShape(QFrame::Shape::VLine);
        line_2->setFrameShadow(QFrame::Shadow::Sunken);
        line_3 = new QFrame(centralwidget);
        line_3->setObjectName("line_3");
        line_3->setGeometry(QRect(880, 30, 3, 61));
        line_3->setStyleSheet(QString::fromUtf8("border: 2px solid #4dd0e1;"));
        line_3->setFrameShape(QFrame::Shape::VLine);
        line_3->setFrameShadow(QFrame::Shadow::Sunken);
        dashboard_2 = new QLabel(centralwidget);
        dashboard_2->setObjectName("dashboard_2");
        dashboard_2->setGeometry(QRect(210, 50, 71, 31));
        QFont font;
        font.setFamilies({QString::fromUtf8("Franklin Gothic Book")});
        font.setPointSize(15);
        dashboard_2->setFont(font);
        dashboard_2->setStyleSheet(QString::fromUtf8("background-color: transparent;\n"
"color: #b2ebf2;"));
        dashboard_7 = new QLabel(centralwidget);
        dashboard_7->setObjectName("dashboard_7");
        dashboard_7->setGeometry(QRect(460, 50, 131, 31));
        dashboard_7->setFont(font);
        dashboard_7->setStyleSheet(QString::fromUtf8("background-color: transparent;\n"
"color: #b2ebf2;"));
        dashboard_3 = new QLabel(centralwidget);
        dashboard_3->setObjectName("dashboard_3");
        dashboard_3->setGeometry(QRect(740, 50, 71, 31));
        dashboard_3->setFont(font);
        dashboard_3->setStyleSheet(QString::fromUtf8("background-color: transparent;\n"
"color: #b2ebf2;"));
        dashboard_4 = new QLabel(centralwidget);
        dashboard_4->setObjectName("dashboard_4");
        dashboard_4->setGeometry(QRect(960, 50, 61, 31));
        dashboard_4->setFont(font);
        dashboard_4->setStyleSheet(QString::fromUtf8("background-color: transparent;\n"
"color: #b2ebf2;"));
        label_4 = new QLabel(centralwidget);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(1120, 50, 40, 40));
        label_4->setStyleSheet(QString::fromUtf8("background-color: transparent;"));
        label_4->setPixmap(QPixmap(QString::fromUtf8("user.png")));
        label_4->setScaledContents(true);
        frame = new QFrame(centralwidget);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(40, 140, 591, 51));
        frame->setStyleSheet(QString::fromUtf8("background-color: #1e4d4a;\n"
"border: 1px solid #4dd0e1;\n"
"border-radius: 8px;"));
        frame->setFrameShape(QFrame::Shape::StyledPanel);
        frame->setFrameShadow(QFrame::Shadow::Raised);
        label_2 = new QLabel(frame);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(10, 10, 41, 30));
        label_2->setStyleSheet(QString::fromUtf8("background-color: #0a2f2d;\n"
"border: 1px solid #4dd0e1;\n"
"border-radius: 5px;\n"
"padding: 6px 12px;"));
        label_2->setPixmap(QPixmap(QString::fromUtf8(":/images/search.png")));
        label_2->setScaledContents(true);
        lineEdit = new QLineEdit(frame);
        lineEdit->setObjectName("lineEdit");
        lineEdit->setGeometry(QRect(60, 10, 341, 31));
        lineEdit->setStyleSheet(QString::fromUtf8("background-color: #0d1f2d;\n"
"border: 2px solid #4dd0e1;\n"
"border-radius: 6px;\n"
"padding: 6px 10px;\n"
"font-size: 14px;\n"
"color: #e0f7fa;"));
        comboBox = new QComboBox(frame);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName("comboBox");
        comboBox->setGeometry(QRect(410, 10, 82, 28));
        comboBox->setStyleSheet(QString::fromUtf8("background-color: #0d1f2d;\n"
"border: 1px solid #4dd0e1;\n"
"color: #e0f7fa;\n"
"border-radius: 4px;"));
        comboBox_2 = new QComboBox(frame);
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->setObjectName("comboBox_2");
        comboBox_2->setGeometry(QRect(500, 10, 82, 28));
        comboBox_2->setStyleSheet(QString::fromUtf8("background-color: #0d1f2d;\n"
"border: 1px solid #4dd0e1;\n"
"color: #e0f7fa;\n"
"border-radius: 4px;"));
        monthCalendarWidget = new QWidget(centralwidget);
        monthCalendarWidget->setObjectName("monthCalendarWidget");
        monthCalendarWidget->setGeometry(QRect(760, 160, 400, 261));
        monthCalendarWidget->setStyleSheet(QString::fromUtf8("background-color: #0d1f2d;\n"
"border-radius: 6px;\n"
"border: 1px solid #4dd0e1;"));
        monthCalendarLayout = new QVBoxLayout(monthCalendarWidget);
        monthCalendarLayout->setSpacing(10);
        monthCalendarLayout->setObjectName("monthCalendarLayout");
        monthCalendarLayout->setContentsMargins(0, 0, 0, 0);
        yearComboBox = new QComboBox(monthCalendarWidget);
        yearComboBox->addItem(QString());
        yearComboBox->addItem(QString());
        yearComboBox->addItem(QString());
        yearComboBox->setObjectName("yearComboBox");
        yearComboBox->setStyleSheet(QString::fromUtf8("background-color: #0d1f2d;\n"
"border: 1px solid #4dd0e1;\n"
"color: #e0f7fa;\n"
"border-radius: 4px;"));

        monthCalendarLayout->addWidget(yearComboBox);

        monthGridLayout = new QGridLayout();
        monthGridLayout->setSpacing(10);
        monthGridLayout->setObjectName("monthGridLayout");
        januaryButton = new QPushButton(monthCalendarWidget);
        januaryButton->setObjectName("januaryButton");
        januaryButton->setMinimumSize(QSize(90, 50));
        januaryButton->setStyleSheet(QString::fromUtf8("background-color: #1e4d4a;\n"
"color: #e0f7fa;\n"
"border: 1px solid #4dd0e1;\n"
"border-radius: 4px;"));

        monthGridLayout->addWidget(januaryButton, 0, 0, 1, 1);

        februaryButton = new QPushButton(monthCalendarWidget);
        februaryButton->setObjectName("februaryButton");
        februaryButton->setMinimumSize(QSize(90, 50));
        februaryButton->setStyleSheet(QString::fromUtf8("background-color: #1e4d4a;\n"
"color: #e0f7fa;\n"
"border: 1px solid #4dd0e1;\n"
"border-radius: 4px;"));

        monthGridLayout->addWidget(februaryButton, 0, 1, 1, 1);

        marchButton = new QPushButton(monthCalendarWidget);
        marchButton->setObjectName("marchButton");
        marchButton->setMinimumSize(QSize(90, 50));
        marchButton->setStyleSheet(QString::fromUtf8("background-color: #1e4d4a;\n"
"color: #e0f7fa;\n"
"border: 1px solid #4dd0e1;\n"
"border-radius: 4px;"));

        monthGridLayout->addWidget(marchButton, 0, 2, 1, 1);

        aprilButton = new QPushButton(monthCalendarWidget);
        aprilButton->setObjectName("aprilButton");
        aprilButton->setMinimumSize(QSize(90, 50));
        aprilButton->setStyleSheet(QString::fromUtf8("background-color: #1e4d4a;\n"
"color: #e0f7fa;\n"
"border: 1px solid #4dd0e1;\n"
"border-radius: 4px;"));

        monthGridLayout->addWidget(aprilButton, 0, 3, 1, 1);

        mayButton = new QPushButton(monthCalendarWidget);
        mayButton->setObjectName("mayButton");
        mayButton->setMinimumSize(QSize(90, 50));
        mayButton->setStyleSheet(QString::fromUtf8("background-color: #1e4d4a;\n"
"color: #e0f7fa;\n"
"border: 1px solid #4dd0e1;\n"
"border-radius: 4px;"));

        monthGridLayout->addWidget(mayButton, 1, 0, 1, 1);

        juneButton = new QPushButton(monthCalendarWidget);
        juneButton->setObjectName("juneButton");
        juneButton->setMinimumSize(QSize(90, 50));
        juneButton->setStyleSheet(QString::fromUtf8("background-color: #1e4d4a;\n"
"color: #e0f7fa;\n"
"border: 1px solid #4dd0e1;\n"
"border-radius: 4px;"));

        monthGridLayout->addWidget(juneButton, 1, 1, 1, 1);

        julyButton = new QPushButton(monthCalendarWidget);
        julyButton->setObjectName("julyButton");
        julyButton->setMinimumSize(QSize(90, 50));
        julyButton->setStyleSheet(QString::fromUtf8("background-color: #1e4d4a;\n"
"color: #e0f7fa;\n"
"border: 1px solid #4dd0e1;\n"
"border-radius: 4px;"));

        monthGridLayout->addWidget(julyButton, 1, 2, 1, 1);

        augustButton = new QPushButton(monthCalendarWidget);
        augustButton->setObjectName("augustButton");
        augustButton->setMinimumSize(QSize(90, 50));
        augustButton->setStyleSheet(QString::fromUtf8("background-color: #1e4d4a;\n"
"color: #e0f7fa;\n"
"border: 1px solid #4dd0e1;\n"
"border-radius: 4px;"));

        monthGridLayout->addWidget(augustButton, 1, 3, 1, 1);

        septemberButton = new QPushButton(monthCalendarWidget);
        septemberButton->setObjectName("septemberButton");
        septemberButton->setMinimumSize(QSize(90, 50));
        septemberButton->setStyleSheet(QString::fromUtf8("background-color: #1e4d4a;\n"
"color: #e0f7fa;\n"
"border: 1px solid #4dd0e1;\n"
"border-radius: 4px;"));

        monthGridLayout->addWidget(septemberButton, 2, 0, 1, 1);

        octoberButton = new QPushButton(monthCalendarWidget);
        octoberButton->setObjectName("octoberButton");
        octoberButton->setMinimumSize(QSize(90, 50));
        octoberButton->setStyleSheet(QString::fromUtf8("background-color: #1e4d4a;\n"
"color: #e0f7fa;\n"
"border: 1px solid #4dd0e1;\n"
"border-radius: 4px;"));

        monthGridLayout->addWidget(octoberButton, 2, 1, 1, 1);

        novemberButton = new QPushButton(monthCalendarWidget);
        novemberButton->setObjectName("novemberButton");
        novemberButton->setMinimumSize(QSize(90, 50));
        novemberButton->setStyleSheet(QString::fromUtf8("background-color: #1e4d4a;\n"
"color: #e0f7fa;\n"
"border: 1px solid #4dd0e1;\n"
"border-radius: 4px;"));

        monthGridLayout->addWidget(novemberButton, 2, 2, 1, 1);

        decemberButton = new QPushButton(monthCalendarWidget);
        decemberButton->setObjectName("decemberButton");
        decemberButton->setMinimumSize(QSize(90, 50));
        decemberButton->setStyleSheet(QString::fromUtf8("background-color: #1e4d4a;\n"
"color: #e0f7fa;\n"
"border: 1px solid #4dd0e1;\n"
"border-radius: 4px;"));

        monthGridLayout->addWidget(decemberButton, 2, 3, 1, 1);


        monthCalendarLayout->addLayout(monthGridLayout);

        listWidget_2 = new QListWidget(centralwidget);
        listWidget_2->setObjectName("listWidget_2");
        listWidget_2->setGeometry(QRect(760, 470, 401, 261));
        listWidget_2->setStyleSheet(QString::fromUtf8("background-color: #0d1f2d;\n"
"border-radius: 6px;\n"
"padding: 10px;\n"
"border: 1px solid #4dd0e1;\n"
"font-size: 16px;\n"
"color: #00e676;"));
        label_5 = new QLabel(centralwidget);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(50, 40, 51, 51));
        label_5->setAutoFillBackground(false);
        label_5->setPixmap(QPixmap(QString::fromUtf8(":/images/logo football.png")));
        label_5->setScaledContents(true);
        pushButton_3 = new QPushButton(centralwidget);
        pushButton_3->setObjectName("pushButton_3");
        pushButton_3->setGeometry(QRect(360, 680, 80, 31));
        pushButton_3->setStyleSheet(QString::fromUtf8("background-color: #00e676;\n"
"color: #ffffff;\n"
"border-radius: 5px;\n"
"padding: 6px 12px;\n"
"border: 1px solid #4dd0e1;"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/images/add.png"), QSize(), QIcon::Mode::Normal, QIcon::State::On);
        pushButton_3->setIcon(icon);
        pushButton_3->setIconSize(QSize(16, 16));
        test = new QTableView(centralwidget);
        test->setObjectName("test");
        test->setGeometry(QRect(40, 210, 591, 451));
        test->setStyleSheet(QString::fromUtf8("background-color: #0d1f2d;\n"
"border: 1px solid #4dd0e1;\n"
"color: #e0f7fa;"));
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(550, 680, 83, 29));
        pushButton->setStyleSheet(QString::fromUtf8("background-color: #d32f2f;\n"
"color: #ffffff;\n"
"border-radius: 5px;\n"
"padding: 6px 12px;\n"
"border: 1px solid #4dd0e1;"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/images/delete.png"), QSize(), QIcon::Mode::Normal, QIcon::State::On);
        pushButton->setIcon(icon1);
        pushButton->setIconSize(QSize(16, 16));
        pushButton_2 = new QPushButton(centralwidget);
        pushButton_2->setObjectName("pushButton_2");
        pushButton_2->setGeometry(QRect(450, 680, 83, 29));
        pushButton_2->setStyleSheet(QString::fromUtf8("background-color: #0288d1;\n"
"color: #ffffff;\n"
"border-radius: 5px;\n"
"padding: 6px 12px;\n"
"border: 1px solid #4dd0e1;"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/images/update.png"), QSize(), QIcon::Mode::Normal, QIcon::State::On);
        pushButton_2->setIcon(icon2);
        pushButton_2->setIconSize(QSize(16, 16));
        pushButton_4 = new QPushButton(centralwidget);
        pushButton_4->setObjectName("pushButton_4");
        pushButton_4->setGeometry(QRect(40, 680, 83, 29));
        pushButton_4->setStyleSheet(QString::fromUtf8("background-color: #0288d1;\n"
"color: #ffffff;\n"
"border-radius: 5px;\n"
"padding: 6px 12px;\n"
"border: 1px solid #4dd0e1;"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/images/stats.png"), QSize(), QIcon::Mode::Normal, QIcon::State::On);
        pushButton_4->setIcon(icon3);
        pushButton_4->setIconSize(QSize(16, 16));
        comp_name = new QLabel(centralwidget);
        comp_name->setObjectName("comp_name");
        comp_name->setGeometry(QRect(780, 480, 281, 41));
        QFont font1;
        font1.setPointSize(12);
        font1.setBold(true);
        comp_name->setFont(font1);
        comp_name->setStyleSheet(QString::fromUtf8("color: #e0f7fa;"));
        team_name = new QLabel(centralwidget);
        team_name->setObjectName("team_name");
        team_name->setGeometry(QRect(860, 580, 201, 51));
        QFont font2;
        font2.setPointSize(25);
        font2.setBold(true);
        team_name->setFont(font2);
        team_name->setStyleSheet(QString::fromUtf8("color: #00e676;"));
        pushButton_5 = new QPushButton(centralwidget);
        pushButton_5->setObjectName("pushButton_5");
        pushButton_5->setGeometry(QRect(130, 680, 101, 29));
        pushButton_5->setStyleSheet(QString::fromUtf8("background-color: #0288d1;\n"
"color: #ffffff;\n"
"border-radius: 5px;\n"
"padding: 6px 12px;\n"
"border: 1px solid #4dd0e1;"));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/images/generate.png"), QSize(), QIcon::Mode::Normal, QIcon::State::On);
        pushButton_5->setIcon(icon4);
        pushButton_5->setIconSize(QSize(16, 16));
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setGeometry(QRect(910, 130, 101, 20));
        QFont font3;
        font3.setPointSize(14);
        font3.setBold(true);
        label->setFont(font3);
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(860, 430, 201, 31));
        label_3->setFont(font3);
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1200, 25));
        menubar->setStyleSheet(QString::fromUtf8("background-color: #1e4d4a;\n"
"color: #e0f7fa;"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        statusbar->setStyleSheet(QString::fromUtf8("background-color: #1e4d4a;\n"
"color: #e0f7fa;"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        dashboard_2->setText(QCoreApplication::translate("MainWindow", "Player", nullptr));
        dashboard_7->setText(QCoreApplication::translate("MainWindow", "Competition", nullptr));
        dashboard_3->setText(QCoreApplication::translate("MainWindow", "Match", nullptr));
        dashboard_4->setText(QCoreApplication::translate("MainWindow", "Team", nullptr));
        comboBox->setItemText(0, QCoreApplication::translate("MainWindow", "Sort by", nullptr));
        comboBox->setItemText(1, QCoreApplication::translate("MainWindow", "By date", nullptr));
        comboBox->setItemText(2, QCoreApplication::translate("MainWindow", "By nb teams", nullptr));

        comboBox_2->setItemText(0, QCoreApplication::translate("MainWindow", "Type", nullptr));
        comboBox_2->setItemText(1, QCoreApplication::translate("MainWindow", "League", nullptr));
        comboBox_2->setItemText(2, QCoreApplication::translate("MainWindow", "Tournement", nullptr));

        yearComboBox->setItemText(0, QCoreApplication::translate("MainWindow", "2000", nullptr));
        yearComboBox->setItemText(1, QCoreApplication::translate("MainWindow", "2025", nullptr));
        yearComboBox->setItemText(2, QCoreApplication::translate("MainWindow", "2500", nullptr));

        januaryButton->setText(QCoreApplication::translate("MainWindow", "January", nullptr));
        februaryButton->setText(QCoreApplication::translate("MainWindow", "February", nullptr));
        marchButton->setText(QCoreApplication::translate("MainWindow", "March", nullptr));
        aprilButton->setText(QCoreApplication::translate("MainWindow", "April", nullptr));
        mayButton->setText(QCoreApplication::translate("MainWindow", "May", nullptr));
        juneButton->setText(QCoreApplication::translate("MainWindow", "June", nullptr));
        julyButton->setText(QCoreApplication::translate("MainWindow", "July", nullptr));
        augustButton->setText(QCoreApplication::translate("MainWindow", "August", nullptr));
        septemberButton->setText(QCoreApplication::translate("MainWindow", "September", nullptr));
        octoberButton->setText(QCoreApplication::translate("MainWindow", "October", nullptr));
        novemberButton->setText(QCoreApplication::translate("MainWindow", "November", nullptr));
        decemberButton->setText(QCoreApplication::translate("MainWindow", "December", nullptr));
        label_5->setText(QString());
        pushButton_3->setText(QCoreApplication::translate("MainWindow", "Add", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "Delete", nullptr));
        pushButton_2->setText(QCoreApplication::translate("MainWindow", "Update", nullptr));
        pushButton_4->setText(QCoreApplication::translate("MainWindow", "Stats", nullptr));
        comp_name->setText(QString());
        team_name->setText(QString());
        pushButton_5->setText(QCoreApplication::translate("MainWindow", "Generate", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Calendar", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "Winner prediction", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
