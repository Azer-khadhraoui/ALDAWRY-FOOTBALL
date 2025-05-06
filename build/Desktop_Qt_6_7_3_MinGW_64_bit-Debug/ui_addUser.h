/********************************************************************************
** Form generated from reading UI file 'addUser.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDUSER_H
#define UI_ADDUSER_H

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

class Ui_AddUser
{
public:
    QWidget *widget;
    QGridLayout *gridLayout_3;
    QLabel *label_8;
    QLineEdit *nom;
    QComboBox *Role;
    QLineEdit *email;
    QLabel *label_4;
    QLabel *label_3;
    QLineEdit *password;
    QPushButton *uploadPhotoButton;
    QLabel *label_5;
    QPushButton *button1;
    QLineEdit *number;
    QLabel *label_6;
    QLabel *label_10;
    QDateEdit *birthday;
    QLabel *label_7;
    QLineEdit *prenom;
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

    void setupUi(QWidget *AddUser)
    {
        if (AddUser->objectName().isEmpty())
            AddUser->setObjectName("AddUser");
        AddUser->resize(581, 782);
        AddUser->setStyleSheet(QString::fromUtf8("background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 #1b1f2a, stop:1 #10131a);"));
        widget = new QWidget(AddUser);
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

        nom = new QLineEdit(widget);
        nom->setObjectName("nom");
        nom->setStyleSheet(QString::fromUtf8("background-color: #2A3240; /* Darker blue-gray for input fields */\n"
