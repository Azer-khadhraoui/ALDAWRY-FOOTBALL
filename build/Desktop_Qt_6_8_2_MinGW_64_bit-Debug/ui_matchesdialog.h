/********************************************************************************
** Form generated from reading UI file 'matchesdialog.ui'
**
** Created by: Qt User Interface Compiler version 6.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MATCHESDIALOG_H
#define UI_MATCHESDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_MatchesDialog
{
public:
    QVBoxLayout *verticalLayout;
    QTableWidget *matchTable;
    QPushButton *closeButton;

    void setupUi(QDialog *MatchesDialog)
    {
        if (MatchesDialog->objectName().isEmpty())
            MatchesDialog->setObjectName("MatchesDialog");
        MatchesDialog->resize(600, 400);
        MatchesDialog->setStyleSheet(QString::fromUtf8("background-color: #0d1f2d; color: #e0f7fa;"));
        verticalLayout = new QVBoxLayout(MatchesDialog);
        verticalLayout->setObjectName("verticalLayout");
        matchTable = new QTableWidget(MatchesDialog);
        if (matchTable->columnCount() < 4)
            matchTable->setColumnCount(4);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        matchTable->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        matchTable->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        matchTable->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        matchTable->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        matchTable->setObjectName("matchTable");
        matchTable->setStyleSheet(QString::fromUtf8("background-color: #1e4d4a; border: 1px solid #4dd0e1; color: #e0f7fa;"));
        matchTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
        matchTable->setSelectionMode(QAbstractItemView::NoSelection);
        matchTable->horizontalHeader()->setDefaultSectionSize(120);
        matchTable->horizontalHeader()->setStretchLastSection(true);
        matchTable->verticalHeader()->setVisible(false);

        verticalLayout->addWidget(matchTable);

        closeButton = new QPushButton(MatchesDialog);
        closeButton->setObjectName("closeButton");
        closeButton->setStyleSheet(QString::fromUtf8("background-color: #0288d1; color: #ffffff; border: 1px solid #4dd0e1; border-radius: 4px;"));

        verticalLayout->addWidget(closeButton);


        retranslateUi(MatchesDialog);
        QObject::connect(closeButton, &QPushButton::clicked, MatchesDialog, qOverload<>(&QDialog::accept));

        QMetaObject::connectSlotsByName(MatchesDialog);
    } // setupUi

    void retranslateUi(QDialog *MatchesDialog)
    {
        MatchesDialog->setWindowTitle(QCoreApplication::translate("MatchesDialog", "Matches", nullptr));
        QTableWidgetItem *___qtablewidgetitem = matchTable->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("MatchesDialog", "Date", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = matchTable->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("MatchesDialog", "Team 1", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = matchTable->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("MatchesDialog", "Team 2", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = matchTable->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("MatchesDialog", "Score", nullptr));
        closeButton->setText(QCoreApplication::translate("MatchesDialog", "Close", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MatchesDialog: public Ui_MatchesDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MATCHESDIALOG_H
