#include "../userheaders/mainwindow.h"
#include "ui_mainwindow.h"
#include "../userheaders/userwindow.h"
#include <QMessageBox>
#include <QStyle>
#include "../userheaders/recoverpassword.h"
#include "../teamheaders/formadd.h"
#include <QSqlQuery>
#include "../teamheaders/team.h"
#include <QSqlError>
#include <QDebug>
#include "../userheaders/sessionmanager.h"
#include "../userheaders/admin.h"
#include "../userheaders/employeview.h" // Added for EmployeeWindow
#include "../userheaders/coach.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    // Set placeholder text for the input fields
    ui->lineEdit->setPlaceholderText("Email");
    ui->lineEdit->clear();
    ui->lineEdit_2->setPlaceholderText("Password");
    ui->lineEdit_2->clear();
    ui->lineEdit_2->setEchoMode(QLineEdit::Password);
    connect(ui->sign_in_2, &QPushButton::clicked, this, &MainWindow::on_sign_in_2_clicked);

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
    QString email = ui->lineEdit->text().trimmed();
    QString password = ui->lineEdit_2->text().trimmed();

    qDebug() << "Sign-in clicked with email:" << email;

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

    if (email.isEmpty() && password.isEmpty()) {
        qDebug() << "Validation failed: Both email and password are empty.";
        QMessageBox msgBox;
        msgBox.setWindowTitle("Login Error");
        msgBox.setText("Oops! You haven't entered your email or password.");
        msgBox.setInformativeText("Please fill in both fields to sign in.");
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setDefaultButton(QMessageBox::Ok);
        msgBox.exec();

        ui->lineEdit->setStyleSheet(
            "background-color: rgb(223, 223, 223);"
            "color: #b9b9b9;"
            "font-size: 14px;"
            "border: 2px solid #ff5555;"
            "border-radius: 6px;"
            "padding: 4px 8px;"
            );
        ui->lineEdit_2->setStyleSheet(
            "background-color: rgb(223, 223, 223);"
            "color: #b9b9b9;"
            "font-size: 14px;"
            "border: 2px solid #ff5555;"
            "border-radius: 6px;"
            "padding: 4px 8px;"
            );
        ui->lineEdit->setFocus();
        return;
    } else if (email.isEmpty()) {
        qDebug() << "Validation failed: Email is empty.";
        QMessageBox msgBox;
        msgBox.setWindowTitle("Login Error");
        msgBox.setText("Oops! You forgot to enter your email.");
        msgBox.setInformativeText("Please enter your email address to sign in.");
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setDefaultButton(QMessageBox::Ok);
        msgBox.exec();

        ui->lineEdit->setStyleSheet(
            "background-color: rgb(223, 223, 223);"
            "color: #b9b9b9;"
            "font-size: 14px;"
            "border: 2px solid #ff5555;"
            "border-radius: 6px;"
            "padding: 4px 8px;"
            );
        ui->lineEdit->setFocus();
        return;
    } else if (password.isEmpty()) {
        qDebug() << "Validation failed: Password is empty.";
        QMessageBox msgBox;
        msgBox.setWindowTitle("Login Error");
        msgBox.setText("Oops! You forgot to enter your password.");
        msgBox.setInformativeText("Please enter your password to sign in.");
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setDefaultButton(QMessageBox::Ok);
        msgBox.exec();

        ui->lineEdit_2->setStyleSheet(
            "background-color: rgb(223, 223, 223);"
            "color: #b9b9b9;"
            "font-size: 14px;"
            "border: 2px solid #ff5555;"
            "border-radius: 6px;"
            "padding: 4px 8px;"
            );
        ui->lineEdit_2->setFocus();
        return;
    }

    Employee emp;
    qDebug() << "Attempting to authenticate user with email:" << email;
    if (emp.authenticate(email, password)) {
        qDebug() << "Authentication successful for email:" << email;
        QSqlQuery query;
        QSqlDatabase db = QSqlDatabase::database();
        if (!db.isOpen()) {
            qDebug() << "Database connection is not open!";
            QMessageBox::critical(this, "Database Error", "Database connection is not open.");
            return;
        }

        // Start a transaction
        if (!db.transaction()) {
            qDebug() << "Failed to start transaction:" << db.lastError().text();
            QMessageBox::critical(this, "Database Error", "Failed to start transaction: " + db.lastError().text());
            return;
        }

        QSqlQuery userQuery;
        userQuery.exec("SELECT USER, SYS_CONTEXT('USERENV', 'CURRENT_SCHEMA') AS CURRENT_SCHEMA FROM DUAL");
        if (userQuery.next()) {
            qDebug() << "Connected as user:" << userQuery.value("USER").toString();
            qDebug() << "Current schema:" << userQuery.value("CURRENT_SCHEMA").toString();
        } else {
            qDebug() << "Failed to fetch user and schema:" << userQuery.lastError().text();
        }
        userQuery.finish(); // Finalize the userQuery

        // Fetch full employee data to store in SessionManager
        query.prepare("SELECT ID_EMP, NOM_EMP, PRENOM_EMP, EMAIL, MDP, NUM, DATEN, ROLE, FACE "
                      "FROM HOTSTUFF.EMPLOYE WHERE EMAIL = :email");
        query.bindValue(":email", email);

        qDebug() << "Executing query with bound values - email:" << email << "password:" << password;

        if (!query.exec()) {
            qDebug() << "Query execution failed:" << query.lastError().text();
            qDebug() << "Database error:" << db.lastError().text();
            db.rollback();
            QMessageBox::critical(this, "Database Error", "Failed to retrieve employee data: " + query.lastError().text());
            return;
        }

        if (!query.next()) {
            qDebug() << "No employee found with the given email and password.";
            db.rollback();
            QMessageBox::critical(this, "Database Error", "No employee found with the given email and password.");
            return;
        }

        Employee loggedInEmployee(
            query.value("ID_EMP").toInt(),
            query.value("NOM_EMP").toString(),
            query.value("PRENOM_EMP").toString(),
            query.value("EMAIL").toString(),
            query.value("NUM").toString(),
            query.value("DATEN").toDate(),
            query.value("ROLE").toString(),
            "",
            query.value("FACE").toByteArray()
            );

        // Store the employee in SessionManager
        SessionManager::instance().setCurrentUser(loggedInEmployee);
        qDebug() << "User stored in SessionManager - ID:" << loggedInEmployee.getId() << "Role:" << loggedInEmployee.getRole();

        // Finalize the query
        while (query.next()) {} // Consume any remaining rows
        query.finish();

        // Commit the transaction
        if (!db.commit()) {
            qDebug() << "Failed to commit transaction:" << db.lastError().text();
            db.rollback();
            QMessageBox::critical(this, "Database Error", "Failed to commit transaction: " + db.lastError().text());
            return;
        }

        // Use SessionManager to get the role and ID
        const Employee& currentUser = SessionManager::instance().getCurrentUser();
        QString role = currentUser.getRole();
        int empId = currentUser.getId();

        if (role.toLower() == "coach") {
            qDebug() << "User is a coach, checking for existing team...";
            Team teamManager;
            Team* team = teamManager.getTeamByCoachId(empId);

            if (team == nullptr) {
                FormAdd *formAdd = new FormAdd(this);
                formAdd->showMaximized();
            } else {
                qDebug() << "Team found for coach, opening CoachWindow...";
                CoachWindow *coachWindow = new CoachWindow(this);
                coachWindow->showMaximized();
            }
        } else if (role.toLower() == "employee") {
            qDebug() << "User is an employee, opening EmployeeWindow...";
            EmployeeWindow *employeeWindow = new EmployeeWindow(this);
            employeeWindow->showMaximized();
            qDebug() << "EmployeeWindow shown.";
        } else if (role.toLower() == "admin") {
            qDebug() << "User is an admin, opening AdminWindow...";
            AdminWindow *adminWindow = new AdminWindow(this);
            adminWindow->showMaximized();
        }
    } else {
        qDebug() << "Authentication failed for email:" << email;
        QMessageBox msgBox;
        msgBox.setWindowTitle("Login Error");
        msgBox.setText("Incorrect email or password.");
        msgBox.setInformativeText("Please double-check your credentials or use 'Forgot Password?' to reset your password.");
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setDefaultButton(QMessageBox::Ok);
        msgBox.exec();

        ui->lineEdit->clear();
        ui->lineEdit_2->clear();
        ui->lineEdit->setFocus();
    }
    this->hide(); // Close the MainWindow after sign-in
}

void MainWindow::on_sign_in_2_clicked() {
    // Check if a RecoverPasswordDialog is already open
    RecoverPasswordDialog *existingDialog = findChild<RecoverPasswordDialog*>();
    if (existingDialog) {
        qDebug() << "RecoverPasswordDialog already open, bringing to front";
        existingDialog->raise();
        existingDialog->activateWindow();
        return;
    }

    qDebug() << "Recover password button clicked";
    RecoverPasswordDialog *dialog = new RecoverPasswordDialog(this);
    dialog->show();
}


void MainWindow::on_togglePasswordButton_clicked() {
    if (isPasswordVisible) {
        // Hide password
        ui->lineEdit_2->setEchoMode(QLineEdit::Password);
        ui->togglePasswordButton->setIcon(QIcon(":/img/eye_off.png"));
        isPasswordVisible = false;
    } else {
        // Show password
        ui->lineEdit_2->setEchoMode(QLineEdit::Normal);
        ui->togglePasswordButton->setIcon(QIcon(":/img/eye_on.png"));
        isPasswordVisible = true;
    }
}
