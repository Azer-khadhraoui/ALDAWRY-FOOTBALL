/********************************************************************************
** Form generated from reading UI file 'fieldwidget.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FIELDWIDGET_H
#define UI_FIELDWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FieldWidget
{
public:

    void setupUi(QWidget *FieldWidget)
    {
        if (FieldWidget->objectName().isEmpty())
            FieldWidget->setObjectName("FieldWidget");
        FieldWidget->resize(400, 300);

        retranslateUi(FieldWidget);

        QMetaObject::connectSlotsByName(FieldWidget);
    } // setupUi

    void retranslateUi(QWidget *FieldWidget)
    {
        FieldWidget->setWindowTitle(QCoreApplication::translate("FieldWidget", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class FieldWidget: public Ui_FieldWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FIELDWIDGET_H
