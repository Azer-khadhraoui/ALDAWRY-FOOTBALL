/********************************************************************************
** Form generated from reading UI file 'EmailSent.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EMAILSENT_H
#define UI_EMAILSENT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_EmailSentDialog
{
public:
    QLineEdit *code_input;
    QPushButton *verify_code_button;
    QWidget *widget;
    QLabel *label_title_5;
    QPushButton *pushButton;
    QLabel *label_title_6;
    QLabel *label_title_7;
    QLabel *label_title_8;
    QLabel *label_title_9;
    QPushButton *pushButton_2;
    QLabel *label_title_10;
    QLabel *label;

    void setupUi(QDialog *EmailSentDialog)
    {
        if (EmailSentDialog->objectName().isEmpty())
            EmailSentDialog->setObjectName("EmailSentDialog");
        EmailSentDialog->resize(450, 363);
        EmailSentDialog->setStyleSheet(QString::fromUtf8("\n"
"background-color: white;"));
        code_input = new QLineEdit(EmailSentDialog);
        code_input->setObjectName("code_input");
        code_input->setEnabled(false);
        code_input->setGeometry(QRect(55, 170, 341, 41));
        code_input->setStyleSheet(QString::fromUtf8("background-color: transparent;\n"
" border: 1px solid grey;\n"
" border-radius: 5px;\n"
" padding: 5px; \n"
"color: black;"));
        verify_code_button = new QPushButton(EmailSentDialog);
        verify_code_button->setObjectName("verify_code_button");
        verify_code_button->setEnabled(false);
        verify_code_button->setGeometry(QRect(300, 170, 100, 41));
        verify_code_button->setStyleSheet(QString::fromUtf8("background-color: #0078d7; color: white; border-radius: 10Px; font-weight: bold;"));
        widget = new QWidget(EmailSentDialog);
        widget->setObjectName("widget");
        widget->setGeometry(QRect(30, 30, 391, 301));
        widget->setStyleSheet(QString::fromUtf8("background-color: rgb(248, 248, 248);\n"
"border-radius: 10Px;"));
        label_title_5 = new QLabel(widget);
        label_title_5->setObjectName("label_title_5");
        label_title_5->setGeometry(QRect(-20, 220, 351, 41));
        QFont font;
        font.setPointSize(9);
        font.setBold(false);
        label_title_5->setFont(font);
        label_title_5->setStyleSheet(QString::fromUtf8("background-color: transparent; color: grey;"));
        label_title_5->setAlignment(Qt::AlignmentFlag::AlignCenter);
        pushButton = new QPushButton(widget);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(230, 230, 80, 24));
        QFont font1;
        font1.setUnderline(true);
        pushButton->setFont(font1);
        pushButton->setStyleSheet(QString::fromUtf8("background-color: transparent;\n"
"color : blue;"));
        label_title_6 = new QLabel(widget);
        label_title_6->setObjectName("label_title_6");
        label_title_6->setGeometry(QRect(-20, 30, 231, 41));
        QFont font2;
        font2.setPointSize(20);
        font2.setBold(true);
        label_title_6->setFont(font2);
        label_title_6->setStyleSheet(QString::fromUtf8("background-color: transparent; color: black;"));
        label_title_6->setAlignment(Qt::AlignmentFlag::AlignCenter);
        label_title_7 = new QLabel(widget);
        label_title_7->setObjectName("label_title_7");
        label_title_7->setGeometry(QRect(-70, 60, 351, 41));
        label_title_7->setFont(font);
        label_title_7->setStyleSheet(QString::fromUtf8("background-color: transparent; color: grey;"));
        label_title_7->setAlignment(Qt::AlignmentFlag::AlignCenter);
        label_title_8 = new QLabel(widget);
        label_title_8->setObjectName("label_title_8");
        label_title_8->setGeometry(QRect(80, 60, 351, 41));
        label_title_8->setFont(font);
        label_title_8->setStyleSheet(QString::fromUtf8("background-color: transparent; color: black;"));
        label_title_8->setAlignment(Qt::AlignmentFlag::AlignCenter);
        label_title_9 = new QLabel(widget);
        label_title_9->setObjectName("label_title_9");
        label_title_9->setGeometry(QRect(-20, 80, 351, 41));
        label_title_9->setFont(font);
        label_title_9->setStyleSheet(QString::fromUtf8("background-color: transparent; color: grey;"));
        label_title_9->setAlignment(Qt::AlignmentFlag::AlignCenter);
        pushButton_2 = new QPushButton(widget);
        pushButton_2->setObjectName("pushButton_2");
        pushButton_2->setGeometry(QRect(200, 260, 121, 24));
        pushButton_2->setFont(font1);
        pushButton_2->setStyleSheet(QString::fromUtf8("background-color: transparent;\n"
"color : blue;"));
        label_title_10 = new QLabel(widget);
        label_title_10->setObjectName("label_title_10");
        label_title_10->setGeometry(QRect(56, 249, 171, 41));
        label_title_10->setFont(font);
        label_title_10->setStyleSheet(QString::fromUtf8("background-color: transparent; color: grey;"));
        label_title_10->setAlignment(Qt::AlignmentFlag::AlignCenter);
        label = new QLabel(widget);
        label->setObjectName("label");
        label->setGeometry(QRect(330, 0, 60, 60));
        label->setStyleSheet(QString::fromUtf8("background-color:transparent;"));
        label->setPixmap(QPixmap(QString::fromUtf8(":/img/mailIcon.png")));
        label->setScaledContents(true);
        widget->raise();
        code_input->raise();
        verify_code_button->raise();

        retranslateUi(EmailSentDialog);

        QMetaObject::connectSlotsByName(EmailSentDialog);
    } // setupUi

    void retranslateUi(QDialog *EmailSentDialog)
    {
        EmailSentDialog->setWindowTitle(QCoreApplication::translate("EmailSentDialog", "Recover Password", nullptr));
        code_input->setPlaceholderText(QCoreApplication::translate("EmailSentDialog", "Enter verification-code", nullptr));
        verify_code_button->setText(QCoreApplication::translate("EmailSentDialog", "Verify Code", nullptr));
        label_title_5->setText(QCoreApplication::translate("EmailSentDialog", "Did not receive the email ?", nullptr));
        pushButton->setText(QCoreApplication::translate("EmailSentDialog", "Resend Email", nullptr));
        label_title_6->setText(QCoreApplication::translate("EmailSentDialog", "Email Sent", nullptr));
        label_title_7->setText(QCoreApplication::translate("EmailSentDialog", "We have sent you an email at ", nullptr));
        label_title_8->setText(QCoreApplication::translate("EmailSentDialog", "my-emailid@gmail.com", nullptr));
        label_title_9->setText(QCoreApplication::translate("EmailSentDialog", "Check your inbox and enter the Verification-Code", nullptr));
        pushButton_2->setText(QCoreApplication::translate("EmailSentDialog", "Change Email Adress", nullptr));
        label_title_10->setText(QCoreApplication::translate("EmailSentDialog", "Wrong Email Adress ?", nullptr));
        label->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class EmailSentDialog: public Ui_EmailSentDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EMAILSENT_H
