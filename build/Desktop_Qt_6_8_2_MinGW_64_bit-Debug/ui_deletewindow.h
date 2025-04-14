/********************************************************************************
** Form generated from reading UI file 'deletewindow.ui'
**
** Created by: Qt User Interface Compiler version 6.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DELETEWINDOW_H
#define UI_DELETEWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_deletewindow
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QHBoxLayout *horizontalLayout;
    QPushButton *deleteButton;
    QPushButton *cancelButton;

    void setupUi(QDialog *deletewindow)
    {
        if (deletewindow->objectName().isEmpty())
            deletewindow->setObjectName("deletewindow");
        deletewindow->resize(400, 200);
        verticalLayout = new QVBoxLayout(deletewindow);
        verticalLayout->setObjectName("verticalLayout");
        label = new QLabel(deletewindow);
        label->setObjectName("label");
        label->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout->addWidget(label);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        deleteButton = new QPushButton(deletewindow);
        deleteButton->setObjectName("deleteButton");

        horizontalLayout->addWidget(deleteButton);

        cancelButton = new QPushButton(deletewindow);
        cancelButton->setObjectName("cancelButton");

        horizontalLayout->addWidget(cancelButton);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(deletewindow);

        QMetaObject::connectSlotsByName(deletewindow);
    } // setupUi

    void retranslateUi(QDialog *deletewindow)
    {
        deletewindow->setWindowTitle(QCoreApplication::translate("deletewindow", "Delete Item", nullptr));
#if QT_CONFIG(tooltip)
        label->setToolTip(QCoreApplication::translate("deletewindow", "This action cannot be undone.", nullptr));
#endif // QT_CONFIG(tooltip)
        label->setText(QCoreApplication::translate("deletewindow", "Are you sure you want to delete this competition?", nullptr));
#if QT_CONFIG(tooltip)
        deleteButton->setToolTip(QCoreApplication::translate("deletewindow", "Click to delete the item.", nullptr));
#endif // QT_CONFIG(tooltip)
        deleteButton->setStyleSheet(QCoreApplication::translate("deletewindow", "background-color: red; color: white;", nullptr));
        deleteButton->setText(QCoreApplication::translate("deletewindow", "Delete", nullptr));
#if QT_CONFIG(tooltip)
        cancelButton->setToolTip(QCoreApplication::translate("deletewindow", "Click to cancel the operation.", nullptr));
#endif // QT_CONFIG(tooltip)
        cancelButton->setText(QCoreApplication::translate("deletewindow", "Cancel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class deletewindow: public Ui_deletewindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DELETEWINDOW_H
