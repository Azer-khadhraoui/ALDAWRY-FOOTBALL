/********************************************************************************
** Form generated from reading UI file 'calendardialog.ui'
**
** Created by: Qt User Interface Compiler version 6.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CALENDARDIALOG_H
#define UI_CALENDARDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>

QT_BEGIN_NAMESPACE

class Ui_CalendarDialog
{
public:

    void setupUi(QDialog *CalendarDialog)
    {
        if (CalendarDialog->objectName().isEmpty())
            CalendarDialog->setObjectName("CalendarDialog");
        CalendarDialog->resize(400, 300);

        retranslateUi(CalendarDialog);

        QMetaObject::connectSlotsByName(CalendarDialog);
    } // setupUi

    void retranslateUi(QDialog *CalendarDialog)
    {
        CalendarDialog->setWindowTitle(QCoreApplication::translate("CalendarDialog", "Dialog", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CalendarDialog: public Ui_CalendarDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CALENDARDIALOG_H
