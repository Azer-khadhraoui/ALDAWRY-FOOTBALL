/********************************************************************************
** Form generated from reading UI file 'ListTD_team.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LISTTD_TEAM_H
#define UI_LISTTD_TEAM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
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
    QPushButton *pushButton_5;
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
        tableWidget->setObjectName("tableWidget");
        tableWidget->setGeometry(QRect(80, 100, 511, 401));
        tableWidget->setStyleSheet(QString::fromUtf8("/* General TableWidget styling */\n"
"QTableWidget#tableWidget {\n"
"    background-color: #1a1a1a; /* Dark blackish background for the table */\n"
"    color: white; /* White text for visibility */\n"
"    border: 1px solid #2d3a4a; /* Subtle dark blue/gray border */\n"
"    border-radius: 5px; /* Slightly rounded corners for modern look */\n"
"    gridline-color: #2d3a4a; /* Dark blue/gray grid lines */\n"
"    font-size: 12px; /* Readable font size */\n"
"    selection-background-color: #0078d7; /* Blue for selected cells */\n"
"    selection-color: white; /* White text in selected cells */\n"
"}\n"
"\n"
"/* Header styling for QTableWidget */\n"
"QTableWidget#tableWidget::item {\n"
"    padding: 5px; /* Internal padding for cells */\n"
"    background-color: transparent; /* Transparent background for cells */\n"
"}\n"
"QTableWidget#tableWidget::horizontalHeader {\n"
"    background-color: #2d3a4a; /* Dark blue/gray header background */\n"
"    color: white; /* White text for headers */\n"
"    border: none;"
                        " /* No border for clean look */\n"
"    font-weight: bold; /* Bold text for headers */\n"
"    border-bottom: 1px solid #2d3a4a; /* Subtle bottom border */\n"
"}\n"
"QTableWidget#tableWidget::verticalHeader {\n"
"    background-color: #1a1a1a; /* Match table background for vertical headers */\n"
"    color: white; /* White text */\n"
"    border: none; /* No border */\n"
"}\n"
"QTableWidget#tableWidget::horizontalHeader::section {\n"
"    background-color: #2d3a4a; /* Ensure header sections match */\n"
"    border: 1px solid #2d3a4a; /* Subtle border between sections */\n"
"    border-radius: 0px; /* No rounding for headers */\n"
"    padding: 5px; /* Internal padding */\n"
"}\n"
"QTableWidget#tableWidget::verticalHeader::section {\n"
"    background-color: #1a1a1a; /* Match table background */\n"
"    border: 1px solid #2d3a4a; /* Subtle border */\n"
"    padding: 5px; /* Internal padding */\n"
"}\n"
"\n"
"/* Hover state for table items */\n"
"QTableWidget#tableWidget::item:hover {\n"
"    background-color: #"
                        "3d4a5a; /* Lighter dark blue/gray on hover for feedback */\n"
"    color: white; /* White text on hover */\n"
"}\n"
"\n"
"/* Selected state for table items */\n"
"QTableWidget#tableWidget::item:selected {\n"
"    background-color: #0078d7; /* Blue for selected items */\n"
"    color: white; /* White text in selected items */\n"
"}\n"
"\n"
"/* Alternating row colors (optional for better readability) */\n"
"QTableWidget#tableWidget::item:alternate {\n"
"    background-color: #232b35; /* Slightly lighter alternate rows */\n"
"}\n"
"\n"
"/* Scrollbar styling (optional, for a consistent look) */\n"
"QTableWidget#tableWidget::verticalScrollBar, QTableWidget#tableWidget::horizontalScrollBar {\n"
"    background-color: #1a1a1a; /* Dark background for scrollbars */\n"
"    border: none; /* No border */\n"
"}\n"
"QTableWidget#tableWidget::verticalScrollBar::handle, QTableWidget#tableWidget::horizontalScrollBar::handle {\n"
"    background-color: #2d3a4a; /* Dark blue/gray handle */\n"
"    border-radius: 3px; /* Rounded"
                        " handle */\n"
"}\n"
"QTableWidget#tableWidget::verticalScrollBar::add-line, QTableWidget#tableWidget::horizontalScrollBar::add-line,\n"
"QTableWidget#tableWidget::verticalScrollBar::sub-line, QTableWidget#tableWidget::horizontalScrollBar::sub-line {\n"
"    background-color: #1a1a1a; /* Match background */\n"
"}\n"
"\n"
"/* Optional: Adjust padding and margins for tighter layout */\n"
"QTableWidget#tableWidget {\n"
"    padding: 0px; /* No padding around the table */\n"
"    margin: 0px; /* No margin */\n"
"}"));
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
        pushButton_6 = new QPushButton(Form);
        pushButton_6->setObjectName("pushButton_6");
        pushButton_6->setGeometry(QRect(520, 120, 122, 34));
        pushButton_6->setStyleSheet(QString::fromUtf8("background-color: #2C2F3F;  /* Elegant dark background */\n"
"    color: green\n"
";\n"
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
        ___qtablewidgetitem->setText(QCoreApplication::translate("Form", "Did", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("Form", "Doing", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(4);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("Form", "ToDO", nullptr));
        pushButton_5->setText(QCoreApplication::translate("Form", "Add", nullptr));
        pushButton_6->setText(QCoreApplication::translate("Form", "List-To-Do", nullptr));
        pushButton_7->setText(QCoreApplication::translate("Form", "Delete", nullptr));
        pushButton_8->setText(QCoreApplication::translate("Form", "Modify", nullptr));
        pushButton_9->setText(QCoreApplication::translate("Form", "Display", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Form: public Ui_Form {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LISTTD_TEAM_H
