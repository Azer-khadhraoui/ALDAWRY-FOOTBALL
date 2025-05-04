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
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_deletewindow
{
public:
    QVBoxLayout *verticalLayout;
    QWidget *widget;
    QLabel *label;
    QWidget *widget1;
    QHBoxLayout *horizontalLayout;
    QPushButton *cancelButton;
    QPushButton *deleteButton;

    void setupUi(QDialog *deletewindow)
    {
        if (deletewindow->objectName().isEmpty())
            deletewindow->setObjectName("deletewindow");
        deletewindow->resize(337, 172);
        deletewindow->setStyleSheet(QString::fromUtf8("background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 #1b1f2a, stop:1 #10131a);"));
        verticalLayout = new QVBoxLayout(deletewindow);
        verticalLayout->setObjectName("verticalLayout");
        widget = new QWidget(deletewindow);
        widget->setObjectName("widget");
        widget->setStyleSheet(QString::fromUtf8("background-color: rgb(25, 31, 42);\n"
"    color: #FFFFFF;\n"
"    font-family: 'Segoe UI', Arial, sans-serif;\n"
"    font-size: 12px;\n"
"    border-radius: 15px;\n"
"    padding: 15px;\n"
"    spacing: 2px;\n"
""));
        label = new QLabel(widget);
        label->setObjectName("label");
        label->setGeometry(QRect(0, 10, 321, 46));
        QFont font;
        font.setFamilies({QString::fromUtf8("Segoe UI")});
        font.setBold(true);
        label->setFont(font);
        label->setStyleSheet(QString::fromUtf8("background-color: transparent;"));
        label->setAlignment(Qt::AlignmentFlag::AlignCenter);
        widget1 = new QWidget(widget);
        widget1->setObjectName("widget1");
        widget1->setGeometry(QRect(30, 100, 251, 48));
        horizontalLayout = new QHBoxLayout(widget1);
        horizontalLayout->setObjectName("horizontalLayout");
        cancelButton = new QPushButton(widget1);
        cancelButton->setObjectName("cancelButton");
        cancelButton->setStyleSheet(QString::fromUtf8("background-color: rgb(126, 126, 126);\n"
"color: rgb(255, 255, 255);"));

        horizontalLayout->addWidget(cancelButton);

        deleteButton = new QPushButton(widget1);
        deleteButton->setObjectName("deleteButton");
        deleteButton->setStyleSheet(QString::fromUtf8("background-color: red;\n"
"color: white;"));

        horizontalLayout->addWidget(deleteButton);


        verticalLayout->addWidget(widget);


        retranslateUi(deletewindow);

        QMetaObject::connectSlotsByName(deletewindow);
    } // setupUi

    void retranslateUi(QDialog *deletewindow)
    {
        deletewindow->setWindowTitle(QCoreApplication::translate("deletewindow", "Delete Item", nullptr));
#if QT_CONFIG(tooltip)
        label->setToolTip(QCoreApplication::translate("deletewindow", "This action cannot be undone.", nullptr));
#endif // QT_CONFIG(tooltip)
        label->setText(QCoreApplication::translate("deletewindow", "Are you sure you want to delete this competition  ?", nullptr));
#if QT_CONFIG(tooltip)
        cancelButton->setToolTip(QCoreApplication::translate("deletewindow", "Click to cancel the operation.", nullptr));
#endif // QT_CONFIG(tooltip)
        cancelButton->setText(QCoreApplication::translate("deletewindow", "Cancel", nullptr));
#if QT_CONFIG(tooltip)
        deleteButton->setToolTip(QCoreApplication::translate("deletewindow", "Click to delete the item.", nullptr));
#endif // QT_CONFIG(tooltip)
        deleteButton->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class deletewindow: public Ui_deletewindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DELETEWINDOW_H
