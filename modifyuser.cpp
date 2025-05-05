#include "modifyuser.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QDebug>
#include <QSqlDatabase>
#include <QRegularExpression>
#include <QCryptographicHash>
#include <QUuid>
#include <QSqlQuery>
#include <QSqlError>

ModifyUser::ModifyUser(int userId, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Form),
    userId(userId),
    employee(nullptr)
{
    ui->setupUi(this);
    setWindowTitle("Modify User");

    setModal(true);

    ui->comboBox_3->clear();
    ui->comboBox_3->addItems({"Admin", "Employee", "Coach"});

    loadUserData();

    connect(ui->pushButton_2, &QPushButton::clicked, this, &ModifyUser::on_pushButton_2_clicked);
    connect(ui->modifyUploadPhotoButton, &QPushButton::clicked, this, &ModifyUser::on_modifyUploadPhotoButton_clicked);
}

ModifyUser::~ModifyUser()
{
    delete employee;
    delete ui;
}

void ModifyUser::loadUserData()
{
    if (!QSqlDatabase::database().isOpen()) {
        QMessageBox::critical(this, "Error", "Database connection is not open.");
        return;
    }

    employee = Employee().getById(userId);
    if (!employee) {
        QMessageBox::critical(this, "Error", "Failed to retrieve user data.");
        reject();
        return;
    }

    ui->lineEdit_3->setText(employee->getLastName());
    ui->lineEdit_4->setText(employee->getFirstName());
    ui->dateEdit->setDate(employee->getDateOfBirth());
    ui->lineEdit_8->setText(employee->getMobileNumber());
    ui->lineEdit_6->setText(employee->getEmail());
    ui->lineEdit_7->setText("");
    ui->comboBox_3->setCurrentText(employee->getRole());

    photoData = employee->getFace();
    if (!photoData.isEmpty()) {
        QPixmap pixmap;
        if (pixmap.loadFromData(photoData)) {
            ui->modifyUploadPhotoButton->setText("Photo Loaded (Click to Change)");
        } else {
            ui->modifyUploadPhotoButton->setText("Invalid Photo (Click to Upload)");
        }
    } else {
        ui->modifyUploadPhotoButton->setText("No Photo (Click to Upload)");
    }

    qDebug() << "Loaded user data for ID:" << userId;
}

bool ModifyUser::checkUniqueFields(const QString& email, const QString& mobileNumber)
{
    QSqlQuery query;
    // Updated schema to ALDAWYRY and treat NUM as a string in the query
    query.prepare("SELECT COUNT(*) FROM EMPLOYE WHERE (UPPER(EMAIL) = UPPER(:email) OR TO_CHAR(NUM) = :mobile) AND ID_EMP != :id");
    query.bindValue(":email", email);
    query.bindValue(":mobile", mobileNumber); // Bind as string to avoid type issues
    query.bindValue(":id", userId);

    if (!query.exec()) {
        qDebug() << "Unique check query failed:" << query.lastError().text();
        qDebug() << "Database error:" << QSqlDatabase::database().lastError().text();
        qDebug() << "Query executed:" << query.lastQuery();
        qDebug() << "Bound values - email:" << email << "mobile:" << mobileNumber << "id:" << userId;
        QMessageBox::critical(this, "Database Error", "Failed to check uniqueness of email or mobile number: " + query.lastError().text());
        return false; // On query failure, treat as if the values exist to prevent updating with invalid data
    }

    if (query.next()) {
        int count = query.value(0).toInt();
        qDebug() << "Unique check result - count:" << count;
        return count == 0; // Return true if no duplicates found (count == 0)
    }

    qDebug() << "Unique check query returned no results.";
    return false; // If query doesn't return results, treat as failure
}

bool ModifyUser::validateStrongPassword(const QString& password)
{
    if (password.length() < 8) return false;

    QRegularExpression passwordRegex("^(?=.*[a-z])(?=.*[A-Z])(?=.*\\d)(?=.*[@$!%*?&])[A-Za-z\\d@$!%*?&]{8,}$");
    return passwordRegex.match(password).hasMatch();
}

