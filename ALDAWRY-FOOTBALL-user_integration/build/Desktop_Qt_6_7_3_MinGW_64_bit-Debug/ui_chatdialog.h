/********************************************************************************
** Form generated from reading UI file 'chatdialog.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHATDIALOG_H
#define UI_CHATDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ChatDialog
{
public:
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QLabel *headerLabel;
    QTextEdit *chatDisplay;
    QWidget *inputWidget;
    QHBoxLayout *horizontalLayout;
    QLineEdit *messageInput;
    QPushButton *sendButton;

    void setupUi(QDialog *ChatDialog)
    {
        if (ChatDialog->objectName().isEmpty())
            ChatDialog->setObjectName("ChatDialog");
        ChatDialog->resize(400, 600);
        ChatDialog->setStyleSheet(QString::fromUtf8("background-color: #1E2633; /* Dark background matching MainWindow */\n"
"color: #E0E6ED; /* Light gray text */"));
        centralWidget = new QWidget(ChatDialog);
        centralWidget->setObjectName("centralWidget");
        centralWidget->setGeometry(QRect(0, 0, 400, 600));
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setObjectName("verticalLayout");
        label = new QLabel(centralWidget);
        label->setObjectName("label");
        label->setScaledContents(true);

        verticalLayout->addWidget(label);

        headerLabel = new QLabel(centralWidget);
        headerLabel->setObjectName("headerLabel");
        QFont font;
        font.setFamilies({QString::fromUtf8("Segoe UI")});
        font.setPointSize(14);
        font.setBold(true);
        headerLabel->setFont(font);
        headerLabel->setStyleSheet(QString::fromUtf8("background-color: #252A38; /* Slightly lighter header */\n"
"border-bottom: 2px solid #00FF7F; /* Green accent */\n"
"padding: 10px;\n"
"color: #E0E6ED;"));
        headerLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout->addWidget(headerLabel);

        chatDisplay = new QTextEdit(centralWidget);
        chatDisplay->setObjectName("chatDisplay");
        chatDisplay->setStyleSheet(QString::fromUtf8("background-color: #252A38; /* Slightly lighter than main bg */\n"
"border: 1px solid #2A3A4A; /* Subtle border */\n"
"border-radius: 5px;\n"
"padding: 10px;\n"
"color: #E0E6ED;\n"
"font-family: 'Segoe UI', Arial, sans-serif;\n"
"font-size: 12px;"));
        chatDisplay->setReadOnly(true);

        verticalLayout->addWidget(chatDisplay);

        inputWidget = new QWidget(centralWidget);
        inputWidget->setObjectName("inputWidget");
        inputWidget->setStyleSheet(QString::fromUtf8("background-color: #1E2633; /* Matches dialog bg */\n"
"border-top: 1px solid #2A3A4A; /* Subtle separator */\n"
"padding: 10px;"));
        horizontalLayout = new QHBoxLayout(inputWidget);
        horizontalLayout->setObjectName("horizontalLayout");
        messageInput = new QLineEdit(inputWidget);
        messageInput->setObjectName("messageInput");
        messageInput->setStyleSheet(QString::fromUtf8("background-color: #2A3240; /* Dark input field */\n"
"border: 1px solid #3A4A5A; /* Subtle border */\n"
"border-radius: 5px;\n"
"padding: 5px;\n"
"color: #E0E6ED;\n"
"font-family: 'Segoe UI', Arial, sans-serif;\n"
"font-size: 12px;"));

        horizontalLayout->addWidget(messageInput);

        sendButton = new QPushButton(inputWidget);
        sendButton->setObjectName("sendButton");
        sendButton->setStyleSheet(QString::fromUtf8("background-color: #00FF7F; /* Green accent */\n"
"color: #1A2633; /* Dark text for contrast */\n"
"font-size: 12px;\n"
"font-weight: bold;\n"
"border-radius: 5px;\n"
"padding: 6px 12px;"));

        horizontalLayout->addWidget(sendButton);


        verticalLayout->addWidget(inputWidget);


        retranslateUi(ChatDialog);

        QMetaObject::connectSlotsByName(ChatDialog);
    } // setupUi

    void retranslateUi(QDialog *ChatDialog)
    {
        ChatDialog->setWindowTitle(QCoreApplication::translate("ChatDialog", "Chat with AlDawry", nullptr));
        label->setText(QString());
        headerLabel->setText(QCoreApplication::translate("ChatDialog", "Chat With Aldawry", nullptr));
        chatDisplay->setHtml(QCoreApplication::translate("ChatDialog", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"hr { height: 1px; border-width: 0; }\n"
"li.unchecked::marker { content: \"\\2610\"; }\n"
"li.checked::marker { content: \"\\2612\"; }\n"
"</style></head><body style=\" font-family:'Segoe UI','Arial','sans-serif'; font-size:12px; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Segoe UI'; font-weight:700;\">AlDawry:</span><span style=\" font-family:'Segoe UI';\"> Hello! How can I assist you today?</span></p></body></html>", nullptr));
        messageInput->setPlaceholderText(QCoreApplication::translate("ChatDialog", "Type your message...", nullptr));
        sendButton->setText(QCoreApplication::translate("ChatDialog", "Send", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ChatDialog: public Ui_ChatDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHATDIALOG_H
