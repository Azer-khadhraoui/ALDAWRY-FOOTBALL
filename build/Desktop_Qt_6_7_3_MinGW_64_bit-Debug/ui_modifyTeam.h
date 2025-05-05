/********************************************************************************
** Form generated from reading UI file 'modifyTeam.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MODIFYTEAM_H
#define UI_MODIFYTEAM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_modifyTeam
{
public:
    QWidget *widget;
    QGridLayout *gridLayout_4;
    QPushButton *button1_2;
    QComboBox *cb_2;
    QLabel *label_12;
    QLineEdit *l1_2;
    QLabel *label_13;
    QLabel *label_14;
    QLabel *label_15;
    QLabel *label_16;
    QLineEdit *l2_3;
    QWidget *widget_3;
    QHBoxLayout *horizontalLayout_2;
    QToolButton *toolButton_2;
    QLabel *label_3;
    QLineEdit *l2_4;
    QLabel *label_19;
    QLabel *label_29;
    QLabel *label_30;
    QLabel *label_27;
    QLabel *label_28;
    QLabel *label_4;

    void setupUi(QWidget *modifyTeam)
    {
        if (modifyTeam->objectName().isEmpty())
            modifyTeam->setObjectName("modifyTeam");
        modifyTeam->resize(561, 591);
        modifyTeam->setStyleSheet(QString::fromUtf8("background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 #1b1f2a, stop:1 #10131a);"));
        widget = new QWidget(modifyTeam);
        widget->setObjectName("widget");
        widget->setGeometry(QRect(10, 80, 541, 491));
        widget->setStyleSheet(QString::fromUtf8("background-color: rgb(25, 31, 42);\n"
"    color: #FFFFFF;\n"
"    font-family: 'Segoe UI', Arial, sans-serif;\n"
"    font-size: 12px;\n"
"    border-radius: 15px;\n"
"    padding: 15px;\n"
"    spacing: 2px;\n"
""));
        gridLayout_4 = new QGridLayout(widget);
        gridLayout_4->setObjectName("gridLayout_4");
        button1_2 = new QPushButton(widget);
        button1_2->setObjectName("button1_2");
        button1_2->setStyleSheet(QString::fromUtf8("background-color: #00FF7F; /* Green to match the accent */\n"
