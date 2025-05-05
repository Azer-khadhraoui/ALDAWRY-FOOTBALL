/********************************************************************************
** Form generated from reading UI file 'formadd.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FORMADD_H
#define UI_FORMADD_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
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

class Ui_FormAdd
{
public:
    QWidget *widget;
    QGridLayout *gridLayout_3;
    QLabel *label_7;
    QLineEdit *l2;
    QLabel *label_8;
    QLineEdit *l2_2;
    QLabel *label_11;
    QPushButton *button1;
    QLineEdit *l1;
    QComboBox *cb;
    QLabel *label_10;
    QWidget *widget_2;
    QHBoxLayout *horizontalLayout;
    QToolButton *toolButton;
    QLabel *label_2;
    QLabel *label_9;
    QLabel *label_28;
    QLabel *label_27;
    QLabel *label_19;
    QLabel *label_29;
    QLabel *label_30;
    QPushButton *resetButton;
    QLabel *label_4;

    void setupUi(QWidget *FormAdd)
    {
        if (FormAdd->objectName().isEmpty())
            FormAdd->setObjectName("FormAdd");
        FormAdd->resize(605, 635);
        FormAdd->setStyleSheet(QString::fromUtf8("background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 #1b1f2a, stop:1 #10131a);"));
        widget = new QWidget(FormAdd);
        widget->setObjectName("widget");
        widget->setGeometry(QRect(30, 90, 541, 521));
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
        label_7 = new QLabel(widget);
        label_7->setObjectName("label_7");
        label_7->setStyleSheet(QString::fromUtf8("color: #A0A8B7;\n"
"font-weight: bold;\n"
"padding-bottom: 5px;background-color:transparent;"));

        gridLayout_3->addWidget(label_7, 0, 0, 1, 1);

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

        label_8 = new QLabel(widget);
        label_8->setObjectName("label_8");
        label_8->setStyleSheet(QString::fromUtf8("color: #A0A8B7;\n"
"font-weight: bold;\n"
"padding-bottom: 5px;background-color:transparent;"));

        gridLayout_3->addWidget(label_8, 2, 0, 1, 1);

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

        label_11 = new QLabel(widget);
        label_11->setObjectName("label_11");
        label_11->setStyleSheet(QString::fromUtf8("color: #A0A8B7;\n"
"font-weight: bold;\n"
"padding-bottom: 5px;background-color:transparent;"));

        gridLayout_3->addWidget(label_11, 8, 0, 1, 1);

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

        widget_2 = new QWidget(widget);
        widget_2->setObjectName("widget_2");
        widget_2->setStyleSheet(QString::fromUtf8("background-color: #2A3240;\n"
"    border: 1px solid #3A4A5A;\n"
"    border-radius: 5px;\n"
"    padding: 3px;\n"
"    color: #E0E6ED;\n"
"    margin-left: 15px;\n"
"    margin-right: 15px;\n"
"    margin-bottom: 15px;"));
        horizontalLayout = new QHBoxLayout(widget_2);
        horizontalLayout->setObjectName("horizontalLayout");
        toolButton = new QToolButton(widget_2);
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

        label_2 = new QLabel(widget_2);
        label_2->setObjectName("label_2");
        label_2->setStyleSheet(QString::fromUtf8("color: #A0A8B7;\n"
"padding-left: 10px;\n"
"background-color: transparent;"));

        horizontalLayout->addWidget(label_2);


        gridLayout_3->addWidget(widget_2, 7, 0, 1, 1);

        label_9 = new QLabel(widget);
        label_9->setObjectName("label_9");
        label_9->setStyleSheet(QString::fromUtf8("color: #A0A8B7;\n"
"font-weight: bold;\n"
"padding-bottom: 5px;background-color:transparent;"));

        gridLayout_3->addWidget(label_9, 4, 0, 1, 1);

        label_28 = new QLabel(FormAdd);
        label_28->setObjectName("label_28");
        label_28->setGeometry(QRect(60, 120, 17, 17));
        label_28->setStyleSheet(QString::fromUtf8("color: #B0C0D0;background-color:transparent;"));
        label_28->setPixmap(QPixmap(QString::fromUtf8(":/teamimg/Userr.png")));
        label_28->setScaledContents(true);
        label_27 = new QLabel(FormAdd);
        label_27->setObjectName("label_27");
        label_27->setGeometry(QRect(60, 300, 12, 18));
        label_27->setStyleSheet(QString::fromUtf8("background-color:transparent;"));
        label_27->setPixmap(QPixmap(QString::fromUtf8(":/teamimg/money.png")));
        label_27->setScaledContents(true);
        label_19 = new QLabel(FormAdd);
        label_19->setObjectName("label_19");
        label_19->setGeometry(QRect(60, 210, 17, 17));
        label_19->setStyleSheet(QString::fromUtf8("background-color:transparent;"));
        label_19->setPixmap(QPixmap(QString::fromUtf8(":/teamimg/terrain.png")));
        label_19->setScaledContents(true);
        label_29 = new QLabel(FormAdd);
        label_29->setObjectName("label_29");
        label_29->setGeometry(QRect(60, 380, 21, 21));
        label_29->setStyleSheet(QString::fromUtf8("background-color:transparent;"));
        label_29->setPixmap(QPixmap(QString::fromUtf8(":/teamimg/logo.png")));
        label_29->setScaledContents(true);
        label_30 = new QLabel(FormAdd);
        label_30->setObjectName("label_30");
        label_30->setGeometry(QRect(60, 500, 18, 16));
        label_30->setStyleSheet(QString::fromUtf8("background-color:transparent;"));
        label_30->setPixmap(QPixmap(QString::fromUtf8(":/teamimg/abv.png")));
        label_30->setScaledContents(true);
        resetButton = new QPushButton(FormAdd);
        resetButton->setObjectName("resetButton");
        resetButton->setGeometry(QRect(350, 570, 31, 24));
        resetButton->setStyleSheet(QString::fromUtf8("background-color: rgb(132, 132, 132);\n"
"       color: white;            \n"
"        font-family: Arial;      \n"
"        font-size: 12px;        \n"
"       font-weight: bold;      \n"
"        border: 1px solid grey ;\n"
"        border-radius: 5px;      \n"
"        padding: 5px 10px;        \n"
"    \n"
""));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/teamimg/reset.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        resetButton->setIcon(icon);
        label_4 = new QLabel(FormAdd);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(240, 20, 151, 41));
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

        retranslateUi(FormAdd);

        QMetaObject::connectSlotsByName(FormAdd);
    } // setupUi

    void retranslateUi(QWidget *FormAdd)
    {
        FormAdd->setWindowTitle(QCoreApplication::translate("FormAdd", "Form", nullptr));
        label_7->setText(QCoreApplication::translate("FormAdd", "            Team_Name :", nullptr));
        label_8->setText(QCoreApplication::translate("FormAdd", "           Home_Stadium :", nullptr));
        label_11->setText(QCoreApplication::translate("FormAdd", "           Team_ABV :", nullptr));
        button1->setText(QCoreApplication::translate("FormAdd", "Confirm", nullptr));
        l1->setText(QString());
        cb->setItemText(0, QCoreApplication::translate("FormAdd", "bernabeu", nullptr));
        cb->setItemText(1, QCoreApplication::translate("FormAdd", "Santiago Bernab\303\251u", nullptr));
        cb->setItemText(2, QCoreApplication::translate("FormAdd", "Camp Nou", nullptr));
        cb->setItemText(3, QCoreApplication::translate("FormAdd", "Old Trafford", nullptr));
        cb->setItemText(4, QCoreApplication::translate("FormAdd", "Wembley Stadium", nullptr));

        label_10->setText(QCoreApplication::translate("FormAdd", "            Team_Logo :", nullptr));
        toolButton->setText(QCoreApplication::translate("FormAdd", "...", nullptr));
        label_2->setText(QCoreApplication::translate("FormAdd", "insert logo here", nullptr));
        label_9->setText(QCoreApplication::translate("FormAdd", "           Budget :", nullptr));
        label_28->setText(QString());
        label_27->setText(QString());
        label_19->setText(QString());
        label_29->setText(QString());
        label_30->setText(QString());
        resetButton->setText(QString());
        label_4->setText(QCoreApplication::translate("FormAdd", "Add Team", nullptr));
    } // retranslateUi

};

namespace Ui {
    class FormAdd: public Ui_FormAdd {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORMADD_H
