#include "newpassword.h"
#include "ui_newpassword.h"
#include "recoverpassword.h"
#include <QMessageBox>
#include <QSqlQuery>
#include <QRegularExpression>
#include <QDebug>
#include <QSqlError>
#include <QCryptographicHash> // For hashing
#include <QUuid> // For generating salt

NewPasswordDialog::NewPasswordDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewPasswordDialog)
{
    ui->setupUi(this);

    // Enable input fields
    ui->new_password_input->setEnabled(true);
    ui->confirm_password_input->setEnabled(true);
    ui->reset_password_button->setEnabled(true);

    // Connect signals
    connect(ui->reset_password_button, &QPushButton::clicked, this, &NewPasswordDialog::on_reset_password_button_clicked, Qt::UniqueConnection);
    connect(ui->pushButton, &QPushButton::clicked, this, &NewPasswordDialog::on_pushButton_clicked, Qt::UniqueConnection);

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

NewPasswordDialog::~NewPasswordDialog() {
    qDebug() << "NewPasswordDialog destroyed";
    delete ui;
}

void NewPasswordDialog::on_reset_password_button_clicked() {
    QString newPassword = ui->new_password_input->text();
    QString confirmPassword = ui->confirm_password_input->text();

    if (newPassword.isEmpty() || confirmPassword.isEmpty()) {
        QMessageBox msgBox(this);
        styleMessageBox(&msgBox);
        msgBox.setWindowTitle("Input Error");
        msgBox.setText("Please fill in both password fields.");
        msgBox.setInformativeText("Both the new password and confirmation fields are required.");
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.exec();
        return;
    }

    if (newPassword != confirmPassword) {
        QMessageBox msgBox(this);
        styleMessageBox(&msgBox);
        msgBox.setWindowTitle("Password Mismatch");
        msgBox.setText("Passwords do not match.");
        msgBox.setInformativeText("Please ensure the new password and confirmation match.");
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.exec();
        return;
    }

    QRegularExpression passwordRegex("^(?=.*[a-z])(?=.*[A-Z])(?=.*[0-9])(?=.*[!@#$%^&*])[A-Za-z0-9!@#$%^&*]{8,}$");
    if (!passwordRegex.match(newPassword).hasMatch()) {
        QMessageBox msgBox(this);
        styleMessageBox(&msgBox);
        msgBox.setWindowTitle("Invalid Password");
        msgBox.setText("Password does not meet requirements.");
        msgBox.setInformativeText(
            "Password must be at least 8 characters long and include:\n"
            "- At least one uppercase letter Verbs\n"
            "- At least one lowercase letter\n"
            "- At least one digit\n"
            "- At least one special character (!@#$%^&*)"
            );
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.exec();
        return;
    }

    QStringList commonPasswords = {"password", "12345678", "qwertyui", "admin123"};
    if (commonPasswords.contains(newPassword.toLower())) {
        QMessageBox msgBox(this);
        styleMessageBox(&msgBox);
        msgBox.setWindowTitle("Weak Password");
        msgBox.setText("This password is too common.");
        msgBox.setInformativeText("Please choose a stronger password to enhance security.");
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.exec();
        return;
    }

    QString email = RecoverPasswordDialog::getCurrentEmail();
    qDebug() << "Attempting to update password for email:" << email;
    if (email.isEmpty()) {
        QMessageBox msgBox(this);
        styleMessageBox(&msgBox);
        msgBox.setWindowTitle("Email Error");
        msgBox.setText("No email address found.");
        msgBox.setInformativeText("The email address for password recovery is missing. Please start the recovery process again.");
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.exec();
        return;
    }

    // Hash the new password with a salt, matching the format in adduser.cpp
    QString salt = QUuid::createUuid().toString();
    QString saltedPassword = newPassword + salt;
    QString hashedPassword = QString(QCryptographicHash::hash(saltedPassword.toUtf8(), QCryptographicHash::Sha256).toHex());
    QString storedPassword = hashedPassword + ":" + salt; // hash:salt format
    qDebug() << "Hashed password with salt:" << storedPassword;

    QSqlQuery query;
    query.prepare("UPDATE HOTSTUFF.EMPLOYE SET MDP = :password WHERE EMAIL = :email");
    query.bindValue(":password", storedPassword); // Store in hash:salt format
    query.bindValue(":email", email);
    qDebug() << "Executing UPDATE query with password (hash:salt):" << storedPassword << "for email:" << email;

    if (query.exec()) {
        qDebug() << "Password update query executed successfully. Rows affected:" << query.numRowsAffected();
        QMessageBox msgBox(this);
        styleMessageBox(&msgBox);
        msgBox.setWindowTitle("Success");
        msgBox.setText("Password reset successfully!");
        msgBox.setInformativeText("You can now log in with your new password.");
        msgBox.setIcon(QMessageBox::Information);
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.exec();

        RecoverPasswordDialog::getRecoveryCodes().remove(email);
        RecoverPasswordDialog::getCodeTimer()->stop();
        accept();
    } else {
        qDebug() << "Failed to update password. Query error:" << query.lastError().text();
        qDebug() << "Database error type:" << query.lastError().type();
        QMessageBox msgBox(this);
        styleMessageBox(&msgBox);
        msgBox.setWindowTitle("Database Error");
        msgBox.setText("Failed to reset password.");
        msgBox.setInformativeText("Error: " + query.lastError().text());
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.exec();
    }
}

void NewPasswordDialog::on_pushButton_clicked() {
    qDebug() << "Login button clicked";
    accept(); // Close dialog to return to login screen
}

void NewPasswordDialog::styleMessageBox(QMessageBox *msgBox) {
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
