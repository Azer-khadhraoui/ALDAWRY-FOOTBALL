/********************************************************************************
** Form generated from reading UI file 'addPlayer.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDPLAYER_H
#define UI_ADDPLAYER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_addPlayer
{
public:
    QWidget *widget;
    QGridLayout *gridLayout_4;
    QLabel *label_15;
    QLabel *label_16;
    QDateEdit *dateEdit;
    QLabel *label_17;
    QLineEdit *lineEditJersey;
    QLineEdit *lineEditLastName;
    QLineEdit *lineEditNationality;
    QLineEdit *lineEditFirstName;
    QLabel *label_18;
    QComboBox *comboBoxTeam;
    QToolButton *toolButtonImage;
    QLabel *label_19;
    QLabel *label_20;
    QLabel *label_21;
    QLabel *label_22;
    QComboBox *comboBoxPosition;
    QPushButton *addButton;
    QLabel *labelImage;
    QLabel *label_4;
    QLabel *label_28;
    QLabel *label_29;
    QLabel *label_30;
    QLabel *label_31;
    QLabel *label_32;
    QLabel *label_33;
    QLabel *label_34;
    QLabel *label_35;

    void setupUi(QWidget *addPlayer)
    {
        if (addPlayer->objectName().isEmpty())
            addPlayer->setObjectName("addPlayer");
        addPlayer->resize(782, 753);
        addPlayer->setStyleSheet(QString::fromUtf8("background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 #1b1f2a, stop:1 #10131a);"));
        widget = new QWidget(addPlayer);
        widget->setObjectName("widget");
        widget->setGeometry(QRect(20, 90, 541, 641));
        widget->setStyleSheet(QString::fromUtf8("background-color: rgb(25, 31, 42);\n"
"    color: #FFFFFF;\n"
"    font-family: 'Segoe UI', Arial, sans-serif;\n"
"    font-size: 12px;\n"
"    border-radius: 15px;\n"
"    padding: 15px;\n"
"    spacing: 2px;\n"
""));
        gridLayout_4 = new QGridLayout(widget);
        gridLayout_4->setObjectName("gridLayout_4");
        label_15 = new QLabel(widget);
        label_15->setObjectName("label_15");
        label_15->setStyleSheet(QString::fromUtf8("color: #A0A8B7;\n"
"font-weight: bold;\n"
"padding-bottom: 3px;background-color:transparent;"));

        gridLayout_4->addWidget(label_15, 4, 0, 1, 1);

        label_16 = new QLabel(widget);
        label_16->setObjectName("label_16");
        QFont font;
        font.setFamilies({QString::fromUtf8("Segoe UI")});
        font.setBold(true);
        label_16->setFont(font);
        label_16->setStyleSheet(QString::fromUtf8("color: #A0A8B7;\n"
"font-weight: bold;\n"
"padding-bottom: 4px;background-color:transparent;"));

        gridLayout_4->addWidget(label_16, 0, 0, 1, 1);

        dateEdit = new QDateEdit(widget);
        dateEdit->setObjectName("dateEdit");
        dateEdit->setStyleSheet(QString::fromUtf8("background-color: #2A3240;\n"
"  border: 1px solid #3A4A5A;\n"
"    border-radius: 5px;\n"
"    padding: 5px;\n"
"    color: #E0E6ED;\n"
"    margin-left: 15px;\n"
"    margin-right: 15px;\n"
"padding-bottom: 3px;\n"
"\n"
""));

        gridLayout_4->addWidget(dateEdit, 5, 0, 1, 1);

        label_17 = new QLabel(widget);
        label_17->setObjectName("label_17");
        label_17->setStyleSheet(QString::fromUtf8("color: #A0A8B7;\n"
"font-weight: bold;\n"
"padding-bottom: 3px;background-color:transparent;"));

        gridLayout_4->addWidget(label_17, 2, 0, 1, 1);

        lineEditJersey = new QLineEdit(widget);
        lineEditJersey->setObjectName("lineEditJersey");
        lineEditJersey->setStyleSheet(QString::fromUtf8("background-color: #2A3240; /* Darker blue-gray for input fields */\n"
