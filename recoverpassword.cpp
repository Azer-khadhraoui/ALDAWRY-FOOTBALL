#include "recoverpassword.h"
#include "ui_recoverpassword.h"
#include <QMessageBox>
#include <QRandomGenerator>
#include <QSqlQuery>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>
#include <QSqlError>


RecoverPasswordDialog::RecoverPasswordDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RecoverPasswordDialog)
{
    ui->setupUi(this);

    // Connect buttons to slots
    connect(ui->send_code_button, &QPushButton::clicked, this, &RecoverPasswordDialog::on_send_code_button_clicked);
    connect(ui->verify_code_button, &QPushButton::clicked, this, &RecoverPasswordDialog::on_verify_code_button_clicked);
    connect(ui->reset_password_button, &QPushButton::clicked, this, &RecoverPasswordDialog::on_reset_password_button_clicked);

    // Initialize timer
    codeTimer = new QTimer(this);
    connect(codeTimer, &QTimer::timeout, this, [this]() {
        recoveryCodes.clear();
        QMessageBox::information(this, "Timeout", "Verification code has expired.");
        ui->code_input->setEnabled(false);
        ui->verify_code_button->setEnabled(false);
        ui->new_password_input->setEnabled(false);
        ui->confirm_password_input->setEnabled(false);
        ui->reset_password_button->setEnabled(false);
    });
}

RecoverPasswordDialog::~RecoverPasswordDialog() {
    delete ui;
    delete codeTimer;
}

void RecoverPasswordDialog::on_send_code_button_clicked() {
    QString email = ui->email_input->text().trimmed();
    if (email.isEmpty()) {
        QMessageBox::warning(this, "Error", "Please enter your email.");
        return;
    }

    // Check if email exists
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM HOTSTUFF.EMPLOYE WHERE EMAIL = :email");
    query.bindValue(":email", email);
    if (!query.exec() || !query.next() || query.value(0).toInt() == 0) {
        QMessageBox::warning(this, "Error", "Email not found in the system.");
        return;
    }

    // Stop any existing timer and clear existing code for this email
    codeTimer->stop();
    recoveryCodes.remove(email);

    // Generate random code
    QString code = QString::number(QRandomGenerator::global()->bounded(100000, 999999));
    recoveryCodes[email] = code;
    currentEmail = email;

    qDebug() << "Generated code for" << email << ":" << code;

    // Send email
    sendRecoveryEmail(email, code);

    // Enable code input and button
    ui->code_input->setEnabled(true);
    ui->verify_code_button->setEnabled(true);
    ui->email_input->setEnabled(false);
    ui->send_code_button->setEnabled(false);

    // Start expiration timer (30 minutes for testing)
    codeTimer->start(30 * 60 * 1000);
}

void RecoverPasswordDialog::on_verify_code_button_clicked() {
    QString inputCode = ui->code_input->text().trimmed();
    if (inputCode.isEmpty()) {
        QMessageBox::warning(this, "Error", "Please enter the verification code.");
        return;
    }

    QString storedCode = recoveryCodes.value(currentEmail);
    qDebug() << "Stored code for" << currentEmail << ":" << storedCode;
    qDebug() << "Entered code:" << inputCode;

    if (inputCode == storedCode) {
        QMessageBox::information(this, "Success", "Code verified!");
        ui->new_password_input->setEnabled(true);
        ui->confirm_password_input->setEnabled(true);
        ui->reset_password_button->setEnabled(true);
        ui->code_input->setEnabled(false);
        ui->verify_code_button->setEnabled(false);
    } else {
        QMessageBox::warning(this, "Error", "Invalid code.");
    }
}

void RecoverPasswordDialog::on_reset_password_button_clicked() {
    QString newPassword = ui->new_password_input->text();
    QString confirmPassword = ui->confirm_password_input->text();

    if (newPassword.isEmpty() || confirmPassword.isEmpty()) {
        QMessageBox::warning(this, "Error", "Please fill in both password fields.");
        return;
    }

    if (newPassword != confirmPassword) {
        QMessageBox::warning(this, "Error", "Passwords do not match.");
        return;
    }

    // Update password in database
    QSqlQuery query;
    query.prepare("UPDATE HOTSTUFF.EMPLOYE SET MDP = :password WHERE EMAIL = :email");
    query.bindValue(":password", newPassword);
    query.bindValue(":email", currentEmail);
    if (query.exec() && query.numRowsAffected() > 0) {
        QMessageBox::information(this, "Success", "Password reset successfully!");
        recoveryCodes.remove(currentEmail);
        codeTimer->stop();
        accept(); // Close dialog
    } else {
        QMessageBox::critical(this, "Error", "Failed to reset password: " + query.lastError().text());
    }
}

void RecoverPasswordDialog::sendRecoveryEmail(const QString &email, const QString &code) {
    QString subject = "Password Recovery Code";
    QString body = QString("Your recovery code is: %1\nThis code will expire in 10 minutes.").arg(code);

    // Use SendGrid API to send the email
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    QNetworkRequest request(QUrl("https://api.sendgrid.com/v3/mail/send"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
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
    from["email"] = "tunisiatour1@gmail.com";

    QJsonArray contentArray;
    QJsonObject content;
    content["type"] = "text/plain";
    content["value"] = body;
    contentArray.append(content);

    json["personalizations"] = personalizations;
    json["from"] = from;
    json["subject"] = subject;
    json["content"] = contentArray;

    QNetworkReply *reply = manager->post(request, QJsonDocument(json).toJson());
    connect(reply, &QNetworkReply::finished, this, [this, reply]() {
        if (reply->error() == QNetworkReply::NoError) {
            QMessageBox::information(this, "Email Sent", "A recovery code has been sent to your email.");
        } else {
            QMessageBox::critical(this, "Error", "Failed to send email: " + reply->errorString() + "\nResponse: " + reply->readAll());
        }
        reply->deleteLater();
    });
}
