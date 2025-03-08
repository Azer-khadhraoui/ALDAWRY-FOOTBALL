#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QMessageBox>
#include <QFileDialog>
#include <QFile>
#include <QPixmap>
#include <QRegularExpression>
#include "joueur.h"
#include "deletejoueur.h"
#include "modifyjoueur.h" 

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)  
{
    ui->setupUi(this);
    
    // Initialize positions combobox
    ui->comboBoxPosition->clear();
    ui->comboBoxPosition->addItems({"Goalkeeper", "Defender", "Midfielder", "Forward"});
    
    // Connect buttons
    connect(ui->button1, &QPushButton::clicked, this, &MainWindow::on_button1_clicked);
    connect(ui->toolButton, &QToolButton::clicked, this, &MainWindow::on_toolButtonImage_clicked);
    connect(ui->pushButton_3, &QPushButton::clicked, this, &MainWindow::on_buttonDelete_clicked);
    connect(ui->lineEdit_10, &QLineEdit::textChanged, this, &MainWindow::onSearchTextChanged); // Connect search field
    
    // Set placeholder text for search field
    ui->lineEdit_10->setPlaceholderText("Search players by name, nationality, position...");
    
    // Set up table
    ui->tableWidget->setColumnCount(14);
    ui->tableWidget->setHorizontalHeaderLabels({
        "ID Player", "ID Team", "First Name", "Last name", "Position", "Jersey Number", "Date of Birth",
        "Nationality", "Goals", "Assists", "Injury", "Yellow Card", "Red Card", "Status"
    });
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);  // Make table non-editable

    loadTeams();
    loadPlayers();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::loadTeams()
{
    // Clear combobox and map
    ui->comboBoxTeam->clear();
    teamMap.clear();
    
    // Load all teams from database
    QSqlQuery query("SELECT id_team, team_name FROM equipe ORDER BY team_name");
    
    while (query.next()) {
        int id = query.value(0).toInt();
        QString name = query.value(1).toString();
        
        // Add to combobox and map
        ui->comboBoxTeam->addItem(name);
        teamMap[name] = id;
    }
    
    if (ui->comboBoxTeam->count() == 0) {
        // No teams found
        QMessageBox::warning(this, "Warning", "No teams were found in the database.");
    }
}

void MainWindow::loadPlayers()
{
    // Clear table
    ui->tableWidget->clearContents();
    ui->tableWidget->setRowCount(0);

    // Make the table non-editable
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

    // Execute query to retrieve players
    QSqlQuery query("SELECT id_player, id_team, first_name, last_name, position, jersey_nb, date_of_birth, nationality, goals, assists, injured, yellow_card, red_card, status FROM joueur");

    // Loop through query results
    int row = 0;
    while (query.next()) {
        // Add new row to table
        ui->tableWidget->insertRow(row);

        // Fill each column with query data
        ui->tableWidget->setItem(row, 0, new QTableWidgetItem(query.value(0).toString())); // id_player
        ui->tableWidget->setItem(row, 1, new QTableWidgetItem(query.value(1).toString())); // id_team
        ui->tableWidget->setItem(row, 2, new QTableWidgetItem(query.value(2).toString())); // first_name
        ui->tableWidget->setItem(row, 3, new QTableWidgetItem(query.value(3).toString())); // last_name
        ui->tableWidget->setItem(row, 4, new QTableWidgetItem(query.value(4).toString())); // position
        ui->tableWidget->setItem(row, 5, new QTableWidgetItem(query.value(5).toString())); // jersey_nb
        ui->tableWidget->setItem(row, 6, new QTableWidgetItem(query.value(6).toDate().toString("dd/MM/yyyy"))); // date_of_birth
        ui->tableWidget->setItem(row, 7, new QTableWidgetItem(query.value(7).toString())); // nationality
        ui->tableWidget->setItem(row, 8, new QTableWidgetItem(query.value(8).toString())); // goals
        ui->tableWidget->setItem(row, 9, new QTableWidgetItem(query.value(9).toString())); // assists
        ui->tableWidget->setItem(row, 10, new QTableWidgetItem(query.value(10).toInt() == 1 ? "Yes" : "No")); // injured
        ui->tableWidget->setItem(row, 11, new QTableWidgetItem(query.value(11).toString())); // yellow_card
        ui->tableWidget->setItem(row, 12, new QTableWidgetItem(query.value(12).toString())); // red_card
        
        // Convert integer status to text
        int status = query.value(13).toInt();
        QString statusText;
        
        switch(status) {
            case 0:
                statusText = "Active";
                break;
            case 1:
                statusText = "Injured";
                break;
            case 2:
                statusText = "Suspended";
                break;
            case 3:
                statusText = "Transferred";
                break;
            default:
                statusText = "Unknown";
        }
        
        ui->tableWidget->setItem(row, 13, new QTableWidgetItem(statusText)); // status
        
        row++;
    }

    // Optional: resize columns to fit content
    ui->tableWidget->resizeColumnsToContents();
    
    // Update status bar with total count
    if (statusBar()) {
        statusBar()->showMessage(QString("%1 players in total").arg(row));
    }
}

