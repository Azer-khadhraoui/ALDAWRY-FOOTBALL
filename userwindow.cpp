#include "userwindow.h"
#include "ui_user.h"
#include <QMessageBox>
#include <QSqlRecord>
#include <QSqlDatabase>
#include <QSqlError>


#include <QPixmap>
#include <QDebug>
#include <QMessageBox>
#include <QSqlTableModel>
#include <QIntValidator>
#include <QTableView>
#include <QSqlRecord>
#include <QMetaObject>
#include <QPdfWriter>
#include <QPrinter>
#include <QPrintDialog>
#include <QFileDialog>
#include <QPainter>
#include <QTextDocument>
#include <QTextStream>
#include <QStringListModel>
#include <QtCharts>
#include <QtCharts/QChartView>
#include <QtCharts/QBarSet>
#include <QtCharts/QBarSeries>
#include <QtCharts/QLegend>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QtWidgets/QVBoxLayout>
#include <QtCharts/QBarSeries>

#include <QUrlQuery>
#include <QJsonObject>
#include <QJsonDocument>
#include <QFileDialog>
#include <QPixmap>
#include <QSqlRecord>


UserWindow::UserWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isOpen()) {
        QMessageBox::critical(this, "Error", "Database connection lost. Please restart the application.");
        return;
    }
    connect(ui->tableView_3, &QTableView::clicked, this, &UserWindow::populateModifyFields);
    QSqlQueryModel *model = Employee::displayEmployees();
    if (!model) {
        QMessageBox::critical(this, "Error", "Failed to load employees. Ensure the table exists.");
    } else {
        ui->tableView_3->setModel(model);
        ui->tableView_3->resizeColumnsToContents();
    }

    connect(ui->searchButton, &QPushButton::clicked, this, &UserWindow::on_searchButton_clicked);
}

UserWindow::~UserWindow() {
    delete ui;
}

void UserWindow::on_button1_clicked() {
    // Check if database connection is still open
    if (!QSqlDatabase::database().isOpen()) {
        QMessageBox::critical(this, "Error", "Database connection is not open. Please restart the application.");
        return;
    }

    QString firstName = ui->nom->text();
    QString lastName = ui->prenom->text();
    QString email = ui->email->text();
    QString mobileNumber = ui->number->text();
    QString role = ui->Role->currentText();
    QString password = ui->password->text();

    // Validate input lengths (updated to 100 characters to match database)
    if (firstName.length() > 100 || lastName.length() > 100 || email.length() > 100 ||
        role.length() > 100 || password.length() > 100) {
        QMessageBox::critical(this, "Error", "Input exceeds maximum length (100 characters) for First Name, Last Name, Email, Role, or Password.");
        return;
    }
    if (mobileNumber.length() > 10) {
        QMessageBox::critical(this, "Error", "Mobile Number exceeds maximum length (10 digits).");
        return;
    }

    // Basic email validation
    if (!email.contains('@') || !email.contains('.')) {
        QMessageBox::critical(this, "Error", "Please enter a valid email address (e.g., example@domain.com).");
        return;
    }

    // Create Employee object with selectedEmployeeId
    Employee emp(
        selectedEmployeeId, // Use the tracked ID (0 for new, non-zero for update)
        firstName,
        lastName,
        email,
        mobileNumber,
        ui->birthday->date(),
        role,
        password
        );

    bool success;
    QString message;
    if (selectedEmployeeId == 0) {
        // Add new employee
        success = emp.addEmployee();
        message = "Employee added successfully!";
    } else {
        // Update existing employee
        success = emp.updateEmployee();
        message = "Employee updated successfully!";
    }

    if (success) {
        QMessageBox::information(this, "Success", message);
        ui->nom->clear();
        ui->prenom->clear();
        ui->email->clear();
        ui->number->clear();
        ui->password->clear();
        selectedEmployeeId = 0; // Reset after operation
        if (ui->tabWidget->currentIndex() == 1) {
            ui->tableView_3->setModel(Employee::displayEmployees());
            ui->tableView_3->resizeColumnsToContents();
        }
    } else {
        QMessageBox::critical(this, "Error", "Operation failed. Check input lengths and database permissions. Error: " + QSqlDatabase::database().lastError().text());
    }
}

void UserWindow::on_pushButton_3_clicked() { // Delete
    QModelIndexList selected = ui->tableView_3->selectionModel()->selectedRows();
    if (selected.isEmpty()) {
        QMessageBox::warning(this, "Warning", "Please select an employee to delete.");
        return;
    }
    int id = ui->tableView_3->model()->data(selected[0]).toInt();
    if (Employee().deleteEmployee(id)) {
        QMessageBox::information(this, "Success", "Employee deleted successfully!");
        ui->tableView_3->setModel(Employee::displayEmployees());
        ui->tableView_3->resizeColumnsToContents();
    } else {
        QMessageBox::critical(this, "Error", "Failed to delete employee.");
    }
}

