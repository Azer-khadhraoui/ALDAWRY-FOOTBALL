/********************************************************************************
** Form generated from reading UI file 'modifyUser.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MODIFYUSER_H
#define UI_MODIFYUSER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Form
{
public:
    QWidget *widget;
    QGridLayout *gridLayout_3;
    QLabel *label_8;
    QLineEdit *lineEdit_3;
    QComboBox *comboBox_3;
    QLineEdit *lineEdit_6;
    QLabel *label_4;
    QLabel *label_3;
    QLineEdit *lineEdit_7;
    QPushButton *modifyUploadPhotoButton;
    QLabel *label_5;
    QPushButton *pushButton_2;
    QLineEdit *lineEdit_8;
    QLabel *label_6;
    QLabel *label_10;
    QDateEdit *dateEdit;
    QLabel *label_7;
    QLineEdit *lineEdit_4;
    QLabel *label_9;
    QLabel *label_11;
    QLabel *label_28;
    QLabel *label_29;
    QLabel *label_30;
    QLabel *label_31;
    QLabel *label_32;
    QLabel *label_33;
    QLabel *label_34;
    QLabel *label_35;

    void setupUi(QWidget *Form)
    {
        if (Form->objectName().isEmpty())
            Form->setObjectName("Form");
        Form->resize(581, 782);
        Form->setStyleSheet(QString::fromUtf8("background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 #1b1f2a, stop:1 #10131a);"));
        widget = new QWidget(Form);
        widget->setObjectName("widget");
        widget->setGeometry(QRect(30, 80, 521, 671));
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
        label_8 = new QLabel(widget);
        label_8->setObjectName("label_8");
        label_8->setStyleSheet(QString::fromUtf8("color: #A0A8B7;\n"
"font-weight: bold;\n"
"padding-bottom: 5px;background-color:transparent;"));

        gridLayout_3->addWidget(label_8, 4, 0, 1, 1);

        lineEdit_3 = new QLineEdit(widget);
        lineEdit_3->setObjectName("lineEdit_3");
        lineEdit_3->setStyleSheet(QString::fromUtf8("background-color: #2A3240; /* Darker blue-gray for input fields */\n"
