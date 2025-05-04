/********************************************************************************
** Form generated from reading UI file 'statistics.ui'
**
** Created by: Qt User Interface Compiler version 6.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STATISTICS_H
#define UI_STATISTICS_H

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

class Ui_statistics
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

    void setupUi(QDialog *statistics)
    {
        if (statistics->objectName().isEmpty())
            statistics->setObjectName("statistics");
        statistics->resize(700, 479);
        verticalLayout = new QVBoxLayout(statistics);
        verticalLayout->setObjectName("verticalLayout");
        comboBox = new QComboBox(statistics);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName("comboBox");

        verticalLayout->addWidget(comboBox);

        dateTimeLabel = new QLabel(statistics);
        dateTimeLabel->setObjectName("dateTimeLabel");
        dateTimeLabel->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTop|Qt::AlignmentFlag::AlignTrailing);

        verticalLayout->addWidget(dateTimeLabel);

        chartWidget = new QChartView(statistics);
        chartWidget->setObjectName("chartWidget");

        verticalLayout->addWidget(chartWidget);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        previousButton = new QPushButton(statistics);
        previousButton->setObjectName("previousButton");

        horizontalLayout->addWidget(previousButton);

        nextButton = new QPushButton(statistics);
        nextButton->setObjectName("nextButton");

        horizontalLayout->addWidget(nextButton);

        exportButton = new QPushButton(statistics);
        exportButton->setObjectName("exportButton");

        horizontalLayout->addWidget(exportButton);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(statistics);

        QMetaObject::connectSlotsByName(statistics);
    } // setupUi

    void retranslateUi(QDialog *statistics)
    {
        statistics->setWindowTitle(QCoreApplication::translate("statistics", "Competition Statistics", nullptr));
        statistics->setStyleSheet(QCoreApplication::translate("statistics", "background-color: #1A3C34; color: #E0E0E0;", nullptr));
        comboBox->setItemText(0, QCoreApplication::translate("statistics", "Type", nullptr));
        comboBox->setItemText(1, QCoreApplication::translate("statistics", "League", nullptr));
        comboBox->setItemText(2, QCoreApplication::translate("statistics", "Tournement", nullptr));

        dateTimeLabel->setStyleSheet(QCoreApplication::translate("statistics", "color: #E0E0E0; padding: 5px;", nullptr));
        previousButton->setStyleSheet(QCoreApplication::translate("statistics", "background-color: #2E6659; color: #E0E0E0; border: 1px solid #3D8B7A; padding: 5px;", nullptr));
        previousButton->setText(QCoreApplication::translate("statistics", "Previous", nullptr));
        nextButton->setStyleSheet(QCoreApplication::translate("statistics", "background-color: #2E6659; color: #E0E0E0; border: 1px solid #3D8B7A; padding: 5px;", nullptr));
        nextButton->setText(QCoreApplication::translate("statistics", "Next", nullptr));
        exportButton->setStyleSheet(QCoreApplication::translate("statistics", "background-color: #2E6659; color: #E0E0E0; border: 1px solid #3D8B7A; padding: 5px;", nullptr));
        exportButton->setText(QCoreApplication::translate("statistics", "Export Chart", nullptr));
    } // retranslateUi

};

namespace Ui {
    class statistics: public Ui_statistics {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STATISTICS_H
