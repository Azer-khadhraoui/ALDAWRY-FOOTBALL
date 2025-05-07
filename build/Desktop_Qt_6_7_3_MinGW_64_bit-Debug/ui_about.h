/********************************************************************************
** Form generated from reading UI file 'about.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ABOUT_H
#define UI_ABOUT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_About
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *labelLogo;
    QLabel *labelTitle;
    QLabel *labelDescription;
    QSpacerItem *verticalSpacer;
    QLabel *labelVersion;
    QPushButton *buttonClose;

    void setupUi(QDialog *About)
    {
        if (About->objectName().isEmpty())
            About->setObjectName("About");
        About->resize(450, 350);
        About->setStyleSheet(QString::fromUtf8("QWidget {\n"
"    background-color: #1A2526;\n"
"    color: #FFFFFF;\n"
"}\n"
"QLabel {\n"
"    padding: 10px;\n"
"}\n"
"QPushButton {\n"
"    background-color: #FFA500;\n"
"    color: #FFFFFF;\n"
"    border: none;\n"
"    padding: 5px 15px;\n"
"    border-radius: 5px;\n"
"}\n"
"QPushButton:hover {\n"
"    background-color: #FF8C00;\n"
"}"));
        verticalLayout = new QVBoxLayout(About);
        verticalLayout->setObjectName("verticalLayout");
        labelLogo = new QLabel(About);
        labelLogo->setObjectName("labelLogo");
        labelLogo->setAlignment(Qt::AlignCenter);
        labelLogo->setStyleSheet(QString::fromUtf8("color: #99CC99; background-color: #1A2526;"));

        verticalLayout->addWidget(labelLogo);

        labelTitle = new QLabel(About);
        labelTitle->setObjectName("labelTitle");
        QFont font;
        font.setPointSize(18);
        font.setBold(true);
        labelTitle->setFont(font);
        labelTitle->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(labelTitle);

        labelDescription = new QLabel(About);
        labelDescription->setObjectName("labelDescription");
        labelDescription->setWordWrap(true);
        labelDescription->setStyleSheet(QString::fromUtf8("color: #CCCCCC; background-color: #1A2526;"));

        verticalLayout->addWidget(labelDescription);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        labelVersion = new QLabel(About);
        labelVersion->setObjectName("labelVersion");
        labelVersion->setAlignment(Qt::AlignCenter);
        labelVersion->setStyleSheet(QString::fromUtf8("color: #AAAAAA; background-color: #1A2526;"));

        verticalLayout->addWidget(labelVersion);

        buttonClose = new QPushButton(About);
        buttonClose->setObjectName("buttonClose");

        verticalLayout->addWidget(buttonClose);


        retranslateUi(About);
        QObject::connect(buttonClose, &QPushButton::clicked, About, qOverload<>(&QDialog::close));

        QMetaObject::connectSlotsByName(About);
    } // setupUi

    void retranslateUi(QDialog *About)
    {
        About->setWindowTitle(QCoreApplication::translate("About", "About ALDAWRY Football", nullptr));
        labelLogo->setText(QCoreApplication::translate("About", "[ALDAWRY Football Logo]", nullptr));
        labelTitle->setText(QCoreApplication::translate("About", "About ALDAWRY Football", nullptr));
        labelDescription->setText(QCoreApplication::translate("About", "Welcome to ALDAWRY Football, your all-in-one solution for football management. This application helps you:\n"
"- Organize matches with ease.\n"
"- Manage competitions and schedules.\n"
"- Add and assign players to teams seamlessly.", nullptr));
        labelVersion->setText(QCoreApplication::translate("About", "Version: 1.0.0 | Contact: support@aldawryfootball.com", nullptr));
        buttonClose->setText(QCoreApplication::translate("About", "Close", nullptr));
    } // retranslateUi

};

namespace Ui {
    class About: public Ui_About {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ABOUT_H
