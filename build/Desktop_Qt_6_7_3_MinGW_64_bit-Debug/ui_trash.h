/********************************************************************************
** Form generated from reading UI file 'trash.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TRASH_H
#define UI_TRASH_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Form
{
public:
    QTabWidget *tabWidget;
    QWidget *tab;
    QWidget *widget;
    QGridLayout *gridLayout_3;
    QPushButton *button1;
    QComboBox *cb;
    QLabel *label_10;
    QLineEdit *l1;
    QLabel *label_9;
    QLabel *label_11;
    QLabel *label_7;
    QLabel *label_8;
    QLineEdit *l2;
    QWidget *widget_2;
    QHBoxLayout *horizontalLayout;
    QToolButton *toolButton;
    QLabel *label_2;
    QLineEdit *l2_2;
    QLabel *label_4;
    QLabel *label_19;
    QLabel *label_27;
    QLabel *label_28;
    QLabel *label_29;
    QLabel *label_30;
    QPushButton *resetButton;
    QWidget *tab_2;
    QTableWidget *tableWidget;
    QFrame *frame_5;
    QLineEdit *searchBar;
    QFrame *frame_7;
    QLabel *label_21;
    QPushButton *deleteButton;
    QPushButton *modifyButton;
    QPushButton *downloadButton;
    QPushButton *deleteButton_2;
    QWidget *tab_3;

    void setupUi(QWidget *Form)
    {
        if (Form->objectName().isEmpty())
            Form->setObjectName("Form");
        Form->resize(1345, 701);
        tabWidget = new QTabWidget(Form);
        tabWidget->setObjectName("tabWidget");
        tabWidget->setGeometry(QRect(320, 70, 951, 611));
        tabWidget->setLayoutDirection(Qt::LayoutDirection::LeftToRight);
        tabWidget->setStyleSheet(QString::fromUtf8("/* Style for the QTabWidget pane (content area) */\n"
"QTabWidget#tabWidget::pane {\n"
"    background-color: #1E2633; /* Match the form widget background */\n"
"    border: 2px solid #2A3A4A; /* Subtle blue-gray border */\n"
"    border-radius: 5px;\n"
"}\n"
"\n"
"/* Style for the tab bar (tabs) */\n"
"QTabBar::tab {\n"
"    background-color: #252A38; /* Slightly lighter than the pane */\n"
"    color: #B0C0D0; /* Light grayish-blue for inactive tab text */\n"
"    padding: 10px 20px; /* Increased padding for better spacing */\n"
"    border: 1px solid #2A3A4A; /* Subtle border */\n"
"    border-top-left-radius: 5px;\n"
"    border-top-right-radius: 5px;\n"
"    margin-right: 2px; /* Space between tabs */\n"
"    font-size: 12px;\n"
"    font-weight: 500;\n"
"}\n"
"\n"
"/* Style for the selected tab */\n"
"QTabBar::tab:selected {\n"
"    background-color: #2E3440; /* Darker shade for the active tab */\n"
"    color: #E0E6ED; /* Brighter text for the active tab */\n"
"    font-weight: bold;\n"
"    border-bott"
                        "om: 2px solid #00FF7F; /* Green underline to match the accent */\n"
