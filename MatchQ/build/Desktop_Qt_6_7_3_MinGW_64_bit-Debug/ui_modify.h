/********************************************************************************
** Form generated from reading UI file 'modify.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MODIFY_H
#define UI_MODIFY_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QDateTimeEdit>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Form
{
public:
    QLineEdit *lineEdit_3;
    QLineEdit *lineEdit_4;
    QLabel *label_8;
    QLabel *label_10;
    QLabel *label_7;
    QComboBox *comboBox;
    QDateEdit *dateEdit;
    QComboBox *comboBox_2;
    QLabel *label_12;
    QLabel *label_9;
    QDateTimeEdit *dateTimeEdit;
    QLabel *label_11;
    QPushButton *pushButton_3;

    void setupUi(QWidget *Form)
    {
        if (Form->objectName().isEmpty())
            Form->setObjectName("Form");
        Form->resize(755, 576);
        Form->setStyleSheet(QString::fromUtf8("background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 #1b1f2a, stop:1 #10131a);"));
        lineEdit_3 = new QLineEdit(Form);
        lineEdit_3->setObjectName("lineEdit_3");
        lineEdit_3->setGeometry(QRect(10, 59, 739, 30));
        lineEdit_3->setStyleSheet(QString::fromUtf8("background-color: #1C1F2A;\n"
"border: 1px solid #2A2D3A;\n"
"border-radius: 5px;\n"
"padding: 5px;\n"
"color: white;\n"
"margin-left: 15px;\n"
"margin-right:15px;"));
        lineEdit_4 = new QLineEdit(Form);
        lineEdit_4->setObjectName("lineEdit_4");
        lineEdit_4->setGeometry(QRect(10, 142, 739, 30));
        lineEdit_4->setStyleSheet(QString::fromUtf8("background-color: #1C1F2A;\n"
"border: 1px solid #2A2D3A;\n"
"border-radius: 5px;\n"
"padding: 5px;\n"
"color: white;\n"
"margin-left: 15px;\n"
"margin-right:15px;"));
        label_8 = new QLabel(Form);
        label_8->setObjectName("label_8");
        label_8->setGeometry(QRect(10, 96, 739, 39));
        label_8->setStyleSheet(QString::fromUtf8("color: #A0A8B7;\n"
"font-weight: bold;\n"
"padding-bottom: 5px;background-color:transparent;"));
        label_10 = new QLabel(Form);
        label_10->setObjectName("label_10");
        label_10->setGeometry(QRect(10, 420, 739, 39));
        label_10->setStyleSheet(QString::fromUtf8("color: #A0A8B7;\n"
"font-weight: bold;\n"
"padding-bottom: 5px;background-color:transparent;"));
        label_7 = new QLabel(Form);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(10, 13, 739, 39));
        label_7->setStyleSheet(QString::fromUtf8("color: #A0A8B7;\n"
"font-weight: bold;\n"
"padding-bottom: 5px;background-color:transparent;"));
        comboBox = new QComboBox(Form);
        comboBox->addItem(QString());
        comboBox->setObjectName("comboBox");
        comboBox->setGeometry(QRect(10, 383, 739, 30));
        comboBox->setStyleSheet(QString::fromUtf8("background-color: #1C1F2A;\n"
"border: 1px solid #2A2D3A;\n"
"border-radius: 5px;\n"
"padding: 5px;\n"
"color: white;\n"
"margin-left: 15px;\n"
"margin-right:15px;"));
        dateEdit = new QDateEdit(Form);
        dateEdit->setObjectName("dateEdit");
        dateEdit->setGeometry(QRect(10, 309, 739, 21));
        dateEdit->setStyleSheet(QString::fromUtf8("background-color: #1C1F2A;\n"
"border: 1px solid #2A2D3A;\n"
"border-radius: 5px;\n"
"padding: 5px;\n"
"color: white;\n"
"margin-left: 15px;\n"
"margin-right:15px;"));
        comboBox_2 = new QComboBox(Form);
        comboBox_2->addItem(QString());
        comboBox_2->setObjectName("comboBox_2");
        comboBox_2->setGeometry(QRect(10, 225, 739, 30));
        comboBox_2->setStyleSheet(QString::fromUtf8("background-color: #1C1F2A;\n"
"border: 1px solid #2A2D3A;\n"
"border-radius: 5px;\n"
"padding: 5px;\n"
"color: white;\n"
"margin-left: 15px;\n"
"margin-right:15px;"));
        label_12 = new QLabel(Form);
        label_12->setObjectName("label_12");
        label_12->setGeometry(QRect(10, 262, 739, 40));
        label_12->setStyleSheet(QString::fromUtf8("color: #A0A8B7;\n"
"font-weight: bold;\n"
"padding-bottom: 5px;\n"
"background-color:transparent;\n"
""));
        label_9 = new QLabel(Form);
        label_9->setObjectName("label_9");
        label_9->setGeometry(QRect(10, 337, 739, 39));
        label_9->setStyleSheet(QString::fromUtf8("color: #A0A8B7;\n"
"font-weight: bold;\n"
"padding-bottom: 5px;background-color:transparent;"));
        dateTimeEdit = new QDateTimeEdit(Form);
        dateTimeEdit->setObjectName("dateTimeEdit");
        dateTimeEdit->setGeometry(QRect(10, 466, 739, 21));
        dateTimeEdit->setStyleSheet(QString::fromUtf8("background-color: #1C1F2A;\n"
"border: 1px solid #2A2D3A;\n"
"border-radius: 5px;\n"
"padding: 5px;\n"
"color: white;\n"
"margin-left: 15px;\n"
"margin-right:15px;"));
        label_11 = new QLabel(Form);
        label_11->setObjectName("label_11");
        label_11->setGeometry(QRect(10, 179, 739, 39));
        label_11->setStyleSheet(QString::fromUtf8("color: #A0A8B7;\n"
"font-weight: bold;\n"
"padding-bottom: 5px;background-color:transparent;"));
        pushButton_3 = new QPushButton(Form);
        pushButton_3->setObjectName("pushButton_3");
        pushButton_3->setGeometry(QRect(650, 530, 83, 29));
        pushButton_3->setStyleSheet(QString::fromUtf8("background-color: #192231;\n"
"border-radius: 5px ;"));

        retranslateUi(Form);

        QMetaObject::connectSlotsByName(Form);
    } // setupUi

    void retranslateUi(QWidget *Form)
    {
        Form->setWindowTitle(QCoreApplication::translate("Form", "Form", nullptr));
        label_8->setText(QCoreApplication::translate("Form", "Team_2", nullptr));
        label_10->setText(QCoreApplication::translate("Form", "Date", nullptr));
        label_7->setText(QCoreApplication::translate("Form", "Team_1", nullptr));
        comboBox->setItemText(0, QCoreApplication::translate("Form", "RMD", nullptr));

        comboBox_2->setItemText(0, QCoreApplication::translate("Form", "Bernabeo", nullptr));

        label_12->setText(QCoreApplication::translate("Form", "Referee's_FullName", nullptr));
        label_9->setText(QCoreApplication::translate("Form", "Competiton", nullptr));
        label_11->setText(QCoreApplication::translate("Form", "Stadium", nullptr));
        pushButton_3->setText(QCoreApplication::translate("Form", "Modify", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Form: public Ui_Form {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MODIFY_H