"    border: 1px solid #3A4A5A; /* Subtle blue-gray border */\n"
"    border-radius: 5px;\n"
"    padding: 5px;\n"
"    color: #E0E6ED; /* Light gray text for readability */\n"
"    margin-left: 15px;\n"
"    margin-right: 15px;\n"
""));

        gridLayout_3->addWidget(lineEdit_3, 1, 0, 1, 1);

        comboBox_3 = new QComboBox(widget);
        comboBox_3->addItem(QString());
        comboBox_3->addItem(QString());
        comboBox_3->addItem(QString());
        comboBox_3->setObjectName("comboBox_3");
        comboBox_3->setStyleSheet(QString::fromUtf8("QComboBox#comboBox_3{\n"
"background-color: #2A3240;\n"
"  border: 1px solid #3A4A5A;\n"
"    border-radius: 5px;\n"
"    padding: 5px;\n"
"    color: #E0E6ED;\n"
"    margin-left: 15px;\n"
"    margin-right: 15px;\n"
"}\n"
"\n"
"QComboBox#ComboBox_3::focus {\n"
"    border: 1px solid #00FF7F;\n"
"    background-color: #323A48;\n"
"}"));

        gridLayout_3->addWidget(comboBox_3, 19, 0, 1, 1);

        lineEdit_6 = new QLineEdit(widget);
        lineEdit_6->setObjectName("lineEdit_6");
        lineEdit_6->setStyleSheet(QString::fromUtf8("background-color: #2A3240; /* Darker blue-gray for input fields */\n"
"    border: 1px solid #3A4A5A; /* Subtle blue-gray border */\n"
"    border-radius: 5px;\n"
"    padding: 5px;\n"
"    color: #E0E6ED; /* Light gray text for readability */\n"
"    margin-left: 15px;\n"
"    margin-right: 15px;\n"
""));

        gridLayout_3->addWidget(lineEdit_6, 13, 0, 1, 1);

        label_4 = new QLabel(widget);
        label_4->setObjectName("label_4");
        label_4->setStyleSheet(QString::fromUtf8("color: #A0A8B7;\n"
"font-weight: bold;\n"
"padding-bottom: 5px;background-color:transparent;"));

        gridLayout_3->addWidget(label_4, 2, 0, 1, 1);

        label_3 = new QLabel(widget);
        label_3->setObjectName("label_3");
        label_3->setStyleSheet(QString::fromUtf8("color: #A0A8B7;\n"
"font-weight: bold;\n"
"padding-bottom: 5px;background-color:transparent;"));

        gridLayout_3->addWidget(label_3, 0, 0, 1, 1);

        lineEdit_7 = new QLineEdit(widget);
        lineEdit_7->setObjectName("lineEdit_7");
        lineEdit_7->setStyleSheet(QString::fromUtf8("background-color: #2A3240; /* Darker blue-gray for input fields */\n"
"    border: 1px solid #3A4A5A; /* Subtle blue-gray border */\n"
"    border-radius: 5px;\n"
"    padding: 5px;\n"
"    color: #E0E6ED; /* Light gray text for readability */\n"
"    margin-left: 15px;\n"
"    margin-right: 15px;\n"
""));
        lineEdit_7->setEchoMode(QLineEdit::EchoMode::Password);

        gridLayout_3->addWidget(lineEdit_7, 17, 0, 1, 1);

        modifyUploadPhotoButton = new QPushButton(widget);
        modifyUploadPhotoButton->setObjectName("modifyUploadPhotoButton");
        modifyUploadPhotoButton->setStyleSheet(QString::fromUtf8("background-color: #1C1F2A;\n"
"border: 1px solid #2A2D3A;\n"
"border-radius: 5px;\n"
"padding: 3px;\n"
"color: white;\n"
"margin-left: 15px;\n"
"margin-right:15px;\n"
""));

        gridLayout_3->addWidget(modifyUploadPhotoButton, 9, 0, 1, 1);

        label_5 = new QLabel(widget);
        label_5->setObjectName("label_5");
        label_5->setStyleSheet(QString::fromUtf8("color: #A0A8B7;\n"
"font-weight: bold;\n"
"padding-bottom: 5px;background-color:transparent;"));

        gridLayout_3->addWidget(label_5, 12, 0, 1, 1);

        pushButton_2 = new QPushButton(widget);
        pushButton_2->setObjectName("pushButton_2");
        pushButton_2->setStyleSheet(QString::fromUtf8("background-color: #00FF7F; /* Green to match the accent */\n"
"    color: #1A2633; /* Dark blue text for contrast */\n"
"    font-size: 12px;\n"
"    font-weight: bold;\n"
"    border-radius: 5px;\n"
"    padding: 6px 12px;\n"
"    margin-left: 350px;\n"
"    margin-right: 20px;\n"
"    margin-bottom: 5px;"));

        gridLayout_3->addWidget(pushButton_2, 20, 0, 1, 1);

        lineEdit_8 = new QLineEdit(widget);
        lineEdit_8->setObjectName("lineEdit_8");
        lineEdit_8->setStyleSheet(QString::fromUtf8("background-color: #2A3240; /* Darker blue-gray for input fields */\n"
"    border: 1px solid #3A4A5A; /* Subtle blue-gray border */\n"
"    border-radius: 5px;\n"
"    padding: 5px;\n"
"    color: #E0E6ED; /* Light gray text for readability */\n"
"    margin-left: 15px;\n"
"    margin-right: 15px;\n"
""));

        gridLayout_3->addWidget(lineEdit_8, 7, 0, 1, 1);

        label_6 = new QLabel(widget);
        label_6->setObjectName("label_6");
        label_6->setStyleSheet(QString::fromUtf8("color: #A0A8B7;\n"
"font-weight: bold;\n"
"padding-bottom: 5px;background-color:transparent;"));

        gridLayout_3->addWidget(label_6, 6, 0, 1, 1);

        label_10 = new QLabel(widget);
        label_10->setObjectName("label_10");
        label_10->setStyleSheet(QString::fromUtf8("color: #A0A8B7;\n"
"font-weight: bold;\n"
"padding-bottom: 5px;background-color:transparent;"));

        gridLayout_3->addWidget(label_10, 8, 0, 1, 1);

        dateEdit = new QDateEdit(widget);
        dateEdit->setObjectName("dateEdit");
        dateEdit->setStyleSheet(QString::fromUtf8("QDateEdit#dateEdit{\n"
"background-color: #2A3240;\n"
"  border: 1px solid #3A4A5A;\n"
"    border-radius: 5px;\n"
"    padding: 5px;\n"
"    color: #E0E6ED;\n"
"    margin-left: 15px;\n"
"    margin-right: 15px;\n"
"}\n"
"\n"
"QDateEdit#dateEdit:focus {\n"
"    border: 1px solid #00FF7F;\n"
"    background-color: #323A48;\n"
"}"));
        dateEdit->setCalendarPopup(true);

        gridLayout_3->addWidget(dateEdit, 5, 0, 1, 1);

        label_7 = new QLabel(widget);
        label_7->setObjectName("label_7");
        label_7->setStyleSheet(QString::fromUtf8("color: #A0A8B7;\n"
"font-weight: bold;\n"
"padding-bottom: 5px;background-color:transparent;"));

        gridLayout_3->addWidget(label_7, 16, 0, 1, 1);

        lineEdit_4 = new QLineEdit(widget);
        lineEdit_4->setObjectName("lineEdit_4");
        lineEdit_4->setStyleSheet(QString::fromUtf8("background-color: #2A3240; /* Darker blue-gray for input fields */\n"
"    border: 1px solid #3A4A5A; /* Subtle blue-gray border */\n"
"    border-radius: 5px;\n"
"    padding: 5px;\n"
"    color: #E0E6ED; /* Light gray text for readability */\n"
"    margin-left: 15px;\n"
"    margin-right: 15px;\n"
""));

        gridLayout_3->addWidget(lineEdit_4, 3, 0, 1, 1);

        label_9 = new QLabel(widget);
        label_9->setObjectName("label_9");
        label_9->setStyleSheet(QString::fromUtf8("color: #A0A8B7;\n"
"font-weight: bold;\n"
"padding-bottom: 5px;background-color:transparent;"));

        gridLayout_3->addWidget(label_9, 18, 0, 1, 1);

        label_11 = new QLabel(Form);
        label_11->setObjectName("label_11");
        label_11->setGeometry(QRect(210, 20, 171, 41));
        QFont font;
        font.setBold(true);
        label_11->setFont(font);
        label_11->setStyleSheet(QString::fromUtf8("/* Style for the Adjust Team title label */\n"
"QLabel#label_11 {\n"
"    background-color: transparent; /* Dark background matching the app */\n"
"    color: #FFFFFF; /* White text for contrast */\n"
"    font-size: 25px; /* Larger font for title emphasis */\n"
"    font-weight: bold; /* Bold for a strong title appearance */\n"
"\n"
"\n"
"    padding: 5px 10px; /* Padding for a balanced look */\n"
"}"));
        label_28 = new QLabel(Form);
        label_28->setObjectName("label_28");
        label_28->setGeometry(QRect(60, 100, 17, 17));
        label_28->setStyleSheet(QString::fromUtf8("color: #B0C0D0;background-color:transparent;"));
        label_28->setPixmap(QPixmap(QString::fromUtf8(":/img/Userr.png")));
        label_28->setScaledContents(true);
        label_29 = new QLabel(Form);
        label_29->setObjectName("label_29");
        label_29->setGeometry(QRect(60, 180, 17, 17));
        label_29->setStyleSheet(QString::fromUtf8("color: #B0C0D0;background-color:transparent;"));
        label_29->setPixmap(QPixmap(QString::fromUtf8(":/img/Userr.png")));
        label_29->setScaledContents(true);
        label_30 = new QLabel(Form);
        label_30->setObjectName("label_30");
        label_30->setGeometry(QRect(60, 260, 17, 17));
        label_30->setStyleSheet(QString::fromUtf8("color: #B0C0D0;background-color:transparent;"));
        label_30->setPixmap(QPixmap(QString::fromUtf8(":/img/StartDate.png")));
        label_30->setScaledContents(true);
        label_31 = new QLabel(Form);
        label_31->setObjectName("label_31");
        label_31->setGeometry(QRect(60, 644, 17, 17));
        label_31->setStyleSheet(QString::fromUtf8("color: #B0C0D0;background-color:transparent;"));
        label_31->setPixmap(QPixmap(QString::fromUtf8(":/img/compType.png")));
        label_31->setScaledContents(true);
        label_32 = new QLabel(Form);
        label_32->setObjectName("label_32");
        label_32->setGeometry(QRect(50, 480, 40, 40));
        label_32->setStyleSheet(QString::fromUtf8("color: #B0C0D0;background-color:transparent;"));
        label_32->setPixmap(QPixmap(QString::fromUtf8(":/img/mailIcon.png")));
        label_32->setScaledContents(true);
        label_33 = new QLabel(Form);
        label_33->setObjectName("label_33");
        label_33->setGeometry(QRect(59, 415, 21, 17));
        label_33->setStyleSheet(QString::fromUtf8("color: #B0C0D0;background-color:transparent;"));
        label_33->setPixmap(QPixmap(QString::fromUtf8(":/img/cam.png")));
        label_33->setScaledContents(true);
        label_34 = new QLabel(Form);
        label_34->setObjectName("label_34");
        label_34->setGeometry(QRect(47, 557, 40, 40));
        label_34->setStyleSheet(QString::fromUtf8("color: #B0C0D0;background-color:transparent;"));
        label_34->setPixmap(QPixmap(QString::fromUtf8(":/img/passwordIcon.png")));
        label_34->setScaledContents(true);
        label_35 = new QLabel(Form);
        label_35->setObjectName("label_35");
        label_35->setGeometry(QRect(60, 340, 17, 17));
        label_35->setStyleSheet(QString::fromUtf8("color: #B0C0D0;background-color:transparent;"));
        label_35->setPixmap(QPixmap(QString::fromUtf8(":/img/mobile.png")));
        label_35->setScaledContents(true);

        retranslateUi(Form);

        QMetaObject::connectSlotsByName(Form);
    } // setupUi

    void retranslateUi(QWidget *Form)
    {
        Form->setWindowTitle(QCoreApplication::translate("Form", "Form", nullptr));
        label_8->setText(QCoreApplication::translate("Form", "               Date_of_Birth :", nullptr));
        comboBox_3->setItemText(0, QCoreApplication::translate("Form", "Admin", nullptr));
        comboBox_3->setItemText(1, QCoreApplication::translate("Form", "Employee", nullptr));
        comboBox_3->setItemText(2, QCoreApplication::translate("Form", "Coach", nullptr));

        label_4->setText(QCoreApplication::translate("Form", "               First_Name :", nullptr));
        label_3->setText(QCoreApplication::translate("Form", "               Last_Name :", nullptr));
        modifyUploadPhotoButton->setText(QCoreApplication::translate("Form", "Upload Photo here", nullptr));
        label_5->setText(QCoreApplication::translate("Form", "               Email :", nullptr));
        pushButton_2->setText(QCoreApplication::translate("Form", "Confirm", nullptr));
        label_6->setText(QCoreApplication::translate("Form", "               Mobile_Number :", nullptr));
        label_10->setText(QCoreApplication::translate("Form", "               Profile_Picture :", nullptr));
        label_7->setText(QCoreApplication::translate("Form", "               Password :", nullptr));
        label_9->setText(QCoreApplication::translate("Form", "               Role", nullptr));
        label_11->setText(QCoreApplication::translate("Form", "Modify User", nullptr));
        label_28->setText(QString());
        label_29->setText(QString());
        label_30->setText(QString());
        label_31->setText(QString());
        label_32->setText(QString());
        label_33->setText(QString());
        label_34->setText(QString());
        label_35->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class Form: public Ui_Form {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MODIFYUSER_H