bool ModifyUser::validateInputs()
{
    if (ui->lineEdit_3->text().trimmed().isEmpty() ||
        ui->lineEdit_4->text().trimmed().isEmpty() ||
        ui->lineEdit_6->text().trimmed().isEmpty() ||
        ui->lineEdit_8->text().trimmed().isEmpty()) {
        QMessageBox::warning(this, "Validation Error", "First Name, Last Name, Email, and Mobile Number are required.");
        return false;
    }

    if (ui->lineEdit_3->text().length() > 100 ||
        ui->lineEdit_4->text().length() > 100 ||
        ui->lineEdit_6->text().length() > 100 ||
        ui->comboBox_3->currentText().length() > 100) {
        QMessageBox::warning(this, "Validation Error", "Input fields cannot exceed 100 characters.");
        return false;
    }

    QRegularExpression phoneRegex("^[0-9]{8,}$");
    if (!phoneRegex.match(ui->lineEdit_8->text()).hasMatch()) {
        QMessageBox::warning(this, "Validation Error", "Mobile number must be at least 8 digits and contain only numbers.");
        return false;
    }

    QDate dob = ui->dateEdit->date();
    QDate currentDate = QDate::currentDate();
    int age = dob.daysTo(currentDate) / 365;
    if (age <= 20) {
        QMessageBox::warning(this, "Validation Error", "Employee must be over 20 years old.");
        return false;
    }

    if (!checkUniqueFields(ui->lineEdit_6->text().trimmed(), ui->lineEdit_8->text().trimmed())) {
        QMessageBox::warning(this, "Validation Error", "Email or Mobile number already exists for another employee.");
        return false;
    }

    if (!ui->lineEdit_7->text().isEmpty()) {
        if (ui->lineEdit_7->text().length() > 110) {
            QMessageBox::warning(this, "Validation Error", "Password cannot exceed 110 characters.");
            return false;
        }
        if (!validateStrongPassword(ui->lineEdit_7->text())) {
            QMessageBox::warning(this, "Validation Error", "Password must be at least 8 characters long and include uppercase, lowercase, number, and special character.");
            return false;
        }
    }

    if (photoData.size() > 5 * 1024 * 1024) {
        QMessageBox::warning(this, "Validation Error", "Photo size cannot exceed 5 MB.");
        return false;
    }

    return true;
}

void ModifyUser::on_pushButton_2_clicked()
{
    if (!QSqlDatabase::database().isOpen()) {
        QMessageBox::critical(this, "Error", "Database connection is not open.");
        return;
    }

    if (!validateInputs()) {
        return;
    }

    QString password = ui->lineEdit_7->text().trimmed();
    if (!password.isEmpty()) {
        QString salt = QUuid::createUuid().toString();
        QString saltedPassword = password + salt;
        QString hashed = QString(QCryptographicHash::hash(saltedPassword.toUtf8(), QCryptographicHash::Sha256).toHex());
        password = hashed + ":" + salt;
    }

    employee->setFirstName(ui->lineEdit_4->text().trimmed());
    employee->setLastName(ui->lineEdit_3->text().trimmed());
    employee->setEmail(ui->lineEdit_6->text().trimmed());
    employee->setMobileNumber(ui->lineEdit_8->text().trimmed());
    employee->setDateOfBirth(ui->dateEdit->date());
    employee->setRole(ui->comboBox_3->currentText());
    if (!password.isEmpty()) {
        employee->setPassword(password);
    }
    employee->setFace(photoData);

    if (employee->updateEmployee()) {
        QMessageBox::information(this, "Success", "User modified successfully!");
        accept();
    } else {
        QMessageBox::critical(this, "Error", "Failed to modify user. Check database permissions or constraints.");
    }
}

void ModifyUser::on_modifyUploadPhotoButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    "Select Photo", "",
                                                    "Images (*.png *.jpg *.jpeg *.bmp)");
    if (fileName.isEmpty()) {
        return;
    }

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox::critical(this, "Error", "Unable to open the selected file.");
        return;
    }

    photoData = file.readAll();
    file.close();

    if (photoData.size() > 5 * 1024 * 1024) {
        QMessageBox::warning(this, "Error", "Photo size cannot exceed 5 MB.");
        photoData.clear();
        ui->modifyUploadPhotoButton->setText("Upload Photo here");
        return;
    }

    QPixmap pixmap;
    if (pixmap.loadFromData(photoData)) {
        ui->modifyUploadPhotoButton->setText("Photo Uploaded (Click to Change)");
        qDebug() << "Photo uploaded successfully, size:" << photoData.size() << "bytes";
    } else {
        QMessageBox::warning(this, "Error", "Invalid image format.");
        photoData.clear();
        ui->modifyUploadPhotoButton->setText("Upload Photo here");
    }
}
