#include "../userheaders/adduser.h"
#include "ui_adduser.h"
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlError>
#include <QFileDialog>
#include <QDebug>
#include <QPushButton>
#include <QCryptographicHash>
#include <QUuid>
#include <QRegularExpression>

AddUser::AddUser(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddUser),
    isProcessing(false)
{
    ui->setupUi(this);
    setWindowTitle("Add New User");

    connect(ui->button1, &QPushButton::clicked, this, &AddUser::on_button1_clicked);
    connect(ui->uploadPhotoButton, &QPushButton::clicked, this, &AddUser::on_uploadPhotoButton_clicked);
}

AddUser::~AddUser()
{
    delete ui;
}

bool AddUser::checkUniqueFields(const QString& email, const QString& mobileNumber)
{
    QSqlQuery query;
    // Updated schema to ALDAWYRY and treat NUM as a string in the query
    query.prepare("SELECT COUNT(*) FROM EMPLOYE WHERE UPPER(EMAIL) = UPPER(:email) OR TO_CHAR(NUM) = :mobile");
    query.bindValue(":email", email);
    query.bindValue(":mobile", mobileNumber); // Bind as string to avoid type issues

    if (!query.exec()) {
        qDebug() << "Unique check query failed:" << query.lastError().text();
        qDebug() << "Database error:" << QSqlDatabase::database().lastError().text();
        qDebug() << "Query executed:" << query.lastQuery();
        qDebug() << "Bound values - email:" << email << "mobile:" << mobileNumber;
        QMessageBox::critical(this, "Database Error", "Failed to check uniqueness of email or mobile number: " + query.lastError().text());
        return false; // On query failure, treat as if the values exist to prevent adding invalid data
    }

    if (query.next()) {
        int count = query.value(0).toInt();
        qDebug() << "Unique check result - count:" << count;
        return count == 0; // Return true if no duplicates found (count == 0)
    }

    qDebug() << "Unique check query returned no results.";
    return false; // If query doesn't return results, treat as failure
}

bool AddUser::validateStrongPassword(const QString& password)
{
    if (password.length() < 8) return false;

    QRegularExpression passwordRegex("^(?=.*[a-z])(?=.*[A-Z])(?=.*\\d)(?=.*[@$!%*?&])[A-Za-z\\d@$!%*?&]{8,}$");
    return passwordRegex.match(password).hasMatch();
}

