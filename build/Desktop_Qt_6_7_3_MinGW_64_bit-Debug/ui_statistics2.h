/********************************************************************************
** Form generated from reading UI file 'statistics2.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STATISTICS2_H
#define UI_STATISTICS2_H

#include <QtCharts/QChartView>
#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_statistics2
{
public:
    QVBoxLayout *verticalLayout;
    QComboBox *comboBox;
    QLabel *dateTimeLabel;
    QChartView *chartWidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *previousButton;
    QPushButton *nextButton;
    QPushButton *exportButton;

    void setupUi(QDialog *statistics2)
    {
        if (statistics2->objectName().isEmpty())
            statistics2->setObjectName("statistics2");
        statistics2->resize(700, 500);
        verticalLayout = new QVBoxLayout(statistics2);
        verticalLayout->setObjectName("verticalLayout");
        comboBox = new QComboBox(statistics2);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName("comboBox");

        verticalLayout->addWidget(comboBox);

        dateTimeLabel = new QLabel(statistics2);
        dateTimeLabel->setObjectName("dateTimeLabel");
        dateTimeLabel->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTop|Qt::AlignmentFlag::AlignTrailing);

        verticalLayout->addWidget(dateTimeLabel);

        chartWidget = new QChartView(statistics2);
        chartWidget->setObjectName("chartWidget");

        verticalLayout->addWidget(chartWidget);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        previousButton = new QPushButton(statistics2);
        previousButton->setObjectName("previousButton");

        horizontalLayout->addWidget(previousButton);

        nextButton = new QPushButton(statistics2);
        nextButton->setObjectName("nextButton");

        horizontalLayout->addWidget(nextButton);

        exportButton = new QPushButton(statistics2);
        exportButton->setObjectName("exportButton");

        horizontalLayout->addWidget(exportButton);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(statistics2);

        QMetaObject::connectSlotsByName(statistics2);
    } // setupUi

    void retranslateUi(QDialog *statistics2)
    {
        statistics2->setWindowTitle(QCoreApplication::translate("statistics2", "Competition Statistics", nullptr));
        statistics2->setStyleSheet(QCoreApplication::translate("statistics2", "background-color: #1A3C34; color: #E0E0E0;", nullptr));
        comboBox->setItemText(0, QCoreApplication::translate("statistics2", "Type", nullptr));
        comboBox->setItemText(1, QCoreApplication::translate("statistics2", "League", nullptr));
        comboBox->setItemText(2, QCoreApplication::translate("statistics2", "Tournament", nullptr));

        dateTimeLabel->setStyleSheet(QCoreApplication::translate("statistics2", "color: #E0E0E0; padding: 5px;", nullptr));
        previousButton->setStyleSheet(QCoreApplication::translate("statistics2", "background-color: #2E6659; color: #E0E0E0; border: 1px solid #3D8B7A; padding: 5px;", nullptr));
        previousButton->setText(QCoreApplication::translate("statistics2", "Previous", nullptr));
        nextButton->setStyleSheet(QCoreApplication::translate("statistics2", "background-color: #2E6659; color: #E0E0E0; border: 1px solid #3D8B7A; padding: 5px;", nullptr));
        nextButton->setText(QCoreApplication::translate("statistics2", "Next", nullptr));
        exportButton->setStyleSheet(QCoreApplication::translate("statistics2", "background-color: #2E6659; color: #E0E0E0; border: 1px solid #3D8B7A; padding: 5px;", nullptr));
        exportButton->setText(QCoreApplication::translate("statistics2", "Export Chart", nullptr));
    } // retranslateUi

};

namespace Ui {
    class statistics2: public Ui_statistics2 {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STATISTICS2_H
