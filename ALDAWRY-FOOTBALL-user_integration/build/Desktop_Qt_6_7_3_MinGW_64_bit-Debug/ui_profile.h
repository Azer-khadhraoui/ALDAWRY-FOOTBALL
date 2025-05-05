/********************************************************************************
** Form generated from reading UI file 'profile.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROFILE_H
#define UI_PROFILE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Profile
{
public:
    QWidget *widget;
    QGridLayout *gridLayout;
    QLabel *firstNameLabel;
    QLabel *emailLabel;
    QLabel *emailValue;
    QPushButton *closeButton;
    QLabel *roleLabel;
    QLabel *mobileValue;
    QLabel *roleValue;
    QLabel *mobileLabel;
    QLabel *firstNameValue;
    QLabel *lastNameValue;
    QLabel *dobLabel;
    QLabel *lastNameLabel;
    QLabel *dobValue;
    QLabel *titleLabel;
    QLabel *iconLastName;
    QLabel *iconFirstName;
    QLabel *iconDob;
    QLabel *iconPhoto;
    QLabel *iconRole;

    void setupUi(QWidget *Profile)
    {
        if (Profile->objectName().isEmpty())
            Profile->setObjectName("Profile");
        Profile->resize(581, 896);
        Profile->setStyleSheet(QString::fromUtf8("background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 #1b1f2a, stop:1 #10131a);"));
        widget = new QWidget(Profile);
        widget->setObjectName("widget");
        widget->setGeometry(QRect(10, 80, 551, 631));
        widget->setStyleSheet(QString::fromUtf8("background-color: rgb(25, 31, 42);\n"
"    color: #FFFFFF;\n"
"    font-family: 'Segoe UI', Arial, sans-serif;\n"
"    font-size: 12px;\n"
"    border-radius: 15px;\n"
"    padding: 15px;\n"
"    spacing: 2px;"));
        gridLayout = new QGridLayout(widget);
        gridLayout->setObjectName("gridLayout");
        firstNameLabel = new QLabel(widget);
        firstNameLabel->setObjectName("firstNameLabel");
        firstNameLabel->setStyleSheet(QString::fromUtf8("color: #A0A8B7;\n"
"font-weight: bold;\n"
"padding-bottom: 5px;\n"
"background-color:transparent;"));

        gridLayout->addWidget(firstNameLabel, 2, 0, 1, 1);

        emailLabel = new QLabel(widget);
        emailLabel->setObjectName("emailLabel");
        emailLabel->setStyleSheet(QString::fromUtf8("color: #A0A8B7;\n"
"font-weight: bold;\n"
"padding-bottom: 5px;\n"
"background-color:transparent;"));

        gridLayout->addWidget(emailLabel, 8, 0, 1, 1);

        emailValue = new QLabel(widget);
        emailValue->setObjectName("emailValue");
        emailValue->setStyleSheet(QString::fromUtf8("background-color: #2A3240;\n"
"    border: 1px solid #3A4A5A;\n"
"    border-radius: 5px;\n"
"    padding: 5px;\n"
"    color: #E0E6ED;\n"
"    margin-left: 15px;\n"
"    margin-right: 15px;"));

        gridLayout->addWidget(emailValue, 9, 0, 1, 1);

        closeButton = new QPushButton(widget);
        closeButton->setObjectName("closeButton");
        closeButton->setStyleSheet(QString::fromUtf8("background-color: #5A626F;\n"
"    color: #FFFFFF;\n"
"    font-size: 12px;\n"
"    font-weight: bold;\n"
"    border-radius: 5px;\n"
"    padding: 6px 12px;\n"
"    margin-left: 350px;\n"
"    margin-right: 20px;\n"
"    margin-bottom: 5px;"));

        gridLayout->addWidget(closeButton, 12, 0, 1, 1);

        roleLabel = new QLabel(widget);
        roleLabel->setObjectName("roleLabel");
        roleLabel->setStyleSheet(QString::fromUtf8("color: #A0A8B7;\n"
"font-weight: bold;\n"
"padding-bottom: 5px;\n"
"background-color:transparent;"));

        gridLayout->addWidget(roleLabel, 10, 0, 1, 1);

        mobileValue = new QLabel(widget);
        mobileValue->setObjectName("mobileValue");
        mobileValue->setStyleSheet(QString::fromUtf8("background-color: #2A3240;\n"
"    border: 1px solid #3A4A5A;\n"
"    border-radius: 5px;\n"
"    padding: 5px;\n"
"    color: #E0E6ED;\n"
"    margin-left: 15px;\n"
"    margin-right: 15px;"));

        gridLayout->addWidget(mobileValue, 7, 0, 1, 1);

        roleValue = new QLabel(widget);
        roleValue->setObjectName("roleValue");
        roleValue->setStyleSheet(QString::fromUtf8("background-color: #2A3240;\n"
"    border: 1px solid #3A4A5A;\n"
"    border-radius: 5px;\n"
"    padding: 5px;\n"
"    color: #E0E6ED;\n"
"    margin-left: 15px;\n"
"    margin-right: 15px;"));

        gridLayout->addWidget(roleValue, 11, 0, 1, 1);

        mobileLabel = new QLabel(widget);
        mobileLabel->setObjectName("mobileLabel");
        mobileLabel->setStyleSheet(QString::fromUtf8("color: #A0A8B7;\n"
"font-weight: bold;\n"
"padding-bottom: 5px;\n"
"background-color:transparent;"));

        gridLayout->addWidget(mobileLabel, 6, 0, 1, 1);

        firstNameValue = new QLabel(widget);
        firstNameValue->setObjectName("firstNameValue");
        firstNameValue->setStyleSheet(QString::fromUtf8("background-color: #2A3240;\n"
"    border: 1px solid #3A4A5A;\n"
"    border-radius: 5px;\n"
"    padding: 5px;\n"
"    color: #E0E6ED;\n"
"    margin-left: 15px;\n"
"    margin-right: 15px;"));

        gridLayout->addWidget(firstNameValue, 3, 0, 1, 1);

        lastNameValue = new QLabel(widget);
        lastNameValue->setObjectName("lastNameValue");
        lastNameValue->setStyleSheet(QString::fromUtf8("background-color: #2A3240;\n"
"    border: 1px solid #3A4A5A;\n"
"    border-radius: 5px;\n"
"    padding: 5px;\n"
"    color: #E0E6ED;\n"
"    margin-left: 15px;\n"
"    margin-right: 15px;"));

        gridLayout->addWidget(lastNameValue, 1, 0, 1, 1);

        dobLabel = new QLabel(widget);
        dobLabel->setObjectName("dobLabel");
        dobLabel->setStyleSheet(QString::fromUtf8("color: #A0A8B7;\n"
"font-weight: bold;\n"
"padding-bottom: 5px;\n"
"background-color:transparent;"));

        gridLayout->addWidget(dobLabel, 4, 0, 1, 1);

        lastNameLabel = new QLabel(widget);
        lastNameLabel->setObjectName("lastNameLabel");
        lastNameLabel->setStyleSheet(QString::fromUtf8("color: #A0A8B7;\n"
"font-weight: bold;\n"
"padding-bottom: 5px;\n"
"background-color:transparent;"));

        gridLayout->addWidget(lastNameLabel, 0, 0, 1, 1);

        dobValue = new QLabel(widget);
        dobValue->setObjectName("dobValue");
        dobValue->setStyleSheet(QString::fromUtf8("background-color: #2A3240;\n"
"    border: 1px solid #3A4A5A;\n"
"    border-radius: 5px;\n"
"    padding: 5px;\n"
"    color: #E0E6ED;\n"
"    margin-left: 15px;\n"
"    margin-right: 15px;"));

        gridLayout->addWidget(dobValue, 5, 0, 1, 1);

        titleLabel = new QLabel(Profile);
        titleLabel->setObjectName("titleLabel");
        titleLabel->setGeometry(QRect(210, 20, 171, 41));
        QFont font;
        font.setBold(true);
        titleLabel->setFont(font);
        titleLabel->setStyleSheet(QString::fromUtf8("background-color: transparent;\n"
"    color: #FFFFFF;\n"
"    font-size: 25px;\n"
"    font-weight: bold;\n"
"    padding: 5px 10px;"));
        iconLastName = new QLabel(Profile);
        iconLastName->setObjectName("iconLastName");
        iconLastName->setGeometry(QRect(60, 100, 17, 17));
        iconLastName->setStyleSheet(QString::fromUtf8("color: #B0C0D0;background-color:transparent;"));
        iconLastName->setPixmap(QPixmap(QString::fromUtf8(":/img/Userr.png")));
        iconLastName->setScaledContents(true);
        iconFirstName = new QLabel(Profile);
        iconFirstName->setObjectName("iconFirstName");
        iconFirstName->setGeometry(QRect(60, 180, 17, 17));
        iconFirstName->setStyleSheet(QString::fromUtf8("color: #B0C0D0;background-color:transparent;"));
        iconFirstName->setPixmap(QPixmap(QString::fromUtf8(":/img/Userr.png")));
        iconFirstName->setScaledContents(true);
        iconDob = new QLabel(Profile);
        iconDob->setObjectName("iconDob");
        iconDob->setGeometry(QRect(60, 221, 17, 17));
        iconDob->setStyleSheet(QString::fromUtf8("color: #B0C0D0;background-color:transparent;"));
        iconDob->setPixmap(QPixmap(QString::fromUtf8(":/img/StartDate.png")));
        iconDob->setScaledContents(true);
        iconPhoto = new QLabel(Profile);
        iconPhoto->setObjectName("iconPhoto");
        iconPhoto->setGeometry(QRect(59, 321, 21, 17));
        iconPhoto->setStyleSheet(QString::fromUtf8("color: #B0C0D0;background-color:transparent;"));
        iconPhoto->setPixmap(QPixmap(QString::fromUtf8(":/img/cam.png")));
        iconPhoto->setScaledContents(true);
        iconRole = new QLabel(Profile);
        iconRole->setObjectName("iconRole");
        iconRole->setGeometry(QRect(60, 421, 17, 17));
        iconRole->setStyleSheet(QString::fromUtf8("color: #B0C0D0;background-color:transparent;"));
        iconRole->setPixmap(QPixmap(QString::fromUtf8(":/img/compType.png")));
        iconRole->setScaledContents(true);

        retranslateUi(Profile);

        QMetaObject::connectSlotsByName(Profile);
    } // setupUi

    void retranslateUi(QWidget *Profile)
    {
        Profile->setWindowTitle(QCoreApplication::translate("Profile", "User Profile", nullptr));
        firstNameLabel->setText(QCoreApplication::translate("Profile", "               First Name :", nullptr));
        emailLabel->setText(QCoreApplication::translate("Profile", "               Email :", nullptr));
        emailValue->setText(QString());
        closeButton->setText(QCoreApplication::translate("Profile", "Close", nullptr));
        roleLabel->setText(QCoreApplication::translate("Profile", "               Role :", nullptr));
        mobileValue->setText(QString());
        roleValue->setText(QString());
        mobileLabel->setText(QCoreApplication::translate("Profile", "               Mobile Number :", nullptr));
        firstNameValue->setText(QString());
        lastNameValue->setText(QString());
        dobLabel->setText(QCoreApplication::translate("Profile", "               Date of Birth :", nullptr));
        lastNameLabel->setText(QCoreApplication::translate("Profile", "               Last Name :", nullptr));
        dobValue->setText(QString());
        titleLabel->setText(QCoreApplication::translate("Profile", "User Profile", nullptr));
        iconLastName->setText(QString());
        iconFirstName->setText(QString());
        iconDob->setText(QString());
        iconPhoto->setText(QString());
        iconRole->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class Profile: public Ui_Profile {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROFILE_H
