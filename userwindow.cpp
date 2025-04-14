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
#include "sessionmanager.h"
#include "mainwindow.h" // Add this line to include MainWindow definition

UserWindow::UserWindow(MainWindow *parent) : QMainWindow(parent), ui(new Ui::MainWindow), mainWindowParent(parent) {
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
    connect(ui->pushButton, &QPushButton::clicked, this, &UserWindow::on_pushButton_clicked); // New connection for sign-out
    connect(ui->lineEdit_10, &QLineEdit::textChanged, this, &UserWindow::on_searchTextChanged);
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
    // Get the current user from SessionManager
    const Employee& currentUser = SessionManager::instance().getCurrentUser();
    if (!SessionManager::instance().isLoggedIn()) {
        QMessageBox::critical(this, "Error", "No user is logged in.");
        return;
    }

    // Open a file dialog to let the user choose the save location
    QString fileName = QFileDialog::getSaveFileName(this, "Save PDF", "", "PDF Files (*.pdf)");
    if (fileName.isEmpty()) return;

    if (!fileName.endsWith(".pdf", Qt::CaseInsensitive)) {
        fileName += ".pdf";
    }

    QPdfWriter pdfWriter(fileName);
    pdfWriter.setPageSize(QPageSize(QPageSize::A4));
    pdfWriter.setPageMargins(QMarginsF(30, 30, 30, 30));

    QPainter painter(&pdfWriter);
    painter.setRenderHint(QPainter::Antialiasing);

    int pageWidth = pdfWriter.width();
    int pageHeight = pdfWriter.height();

    // Layout variables
    int margin = 500;
    int cardWidth = pageWidth - 2 * margin;
    int cardHeight = 5500;
    int cardX = margin;
    int cardY = 500;
    int yPos = cardY + 300;
    int rowSpacing = 800;
    int titleFontSize = 16;
    int subtitleFontSize = 14;
    int bodyFontSize = 12;

    QFont titleFont("Arial", titleFontSize, QFont::Bold);
    QFont subtitleFont("Arial", subtitleFontSize, QFont::Bold);
    QFont bodyFont("Arial", bodyFontSize);

    // Draw title
    painter.setFont(titleFont);
    painter.setPen(Qt::black);
    painter.drawText(0, 200, pageWidth, 300, Qt::AlignCenter, "User Profile");

    // Card shadow
    painter.setPen(Qt::NoPen);
    painter.setBrush(QColor(0, 0, 0, 50));
    QRect shadowRect(cardX + 50, cardY + 50, cardWidth, cardHeight);
    painter.drawRoundedRect(shadowRect, 150, 150);

    // Card background
    painter.setBrush(QColor(240, 240, 240));
    painter.setPen(Qt::black);
    QRect cardRect(cardX, cardY, cardWidth, cardHeight);
    painter.drawRoundedRect(cardRect, 150, 150);

    // User full name
    painter.setFont(subtitleFont);
    painter.setPen(Qt::black);
    QString userName = currentUser.getFirstName() + " " + currentUser.getLastName();
    painter.drawText(cardX, yPos, cardWidth, rowSpacing, Qt::AlignCenter, userName);
    yPos += rowSpacing + 200;

    // Labels and values
    QStringList labels = {"First Name:", "Last Name:", "Email:", "Mobile Number:", "Role:", "Date of Birth:"};
    QStringList values = {
        currentUser.getFirstName(),
        currentUser.getLastName(),
        currentUser.getEmail(),
        currentUser.getMobileNumber(),
        currentUser.getRole(),
        currentUser.getDateOfBirth().toString("yyyy-MM-dd")
    };

    painter.setFont(bodyFont);
    for (int i = 0; i < labels.size(); ++i) {
        // Bullet
        painter.setBrush(QColor(0, 120, 215));
        painter.setPen(Qt::NoPen);
        painter.drawEllipse(cardX + 200, yPos + 50, 100, 100);

        // Label
        painter.setPen(Qt::black);
        int labelX = cardX + 350;
        painter.drawText(labelX, yPos, 3000, rowSpacing, Qt::AlignLeft, labels[i]);

        // Value
        QFont boldFont = bodyFont;
        boldFont.setBold(true);
        painter.setFont(boldFont);
        int valueX = labelX + 2000;
        painter.drawText(valueX, yPos, cardWidth - 2500, rowSpacing, Qt::AlignLeft, values[i]);

        yPos += rowSpacing;
        painter.setFont(bodyFont);
    }

    // Decorative line at bottom
    painter.setPen(QPen(QColor(0, 120, 215), 50));
    painter.drawLine(cardX + 200, yPos, cardX + cardWidth - 200, yPos);

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
// userwindow.cpp

void UserWindow::drawStatistics(QPainter &painter) {
    if (totalEmployees == 0) {
        painter.setFont(QFont("Arial", 12));
        painter.setPen(Qt::white);
        painter.drawText(rect(), Qt::AlignCenter, "No employee data available to display statistics.");
        return;
    }

    int yPos = 30;
    const int margin = 100; // Left margin
    const int rowHeight = 30;
    const int chartWidth = 150;
    const int chartHeight = 150;
    const int sectionSpacing = 60; // Gap between pie charts
    int availableWidth = width() - 2 * margin;
    int chartSectionWidth = chartWidth + 150; // Space for chart + legend + labels
    int tableSectionX = margin + chartSectionWidth + 30; // Start table to the right of charts

    QFont titleFont("Arial", 18, QFont::Bold);
    QFont subtitleFont("Arial", 14, QFont::Bold);
    QFont textFont("Arial", 10);
    QFont legendFont("Arial", 8); // Reduced font size for legend

    // Enhanced color palette for better contrast and accessibility
    QList<QColor> colors = {
        QColor("#FF5733"), // Vibrant Orange
        QColor("#C70039"), // Deep Red
        QColor("#900C3F"), // Dark Magenta
        QColor("#581845"), // Deep Purple
        QColor("#2ECC71"), // Bright Green
        QColor("#3498DB")  // Bright Blue
    };

    // Title with Total Employees
    painter.setFont(titleFont);
    painter.setPen(Qt::white);
    painter.drawText(QRect(0, yPos, width(), 30), Qt::AlignCenter,
                     QString("Employee Statistics (Total: %1)").arg(totalEmployees));
    yPos += 50;

    // Age Distribution Pie Chart (Left Side)
    int chartYPos = yPos; // Keep track of y position for charts
    painter.setFont(subtitleFont);
    painter.setPen(Qt::white);
    painter.drawText(margin, chartYPos, "Age Distribution");
    chartYPos += 25;

    // Removed the gray background for the chart
    // painter.setBrush(QColor(50, 50, 50, 100));
    // painter.setPen(Qt::NoPen);
    // painter.drawRoundedRect(margin - 10, chartYPos - 10, chartWidth + 120, chartHeight + 50, 10, 10);

    // Draw a shadow effect for the pie chart
    QRect shadowRect(margin + 5, chartYPos + 5, chartWidth, chartHeight);
    painter.setBrush(QColor(0, 0, 0, 50)); // Semi-transparent black for shadow
    painter.setPen(Qt::NoPen);
    painter.drawEllipse(shadowRect);

    QRect agePieRect(margin, chartYPos, chartWidth, chartHeight);
    int startAngle = 0;
    int colorIndex = 0;

    // Draw pie chart
    for (auto it = ageCategories.constBegin(); it != ageCategories.constEnd(); ++it) {
        int value = it.value();
        if (value == 0) continue;

        int spanAngle = (360.0 * value / totalEmployees) * 16;
        QColor color = colors[colorIndex % colors.size()];
        painter.setBrush(color);
        painter.setPen(Qt::black);
        painter.drawPie(agePieRect, startAngle, spanAngle);
        startAngle += spanAngle;
        colorIndex++;
    }

    // Draw labels and legend
    startAngle = 0;
    colorIndex = 0;
    int legendY = chartYPos;
    int legendX = margin + chartWidth + 15;
    painter.setFont(legendFont); // Use smaller font for legend
    for (auto it = ageCategories.constBegin(); it != ageCategories.constEnd(); ++it) {
        int value = it.value();
        if (value == 0) continue;

        int spanAngle = (360.0 * value / totalEmployees) * 16;
        QColor color = colors[colorIndex % colors.size()];

        // Legend
        painter.setBrush(color);
        painter.setPen(Qt::white);
        painter.drawRect(legendX, legendY, 12, 12);
        painter.drawText(legendX + 20, legendY + 10, QString("%1 (%2)").arg(it.key()).arg(value));

        // Label on pie chart
        double angle = (startAngle + spanAngle / 2) / 16.0;
        double radius = chartWidth / 2 + 25;
        QPoint labelPos = agePieRect.center() + QPoint(
                              qCos(angle * M_PI / 180.0) * radius,
                              qSin(angle * M_PI / 180.0) * radius
                              );
        painter.setPen(Qt::white);
        QString label = QString("%1 (%2)").arg(it.key()).arg(value);
        QRect labelRect(labelPos.x() - 40, labelPos.y() - 10, 80, 20);
        painter.drawText(labelRect, Qt::AlignCenter, label);

        // Draw a line connecting the label to the pie slice
        QPoint pieEdge = agePieRect.center() + QPoint(
                             qCos(angle * M_PI / 180.0) * (chartWidth / 2),
                             qSin(angle * M_PI / 180.0) * (chartHeight / 2)
                             );
        painter.drawLine(pieEdge, labelPos);

        startAngle += spanAngle;
        colorIndex++;
        legendY += 20;
    }

    chartYPos += chartHeight + sectionSpacing;

    // Role Distribution Pie Chart (Left Side, below Age Distribution)
    painter.setFont(subtitleFont);
    painter.setPen(Qt::white);
    painter.drawText(margin, chartYPos, "Role Distribution");
    chartYPos += 25;

    // Removed the gray background for the chart
    // painter.setBrush(QColor(50, 50, 50, 100));
    // painter.setPen(Qt::NoPen);
    // painter.drawRoundedRect(margin - 10, chartYPos - 10, chartWidth + 120, chartHeight + 50, 10, 10);

    // Draw a shadow effect for the pie chart
    shadowRect = QRect(margin + 5, chartYPos + 5, chartWidth, chartHeight);
    painter.setBrush(QColor(0, 0, 0, 50));
    painter.setPen(Qt::NoPen);
    painter.drawEllipse(shadowRect);

    QRect rolePieRect(margin, chartYPos, chartWidth, chartHeight);
    startAngle = 0;
    colorIndex = 0;

    // Draw pie chart
    for (auto it = roleCount.constBegin(); it != roleCount.constEnd(); ++it) {
        int value = it.value();
        if (value == 0) continue;

        int spanAngle = (360.0 * value / totalEmployees) * 16;
        QColor color = colors[colorIndex % colors.size()];
        painter.setBrush(color);
        painter.setPen(Qt::black);
        painter.drawPie(rolePieRect, startAngle, spanAngle);
        startAngle += spanAngle;
        colorIndex++;
    }

    // Draw labels and legend
    startAngle = 0;
    colorIndex = 0;
    legendY = chartYPos;
    legendX = margin + chartWidth + 15;
    painter.setFont(legendFont); // Use smaller font for legend
    for (auto it = roleCount.constBegin(); it != roleCount.constEnd(); ++it) {
        int value = it.value();
        if (value == 0) continue;

        int spanAngle = (360.0 * value / totalEmployees) * 16;
        QColor color = colors[colorIndex % colors.size()];

        // Legend
        painter.setBrush(color);
        painter.setPen(Qt::white);
        painter.drawRect(legendX, legendY, 12, 12);
        painter.drawText(legendX + 20, legendY + 10, QString("%1 (%2)").arg(it.key()).arg(value));

        // Label on pie chart
        double angle = (startAngle + spanAngle / 2) / 16.0;
        double radius = chartWidth / 2 + 25;
        QPoint labelPos = rolePieRect.center() + QPoint(
                              qCos(angle * M_PI / 180.0) * radius,
                              qSin(angle * M_PI / 180.0) * radius
                              );
        painter.setPen(Qt::white);
        QString label = QString("%1 (%2)").arg(it.key()).arg(value);
        QRect labelRect(labelPos.x() - 40, labelPos.y() - 10, 80, 20);
        painter.drawText(labelRect, Qt::AlignCenter, label);

        // Draw a line connecting the label to the pie slice
        QPoint pieEdge = rolePieRect.center() + QPoint(
                             qCos(angle * M_PI / 180.0) * (chartWidth / 2),
                             qSin(angle * M_PI / 180.0) * (chartHeight / 2)
                             );
        painter.drawLine(pieEdge, labelPos);

        startAngle += spanAngle;
        colorIndex++;
        legendY += 20;
    }

    // Role by Age Table (Right Side)
    int tableYPos = yPos; // Start table at the same vertical level as the first chart
    painter.setFont(subtitleFont);
    painter.setPen(Qt::white);
    painter.drawText(tableSectionX, tableYPos, "Role Distribution by Age Category");
    tableYPos += 25;

    // Calculate table dimensions with adjusted column widths
    int tableWidth = availableWidth - chartSectionWidth - 30;
    int colWidth = tableWidth / 3 + 20; // Increased column width to accommodate text
    int tableHeight = (roleByAge.size() + 1) * rowHeight + 20;

    // Removed the gray background for the table
    // painter.setBrush(QColor(50, 50, 50, 100));
    // painter.setPen(Qt::NoPen);
    // painter.drawRoundedRect(tableSectionX - 10, tableYPos - 10, tableWidth + 20, tableHeight, 10, 10);

    // Table Header with a gradient effect
    QLinearGradient headerGradient(tableSectionX, tableYPos, tableSectionX, tableYPos + rowHeight);
    headerGradient.setColorAt(0, QColor("#555"));
    headerGradient.setColorAt(1, QColor("#333"));
    painter.setBrush(headerGradient);
    painter.setPen(Qt::white);
    painter.drawRect(tableSectionX, tableYPos, colWidth, rowHeight);
    painter.drawRect(tableSectionX + colWidth, tableYPos, colWidth, rowHeight);
    painter.drawRect(tableSectionX + 2 * colWidth, tableYPos, colWidth, rowHeight);
    painter.drawText(tableSectionX, tableYPos, colWidth, rowHeight, Qt::AlignCenter, "Age Category");
    painter.drawText(tableSectionX + colWidth, tableYPos, colWidth, rowHeight, Qt::AlignCenter, "Role");
    painter.drawText(tableSectionX + 2 * colWidth, tableYPos, colWidth, rowHeight, Qt::AlignCenter, "Count");
    tableYPos += rowHeight;

    // Table Rows with enhanced styling
    painter.setFont(textFont);
    bool alternate = false;
    for (auto ageIt = roleByAge.constBegin(); ageIt != roleByAge.constEnd(); ++ageIt) {
        for (auto roleIt = ageIt.value().constBegin(); roleIt != ageIt.value().constEnd(); ++roleIt) {
            // Use a gradient for alternating rows
            QLinearGradient rowGradient(tableSectionX, tableYPos, tableSectionX, tableYPos + rowHeight);
            if (alternate) {
                rowGradient.setColorAt(0, QColor(40, 40, 40));
                rowGradient.setColorAt(1, QColor(30, 30, 30));
            } else {
                rowGradient.setColorAt(0, QColor(25, 25, 25));
                rowGradient.setColorAt(1, QColor(15, 15, 15));
            }
            painter.setBrush(rowGradient);
            painter.setPen(Qt::white);
            painter.drawRect(tableSectionX, tableYPos, colWidth, rowHeight);
            painter.drawRect(tableSectionX + colWidth, tableYPos, colWidth, rowHeight);
            painter.drawRect(tableSectionX + 2 * colWidth, tableYPos, colWidth, rowHeight);
            // Adjusted text drawing to ensure it fits within the cell
            painter.drawText(tableSectionX + 5, tableYPos, colWidth - 10, rowHeight, Qt::AlignCenter, ageIt.key());
            painter.drawText(tableSectionX + colWidth + 5, tableYPos, colWidth - 10, rowHeight, Qt::AlignCenter, roleIt.key());
            painter.drawText(tableSectionX + 2 * colWidth + 5, tableYPos, colWidth - 10, rowHeight, Qt::AlignCenter, QString::number(roleIt.value()));
            tableYPos += rowHeight;
            alternate = !alternate;
        }
    }
}

void UserWindow::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    drawStatistics(painter);
    QMainWindow::paintEvent(event);
}