"    color: #1A2633; /* Dark blue text for contrast */\n"
"    font-size: 12px;\n"
"    font-weight: bold;\n"
"    border-radius: 5px;\n"
"    padding: 6px 12px;\n"
"    margin-left: 350px;\n"
"    margin-right: 20px;\n"
"    margin-bottom: 5px;"));

        gridLayout_4->addWidget(button1_2, 10, 0, 1, 1);

        cb_2 = new QComboBox(widget);
        cb_2->addItem(QString());
        cb_2->addItem(QString());
        cb_2->addItem(QString());
        cb_2->addItem(QString());
        cb_2->addItem(QString());
        cb_2->setObjectName("cb_2");
        cb_2->setStyleSheet(QString::fromUtf8("background-color: #2A3240;\n"
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

        gridLayout_4->addWidget(cb_2, 3, 0, 1, 1);

        label_12 = new QLabel(widget);
        label_12->setObjectName("label_12");
        label_12->setStyleSheet(QString::fromUtf8("color: #A0A8B7;\n"
"font-weight: bold;\n"
"padding-bottom: 5px;background-color:transparent;"));

        gridLayout_4->addWidget(label_12, 6, 0, 1, 1);

        l1_2 = new QLineEdit(widget);
        l1_2->setObjectName("l1_2");
        l1_2->setStyleSheet(QString::fromUtf8("background-color: #2A3240; /* Darker blue-gray for input fields */\n"
"    border: 1px solid #3A4A5A; /* Subtle blue-gray border */\n"
"    border-radius: 5px;\n"
"    padding: 5px;\n"
"    color: #E0E6ED; /* Light gray text for readability */\n"
"    margin-left: 15px;\n"
"    margin-right: 15px;\n"
""));

        gridLayout_4->addWidget(l1_2, 1, 0, 1, 1);

        label_13 = new QLabel(widget);
        label_13->setObjectName("label_13");
        label_13->setStyleSheet(QString::fromUtf8("color: #A0A8B7;\n"
"font-weight: bold;\n"
"padding-bottom: 5px;background-color:transparent;"));

        gridLayout_4->addWidget(label_13, 4, 0, 1, 1);

        label_14 = new QLabel(widget);
        label_14->setObjectName("label_14");
        label_14->setStyleSheet(QString::fromUtf8("color: #A0A8B7;\n"
"font-weight: bold;\n"
"padding-bottom: 5px;background-color:transparent;"));

        gridLayout_4->addWidget(label_14, 8, 0, 1, 1);

        label_15 = new QLabel(widget);
        label_15->setObjectName("label_15");
        label_15->setStyleSheet(QString::fromUtf8("color: #A0A8B7;\n"
"font-weight: bold;\n"
"padding-bottom: 5px;background-color:transparent;"));

        gridLayout_4->addWidget(label_15, 0, 0, 1, 1);

        label_16 = new QLabel(widget);
        label_16->setObjectName("label_16");
        label_16->setStyleSheet(QString::fromUtf8("color: #A0A8B7;\n"
"font-weight: bold;\n"
"padding-bottom: 5px;background-color:transparent;"));

        gridLayout_4->addWidget(label_16, 2, 0, 1, 1);

        l2_3 = new QLineEdit(widget);
        l2_3->setObjectName("l2_3");
        l2_3->setStyleSheet(QString::fromUtf8("background-color: #2A3240; /* Darker blue-gray for input fields */\n"
"    border: 1px solid #3A4A5A; /* Subtle blue-gray border */\n"
"    border-radius: 5px;\n"
"    padding: 5px;\n"
"    color: #E0E6ED; /* Light gray text for readability */\n"
"    margin-left: 15px;\n"
"    margin-right: 15px;"));

        gridLayout_4->addWidget(l2_3, 5, 0, 1, 1);

        widget_3 = new QWidget(widget);
        widget_3->setObjectName("widget_3");
        widget_3->setStyleSheet(QString::fromUtf8("background-color: #2A3240;\n"
"    border: 1px solid #3A4A5A;\n"
"    border-radius: 5px;\n"
"    padding: 3px;\n"
"    color: #E0E6ED;\n"
"    margin-left: 15px;\n"
"    margin-right: 15px;\n"
"    margin-bottom: 15px;"));
        horizontalLayout_2 = new QHBoxLayout(widget_3);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        toolButton_2 = new QToolButton(widget_3);
        toolButton_2->setObjectName("toolButton_2");
        toolButton_2->setStyleSheet(QString::fromUtf8("background-color: #1C1F2A;\n"
"border: 1px solid #2A2D3A;\n"
"border-radius: 5px;\n"
"padding: 3px;\n"
"color: white;\n"
"margin-left: 15px;\n"
"margin-right:15px;\n"
"margin-bottom:15px;"));

        horizontalLayout_2->addWidget(toolButton_2);

        label_3 = new QLabel(widget_3);
        label_3->setObjectName("label_3");
        label_3->setStyleSheet(QString::fromUtf8("color: #A0A8B7;\n"
"padding-left: 10px;\n"
"background-color: transparent;"));

        horizontalLayout_2->addWidget(label_3);


        gridLayout_4->addWidget(widget_3, 7, 0, 1, 1);

        l2_4 = new QLineEdit(widget);
        l2_4->setObjectName("l2_4");
        l2_4->setStyleSheet(QString::fromUtf8("background-color: #2A3240; /* Darker blue-gray for input fields */\n"
"    border: 1px solid #3A4A5A; /* Subtle blue-gray border */\n"
"    border-radius: 5px;\n"
"    padding: 5px;\n"
"    color: #E0E6ED; /* Light gray text for readability */\n"
"    margin-left: 15px;\n"
"    margin-right: 15px;"));

        gridLayout_4->addWidget(l2_4, 9, 0, 1, 1);

        label_19 = new QLabel(modifyTeam);
        label_19->setObjectName("label_19");
        label_19->setGeometry(QRect(40, 190, 17, 17));
        label_19->setStyleSheet(QString::fromUtf8("background-color:transparent;"));
        label_19->setPixmap(QPixmap(QString::fromUtf8(":/teamimg/terrain.png")));
        label_19->setScaledContents(true);
        label_29 = new QLabel(modifyTeam);
        label_29->setObjectName("label_29");
        label_29->setGeometry(QRect(40, 346, 21, 21));
        label_29->setStyleSheet(QString::fromUtf8("background-color:transparent;"));
        label_29->setPixmap(QPixmap(QString::fromUtf8(":/teamimg/logo.png")));
        label_29->setScaledContents(true);
        label_30 = new QLabel(modifyTeam);
        label_30->setObjectName("label_30");
        label_30->setGeometry(QRect(40, 470, 18, 16));
        label_30->setStyleSheet(QString::fromUtf8("background-color:transparent;"));
        label_30->setPixmap(QPixmap(QString::fromUtf8(":/teamimg/abv.png")));
        label_30->setScaledContents(true);
        label_27 = new QLabel(modifyTeam);
        label_27->setObjectName("label_27");
        label_27->setGeometry(QRect(40, 270, 12, 18));
        label_27->setStyleSheet(QString::fromUtf8("background-color:transparent;"));
        label_27->setPixmap(QPixmap(QString::fromUtf8(":/teamimg/money.png")));
        label_27->setScaledContents(true);
        label_28 = new QLabel(modifyTeam);
        label_28->setObjectName("label_28");
        label_28->setGeometry(QRect(40, 110, 17, 17));
        label_28->setStyleSheet(QString::fromUtf8("color: #B0C0D0;background-color:transparent;"));
        label_28->setPixmap(QPixmap(QString::fromUtf8(":/teamimg/Userr.png")));
        label_28->setScaledContents(true);
        label_4 = new QLabel(modifyTeam);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(180, 20, 191, 41));
        QFont font;
        font.setBold(true);
        label_4->setFont(font);
        label_4->setStyleSheet(QString::fromUtf8("/* Style for the Adjust Team title label */\n"
"QLabel#label_4 {\n"
"    background-color: transparent; /* Dark background matching the app */\n"
"    color: #FFFFFF; /* White text for contrast */\n"
"    font-size: 25px; /* Larger font for title emphasis */\n"
"    font-weight: bold; /* Bold for a strong title appearance */\n"
"\n"
"\n"
"    padding: 5px 10px; /* Padding for a balanced look */\n"
"}"));

        retranslateUi(modifyTeam);

        QMetaObject::connectSlotsByName(modifyTeam);
    } // setupUi

    void retranslateUi(QWidget *modifyTeam)
    {
        modifyTeam->setWindowTitle(QCoreApplication::translate("modifyTeam", "Form", nullptr));
        button1_2->setText(QCoreApplication::translate("modifyTeam", "Confirm", nullptr));
        cb_2->setItemText(0, QCoreApplication::translate("modifyTeam", "bernabeu", nullptr));
        cb_2->setItemText(1, QCoreApplication::translate("modifyTeam", "Santiago Bernab\303\251u", nullptr));
        cb_2->setItemText(2, QCoreApplication::translate("modifyTeam", "Camp Nou", nullptr));
        cb_2->setItemText(3, QCoreApplication::translate("modifyTeam", "Old Trafford", nullptr));
        cb_2->setItemText(4, QCoreApplication::translate("modifyTeam", "Wembley Stadium", nullptr));

        label_12->setText(QCoreApplication::translate("modifyTeam", "         Team_Logo :", nullptr));
        l1_2->setText(QString());
        label_13->setText(QCoreApplication::translate("modifyTeam", "         Budget :", nullptr));
        label_14->setText(QCoreApplication::translate("modifyTeam", "        Team_ABV :", nullptr));
        label_15->setText(QCoreApplication::translate("modifyTeam", "          Team_Name :", nullptr));
        label_16->setText(QCoreApplication::translate("modifyTeam", "         Home_Stadium :", nullptr));
        toolButton_2->setText(QCoreApplication::translate("modifyTeam", "...", nullptr));
        label_3->setText(QCoreApplication::translate("modifyTeam", "insert logo here", nullptr));
        label_19->setText(QString());
        label_29->setText(QString());
        label_30->setText(QString());
        label_27->setText(QString());
        label_28->setText(QString());
        label_4->setText(QCoreApplication::translate("modifyTeam", " Modify Team", nullptr));
    } // retranslateUi

};

namespace Ui {
    class modifyTeam: public Ui_modifyTeam {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MODIFYTEAM_H
