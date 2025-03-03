/********************************************************************************
** Form generated from reading UI file 'modify_joueur.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MODIFY_JOUEUR_H
#define UI_MODIFY_JOUEUR_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Form
{
public:
    QPushButton *pushButton_3;
    QComboBox *comboBox;
    QComboBox *comboBox_2;
    QLabel *label_11;
    QLineEdit *lineEdit_3;
    QLabel *label_14;
    QComboBox *comboBox_3;
    QLabel *label_9;
    QLabel *label_8;
    QLineEdit *lineEdit_5;
    QToolButton *toolButton;
    QDateEdit *dateEdit;
    QLineEdit *lineEdit_4;
    QLabel *label_12;
    QLabel *label_13;
    QLabel *label_7;
    QLabel *label_10;

    void setupUi(QWidget *Form)
    {
        if (Form->objectName().isEmpty())
            Form->setObjectName("Form");
        Form->resize(678, 600);
        Form->setStyleSheet(QString::fromUtf8("background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 #1b1f2a, stop:1 #10131a);"));
        pushButton_3 = new QPushButton(Form);
        pushButton_3->setObjectName("pushButton_3");
        pushButton_3->setGeometry(QRect(580, 560, 83, 29));
        pushButton_3->setStyleSheet(QString::fromUtf8("background-color: #192231;\n"
"border-radius: 5px ;"));
        comboBox = new QComboBox(Form);
        comboBox->addItem(QString());
        comboBox->setObjectName("comboBox");
        comboBox->setGeometry(QRect(10, 262, 629, 30));
        comboBox->setStyleSheet(QString::fromUtf8("background-color: #1C1F2A;\n"
"border: 1px solid #2A2D3A;\n"
"border-radius: 5px;\n"
"padding: 5px;\n"
"color: white;\n"
"margin-left: 15px;\n"
"margin-right:15px;"));
        comboBox_2 = new QComboBox(Form);
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->setObjectName("comboBox_2");
        comboBox_2->setGeometry(QRect(10, 337, 629, 30));
        comboBox_2->setStyleSheet(QString::fromUtf8("background-color: #1C1F2A;\n"
"border: 1px solid #2A2D3A;\n"
"border-radius: 5px;\n"
"padding: 5px;\n"
"color: white;\n"
"margin-left: 15px;\n"
"margin-right:15px;"));
        label_11 = new QLabel(Form);
        label_11->setObjectName("label_11");
        label_11->setGeometry(QRect(10, 374, 629, 31));
        label_11->setStyleSheet(QString::fromUtf8("color: #A0A8B7;\n"
"font-weight: bold;\n"
"padding-bottom: 5px;background-color:transparent;"));
        lineEdit_3 = new QLineEdit(Form);
        lineEdit_3->setObjectName("lineEdit_3");
        lineEdit_3->setGeometry(QRect(10, 48, 629, 30));
        lineEdit_3->setStyleSheet(QString::fromUtf8("background-color: #1C1F2A;\n"
"border: 1px solid #2A2D3A;\n"
"border-radius: 5px;\n"
"padding: 5px;\n"
"color: white;\n"
"margin-left: 15px;\n"
"margin-right:15px;"));
        label_14 = new QLabel(Form);
        label_14->setObjectName("label_14");
        label_14->setGeometry(QRect(10, 523, 629, 30));
        label_14->setStyleSheet(QString::fromUtf8("color: #A0A8B7;\n"
"font-weight: bold;\n"
"padding-bottom: 5px;background-color:transparent;"));
        comboBox_3 = new QComboBox(Form);
        comboBox_3->addItem(QString());
        comboBox_3->setObjectName("comboBox_3");
        comboBox_3->setGeometry(QRect(10, 486, 629, 30));
        comboBox_3->setStyleSheet(QString::fromUtf8("background-color: #1C1F2A;\n"
"border: 1px solid #2A2D3A;\n"
"border-radius: 5px;\n"
"padding: 5px;\n"
"color: white;\n"
"margin-left: 15px;\n"
"margin-right:15px;"));
        label_9 = new QLabel(Form);
        label_9->setObjectName("label_9");
        label_9->setGeometry(QRect(10, 224, 629, 31));
        label_9->setStyleSheet(QString::fromUtf8("color: #A0A8B7;\n"
"font-weight: bold;\n"
"padding-bottom: 5px;background-color:transparent;"));
        label_8 = new QLabel(Form);
        label_8->setObjectName("label_8");
        label_8->setGeometry(QRect(10, 85, 629, 30));
        label_8->setStyleSheet(QString::fromUtf8("color: #A0A8B7;\n"
"font-weight: bold;\n"
"padding-bottom: 5px;background-color:transparent;"));
        lineEdit_5 = new QLineEdit(Form);
        lineEdit_5->setObjectName("lineEdit_5");
        lineEdit_5->setGeometry(QRect(10, 412, 629, 30));
        lineEdit_5->setStyleSheet(QString::fromUtf8("background-color: #1C1F2A;\n"
"border: 1px solid #2A2D3A;\n"
"border-radius: 5px;\n"
"padding: 5px;\n"
"color: white;\n"
"margin-left: 15px;\n"
"margin-right:15px;"));
        toolButton = new QToolButton(Form);
        toolButton->setObjectName("toolButton");
        toolButton->setGeometry(QRect(10, 560, 56, 41));
        toolButton->setStyleSheet(QString::fromUtf8("background-color: #1C1F2A;\n"
"border: 1px solid #2A2D3A;\n"
"border-radius: 5px;\n"
"padding: 3px;\n"
"color: white;\n"
"margin-left: 15px;\n"
"margin-right:15px;\n"
"margin-bottom:15px;"));
        dateEdit = new QDateEdit(Form);
        dateEdit->setObjectName("dateEdit");
        dateEdit->setGeometry(QRect(10, 196, 629, 21));
        dateEdit->setStyleSheet(QString::fromUtf8("background-color: #1C1F2A;\n"
"border: 1px solid #2A2D3A;\n"
"border-radius: 5px;\n"
"padding: 5px;\n"
"color: white;\n"
"margin-left: 15px;\n"
"margin-right:15px;"));
        lineEdit_4 = new QLineEdit(Form);
        lineEdit_4->setObjectName("lineEdit_4");
        lineEdit_4->setGeometry(QRect(10, 122, 629, 30));
        lineEdit_4->setStyleSheet(QString::fromUtf8("background-color: #1C1F2A;\n"
"border: 1px solid #2A2D3A;\n"
"border-radius: 5px;\n"
"padding: 5px;\n"
"color: white;\n"
"margin-left: 15px;\n"
"margin-right:15px;"));
        label_12 = new QLabel(Form);
        label_12->setObjectName("label_12");
        label_12->setGeometry(QRect(10, 159, 629, 30));
        label_12->setStyleSheet(QString::fromUtf8("color: #A0A8B7;\n"
"font-weight: bold;\n"
"padding-bottom: 5px;background-color:transparent;"));
        label_13 = new QLabel(Form);
        label_13->setObjectName("label_13");
        label_13->setGeometry(QRect(10, 449, 629, 30));
        label_13->setStyleSheet(QString::fromUtf8("color: #A0A8B7;\n"
"font-weight: bold;\n"
"padding-bottom: 5px;background-color:transparent;"));
        label_7 = new QLabel(Form);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(10, 10, 629, 31));
        label_7->setStyleSheet(QString::fromUtf8("color: #A0A8B7;\n"
"font-weight: bold;\n"
"padding-bottom: 5px;background-color:transparent;"));
        label_10 = new QLabel(Form);
        label_10->setObjectName("label_10");
        label_10->setGeometry(QRect(10, 299, 629, 31));
        label_10->setStyleSheet(QString::fromUtf8("color: #A0A8B7;\n"
"font-weight: bold;\n"
"padding-bottom: 5px;background-color:transparent;"));

        retranslateUi(Form);

        QMetaObject::connectSlotsByName(Form);
    } // setupUi

    void retranslateUi(QWidget *Form)
    {
        Form->setWindowTitle(QCoreApplication::translate("Form", "Form", nullptr));
        pushButton_3->setText(QCoreApplication::translate("Form", "Modify", nullptr));
        comboBox->setItemText(0, QCoreApplication::translate("Form", "RMD", nullptr));

        comboBox_2->setItemText(0, QCoreApplication::translate("Form", "LW", nullptr));
        comboBox_2->setItemText(1, QCoreApplication::translate("Form", "RW", nullptr));

        label_11->setText(QCoreApplication::translate("Form", "Jersey_Nb", nullptr));
        label_14->setText(QCoreApplication::translate("Form", "Insert player photo", nullptr));
        comboBox_3->setItemText(0, QCoreApplication::translate("Form", "BR", nullptr));

        label_9->setText(QCoreApplication::translate("Form", "Team", nullptr));
        label_8->setText(QCoreApplication::translate("Form", "Last_Name", nullptr));
        toolButton->setText(QCoreApplication::translate("Form", "...", nullptr));
        label_12->setText(QCoreApplication::translate("Form", "Date_Of_Birth", nullptr));
        label_13->setText(QCoreApplication::translate("Form", "Nationality", nullptr));
        label_7->setText(QCoreApplication::translate("Form", "First_Name", nullptr));
        label_10->setText(QCoreApplication::translate("Form", "Position", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Form: public Ui_Form {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MODIFY_JOUEUR_H
