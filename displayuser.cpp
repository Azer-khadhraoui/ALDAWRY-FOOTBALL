// displayuser.cpp
#include "displayuser.h"
#include "modifyuser.h" // Add this include
#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>
#include <QStandardItem>
#include <QMessageBox>
#include <QFileDialog>
#include <QPdfWriter>
#include <QPainter>
#include <QDate>
#include "sessionmanager.h"

DisplayUser::DisplayUser(const QString &role, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DisplayUser),
    model(new QStandardItemModel(this)),
    proxyModel(new QSortFilterProxyModel(this)),
    selectedUserId(0)
{
    ui->setupUi(this);
    setWindowTitle("Users - " + role);

    // Make the dialog modal
    setModal(true);

    // Set up table model
    model->setColumnCount(4);
    model->setHorizontalHeaderLabels({"First Name", "Last Name", "Email", "Telephone"}); // Updated headers

    // Set up proxy model for sorting and filtering
    proxyModel->setSourceModel(model);
    ui->tableView_3->setModel(proxyModel);
    ui->tableView_3->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView_3->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView_3->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView_3->setSortingEnabled(true);
    ui->tableView_3->horizontalHeader()->setSortIndicatorShown(true);
    ui->tableView_3->horizontalHeader()->setSectionsClickable(true);

    // Populate table with users of the specified role
    populateUserTable(role);

    // Connect signals to slots
    connect(ui->tableView_3, &QTableView::clicked, this, &DisplayUser::on_tableRowClicked);
    connect(ui->pushButton_3, &QPushButton::clicked, this, &DisplayUser::on_pushButton_3_clicked);
    connect(ui->pdfButton, &QPushButton::clicked, this, &DisplayUser::on_pdfButton_clicked);
    connect(ui->ModifyUser, &QPushButton::clicked, this, &DisplayUser::on_ModifyUser_clicked);
    connect(ui->lineEdit_10, &QLineEdit::textChanged, this, &DisplayUser::on_searchTextChanged);
}

DisplayUser::~DisplayUser()
{
    delete proxyModel;
    delete model;
    delete ui;
}

void DisplayUser::populateUserTable(const QString &role)
{
    // Clear existing data
    model->removeRows(0, model->rowCount());

    // Execute SQL query to fetch users filtered by role
    QSqlQuery query;
    query.prepare("SELECT NOM_EMP, PRENOM_EMP, EMAIL, TO_CHAR(NUM) "
                  "FROM HOTSTUFF.EMPLOYE WHERE UPPER(ROLE) = UPPER(:role)");
    query.bindValue(":role", role);

    if (!query.exec()) {
        qDebug() << "Failed to fetch users for role" << role << ":" << query.lastError().text();
        return;
    }

    // Populate table
    while (query.next()) {
        QList<QStandardItem*> row;
        row << new QStandardItem(query.value(0).toString()) // NOM_EMP (First Name)
            << new QStandardItem(query.value(1).toString()) // PRENOM_EMP (Last Name)
            << new QStandardItem(query.value(2).toString()) // EMAIL
            << new QStandardItem(query.value(3).toString()); // NUM (Telephone)
        model->appendRow(row);
    }

    qDebug() << "Populated table with" << model->rowCount() << "users of role:" << role;
}

void DisplayUser::refreshUserTable()
{
    QString role = windowTitle().split(" - ").last();
    populateUserTable(role);
}

