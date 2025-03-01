/********************************************************************************
** Form generated from reading UI file 'Modify_joueur.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MODIFY_JOUEUR_H
#define UI_MODIFY_JOUEUR_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Form
{
public:
    QLabel *dashboard_2;
    QFrame *line_2;
    QListWidget *menu;
    QFrame *line_3;
    QLabel *label_4;
    QLabel *dashboard_3;
    QLabel *dashboard_7;
    QLabel *dashboard_4;
    QLabel *label;
    QFrame *line;
    QLabel *label_3;
    QListWidget *menu_2;
    QLabel *label_17;
    QFrame *frame_6;
    QTableWidget *tableWidget;
    QFrame *frame_2;
    QLineEdit *lineEdit_7;
    QLabel *label_5;
    QFrame *frame;
    QLabel *label_16;
    QPushButton *pushButton_5;
    QFrame *frame_3;
    QListWidget *azer;
    QListWidget *listWidget_2;
    QLabel *dashboard_6;
    QLineEdit *lineEdit;
    QLabel *label_6;
    QPushButton *pushButton_6;
    QPushButton *pushButton_7;
    QPushButton *pushButton_8;
    QPushButton *pushButton_9;

    void setupUi(QWidget *Form)
    {
        if (Form->objectName().isEmpty())
            Form->setObjectName("Form");
        Form->resize(1200, 800);
        QFont font;
        font.setPointSize(10);
        Form->setFont(font);
        Form->setStyleSheet(QString::fromUtf8("background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 #1b1f2a, stop:1 #10131a);\n"
""));
        dashboard_2 = new QLabel(Form);
        dashboard_2->setObjectName("dashboard_2");
        dashboard_2->setGeometry(QRect(210, 40, 71, 31));
        QFont font1;
        font1.setFamilies({QString::fromUtf8("Franklin Gothic Book")});
        font1.setPointSize(12);
        font1.setWeight(QFont::Thin);
        dashboard_2->setFont(font1);
        dashboard_2->setStyleSheet(QString::fromUtf8("background-color: transparent;\n"
"color: rgb(255, 255, 255);"));
        line_2 = new QFrame(Form);
        line_2->setObjectName("line_2");
        line_2->setGeometry(QRect(640, 20, 3, 61));
        line_2->setStyleSheet(QString::fromUtf8("border: 2px solid #4C5C75;"));
        line_2->setFrameShape(QFrame::Shape::VLine);
        line_2->setFrameShadow(QFrame::Shadow::Sunken);
        menu = new QListWidget(Form);
        menu->setObjectName("menu");
        menu->setGeometry(QRect(20, 20, 1151, 71));
        menu->setStyleSheet(QString::fromUtf8("background: #192231;\n"
"color: #D3D3D3;\n"
"border-bottom: 2px solid #4C5C75;\n"
"\n"
"border-radius: 30px;\n"
"\n"
""));
        line_3 = new QFrame(Form);
        line_3->setObjectName("line_3");
        line_3->setGeometry(QRect(880, 20, 3, 61));
        line_3->setStyleSheet(QString::fromUtf8("border: 2px solid #4C5C75;"));
        line_3->setFrameShape(QFrame::Shape::VLine);
        line_3->setFrameShadow(QFrame::Shadow::Sunken);
        label_4 = new QLabel(Form);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(1120, 40, 40, 40));
        label_4->setStyleSheet(QString::fromUtf8("background-color:transparent;"));
        label_4->setPixmap(QPixmap(QString::fromUtf8("user.png")));
        label_4->setScaledContents(true);
        dashboard_3 = new QLabel(Form);
        dashboard_3->setObjectName("dashboard_3");
        dashboard_3->setGeometry(QRect(740, 40, 71, 31));
        dashboard_3->setFont(font1);
        dashboard_3->setStyleSheet(QString::fromUtf8("background-color: transparent;\n"
"color: rgb(158, 158, 158);"));
        dashboard_7 = new QLabel(Form);
        dashboard_7->setObjectName("dashboard_7");
        dashboard_7->setGeometry(QRect(460, 40, 131, 31));
        dashboard_7->setFont(font1);
        dashboard_7->setStyleSheet(QString::fromUtf8("background-color: transparent;\n"
"color: rgb(158, 158, 158);"));
        dashboard_4 = new QLabel(Form);
        dashboard_4->setObjectName("dashboard_4");
        dashboard_4->setGeometry(QRect(960, 40, 61, 31));
        dashboard_4->setFont(font1);
        dashboard_4->setStyleSheet(QString::fromUtf8("background-color: transparent;\n"
"color: rgb(158, 158, 158);"));
        label = new QLabel(Form);
        label->setObjectName("label");
        label->setGeometry(QRect(50, 30, 50, 50));
        label->setPixmap(QPixmap(QString::fromUtf8("../../../../../Pictures/proj QT/logo football.png")));
        label->setScaledContents(true);
        line = new QFrame(Form);
        line->setObjectName("line");
        line->setGeometry(QRect(360, 20, 3, 61));
        line->setStyleSheet(QString::fromUtf8("color: rgb(40, 40, 40);\n"
"border: 2px solid #4C5C75;"));
        line->setFrameShape(QFrame::Shape::VLine);
        line->setFrameShadow(QFrame::Shadow::Sunken);
        label_3 = new QLabel(Form);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(1110, 40, 40, 40));
        label_3->setStyleSheet(QString::fromUtf8("background-color: transparent;"));
        label_3->setPixmap(QPixmap(QString::fromUtf8("../../../../../Pictures/icons/user.png")));
        label_3->setScaledContents(true);
        menu_2 = new QListWidget(Form);
        menu_2->setObjectName("menu_2");
        menu_2->setGeometry(QRect(20, 20, 111, 71));
        menu_2->setStyleSheet(QString::fromUtf8("background: #0A1628;\n"
"color: #FFFFFF;\n"
"border-bottom: 3px solid #00FF7F;\n"
"\n"
"border-radius: 30px;\n"
"\n"
""));
        label_17 = new QLabel(Form);
        label_17->setObjectName("label_17");
        label_17->setGeometry(QRect(1110, 40, 30, 30));
        label_17->setStyleSheet(QString::fromUtf8("background-color:transparent;"));
        label_17->setPixmap(QPixmap(QString::fromUtf8("../../../../../Pictures/proj QT/user.png")));
        label_17->setScaledContents(true);
        frame_6 = new QFrame(Form);
        frame_6->setObjectName("frame_6");
        frame_6->setGeometry(QRect(20, 140, 651, 641));
        frame_6->setFrameShape(QFrame::Shape::StyledPanel);
        frame_6->setFrameShadow(QFrame::Shadow::Raised);
        tableWidget = new QTableWidget(frame_6);
        if (tableWidget->columnCount() < 5)
            tableWidget->setColumnCount(5);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        if (tableWidget->rowCount() < 11)
            tableWidget->setRowCount(11);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(0, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(1, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(2, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(3, __qtablewidgetitem8);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(4, __qtablewidgetitem9);
        QTableWidgetItem *__qtablewidgetitem10 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(5, __qtablewidgetitem10);
        QTableWidgetItem *__qtablewidgetitem11 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(6, __qtablewidgetitem11);
        QTableWidgetItem *__qtablewidgetitem12 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(7, __qtablewidgetitem12);
        QTableWidgetItem *__qtablewidgetitem13 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(8, __qtablewidgetitem13);
        QTableWidgetItem *__qtablewidgetitem14 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(9, __qtablewidgetitem14);
        QTableWidgetItem *__qtablewidgetitem15 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(10, __qtablewidgetitem15);
        QTableWidgetItem *__qtablewidgetitem16 = new QTableWidgetItem();
        tableWidget->setItem(0, 0, __qtablewidgetitem16);
        QTableWidgetItem *__qtablewidgetitem17 = new QTableWidgetItem();
        tableWidget->setItem(1, 0, __qtablewidgetitem17);
        QTableWidgetItem *__qtablewidgetitem18 = new QTableWidgetItem();
        tableWidget->setItem(2, 0, __qtablewidgetitem18);
        QTableWidgetItem *__qtablewidgetitem19 = new QTableWidgetItem();
        tableWidget->setItem(3, 0, __qtablewidgetitem19);
        QTableWidgetItem *__qtablewidgetitem20 = new QTableWidgetItem();
        tableWidget->setItem(4, 0, __qtablewidgetitem20);
        QTableWidgetItem *__qtablewidgetitem21 = new QTableWidgetItem();
        tableWidget->setItem(5, 0, __qtablewidgetitem21);
        QTableWidgetItem *__qtablewidgetitem22 = new QTableWidgetItem();
        tableWidget->setItem(6, 0, __qtablewidgetitem22);
        QTableWidgetItem *__qtablewidgetitem23 = new QTableWidgetItem();
        tableWidget->setItem(7, 0, __qtablewidgetitem23);
        QTableWidgetItem *__qtablewidgetitem24 = new QTableWidgetItem();
        tableWidget->setItem(8, 0, __qtablewidgetitem24);
        QTableWidgetItem *__qtablewidgetitem25 = new QTableWidgetItem();
        tableWidget->setItem(9, 0, __qtablewidgetitem25);
        tableWidget->setObjectName("tableWidget");
        tableWidget->setGeometry(QRect(20, 130, 601, 361));
        tableWidget->setStyleSheet(QString::fromUtf8("/* Style for the specific QTableView named tableView */\n"
