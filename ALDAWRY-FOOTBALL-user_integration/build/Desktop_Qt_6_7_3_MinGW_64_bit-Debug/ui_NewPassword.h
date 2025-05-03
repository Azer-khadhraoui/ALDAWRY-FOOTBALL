/********************************************************************************
** Form generated from reading UI file 'NewPassword.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NEWPASSWORD_H
#define UI_NEWPASSWORD_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_NewPasswordDialog
{
public:
    QLineEdit *new_password_input;
    QLineEdit *confirm_password_input;
    QWidget *widget;
    QLabel *label_title_5;
    QPushButton *pushButton;
    QLabel *label_title_10;
    QLabel *label_title_11;
    QLabel *label_title_12;
    QPushButton *reset_password_button;
    QLabel *label_title_13;
    QLabel *label_title_14;

    void setupUi(QDialog *NewPassword)
    {
        if (NewPassword->objectName().isEmpty())
            NewPassword->setObjectName("NewPassword");
        NewPassword->resize(450, 451);
        NewPassword->setStyleSheet(QString::fromUtf8("\n"
"background-color: white;"));
        new_password_input = new QLineEdit(NewPassword);
        new_password_input->setObjectName("new_password_input");
        new_password_input->setEnabled(false);
        new_password_input->setGeometry(QRect(56, 160, 300, 41));
        new_password_input->setStyleSheet(QString::fromUtf8("background-color: transparent;\n"
" border: 1px solid grey;\n"
" border-radius: 5px;\n"
" padding: 5px; \n"
"color: black;"));
        new_password_input->setEchoMode(QLineEdit::EchoMode::Password);
        confirm_password_input = new QLineEdit(NewPassword);
        confirm_password_input->setObjectName("confirm_password_input");
        confirm_password_input->setEnabled(false);
        confirm_password_input->setGeometry(QRect(56, 250, 300, 41));
        confirm_password_input->setStyleSheet(QString::fromUtf8("background-color: transparent;\n"
" border: 1px solid grey;\n"
" border-radius: 5px;\n"
" padding: 5px; \n"
"color: black;"));
        confirm_password_input->setEchoMode(QLineEdit::EchoMode::Password);
        widget = new QWidget(NewPassword);
        widget->setObjectName("widget");
        widget->setGeometry(QRect(30, 30, 391, 391));
        widget->setStyleSheet(QString::fromUtf8("background-color: rgb(248, 248, 248);\n"
"border-radius: 10Px;"));
        label_title_5 = new QLabel(widget);
        label_title_5->setObjectName("label_title_5");
        label_title_5->setGeometry(QRect(-10, 350, 351, 41));
        QFont font;
        font.setPointSize(9);
        font.setBold(false);
        label_title_5->setFont(font);
        label_title_5->setStyleSheet(QString::fromUtf8("background-color: transparent; color: grey;"));
        label_title_5->setAlignment(Qt::AlignmentFlag::AlignCenter);
        pushButton = new QPushButton(widget);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(210, 360, 80, 24));
        QFont font1;
        font1.setUnderline(true);
        pushButton->setFont(font1);
        pushButton->setStyleSheet(QString::fromUtf8("background-color: transparent;\n"
"color : blue;"));
        label_title_10 = new QLabel(widget);
        label_title_10->setObjectName("label_title_10");
        label_title_10->setGeometry(QRect(27, 20, 281, 41));
        QFont font2;
        font2.setPointSize(20);
        font2.setBold(true);
        label_title_10->setFont(font2);
        label_title_10->setStyleSheet(QString::fromUtf8("background-color: transparent; color: black;"));
        label_title_10->setAlignment(Qt::AlignmentFlag::AlignCenter);
        label_title_11 = new QLabel(widget);
        label_title_11->setObjectName("label_title_11");
        label_title_11->setGeometry(QRect(-5, 50, 351, 41));
        label_title_11->setFont(font);
        label_title_11->setStyleSheet(QString::fromUtf8("background-color: transparent; color: grey;"));
        label_title_11->setAlignment(Qt::AlignmentFlag::AlignCenter);
        label_title_12 = new QLabel(widget);
        label_title_12->setObjectName("label_title_12");
        label_title_12->setGeometry(QRect(-96, 70, 351, 41));
        label_title_12->setFont(font);
        label_title_12->setStyleSheet(QString::fromUtf8("background-color: transparent; color: grey;"));
        label_title_12->setAlignment(Qt::AlignmentFlag::AlignCenter);
        reset_password_button = new QPushButton(widget);
        reset_password_button->setObjectName("reset_password_button");
        reset_password_button->setEnabled(false);
        reset_password_button->setGeometry(QRect(20, 290, 351, 41));
        reset_password_button->setStyleSheet(QString::fromUtf8("background-color: #0078d7; color: white; border-radius: 5px; font-weight: bold;"));
        label_title_13 = new QLabel(widget);
        label_title_13->setObjectName("label_title_13");
        label_title_13->setGeometry(QRect(-110, 100, 351, 41));
        QFont font3;
        font3.setPointSize(9);
        font3.setBold(true);
        label_title_13->setFont(font3);
        label_title_13->setStyleSheet(QString::fromUtf8("background-color: transparent; color: grey;"));
        label_title_13->setAlignment(Qt::AlignmentFlag::AlignCenter);
        label_title_14 = new QLabel(widget);
        label_title_14->setObjectName("label_title_14");
        label_title_14->setGeometry(QRect(-103, 190, 351, 41));
        label_title_14->setFont(font3);
        label_title_14->setStyleSheet(QString::fromUtf8("background-color: transparent; color: grey;"));
        label_title_14->setAlignment(Qt::AlignmentFlag::AlignCenter);
        widget->raise();
        new_password_input->raise();
        confirm_password_input->raise();

        retranslateUi(NewPassword);

        QMetaObject::connectSlotsByName(NewPassword);
    } // setupUi

    void retranslateUi(QDialog *NewPassword)
    {
        NewPassword->setWindowTitle(QCoreApplication::translate("NewPasswordDialog", "Recover Password", nullptr));
        new_password_input->setPlaceholderText(QCoreApplication::translate("NewPasswordDialog", "Enter Password", nullptr));
        confirm_password_input->setPlaceholderText(QCoreApplication::translate("NewPasswordDialog", "Re-enter Password", nullptr));
        label_title_5->setText(QCoreApplication::translate("NewPasswordDialog", "Remember Password?", nullptr));
        pushButton->setText(QCoreApplication::translate("NewPasswordDialog", "Login", nullptr));
        label_title_10->setText(QCoreApplication::translate("NewPasswordDialog", "Create New Password", nullptr));
        label_title_11->setText(QCoreApplication::translate("NewPasswordDialog", "Your new password must be different from any of your ", nullptr));
        label_title_12->setText(QCoreApplication::translate("NewPasswordDialog", "previous passwords.", nullptr));
        reset_password_button->setText(QCoreApplication::translate("NewPasswordDialog", "Reset Password", nullptr));
        label_title_13->setText(QCoreApplication::translate("NewPasswordDialog", "New Password", nullptr));
        label_title_14->setText(QCoreApplication::translate("NewPasswordDialog", "Confirm Password", nullptr));
    } // retranslateUi

};

namespace Ui {
    class NewPasswordDialog: public Ui_NewPasswordDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NEWPASSWORD_H