void DisplayUser::on_tableRowClicked(const QModelIndex &index)
{
    // Map the selected index from the proxy model to the source model
    QModelIndex sourceIndex = proxyModel->mapToSource(index);

    // Fetch the ID by querying the database since ID is no longer in the table
    QString firstName = model->data(sourceIndex.sibling(sourceIndex.row(), 0)).toString();
    QString lastName = model->data(sourceIndex.sibling(sourceIndex.row(), 1)).toString();
    QString role = windowTitle().split(" - ").last();

    QSqlQuery query;
    query.prepare("SELECT ID_EMP FROM HOTSTUFF.EMPLOYE "
                  "WHERE UPPER(NOM_EMP) = UPPER(:firstName) "
                  "AND UPPER(PRENOM_EMP) = UPPER(:lastName) "
                  "AND UPPER(ROLE) = UPPER(:role)");
    query.bindValue(":firstName", firstName);
    query.bindValue(":lastName", lastName);
    query.bindValue(":role", role);

    if (!query.exec() || !query.next()) {
        qDebug() << "Failed to fetch user ID for" << firstName << lastName << ":" << query.lastError().text();
        QMessageBox::critical(this, "Error", "Failed to retrieve user data.");
        ui->photoLabel->setText("Error");
        selectedUserId = 0;
        return;
    }

    int id = query.value(0).toInt();
    qDebug() << "Table row clicked, selected user ID:" << id;

    // Fetch user details
    Employee emp;
    Employee* employee = emp.getById(id);
    if (!employee) {
        qDebug() << "Failed to retrieve user data for ID:" << id;
        QMessageBox::critical(this, "Error", "Failed to retrieve user data.");
        ui->photoLabel->setText("Error");
        selectedUserId = 0;
        return;
    }

    // Load the selected user's photo into photoLabel
    selectedUserPhoto = employee->getFace();
    if (!selectedUserPhoto.isEmpty()) {
        QPixmap pixmap;
        if (pixmap.loadFromData(selectedUserPhoto)) {
            ui->photoLabel->setPixmap(pixmap.scaled(ui->photoLabel->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
            qDebug() << "User photo loaded successfully for ID:" << id;
        } else {
            qDebug() << "Failed to load photo for user ID:" << id;
            ui->photoLabel->setText("Invalid Image");
        }
    } else {
        qDebug() << "No photo found for user ID:" << id;
        ui->photoLabel->setText("No Photo");
    }

    // Store the selected user's ID
    selectedUserId = id;
    qDebug() << "Selected user ID set to:" << selectedUserId;

    delete employee;
}

void DisplayUser::on_pushButton_3_clicked()
{
    if (!QSqlDatabase::database().isOpen()) {
        QMessageBox::critical(this, "Error", "Database connection is not open.");
        return;
    }

    if (selectedUserId == 0) {
        QMessageBox::warning(this, "Warning", "Please select a user to delete.");
        return;
    }

    Employee emp;
    Employee* employee = emp.getById(selectedUserId);
    if (!employee) {
        QMessageBox::critical(this, "Error", "Failed to retrieve user data for deletion.");
        return;
    }

    QString userName = employee->getFirstName() + " " + employee->getLastName();
    delete employee;

    QMessageBox::StandardButton reply = QMessageBox::question(
        this,
        "Confirm Deletion",
        "Are you sure you want to delete user " + userName + " (ID: " + QString::number(selectedUserId) + ")?",
        QMessageBox::Yes | QMessageBox::No
        );

    if (reply != QMessageBox::Yes) {
        qDebug() << "User canceled deletion of user ID:" << selectedUserId;
        return;
    }

    if (Employee().deleteEmployee(selectedUserId)) {
        QMessageBox::information(this, "Success", "User deleted successfully!");
        selectedUserId = 0;
        ui->photoLabel->setText("No Photo");
        refreshUserTable();
    } else {
        qDebug() << "Failed to delete user ID:" << selectedUserId << " - Database error:" << QSqlDatabase::database().lastError().text();
        QMessageBox::critical(this, "Error", "Failed to delete user. Check database permissions or constraints.");
    }
}

void DisplayUser::on_pdfButton_clicked()
{
    if (!QSqlDatabase::database().isOpen()) {
        QMessageBox::critical(this, "Error", "Database connection is not open.");
        return;
    }

    if (selectedUserId == 0) {
        QMessageBox::warning(this, "Warning", "Please select a user to export to PDF.");
        return;
    }

    Employee emp;
    Employee* employee = emp.getById(selectedUserId);
    if (!employee) {
        QMessageBox::critical(this, "Error", "Failed to retrieve user data.");
        return;
    }

    QString fileName = QFileDialog::getSaveFileName(this, "Save PDF", "", "PDF Files (*.pdf)");
    if (fileName.isEmpty()) {
        delete employee;
        return;
    }

    if (!fileName.endsWith(".pdf", Qt::CaseInsensitive)) {
        fileName += ".pdf";
    }

    QPdfWriter pdfWriter(fileName);
    pdfWriter.setPageSize(QPageSize(QPageSize::A4));
    pdfWriter.setPageMargins(QMarginsF(30, 30, 30, 30));

    QPainter painter(&pdfWriter);
    if (!painter.isActive()) {
        QMessageBox::critical(this, "Error", "Failed to initialize PDF writer.");
        delete employee;
        return;
    }

    painter.setRenderHint(QPainter::Antialiasing);

    int pageWidth = pdfWriter.width();
    int pageHeight = pdfWriter.height();

    int margin = 500;
    int cardWidth = pageWidth - 2 * margin;
    int cardHeight = 6000;
    int cardX = margin;
    int cardY = 1200;
    int yPos = cardY + 400;
    int rowSpacing = 600;
    int titleFontSize = 20;
    int subtitleFontSize = 18;
    int bodyFontSize = 14;

    QFont titleFont("Arial", titleFontSize, QFont::Bold);
    QFont subtitleFont("Arial", subtitleFontSize, QFont::Bold);
    QFont bodyFont("Arial", bodyFontSize);

    QColor fieldGreen(34, 139, 34);
    QColor footballWhite(255, 255, 255);
    QColor accentColor(255, 215, 0);

    QLinearGradient gradient(0, 0, 0, pageHeight);
    gradient.setColorAt(0, fieldGreen.lighter(120));
    gradient.setColorAt(1, fieldGreen.darker(120));
    painter.setBrush(gradient);
    painter.setPen(Qt::NoPen);
    painter.drawRect(0, 0, pageWidth, pageHeight);

    painter.setPen(QPen(footballWhite, 30));
    painter.setBrush(Qt::NoBrush);
    painter.drawEllipse(QPoint(pageWidth / 2, pageHeight / 2), 1000, 1000);
    painter.setPen(QPen(footballWhite, 20, Qt::DashLine));
    painter.drawLine(0, pageHeight / 2, pageWidth, pageHeight / 2);
    painter.drawRect(margin, pageHeight / 2 - 1500, 1000, 3000);
    painter.drawRect(pageWidth - margin - 1000, pageHeight / 2 - 1500, 1000, 3000);

    QImage logo(":/images/aldawry_logo.png");
    if (!logo.isNull()) {
        int logoWidth = 2000;
        int logoHeight = 2000;
        int logoX = (pageWidth - logoWidth) / 2;
        int logoY = 200;
        painter.drawImage(QRect(logoX, logoY, logoWidth, logoHeight), logo);
        yPos = logoY + logoHeight + 200;
    } else {
        qDebug() << "Failed to load Aldawry Football logo. Using fallback text.";
        painter.setFont(titleFont);
        painter.setPen(footballWhite);
        painter.drawText(0, 200, pageWidth, 400, Qt::AlignCenter, "[Logo Missing]");
        yPos = 800;
    }

    painter.setFont(titleFont);
    painter.setPen(footballWhite);
    QRect titleRect(0, yPos, pageWidth, 400);
    painter.drawText(titleRect, Qt::AlignCenter, "Aldawry Football User Profile");
    yPos += 600;

    painter.setPen(Qt::NoPen);
    painter.setBrush(QColor(0, 0, 0, 80));
    QRect shadowRect(cardX + 50, cardY + 50, cardWidth, cardHeight);
    painter.drawRoundedRect(shadowRect, 200, 200);

    painter.setBrush(QColor(255, 255, 255, 220));
    painter.setPen(Qt::black);
    QRect cardRect(cardX, cardY, cardWidth, cardHeight);
    painter.drawRoundedRect(cardRect, 200, 200);

    painter.setFont(subtitleFont);
    painter.setPen(fieldGreen.darker(150));
    QString userName = employee->getFirstName() + " " + employee->getLastName();
    painter.drawText(cardX, yPos, cardWidth, rowSpacing, Qt::AlignCenter, userName);
    yPos += rowSpacing + 300;

    QStringList labels = {"First Name:", "Last Name:", "Email:", "Mobile Number:", "Role:", "Date of Birth:"};
    QStringList values = {
        employee->getFirstName(),
        employee->getLastName(),
        employee->getEmail(),
        employee->getMobileNumber(),
        employee->getRole(),
        employee->getDateOfBirth().toString("yyyy-MM-dd")
    };

    painter.setFont(bodyFont);
    for (int i = 0; i < labels.size(); ++i) {
        QImage footballIcon(":/images/football_icon.png");
        if (!footballIcon.isNull()) {
            painter.drawImage(QRect(cardX + 200, yPos, 150, 150), footballIcon);
        } else {
            qDebug() << "Failed to load football icon. Using fallback shape.";
            painter.setBrush(accentColor);
            painter.setPen(Qt::NoPen);
            painter.drawEllipse(cardX + 200, yPos + 50, 100, 100);
        }

        painter.setPen(fieldGreen.darker(150));
        int labelX = cardX + 400;
        painter.drawText(labelX, yPos, 3000, rowSpacing, Qt::AlignLeft, labels[i]);

        QFont boldFont = bodyFont;
        boldFont.setBold(true);
        painter.setFont(boldFont);
        int valueX = labelX + 1500;
        painter.drawText(valueX, yPos, cardWidth - 2000, rowSpacing, Qt::AlignLeft, values[i]);

        yPos += rowSpacing;
        painter.setFont(bodyFont);
    }

    painter.setPen(QPen(accentColor, 50));
    painter.drawLine(cardX + 200, yPos, cardX + cardWidth - 200, yPos);

    QFont footerFont("Arial", 10);
    painter.setFont(footerFont);
    painter.setPen(footballWhite);
    QString footerText = "Generated on: " + QDate::currentDate().toString("yyyy-MM-dd");
    painter.drawText(0, pageHeight - 300, pageWidth, 200, Qt::AlignCenter, footerText);

    painter.end();

    QMessageBox::information(this, "Success", "Enhanced Football-themed PDF generated successfully at: " + fileName);
    delete employee;
}

void DisplayUser::on_ModifyUser_clicked()
{
    if (!QSqlDatabase::database().isOpen()) {
        QMessageBox::critical(this, "Error", "Database connection is not open.");
        return;
    }

    if (selectedUserId == 0) {
        QMessageBox::warning(this, "Warning", "Please select a user to modify.");
        return;
    }

    qDebug() << "Modify button clicked for user ID:" << selectedUserId;

    // Open ModifyUser dialog
    ModifyUser modifyDialog(selectedUserId, this);
    if (modifyDialog.exec() == QDialog::Accepted) {
        // Refresh table after successful modification
        refreshUserTable();
        // Reset selected user ID and photo
        selectedUserId = 0;
        ui->photoLabel->setText("No Photo");
        qDebug() << "User modified successfully, table refreshed.";
    }
}

void DisplayUser::on_searchTextChanged(const QString &text)
{
    if (!QSqlDatabase::database().isOpen()) {
        QMessageBox::critical(this, "Error", "Database connection is not open.");
        return;
    }

    QString searchTerm = text.trimmed();
    QString role = windowTitle().split(" - ").last();

    QSqlQuery query;
    QString queryStr = "SELECT NOM_EMP, PRENOM_EMP, EMAIL, TO_CHAR(NUM) "
                       "FROM HOTSTUFF.EMPLOYE "
                       "WHERE UPPER(ROLE) = UPPER(:role) "
                       "AND (UPPER(NOM_EMP) LIKE UPPER(:term) "
                       "OR UPPER(PRENOM_EMP) LIKE UPPER(:term) "
                       "OR UPPER(EMAIL) LIKE UPPER(:term))";
    query.prepare(queryStr);
    query.bindValue(":role", role);
    query.bindValue(":term", "%" + searchTerm + "%");

    if (!query.exec()) {
        qDebug() << "Search query failed:" << query.lastError().text();
        refreshUserTable();
        return;
    }

    model->removeRows(0, model->rowCount());

    while (query.next()) {
        QList<QStandardItem*> row;
        row << new QStandardItem(query.value(0).toString()) // NOM_EMP
            << new QStandardItem(query.value(1).toString()) // PRENOM_EMP
            << new QStandardItem(query.value(2).toString()) // EMAIL
            << new QStandardItem(query.value(3).toString()); // NUM
        model->appendRow(row);
    }

    if (model->rowCount() == 0) {
        QMessageBox::information(this, "No Results", "No users found matching the search term.");
    }
}
