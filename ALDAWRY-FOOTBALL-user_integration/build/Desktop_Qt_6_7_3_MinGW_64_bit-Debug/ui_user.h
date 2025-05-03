/********************************************************************************
** Form generated from reading UI file 'user.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_USER_H
#define UI_USER_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QTabWidget *tabWidget;
    QWidget *tab;
    QWidget *widget;
    QGridLayout *gridLayout_3;
    QLabel *label_3;
    QDateEdit *birthday;
    QLineEdit *email;
    QLineEdit *nom;
    QLabel *label_5;
    QLabel *label_6;
    QLineEdit *prenom;
    QLabel *label_9;
    QLabel *label_7;
    QLabel *label_8;
    QLabel *label_4;
    QLineEdit *password;
    QLineEdit *number;
    QComboBox *Role;
    QPushButton *button1;
    QPushButton *uploadPhotoButton;
    QWidget *tab_2;
    QWidget *widget_2;
    QGridLayout *gridLayout_4;
    QLabel *label_10;
    QLineEdit *lineEdit_3;
    QLabel *label_11;
    QLineEdit *lineEdit_4;
    QLabel *label_12;
    QLineEdit *lineEdit_6;
    QLabel *label_13;
    QLineEdit *lineEdit_8;
    QLabel *label_14;
    QLineEdit *lineEdit_7;
    QLabel *label_15;
    QDateEdit *dateEdit;
    QLabel *label_16;
    QComboBox *comboBox_3;
    QPushButton *pushButton_2;
    QPushButton *modifyUploadPhotoButton;
    QWidget *tab_4;
    QTableView *tableView_3;
    QLabel *photoLabel;
    QFrame *frame_5;
    QLineEdit *lineEdit_10;
    QLabel *label_20;
    QPushButton *searchButton;
    QPushButton *pushButton_3;
    QPushButton *pdfButton;
    QPushButton *statButton;
    QWidget *tab_5;
    QWidget *statsWidget;
    QLabel *currentUserPhotoLabel;
    QPushButton *pushButton;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1251, 741);
        MainWindow->setStyleSheet(QString::fromUtf8("background: linear-gradient(135deg, #0F111A 0%, #1A1C2A 100%);\n"
"color: #FFFFFF;"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName("tabWidget");
        tabWidget->setGeometry(QRect(0, 0, 1251, 741));
        tabWidget->setStyleSheet(QString::fromUtf8("QTabWidget::pane {\n"
" background: linear-gradient(135deg, #0F111A 0%, #1A1C2A 100%);\n"
" border: 1px solid #2A2D3A;\n"
" border-radius: 10px;\n"
"}\n"
"QTabBar::tab {\n"
" background: #1E1F2D;\n"
" color: #B0BEC5;\n"
" padding: 10px 20px;\n"
" margin: 2px;\n"
" border-radius: 8px;\n"
" font-size: 14px;\n"
"}\n"
"QTabBar::tab:selected {\n"
" background: #0288D1;\n"
" color: #FFFFFF;\n"
"}\n"
"QTabBar::tab:hover {\n"
" background: #2A2D3A;\n"
"}"));
        tab = new QWidget();
        tab->setObjectName("tab");
        widget = new QWidget(tab);
        widget->setObjectName("widget");
        widget->setGeometry(QRect(170, 10, 651, 671));
        widget->setStyleSheet(QString::fromUtf8("background: linear-gradient(145deg, #141821 0%, #1E1F2D 100%);\n"
"color: #FFFFFF;\n"
"font-family: 'Segoe UI', Arial, sans-serif;\n"
"font-size: 12px;\n"
"border-radius: 15px;\n"
"padding: 20px;\n"
"box-shadow: 0 4px 15px rgba(0, 0, 0, 0.3);"));
        gridLayout_3 = new QGridLayout(widget);
        gridLayout_3->setObjectName("gridLayout_3");
        label_3 = new QLabel(widget);
        label_3->setObjectName("label_3");
        label_3->setStyleSheet(QString::fromUtf8("color: #CFD8DC;\n"
"font-size: 14px;\n"
"font-weight: 500;"));

        gridLayout_3->addWidget(label_3, 0, 0, 1, 1);

        birthday = new QDateEdit(widget);
        birthday->setObjectName("birthday");
        birthday->setStyleSheet(QString::fromUtf8("background: #1E1F2D;\n"
"border: 1px solid #3A3D4A;\n"
"border-radius: 8px;\n"
"padding: 8px 12px;\n"
"font-size: 14px;\n"
"color: #FFFFFF;\n"
"}\n"
"QDateEdit::drop-down {\n"
" width: 20px;\n"
"}\n"
"QDateEdit:focus {\n"
" border-color: #0288D1;\n"
" box-shadow: 0 0 5px rgba(2, 136, 209, 0.5);\n"
"}"));
        birthday->setCalendarPopup(true);

        gridLayout_3->addWidget(birthday, 11, 0, 1, 1);

        email = new QLineEdit(widget);
        email->setObjectName("email");
        email->setStyleSheet(QString::fromUtf8("background: #1E1F2D;\n"
"border: 1px solid #3A3D4A;\n"
"border-radius: 8px;\n"
"padding: 8px 12px;\n"
"font-size: 14px;\n"
"color: #FFFFFF;\n"
"transition: border-color 0.3s;\n"
"}\n"
"QLineEdit:focus {\n"
" border-color: #0288D1;\n"
" box-shadow: 0 0 5px rgba(2, 136, 209, 0.5);\n"
"}"));

        gridLayout_3->addWidget(email, 5, 0, 1, 1);

        nom = new QLineEdit(widget);
        nom->setObjectName("nom");
        nom->setStyleSheet(QString::fromUtf8("background: #1E1F2D;\n"
"border: 1px solid #3A3D4A;\n"
"border-radius: 8px;\n"
"padding: 8px 12px;\n"
"font-size: 14px;\n"
"color: #FFFFFF;\n"
"transition: border-color 0.3s;\n"
"}\n"
"QLineEdit:focus {\n"
" border-color: #0288D1;\n"
" box-shadow: 0 0 5px rgba(2, 136, 209, 0.5);\n"
"}"));

        gridLayout_3->addWidget(nom, 1, 0, 1, 1);

        label_5 = new QLabel(widget);
        label_5->setObjectName("label_5");
        label_5->setStyleSheet(QString::fromUtf8("color: #CFD8DC;\n"
"font-size: 14px;\n"
"font-weight: 500;"));

        gridLayout_3->addWidget(label_5, 4, 0, 1, 1);

        label_6 = new QLabel(widget);
        label_6->setObjectName("label_6");
        label_6->setStyleSheet(QString::fromUtf8("color: #CFD8DC;\n"
"font-size: 14px;\n"
"font-weight: 500;"));

        gridLayout_3->addWidget(label_6, 6, 0, 1, 1);

        prenom = new QLineEdit(widget);
        prenom->setObjectName("prenom");
        prenom->setStyleSheet(QString::fromUtf8("background: #1E1F2D;\n"
"border: 1px solid #3A3D4A;\n"
"border-radius: 8px;\n"
"padding: 8px 12px;\n"
"font-size: 14px;\n"
"color: #FFFFFF;\n"
"transition: border-color 0.3s;\n"
"}\n"
"QLineEdit:focus {\n"
" border-color: #0288D1;\n"
" box-shadow: 0 0 5px rgba(2, 136, 209, 0.5);\n"
"}"));

        gridLayout_3->addWidget(prenom, 3, 0, 1, 1);

        label_9 = new QLabel(widget);
        label_9->setObjectName("label_9");
        label_9->setStyleSheet(QString::fromUtf8("color: #CFD8DC;\n"
"font-size: 14px;\n"
"font-weight: 500;"));

        gridLayout_3->addWidget(label_9, 12, 0, 1, 1);

        label_7 = new QLabel(widget);
        label_7->setObjectName("label_7");
        label_7->setStyleSheet(QString::fromUtf8("color: #CFD8DC;\n"
"font-size: 14px;\n"
"font-weight: 500;"));

        gridLayout_3->addWidget(label_7, 8, 0, 1, 1);

        label_8 = new QLabel(widget);
        label_8->setObjectName("label_8");
        label_8->setStyleSheet(QString::fromUtf8("color: #CFD8DC;\n"
"font-size: 14px;\n"
"font-weight: 500;"));

        gridLayout_3->addWidget(label_8, 10, 0, 1, 1);

        label_4 = new QLabel(widget);
        label_4->setObjectName("label_4");
        label_4->setStyleSheet(QString::fromUtf8("color: #CFD8DC;\n"
"font-size: 14px;\n"
"font-weight: 500;"));

        gridLayout_3->addWidget(label_4, 2, 0, 1, 1);

        password = new QLineEdit(widget);
        password->setObjectName("password");
        password->setStyleSheet(QString::fromUtf8("background: #1E1F2D;\n"
"border: 1px solid #3A3D4A;\n"
"border-radius: 8px;\n"
"padding: 8px 12px;\n"
"font-size: 14px;\n"
"color: #FFFFFF;\n"
"transition: border-color 0.3s;\n"
"}\n"
"QLineEdit:focus {\n"
" border-color: #0288D1;\n"
" box-shadow: 0 0 5px rgba(2, 136, 209, 0.5);\n"
"}"));
        password->setEchoMode(QLineEdit::EchoMode::Password);

        gridLayout_3->addWidget(password, 9, 0, 1, 1);

        number = new QLineEdit(widget);
        number->setObjectName("number");
        number->setStyleSheet(QString::fromUtf8("background: #1E1F2D;\n"
"border: 1px solid #3A3D4A;\n"
"border-radius: 8px;\n"
"padding: 8px 12px;\n"
"font-size: 14px;\n"
"color: #FFFFFF;\n"
"transition: border-color 0.3s;\n"
"}\n"
"QLineEdit:focus {\n"
" border-color: #0288D1;\n"
" box-shadow: 0 0 5px rgba(2, 136, 209, 0.5);\n"
"}"));

        gridLayout_3->addWidget(number, 7, 0, 1, 1);

        Role = new QComboBox(widget);
        Role->addItem(QString());
        Role->addItem(QString());
        Role->addItem(QString());
        Role->setObjectName("Role");
        Role->setStyleSheet(QString::fromUtf8("background: #1E1F2D;\n"
"border: 1px solid #3A3D4A;\n"
"border-radius: 8px;\n"
"padding: 8px 12px;\n"
"font-size: 14px;\n"
"color: #FFFFFF;\n"
"}\n"
"QComboBox::drop-down {\n"
" width: 20px;\n"
"}\n"
"QComboBox:focus {\n"
" border-color: #0288D1;\n"
" box-shadow: 0 0 5px rgba(2, 136, 209, 0.5);\n"
"}\n"
"QComboBox QAbstractItemView {\n"
" background: #1E1F2D;\n"
" color: #FFFFFF;\n"
" selection-background-color: #0288D1;\n"
"}"));

        gridLayout_3->addWidget(Role, 13, 0, 1, 1);

        button1 = new QPushButton(tab);
        button1->setObjectName("button1");
        button1->setGeometry(QRect(890, 510, 241, 35));
        button1->setStyleSheet(QString::fromUtf8("background: linear-gradient(45deg, #0288D1 0%, #03A9F4 100%);\n"
"color: #FFFFFF;\n"
"font-size: 14px;\n"
"font-weight: 500;\n"
"border-radius: 8px;\n"
"padding: 10px 20px;\n"
"margin: 10px 15px;\n"
"transition: background 0.3s, transform 0.2s;\n"
"}\n"
"QPushButton:hover {\n"
" background: linear-gradient(45deg, #03A9F4 0%, #4FC3F7 100%);\n"
" transform: scale(1.05);\n"
"}\n"
"QPushButton:pressed {\n"
" background: linear-gradient(45deg, #01579B 0%, #0288D1 100%);\n"
" transform: scale(0.95);\n"
"}"));
        uploadPhotoButton = new QPushButton(tab);
        uploadPhotoButton->setObjectName("uploadPhotoButton");
        uploadPhotoButton->setGeometry(QRect(880, 390, 291, 38));
        uploadPhotoButton->setStyleSheet(QString::fromUtf8("background: linear-gradient(45deg, #0288D1 0%, #03A9F4 100%);\n"
"color: #FFFFFF;\n"
"font-size: 14px;\n"
"font-weight: 500;\n"
"border-radius: 8px;\n"
"padding: 10px 20px;\n"
"margin: 10px 15px;\n"
"transition: background 0.3s, transform 0.2s;\n"
"}\n"
"QPushButton:hover {\n"
" background: linear-gradient(45deg, #03A9F4 0%, #4FC3F7 100%);\n"
" transform: scale(1.05);\n"
"}\n"
"QPushButton:pressed {\n"
" background: linear-gradient(45deg, #01579B 0%, #0288D1 100%);\n"
" transform: scale(0.95);\n"
"}"));
        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName("tab_2");
        widget_2 = new QWidget(tab_2);
        widget_2->setObjectName("widget_2");
        widget_2->setGeometry(QRect(120, 0, 651, 661));
        widget_2->setStyleSheet(QString::fromUtf8("background: linear-gradient(145deg, #141821 0%, #1E1F2D 100%);\n"
"color: #FFFFFF;\n"
"font-family: 'Segoe UI', Arial, sans-serif;\n"
"font-size: 12px;\n"
"border-radius: 15px;\n"
"padding: 20px;\n"
"box-shadow: 0 4px 15px rgba(0, 0, 0, 0.3);"));
        gridLayout_4 = new QGridLayout(widget_2);
        gridLayout_4->setObjectName("gridLayout_4");
        label_10 = new QLabel(widget_2);
        label_10->setObjectName("label_10");
        label_10->setStyleSheet(QString::fromUtf8("color: #CFD8DC;\n"
"font-size: 14px;\n"
"font-weight: 500;"));

        gridLayout_4->addWidget(label_10, 0, 0, 1, 1);

        lineEdit_3 = new QLineEdit(widget_2);
        lineEdit_3->setObjectName("lineEdit_3");
        lineEdit_3->setStyleSheet(QString::fromUtf8("background: #1E1F2D;\n"
"border: 1px solid #3A3D4A;\n"
"border-radius: 8px;\n"
"padding: 8px 12px;\n"
"font-size: 14px;\n"
"color: #FFFFFF;\n"
"transition: border-color 0.3s;\n"
"}\n"
"QLineEdit:focus {\n"
" border-color: #0288D1;\n"
" box-shadow: 0 0 5px rgba(2, 136, 209, 0.5);\n"
"}"));

        gridLayout_4->addWidget(lineEdit_3, 1, 0, 1, 1);

        label_11 = new QLabel(widget_2);
        label_11->setObjectName("label_11");
        label_11->setStyleSheet(QString::fromUtf8("color: #CFD8DC;\n"
"font-size: 14px;\n"
"font-weight: 500;"));

        gridLayout_4->addWidget(label_11, 2, 0, 1, 1);

        lineEdit_4 = new QLineEdit(widget_2);
        lineEdit_4->setObjectName("lineEdit_4");
        lineEdit_4->setStyleSheet(QString::fromUtf8("background: #1E1F2D;\n"
"border: 1px solid #3A3D4A;\n"
"border-radius: 8px;\n"
"padding: 8px 12px;\n"
"font-size: 14px;\n"
"color: #FFFFFF;\n"
"transition: border-color 0.3s;\n"
"}\n"
"QLineEdit:focus {\n"
" border-color: #0288D1;\n"
" box-shadow: 0 0 5px rgba(2, 136, 209, 0.5);\n"
"}"));

        gridLayout_4->addWidget(lineEdit_4, 3, 0, 1, 1);

        label_12 = new QLabel(widget_2);
        label_12->setObjectName("label_12");
        label_12->setStyleSheet(QString::fromUtf8("color: #CFD8DC;\n"
"font-size: 14px;\n"
"font-weight: 500;"));

        gridLayout_4->addWidget(label_12, 4, 0, 1, 1);

        lineEdit_6 = new QLineEdit(widget_2);
        lineEdit_6->setObjectName("lineEdit_6");
        lineEdit_6->setStyleSheet(QString::fromUtf8("background: #1E1F2D;\n"
"border: 1px solid #3A3D4A;\n"
"border-radius: 8px;\n"
"padding: 8px 12px;\n"
"font-size: 14px;\n"
"color: #FFFFFF;\n"
"transition: border-color 0.3s;\n"
"}\n"
"QLineEdit:focus {\n"
" border-color: #0288D1;\n"
" box-shadow: 0 0 5px rgba(2, 136, 209, 0.5);\n"
"}"));

        gridLayout_4->addWidget(lineEdit_6, 5, 0, 1, 1);

        label_13 = new QLabel(widget_2);
        label_13->setObjectName("label_13");
        label_13->setStyleSheet(QString::fromUtf8("color: #CFD8DC;\n"
"font-size: 14px;\n"
"font-weight: 500;"));

        gridLayout_4->addWidget(label_13, 6, 0, 1, 1);

        lineEdit_8 = new QLineEdit(widget_2);
        lineEdit_8->setObjectName("lineEdit_8");
        lineEdit_8->setStyleSheet(QString::fromUtf8("background: #1E1F2D;\n"
"border: 1px solid #3A3D4A;\n"
"border-radius: 8px;\n"
"padding: 8px 12px;\n"
"font-size: 14px;\n"
"color: #FFFFFF;\n"
"transition: border-color 0.3s;\n"
"}\n"
"QLineEdit:focus {\n"
" border-color: #0288D1;\n"
" box-shadow: 0 0 5px rgba(2, 136, 209, 0.5);\n"
"}"));

        gridLayout_4->addWidget(lineEdit_8, 7, 0, 1, 1);

        label_14 = new QLabel(widget_2);
        label_14->setObjectName("label_14");
        label_14->setStyleSheet(QString::fromUtf8("color: #CFD8DC;\n"
"font-size: 14px;\n"
"font-weight: 500;"));

        gridLayout_4->addWidget(label_14, 8, 0, 1, 1);

        lineEdit_7 = new QLineEdit(widget_2);
        lineEdit_7->setObjectName("lineEdit_7");
        lineEdit_7->setStyleSheet(QString::fromUtf8("background: #1E1F2D;\n"
"border: 1px solid #3A3D4A;\n"
"border-radius: 8px;\n"
"padding: 8px 12px;\n"
"font-size: 14px;\n"
"color: #FFFFFF;\n"
"transition: border-color 0.3s;\n"
"}\n"
"QLineEdit:focus {\n"
" border-color: #0288D1;\n"
" box-shadow: 0 0 5px rgba(2, 136, 209, 0.5);\n"
"}"));
        lineEdit_7->setEchoMode(QLineEdit::EchoMode::Password);

        gridLayout_4->addWidget(lineEdit_7, 9, 0, 1, 1);

        label_15 = new QLabel(widget_2);
        label_15->setObjectName("label_15");
        label_15->setStyleSheet(QString::fromUtf8("color: #CFD8DC;\n"
"font-size: 14px;\n"
"font-weight: 500;"));

        gridLayout_4->addWidget(label_15, 10, 0, 1, 1);

        dateEdit = new QDateEdit(widget_2);
        dateEdit->setObjectName("dateEdit");
        dateEdit->setStyleSheet(QString::fromUtf8("background: #1E1F2D;\n"
"border: 1px solid #3A3D4A;\n"
"border-radius: 8px;\n"
"padding: 8px 12px;\n"
"font-size: 14px;\n"
"color: #FFFFFF;\n"
"}\n"
"QDateEdit::drop-down {\n"
" width: 20px;\n"
"}\n"
"QDateEdit:focus {\n"
" border-color: #0288D1;\n"
" box-shadow: 0 0 5px rgba(2, 136, 209, 0.5);\n"
"}"));
        dateEdit->setCalendarPopup(true);

        gridLayout_4->addWidget(dateEdit, 11, 0, 1, 1);

        label_16 = new QLabel(widget_2);
        label_16->setObjectName("label_16");
        label_16->setStyleSheet(QString::fromUtf8("color: #CFD8DC;\n"
"font-size: 14px;\n"
"font-weight: 500;"));

        gridLayout_4->addWidget(label_16, 12, 0, 1, 1);

        comboBox_3 = new QComboBox(widget_2);
        comboBox_3->addItem(QString());
        comboBox_3->addItem(QString());
        comboBox_3->addItem(QString());
        comboBox_3->setObjectName("comboBox_3");
        comboBox_3->setStyleSheet(QString::fromUtf8("background: #1E1F2D;\n"
"border: 1px solid #3A3D4A;\n"
"border-radius: 8px;\n"
"padding: 8px 12px;\n"
"font-size: 14px;\n"
"color: #FFFFFF;\n"
"}\n"
"QComboBox::drop-down {\n"
" width: 20px;\n"
"}\n"
"QComboBox:focus {\n"
" border-color: #0288D1;\n"
" box-shadow: 0 0 5px rgba(2, 136, 209, 0.5);\n"
"}\n"
"QComboBox QAbstractItemView {\n"
" background: #1E1F2D;\n"
" color: #FFFFFF;\n"
" selection-background-color: #0288D1;\n"
"}"));

        gridLayout_4->addWidget(comboBox_3, 13, 0, 1, 1);

        pushButton_2 = new QPushButton(widget_2);
        pushButton_2->setObjectName("pushButton_2");
        pushButton_2->setStyleSheet(QString::fromUtf8("background: linear-gradient(45deg, #0288D1 0%, #03A9F4 100%);\n"
"color: #FFFFFF;\n"
"font-size: 14px;\n"
"font-weight: 500;\n"
"border-radius: 8px;\n"
"padding: 10px 20px;\n"
"margin: 10px 15px;\n"
"transition: background 0.3s, transform 0.2s;\n"
"}\n"
"QPushButton:hover {\n"
" background: linear-gradient(45deg, #03A9F4 0%, #4FC3F7 100%);\n"
" transform: scale(1.05);\n"
"}\n"
"QPushButton:pressed {\n"
" background: linear-gradient(45deg, #01579B 0%, #0288D1 100%);\n"
" transform: scale(0.95);\n"
"}"));

        gridLayout_4->addWidget(pushButton_2, 15, 0, 1, 1);

        modifyUploadPhotoButton = new QPushButton(widget_2);
        modifyUploadPhotoButton->setObjectName("modifyUploadPhotoButton");
        modifyUploadPhotoButton->setStyleSheet(QString::fromUtf8("background: linear-gradient(45deg, #0288D1 0%, #03A9F4 100%);\n"
"color: #FFFFFF;\n"
"font-size: 14px;\n"
"font-weight: 500;\n"
"border-radius: 8px;\n"
"padding: 10px 20px;\n"
"margin: 10px 15px;\n"
"transition: background 0.3s, transform 0.2s;\n"
"}\n"
"QPushButton:hover {\n"
" background: linear-gradient(45deg, #03A9F4 0%, #4FC3F7 100%);\n"
" transform: scale(1.05);\n"
"}\n"
"QPushButton:pressed {\n"
" background: linear-gradient(45deg, #01579B 0%, #0288D1 100%);\n"
" transform: scale(0.95);\n"
"}"));

        gridLayout_4->addWidget(modifyUploadPhotoButton, 16, 0, 1, 1);

        tabWidget->addTab(tab_2, QString());
        tab_4 = new QWidget();
        tab_4->setObjectName("tab_4");
        tableView_3 = new QTableView(tab_4);
        tableView_3->setObjectName("tableView_3");
        tableView_3->setGeometry(QRect(100, 100, 701, 421));
        tableView_3->setStyleSheet(QString::fromUtf8("background: #1E1F2D;\n"
"border: 1px solid #3A3D4A;\n"
"border-radius: 10px;\n"
"color: #FFFFFF;\n"
"}\n"
"QTableView::item {\n"
" padding: 8px;\n"
"}\n"
"QTableView::item:selected {\n"
" background: #0288D1;\n"
" color: #FFFFFF;\n"
"}\n"
"QHeaderView::section {\n"
" background: #2A2D3A;\n"
" color: #CFD8DC;\n"
" padding: 8px;\n"
" border: 1px solid #3A3D4A;\n"
"}"));
        photoLabel = new QLabel(tab_4);
        photoLabel->setObjectName("photoLabel");
        photoLabel->setGeometry(QRect(820, 100, 200, 200));
        photoLabel->setStyleSheet(QString::fromUtf8("background: #1E1F2D;\n"
"border: 1px solid #3A3D4A;\n"
"border-radius: 12px;\n"
"box-shadow: 0 4px 10px rgba(0, 0, 0, 0.2);"));
        photoLabel->setScaledContents(true);
        frame_5 = new QFrame(tab_4);
        frame_5->setObjectName("frame_5");
        frame_5->setGeometry(QRect(340, 30, 331, 61));
        frame_5->setStyleSheet(QString::fromUtf8("background: linear-gradient(145deg, #1E1F2D 0%, #2A2D3A 100%);\n"
"border-radius: 10px;\n"
"box-shadow: 0 4px 10px rgba(0, 0, 0, 0.2);"));
        frame_5->setFrameShape(QFrame::Shape::StyledPanel);
        frame_5->setFrameShadow(QFrame::Shadow::Raised);
        lineEdit_10 = new QLineEdit(frame_5);
        lineEdit_10->setObjectName("lineEdit_10");
        lineEdit_10->setGeometry(QRect(10, 10, 211, 41));
        lineEdit_10->setStyleSheet(QString::fromUtf8("background: #2A2D3A;\n"
"border: 1px solid #3A3D4A;\n"
"border-radius: 8px;\n"
"padding: 8px 12px;\n"
"font-size: 14px;\n"
"color: #FFFFFF;\n"
"transition: border-color 0.3s;\n"
"}\n"
"QLineEdit:focus {\n"
" border-color: #0288D1;\n"
" box-shadow: 0 0 5px rgba(2, 136, 209, 0.5);\n"
"}"));
        label_20 = new QLabel(frame_5);
        label_20->setObjectName("label_20");
        label_20->setGeometry(QRect(300, 20, 18, 18));
        label_20->setStyleSheet(QString::fromUtf8("transition: transform 0.2s;\n"
"}\n"
"QLabel:hover {\n"
" transform: scale(1.2);\n"
"}"));
        label_20->setPixmap(QPixmap(QString::fromUtf8("../../../../../Pictures/proj QT/trier.png")));
        label_20->setScaledContents(true);
        searchButton = new QPushButton(frame_5);
        searchButton->setObjectName("searchButton");
        searchButton->setGeometry(QRect(240, 20, 80, 24));
        searchButton->setStyleSheet(QString::fromUtf8("background: linear-gradient(45deg, #0288D1 0%, #03A9F4 100%);\n"
"color: #FFFFFF;\n"
"font-size: 14px;\n"
"font-weight: 500;\n"
"border-radius: 8px;\n"
"padding: 6px;\n"
"transition: background 0.3s, transform 0.2s;\n"
"}\n"
"QPushButton:hover {\n"
" background: linear-gradient(45deg, #03A9F4 0%, #4FC3F7 100%);\n"
" transform: scale(1.05);\n"
"}\n"
"QPushButton:pressed {\n"
" background: linear-gradient(45deg, #01579B 0%, #0288D1 100%);\n"
" transform: scale(0.95);\n"
"}"));
        pushButton_3 = new QPushButton(tab_4);
        pushButton_3->setObjectName("pushButton_3");
        pushButton_3->setGeometry(QRect(720, 540, 83, 29));
        pushButton_3->setStyleSheet(QString::fromUtf8("background: linear-gradient(45deg, #D32F2F 0%, #F44336 100%);\n"
"color: #FFFFFF;\n"
"font-size: 14px;\n"
"font-weight: 500;\n"
"border-radius: 8px;\n"
"padding: 8px;\n"
"transition: background 0.3s, transform 0.2s;\n"
"}\n"
"QPushButton:hover {\n"
" background: linear-gradient(45deg, #F44336 0%, #EF5350 100%);\n"
" transform: scale(1.05);\n"
"}\n"
"QPushButton:pressed {\n"
" background: linear-gradient(45deg, #B71C1C 0%, #D32F2F 100%);\n"
" transform: scale(0.95);\n"
"}"));
        pdfButton = new QPushButton(tab_4);
        pdfButton->setObjectName("pdfButton");
        pdfButton->setGeometry(QRect(130, 40, 80, 24));
        pdfButton->setStyleSheet(QString::fromUtf8("background: linear-gradient(45deg, #7B1FA2 0%, #9C27B0 100%);\n"
"color: #FFFFFF;\n"
"font-size: 14px;\n"
"font-weight: 500;\n"
"border-radius: 8px;\n"
"padding: 6px;\n"
"transition: background 0.3s, transform 0.2s;\n"
"}\n"
"QPushButton:hover {\n"
" background: linear-gradient(45deg, #9C27B0 0%, #AB47BC 100%);\n"
" transform: scale(1.05);\n"
"}\n"
"QPushButton:pressed {\n"
" background: linear-gradient(45deg, #4A148C 0%, #7B1FA2 100%);\n"
" transform: scale(0.95);\n"
"}"));
        statButton = new QPushButton(tab_4);
        statButton->setObjectName("statButton");
        statButton->setGeometry(QRect(240, 40, 80, 24));
        statButton->setStyleSheet(QString::fromUtf8("background: linear-gradient(45deg, #FBC02D 0%, #FFCA28 100%);\n"
"color: #FFFFFF;\n"
"font-size: 14px;\n"
"font-weight: 500;\n"
"border-radius: 8px;\n"
"padding: 6px;\n"
"transition: background 0.3s, transform 0.2s;\n"
"}\n"
"QPushButton:hover {\n"
" background: linear-gradient(45deg, #FFCA28 0%, #FFD54F 100%);\n"
" transform: scale(1.05);\n"
"}\n"
"QPushButton:pressed {\n"
" background: linear-gradient(45deg, #F57F17 0%, #FBC02D 100%);\n"
" transform: scale(0.95);\n"
"}"));
        tabWidget->addTab(tab_4, QString());
        tab_5 = new QWidget();
        tab_5->setObjectName("tab_5");
        statsWidget = new QWidget(tab_5);
        statsWidget->setObjectName("statsWidget");
        statsWidget->setGeometry(QRect(0, 0, 1251, 741));
        statsWidget->setStyleSheet(QString::fromUtf8("background: linear-gradient(135deg, #0F111A 0%, #1A1C2A 100%);\n"
"border-radius: 10px;"));
        tabWidget->addTab(tab_5, QString());
        currentUserPhotoLabel = new QLabel(centralwidget);
        currentUserPhotoLabel->setObjectName("currentUserPhotoLabel");
        currentUserPhotoLabel->setGeometry(QRect(1080, 20, 60, 60));
        currentUserPhotoLabel->setStyleSheet(QString::fromUtf8("background: #1E1F2D;\n"
"border: 1px solid #3A3D4A;\n"
"border-radius: 12px;\n"
"box-shadow: 0 4px 10px rgba(0, 0, 0, 0.2);"));
        currentUserPhotoLabel->setScaledContents(true);
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(1160, 20, 61, 61));
        pushButton->setStyleSheet(QString::fromUtf8("background: linear-gradient(45deg, #0288D1 0%, #03A9F4 100%);\n"
"border-radius: 30px;\n"
"transition: background 0.3s, transform 0.2s;\n"
"}\n"
"QPushButton:hover {\n"
" background: linear-gradient(45deg, #03A9F4 0%, #4FC3F7 100%);\n"
" transform: scale(1.1);\n"
"}\n"
"QPushButton:pressed {\n"
" background: linear-gradient(45deg, #01579B 0%, #0288D1 100%);\n"
" transform: scale(0.9);\n"
"}"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/images/logout.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButton->setIcon(icon);
        pushButton->setIconSize(QSize(40, 40));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1251, 24));
        menubar->setStyleSheet(QString::fromUtf8("background: #1E1F2D;\n"
"color: #FFFFFF;\n"
"}\n"
"QMenuBar::item {\n"
" padding: 4px 10px;\n"
"}\n"
"QMenuBar::item:selected {\n"
" background: #0288D1;\n"
"}"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        statusbar->setStyleSheet(QString::fromUtf8("background: #1E1F2D;\n"
"color: #CFD8DC;"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "Last Name", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "Email", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "Mobile Number", nullptr));
        label_9->setText(QCoreApplication::translate("MainWindow", "Role", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "Password", nullptr));
        label_8->setText(QCoreApplication::translate("MainWindow", "Birthday", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "First Name", nullptr));
        Role->setItemText(0, QCoreApplication::translate("MainWindow", "Admin", nullptr));
        Role->setItemText(1, QCoreApplication::translate("MainWindow", "Employee", nullptr));
        Role->setItemText(2, QCoreApplication::translate("MainWindow", "Coach", nullptr));

        button1->setText(QCoreApplication::translate("MainWindow", "Confirm", nullptr));
        uploadPhotoButton->setText(QCoreApplication::translate("MainWindow", "Upload Photo", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QCoreApplication::translate("MainWindow", "Add user", nullptr));
        label_10->setText(QCoreApplication::translate("MainWindow", "Last Name", nullptr));
        label_11->setText(QCoreApplication::translate("MainWindow", "First Name", nullptr));
        label_12->setText(QCoreApplication::translate("MainWindow", "Email", nullptr));
        label_13->setText(QCoreApplication::translate("MainWindow", "Mobile Number", nullptr));
        label_14->setText(QCoreApplication::translate("MainWindow", "Password", nullptr));
        label_15->setText(QCoreApplication::translate("MainWindow", "Birthday", nullptr));
        label_16->setText(QCoreApplication::translate("MainWindow", "Role", nullptr));
        comboBox_3->setItemText(0, QCoreApplication::translate("MainWindow", "Admin", nullptr));
        comboBox_3->setItemText(1, QCoreApplication::translate("MainWindow", "Coach", nullptr));
        comboBox_3->setItemText(2, QCoreApplication::translate("MainWindow", "Employee", nullptr));

        pushButton_2->setText(QCoreApplication::translate("MainWindow", "modify", nullptr));
        modifyUploadPhotoButton->setText(QCoreApplication::translate("MainWindow", "Upload Photo", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QCoreApplication::translate("MainWindow", "modify", nullptr));
        photoLabel->setText(QString());
        label_20->setText(QString());
        searchButton->setText(QCoreApplication::translate("MainWindow", "search", nullptr));
        pushButton_3->setText(QCoreApplication::translate("MainWindow", "Delete", nullptr));
        pdfButton->setText(QCoreApplication::translate("MainWindow", "pdf", nullptr));
        statButton->setText(QCoreApplication::translate("MainWindow", "stat", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_4), QCoreApplication::translate("MainWindow", "Display user", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_5), QCoreApplication::translate("MainWindow", "Stats", nullptr));
        currentUserPhotoLabel->setText(QString());
        pushButton->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_USER_H
