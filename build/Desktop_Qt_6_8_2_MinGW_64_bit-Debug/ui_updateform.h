/********************************************************************************
** Form generated from reading UI file 'updateform.ui'
**
** Created by: Qt User Interface Compiler version 6.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_UPDATEFORM_H
#define UI_UPDATEFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_updateform
{
public:
    QLabel *label_comp_name;
    QLineEdit *lineEdit_comp_name;
    QLabel *label_comp_type;
    QComboBox *comboBox_comp_type;
    QLabel *label_start_date;
    QDateEdit *dateEdit_start_date;
    QLabel *label_end_date;
    QDateEdit *dateEdit_end_date;
    QLabel *label_numbers_teams;
    QSpinBox *spinBox_numbers_teams;
    QLabel *label_reward;
    QLineEdit *lineEdit_reward;
    QPushButton *pushButton_submit;
    QLabel *label_comp_name_2;
    QLineEdit *lineEdit_id;
    QPushButton *pushButton_submit_2;

    void setupUi(QWidget *updateform)
    {
        if (updateform->objectName().isEmpty())
            updateform->setObjectName("updateform");
        updateform->resize(400, 500);
        updateform->setStyleSheet(QString::fromUtf8("background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 #1b1f2a, stop:1 #10131a);"));
        label_comp_name = new QLabel(updateform);
        label_comp_name->setObjectName("label_comp_name");
        label_comp_name->setGeometry(QRect(30, 120, 120, 25));
        label_comp_name->setStyleSheet(QString::fromUtf8("color: #D3D3D3; font-size: 14px;"));
        lineEdit_comp_name = new QLineEdit(updateform);
        lineEdit_comp_name->setObjectName("lineEdit_comp_name");
        lineEdit_comp_name->setGeometry(QRect(160, 120, 200, 30));
        lineEdit_comp_name->setStyleSheet(QString::fromUtf8("background-color: #141821;\n"
"border: 2px solid #cccccc;\n"
"border-radius: 6px;\n"
"padding: 6px 10px;\n"
"font-size: 14px;\n"
"color: white;"));
        label_comp_type = new QLabel(updateform);
        label_comp_type->setObjectName("label_comp_type");
        label_comp_type->setGeometry(QRect(30, 170, 120, 25));
        label_comp_type->setStyleSheet(QString::fromUtf8("color: #D3D3D3; font-size: 14px;"));
        comboBox_comp_type = new QComboBox(updateform);
        comboBox_comp_type->addItem(QString());
        comboBox_comp_type->addItem(QString());
        comboBox_comp_type->addItem(QString());
        comboBox_comp_type->setObjectName("comboBox_comp_type");
        comboBox_comp_type->setGeometry(QRect(160, 170, 200, 30));
        comboBox_comp_type->setStyleSheet(QString::fromUtf8("background-color: #141821;\n"
"border: 2px solid #cccccc;\n"
"border-radius: 6px;\n"
"color: white;"));
        label_start_date = new QLabel(updateform);
        label_start_date->setObjectName("label_start_date");
        label_start_date->setGeometry(QRect(30, 220, 120, 25));
        label_start_date->setStyleSheet(QString::fromUtf8("color: #D3D3D3; font-size: 14px;"));
        dateEdit_start_date = new QDateEdit(updateform);
        dateEdit_start_date->setObjectName("dateEdit_start_date");
        dateEdit_start_date->setGeometry(QRect(160, 220, 200, 30));
        dateEdit_start_date->setStyleSheet(QString::fromUtf8("background-color: #141821;\n"
"border: 2px solid #cccccc;\n"
"border-radius: 6px;\n"
"color: white;"));
        dateEdit_start_date->setCalendarPopup(true);
        label_end_date = new QLabel(updateform);
        label_end_date->setObjectName("label_end_date");
        label_end_date->setGeometry(QRect(30, 270, 120, 25));
        label_end_date->setStyleSheet(QString::fromUtf8("color: #D3D3D3; font-size: 14px;"));
        dateEdit_end_date = new QDateEdit(updateform);
        dateEdit_end_date->setObjectName("dateEdit_end_date");
        dateEdit_end_date->setGeometry(QRect(160, 270, 200, 30));
        dateEdit_end_date->setStyleSheet(QString::fromUtf8("background-color: #141821;\n"
"border: 2px solid #cccccc;\n"
"border-radius: 6px;\n"
"color: white;"));
        dateEdit_end_date->setCalendarPopup(true);
        label_numbers_teams = new QLabel(updateform);
        label_numbers_teams->setObjectName("label_numbers_teams");
        label_numbers_teams->setGeometry(QRect(30, 320, 120, 25));
        label_numbers_teams->setStyleSheet(QString::fromUtf8("color: #D3D3D3; font-size: 14px;"));
        spinBox_numbers_teams = new QSpinBox(updateform);
        spinBox_numbers_teams->setObjectName("spinBox_numbers_teams");
        spinBox_numbers_teams->setGeometry(QRect(160, 320, 200, 30));
        spinBox_numbers_teams->setStyleSheet(QString::fromUtf8("background-color: #141821;\n"
"border: 2px solid #cccccc;\n"
"border-radius: 6px;\n"
"color: white;"));
        spinBox_numbers_teams->setMinimum(2);
        spinBox_numbers_teams->setMaximum(100);
        label_reward = new QLabel(updateform);
        label_reward->setObjectName("label_reward");
        label_reward->setGeometry(QRect(30, 370, 120, 25));
        label_reward->setStyleSheet(QString::fromUtf8("color: #D3D3D3; font-size: 14px;"));
        lineEdit_reward = new QLineEdit(updateform);
        lineEdit_reward->setObjectName("lineEdit_reward");
        lineEdit_reward->setGeometry(QRect(160, 370, 200, 30));
        lineEdit_reward->setStyleSheet(QString::fromUtf8("background-color: #141821;\n"
"border: 2px solid #cccccc;\n"
"border-radius: 6px;\n"
"padding: 6px 10px;\n"
"font-size: 14px;\n"
"color: white;"));
        pushButton_submit = new QPushButton(updateform);
        pushButton_submit->setObjectName("pushButton_submit");
        pushButton_submit->setGeometry(QRect(150, 430, 100, 40));
        pushButton_submit->setStyleSheet(QString::fromUtf8("background-color: #20242e;\n"
"color: white;\n"
"border-radius: 5px;\n"
"padding: 6px 12px;\n"
"border: 1px solid #666666;\n"
"font-size: 14px;"));
        label_comp_name_2 = new QLabel(updateform);
        label_comp_name_2->setObjectName("label_comp_name_2");
        label_comp_name_2->setGeometry(QRect(30, 30, 120, 25));
        label_comp_name_2->setStyleSheet(QString::fromUtf8("color: #D3D3D3; font-size: 14px;"));
        lineEdit_id = new QLineEdit(updateform);
        lineEdit_id->setObjectName("lineEdit_id");
        lineEdit_id->setGeometry(QRect(160, 30, 200, 30));
        lineEdit_id->setStyleSheet(QString::fromUtf8("background-color: #141821;\n"
"border: 2px solid #cccccc;\n"
"border-radius: 6px;\n"
"padding: 6px 10px;\n"
"font-size: 14px;\n"
"color: white;"));
        pushButton_submit_2 = new QPushButton(updateform);
        pushButton_submit_2->setObjectName("pushButton_submit_2");
        pushButton_submit_2->setGeometry(QRect(130, 70, 100, 40));
        pushButton_submit_2->setStyleSheet(QString::fromUtf8("background-color: #20242e;\n"
"color: white;\n"
"border-radius: 5px;\n"
"padding: 6px 12px;\n"
"border: 1px solid #666666;\n"
"font-size: 14px;"));

        retranslateUi(updateform);

        QMetaObject::connectSlotsByName(updateform);
    } // setupUi

    void retranslateUi(QWidget *updateform)
    {
        updateform->setWindowTitle(QCoreApplication::translate("updateform", "Add New Competition", nullptr));
        label_comp_name->setText(QCoreApplication::translate("updateform", "Competition Name:", nullptr));
        label_comp_type->setText(QCoreApplication::translate("updateform", "Competition Type:", nullptr));
        comboBox_comp_type->setItemText(0, QCoreApplication::translate("updateform", "League", nullptr));
        comboBox_comp_type->setItemText(1, QCoreApplication::translate("updateform", "Tournament", nullptr));
        comboBox_comp_type->setItemText(2, QCoreApplication::translate("updateform", "Cup", nullptr));

        label_start_date->setText(QCoreApplication::translate("updateform", "Start Date:", nullptr));
        label_end_date->setText(QCoreApplication::translate("updateform", "End Date:", nullptr));
        label_numbers_teams->setText(QCoreApplication::translate("updateform", "Number of Teams:", nullptr));
        label_reward->setText(QCoreApplication::translate("updateform", "Reward:", nullptr));
        pushButton_submit->setText(QCoreApplication::translate("updateform", "Submit", nullptr));
        label_comp_name_2->setText(QCoreApplication::translate("updateform", "ID:", nullptr));
        pushButton_submit_2->setText(QCoreApplication::translate("updateform", "Generate", nullptr));
    } // retranslateUi

};

namespace Ui {
    class updateform: public Ui_updateform {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_UPDATEFORM_H
