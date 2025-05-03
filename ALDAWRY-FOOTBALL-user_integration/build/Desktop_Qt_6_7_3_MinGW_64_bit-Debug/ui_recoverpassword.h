/********************************************************************************
** Form generated from reading UI file 'recoverpassword.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RECOVERPASSWORD_H
#define UI_RECOVERPASSWORD_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_RecoverPasswordDialog
{
public:
    QWidget *widget;
    QLabel *label_title_2;
    QLabel *label_title;
    QLabel *label_title_3;
    QPushButton *send_code_button;
    QLabel *label_title_4;
    QLineEdit *email_input;
    QLabel *label_title_5;
    QPushButton *pushButton;
    QLabel *label;

    void setupUi(QDialog *RecoverPasswordDialog)
    {
        if (RecoverPasswordDialog->objectName().isEmpty())
            RecoverPasswordDialog->setObjectName("RecoverPasswordDialog");
        RecoverPasswordDialog->resize(453, 379);
        RecoverPasswordDialog->setStyleSheet(QString::fromUtf8("\n"
"background-color: white;"));
        widget = new QWidget(RecoverPasswordDialog);
        widget->setObjectName("widget");
        widget->setGeometry(QRect(30, 30, 391, 321));
        widget->setStyleSheet(QString::fromUtf8("background-color: rgb(248, 248, 248);\n"
"border-radius: 10Px;"));
        label_title_2 = new QLabel(widget);
        label_title_2->setObjectName("label_title_2");
        label_title_2->setGeometry(QRect(25, 50, 351, 41));
        QFont font;
        font.setPointSize(9);
        font.setBold(false);
        label_title_2->setFont(font);
        label_title_2->setStyleSheet(QString::fromUtf8("background-color: transparent; color: grey;"));
        label_title_2->setAlignment(Qt::AlignmentFlag::AlignCenter);
        label_title = new QLabel(widget);
        label_title->setObjectName("label_title");
        label_title->setGeometry(QRect(20, 20, 231, 41));
        QFont font1;
        font1.setPointSize(20);
        font1.setBold(true);
        label_title->setFont(font1);
        label_title->setStyleSheet(QString::fromUtf8("background-color: transparent; color: black;"));
        label_title->setAlignment(Qt::AlignmentFlag::AlignCenter);
        label_title_3 = new QLabel(widget);
        label_title_3->setObjectName("label_title_3");
        label_title_3->setGeometry(QRect(-30, 70, 351, 41));
        label_title_3->setFont(font);
        label_title_3->setStyleSheet(QString::fromUtf8("background-color: transparent; color: grey;"));
        label_title_3->setAlignment(Qt::AlignmentFlag::AlignCenter);
        send_code_button = new QPushButton(widget);
        send_code_button->setObjectName("send_code_button");
        send_code_button->setGeometry(QRect(20, 220, 351, 41));
        send_code_button->setStyleSheet(QString::fromUtf8("background-color: #0078d7; color: white; border-radius: 10Px; font-weight: bold;"));
        label_title_4 = new QLabel(widget);
        label_title_4->setObjectName("label_title_4");
        label_title_4->setGeometry(QRect(5, 114, 114, 41));
        QFont font2;
        font2.setPointSize(9);
        font2.setBold(true);
        label_title_4->setFont(font2);
        label_title_4->setStyleSheet(QString::fromUtf8("background-color: transparent; color: grey;"));
        label_title_4->setAlignment(Qt::AlignmentFlag::AlignCenter);
        email_input = new QLineEdit(widget);
        email_input->setObjectName("email_input");
        email_input->setGeometry(QRect(25, 150, 341, 41));
        email_input->setStyleSheet(QString::fromUtf8("background-color: transparent;\n"
" border: 1px solid grey;\n"
" border-radius: 5px;\n"
" padding: 5px; \n"
"color: black;"));
        label_title_5 = new QLabel(widget);
        label_title_5->setObjectName("label_title_5");
        label_title_5->setGeometry(QRect(-10, 280, 351, 41));
        label_title_5->setFont(font);
        label_title_5->setStyleSheet(QString::fromUtf8("background-color: transparent; color: grey;"));
        label_title_5->setAlignment(Qt::AlignmentFlag::AlignCenter);
        pushButton = new QPushButton(widget);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(210, 290, 80, 24));
        QFont font3;
        font3.setUnderline(true);
        pushButton->setFont(font3);
        pushButton->setStyleSheet(QString::fromUtf8("background-color: transparent;\n"
"color : blue;"));
        label = new QLabel(RecoverPasswordDialog);
        label->setObjectName("label");
        label->setGeometry(QRect(352, 177, 49, 46));
        label->setStyleSheet(QString::fromUtf8("background-color:transparent;"));
        label->setPixmap(QPixmap(QString::fromUtf8(":/img/mailIcon.png")));
        label->setScaledContents(true);

        retranslateUi(RecoverPasswordDialog);

        QMetaObject::connectSlotsByName(RecoverPasswordDialog);
    } // setupUi

    void retranslateUi(QDialog *RecoverPasswordDialog)
    {
        RecoverPasswordDialog->setWindowTitle(QCoreApplication::translate("RecoverPasswordDialog", "Recover Password", nullptr));
        label_title_2->setText(QCoreApplication::translate("RecoverPasswordDialog", "Enter the email adress you used to create the account, and we will ", nullptr));
        label_title->setText(QCoreApplication::translate("RecoverPasswordDialog", "Forgot Password", nullptr));
        label_title_3->setText(QCoreApplication::translate("RecoverPasswordDialog", "email you instructions to reset your password", nullptr));
        send_code_button->setText(QCoreApplication::translate("RecoverPasswordDialog", "Send Email", nullptr));
        label_title_4->setText(QCoreApplication::translate("RecoverPasswordDialog", "Email Adress", nullptr));
        email_input->setPlaceholderText(QCoreApplication::translate("RecoverPasswordDialog", "Enter email", nullptr));
        label_title_5->setText(QCoreApplication::translate("RecoverPasswordDialog", "Remember Password?", nullptr));
        pushButton->setText(QCoreApplication::translate("RecoverPasswordDialog", "Login", nullptr));
        label->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class RecoverPasswordDialog: public Ui_RecoverPasswordDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RECOVERPASSWORD_H