void UserWindow::on_pushButton_4_clicked() { // Modify
    // Validate input lengths (updated to 100 characters to match database)
    QModelIndexList selected = ui->tableView_3->selectionModel()->selectedRows();
    if (selected.isEmpty()) {
        QMessageBox::warning(this, "Warning", "Please select an employee to modify.");
        return;
    }
    int id = ui->tableView_3->model()->data(selected[0]).toInt();


    QString firstName = ui->nom->text();
    QString lastName = ui->prenom->text();
    QString email = ui->email->text();
    QString mobileNumber = ui->number->text();
    QString role = ui->Role->currentText();
    QString password = ui->password->text();
    Employee emp(id, firstName, lastName, email, mobileNumber, ui->birthday->date(), role, password);

    if (firstName.length() > 10 || lastName.length() > 10 || email.length() > 10 ||
        role.length() > 10 || password.length() > 10) {
        QMessageBox::critical(this, "Error", "Input exceeds maximum length (100 characters) for First Name, Last Name, Email, Role, or Password.");
        return;
    }
    if (mobileNumber.length() > 10) {
        QMessageBox::critical(this, "Error", "Mobile Number exceeds maximum length (10 digits).");
        return;
    }


    if (emp.updateEmployee()) {
        QMessageBox::information(this, "Success", "Employee updated successfully!");
        ui->tableView_3->setModel(Employee::displayEmployees());
        ui->tableView_3->resizeColumnsToContents();
    } else {
        QMessageBox::critical(this, "Error", "Failed to update employee.");
    }
}

void UserWindow::on_tabWidget_currentChanged(int index) {
    if (index == 1) { // Display tab
        ui->tableView_3->setModel(Employee::displayEmployees());
        ui->tableView_3->resizeColumnsToContents();
    }
}

void UserWindow::populateModifyFields(const QModelIndex &index) {
    QSqlQueryModel *model = qobject_cast<QSqlQueryModel*>(ui->tableView_3->model());
    if (!model) return;

    // Get the employee ID from the selected row
    QSqlRecord record = model->record(index.row());
    int empId = record.value("ID_EMP").toInt();

    // Create a temporary Employee object and use its static method
    Employee emp;
    Employee* employee = emp.getById(empId);

    if (employee) {
        // Populate the form fields with the employee data
        ui->lineEdit_3->setText(employee->getLastName());
        ui->lineEdit_4->setText(employee->getFirstName());
        ui->lineEdit_6->setText(employee->getEmail());
        ui->lineEdit_8->setText(employee->getMobileNumber());
        ui->dateEdit->setDate(employee->getDateOfBirth());
        ui->comboBox_3->setCurrentText(employee->getRole());
        ui->lineEdit_7->setText(""); // Password not displayed for security

        // Store the selected employee ID
        selectedEmployeeId = empId;

        // Switch to the "modify user" tab
        ui->tabWidget->setCurrentIndex(2);

        // Free the employee object to prevent memory leaks
        delete employee;
    }
}
void UserWindow::on_pushButton_2_clicked() {
    // Create an Employee object with the updated information
    Employee employee;

    // Set the ID of the employee to be updated
    employee.setId(selectedEmployeeId);

    // Get values from the form fields
    employee.setLastName(ui->lineEdit_3->text());
    employee.setFirstName(ui->lineEdit_4->text());
    employee.setEmail(ui->lineEdit_6->text());
    employee.setMobileNumber(ui->lineEdit_8->text());
    employee.setDateOfBirth(ui->dateEdit->date());
    employee.setRole(ui->comboBox_3->currentText());

    // Only update password if a new one was entered
    QString password = ui->lineEdit_7->text();
    if (!password.isEmpty()) {
        employee.setPassword(password);
    }

    // Call the update method
    bool success = employee.updateEmployee();

    if (success) {
        QMessageBox::information(this, "Success", "Employee information updated successfully.");

        // Refresh the table view to show updated data
        refreshEmployeeTable();

        // Clear the form fields
        clearModifyFields();

        // Switch back to the employee list tab
        ui->tabWidget->setCurrentIndex(0);
    } else {
        QMessageBox::critical(this, "Error", "Failed to update employee information.");
    }
}

// Helper method to refresh the employee table
void UserWindow::refreshEmployeeTable() {
    Employee emp;
    ui->tableView_3->setModel(emp.displayEmployees());
}

// Helper method to clear the modify form fields
void UserWindow::clearModifyFields() {
    ui->lineEdit_3->clear();
    ui->lineEdit_4->clear();
    ui->lineEdit_6->clear();
    ui->lineEdit_7->clear();
    ui->lineEdit_8->clear();
    ui->dateEdit->setDate(QDate::currentDate());
    ui->comboBox_3->setCurrentIndex(0);
}
void UserWindow::on_searchButton_clicked() {
    if (!QSqlDatabase::database().isOpen()) {
        QMessageBox::critical(this, "Error", "Database connection is not open.");
        return;
    }

    QString searchTerm = ui->lineEdit_10->text().trimmed();
    if (searchTerm.isEmpty()) {
        QMessageBox::warning(this, "Warning", "Please enter a search term.");
        ui->tableView_3->setModel(Employee::displayEmployees());
        ui->tableView_3->resizeColumnsToContents();
        return;
    }

    // Default to searching by "First Name" for now
    QSqlQueryModel* model = Employee::search("First Name", searchTerm);
    if (!model) {
        QMessageBox::critical(this, "Error", "Search failed.");
        return;
    }

    ui->tableView_3->setModel(model);
    ui->tableView_3->resizeColumnsToContents();

    if (model->rowCount() == 0) {
        QMessageBox::information(this, "No Results", "No employees found.");
    }
}