"}\n"
"\n"
"/* Style for tab on hover */\n"
"QTabBar::tab:hover {\n"
"    background-color: #353F4D; /* Lighter blue-gray on hover */\n"
"    color: #E0E6ED;\n"
"}\n"
"\n"
"/* Style for non-selected tabs */\n"
"QTabBar::tab:!selected {\n"
"    margin-top: 2px; /* Slightly lower non-selected tabs */\n"
"    color: #A0A8B7; /* Dimmer text for non-selected tabs */\n"
"}\n"
"\n"
"/* Style for the tab bar's corner button (if any) */\n"
"QTabWidget#tabWidget QTableCornerButton::section {\n"
"    background-color: #252A38;\n"
"    border: 1px solid #2A3A4A;\n"
"}\n"
"QTabBar::tab:hover {\n"
"    background: #3d5a73; /* Slight highlight on hover */\n"
"}\n"
"\n"
"QTabBar::tab:selected {\n"
"    background: #34495e;\n"
"    font-weight: bold;\n"
"}\n"
"/* Selected tab */\n"
"QTabBar::tab:selected {\n"
"    background: #4a6a89;\n"
"    color: #ffffff;\n"
"}\n"
"\n"
"/* Unselected tabs */\n"
"QTabBar::tab:!selected {\n"
"    margin-top: 2px;\n"
"}"));
        tab = new QWidget();
        tab->setObjectName("tab");
        widget = new QWidget(tab);
        widget->setObjectName("widget");
        widget->setGeometry(QRect(220, 60, 541, 491));
        widget->setStyleSheet(QString::fromUtf8("background-color: rgb(25, 31, 42);\n"
"    color: #FFFFFF;\n"
"    font-family: 'Segoe UI', Arial, sans-serif;\n"
"    font-size: 12px;\n"
"    border-radius: 15px;\n"
"    padding: 15px;\n"
"    spacing: 2px;\n"
""));
        gridLayout_3 = new QGridLayout(widget);
        gridLayout_3->setObjectName("gridLayout_3");
        button1 = new QPushButton(widget);
        button1->setObjectName("button1");
        button1->setStyleSheet(QString::fromUtf8("background-color: #00FF7F; /* Green to match the accent */\n"
"    color: #1A2633; /* Dark blue text for contrast */\n"
"    font-size: 12px;\n"
"    font-weight: bold;\n"
"    border-radius: 5px;\n"
"    padding: 6px 12px;\n"
"    margin-left: 350px;\n"
"    margin-right: 20px;\n"
"    margin-bottom: 5px;"));

        gridLayout_3->addWidget(button1, 10, 0, 1, 1);

        cb = new QComboBox(widget);
        cb->addItem(QString());
        cb->addItem(QString());
        cb->addItem(QString());
        cb->addItem(QString());
        cb->addItem(QString());
        cb->setObjectName("cb");
        cb->setStyleSheet(QString::fromUtf8("background-color: #2A3240;\n"
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

        gridLayout_3->addWidget(cb, 3, 0, 1, 1);

        label_10 = new QLabel(widget);
        label_10->setObjectName("label_10");
        label_10->setStyleSheet(QString::fromUtf8("color: #A0A8B7;\n"
"font-weight: bold;\n"
"padding-bottom: 5px;background-color:transparent;"));

        gridLayout_3->addWidget(label_10, 6, 0, 1, 1);

        l1 = new QLineEdit(widget);
        l1->setObjectName("l1");
        l1->setStyleSheet(QString::fromUtf8("background-color: #2A3240; /* Darker blue-gray for input fields */\n"
"    border: 1px solid #3A4A5A; /* Subtle blue-gray border */\n"
"    border-radius: 5px;\n"
"    padding: 5px;\n"
"    color: #E0E6ED; /* Light gray text for readability */\n"
"    margin-left: 15px;\n"
"    margin-right: 15px;\n"
""));

        gridLayout_3->addWidget(l1, 1, 0, 1, 1);

        label_9 = new QLabel(widget);
        label_9->setObjectName("label_9");
        label_9->setStyleSheet(QString::fromUtf8("color: #A0A8B7;\n"
"font-weight: bold;\n"
"padding-bottom: 5px;background-color:transparent;"));

        gridLayout_3->addWidget(label_9, 4, 0, 1, 1);

        label_11 = new QLabel(widget);
        label_11->setObjectName("label_11");
        label_11->setStyleSheet(QString::fromUtf8("color: #A0A8B7;\n"
"font-weight: bold;\n"
"padding-bottom: 5px;background-color:transparent;"));

        gridLayout_3->addWidget(label_11, 8, 0, 1, 1);

        label_7 = new QLabel(widget);
        label_7->setObjectName("label_7");
        label_7->setStyleSheet(QString::fromUtf8("color: #A0A8B7;\n"
"font-weight: bold;\n"
"padding-bottom: 5px;background-color:transparent;"));

        gridLayout_3->addWidget(label_7, 0, 0, 1, 1);

        label_8 = new QLabel(widget);
        label_8->setObjectName("label_8");
        label_8->setStyleSheet(QString::fromUtf8("color: #A0A8B7;\n"
"font-weight: bold;\n"
"padding-bottom: 5px;background-color:transparent;"));

        gridLayout_3->addWidget(label_8, 2, 0, 1, 1);

        l2 = new QLineEdit(widget);
        l2->setObjectName("l2");
        l2->setStyleSheet(QString::fromUtf8("background-color: #2A3240; /* Darker blue-gray for input fields */\n"
"    border: 1px solid #3A4A5A; /* Subtle blue-gray border */\n"
"    border-radius: 5px;\n"
"    padding: 5px;\n"
"    color: #E0E6ED; /* Light gray text for readability */\n"
"    margin-left: 15px;\n"
"    margin-right: 15px;"));

        gridLayout_3->addWidget(l2, 5, 0, 1, 1);

        widget_2 = new QWidget(widget);
        widget_2->setObjectName("widget_2");
        widget_2->setStyleSheet(QString::fromUtf8("background-color: #2A3240;\n"
"    border: 1px solid #3A4A5A;\n"
"    border-radius: 5px;\n"
"    padding: 3px;\n"
"    color: #E0E6ED;\n"
"    margin-left: 15px;\n"
"    margin-right: 15px;\n"
"    margin-bottom: 15px;"));
        horizontalLayout = new QHBoxLayout(widget_2);
        horizontalLayout->setObjectName("horizontalLayout");
        toolButton = new QToolButton(widget_2);
        toolButton->setObjectName("toolButton");
        toolButton->setStyleSheet(QString::fromUtf8("background-color: #1C1F2A;\n"
"border: 1px solid #2A2D3A;\n"
"border-radius: 5px;\n"
"padding: 3px;\n"
"color: white;\n"
"margin-left: 15px;\n"
"margin-right:15px;\n"
"margin-bottom:15px;"));

        horizontalLayout->addWidget(toolButton);

        label_2 = new QLabel(widget_2);
        label_2->setObjectName("label_2");
        label_2->setStyleSheet(QString::fromUtf8("color: #A0A8B7;\n"
"padding-left: 10px;\n"
"background-color: transparent;"));

        horizontalLayout->addWidget(label_2);


        gridLayout_3->addWidget(widget_2, 7, 0, 1, 1);

        l2_2 = new QLineEdit(widget);
        l2_2->setObjectName("l2_2");
        l2_2->setStyleSheet(QString::fromUtf8("background-color: #2A3240; /* Darker blue-gray for input fields */\n"
"    border: 1px solid #3A4A5A; /* Subtle blue-gray border */\n"
"    border-radius: 5px;\n"
"    padding: 5px;\n"
"    color: #E0E6ED; /* Light gray text for readability */\n"
"    margin-left: 15px;\n"
"    margin-right: 15px;"));

        gridLayout_3->addWidget(l2_2, 9, 0, 1, 1);

        label_4 = new QLabel(tab);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(320, 25, 361, 21));
        QFont font;
        font.setFamilies({QString::fromUtf8("PT Dusky")});
        font.setPointSize(12);
        font.setBold(true);
        label_4->setFont(font);
        label_4->setStyleSheet(QString::fromUtf8("background-color: transparent\n"
";"));
        label_19 = new QLabel(tab);
        label_19->setObjectName("label_19");
        label_19->setGeometry(QRect(250, 170, 17, 17));
        label_19->setStyleSheet(QString::fromUtf8("background-color:transparent;"));
        label_19->setPixmap(QPixmap(QString::fromUtf8(":/img/terrain.png")));
        label_19->setScaledContents(true);
        label_27 = new QLabel(tab);
        label_27->setObjectName("label_27");
        label_27->setGeometry(QRect(250, 250, 12, 18));
        label_27->setStyleSheet(QString::fromUtf8("background-color:transparent;"));
        label_27->setPixmap(QPixmap(QString::fromUtf8(":/img/money.png")));
        label_27->setScaledContents(true);
        label_28 = new QLabel(tab);
        label_28->setObjectName("label_28");
        label_28->setGeometry(QRect(250, 90, 17, 17));
        label_28->setStyleSheet(QString::fromUtf8("color: #B0C0D0;background-color:transparent;"));
        label_28->setPixmap(QPixmap(QString::fromUtf8(":/img/Userr.png")));
        label_28->setScaledContents(true);
        label_29 = new QLabel(tab);
        label_29->setObjectName("label_29");
        label_29->setGeometry(QRect(250, 326, 21, 21));
        label_29->setStyleSheet(QString::fromUtf8("background-color:transparent;"));
        label_29->setPixmap(QPixmap(QString::fromUtf8(":/img/logo.png")));
        label_29->setScaledContents(true);
        label_30 = new QLabel(tab);
        label_30->setObjectName("label_30");
        label_30->setGeometry(QRect(250, 450, 18, 16));
        label_30->setStyleSheet(QString::fromUtf8("background-color:transparent;"));
        label_30->setPixmap(QPixmap(QString::fromUtf8(":/img/abv.png")));
        label_30->setScaledContents(true);
        resetButton = new QPushButton(tab);
        resetButton->setObjectName("resetButton");
        resetButton->setGeometry(QRect(780, 510, 31, 24));
        resetButton->setStyleSheet(QString::fromUtf8("background-color: rgb(132, 132, 132);\n"
"       color: white;            \n"
"        font-family: Arial;      \n"
"        font-size: 12px;        \n"
"       font-weight: bold;      \n"
"        border: 1px solid grey ;\n"
"        border-radius: 5px;      \n"
"        padding: 5px 10px;        \n"
"    \n"
""));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/img/reset.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        resetButton->setIcon(icon);
        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName("tab_2");
        tableWidget = new QTableWidget(tab_2);
        tableWidget->setObjectName("tableWidget");
        tableWidget->setGeometry(QRect(130, 90, 701, 391));
        tableWidget->setStyleSheet(QString::fromUtf8("/* Style for the QTableWidget */\n"
"\n"
"QTableWidget#tableWidget {\n"
"\n"
"background-color: #1E2633; /* Match tab pane and form widget */\n"
"\n"
"border: 2px solid #2A3A4A; /* Subtle blue-gray border */\n"
"\n"
"gridline-color: #3A4A5A; /* Light grid lines */\n"
"\n"
"alternate-background-color: #252A38; /* Alternating row color */\n"
"\n"
"color: #E0E6ED; /* Light gray text */\n"
"\n"
"selection-background-color: #00FF7F; /* Green selection */\n"
"\n"
"selection-color: #1A2633; /* Dark blue text on selection */\n"
"\n"
"border-radius: 5px;\n"
"\n"
"}\n"
"\n"
"QTableWidget#tableWidget::item {\n"
"\n"
"padding: 5px;\n"
"\n"
"border: none; /* Remove individual cell borders */\n"
"\n"
"}\n"
"\n"
"QTableWidget#tableWidget::item:focus {\n"
"\n"
"outline: none; /* Remove focus outline */\n"
"\n"
"}\n"
"\n"
"\n"
"\n"
"/* Style for the table header */\n"
"\n"
"QHeaderView::section {\n"
"\n"
"background-color: #252A38; /* Match alternating row color */\n"
"\n"
"color: #E0E6ED;\n"
"\n"
"border: 1px solid #2A3A4A;\n"
""
                        "\n"
"padding: 4px;\n"
"\n"
"font-weight: bold;\n"
"\n"
"border-radius: 0;\n"
"\n"
"}\n"
"\n"
"QTableWidget#tableWidget QTableCornerButton::section {\n"
"\n"
"background-color: #252A38;\n"
"\n"
"border: 1px solid #2A3A4A;\n"
"\n"
"}"));
        frame_5 = new QFrame(tab_2);
        frame_5->setObjectName("frame_5");
        frame_5->setGeometry(QRect(500, 30, 325, 48));
        frame_5->setStyleSheet(QString::fromUtf8("QFrame#frame_5 {\n"
"    background-color: #1a212c; /* Dark background to match the page */\n"
"    border: 1px solid #4A5E61; /* Slightly lighter border to match other elements */\n"
"    border-radius: 8px; /* Rounded corners to match the page's design */\n"
"}"));
        frame_5->setFrameShape(QFrame::Shape::StyledPanel);
        frame_5->setFrameShadow(QFrame::Shadow::Raised);
        searchBar = new QLineEdit(frame_5);
        searchBar->setObjectName("searchBar");
        searchBar->setGeometry(QRect(50, 10, 251, 27));
        searchBar->setStyleSheet(QString::fromUtf8("\n"
"/* Styling the QLineEdit (searchBar) inside frame_5 */\n"
"QFrame#frame_5 QLineEdit#searchBar {\n"
"    background-color: #ebebeb; /* Same dark background as the frame */\n"
"    border: 1px solid #4A5E61; /* Light gray border to match the page's style */\n"
"    border-radius: 6px; /* Slightly smaller radius for the inner widget */\n"
"    padding: 5px 30px 5px 10px; /* Padding to make room for the icon on the right */\n"
"    color: black; /* Light gray text to match the page's text color */\n"
"    font-size: 14px; /* Readable font size */\n"
"}\n"
""));
        frame_7 = new QFrame(frame_5);
        frame_7->setObjectName("frame_7");
        frame_7->setGeometry(QRect(10, 10, 31, 31));
        frame_7->setStyleSheet(QString::fromUtf8("/* Styling the QFrame (frame_7) for the search icon */\n"
"QFrame#frame_7 {\n"
"    background-color: #1A2526;\n"
"    border: none;\n"
"    border-radius: 6px 0 0 6px;\n"
"    padding: 0;\n"
"    margin: 0;\n"
"}"));
        frame_7->setFrameShape(QFrame::Shape::StyledPanel);
        frame_7->setFrameShadow(QFrame::Shadow::Raised);
        label_21 = new QLabel(frame_7);
        label_21->setObjectName("label_21");
        label_21->setGeometry(QRect(10, 10, 15, 15));
        label_21->setPixmap(QPixmap(QString::fromUtf8(":/img/search.png")));
        label_21->setScaledContents(true);
        deleteButton = new QPushButton(tab_2);
        deleteButton->setObjectName("deleteButton");
        deleteButton->setGeometry(QRect(731, 500, 101, 24));
        deleteButton->setStyleSheet(QString::fromUtf8("/* Style for the Delete button */\n"
"QPushButton#deleteButton {\n"
"    background-color: #4A1A1A; /* Muted dark red */\n"
"    color: #E0E6ED; /* Light gray text */\n"
"    font-size: 12px;\n"
"    font-weight: bold;\n"
"    border-radius: 5px;\n"
"    padding: 6px 12px;\n"
"}\n"
"QPushButton#deleteButton:hover {\n"
"    background-color: #5A2A2A; /* Lighter red on hover */\n"
"}\n"
"QPushButton#deleteButton:pressed {\n"
"    background-color: #6A3A3A; /* Darker red when pressed */\n"
"}"));
        modifyButton = new QPushButton(tab_2);
        modifyButton->setObjectName("modifyButton");
        modifyButton->setGeometry(QRect(620, 500, 101, 24));
        modifyButton->setStyleSheet(QString::fromUtf8("/* Style for the Modify button */\n"
"QPushButton#modifyButton {\n"
"    background-color: #00FF7F; /* Green to match the accent */\n"
"    color: #1A2633; /* Dark blue text */\n"
"    font-size: 12px;\n"
"    font-weight: bold;\n"
"    border-radius: 5px;\n"
"    padding: 6px 12px;\n"
"    margin-right: 10px;\n"
"}\n"
"QPushButton#modifyButton:hover {\n"
"    background-color: #00CC66; /* Darker green on hover */\n"
"}\n"
"QPushButton#modifyButton:pressed {\n"
"    background-color: #00994D; /* Even darker green when pressed */\n"
"}"));
        downloadButton = new QPushButton(tab_2);
        downloadButton->setObjectName("downloadButton");
        downloadButton->setGeometry(QRect(130, 500, 151, 24));
        downloadButton->setStyleSheet(QString::fromUtf8("/* Style for the Modify button */\n"
"QPushButton#downloadButton {\n"
"	background-color: rgb(120, 120, 120);\n"
"    color: #1A2633; /* Dark blue text */\n"
"    font-size: 12px;\n"
"    font-weight: bold;\n"
"    border-radius: 5px;\n"
"    padding: 6px 12px;\n"
"    margin-right: 10px;\n"
"}\n"
"QPushButton#downloadButton:hover {\n"
"    background-color:#ffffff ; /* Darker green on hover */\n"
"}\n"
"QPushButton#downloadButton:pressed {\n"
"    background-color: #ffffff; /* Even darker green when pressed */\n"
"}"));
        deleteButton_2 = new QPushButton(tab_2);
        deleteButton_2->setObjectName("deleteButton_2");
        deleteButton_2->setGeometry(QRect(780, 530, 51, 24));
        deleteButton_2->setStyleSheet(QString::fromUtf8("/* Style for the Delete button */\n"
"QPushButton#deleteButton_2 {\n"
"    background-color: #360e0a; /* Muted dark red */\n"
"    color: #E0E6ED; /* Light gray text */\n"
"    font-size: 12px;\n"
"    font-weight: bold;\n"
"    border-radius: 5px;\n"
"    padding: 6px 12px;\n"
"}\n"
"QPushButton#deleteButton_2:hover {\n"
"    background-color: #5A2A2A; /* Lighter red on hover */\n"
"}\n"
"QPushButton#deleteButton_2:pressed {\n"
"    background-color: #6A3A3A; /* Darker red when pressed */\n"
"}"));
        tabWidget->addTab(tab_2, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName("tab_3");
        tabWidget->addTab(tab_3, QString());

        retranslateUi(Form);

        tabWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(Form);
    } // setupUi

    void retranslateUi(QWidget *Form)
    {
        Form->setWindowTitle(QCoreApplication::translate("Form", "Form", nullptr));
        button1->setText(QCoreApplication::translate("Form", "Confirm", nullptr));
        cb->setItemText(0, QCoreApplication::translate("Form", "bernabeu", nullptr));
        cb->setItemText(1, QCoreApplication::translate("Form", "Santiago Bernab\303\251u", nullptr));
        cb->setItemText(2, QCoreApplication::translate("Form", "Camp Nou", nullptr));
        cb->setItemText(3, QCoreApplication::translate("Form", "Old Trafford", nullptr));
        cb->setItemText(4, QCoreApplication::translate("Form", "Wembley Stadium", nullptr));

        label_10->setText(QCoreApplication::translate("Form", "         Team_Logo :", nullptr));
        l1->setText(QString());
        label_9->setText(QCoreApplication::translate("Form", "         Budget :", nullptr));
        label_11->setText(QCoreApplication::translate("Form", "        Team_ABV :", nullptr));
        label_7->setText(QCoreApplication::translate("Form", "          Team_Name :", nullptr));
        label_8->setText(QCoreApplication::translate("Form", "         Home_Stadium :", nullptr));
        toolButton->setText(QCoreApplication::translate("Form", "...", nullptr));
        label_2->setText(QCoreApplication::translate("Form", "insert logo here", nullptr));
        label_4->setText(QCoreApplication::translate("Form", "FILL IN THIS FORM TO ADD A TEAM", nullptr));
        label_19->setText(QString());
        label_27->setText(QString());
        label_28->setText(QString());
        label_29->setText(QString());
        label_30->setText(QString());
        resetButton->setText(QString());
        tabWidget->setTabText(tabWidget->indexOf(tab), QCoreApplication::translate("Form", "     Add Team     ", nullptr));
        label_21->setText(QString());
        deleteButton->setText(QCoreApplication::translate("Form", "Delete", nullptr));
        modifyButton->setText(QCoreApplication::translate("Form", "Modify", nullptr));
        downloadButton->setText(QCoreApplication::translate("Form", "Download PDF", nullptr));
        deleteButton_2->setText(QCoreApplication::translate("Form", "All", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QCoreApplication::translate("Form", "     Display Team    ", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QCoreApplication::translate("Form", "         Stats          ", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Form: public Ui_Form {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TRASH_H