"#tableView {\n"
"    background-color: #1C1F2A; /* Matches the dark background of your UI */\n"
"    border: 1px solid #2A2D3A; /* Subtle border for definition */\n"
"    border-radius: 5px; /* Rounded corners to match your UI */\n"
"    color: white; /* White text for readability on dark background */\n"
"    gridline-color: #2A2D3A; /* Dark grid lines for better visibility */\n"
"    selection-background-color: #4A5970; /* Slightly lighter blue-gray for selected rows */\n"
"    selection-color: white; /* White text for selected items */\n"
"    alternate-background-color: #192231; /* Alternate row color for better readability */\n"
"}\n"
"\n"
"/* Style for headers (horizontal and vertical) of tableView */\n"
"#tableView QHeaderView::section {\n"
"    background-color: #2E3B4E; /* Slightly lighter header background */\n"
"    border: 1px solid #4C5C75; /* Matching border color from your UI */\n"
"    border-radius: 3px; /* Subtle rounding */\n"
"    "
                        "color: white; /* White text for headers */\n"
"    padding: 5px; /* Padding for better spacing */\n"
"    font-weight: bold; /* Bold headers for emphasis */\n"
"    margin: 0px; /* Remove extra margins */\n"
"}\n"
"\n"
"/* Style for items (cells) in tableView */\n"
"#tableView::item {\n"
"    padding: 5px; /* Padding inside cells */\n"
"}\n"
"\n"
"/* Style for scroll bars of tableView */\n"
"#tableView::verticalScrollBar, #tableView::horizontalScrollBar {\n"
"    background-color: #1C1F2A; /* Dark background for scroll bars */\n"
"    width: 15px; /* Width of vertical scroll bar */\n"
"    height: 15px; /* Height of horizontal scroll bar */\n"
"}\n"
"\n"
"#tableView QScrollBar::handle:vertical, #tableView QScrollBar::handle:horizontal {\n"
"    background-color: #4C5C75; /* Scroll handle color matching your UI lines */\n"
"    border-radius: 7px; /* Rounded scroll handle */\n"
"    min-height: 20px;\n"
"    min-width: 20px;\n"
"}\n"
"\n"
"#tableView QScrollBar::add-line, #tableView QScrollBar::sub-line {\n"
" "
                        "   background: none; /* Remove arrows */\n"
