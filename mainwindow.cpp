#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "team.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QFile>
#include <QBuffer>
#include <QDir>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QRegularExpression>
#include <QPixmap>
#include <QIcon>
#include <QTextStream>
#include <QPdfWriter>
#include <QPainter>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->button1, &QPushButton::clicked, this, &MainWindow::on_addButtonclicked);
    connect(ui->resetButton, &QPushButton::clicked, this, &MainWindow::on_resetButton_clicked);  // Connect the reset button
    connect(ui->searchBar, &QLineEdit::textChanged, this, &MainWindow::on_searchBar_textChanged);  // Connect the search bar
    connect(ui->modifyButton, &QPushButton::clicked, this, &MainWindow::on_modifyButton_clicked);  // Connect the modify button

    // Enable sorting
    ui->tableWidget->setSortingEnabled(true);
    connect(ui->tableWidget->horizontalHeader(), &QHeaderView::sectionClicked, this, &MainWindow::on_tableWidget_sectionClicked);

    // Set up table widget columns
    ui->tableWidget->setColumnCount(5);
    QStringList headers = {"Team Name", "Home Stadium", "Budget", "Team ABV", "Team Logo"};
    ui->tableWidget->setHorizontalHeaderLabels(headers);

    // Load and display all teams
    loadTeams();
    if (!QSqlDatabase::database().isOpen()) {
        qDebug() << "Database connection failed to open in MainWindow!";
        QMessageBox::critical(this, "Error", "Database connection is not open!");
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_toolButton_clicked()
{
    qDebug() << "on_toolButton_clicked called";

    // Open file dialog starting at "This PC" (approximated by "C:/")
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Select Team Logo"),
                                                    "C:/",  // Start at C:/ to approximate "This PC"
                                                    tr("Images (*.png *.jpg *.jpeg *.bmp)"));
    if (!fileName.isEmpty()) {
        QFile file(fileName);
        if (file.open(QIODevice::ReadOnly)) {
            teamLogo = file.readAll();  // Store the image data in the member variable
            file.close();
            ui->label_2->setText(QFileInfo(fileName).fileName());
            qDebug() << "Image loaded, size:" << teamLogo.size() << "bytes";
        } else {
            QMessageBox::warning(this, "File Error", "Could not open the selected image.");
            ui->label_2->setText("insert logo here");
        }
    } else {
        ui->label_2->setText("insert logo here");
    }
}

void MainWindow::on_addButtonclicked()
{
    QString teamName = ui->l1->text();
    QString homeStadium = ui->cb->currentText();
    QString budgetText = ui->l2->text();
    QString teamABV = ui->l2_2->text();

    // Validate required fields
    if (teamName.isEmpty() || homeStadium.isEmpty() || budgetText.isEmpty() || teamABV.isEmpty() || teamLogo.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Please fill in all required fields and select a team logo.");
        return;
    }

    // Validate Team Name (only alphabets)
    QRegularExpression reAlpha("^[A-Za-z]+$");
    if (!reAlpha.match(teamName).hasMatch()) {
        QMessageBox::warning(this, "Input Error", "Team Name must contain only alphabets.");
        return;
    }

    // Validate Budget (only numbers)
    bool ok;
    int budget = budgetText.toInt(&ok);
    if (!ok) {
        QMessageBox::warning(this, "Input Error", "Budget must be a valid integer.");
        return;
    }

    // Validate Team ABV (only uppercase alphabets)
    QRegularExpression reUpperAlpha("^[A-Z]+$");
    if (!reUpperAlpha.match(teamABV).hasMatch()) {
        QMessageBox::warning(this, "Input Error", "Team ABV must contain only uppercase alphabets.");
        return;
    }

    // Create a new team using setters
    Team newTeam;
    newTeam.setTeamName(teamName);
    newTeam.setHomeStadium(homeStadium);
    newTeam.setBudget(budget);
    newTeam.setTeamABV(teamABV);
    newTeam.setTeamLogo(teamLogo);  // Use the stored logo data

    if (newTeam.Ajouter()) {
        QMessageBox::information(this, "Success", "Team added successfully!");
        
        // Clear input fields
        ui->l1->clear();
        ui->l2->clear();
        ui->l2_2->clear();
        ui->label_2->setText("insert logo here");
        teamLogo.clear();  // Clear the stored logo data
        ui->cb->setCurrentIndex(0);

        // Add the new team to the table widget
        int row = ui->tableWidget->rowCount();
        ui->tableWidget->insertRow(row);
        ui->tableWidget->setItem(row, 0, new QTableWidgetItem(teamName));
        ui->tableWidget->setItem(row, 1, new QTableWidgetItem(homeStadium));
        ui->tableWidget->setItem(row, 2, new QTableWidgetItem(QString::number(budget)));
        ui->tableWidget->setItem(row, 3, new QTableWidgetItem(teamABV));

        // Set the logo as an icon in the table widget
        QTableWidgetItem *logoItem = new QTableWidgetItem();
        QPixmap pixmap;
        pixmap.loadFromData(teamLogo);
        logoItem->setIcon(QIcon(pixmap));
        ui->tableWidget->setItem(row, 4, logoItem);
    } else {
        QMessageBox::critical(this, "Error", "Failed to add team to the database.");
    }
}

