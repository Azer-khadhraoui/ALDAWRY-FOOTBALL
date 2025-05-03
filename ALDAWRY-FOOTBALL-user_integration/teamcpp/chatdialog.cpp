#include "../teamheaders/chatdialog.h"
#include "ui_chatdialog.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QNetworkRequest>
#include <QDebug>

ChatDialog::ChatDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChatDialog),
    networkManager(new QNetworkAccessManager(this))
{
    ui->setupUi(this);

    // Connect send button and Enter key
    connect(ui->sendButton, &QPushButton::clicked, this, &ChatDialog::on_sendButton_clicked);
    connect(ui->messageInput, &QLineEdit::returnPressed, this, &ChatDialog::on_sendButton_clicked);

    // Connect network reply signal
    connect(networkManager, &QNetworkAccessManager::finished, this, &ChatDialog::on_apiReplyFinished);
}

ChatDialog::~ChatDialog()
{
    delete networkManager;
    delete ui;
}

void ChatDialog::on_sendButton_clicked()
{
    sendMessage();
}

void ChatDialog::sendMessage()
{
    QString userMessage = ui->messageInput->text().trimmed();
    if (userMessage.isEmpty()) return;

    // Display user message
    ui->chatDisplay->append("<b>You:</b> " + userMessage);

    // Send API request
    sendApiRequest(userMessage);

    // Clear input while waiting for response
    ui->messageInput->clear();
}

void ChatDialog::sendApiRequest(const QString &userMessage)
{
    QNetworkRequest request(QUrl("https://generativelanguage.googleapis.com/v1beta/models/gemini-1.5-flash:generateContent?key=AIzaSyDcbI8uYKJMSQvroFCcQB6RSr0nBtAqEUU"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QJsonObject json;
    QJsonArray contents;
    QJsonObject content;
    content["text"] = userMessage;
    QJsonArray parts;
    parts.append(content);
    QJsonObject message;
    message["parts"] = parts;
    contents.append(message);
    json["contents"] = contents;

    QJsonDocument doc(json);
    QByteArray data = doc.toJson();

    networkManager->post(request, data);
}

void ChatDialog::on_apiReplyFinished(QNetworkReply *reply)
{
    if (reply->error() != QNetworkReply::NoError) {
        ui->chatDisplay->append("<b>AlDawry:</b> Error: " + reply->errorString());
        reply->deleteLater();
        return;
    }

    QJsonDocument doc = QJsonDocument::fromJson(reply->readAll());
    QJsonObject json = doc.object();
    QString botResponse = json["candidates"].toArray()[0].toObject()["content"].toObject()["parts"].toArray()[0].toObject()["text"].toString().trimmed();
    if (botResponse.isEmpty()) {
        botResponse = "No response from Gemini.";
    }

    ui->chatDisplay->append("<b>Aldawry:</b> " + botResponse);
    reply->deleteLater();
}