void AddUser::on_button1_clicked()
{
    if (isProcessing) {
        qDebug() << "on_button1_clicked: Already processing, ignoring additional click.";
        return;
    }

    isProcessing = true;
    disconnect(ui->button1, &QPushButton::clicked, this, &AddUser::on_button1_clicked);

    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isOpen()) {
        qDebug() << "Database connection is not open.";
        QMessageBox::critical(this, "Error", "Database connection is not open. Please restart the application.");
        isProcessing = false;
        connect(ui->button1, &QPushButton::clicked, this, &AddUser::on_button1_clicked);
        return;
    }

    QString lastName = ui->nom->text().trimmed();
    QString firstName = ui->prenom->text().trimmed();
    QString email = ui->email->text().trimmed();
    QString mobileNumber = ui->number->text().trimmed();
    QString role = ui->Role->currentText().trimmed();
    QString password = ui->password->text().trimmed();
    QDate dob = ui->birthday->date();

    qDebug() << "Add Employee Inputs:"
             << "First Name:" << firstName
             << "Last Name:" << lastName
             << "Email:" << email
             << "Mobile Number:" << mobileNumber
             << "Role:" << role
             << "Password:" << (password.isEmpty() ? "[empty]" : "[set]")
             << "DOB:" << dob.toString("yyyy-MM-dd")
             << "Photo Size:" << newEmployeePhoto.size() << "bytes";

    if (firstName.isEmpty() || lastName.isEmpty() || email.isEmpty() || mobileNumber.isEmpty() || role.isEmpty()) {
        qDebug() << "Validation failed: Required fields are empty.";
        QMessageBox::critical(this, "Error", "All fields except Password are required.");
        isProcessing = false;
        connect(ui->button1, &QPushButton::clicked, this, &AddUser::on_button1_clicked);
        return;
    }

    if (firstName.length() > 100 || lastName.length() > 100 || email.length() > 100 ||
        role.length() > 100 || (!password.isEmpty() && password.length() > 100)) {
        qDebug() << "Validation failed: Input exceeds 100 characters.";
        QMessageBox::critical(this, "Error", "Input exceeds maximum length (100 characters).");
        isProcessing = false;
        connect(ui->button1, &QPushButton::clicked, this, &AddUser::on_button1_clicked);
        return;
    }

    if (mobileNumber.length() > 10) {
        qDebug() << "Validation failed: Mobile number exceeds 10 digits.";
        QMessageBox::critical(this, "Error", "Mobile Number exceeds maximum length (10 digits).");
        isProcessing = false;
        connect(ui->button1, &QPushButton::clicked, this, &AddUser::on_button1_clicked);
        return;
    }

    if (!email.contains('@') || !email.contains('.')) {
        qDebug() << "Validation failed: Invalid email format.";
        QMessageBox::critical(this, "Error", "Please enter a valid email address (e.g., example@domain.com).");
        isProcessing = false;
        connect(ui->button1, &QPushButton::clicked, this, &AddUser::on_button1_clicked);
        return;
    }

    QRegularExpression re("^[0-9]{8,}$");
    if (!re.match(mobileNumber).hasMatch()) {
        qDebug() << "Validation failed: Invalid mobile number.";
        QMessageBox::critical(this, "Error", "Mobile Number must contain only numbers and be at least 8 digits long.");
        isProcessing = false;
        connect(ui->button1, &QPushButton::clicked, this, &AddUser::on_button1_clicked);
        return;
    }

    if (!dob.isValid()) {
        qDebug() << "Validation failed: Invalid date of birth.";
        QMessageBox::critical(this, "Error", "Invalid date of birth.");
        isProcessing = false;
        connect(ui->button1, &QPushButton::clicked, this, &AddUser::on_button1_clicked);
        return;
    }

    QDate currentDate = QDate::currentDate();
    int age = dob.daysTo(currentDate) / 365;
    if (age <= 20) {
        qDebug() << "Validation failed: Employee must be over 20 years old.";
        QMessageBox::critical(this, "Error", "Employee must be over 20 years old.");
        isProcessing = false;
        connect(ui->button1, &QPushButton::clicked, this, &AddUser::on_button1_clicked);
        return;
    }

    if (!checkUniqueFields(email, mobileNumber)) {
        qDebug() << "Validation failed: Email or Mobile number already exists.";
        QMessageBox::critical(this, "Error", "Email or Mobile number already exists in the database.");
        isProcessing = false;
        connect(ui->button1, &QPushButton::clicked, this, &AddUser::on_button1_clicked);
        return;
    }

    if (!password.isEmpty() && !validateStrongPassword(password)) {
        qDebug() << "Validation failed: Password not strong enough.";
        QMessageBox::critical(this, "Error", "Password must be at least 8 characters long and include uppercase, lowercase, number, and special character.");
        isProcessing = false;
        connect(ui->button1, &QPushButton::clicked, this, &AddUser::on_button1_clicked);
        return;
    }

    if (newEmployeePhoto.size() > 5 * 1024 * 1024) {
        qDebug() << "Validation failed: Photo size exceeds 5MB.";
        QMessageBox::critical(this, "Error", "Photo size exceeds 5MB limit.");
        isProcessing = false;
        connect(ui->button1, &QPushButton::clicked, this, &AddUser::on_button1_clicked);
        return;
    }

    bool ok;
    qlonglong mobileNumLong = mobileNumber.toLongLong(&ok);
    if (!ok || mobileNumLong > 9999999999LL) {
        qDebug() << "Validation failed: Invalid mobile number range.";
        QMessageBox::critical(this, "Error", "Mobile Number is too large or invalid.");
        isProcessing = false;
        connect(ui->button1, &QPushButton::clicked, this, &AddUser::on_button1_clicked);
        return;
    }

    if (!password.isEmpty()) {
        QString salt = QUuid::createUuid().toString();
        QString saltedPassword = password + salt;
        QString hashed = QString(QCryptographicHash::hash(saltedPassword.toUtf8(), QCryptographicHash::Sha256).toHex());
        password = hashed + ":" + salt;
    }

    int newId = 0;
    QSqlQuery idQuery;
    idQuery.exec("SELECT NVL(MAX(ID_EMP), 0) + 1 FROM EMPLOYE");
    if (idQuery.next()) {
        newId = idQuery.value(0).toInt();
        qDebug() << "Generated new ID:" << newId;
    } else {
        qDebug() << "Failed to generate ID:" << idQuery.lastError().text();
        QMessageBox::critical(this, "Error", "Failed to generate employee ID: " + idQuery.lastError().text());
        isProcessing = false;
        connect(ui->button1, &QPushButton::clicked, this, &AddUser::on_button1_clicked);
        return;
    }

    Employee emp(
        newId,
        firstName,
        lastName,
        email,
        mobileNumber,
        dob,
        role,
        password,
        newEmployeePhoto
        );

    if (emp.addEmployee()) {
        qDebug() << "Employee added successfully.";
        QMessageBox::information(this, "Success", "Employee added successfully!");
        ui->nom->clear();
        ui->prenom->clear();
        ui->email->clear();
        ui->number->clear();
        ui->password->clear();
        ui->birthday->setDate(QDate::currentDate());
        ui->Role->setCurrentIndex(0);
        newEmployeePhoto.clear();
        this->accept();
    } else {
        QString dbError = QSqlDatabase::database().lastError().text();
        if (dbError.isEmpty()) {
            qDebug() << "Failed to add employee: Validation or database error.";
            QMessageBox::critical(this, "Error", "Failed to add employee. Check input data (e.g., field lengths) and database permissions.");
        } else {
            qDebug() << "Failed to add employee. Database error:" << dbError;
            QMessageBox::critical(this, "Error", "Failed to add employee. Database error: " + dbError);
        }
        isProcessing = false;
        connect(ui->button1, &QPushButton::clicked, this, &AddUser::on_button1_clicked);
    }
}

void AddUser::on_uploadPhotoButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Select Photo", "", "Images (*.png *.jpg *.jpeg *.bmp)");
    if (fileName.isEmpty()) return;

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox::critical(this, "Error", "Unable to open the selected file: " + file.errorString());
        return;
    }

    newEmployeePhoto = file.readAll();
    file.close();

    qDebug() << "Uploaded photo size:" << newEmployeePhoto.size() << "bytes";

    if (newEmployeePhoto.size() > 5 * 1024 * 1024) {
        QMessageBox::critical(this, "Error", "Photo size exceeds 5MB limit.");
        newEmployeePhoto.clear();
        return;
    }

    QMessageBox::information(this, "Success", "Photo uploaded successfully.");
}
