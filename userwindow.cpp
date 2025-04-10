#include "userwindow.h"
#include "ui_user.h"
#include <QMessageBox>
#include <QSqlRecord>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QTableView>
#include <QPdfWriter>
#include <QPainter>
#include <QFileDialog>
#include <QTextDocument>
#include <QDate>

UserWindow::UserWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isOpen()) {
        QMessageBox::critical(this, "Error", "Database connection lost. Please restart the application.");
        return;
    }

    // Initialize the proxy model
    proxyModel = new QSortFilterProxyModel(this);

    // Set up the table view for sorting
    ui->tableView_3->setSortingEnabled(true);
    ui->tableView_3->horizontalHeader()->setSortIndicatorShown(true);
    ui->tableView_3->horizontalHeader()->setSectionsClickable(true);

    QSqlQueryModel *sourceModel = Employee::displayEmployees();
    if (!sourceModel) {
        QMessageBox::critical(this, "Error", "Failed to load employees. Ensure the table exists.");
    } else {
        proxyModel->setSourceModel(sourceModel);
        ui->tableView_3->setModel(proxyModel);
        ui->tableView_3->hideColumn(0); // Hide the ID column (index 0)
        ui->tableView_3->resizeColumnsToContents();
    }

    // Connect signals to slots
    connect(ui->tableView_3, &QTableView::clicked, this, &UserWindow::populateModifyFields);
    connect(ui->searchButton, &QPushButton::clicked, this, &UserWindow::on_searchButton_clicked);
    connect(ui->pdfButton, &QPushButton::clicked, this, &UserWindow::on_pdfButton_clicked);
    connect(ui->statButton, &QPushButton::clicked, this, &UserWindow::on_statButton_clicked);
}

UserWindow::~UserWindow() {
    delete proxyModel;
    delete ui;
}

void UserWindow::on_button1_clicked() {
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

    if (firstName.length() > 100 || lastName.length() > 100 || email.length() > 100 ||
        role.length() > 100 || password.length() > 100) {
        QMessageBox::critical(this, "Error", "Input exceeds maximum length (100 characters) for First Name, Last Name, Email, Role, or Password.");
        return;
    }
    if (mobileNumber.length() > 10) {
        QMessageBox::critical(this, "Error", "Mobile Number exceeds maximum length (10 digits).");
        return;
    }

    if (!email.contains('@') || !email.contains('.')) {
        QMessageBox::critical(this, "Error", "Please enter a valid email address (e.g., example@domain.com).");
        return;
    }

    // Add phone number validation
    if (!validatePhoneNumber(mobileNumber)) {
        QMessageBox::critical(this, "Error", "Mobile Number must contain only numbers and be at least 8 digits long.");
        return;
    }

    // Add age validation
    QDate dob = ui->birthday->date();
    if (!validateAge(dob)) {
        QMessageBox::critical(this, "Error", "Employee must be at least 18 years old.");
        return;
    }

    Employee emp(
        selectedEmployeeId,
        firstName,
        lastName,
        email,
        mobileNumber,
        dob,
        role,
        password
        );

    bool success;
    QString message;
    if (selectedEmployeeId == 0) {
        success = emp.addEmployee();
        message = "Employee added successfully!";
    } else {
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
        selectedEmployeeId = 0;
        if (ui->tabWidget->currentIndex() == 1) {
            refreshEmployeeTable();
        }
    } else {
        QMessageBox::critical(this, "Error", "Operation failed. Check input lengths and database permissions. Error: " + QSqlDatabase::database().lastError().text());
    }
}

void UserWindow::on_pushButton_3_clicked() {
    QModelIndexList selected = ui->tableView_3->selectionModel()->selectedRows();
    if (selected.isEmpty()) {
        QMessageBox::warning(this, "Warning", "Please select an employee to delete.");
        return;
    }
    QModelIndex sourceIndex = proxyModel->mapToSource(selected[0]);
    int id = proxyModel->sourceModel()->data(sourceIndex.sibling(sourceIndex.row(), 0)).toInt(); // Get ID from hidden column

    if (Employee().deleteEmployee(id)) {
        QMessageBox::information(this, "Success", "Employee deleted successfully!");
        refreshEmployeeTable();
    } else {
        QMessageBox::critical(this, "Error", "Failed to delete employee.");
    }
}



void UserWindow::on_tabWidget_currentChanged(int index) {
    if (index == 1) {
        refreshEmployeeTable();
    }
}