void MainWindow::onSearchTextChanged(const QString &text)
{
    // If search text is empty, show all players
    if (text.isEmpty()) {
        loadPlayers();
        return;
    }
    
    // Clear the table
    ui->tableWidget->clearContents();
    ui->tableWidget->setRowCount(0);
    
    // Build query with search conditions (search in multiple fields)
    QString searchQuery = "SELECT id_player, id_team, first_name, last_name, position, jersey_nb, "
                         "date_of_birth, nationality, goals, assists, injured, yellow_card, red_card, status "
                         "FROM joueur "
                         "WHERE first_name LIKE :search "
                         "OR last_name LIKE :search "
                         "OR nationality LIKE :search "
                         "OR position LIKE :search";
    
    QSqlQuery query;
    query.prepare(searchQuery);
    query.bindValue(":search", "%" + text + "%"); // Use % for wildcard matching
    
    if (query.exec()) {
        // Populate table with search results
        int row = 0;
        while (query.next()) {
            ui->tableWidget->insertRow(row);
            
            // Fill each column with query data
            ui->tableWidget->setItem(row, 0, new QTableWidgetItem(query.value(0).toString())); // id_player
            ui->tableWidget->setItem(row, 1, new QTableWidgetItem(query.value(1).toString())); // id_team
            ui->tableWidget->setItem(row, 2, new QTableWidgetItem(query.value(2).toString())); // first_name
            ui->tableWidget->setItem(row, 3, new QTableWidgetItem(query.value(3).toString())); // last_name
            ui->tableWidget->setItem(row, 4, new QTableWidgetItem(query.value(4).toString())); // position
            ui->tableWidget->setItem(row, 5, new QTableWidgetItem(query.value(5).toString())); // jersey_nb
            ui->tableWidget->setItem(row, 6, new QTableWidgetItem(query.value(6).toDate().toString("dd/MM/yyyy"))); // date_of_birth
            ui->tableWidget->setItem(row, 7, new QTableWidgetItem(query.value(7).toString())); // nationality
            ui->tableWidget->setItem(row, 8, new QTableWidgetItem(query.value(8).toString())); // goals
            ui->tableWidget->setItem(row, 9, new QTableWidgetItem(query.value(9).toString())); // assists
            ui->tableWidget->setItem(row, 10, new QTableWidgetItem(query.value(10).toInt() == 1 ? "Yes" : "No")); // injured
            ui->tableWidget->setItem(row, 11, new QTableWidgetItem(query.value(11).toString())); // yellow_card
            ui->tableWidget->setItem(row, 12, new QTableWidgetItem(query.value(12).toString())); // red_card
            
            // Convert integer status to text
            int status = query.value(13).toInt();
            QString statusText;
            
            switch(status) {
                case 0:
                    statusText = "Active";
                    break;
                case 1:
                    statusText = "Injured";
                    break;
                case 2:
                    statusText = "Suspended";
                    break;
                case 3:
                    statusText = "Transferred";
                    break;
                default:
                    statusText = "Unknown";
            }
            
            ui->tableWidget->setItem(row, 13, new QTableWidgetItem(statusText)); // status
            
            row++;
        }
        
        // Update status bar with search results count
        if (statusBar()) {
            statusBar()->showMessage(QString("%1 player(s) found").arg(row));
        }
    } else {
        qDebug() << "Search query error: " << query.lastError().text();
    }
}

