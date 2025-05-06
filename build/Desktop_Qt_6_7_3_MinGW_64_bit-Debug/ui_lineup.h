/********************************************************************************
** Form generated from reading UI file 'lineup.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LINEUP_H
#define UI_LINEUP_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_lineup
{
public:

    void setupUi(QWidget *lineup)
    {
        if (lineup->objectName().isEmpty())
            lineup->setObjectName("lineup");
        lineup->resize(400, 300);

        retranslateUi(lineup);

        QMetaObject::connectSlotsByName(lineup);
    } // setupUi

    void retranslateUi(QWidget *lineup)
    {
        lineup->setWindowTitle(QCoreApplication::translate("lineup", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class lineup: public Ui_lineup {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LINEUP_H