void UserWindow::populateModifyFields(const QModelIndex &index) {
    QModelIndex sourceIndex = proxyModel->mapToSource(index);
    QSqlQueryModel *model = qobject_cast<QSqlQueryModel*>(proxyModel->sourceModel());
    if (!model) return;

    QSqlRecord record = model->record(sourceIndex.row());
    int empId = record.value("ID_EMP").toInt();

    Employee emp;
    Employee* employee = emp.getById(empId);

    if (employee) {
        ui->lineEdit_3->setText(employee->getLastName());
        ui->lineEdit_4->setText(employee->getFirstName());
        ui->lineEdit_6->setText(employee->getEmail());
        ui->lineEdit_8->setText(employee->getMobileNumber());
        ui->dateEdit->setDate(employee->getDateOfBirth());
        ui->comboBox_3->setCurrentText(employee->getRole());
        ui->lineEdit_7->setText("");

        selectedEmployeeId = empId;
        ui->tabWidget->setCurrentIndex(2);

        delete employee;
    }
}

void UserWindow::on_pushButton_2_clicked() {
    Employee employee;
    employee.setId(selectedEmployeeId);
    employee.setLastName(ui->lineEdit_3->text());
    employee.setFirstName(ui->lineEdit_4->text());
    employee.setEmail(ui->lineEdit_6->text());
    employee.setMobileNumber(ui->lineEdit_8->text());
    employee.setDateOfBirth(ui->dateEdit->date());
    employee.setRole(ui->comboBox_3->currentText());

    QString password = ui->lineEdit_7->text();
    if (!password.isEmpty()) {
        employee.setPassword(password);
    }

    if (employee.getFirstName().length() > 100 || employee.getLastName().length() > 100 ||
        employee.getEmail().length() > 100 || employee.getRole().length() > 100 ||
        (!password.isEmpty() && password.length() > 100)) {
        QMessageBox::critical(this, "Error", "Input exceeds maximum length (100 characters).");
        return;
    }

    // Add phone number validation
    if (!validatePhoneNumber(employee.getMobileNumber())) {
        QMessageBox::critical(this, "Error", "Mobile Number must contain only numbers and be at least 8 digits long.");
        return;
    }

    // Add age validation
    if (!validateAge(employee.getDateOfBirth())) {
        QMessageBox::critical(this, "Error", "Employee must be at least 18 years old.");
        return;
    }

    bool success = employee.updateEmployee();
    if (success) {
        QMessageBox::information(this, "Success", "Employee information updated successfully.");
        refreshEmployeeTable();
        clearModifyFields();
        ui->tabWidget->setCurrentIndex(0);
    } else {
        QMessageBox::critical(this, "Error", "Failed to update employee information.");
    }
}

void UserWindow::refreshEmployeeTable() {
    QSqlQueryModel *sourceModel = Employee::displayEmployees();
    if (!sourceModel) {
        QMessageBox::critical(this, "Error", "Failed to load employees. Ensure the table exists.");
        return;
    }
    proxyModel->setSourceModel(sourceModel);
    ui->tableView_3->hideColumn(0);
    ui->tableView_3->resizeColumnsToContents();
}

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
    QSqlQueryModel *sourceModel;

    if (searchTerm.isEmpty()) {
        sourceModel = Employee::displayEmployees();
    } else {
        sourceModel = Employee::search("First Name", searchTerm);
    }

    if (!sourceModel) {
        QMessageBox::critical(this, "Error", "Search failed.");
        return;
    }

    proxyModel->setSourceModel(sourceModel);
    ui->tableView_3->setModel(proxyModel);
    ui->tableView_3->hideColumn(0); // Hide the ID column
    ui->tableView_3->resizeColumnsToContents();

    if (sourceModel->rowCount() == 0) {
        QMessageBox::information(this, "No Results", "No employees found.");
    }
}

