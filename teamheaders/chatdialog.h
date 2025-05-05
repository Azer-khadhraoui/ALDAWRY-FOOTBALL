#ifndef CHATDIALOG_H
#define CHATDIALOG_H

#include <QDialog>
#include <QNetworkAccessManager>
#include <QNetworkReply>

namespace Ui {
class ChatDialog;
}

class ChatDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ChatDialog(QWidget *parent = nullptr);
    ~ChatDialog();

private slots:
    void on_sendButton_clicked(); // Slot for sending messages
    void sendMessage();           // Helper to process and display messages
    void on_apiReplyFinished(QNetworkReply *reply); // Handle API response

private:
    Ui::ChatDialog *ui;
    QNetworkAccessManager *networkManager; // For API requests
    void sendApiRequest(const QString &userMessage); // Send request to API
};

#endif // CHATDIALOG_H