"    border: 1px solid #3A4A5A; /* Subtle blue-gray border */\n"
"    border-radius: 5px;\n"
"    padding: 5px;\n"
"    color: #E0E6ED; /* Light gray text for readability */\n"
"    margin-left: 15px;\n"
"    margin-right: 15px;\n"
""));

        gridLayout_3->addWidget(nom, 1, 0, 1, 1);

        Role = new QComboBox(widget);
        Role->addItem(QString());
        Role->addItem(QString());
        Role->addItem(QString());
        Role->setObjectName("Role");
        Role->setStyleSheet(QString::fromUtf8("QComboBox#Role{\n"
"background-color: #2A3240;\n"
"  border: 1px solid #3A4A5A;\n"
"    border-radius: 5px;\n"
"    padding: 5px;\n"
"    color: #E0E6ED;\n"
"    margin-left: 15px;\n"
"    margin-right: 15px;\n"
"}\n"
"\n"
"QComboBox#Role::focus {\n"
"    border: 1px solid #00FF7F;\n"
"    background-color: #323A48;\n"
"}"));

        gridLayout_3->addWidget(Role, 19, 0, 1, 1);

        email = new QLineEdit(widget);
        email->setObjectName("email");
        email->setStyleSheet(QString::fromUtf8("background-color: #2A3240; /* Darker blue-gray for input fields */\n"
"    border: 1px solid #3A4A5A; /* Subtle blue-gray border */\n"
"    border-radius: 5px;\n"
"    padding: 5px;\n"
"    color: #E0E6ED; /* Light gray text for readability */\n"
"    margin-left: 15px;\n"
"    margin-right: 15px;\n"
""));

        gridLayout_3->addWidget(email, 13, 0, 1, 1);

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

        password = new QLineEdit(widget);
        password->setObjectName("password");
        password->setStyleSheet(QString::fromUtf8("background-color: #2A3240; /* Darker blue-gray for input fields */\n"
"    border: 1px solid #3A4A5A; /* Subtle blue-gray border */\n"
"    border-radius: 5px;\n"
"    padding: 5px;\n"
"    color: #E0E6ED; /* Light gray text for readability */\n"
"    margin-left: 15px;\n"
"    margin-right: 15px;\n"
""));
        password->setEchoMode(QLineEdit::EchoMode::Password);

        gridLayout_3->addWidget(password, 17, 0, 1, 1);

        uploadPhotoButton = new QPushButton(widget);
        uploadPhotoButton->setObjectName("uploadPhotoButton");
        uploadPhotoButton->setStyleSheet(QString::fromUtf8("background-color: #1C1F2A;\n"
"border: 1px solid #2A2D3A;\n"
"border-radius: 5px;\n"
"padding: 3px;\n"
"color: white;\n"
"margin-left: 15px;\n"
"margin-right:15px;\n"
""));

        gridLayout_3->addWidget(uploadPhotoButton, 9, 0, 1, 1);

        label_5 = new QLabel(widget);
        label_5->setObjectName("label_5");
        label_5->setStyleSheet(QString::fromUtf8("color: #A0A8B7;\n"
"font-weight: bold;\n"
"padding-bottom: 5px;background-color:transparent;"));

        gridLayout_3->addWidget(label_5, 12, 0, 1, 1);

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

        gridLayout_3->addWidget(button1, 20, 0, 1, 1);

        number = new QLineEdit(widget);
        number->setObjectName("number");
        number->setStyleSheet(QString::fromUtf8("background-color: #2A3240; /* Darker blue-gray for input fields */\n"
"    border: 1px solid #3A4A5A; /* Subtle blue-gray border */\n"
"    border-radius: 5px;\n"
"    padding: 5px;\n"
"    color: #E0E6ED; /* Light gray text for readability */\n"
"    margin-left: 15px;\n"
"    margin-right: 15px;\n"
""));

        gridLayout_3->addWidget(number, 7, 0, 1, 1);

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

        birthday = new QDateEdit(widget);
        birthday->setObjectName("birthday");
        birthday->setStyleSheet(QString::fromUtf8("QDateEdit#birthday{\n"
"background-color: #2A3240;\n"
"  border: 1px solid #3A4A5A;\n"
"    border-radius: 5px;\n"
"    padding: 5px;\n"
"    color: #E0E6ED;\n"
"    margin-left: 15px;\n"
"    margin-right: 15px;\n"
"}\n"
"\n"
"QDateEdit#birthday:focus {\n"
"    border: 1px solid #00FF7F;\n"
"    background-color: #323A48;\n"
"}"));
        birthday->setCalendarPopup(true);

        gridLayout_3->addWidget(birthday, 5, 0, 1, 1);

        label_7 = new QLabel(widget);
        label_7->setObjectName("label_7");
        label_7->setStyleSheet(QString::fromUtf8("color: #A0A8B7;\n"
"font-weight: bold;\n"
"padding-bottom: 5px;background-color:transparent;"));

        gridLayout_3->addWidget(label_7, 16, 0, 1, 1);

        prenom = new QLineEdit(widget);
        prenom->setObjectName("prenom");
        prenom->setStyleSheet(QString::fromUtf8("background-color: #2A3240; /* Darker blue-gray for input fields */\n"
"    border: 1px solid #3A4A5A; /* Subtle blue-gray border */\n"
"    border-radius: 5px;\n"
"    padding: 5px;\n"
"    color: #E0E6ED; /* Light gray text for readability */\n"
"    margin-left: 15px;\n"
"    margin-right: 15px;\n"
""));

        gridLayout_3->addWidget(prenom, 3, 0, 1, 1);

        label_9 = new QLabel(widget);
        label_9->setObjectName("label_9");
        label_9->setStyleSheet(QString::fromUtf8("color: #A0A8B7;\n"
"font-weight: bold;\n"
"padding-bottom: 5px;background-color:transparent;"));

        gridLayout_3->addWidget(label_9, 18, 0, 1, 1);

        label_11 = new QLabel(AddUser);
        label_11->setObjectName("label_11");
        label_11->setGeometry(QRect(220, 20, 151, 41));
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
        label_28 = new QLabel(AddUser);
        label_28->setObjectName("label_28");
        label_28->setGeometry(QRect(60, 100, 17, 17));
        label_28->setStyleSheet(QString::fromUtf8("color: #B0C0D0;background-color:transparent;"));
        label_28->setPixmap(QPixmap(QString::fromUtf8(":/teamimg/Userr.png")));
        label_28->setScaledContents(true);
        label_29 = new QLabel(AddUser);
        label_29->setObjectName("label_29");
        label_29->setGeometry(QRect(60, 180, 17, 17));
        label_29->setStyleSheet(QString::fromUtf8("color: #B0C0D0;background-color:transparent;"));
        label_29->setPixmap(QPixmap(QString::fromUtf8(":/teamimg/Userr.png")));
        label_29->setScaledContents(true);
        label_30 = new QLabel(AddUser);
        label_30->setObjectName("label_30");
        label_30->setGeometry(QRect(60, 260, 17, 17));
        label_30->setStyleSheet(QString::fromUtf8("color: #B0C0D0;background-color:transparent;"));
        label_30->setPixmap(QPixmap(QString::fromUtf8(":/compimg/StartDate.png")));
        label_30->setScaledContents(true);
        label_31 = new QLabel(AddUser);
        label_31->setObjectName("label_31");
        label_31->setGeometry(QRect(60, 644, 17, 17));
        label_31->setStyleSheet(QString::fromUtf8("color: #B0C0D0;background-color:transparent;"));
        label_31->setPixmap(QPixmap(QString::fromUtf8(":/playerimg/compType.png")));
        label_31->setScaledContents(true);
        label_32 = new QLabel(AddUser);
        label_32->setObjectName("label_32");
        label_32->setGeometry(QRect(50, 480, 40, 40));
        label_32->setStyleSheet(QString::fromUtf8("color: #B0C0D0;background-color:transparent;"));
        label_32->setPixmap(QPixmap(QString::fromUtf8(":/img/mailIcon.png")));
        label_32->setScaledContents(true);
        label_33 = new QLabel(AddUser);
        label_33->setObjectName("label_33");
        label_33->setGeometry(QRect(59, 415, 21, 17));
        label_33->setStyleSheet(QString::fromUtf8("color: #B0C0D0;background-color:transparent;"));
        label_33->setPixmap(QPixmap(QString::fromUtf8(":/playerimg/cam.png")));
        label_33->setScaledContents(true);
        label_34 = new QLabel(AddUser);
        label_34->setObjectName("label_34");
        label_34->setGeometry(QRect(47, 557, 40, 40));
        label_34->setStyleSheet(QString::fromUtf8("color: #B0C0D0;background-color:transparent;"));
        label_34->setPixmap(QPixmap(QString::fromUtf8(":/img/passwordIcon.png")));
        label_34->setScaledContents(true);
        label_35 = new QLabel(AddUser);
        label_35->setObjectName("label_35");
        label_35->setGeometry(QRect(60, 340, 17, 17));
        label_35->setStyleSheet(QString::fromUtf8("color: #B0C0D0;background-color:transparent;"));
        label_35->setPixmap(QPixmap(QString::fromUtf8(":/img/mobile.png")));
        label_35->setScaledContents(true);

        retranslateUi(AddUser);

        QMetaObject::connectSlotsByName(AddUser);
    } // setupUi

    void retranslateUi(QWidget *AddUser)
    {
        AddUser->setWindowTitle(QCoreApplication::translate("AddUser", "Form", nullptr));
        label_8->setText(QCoreApplication::translate("AddUser", "               Date_of_Birth :", nullptr));
        Role->setItemText(0, QCoreApplication::translate("AddUser", "Admin", nullptr));
        Role->setItemText(1, QCoreApplication::translate("AddUser", "Employee", nullptr));
        Role->setItemText(2, QCoreApplication::translate("AddUser", "Coach", nullptr));

        label_4->setText(QCoreApplication::translate("AddUser", "               First_Name :", nullptr));
        label_3->setText(QCoreApplication::translate("AddUser", "               Last_Name :", nullptr));
        uploadPhotoButton->setText(QCoreApplication::translate("AddUser", "Upload Photo here", nullptr));
        label_5->setText(QCoreApplication::translate("AddUser", "               Email :", nullptr));
        button1->setText(QCoreApplication::translate("AddUser", "Confirm", nullptr));
        label_6->setText(QCoreApplication::translate("AddUser", "               Mobile_Number :", nullptr));
        label_10->setText(QCoreApplication::translate("AddUser", "               Profile_Picture :", nullptr));
        label_7->setText(QCoreApplication::translate("AddUser", "               Password :", nullptr));
        label_9->setText(QCoreApplication::translate("AddUser", "               Role", nullptr));
        label_11->setText(QCoreApplication::translate("AddUser", "Add User", nullptr));
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
    class AddUser: public Ui_AddUser {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDUSER_H