void UserWindow::on_pdfButton_clicked() {
    // Open a file dialog to let the user choose the save location
    QString fileName = QFileDialog::getSaveFileName(this, "Save PDF", "", "PDF Files (*.pdf)");
    if (fileName.isEmpty()) {
        return; // User canceled the dialog
    }

    // Ensure the file has a .pdf extension
    if (!fileName.endsWith(".pdf", Qt::CaseInsensitive)) {
        fileName += ".pdf";
    }

    // Create a QPdfWriter to write the PDF
    QPdfWriter pdfWriter(fileName);
    pdfWriter.setPageSize(QPageSize(QPageSize::A4));
    pdfWriter.setPageMargins(QMarginsF(30, 30, 30, 30)); // Set margins (left, top, right, bottom)

    // Create a QPainter to draw on the PDF
    QPainter painter(&pdfWriter);
    painter.setRenderHint(QPainter::Antialiasing);

    // Get the dimensions of the page (in painter units)
    int pageWidth = pdfWriter.width();
    int pageHeight = pdfWriter.height();

    // Define formatting variables
    int margin = 100; // Margin for the table
    int rowHeight = 300; // Height of each row in the table
    int fontSize = 10;
    int titleFontSize = 14;
    int colCount = 6; // Number of visible columns (excluding hidden ID column)
    int colWidth = (pageWidth - 2 * margin) / colCount; // Width of each column

    // Set up fonts
    QFont titleFont("Arial", titleFontSize, QFont::Bold);
    QFont headerFont("Arial", fontSize, QFont::Bold);
    QFont bodyFont("Arial", fontSize);

    // Draw the title
    painter.setFont(titleFont);
    painter.setPen(Qt::black);
    painter.drawText(margin, margin, "Employee List");

    // Move down for the table
    int yPos = margin + rowHeight;

    // Get the model from the table view
    QSqlQueryModel *model = qobject_cast<QSqlQueryModel*>(proxyModel->sourceModel());
    if (!model) {
        QMessageBox::critical(this, "Error", "Failed to access table data.");
        return;
    }

    // Get the number of rows and columns
    int rowCount = model->rowCount();
    int totalColCount = model->columnCount(); // Total columns including hidden ID

    // Draw the table headers with a colored background
    painter.setFont(headerFont);
    painter.setPen(Qt::black);
    painter.setBrush(QColor(173, 216, 230)); // Light blue background for headers
    for (int col = 0; col < totalColCount; col++) {
        if (col == 0) continue; // Skip the ID column (hidden)
        int xPos = margin + (col - 1) * colWidth;
        QRect headerRect(xPos, yPos, colWidth, rowHeight);
        painter.drawRect(headerRect); // Draw the cell border
        QString header = model->headerData(col, Qt::Horizontal).toString();
        painter.drawText(headerRect, Qt::AlignCenter | Qt::AlignVCenter, header);
    }
    yPos += rowHeight;

    // Draw the table data with alternating row colors
    painter.setFont(bodyFont);
    for (int row = 0; row < rowCount; row++) {
        // Set alternating row colors
        if (row % 2 == 0) {
            painter.setBrush(QColor(240, 240, 240)); // Light gray for even rows
        } else {
            painter.setBrush(Qt::white); // White for odd rows
        }

        for (int col = 0; col < totalColCount; col++) {
            if (col == 0) continue; // Skip the ID column
            int xPos = margin + (col - 1) * colWidth;
            QRect cellRect(xPos, yPos, colWidth, rowHeight);
            painter.drawRect(cellRect); // Draw the cell border
            painter.setPen(Qt::black);
            QString data = model->data(model->index(row, col)).toString();
            painter.drawText(cellRect, Qt::AlignCenter | Qt::AlignVCenter, data);
        }
        yPos += rowHeight;

        // Check if we need a new page
        if (yPos > pageHeight - margin - rowHeight) {
            pdfWriter.newPage();
            yPos = margin;
            // Redraw headers on the new page
            painter.setFont(headerFont);
            painter.setBrush(QColor(173, 216, 230)); // Light blue background for headers
            for (int col = 0; col < totalColCount; col++) {
                if (col == 0) continue;
                int xPos = margin + (col - 1) * colWidth;
                QRect headerRect(xPos, yPos, colWidth, rowHeight);
                painter.drawRect(headerRect);
                QString header = model->headerData(col, Qt::Horizontal).toString();
                painter.drawText(headerRect, Qt::AlignCenter | Qt::AlignVCenter, header);
            }
            yPos += rowHeight;
        }
    }

    // End painting
    painter.end();

    QMessageBox::information(this, "Success", "PDF generated successfully at: " + fileName);
}

void UserWindow::on_statButton_clicked() {
    collectStatistics(); // Prepare the data

    // If already exists, delete and re-create
    if (statsView) {
        delete statsView;
        statsView = nullptr;
    }

    // Create and embed the custom stats widget
    statsView = new statsWidget(this);
    statsView->setMinimumSize(ui->statsWidget->size()); // Optional: match size
    statsView->setAutoFillBackground(true);

    // Clear statsWidget container before inserting
    QLayout* layout = ui->statsWidget->layout();
    if (!layout) {
        layout = new QVBoxLayout(ui->statsWidget);
        ui->statsWidget->setLayout(layout);
    } else {
        QLayoutItem* item;
        while ((item = layout->takeAt(0)) != nullptr) {
            delete item->widget();
            delete item;
        }
    }

    layout->addWidget(statsView);
    statsView->show();
}


void UserWindow::showStatistics() {
    // This method is no longer needed since we're displaying directly in the UI
    // But since it's in your code, I'll keep it and make it call on_statButton_clicked
    on_statButton_clicked();
}


bool UserWindow::validatePhoneNumber(const QString& mobileNumber) {
    QRegularExpression re("^[0-9]{8,}$"); // At least 8 digits, only numbers
    return re.match(mobileNumber).hasMatch();
}

bool UserWindow::validateAge(const QDate& dob) {
    QDate currentDate = QDate::currentDate(); // Use current date instead of hardcoding
    int age = dob.daysTo(currentDate) / 365; // Approximate age in years
    return age >= 18;
}

void UserWindow::collectStatistics() {
    QSqlQuery query;
    QDate currentDate = QDate::currentDate();

    totalEmployees = 0;
    ageCategories = {{"<25", 0}, {"25-35", 0}, {"36-45", 0}, {">45", 0}};
    roleCount.clear();
    roleByAge.clear();

    // Debug: Check if database connection is open
    if (!QSqlDatabase::database().isOpen()) {
        QMessageBox::critical(this, "Error", "Database connection is not open.");
        return;
    }

    // Fetch age data (using DATEN instead of "Date of Birth")
    if (query.exec("SELECT DATEN FROM HOTSTUFF.EMPLOYE")) {
        int count = 0;
        while (query.next()) {
            QDate dob = query.value(0).toDate();
            if (!dob.isValid()) {
                continue; // Skip invalid dates
            }
            int age = dob.daysTo(currentDate) / 365;
            if (age < 25) ageCategories["<25"]++;
            else if (age <= 35) ageCategories["25-35"]++;
            else if (age <= 45) ageCategories["36-45"]++;
            else ageCategories[">45"]++;
            totalEmployees++;
            count++;
        }
        qDebug() << "Fetched" << count << "employees for age distribution. Total employees:" << totalEmployees;
    } else {
        QMessageBox::critical(this, "Error", "Failed to fetch age data: " + query.lastError().text());
        qDebug() << "Query failed:" << query.lastQuery() << "Error:" << query.lastError().text();
    }

    // Fetch role data (using ROLE)
    if (query.exec("SELECT ROLE FROM HOTSTUFF.EMPLOYE")) {
        int count = 0;
        while (query.next()) {
            QString role = query.value(0).toString();
            if (role.isEmpty()) {
                continue; // Skip empty roles
            }
            roleCount[role]++;
            count++;
        }
        qDebug() << "Fetched" << count << "roles. Role count:" << roleCount;
    } else {
        QMessageBox::critical(this, "Error", "Failed to fetch role data: " + query.lastError().text());
        qDebug() << "Query failed:" << query.lastQuery() << "Error:" << query.lastError().text();
    }

    // Initialize roleByAge for each age category
    for (const QString &ageCat : ageCategories.keys()) {
        roleByAge[ageCat] = QMap<QString, int>();
    }

    // Fetch role by age data
    if (query.exec("SELECT DATEN, ROLE FROM HOTSTUFF.EMPLOYE")) {
        int count = 0;
        while (query.next()) {
            QDate dob = query.value(0).toDate();
            QString role = query.value(1).toString();
            if (!dob.isValid() || role.isEmpty()) {
                continue; // Skip invalid entries
            }
            int age = dob.daysTo(currentDate) / 365;
            QString ageCat = (age < 25) ? "<25" : (age <= 35) ? "25-35" : (age <= 45) ? "36-45" : ">45";
            roleByAge[ageCat][role]++;
            count++;
        }
        qDebug() << "Fetched" << count << "entries for role by age. Role by age:" << roleByAge;
    } else {
        QMessageBox::critical(this, "Error", "Failed to fetch role by age data: " + query.lastError().text());
        qDebug() << "Query failed:" << query.lastQuery() << "Error:" << query.lastError().text();
    }
}
void UserWindow::drawStatistics(QPainter &painter) {
    qDebug() << "Drawing statistics... Total employees:" << totalEmployees;
    qDebug() << "Age categories:" << ageCategories;
    qDebug() << "Role count:" << roleCount;
    qDebug() << "Role by age:" << roleByAge;

    int yPos = 20;
    const int margin = 20;
    const int barHeight = 30;
    const int maxBarWidth = 600; // Increased from 400
    const int rowHeight = 30;

    QFont titleFont("Arial", 16, QFont::Bold);
    QFont subtitleFont("Arial", 12, QFont::Bold);
    QFont textFont("Arial", 10);

    painter.setFont(titleFont);
    painter.drawText(margin, yPos, "Employee Statistics");
    yPos += 50;

    painter.setFont(subtitleFont);
    painter.drawText(margin, yPos, "Age Distribution");
    yPos += 30;

    QList<QColor> colors = {Qt::red, Qt::green, Qt::blue, Qt::yellow};
    int colorIndex = 0;

    for (auto it = ageCategories.constBegin(); it != ageCategories.constEnd(); ++it) {
        qreal percentage = totalEmployees > 0 ? (qreal)it.value() / totalEmployees * 100 : 0;
        int barWidth = totalEmployees > 0 ? (it.value() * maxBarWidth) / totalEmployees : 0;
        qDebug() << "Drawing age category" << it.key() << ": count =" << it.value() << ", percentage =" << percentage << ", barWidth =" << barWidth;

        painter.setBrush(colors[colorIndex % colors.size()]);
        painter.drawRect(margin, yPos, barWidth, barHeight);
        painter.setFont(textFont);
        painter.drawText(margin + barWidth + 10, yPos + barHeight / 2 + 5,
                         QString("%1: %2 (%3%)").arg(it.key()).arg(it.value()).arg(percentage, 0, 'f', 1));
        yPos += barHeight + 10;
        colorIndex++;
    }
    yPos += 30;

    painter.setFont(subtitleFont);
    painter.drawText(margin, yPos, "Role Distribution");
    yPos += 30;

    colorIndex = 0;
    for (auto it = roleCount.constBegin(); it != roleCount.constEnd(); ++it) {
        qreal percentage = totalEmployees > 0 ? (qreal)it.value() / totalEmployees * 100 : 0;
        int barWidth = totalEmployees > 0 ? (it.value() * maxBarWidth) / totalEmployees : 0;
        qDebug() << "Drawing role" << it.key() << ": count =" << it.value() << ", percentage =" << percentage << ", barWidth =" << barWidth;

        painter.setBrush(colors[colorIndex % colors.size()]);
        painter.drawRect(margin, yPos, barWidth, barHeight);
        painter.drawText(margin + barWidth + 10, yPos + barHeight / 2 + 5,
                         QString("%1: %2 (%3%)").arg(it.key()).arg(it.value()).arg(percentage, 0, 'f', 1));
        yPos += barHeight + 10;
        colorIndex++;
    }
    yPos += 30;

    painter.setFont(subtitleFont);
    painter.drawText(margin, yPos, "Role Distribution by Age Category");
    yPos += 30;

    const int tableWidth = 600;
    const int colWidth = tableWidth / 3;

    painter.setFont(subtitleFont);
    painter.setBrush(QColor(173, 216, 230));
    painter.drawRect(margin, yPos, colWidth, rowHeight);
    painter.drawRect(margin + colWidth, yPos, colWidth, rowHeight);
    painter.drawRect(margin + 2 * colWidth, yPos, colWidth, rowHeight);
    painter.setPen(Qt::black);
    painter.drawText(margin, yPos, colWidth, rowHeight, Qt::AlignCenter, "Age Category");
    painter.drawText(margin + colWidth, yPos, colWidth, rowHeight, Qt::AlignCenter, "Role");
    painter.drawText(margin + 2 * colWidth, yPos, colWidth, rowHeight, Qt::AlignCenter, "Count");
    yPos += rowHeight;

    painter.setFont(textFont);
    for (auto ageIt = roleByAge.constBegin(); ageIt != roleByAge.constEnd(); ++ageIt) {
        for (auto roleIt = ageIt.value().constBegin(); roleIt != ageIt.value().constEnd(); ++roleIt) {
            qDebug() << "Drawing table row: Age =" << ageIt.key() << ", Role =" << roleIt.key() << ", Count =" << roleIt.value();
            painter.setBrush(Qt::white);
            painter.drawRect(margin, yPos, colWidth, rowHeight);
            painter.drawRect(margin + colWidth, yPos, colWidth, rowHeight);
            painter.drawRect(margin + 2 * colWidth, yPos, colWidth, rowHeight);
            painter.setPen(Qt::black);
            painter.drawText(margin, yPos, colWidth, rowHeight, Qt::AlignCenter, ageIt.key());
            painter.drawText(margin + colWidth, yPos, colWidth, rowHeight, Qt::AlignCenter, roleIt.key());
            painter.drawText(margin + 2 * colWidth, yPos, colWidth, rowHeight, Qt::AlignCenter, QString::number(roleIt.value()));
            yPos += rowHeight;
        }
    }
}
