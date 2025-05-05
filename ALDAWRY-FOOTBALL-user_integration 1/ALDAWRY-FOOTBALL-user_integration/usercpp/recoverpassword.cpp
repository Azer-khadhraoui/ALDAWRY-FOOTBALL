#include "../userheaders/recoverpassword.h"
#include "ui_recoverpassword.h"
#include "../userheaders/emailsent.h"
#include <QMessageBox>
#include <QRandomGenerator>
#include <QSqlQuery>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QRegularExpression>
#include <QDebug>
#include <QSqlError>

// Initialize static members
QMap<QString, QString> RecoverPasswordDialog::recoveryCodes;
QTimer* RecoverPasswordDialog::codeTimer = nullptr;
QString RecoverPasswordDialog::currentEmail;

RecoverPasswordDialog::RecoverPasswordDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RecoverPasswordDialog)
{
    ui->setupUi(this);

    // Initialize timer if not already created
    if (!codeTimer) {
        codeTimer = new QTimer(this);
        connect(codeTimer, &QTimer::timeout, this, &RecoverPasswordDialog::onCodeTimerTimeout);
    }

    // Ensure single connection for signals
    connect(ui->send_code_button, &QPushButton::clicked, this, &RecoverPasswordDialog::on_send_code_button_clicked, Qt::UniqueConnection);
    connect(ui->pushButton, &QPushButton::clicked, this, &RecoverPasswordDialog::on_pushButton_clicked, Qt::UniqueConnection);

    // Ensure the send_code_button is enabled when the dialog is opened
    ui->send_code_button->setEnabled(true);

    // Apply stylesheet to the dialog for consistency
    this->setStyleSheet(
        "QDialog {"
        "    background-color: #ffffff;"
        "    border: 2px solid qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 #1b1f2a, stop:1 #10131a);"
        "    border-radius: 10px;"
        "}"
        "QLabel {"
        "    color: #333333;"
        "    font-size: 14px;"
        "    font-weight: bold;"
        "}"
        "QLineEdit {"
        "    background-color: #f0f0f0;"
        "    border: 1px solid #cccccc;"
        "    border-radius: 5px;"
        "    padding: 5px;"
        "    font-size: 14px;"
        "}"
        "QPushButton {"
        "    background-color: #0078d7;"
        "    color: white;"
        "    border: none;"
        "    border-radius: 5px;"
        "    padding: 8px 16px;"
        "    font-size: 14px;"
        "}"
        "QPushButton:hover {"
        "    background-color: #005bb5;"
        "}"
        "QPushButton:disabled {"
        "    background-color: #cccccc;"
        "}"
        );
}

RecoverPasswordDialog::~RecoverPasswordDialog() {
    qDebug() << "RecoverPasswordDialog destroyed";
    delete ui;
}

void RecoverPasswordDialog::closeEvent(QCloseEvent *event) {
    // Stop the timer and clean up static variables when the dialog is closed
    if (codeTimer) {
        codeTimer->stop();
    }
    recoveryCodes.clear();
    currentEmail.clear();
    QDialog::closeEvent(event);
}

void RecoverPasswordDialog::onCodeTimerTimeout() {
    recoveryCodes.clear();
    currentEmail.clear();
    QMessageBox msgBox(this);
    styleMessageBox(&msgBox);
    msgBox.setWindowTitle("Code Expired");
    msgBox.setText("Verification code has expired.");
    msgBox.setInformativeText("Please request a new code to continue.");
    msgBox.setIcon(QMessageBox::Information);
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.exec();

    // Disable fields in EmailSentDialog if open
    EmailSentDialog* emailSent = findChild<EmailSentDialog*>();
    if (emailSent) {
        emailSent->disableCodeInput();
    }
}

void RecoverPasswordDialog::resendRecoveryEmail() {
    QString email = currentEmail;
    if (email.isEmpty()) {
        QMessageBox msgBox(this);
        styleMessageBox(&msgBox);
        msgBox.setWindowTitle("Resend Error");
        msgBox.setText("No email address available to resend.");
        msgBox.setInformativeText("Please enter an email address and try again.");
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.exec();
        return;
    }

    codeTimer->stop();
    recoveryCodes.remove(email);

    QString code = QString::number(QRandomGenerator::global()->bounded(100000, 999999));
    recoveryCodes[email] = code;

    qDebug() << "Resending code for" << email << ":" << code;

    sendRecoveryEmail(email, code);
    codeTimer->start(10 * 60 * 1000);

    QMessageBox msgBox(this);
    styleMessageBox(&msgBox);
    msgBox.setWindowTitle("Email Resent");
    msgBox.setText("A new recovery code has been sent!");
    msgBox.setInformativeText(QString("Please check your inbox at %1 for the new code.").arg(email));
    msgBox.setIcon(QMessageBox::Information);
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.exec();
}

