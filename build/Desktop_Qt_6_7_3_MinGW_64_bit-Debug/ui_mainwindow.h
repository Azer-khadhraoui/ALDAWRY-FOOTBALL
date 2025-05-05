/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QLabel *label_4;
    QLineEdit *lineEdit;
    QLineEdit *lineEdit_2;
    QPushButton *sign_in;
    QLabel *label_6;
    QPushButton *sign_in_2;
    QPushButton *togglePasswordButton;
    QLabel *label_2;
    QLabel *label_5;
    QLabel *label;
    QLabel *label_7;
    QLabel *label_8;
    QFrame *line;
    QLabel *label_3;
    QLabel *label_9;

    void setupUi(QWidget *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1920, 1080);
        MainWindow->setStyleSheet(QString::fromUtf8(""));
        label_4 = new QLabel(MainWindow);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(807, 137, 431, 101));
        QFont font;
        font.setFamilies({QString::fromUtf8("Arial Nova")});
        font.setPointSize(64);
        font.setBold(true);
        label_4->setFont(font);
        label_4->setStyleSheet(QString::fromUtf8("letter-spacing:2px;\n"
" background-color:transparent;"));
        lineEdit = new QLineEdit(MainWindow);
        lineEdit->setObjectName("lineEdit");
        lineEdit->setGeometry(QRect(630, 590, 671, 61));
        lineEdit->setStyleSheet(QString::fromUtf8("background-color: transparent;\n"
"border: 1px solid #E6E6E6; /* Subtle border matching chart borders */\n"
"border-radius: 5px; /* Slightly rounded corners for a modern look */\n"
"color: #000000; /* Black for typed text */\n"
"QLineEdit[placeholderText] {\n"
"    color: #666666; /* Medium gray for placeholder text */\n"
"}"));
        lineEdit_2 = new QLineEdit(MainWindow);
        lineEdit_2->setObjectName("lineEdit_2");
        lineEdit_2->setGeometry(QRect(630, 710, 671, 61));
        lineEdit_2->setStyleSheet(QString::fromUtf8("background-color: transparent;\n"
"border: 1px solid #E6E6E6; /* Subtle border matching chart borders */\n"
"border-radius: 5px; /* Slightly rounded corners for a modern look */\n"
"color: #000000; /* Black for typed text */\n"
"QLineEdit[placeholderText] {\n"
"    color: #666666; /* Medium gray for placeholder text */\n"
"}"));
        sign_in = new QPushButton(MainWindow);
        sign_in->setObjectName("sign_in");
        sign_in->setGeometry(QRect(870, 860, 201, 41));
        QFont font1;
        font1.setFamilies({QString::fromUtf8("Segoe Script")});
        font1.setPointSize(10);
        font1.setBold(true);
        sign_in->setFont(font1);
        sign_in->setStyleSheet(QString::fromUtf8("background-color: transparent;\n"
"border: 1px solid #E6E6E6; /* Subtle border matching chart borders */\n"
"border-radius: 5px; /* Slightly rounded corners for a modern look */\n"
"background-color: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 #1b1f2a, stop:1 #10131a);"));
        label_6 = new QLabel(MainWindow);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(800, 800, 22, 21));
        label_6->setStyleSheet(QString::fromUtf8("background-color:transparent;"));
        label_6->setPixmap(QPixmap(QString::fromUtf8("../../../../../Pictures/proj QT/password.png")));
        label_6->setScaledContents(true);
        sign_in_2 = new QPushButton(MainWindow);
        sign_in_2->setObjectName("sign_in_2");
        sign_in_2->setGeometry(QRect(1140, 780, 161, 41));
        QFont font2;
        font2.setUnderline(true);
        sign_in_2->setFont(font2);
        sign_in_2->setStyleSheet(QString::fromUtf8("background-color: transparent;\n"
"border: 1px solid transparent ; /* Subtle border matching chart borders */\n"
""));
        togglePasswordButton = new QPushButton(MainWindow);
        togglePasswordButton->setObjectName("togglePasswordButton");
        togglePasswordButton->setGeometry(QRect(1220, 720, 31, 51));
        togglePasswordButton->setStyleSheet(QString::fromUtf8("background-color: transparent; border: none;"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/img/eye_off.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        togglePasswordButton->setIcon(icon);
        togglePasswordButton->setIconSize(QSize(24, 24));
        togglePasswordButton->setFlat(true);
        label_2 = new QLabel(MainWindow);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(0, 0, 1920, 1080));
        label_2->setPixmap(QPixmap(QString::fromUtf8(":/img/wallpaperflare.com_wallpaper.png")));
        label_2->setScaledContents(true);
        label_5 = new QLabel(MainWindow);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(808, 222, 161, 53));
        QFont font3;
        font3.setFamilies({QString::fromUtf8("Simplified Arabic")});
        font3.setPointSize(36);
        font3.setBold(false);
        label_5->setFont(font3);
        label_5->setStyleSheet(QString::fromUtf8(" background-color:transparent;"));
        label = new QLabel(MainWindow);
        label->setObjectName("label");
        label->setGeometry(QRect(670, 156, 111, 109));
        label->setStyleSheet(QString::fromUtf8("background-color:transparent;"));
        label->setPixmap(QPixmap(QString::fromUtf8(":/img/logo_football.png")));
        label->setScaledContents(true);
        label_7 = new QLabel(MainWindow);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(590, 390, 741, 101));
        QFont font4;
        font4.setPointSize(64);
        font4.setBold(true);
        label_7->setFont(font4);
        label_7->setStyleSheet(QString::fromUtf8("letter-spacing:2px;\n"
" background-color:transparent;"));
        label_8 = new QLabel(MainWindow);
        label_8->setObjectName("label_8");
        label_8->setGeometry(QRect(600, 470, 331, 71));
        QFont font5;
        font5.setFamilies({QString::fromUtf8("Yu Gothic UI")});
        font5.setPointSize(14);
        label_8->setFont(font5);
        label_8->setStyleSheet(QString::fromUtf8(" background-color:transparent;"));
        line = new QFrame(MainWindow);
        line->setObjectName("line");
        line->setGeometry(QRect(1248, 160, 1, 91));
        line->setStyleSheet(QString::fromUtf8("background-color: #E6E6E6;"));
        line->setFrameShape(QFrame::Shape::VLine);
        line->setFrameShadow(QFrame::Shadow::Sunken);
        label_3 = new QLabel(MainWindow);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(1230, 590, 71, 71));
        label_3->setPixmap(QPixmap(QString::fromUtf8(":/img/mailIcon.png")));
        label_3->setScaledContents(true);
        label_9 = new QLabel(MainWindow);
        label_9->setObjectName("label_9");
        label_9->setGeometry(QRect(1240, 700, 81, 81));
        label_9->setPixmap(QPixmap(QString::fromUtf8(":/img/passwordIcon.png")));
        label_9->setScaledContents(true);
        label_2->raise();
        label_4->raise();
        lineEdit->raise();
        lineEdit_2->raise();
        sign_in->raise();
        sign_in_2->raise();
        togglePasswordButton->raise();
        label_5->raise();
        label->raise();
        label_7->raise();
        label_8->raise();
        label_6->raise();
        line->raise();
        label_3->raise();
        label_9->raise();

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QWidget *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Form", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "ALDAWRY", nullptr));
        lineEdit->setText(QString());
        lineEdit->setPlaceholderText(QCoreApplication::translate("MainWindow", "                                            Enter your email adress", nullptr));
        lineEdit_2->setText(QString());
        lineEdit_2->setPlaceholderText(QCoreApplication::translate("MainWindow", "                                            Enter your password", nullptr));
        sign_in->setText(QCoreApplication::translate("MainWindow", "SIGN IN", nullptr));
        label_6->setText(QString());
        sign_in_2->setText(QCoreApplication::translate("MainWindow", "I've forgotten my password", nullptr));
#if QT_CONFIG(tooltip)
        togglePasswordButton->setToolTip(QCoreApplication::translate("MainWindow", "Toggle password visibility", nullptr));
#endif // QT_CONFIG(tooltip)
        label_2->setText(QString());
        label_5->setText(QCoreApplication::translate("MainWindow", "football", nullptr));
        label->setText(QString());
        label_7->setText(QCoreApplication::translate("MainWindow", "WELCOME BACK !", nullptr));
        label_8->setText(QCoreApplication::translate("MainWindow", "please login to get started .", nullptr));
        label_3->setText(QString());
        label_9->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
