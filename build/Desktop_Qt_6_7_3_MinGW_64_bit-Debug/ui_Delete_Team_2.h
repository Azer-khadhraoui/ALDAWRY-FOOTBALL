/********************************************************************************
** Form generated from reading UI file 'Delete_Team_2.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DELETE_TEAM_2_H
#define UI_DELETE_TEAM_2_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Form
{
public:
    QLabel *label_2;
    QPushButton *pushButton_2;
    QLineEdit *lineEdit;

    void setupUi(QWidget *Form)
    {
        if (Form->objectName().isEmpty())
            Form->setObjectName("Form");
        Form->resize(352, 125);
        Form->setStyleSheet(QString::fromUtf8("background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 #1b1f2a, stop:1 #10131a);\n"
""));
        label_2 = new QLabel(Form);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(20, 30, 71, 16));
        label_2->setStyleSheet(QString::fromUtf8("background-color: transparent;"));
        pushButton_2 = new QPushButton(Form);
        pushButton_2->setObjectName("pushButton_2");
        pushButton_2->setGeometry(QRect(220, 80, 80, 24));
        lineEdit = new QLineEdit(Form);
        lineEdit->setObjectName("lineEdit");
        lineEdit->setGeometry(QRect(130, 30, 171, 19));

        retranslateUi(Form);

        QMetaObject::connectSlotsByName(Form);
    } // setupUi

    void retranslateUi(QWidget *Form)
    {
        Form->setWindowTitle(QCoreApplication::translate("Form", "Form", nullptr));
        label_2->setText(QCoreApplication::translate("Form", "Team_Id :", nullptr));
        pushButton_2->setText(QCoreApplication::translate("Form", "Confirm", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Form: public Ui_Form {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DELETE_TEAM_2_H