void MainWindow::on_toolButtonImage_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Select an image", "", "Images (*.png *.jpg *.jpeg *.bmp)");
    if (!fileName.isEmpty()) {
        QFile file(fileName);
        if (file.open(QIODevice::ReadOnly)) {
            img_joueur = file.readAll();
            file.close();
            QPixmap pixmap;
            pixmap.loadFromData(img_joueur);
            ui->label_2->setPixmap(pixmap.scaled(ui->label_2->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
            QMessageBox::information(this, "Success", "Image loaded successfully.");
        } else {
            QMessageBox::critical(this, "Error", "Unable to read the image file.");
        }
    }
}

void MainWindow::on_button1_clicked()
{
    // Step 1: Verify team selection
    if (ui->comboBoxTeam->currentIndex() < 0) {
        QMessageBox::warning(this, "Error", "Please select a team.");
        return;
    }
    
    // Step 2: Get team ID
    QString teamName = ui->comboBoxTeam->currentText();
    int id_team = teamMap[teamName];
    
    // Step 3: Get and validate player information
    QString first_name = ui->lineEdit_3->text().trimmed();
    QString last_name = ui->lineEdit_4->text().trimmed();
    
    // Get position from comboBox instead of lineEdit
    QString position = ui->comboBoxPosition->currentText();
    
    QString nationality = ui->lineEdit_9->text().trimmed();
    
    // Step 4: Field validation
    
    // Check for empty fields
    if (first_name.isEmpty() || last_name.isEmpty() || nationality.isEmpty()) {
        QMessageBox::warning(this, "Error", "Please fill all required fields (First Name, Last Name, Nationality).");
        return;
    }
    
    // Validate name format (only letters and spaces)
    QRegularExpression nameRegex("^[A-Za-z\\s'-]+$");
    if (!nameRegex.match(first_name).hasMatch()) {
        QMessageBox::warning(this, "Error", "First name contains invalid characters. Only letters, spaces, hyphens and apostrophes are allowed.");
        ui->lineEdit_3->setFocus();
        return;
    }
    
    if (!nameRegex.match(last_name).hasMatch()) {
        QMessageBox::warning(this, "Error", "Last name contains invalid characters. Only letters, spaces, hyphens and apostrophes are allowed.");
        ui->lineEdit_4->setFocus();
        return;
    }
    
    // Position validation not needed anymore as it's limited by comboBox
    
    // Validate jersey number
    bool ok;
    int jersey_nb = ui->lineEdit_8->text().toInt(&ok);
    if (!ok || jersey_nb <= 0 || jersey_nb > 99) {
        QMessageBox::warning(this, "Error", "Jersey number must be a positive integer between 1 and 99.");
        ui->lineEdit_8->setFocus();
        return;
    }
    
    // Validate nationality
    if (!nameRegex.match(nationality).hasMatch()) {
        QMessageBox::warning(this, "Error", "Nationality contains invalid characters. Only letters, spaces, hyphens and apostrophes are allowed.");
        ui->lineEdit_9->setFocus();
        return;
    }
    
    // Validate birth date
    QDate date_of_birth = ui->dateEdit->date();
    QDate currentDate = QDate::currentDate();
    QDate minDate = currentDate.addYears(-50); // No players older than 50
    QDate maxDate = currentDate.addYears(-16); // No players younger than 16
    
    if (date_of_birth > maxDate || date_of_birth < minDate) {
        QMessageBox::warning(this, "Error", "Invalid date of birth. Player must be between 16 and 50 years old.");
        ui->dateEdit->setFocus();
        return;
    }
    
    // Step 5: Create and add player
    joueur newPlayer(id_team, first_name, last_name, position, jersey_nb, date_of_birth, nationality, img_joueur);
    
    if (newPlayer.ajouterDansBD()) {
        QMessageBox::information(this, "Success", "Player has been successfully added.");
        // Clear input fields
        ui->lineEdit_3->clear();
        ui->lineEdit_4->clear();
        // Don't clear comboBoxPosition as it contains valid values
        ui->lineEdit_8->clear();
        ui->lineEdit_9->clear();
        img_joueur.clear();
        ui->label_2->clear();

        // Clear search field to show all players including the newly added one
        ui->lineEdit_10->clear();
        
        // Update player table
        loadPlayers();
    } else {
        QMessageBox::critical(this, "Error", "Unable to add player to the database.");
    }
}

void MainWindow::on_buttonDelete_clicked()
{
    // Check if a player is selected
    if (!validateTableSelection()) {
        return;
    }
    
    // Get ID of selected player
    int row = ui->tableWidget->selectionModel()->selectedRows().first().row();
    int joueurId = ui->tableWidget->item(row, 0)->text().toInt();
    
    // Get player name for confirmation message
    QString firstName = ui->tableWidget->item(row, 2)->text();
    QString lastName = ui->tableWidget->item(row, 3)->text();
    
    // Ask user for confirmation
    QMessageBox::StandardButton confirmation;
    confirmation = QMessageBox::question(this, "Confirm Deletion", 
        "Are you sure you want to delete player " + firstName + " " + lastName + " (ID: " + QString::number(joueurId) + ")?",
        QMessageBox::Yes | QMessageBox::No);
        
    if (confirmation == QMessageBox::No) {
        return;
    }
    
    // Try to delete the player
    if (joueur::supprimer(joueurId)) {
        QMessageBox::information(this, "Success", "Player has been successfully deleted.");
        
        // Clear search field to show all players
        ui->lineEdit_10->clear();
        
        // Reload player list
        loadPlayers();
    } else {
        QMessageBox::critical(this, "Error", "Could not delete the player. Please try again.");
    }
}

void MainWindow::on_buttonModify_clicked()
{
    // Check if a player is selected
    if (!validateTableSelection()) {
        return;
    }
    
    ModifyJoueur modifyDialog(this);
    
    // Get selected player's ID
    int row = ui->tableWidget->selectionModel()->selectedRows().first().row();
    int joueurId = ui->tableWidget->item(row, 0)->text().toInt();
    modifyDialog.setJoueurId(joueurId);
    
    if (modifyDialog.exec() == QDialog::Accepted) {
        // Clear search field to show all players
        ui->lineEdit_10->clear();
        
        // Reload player list to reflect changes
        loadPlayers();
    }
}

bool MainWindow::validateTableSelection()
{
    QModelIndexList selection = ui->tableWidget->selectionModel()->selectedRows();
    if (selection.isEmpty()) {
        QMessageBox::warning(this, "Error", "Please select a player from the table first.");
        return false;
    }
    return true;
}