void UserWindow::on_pushButton_clicked() {
    // Clear the session to log out the user
    SessionManager::instance().clearSession();

    // Re-show the parent MainWindow if it exists
    if (mainWindowParent) {
        // Clear the email and password fields in MainWindow
        mainWindowParent->findChild<QLineEdit*>("lineEdit")->clear();
        mainWindowParent->findChild<QLineEdit*>("lineEdit_2")->clear();
        mainWindowParent->show();
    } else {
        // Fallback: Create a new MainWindow (shouldn't happen if parent is set)
        MainWindow *mainWindow = new MainWindow();
        mainWindow->show();
    }

    // Close the current UserWindow
    this->close();
}

void UserWindow::on_searchTextChanged(const QString &text) {
    if (!QSqlDatabase::database().isOpen()) {
        QMessageBox::critical(this, "Error", "Database connection is not open.");
        return;
    }

    QString searchTerm = text.trimmed();
    QSqlQueryModel *sourceModel;

    if (searchTerm.isEmpty()) {
        sourceModel = Employee::displayEmployees();
    } else {
        // Custom query to search across multiple fields
        QSqlQuery query;
        QString queryStr = "SELECT ID_EMP, NOM_EMP, PRENOM_EMP, EMAIL, TO_CHAR(NUM), DATEN, ROLE "
                           "FROM HOTSTUFF.EMPLOYE "
                           "WHERE UPPER(NOM_EMP) LIKE UPPER(:term) "
                           "OR UPPER(PRENOM_EMP) LIKE UPPER(:term) "
                           "OR UPPER(EMAIL) LIKE UPPER(:term)";
        query.prepare(queryStr);
        query.bindValue(":term", "%" + searchTerm + "%");

        if (query.exec()) {
            sourceModel = new QSqlQueryModel();
            sourceModel->setQuery(query);
            sourceModel->setHeaderData(0, Qt::Horizontal, "ID");
            sourceModel->setHeaderData(1, Qt::Horizontal, "First Name");
            sourceModel->setHeaderData(2, Qt::Horizontal, "Last Name");
            sourceModel->setHeaderData(3, Qt::Horizontal, "Email");
            sourceModel->setHeaderData(4, Qt::Horizontal, "Mobile Number");
            sourceModel->setHeaderData(5, Qt::Horizontal, "Date of Birth");
            sourceModel->setHeaderData(6, Qt::Horizontal, "Role");
        } else {
            qDebug() << "Search query failed:" << query.lastError().text();
            sourceModel = Employee::displayEmployees();
        }
    }

    if (!sourceModel) {
        QMessageBox::critical(this, "Error", "Search failed.");
        return;
    }

    proxyModel->setSourceModel(sourceModel);
    ui->tableView_3->setModel(proxyModel);
    ui->tableView_3->hideColumn(0);
    ui->tableView_3->resizeColumnsToContents();
}