void MainWindow::on_deleteButton_clicked()
{
    int currentRow = ui->tableWidget->currentRow();
    if (currentRow >= 0) {
        QString teamName = ui->tableWidget->item(currentRow, 0)->text();

        // Remove the team from the database
        QSqlQuery query;
        query.prepare("DELETE FROM HOTSTUFF.EQUIPE WHERE TEAM_NAME = :team_name");
        query.bindValue(":team_name", teamName);
        if (query.exec()) {
            // Remove the row from the table widget
            ui->tableWidget->removeRow(currentRow);
            QMessageBox::information(this, "Success", "Team deleted successfully!");
        } else {
            qDebug() << "Failed to delete team from the database:" << query.lastError().text();
            QMessageBox::critical(this, "Error", "Failed to delete team from the database.");
        }
    } else {
        QMessageBox::warning(this, "Selection Error", "Please select a row to delete.");
    }
}

void MainWindow::loadTeams()
{
    QSqlQuery query("SELECT TEAM_NAME, HOME_STADIUM, BUDG, TEAM_ABV, TEAM_LOGO FROM HOTSTUFF.EQUIPE");
    qDebug() << "Loading teams from database...";
    while (query.next()) {
        QString teamName = query.value(0).toString();
        QString homeStadium = query.value(1).toString();
        int budget = query.value(2).toInt();
        QString teamABV = query.value(3).toString();
        QByteArray teamLogo = query.value(4).toByteArray();

        int row = ui->tableWidget->rowCount();
        ui->tableWidget->insertRow(row);
        ui->tableWidget->setItem(row, 0, new QTableWidgetItem(teamName));
        ui->tableWidget->setItem(row, 1, new QTableWidgetItem(homeStadium));
        ui->tableWidget->setItem(row, 2, new QTableWidgetItem(QString::number(budget)));
        ui->tableWidget->setItem(row, 3, new QTableWidgetItem(teamABV));

        // Set the logo as an icon in the table widget
        QTableWidgetItem *logoItem = new QTableWidgetItem();
        QPixmap pixmap;
        pixmap.loadFromData(teamLogo);
        logoItem->setIcon(QIcon(pixmap));
        ui->tableWidget->setItem(row, 4, logoItem);
        qDebug() << "Loaded team:" << teamName << homeStadium << budget << teamABV;
    }
    qDebug() << "Finished loading teams, total rows:" << ui->tableWidget->rowCount();
}

void MainWindow::on_resetButton_clicked()
{
    // Clear input fields
    ui->l1->clear();
    ui->l2->clear();
    ui->l2_2->clear();
    ui->label_2->setText("insert logo here");
    teamLogo.clear();  // Clear the stored logo data
    ui->cb->setCurrentIndex(0);
}

void MainWindow::on_searchBar_textChanged(const QString &text)
{
    for (int i = 0; i < ui->tableWidget->rowCount(); ++i) {
        bool match = ui->tableWidget->item(i, 0)->text().contains(text, Qt::CaseInsensitive);
        ui->tableWidget->setRowHidden(i, !match);
    }
}

void MainWindow::on_tableWidget_sectionClicked(int logicalIndex)
{
    if (logicalIndex == 2) {  // Assuming the budget column is the third column (index 2)
        ui->tableWidget->sortItems(logicalIndex, Qt::AscendingOrder);
    } else {
        ui->tableWidget->sortItems(logicalIndex);
    }
}

void MainWindow::on_modifyButton_clicked()
{
    int currentRow = ui->tableWidget->currentRow();
    if (currentRow >= 0) {
        QString teamName = ui->tableWidget->item(currentRow, 0)->text();
        QString homeStadium = ui->tableWidget->item(currentRow, 1)->text();
        int budget = ui->tableWidget->item(currentRow, 2)->text().toInt();
        QString teamABV = ui->tableWidget->item(currentRow, 3)->text();

        QSqlQuery query;
        query.prepare("SELECT TEAM_LOGO FROM HOTSTUFF.EQUIPE WHERE TEAM_NAME = :team_name");
        query.bindValue(":team_name", teamName);
        if (query.exec() && query.next()) {
            QByteArray teamLogo = query.value(0).toByteArray();

            ModifyTeam modifyTeamDialog(this);
            modifyTeamDialog.setTeamData(teamName, homeStadium, budget, teamABV, teamLogo);

            if (modifyTeamDialog.exec() == QDialog::Accepted) {
                // Refresh the table
                ui->tableWidget->clearContents();
                ui->tableWidget->setRowCount(0);
                loadTeams();
                qDebug() << "Table refreshed after modification.";
            }
        } else {
            qDebug() << "Failed to fetch team logo:" << query.lastError().text();
            QMessageBox::critical(this, "Error", "Failed to fetch team logo from the database.");
        }
    } else {
        QMessageBox::warning(this, "Selection Error", "Please select a team to modify.");
    }
}

void MainWindow::on_downloadButton_clicked()
{
    int selectedRow = ui->tableWidget->currentRow();
    if (selectedRow < 0) {
        QMessageBox::warning(this, "No Selection", "Please select a row to download.");
        return;
    }

    QString data;
    QStringList headers = {"Team Name", "Home Stadium", "Budget", "Team ABV", "Team Logo"};
    for (int col = 0; col < ui->tableWidget->columnCount(); ++col) {
        QTableWidgetItem *item = ui->tableWidget->item(selectedRow, col);
        if (item) {
            data += headers[col] + ": " + item->text() + "\n";
        }
    }

    QString fileName = QFileDialog::getSaveFileName(this, "Save File", "", "PDF Files (*.pdf);;All Files (*)");
    if (fileName.isEmpty()) {
        return;
    }

    QPdfWriter pdfWriter(fileName);
    pdfWriter.setPageSize(QPageSize(QPageSize::A4));
    pdfWriter.setPageMargins(QMargins(30, 30, 30, 30));

    QPainter painter(&pdfWriter);
    painter.setFont(QFont("Times", 12));
    painter.drawText(100, 100, data);
    painter.end();

    QMessageBox::information(this, "Download Complete", "The data has been downloaded successfully.");
}