void RecoverPasswordDialog::on_send_code_button_clicked() {
    if (!ui->send_code_button->isEnabled()) {
        qDebug() << "Send email button is disabled, ignoring click";
        return;
    }

    ui->send_code_button->setEnabled(false);
    qDebug() << "Send email button clicked";

    QString email = ui->email_input->text().trimmed();
    if (email.isEmpty()) {
        QMessageBox msgBox(this);
        styleMessageBox(&msgBox);
        msgBox.setWindowTitle("Input Error");
        msgBox.setText("Please enter your email.");
        msgBox.setInformativeText("An email address is required to send a recovery code.");
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.exec();
        ui->send_code_button->setEnabled(true);
        return;
    }

    QRegularExpression emailRegex("^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,}$");
    if (!emailRegex.match(email).hasMatch()) {
        QMessageBox msgBox(this);
        styleMessageBox(&msgBox);
        msgBox.setWindowTitle("Invalid Email");
        msgBox.setText("Please enter a valid email address.");
        msgBox.setInformativeText("The email format is incorrect. Example: user@example.com");
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.exec();
        ui->send_code_button->setEnabled(true);
        return;
    }

    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM HOTSTUFF.EMPLOYE WHERE EMAIL = :email");
    query.bindValue(":email", email);
    if (!query.exec()) {
        qDebug() << "Email check query failed:" << query.lastError().text();
        QMessageBox msgBox(this);
        styleMessageBox(&msgBox);
        msgBox.setWindowTitle("Database Error");
        msgBox.setText("Failed to verify email.");
        msgBox.setInformativeText("Database error: " + query.lastError().text());
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.exec();
        ui->send_code_button->setEnabled(true);
        return;
    }
    if (!query.next() || query.value(0).toInt() == 0) {
        QMessageBox msgBox(this);
        styleMessageBox(&msgBox);
        msgBox.setWindowTitle("Email Not Found");
        msgBox.setText("Email not found in the system.");
        msgBox.setInformativeText("Please check the email or contact support if you believe this is an error.");
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.exec();
        ui->send_code_button->setEnabled(true);
        return;
    }

    codeTimer->stop();
    recoveryCodes.remove(email);

    QString code = QString::number(QRandomGenerator::global()->bounded(100000, 999999));
    recoveryCodes[email] = code;
    currentEmail = email;

    qDebug() << "Generated code for" << email << ":" << code;

    sendRecoveryEmail(email, code);

    // Create and show EmailSentDialog, then close this dialog
    EmailSentDialog *emailSent = new EmailSentDialog(this);
    emailSent->show();
    this->accept(); // Close the RecoverPasswordDialog
}

void RecoverPasswordDialog::on_pushButton_clicked() {
    qDebug() << "Login button clicked";
    codeTimer->stop();
    recoveryCodes.clear();
    currentEmail.clear();
    this->accept(); // Close dialog to return to login screen
}

void RecoverPasswordDialog::sendRecoveryEmail(const QString &email, const QString &code) {
    QString subject = "Password Recovery Code";
    QString body = QString("Your recovery code is: %1\nThis code will expire in 10 minutes.").arg(code);

    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    QNetworkRequest request(QUrl("https://api.sendgrid.com/v3/mail/send"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    // Updated API key
    request.setRawHeader("Authorization", "Bearer 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");

    QJsonObject json;
    QJsonArray toArray;
    QJsonObject toEmail;
    toEmail["email"] = email;
    toArray.append(toEmail);

    QJsonObject personalization;
    personalization["to"] = toArray;
    QJsonArray personalizations;
    personalizations.append(personalization);

    QJsonObject from;
    from["email"] = "aldawryfootball@gmail.com";
    from["name"] = "Aldawry Football";

    QJsonArray contentArray;
    QJsonObject content;
    content["type"] = "text/plain";
    content["value"] = body;
    contentArray.append(content);

    json["personalizations"] = personalizations;
    json["from"] = from;
    json["subject"] = subject;
    json["content"] = contentArray;

    qDebug() << "Sending JSON payload:" << QJsonDocument(json).toJson(QJsonDocument::Indented);

    QNetworkReply *reply = manager->post(request, QJsonDocument(json).toJson());
    connect(reply, &QNetworkReply::finished, this, &RecoverPasswordDialog::onEmailSendFinished);
}

void RecoverPasswordDialog::onEmailSendFinished() {
    QNetworkReply *reply = qobject_cast<QNetworkReply*>(sender());
    if (!reply) {
        qDebug() << "No valid QNetworkReply received";
        ui->send_code_button->setEnabled(true);
        return;
    }

    qDebug() << "Email send response received";
    if (reply->error() == QNetworkReply::NoError) {
        qDebug() << "Email sent successfully";
        codeTimer->start(10 * 60 * 1000); // Start the timer only if email is sent successfully
    } else {
        qDebug() << "Failed to send email:" << reply->errorString() << "Response:" << reply->readAll();
        QMessageBox msgBox(this);
        styleMessageBox(&msgBox);
        msgBox.setWindowTitle("Email Error");
        msgBox.setText("Failed to send email.");
        msgBox.setInformativeText("Error: " + reply->errorString());
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.exec();
        ui->send_code_button->setEnabled(true);
    }
    reply->deleteLater();
    reply->manager()->deleteLater();
}

void RecoverPasswordDialog::styleMessageBox(QMessageBox *msgBox) {
    msgBox->setStyleSheet(
        "QMessageBox {"
        "    background-color: #f5f7fa;"
        "    border: 2px solid qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 #1b1f2a, stop:1 #10131a);"
        "    border-radius: 10px;"
        "}"
        "QLabel {"
        "    color: #333333;"
        "    font-size: 14px;"
        "}"
        "QPushButton {"
        "    background-color: #0078d7;"
        "    color: white;"
        "    border: none;"
        "    border-radius: 5px;"
        "    padding: 8px 16px;"
        "    font-size: 14px;"
        "}"
        "QPushButton:hover {"
        "    background-color: #005bb5;"
        "}"
        );
}