"    border: 1px solid #3A4A5A; /* Subtle blue-gray border */\n"
"    border-radius: 5px;\n"
"    padding: 5px;\n"
"    color: #E0E6ED; /* Light gray text for readability */\n"
"    margin-left: 15px;\n"
"    margin-right: 15px;\n"
""));

        gridLayout_4->addWidget(lineEditJersey, 11, 0, 1, 1);

        lineEditLastName = new QLineEdit(widget);
        lineEditLastName->setObjectName("lineEditLastName");
        lineEditLastName->setStyleSheet(QString::fromUtf8("background-color: #2A3240; /* Darker blue-gray for input fields */\n"
"    border: 1px solid #3A4A5A; /* Subtle blue-gray border */\n"
"    border-radius: 5px;\n"
"    padding: 5px;\n"
"    color: #E0E6ED; /* Light gray text for readability */\n"
"    margin-left: 15px;\n"
"    margin-right: 15px;\n"
""));

        gridLayout_4->addWidget(lineEditLastName, 3, 0, 1, 1);

        lineEditNationality = new QLineEdit(widget);
        lineEditNationality->setObjectName("lineEditNationality");
        lineEditNationality->setStyleSheet(QString::fromUtf8("background-color: #2A3240; /* Darker blue-gray for input fields */\n"
"    border: 1px solid #3A4A5A; /* Subtle blue-gray border */\n"
"    border-radius: 5px;\n"
"    padding: 5px;\n"
"    color: #E0E6ED; /* Light gray text for readability */\n"
"    margin-left: 15px;\n"
"    margin-right: 15px;\n"
""));

        gridLayout_4->addWidget(lineEditNationality, 13, 0, 1, 1);

        lineEditFirstName = new QLineEdit(widget);
        lineEditFirstName->setObjectName("lineEditFirstName");
        lineEditFirstName->setStyleSheet(QString::fromUtf8("background-color: #2A3240; /* Darker blue-gray for input fields */\n"
"    border: 1px solid #3A4A5A; /* Subtle blue-gray border */\n"
"    border-radius: 5px;\n"
"    padding: 5px;\n"
"    color: #E0E6ED; /* Light gray text for readability */\n"
"    margin-left: 15px;\n"
"    margin-right: 15px;\n"
""));

        gridLayout_4->addWidget(lineEditFirstName, 1, 0, 1, 1);

        label_18 = new QLabel(widget);
        label_18->setObjectName("label_18");
        label_18->setStyleSheet(QString::fromUtf8("color: #A0A8B7;\n"
"font-weight: bold;\n"
"padding-bottom: 4px;background-color:transparent;"));

        gridLayout_4->addWidget(label_18, 10, 0, 1, 1);

        comboBoxTeam = new QComboBox(widget);
        comboBoxTeam->addItem(QString());
        comboBoxTeam->setObjectName("comboBoxTeam");
        comboBoxTeam->setStyleSheet(QString::fromUtf8("background-color: #2A3240;\n"
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

        gridLayout_4->addWidget(comboBoxTeam, 7, 0, 1, 1);

        toolButtonImage = new QToolButton(widget);
        toolButtonImage->setObjectName("toolButtonImage");
        toolButtonImage->setStyleSheet(QString::fromUtf8("background-color: #1C1F2A;\n"
"border: 1px solid #2A2D3A;\n"
"border-radius: 5px;\n"
"padding: 3px;\n"
"color: white;\n"
"margin-left: 15px;\n"
"margin-right:15px;\n"
"margin-bottom:6px;"));

        gridLayout_4->addWidget(toolButtonImage, 15, 0, 1, 1);

        label_19 = new QLabel(widget);
        label_19->setObjectName("label_19");
        label_19->setStyleSheet(QString::fromUtf8("color: #A0A8B7;\n"
"font-weight: bold;\n"
"padding-bottom: 5px;background-color:transparent;"));

        gridLayout_4->addWidget(label_19, 8, 0, 1, 1);

        label_20 = new QLabel(widget);
        label_20->setObjectName("label_20");
        label_20->setStyleSheet(QString::fromUtf8("color: #A0A8B7;\n"
"font-weight: bold;\n"
"padding-bottom: 5px;background-color:transparent;"));

        gridLayout_4->addWidget(label_20, 12, 0, 1, 1);

        label_21 = new QLabel(widget);
        label_21->setObjectName("label_21");
        label_21->setStyleSheet(QString::fromUtf8("color: #A0A8B7;\n"
"font-weight: bold;\n"
"padding-bottom: 5px;background-color:transparent;"));

        gridLayout_4->addWidget(label_21, 14, 0, 1, 1);

        label_22 = new QLabel(widget);
        label_22->setObjectName("label_22");
        label_22->setStyleSheet(QString::fromUtf8("color: #A0A8B7;\n"
"font-weight: bold;\n"
"padding-bottom: 5px;background-color:transparent;"));

        gridLayout_4->addWidget(label_22, 6, 0, 1, 1);

        comboBoxPosition = new QComboBox(widget);
        comboBoxPosition->addItem(QString());
        comboBoxPosition->setObjectName("comboBoxPosition");
        comboBoxPosition->setStyleSheet(QString::fromUtf8("background-color: #2A3240;\n"
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

        gridLayout_4->addWidget(comboBoxPosition, 9, 0, 1, 1);

        addButton = new QPushButton(widget);
        addButton->setObjectName("addButton");
        addButton->setStyleSheet(QString::fromUtf8("background-color: #00FF7F; /* Green to match the accent */\n"
"    color: #1A2633; /* Dark blue text for contrast */\n"
"    font-size: 12px;\n"
"    font-weight: bold;\n"
"    border-radius: 5px;\n"
"    padding: 6px 12px;\n"
"    margin-left: 350px;\n"
"    margin-right: 20px;\n"
"    margin-bottom: 5px;"));

        gridLayout_4->addWidget(addButton, 16, 0, 2, 1);

        labelImage = new QLabel(addPlayer);
        labelImage->setObjectName("labelImage");
        labelImage->setGeometry(QRect(590, 560, 161, 171));
        label_4 = new QLabel(addPlayer);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(240, 20, 161, 41));
        QFont font1;
        font1.setBold(true);
        label_4->setFont(font1);
        label_4->setStyleSheet(QString::fromUtf8("/* Style for the Adjust Team title label */\n"
"QLabel#label_4 {\n"
"    background-color: transparent; /* Dark background matching the app */\n"
"    color: #FFFFFF; /* White text for contrast */\n"
"    font-size: 25px; /* Larger font for title emphasis */\n"
"    font-weight: bold; /* Bold for a strong title appearance */\n"
"\n"
"\n"
"    padding: 5px 10px; /* Padding for a balanced look */\n"
"}"));
        label_28 = new QLabel(addPlayer);
        label_28->setObjectName("label_28");
        label_28->setGeometry(QRect(60, 110, 17, 17));
        label_28->setStyleSheet(QString::fromUtf8("color: #B0C0D0;background-color:transparent;"));
        label_28->setPixmap(QPixmap(QString::fromUtf8(":/playerimg/user.png")));
        label_28->setScaledContents(true);
        label_29 = new QLabel(addPlayer);
        label_29->setObjectName("label_29");
        label_29->setGeometry(QRect(61, 185, 17, 17));
        label_29->setStyleSheet(QString::fromUtf8("color: #B0C0D0;background-color:transparent;"));
        label_29->setPixmap(QPixmap(QString::fromUtf8(":/playerimg/user.png")));
        label_29->setScaledContents(true);
        label_30 = new QLabel(addPlayer);
        label_30->setObjectName("label_30");
        label_30->setGeometry(QRect(60, 260, 17, 17));
        label_30->setStyleSheet(QString::fromUtf8("color: #B0C0D0;background-color:transparent;"));
        label_30->setPixmap(QPixmap(QString::fromUtf8(":/playerimg/StartDate.png")));
        label_30->setScaledContents(true);
        label_31 = new QLabel(addPlayer);
        label_31->setObjectName("label_31");
        label_31->setGeometry(QRect(60, 320, 21, 17));
        label_31->setStyleSheet(QString::fromUtf8("color: #B0C0D0;background-color:transparent;"));
        label_31->setPixmap(QPixmap(QString::fromUtf8(":/playerimg/teamName.png")));
        label_31->setScaledContents(true);
        label_32 = new QLabel(addPlayer);
        label_32->setObjectName("label_32");
        label_32->setGeometry(QRect(60, 400, 21, 17));
        label_32->setStyleSheet(QString::fromUtf8("color: #B0C0D0;background-color:transparent;"));
        label_32->setPixmap(QPixmap(QString::fromUtf8(":/playerimg/position.png")));
        label_32->setScaledContents(true);
        label_33 = new QLabel(addPlayer);
        label_33->setObjectName("label_33");
        label_33->setGeometry(QRect(60, 470, 16, 17));
        label_33->setStyleSheet(QString::fromUtf8("color: #B0C0D0;background-color:transparent;"));
        label_33->setPixmap(QPixmap(QString::fromUtf8(":/playerimg/numbers.png")));
        label_33->setScaledContents(true);
        label_34 = new QLabel(addPlayer);
        label_34->setObjectName("label_34");
        label_34->setGeometry(QRect(60, 546, 21, 21));
        label_34->setStyleSheet(QString::fromUtf8("color: #B0C0D0;background-color:transparent;"));
        label_34->setPixmap(QPixmap(QString::fromUtf8(":/playerimg/nationality.png")));
        label_34->setScaledContents(true);
        label_35 = new QLabel(addPlayer);
        label_35->setObjectName("label_35");
        label_35->setGeometry(QRect(57, 622, 21, 18));
        label_35->setStyleSheet(QString::fromUtf8("color: #B0C0D0;background-color:transparent;"));
        label_35->setPixmap(QPixmap(QString::fromUtf8(":/playerimg/cam.png")));
        label_35->setScaledContents(true);

        retranslateUi(addPlayer);

        QMetaObject::connectSlotsByName(addPlayer);
    } // setupUi

    void retranslateUi(QWidget *addPlayer)
    {
        addPlayer->setWindowTitle(QCoreApplication::translate("addPlayer", "Form", nullptr));
        label_15->setText(QCoreApplication::translate("addPlayer", "               Date_Of_Birth :", nullptr));
        label_16->setText(QCoreApplication::translate("addPlayer", "               First_Name :", nullptr));
        label_17->setText(QCoreApplication::translate("addPlayer", "               Last_Name :", nullptr));
        label_18->setText(QCoreApplication::translate("addPlayer", "               Jersey_Nb :", nullptr));
        comboBoxTeam->setItemText(0, QCoreApplication::translate("addPlayer", "RMD", nullptr));

        toolButtonImage->setText(QCoreApplication::translate("addPlayer", "...", nullptr));
        label_19->setText(QCoreApplication::translate("addPlayer", "               Position", nullptr));
        label_20->setText(QCoreApplication::translate("addPlayer", "               Nationality :", nullptr));
        label_21->setText(QCoreApplication::translate("addPlayer", "               Player_Photo :", nullptr));
        label_22->setText(QCoreApplication::translate("addPlayer", "               Team :", nullptr));
        comboBoxPosition->setItemText(0, QCoreApplication::translate("addPlayer", "Goalkeeper", nullptr));

        addButton->setText(QCoreApplication::translate("addPlayer", "Confirm", nullptr));
        labelImage->setText(QString());
        label_4->setText(QCoreApplication::translate("addPlayer", "Add Player", nullptr));
        label_28->setText(QString());
        label_29->setText(QString());
        label_30->setText(QString());
        label_31->setText(QString());
        label_32->setText(QString());
        label_33->setText(QString());
        label_34->setText(QString());
        label_35->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class addPlayer: public Ui_addPlayer {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDPLAYER_H