"    border: none;\n"
"}\n"
"\n"
"#tableView QScrollBar::add-page, #tableView QScrollBar::sub-page {\n"
"    background: none; /* Transparent background for scroll areas */\n"
"}\n"
"\n"
"/* Focus frame (when an item in tableView is focused) */\n"
"#tableView:focus {\n"
"    border: 2px solid #00FF7F; /* Green outline for focus, matching your logo */\n"
"}\n"
"\n"
"/* Disabled state for tableView */\n"
"#tableView:disabled {\n"
"    color: #808080; /* Gray text for disabled state */\n"
"    background-color: #151A24; /* Slightly darker background for disabled state */\n"
"}"));
        frame_2 = new QFrame(frame_6);
        frame_2->setObjectName("frame_2");
        frame_2->setGeometry(QRect(280, 60, 341, 41));
        frame_2->setStyleSheet(QString::fromUtf8("    background-color: #1E1E2D;  /* Dark matte background */\n"
"\n"
"\n"
" \n"
"\n"
""));
        frame_2->setFrameShape(QFrame::Shape::StyledPanel);
        frame_2->setFrameShadow(QFrame::Shadow::Raised);
        lineEdit_7 = new QLineEdit(frame_2);
        lineEdit_7->setObjectName("lineEdit_7");
        lineEdit_7->setGeometry(QRect(70, 10, 211, 23));
        lineEdit_7->setStyleSheet(QString::fromUtf8("    background-color: #141821;  /* Slightly lighter for contrast */\n"
"    border: 2px solid #cccccc;  /* Keep borders subtle */\n"
"    border-radius: 6px;\n"
"    padding: 6px 10px;\n"
"    font-size: 14px;\n"
"    color: white;"));
        label_5 = new QLabel(frame_2);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(300, 20, 18, 18));
        label_5->setPixmap(QPixmap(QString::fromUtf8("../../../../../Pictures/proj QT/trier.png")));
        label_5->setScaledContents(true);
        frame = new QFrame(frame_2);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(20, 10, 31, 25));
        frame->setFrameShape(QFrame::Shape::StyledPanel);
        frame->setFrameShadow(QFrame::Shadow::Raised);
        label_16 = new QLabel(frame);
        label_16->setObjectName("label_16");
        label_16->setGeometry(QRect(10, 10, 11, 11));
        label_16->setPixmap(QPixmap(QString::fromUtf8("../../../../../Pictures/proj QT/search.png")));
        label_16->setScaledContents(true);
        frame->raise();
        lineEdit_7->raise();
        label_5->raise();
        pushButton_5 = new QPushButton(Form);
        pushButton_5->setObjectName("pushButton_5");
        pushButton_5->setGeometry(QRect(40, 120, 122, 34));
        pushButton_5->setStyleSheet(QString::fromUtf8("background-color: #2C2F3F;  /* Elegant dark background */\n"
"    color: white;\n"
"    font-size: 14px;\n"
"    font-weight: bold;\n"
"    border: 1px solid #5A5F69;\n"
"    border-radius: 6px;\n"
"    padding: 8px 15px;\n"
"    min-width: 90px;\n"
"    transition: all 0.3s ease-in-out;"));
        frame_3 = new QFrame(Form);
        frame_3->setObjectName("frame_3");
        frame_3->setGeometry(QRect(720, 220, 431, 501));
        frame_3->setFrameShape(QFrame::Shape::StyledPanel);
        frame_3->setFrameShadow(QFrame::Shadow::Raised);
        azer = new QListWidget(frame_3);
        azer->setObjectName("azer");
        azer->setGeometry(QRect(60, 160, 291, 281));
        azer->setStyleSheet(QString::fromUtf8("background: #2E3B4E;\n"
"border: 1px solid #4C5C75;\n"
"\n"
"border-radius: 30px;\n"
"\n"
""));
        listWidget_2 = new QListWidget(frame_3);
        listWidget_2->setObjectName("listWidget_2");
        listWidget_2->setGeometry(QRect(110, 70, 191, 201));
        listWidget_2->setStyleSheet(QString::fromUtf8("border-radius: 90px;\n"
"background-color: qradialgradient(spread:pad, cx:0.5, cy:0.5, radius:0.5, fx:0.5, fy:0.5, stop:0 rgba(13, 27, 42, 255), stop:1 rgba(27, 38, 59, 255));"));
        dashboard_6 = new QLabel(frame_3);
        dashboard_6->setObjectName("dashboard_6");
        dashboard_6->setGeometry(QRect(120, 330, 171, 31));
        QFont font2;
        font2.setFamilies({QString::fromUtf8("Sans Serif Collection")});
        font2.setPointSize(10);
        font2.setBold(true);
        dashboard_6->setFont(font2);
        dashboard_6->setStyleSheet(QString::fromUtf8("background-color: transparent;\n"
"    color: red;\n"
"    font-weight: bold;\n"
"    text-shadow: 0px 0px 8px rgba(255, 215, 0, 0.8); /* Gold glow */\n"
""));
        lineEdit = new QLineEdit(frame_3);
        lineEdit->setObjectName("lineEdit");
        lineEdit->setGeometry(QRect(90, 330, 231, 31));
        label_6 = new QLabel(frame_3);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(0, 10, 461, 271));
        label_6->setStyleSheet(QString::fromUtf8("background-color: transparent;"));
        label_6->setPixmap(QPixmap(QString::fromUtf8("../../../../../../Downloads/Unazeaztitled-1.png")));
        label_6->setScaledContents(true);
        azer->raise();
        lineEdit->raise();
        listWidget_2->raise();
        dashboard_6->raise();
        label_6->raise();
        pushButton_6 = new QPushButton(Form);
        pushButton_6->setObjectName("pushButton_6");
        pushButton_6->setGeometry(QRect(520, 120, 122, 34));
        pushButton_6->setStyleSheet(QString::fromUtf8("background-color: #2C2F3F;  /* Elegant dark background */\n"
"    color: white;\n"
"    font-size: 14px;\n"
"    font-weight: bold;\n"
"    border: 1px solid #5A5F69;\n"
"    border-radius: 6px;\n"
"    padding: 8px 15px;\n"
"    min-width: 90px;\n"
"    transition: all 0.3s ease-in-out;"));
        pushButton_7 = new QPushButton(Form);
        pushButton_7->setObjectName("pushButton_7");
        pushButton_7->setGeometry(QRect(400, 120, 122, 34));
        pushButton_7->setStyleSheet(QString::fromUtf8("background-color: #2C2F3F;  /* Elegant dark background */\n"
"    color: white;\n"
"    font-size: 14px;\n"
"    font-weight: bold;\n"
"    border: 1px solid #5A5F69;\n"
"    border-radius: 6px;\n"
"    padding: 8px 15px;\n"
"    min-width: 90px;\n"
"    transition: all 0.3s ease-in-out;"));
        pushButton_8 = new QPushButton(Form);
        pushButton_8->setObjectName("pushButton_8");
        pushButton_8->setGeometry(QRect(280, 120, 122, 34));
        pushButton_8->setStyleSheet(QString::fromUtf8("background-color: #2C2F3F;  /* Elegant dark background */\n"
"    color: white;\n"
"    font-size: 14px;\n"
"    font-weight: bold;\n"
"    border: 1px solid #5A5F69;\n"
"    border-radius: 6px;\n"
"    padding: 8px 15px;\n"
"    min-width: 90px;\n"
"    transition: all 0.3s ease-in-out;"));
        pushButton_9 = new QPushButton(Form);
        pushButton_9->setObjectName("pushButton_9");
        pushButton_9->setGeometry(QRect(160, 120, 122, 34));
        pushButton_9->setStyleSheet(QString::fromUtf8("background-color: #2C2F3F;  /* Elegant dark background */\n"
"    color: white;\n"
"    font-size: 14px;\n"
"    font-weight: bold;\n"
"    border: 1px solid #5A5F69;\n"
"    border-radius: 6px;\n"
"    padding: 8px 15px;\n"
"    min-width: 90px;\n"
"    transition: all 0.3s ease-in-out;"));
        menu->raise();
        menu_2->raise();
        dashboard_2->raise();
        line_2->raise();
        line_3->raise();
        label_4->raise();
        dashboard_3->raise();
        dashboard_7->raise();
        dashboard_4->raise();
        line->raise();
        label_3->raise();
        label->raise();
        label_17->raise();
        frame_6->raise();
        pushButton_5->raise();
        frame_3->raise();
        pushButton_6->raise();
        pushButton_7->raise();
        pushButton_8->raise();
        pushButton_9->raise();

        retranslateUi(Form);

        QMetaObject::connectSlotsByName(Form);
    } // setupUi

    void retranslateUi(QWidget *Form)
    {
        Form->setWindowTitle(QCoreApplication::translate("Form", "Form", nullptr));
        dashboard_2->setText(QCoreApplication::translate("Form", "Player", nullptr));
        label_4->setText(QString());
        dashboard_3->setText(QCoreApplication::translate("Form", "Match", nullptr));
        dashboard_7->setText(QCoreApplication::translate("Form", "Competition", nullptr));
        dashboard_4->setText(QCoreApplication::translate("Form", "Team", nullptr));
        label->setText(QString());
        label_3->setText(QString());
        label_17->setText(QString());
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("Form", "Ronaldo", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("Form", "neuer", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("Form", "modric", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("Form", "vini", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("Form", "Messi", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidget->verticalHeaderItem(0);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("Form", "First_Name", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidget->verticalHeaderItem(1);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("Form", "Last_Name", nullptr));
        QTableWidgetItem *___qtablewidgetitem7 = tableWidget->verticalHeaderItem(2);
        ___qtablewidgetitem7->setText(QCoreApplication::translate("Form", "Postion", nullptr));
        QTableWidgetItem *___qtablewidgetitem8 = tableWidget->verticalHeaderItem(3);
        ___qtablewidgetitem8->setText(QCoreApplication::translate("Form", "Jersey_nb", nullptr));
        QTableWidgetItem *___qtablewidgetitem9 = tableWidget->verticalHeaderItem(4);
        ___qtablewidgetitem9->setText(QCoreApplication::translate("Form", "Date_Of_Birth", nullptr));
        QTableWidgetItem *___qtablewidgetitem10 = tableWidget->verticalHeaderItem(5);
        ___qtablewidgetitem10->setText(QCoreApplication::translate("Form", "Nationailty", nullptr));
        QTableWidgetItem *___qtablewidgetitem11 = tableWidget->verticalHeaderItem(6);
        ___qtablewidgetitem11->setText(QCoreApplication::translate("Form", "Goals", nullptr));
        QTableWidgetItem *___qtablewidgetitem12 = tableWidget->verticalHeaderItem(7);
        ___qtablewidgetitem12->setText(QCoreApplication::translate("Form", "Injured", nullptr));
        QTableWidgetItem *___qtablewidgetitem13 = tableWidget->verticalHeaderItem(8);
        ___qtablewidgetitem13->setText(QCoreApplication::translate("Form", "Red_cart", nullptr));
        QTableWidgetItem *___qtablewidgetitem14 = tableWidget->verticalHeaderItem(9);
        ___qtablewidgetitem14->setText(QCoreApplication::translate("Form", "Red_card", nullptr));
        QTableWidgetItem *___qtablewidgetitem15 = tableWidget->verticalHeaderItem(10);
        ___qtablewidgetitem15->setText(QCoreApplication::translate("Form", "Picture", nullptr));

        const bool __sortingEnabled = tableWidget->isSortingEnabled();
        tableWidget->setSortingEnabled(false);
        QTableWidgetItem *___qtablewidgetitem16 = tableWidget->item(0, 0);
        ___qtablewidgetitem16->setText(QCoreApplication::translate("Form", "Cristiano", nullptr));
        QTableWidgetItem *___qtablewidgetitem17 = tableWidget->item(1, 0);
        ___qtablewidgetitem17->setText(QCoreApplication::translate("Form", "Ronaldo", nullptr));
        QTableWidgetItem *___qtablewidgetitem18 = tableWidget->item(2, 0);
        ___qtablewidgetitem18->setText(QCoreApplication::translate("Form", "ATT", nullptr));
        QTableWidgetItem *___qtablewidgetitem19 = tableWidget->item(3, 0);
        ___qtablewidgetitem19->setText(QCoreApplication::translate("Form", "7", nullptr));
        QTableWidgetItem *___qtablewidgetitem20 = tableWidget->item(4, 0);
        ___qtablewidgetitem20->setText(QCoreApplication::translate("Form", "&&&", nullptr));
        QTableWidgetItem *___qtablewidgetitem21 = tableWidget->item(5, 0);
        ___qtablewidgetitem21->setText(QCoreApplication::translate("Form", "PORT", nullptr));
        QTableWidgetItem *___qtablewidgetitem22 = tableWidget->item(6, 0);
        ___qtablewidgetitem22->setText(QCoreApplication::translate("Form", "99", nullptr));
        QTableWidgetItem *___qtablewidgetitem23 = tableWidget->item(7, 0);
        ___qtablewidgetitem23->setText(QCoreApplication::translate("Form", "NO", nullptr));
        QTableWidgetItem *___qtablewidgetitem24 = tableWidget->item(8, 0);
        ___qtablewidgetitem24->setText(QCoreApplication::translate("Form", "2", nullptr));
        QTableWidgetItem *___qtablewidgetitem25 = tableWidget->item(9, 0);
        ___qtablewidgetitem25->setText(QCoreApplication::translate("Form", "1", nullptr));
        tableWidget->setSortingEnabled(__sortingEnabled);

        label_5->setText(QString());
        label_16->setText(QString());
        pushButton_5->setText(QCoreApplication::translate("Form", "Add", nullptr));
        dashboard_6->setText(QCoreApplication::translate("Form", "Player Of The Week", nullptr));
        label_6->setText(QString());
        pushButton_6->setText(QCoreApplication::translate("Form", "Stats", nullptr));
        pushButton_7->setText(QCoreApplication::translate("Form", "Delete", nullptr));
        pushButton_8->setText(QCoreApplication::translate("Form", "Modify", nullptr));
        pushButton_9->setText(QCoreApplication::translate("Form", "Display", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Form: public Ui_Form {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MODIFY_JOUEUR_H
