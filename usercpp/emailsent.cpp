#include "../userheaders/emailsent.h"
#include "ui_emailsent.h"
#include "../userheaders/newpassword.h"
#include "../userheaders/recoverpassword.h"
#include <QMessageBox>
#include <QDebug>

EmailSentDialog::EmailSentDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EmailSentDialog),
    isProcessing(false) // Initialize the flag
{
    ui->setupUi(this);

    // Enable input fields
    ui->code_input->setEnabled(true);
    ui->verify_code_button->setEnabled(true);

    // Set email label
    ui->label_title_8->setText(RecoverPasswordDialog::getCurrentEmail());

    // Connect signals
    connect(ui->verify_code_button, &QPushButton::clicked, this, &EmailSentDialog::on_verify_code_button_clicked, Qt::UniqueConnection);
    connect(ui->pushButton, &QPushButton::clicked, this, &EmailSentDialog::on_pushButton_clicked, Qt::UniqueConnection);
    connect(ui->pushButton_2, &QPushButton::clicked, this, &EmailSentDialog::on_pushButton_2_clicked, Qt::UniqueConnection);

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

    // Show email sent message
    QMessageBox msgBox(this);
    styleMessageBox(&msgBox);
    msgBox.setWindowTitle("Email Sent");
    msgBox.setText("A recovery code has been sent!");
    msgBox.setInformativeText(QString("Please check your inbox at %1 and enter the code below.").arg(RecoverPasswordDialog::getCurrentEmail()));
    msgBox.setIcon(QMessageBox::Information);
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.exec();
}

EmailSentDialog::~EmailSentDialog() {
    qDebug() << "EmailSentDialog destroyed";
    delete ui;
}

void EmailSentDialog::disableCodeInput() {
    ui->code_input->setEnabled(false);
    ui->verify_code_button->setEnabled(false);
}

void EmailSentDialog::on_verify_code_button_clicked() {
    if (isProcessing) {
        qDebug() << "Already processing verification, ignoring click";
        return;
    }

    isProcessing = true;
    ui->verify_code_button->setEnabled(false); // Disable button to prevent double-clicks
    qDebug() << "Verify code button clicked";

    QString inputCode = ui->code_input->text().trimmed();
    if (inputCode.isEmpty()) {
        QMessageBox msgBox(this);
        styleMessageBox(&msgBox);
        msgBox.setWindowTitle("Input Error");
        msgBox.setText("Please enter the verification code.");
        msgBox.setInformativeText("A code is required to proceed with password recovery.");
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.exec();
        isProcessing = false;
        ui->verify_code_button->setEnabled(true);
        return;
    }

    QString storedCode = RecoverPasswordDialog::getRecoveryCodes().value(RecoverPasswordDialog::getCurrentEmail());
    qDebug() << "Stored code for" << RecoverPasswordDialog::getCurrentEmail() << ":" << storedCode;
    qDebug() << "Entered code:" << inputCode;

    if (inputCode == storedCode) {
        QMessageBox msgBox(this);
        styleMessageBox(&msgBox);
        msgBox.setWindowTitle("Success");
        msgBox.setText("Code verified successfully!");
        msgBox.setInformativeText("You can now set a new password.");
        msgBox.setIcon(QMessageBox::Information);
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.exec();

        NewPasswordDialog *newPassword = new NewPasswordDialog(this);
        newPassword->show();
        this->accept(); // Close EmailSentDialog
    } else {
        QMessageBox msgBox(this);
        styleMessageBox(&msgBox);
        msgBox.setWindowTitle("Invalid Code");
        msgBox.setText("Invalid code entered.");
        msgBox.setInformativeText("Please check the code and try again, or request a new one.");
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.exec();
        isProcessing = false;
        ui->verify_code_button->setEnabled(true);
    }
}

void EmailSentDialog::on_pushButton_clicked() {
    if (isProcessing) {
        qDebug() << "Already processing, ignoring resend click";
        return;
    }

    qDebug() << "Resend email button clicked";
    RecoverPasswordDialog *recover = qobject_cast<RecoverPasswordDialog*>(parent());
    if (recover) {
        recover->resendRecoveryEmail();
    } else {
        QMessageBox msgBox(this);
        styleMessageBox(&msgBox);
        msgBox.setWindowTitle("Resend Error");
        msgBox.setText("Cannot resend email.");
        msgBox.setInformativeText("Please try changing the email address or contact support.");
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.exec();
    }
}

void EmailSentDialog::on_pushButton_2_clicked() {
    if (isProcessing) {
        qDebug() << "Already processing, ignoring change email click";
        return;
    }

    qDebug() << "Change email address button clicked";
    RecoverPasswordDialog *recover = new RecoverPasswordDialog(this);
    recover->show();
    this->accept(); // Close EmailSentDialog
}

void EmailSentDialog::styleMessageBox(QMessageBox *msgBox) {
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
