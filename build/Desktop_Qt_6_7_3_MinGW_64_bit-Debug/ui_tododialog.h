/********************************************************************************
** Form generated from reading UI file 'tododialog.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TODODIALOG_H
#define UI_TODODIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateTimeEdit>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_TodoDialog
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *teamLabel;
    QComboBox *teamComboBox;
    QLabel *todoLabel;
    QLineEdit *todoLineEdit;
    QLabel *statusLabel;
    QLineEdit *statusLineEdit;
    QLabel *dateLabel;
    QDateTimeEdit *dateTimeEdit;
    QHBoxLayout *buttonLayout;
    QPushButton *saveButton;
    QPushButton *cancelButton;

    void setupUi(QDialog *TodoDialog)
    {
        if (TodoDialog->objectName().isEmpty())
            TodoDialog->setObjectName("TodoDialog");
        TodoDialog->resize(375, 353);
        verticalLayout = new QVBoxLayout(TodoDialog);
        verticalLayout->setObjectName("verticalLayout");
        teamLabel = new QLabel(TodoDialog);
        teamLabel->setObjectName("teamLabel");

        verticalLayout->addWidget(teamLabel);

        teamComboBox = new QComboBox(TodoDialog);
        teamComboBox->setObjectName("teamComboBox");
        teamComboBox->setStyleSheet(QString::fromUtf8("background-color: #2A3240;\n"
"  border: 1px solid #3A4A5A;\n"
"    border-radius: 5px;\n"
"    padding: 5px;\n"
"    color: #E0E6ED;\n"
"    margin-left: 15px;\n"
"    margin-right: 15px;\n"
"\n"
"Qcb::drop-down {\n"
"    border-left: 1px solid #3A4A5A;\n"
"    width: 20px;\n"
"}\n"
"Qcb:focus {\n"
"    border: 1px solid #00FF7F;\n"
"    background-color: #323A48;\n"
"}"));

        verticalLayout->addWidget(teamComboBox);

        todoLabel = new QLabel(TodoDialog);
        todoLabel->setObjectName("todoLabel");

        verticalLayout->addWidget(todoLabel);

        todoLineEdit = new QLineEdit(TodoDialog);
        todoLineEdit->setObjectName("todoLineEdit");
        todoLineEdit->setStyleSheet(QString::fromUtf8("background-color: #2A3240; /* Darker blue-gray for input fields */\n"
"    border: 1px solid #3A4A5A; /* Subtle blue-gray border */\n"
"    border-radius: 5px;\n"
"    padding: 5px;\n"
"    color: #E0E6ED; /* Light gray text for readability */\n"
"    margin-left: 15px;\n"
"    margin-right: 15px;\n"
""));

        verticalLayout->addWidget(todoLineEdit);

        statusLabel = new QLabel(TodoDialog);
        statusLabel->setObjectName("statusLabel");

        verticalLayout->addWidget(statusLabel);

        statusLineEdit = new QLineEdit(TodoDialog);
        statusLineEdit->setObjectName("statusLineEdit");
        statusLineEdit->setStyleSheet(QString::fromUtf8("background-color: #2A3240; /* Darker blue-gray for input fields */\n"
"    border: 1px solid #3A4A5A; /* Subtle blue-gray border */\n"
"    border-radius: 5px;\n"
"    padding: 5px;\n"
"    color: #E0E6ED; /* Light gray text for readability */\n"
"    margin-left: 15px;\n"
"    margin-right: 15px;\n"
""));

        verticalLayout->addWidget(statusLineEdit);

        dateLabel = new QLabel(TodoDialog);
        dateLabel->setObjectName("dateLabel");

        verticalLayout->addWidget(dateLabel);

        dateTimeEdit = new QDateTimeEdit(TodoDialog);
        dateTimeEdit->setObjectName("dateTimeEdit");
        dateTimeEdit->setCalendarPopup(true);

        verticalLayout->addWidget(dateTimeEdit);

        buttonLayout = new QHBoxLayout();
        buttonLayout->setObjectName("buttonLayout");
        saveButton = new QPushButton(TodoDialog);
        saveButton->setObjectName("saveButton");

        buttonLayout->addWidget(saveButton);

        cancelButton = new QPushButton(TodoDialog);
        cancelButton->setObjectName("cancelButton");

        buttonLayout->addWidget(cancelButton);


        verticalLayout->addLayout(buttonLayout);


        retranslateUi(TodoDialog);

        QMetaObject::connectSlotsByName(TodoDialog);
    } // setupUi

    void retranslateUi(QDialog *TodoDialog)
    {
        TodoDialog->setWindowTitle(QCoreApplication::translate("TodoDialog", "Add To-Do", nullptr));
        teamLabel->setText(QCoreApplication::translate("TodoDialog", "                Team:", nullptr));
        todoLabel->setText(QCoreApplication::translate("TodoDialog", "              To-Do Description:", nullptr));
        statusLabel->setText(QCoreApplication::translate("TodoDialog", "             Status:", nullptr));
        dateLabel->setText(QCoreApplication::translate("TodoDialog", "             Date:", nullptr));
        saveButton->setText(QCoreApplication::translate("TodoDialog", "Save", nullptr));
        cancelButton->setText(QCoreApplication::translate("TodoDialog", "Cancel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class TodoDialog: public Ui_TodoDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TODODIALOG_H
