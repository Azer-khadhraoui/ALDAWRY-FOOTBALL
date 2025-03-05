/********************************************************************************
** Form generated from reading UI file 'addcompetitionwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDCOMPETITIONWINDOW_H
#define UI_ADDCOMPETITIONWINDOW_H

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

class Ui_AddCompetitionForm
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

    void setupUi(QWidget *AddCompetitionForm)
    {
        if (AddCompetitionForm->objectName().isEmpty())
            AddCompetitionForm->setObjectName("AddCompetitionForm");
        AddCompetitionForm->resize(400, 500);
        AddCompetitionForm->setStyleSheet(QString::fromUtf8("background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 #1b1f2a, stop:1 #10131a);"));
        label_comp_name = new QLabel(AddCompetitionForm);
        label_comp_name->setObjectName("label_comp_name");
        label_comp_name->setGeometry(QRect(30, 30, 120, 25));
        label_comp_name->setStyleSheet(QString::fromUtf8("color: #D3D3D3; font-size: 14px;"));
        lineEdit_comp_name = new QLineEdit(AddCompetitionForm);
        lineEdit_comp_name->setObjectName("lineEdit_comp_name");
        lineEdit_comp_name->setGeometry(QRect(160, 30, 200, 30));
        lineEdit_comp_name->setStyleSheet(QString::fromUtf8("background-color: #141821;\n"
"border: 2px solid #cccccc;\n"
"border-radius: 6px;\n"
"padding: 6px 10px;\n"
"font-size: 14px;\n"
"color: white;"));
        label_comp_type = new QLabel(AddCompetitionForm);
        label_comp_type->setObjectName("label_comp_type");
        label_comp_type->setGeometry(QRect(30, 80, 120, 25));
        label_comp_type->setStyleSheet(QString::fromUtf8("color: #D3D3D3; font-size: 14px;"));
        comboBox_comp_type = new QComboBox(AddCompetitionForm);
        comboBox_comp_type->addItem(QString());
        comboBox_comp_type->addItem(QString());
        comboBox_comp_type->addItem(QString());
        comboBox_comp_type->setObjectName("comboBox_comp_type");
        comboBox_comp_type->setGeometry(QRect(160, 80, 200, 30));
        comboBox_comp_type->setStyleSheet(QString::fromUtf8("background-color: #141821;\n"
"border: 2px solid #cccccc;\n"
"border-radius: 6px;\n"
"color: white;"));
        label_start_date = new QLabel(AddCompetitionForm);
        label_start_date->setObjectName("label_start_date");
        label_start_date->setGeometry(QRect(30, 130, 120, 25));
        label_start_date->setStyleSheet(QString::fromUtf8("color: #D3D3D3; font-size: 14px;"));
        dateEdit_start_date = new QDateEdit(AddCompetitionForm);
        dateEdit_start_date->setObjectName("dateEdit_start_date");
        dateEdit_start_date->setGeometry(QRect(160, 130, 200, 30));
        dateEdit_start_date->setStyleSheet(QString::fromUtf8("background-color: #141821;\n"
"border: 2px solid #cccccc;\n"
"border-radius: 6px;\n"
"color: white;"));
        dateEdit_start_date->setCalendarPopup(true);
        label_end_date = new QLabel(AddCompetitionForm);
        label_end_date->setObjectName("label_end_date");
        label_end_date->setGeometry(QRect(30, 180, 120, 25));
        label_end_date->setStyleSheet(QString::fromUtf8("color: #D3D3D3; font-size: 14px;"));
        dateEdit_end_date = new QDateEdit(AddCompetitionForm);
        dateEdit_end_date->setObjectName("dateEdit_end_date");
        dateEdit_end_date->setGeometry(QRect(160, 180, 200, 30));
        dateEdit_end_date->setStyleSheet(QString::fromUtf8("background-color: #141821;\n"
"border: 2px solid #cccccc;\n"
"border-radius: 6px;\n"
"color: white;"));
        dateEdit_end_date->setCalendarPopup(true);
        label_numbers_teams = new QLabel(AddCompetitionForm);
        label_numbers_teams->setObjectName("label_numbers_teams");
        label_numbers_teams->setGeometry(QRect(30, 230, 120, 25));
        label_numbers_teams->setStyleSheet(QString::fromUtf8("color: #D3D3D3; font-size: 14px;"));
        spinBox_numbers_teams = new QSpinBox(AddCompetitionForm);
        spinBox_numbers_teams->setObjectName("spinBox_numbers_teams");
        spinBox_numbers_teams->setGeometry(QRect(160, 230, 200, 30));
        spinBox_numbers_teams->setStyleSheet(QString::fromUtf8("background-color: #141821;\n"
"border: 2px solid #cccccc;\n"
"border-radius: 6px;\n"
"color: white;"));
        spinBox_numbers_teams->setMinimum(2);
        spinBox_numbers_teams->setMaximum(100);
        label_reward = new QLabel(AddCompetitionForm);
        label_reward->setObjectName("label_reward");
        label_reward->setGeometry(QRect(30, 280, 120, 25));
        label_reward->setStyleSheet(QString::fromUtf8("color: #D3D3D3; font-size: 14px;"));
        lineEdit_reward = new QLineEdit(AddCompetitionForm);
        lineEdit_reward->setObjectName("lineEdit_reward");
        lineEdit_reward->setGeometry(QRect(160, 280, 200, 30));
        lineEdit_reward->setStyleSheet(QString::fromUtf8("background-color: #141821;\n"
"border: 2px solid #cccccc;\n"
"border-radius: 6px;\n"
"padding: 6px 10px;\n"
"font-size: 14px;\n"
"color: white;"));
        pushButton_submit = new QPushButton(AddCompetitionForm);
        pushButton_submit->setObjectName("pushButton_submit");
        pushButton_submit->setGeometry(QRect(150, 340, 100, 40));
        pushButton_submit->setStyleSheet(QString::fromUtf8("background-color: #20242e;\n"
"color: white;\n"
"border-radius: 5px;\n"
"padding: 6px 12px;\n"
"border: 1px solid #666666;\n"
"font-size: 14px;"));

        retranslateUi(AddCompetitionForm);

        QMetaObject::connectSlotsByName(AddCompetitionForm);
    } // setupUi

    void retranslateUi(QWidget *AddCompetitionForm)
    {
        AddCompetitionForm->setWindowTitle(QCoreApplication::translate("AddCompetitionForm", "Add New Competition", nullptr));
        label_comp_name->setText(QCoreApplication::translate("AddCompetitionForm", "Competition Name:", nullptr));
        label_comp_type->setText(QCoreApplication::translate("AddCompetitionForm", "Competition Type:", nullptr));
        comboBox_comp_type->setItemText(0, QCoreApplication::translate("AddCompetitionForm", "League", nullptr));
        comboBox_comp_type->setItemText(1, QCoreApplication::translate("AddCompetitionForm", "Tournament", nullptr));
        comboBox_comp_type->setItemText(2, QCoreApplication::translate("AddCompetitionForm", "Cup", nullptr));

        label_start_date->setText(QCoreApplication::translate("AddCompetitionForm", "Start Date:", nullptr));
        label_end_date->setText(QCoreApplication::translate("AddCompetitionForm", "End Date:", nullptr));
        label_numbers_teams->setText(QCoreApplication::translate("AddCompetitionForm", "Number of Teams:", nullptr));
        label_reward->setText(QCoreApplication::translate("AddCompetitionForm", "Reward:", nullptr));
        pushButton_submit->setText(QCoreApplication::translate("AddCompetitionForm", "Submit", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AddCompetitionForm: public Ui_AddCompetitionForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDCOMPETITIONWINDOW_H
