// mainwindow.cpp
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "userwindow.h"
#include <QMessageBox>
#include <QStyle>
#include "userwindow.h" // Assuming this is the next window after login
#include "recoverpassword.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    // Set placeholder text for the input fields
    ui->lineEdit->setPlaceholderText("Email");
    ui->lineEdit->clear(); // Clear the default "Email" text
    ui->lineEdit_2->setPlaceholderText("Password");
    ui->lineEdit_2->clear(); // Clear the default "Password" text
    ui->lineEdit_2->setEchoMode(QLineEdit::Password); // Hide password input
    connect(ui->sign_in_2, &QPushButton::clicked, this, &MainWindow::on_sign_in_2_clicked);






    // Optional: Set a default style for the input fields
    ui->lineEdit->setStyleSheet(
        "background-color: rgb(223, 223, 223);"
        "color: #b9b9b9;"
        "font-size: 14px;"
        "border: 2px solid qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 #1b1f2a, stop:1 #10131a);"
        "border-radius: 6px;"
        "padding: 4px 8px;"
        );
    ui->lineEdit_2->setStyleSheet(
        "background-color: rgb(223, 223, 223);"
        "color: #b9b9b9;"
        "font-size: 14px;"
        "border: 2px solid qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 #1b1f2a, stop:1 #10131a);"
        "border-radius: 6px;"
        "padding: 4px 8px;"
        );
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_sign_in_clicked() {
    // Get the email and password from the input fields
    QString email = ui->lineEdit->text().trimmed();
    QString password = ui->lineEdit_2->text().trimmed();

    // Reset the styles of the input fields to default
    ui->lineEdit->setStyleSheet(
        "background-color: rgb(223, 223, 223);"
        "color: #b9b9b9;"
        "font-size: 14px;"
        "border: 2px solid qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 #1b1f2a, stop:1 #10131a);"
        "border-radius: 6px;"
        "padding: 4px 8px;"
        );
    ui->lineEdit_2->setStyleSheet(
        "background-color: rgb(223, 223, 223);"
        "color: #b9b9b9;"
        "font-size: 14px;"
        "border: 2px solid qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 #1b1f2a, stop:1 #10131a);"
        "border-radius: 6px;"
        "padding: 4px 8px;"
        );

    // Basic validation for empty fields
    if (email.isEmpty() && password.isEmpty()) {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Login Error");
        msgBox.setText("Oops! You haven't entered your email or password.");
        msgBox.setInformativeText("Please fill in both fields to sign in.");
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setDefaultButton(QMessageBox::Ok);
        msgBox.exec();

        // Highlight both fields and set focus to the email field
        ui->lineEdit->setStyleSheet(
            "background-color: rgb(223, 223, 223);"
            "color: #b9b9b9;"
            "font-size: 14px;"
            "border: 2px solid #ff5555;" // Red border to highlight error
            "border-radius: 6px;"
            "padding: 4px 8px;"
            );
        ui->lineEdit_2->setStyleSheet(
            "background-color: rgb(223, 223, 223);"
            "color: #b9b9b9;"
            "font-size: 14px;"
            "border: 2px solid #ff5555;" // Red border to highlight error
            "border-radius: 6px;"
            "padding: 4px 8px;"
            );
        ui->lineEdit->setFocus();
        return;
    } else if (email.isEmpty()) {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Login Error");
        msgBox.setText("Oops! You forgot to enter your email.");
        msgBox.setInformativeText("Please enter your email address to sign in.");
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setDefaultButton(QMessageBox::Ok);
        msgBox.exec();

        // Highlight the email field and set focus
        ui->lineEdit->setStyleSheet(
            "background-color: rgb(223, 223, 223);"
            "color: #b9b9b9;"
            "font-size: 14px;"
            "border: 2px solid #ff5555;" // Red border to highlight error
            "border-radius: 6px;"
            "padding: 4px 8px;"
            );
        ui->lineEdit->setFocus();
        return;
    } else if (password.isEmpty()) {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Login Error");
        msgBox.setText("Oops! You forgot to enter your password.");
        msgBox.setInformativeText("Please enter your password to sign in.");
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setDefaultButton(QMessageBox::Ok);
        msgBox.exec();

        // Highlight the password field and set focus
        ui->lineEdit_2->setStyleSheet(
            "background-color: rgb(223, 223, 223);"
            "color: #b9b9b9;"
            "font-size: 14px;"
            "border: 2px solid #ff5555;" // Red border to highlight error
            "border-radius: 6px;"
            "padding: 4px 8px;"
            );
        ui->lineEdit_2->setFocus();
        return;
    }

    // Authenticate the user
    Employee emp;
    if (emp.authenticate(email, password)) {
        // Authentication successful, open UserWindow
        UserWindow *userWindow = new UserWindow(this);
        userWindow->show();
        this->hide(); // Hide the sign-in window
    } else {
        // Authentication failed, show error message
        QMessageBox msgBox;
        msgBox.setWindowTitle("Login Error");
        msgBox.setText("Incorrect email or password.");
        msgBox.setInformativeText("Please double-check your credentials or use 'Forgot Password?' to reset your password.");
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setDefaultButton(QMessageBox::Ok);
        msgBox.exec();

        // Clear the fields and set focus to the email field
        ui->lineEdit->clear();
        ui->lineEdit_2->clear();
        ui->lineEdit->setFocus();
    }
}


void MainWindow::on_sign_in_2_clicked() {
    RecoverPasswordDialog dialog(this);
    dialog.exec();
}
