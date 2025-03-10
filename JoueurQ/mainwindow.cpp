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
#include <QItemSelection>

#include <QPainter>
#include <QFileDialog>

#include <QPdfWriter>
#include <QTextDocument>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , currentDisplayedPlayerId(-1)  // Initialiser à -1 (pas de joueur affiché)
{
    ui->setupUi(this);
    
    // Initialize positions combobox
    ui->comboBoxPosition->clear();
    ui->comboBoxPosition->addItems({"Goalkeeper", "Defender", "Midfielder", "Forward"});
    
    // Initialiser les options de tri
    ui->comboBoxTri->clear();
    ui->comboBoxTri->addItem("Default (No Sorting)", "none");
    ui->comboBoxTri->addItem("Name (A-Z)", "name_asc");
    ui->comboBoxTri->addItem("Name (Z-A)", "name_desc");
    ui->comboBoxTri->addItem("Team", "team");
    ui->comboBoxTri->addItem("Position", "position");
    ui->comboBoxTri->addItem("Goals (High-Low)", "goals_desc");
    ui->comboBoxTri->addItem("Goals (Low-High)", "goals_asc");
    
    // Connect buttons
    connect(ui->button1, &QPushButton::clicked, this, &MainWindow::on_button1_clicked);
    connect(ui->toolButton, &QToolButton::clicked, this, &MainWindow::on_toolButtonImage_clicked);
    connect(ui->pushButton_3, &QPushButton::clicked, this, &MainWindow::on_buttonDelete_clicked);
    connect(ui->lineEdit_10, &QLineEdit::textChanged, this, &MainWindow::onSearchTextChanged); // Connect search field
    connect(ui->buttonViewDetails, &QPushButton::clicked, this, &MainWindow::on_buttonViewDetails_clicked);
    connect(ui->comboBoxTri, &QComboBox::currentIndexChanged, this, &MainWindow::onSortingChanged);
    
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

    connect(ui->tableWidget->selectionModel(), &QItemSelectionModel::selectionChanged, 
        this, &MainWindow::onTableSelectionChanged);
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

    // Reduce number of columns to essential attributes
    ui->tableWidget->setColumnCount(7); // Reduced from 14
    ui->tableWidget->setHorizontalHeaderLabels({
        "ID", "First Name", "Last Name", "Position", "Team", "Jersey", "Status"
    });

    // Execute query to retrieve players with team name
    QSqlQuery query("SELECT j.id_player, j.first_name, j.last_name, j.position, "
                    "e.team_name, j.jersey_nb, j.status "
                    "FROM joueur j "
                    "JOIN equipe e ON j.id_team = e.id_team");

    // Loop through query results
    int row = 0;
    while (query.next()) {
        // Add new row to table
        ui->tableWidget->insertRow(row);

        
        ui->tableWidget->setItem(row, 0, new QTableWidgetItem(query.value(0).toString())); // id_player
        ui->tableWidget->setItem(row, 1, new QTableWidgetItem(query.value(1).toString())); // first_name
        ui->tableWidget->setItem(row, 2, new QTableWidgetItem(query.value(2).toString())); // last_name
        ui->tableWidget->setItem(row, 3, new QTableWidgetItem(query.value(3).toString())); // position
        ui->tableWidget->setItem(row, 4, new QTableWidgetItem(query.value(4).toString())); // team_name
        ui->tableWidget->setItem(row, 5, new QTableWidgetItem(query.value(5).toString())); // jersey_nb
        
        // Convert integer status to text
        int status = query.value(6).toInt();
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
        
        ui->tableWidget->setItem(row, 6, new QTableWidgetItem(statusText)); // status
        
        row++;
    }

    // Optional: resize columns to fit content
    ui->tableWidget->resizeColumnsToContents();
    
    // Update status bar with total count
    if (statusBar()) {
        statusBar()->showMessage(QString("%1 players in total").arg(row));
    }
    onSortingChanged(ui->comboBoxTri->currentIndex());
}

void MainWindow::onSearchTextChanged(const QString &text)
{
    // Si le champ de recherche est vide, montrer tous les joueurs
    if (text.isEmpty()) {
        loadPlayers();
        return;
    }
    
    // Récupérer l'identifiant de tri actuel
    int index = ui->comboBoxTri->currentIndex();
    QString sortOption = ui->comboBoxTri->itemData(index).toString();
    
    // Déterminer la clause ORDER BY selon l'option de tri
    QString orderByClause;
    if (sortOption == "name_asc") {
        orderByClause = " ORDER BY j.last_name ASC, j.first_name ASC";
    } else if (sortOption == "name_desc") {
        orderByClause = " ORDER BY j.last_name DESC, j.first_name DESC";
    } else if (sortOption == "team") {
        orderByClause = " ORDER BY e.team_name ASC, j.last_name ASC";
    } else if (sortOption == "position") {
        orderByClause = " ORDER BY j.position ASC, j.last_name ASC";
    } else if (sortOption == "goals_desc") {
        orderByClause = " ORDER BY j.goals DESC, j.last_name ASC";
    } else if (sortOption == "goals_asc") {
        orderByClause = " ORDER BY j.goals ASC, j.last_name ASC";
    }
    
    // Vider le tableau
    ui->tableWidget->clearContents();
    ui->tableWidget->setRowCount(0);
    
    // Construire la requête avec les conditions de recherche
    QString searchQuery = "SELECT j.id_player, j.first_name, j.last_name, j.position, "
                          "e.team_name, j.jersey_nb, j.status "
                          "FROM joueur j "
                          "JOIN equipe e ON j.id_team = e.id_team "
                          "WHERE j.first_name LIKE :search "
                          "OR j.last_name LIKE :search "
                          "OR j.nationality LIKE :search "
                          "OR j.position LIKE :search "
                          "OR e.team_name LIKE :search";
                          
    // Ajouter la clause ORDER BY si nécessaire
    if (!orderByClause.isEmpty()) {
        searchQuery += orderByClause;
    }
    
    QSqlQuery query;
    query.prepare(searchQuery);
    query.bindValue(":search", "%" + text + "%"); // Utiliser % pour la correspondance partielle
    
    if (query.exec()) {
        // Populate table with search results
        int row = 0;
        while (query.next()) {
            ui->tableWidget->insertRow(row);
            
            // Fill each column with query data (reduced set)
            ui->tableWidget->setItem(row, 0, new QTableWidgetItem(query.value(0).toString())); // id_player
            ui->tableWidget->setItem(row, 1, new QTableWidgetItem(query.value(1).toString())); // first_name
            ui->tableWidget->setItem(row, 2, new QTableWidgetItem(query.value(2).toString())); // last_name
            ui->tableWidget->setItem(row, 3, new QTableWidgetItem(query.value(3).toString())); // position
            ui->tableWidget->setItem(row, 4, new QTableWidgetItem(query.value(4).toString())); // team_name
            ui->tableWidget->setItem(row, 5, new QTableWidgetItem(query.value(5).toString())); // jersey_nb
            
            // Convert integer status to text
            int status = query.value(6).toInt();
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
            
            ui->tableWidget->setItem(row, 6, new QTableWidgetItem(statusText)); // status
            
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
    QString firstName = ui->tableWidget->item(row, 1)->text();
    QString lastName = ui->tableWidget->item(row, 2)->text();
    
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
        
        // If the deleted player was being displayed, hide the details frame
        if (currentDisplayedPlayerId == joueurId) {
            ui->formFrame->setVisible(false);
            currentDisplayedPlayerId = -1;
        }
        
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
        
        // Refresh player details if the modified player is currently displayed
        if (currentDisplayedPlayerId == joueurId) {
            refreshPlayerDetails();
        }
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

void MainWindow::on_buttonViewDetails_clicked()
{
    // Check if a player is selected
    if (!validateTableSelection()) {
        return;
    }
    
    // Get ID of selected player
    int row = ui->tableWidget->selectionModel()->selectedRows().first().row();
    int joueurId = ui->tableWidget->item(row, 0)->text().toInt();
    
    // Store the current displayed player ID
    currentDisplayedPlayerId = joueurId;
    
    // Load the player details
    refreshPlayerDetails();
}

void MainWindow::refreshPlayerDetails()
{
    // If no player is selected to display
    if (currentDisplayedPlayerId <= 0) {
        ui->formFrame->setVisible(false);
        return;
    }
    
    // Clear any existing content in the formFrame
    qDeleteAll(ui->formFrame->findChildren<QWidget*>(QString(), Qt::FindDirectChildrenOnly));
    
    // Create a layout for the frame if it doesn't already have one
    QLayout *existingLayout = ui->formFrame->layout();
    if (existingLayout) {
        delete existingLayout;  // Remove any existing layout
    }
    
    // Create new layout for the frame
    QVBoxLayout *frameLayout = new QVBoxLayout(ui->formFrame);
    ui->formFrame->setLayout(frameLayout);
    
    // Query all player details
    QSqlQuery query;
    query.prepare("SELECT j.*, e.team_name "
                  "FROM joueur j "
                  "JOIN equipe e ON j.id_team = e.id_team "
                  "WHERE j.id_player = :id");
    query.bindValue(":id", currentDisplayedPlayerId);
    
    if (query.exec() && query.next()) {
        // Créer un header stylisé avec le nom du joueur
        QString playerFullName = query.value("first_name").toString() + " " + query.value("last_name").toString();
        QLabel *playerNameHeader = new QLabel(playerFullName);
        QFont headerFont = playerNameHeader->font();
        headerFont.setBold(true);
        headerFont.setPointSize(16);
        playerNameHeader->setFont(headerFont);
        playerNameHeader->setAlignment(Qt::AlignCenter);
        playerNameHeader->setStyleSheet("background-color:rgba(0, 1, 8, 0.35); padding: 5px; border-radius: 3px;");
        frameLayout->addWidget(playerNameHeader);

        // Ajouter l'équipe sous le nom
        QLabel *teamLabel = new QLabel("Team: " + query.value("team_name").toString());
        teamLabel->setAlignment(Qt::AlignCenter);
        teamLabel->setStyleSheet("font-style: italic;");
        frameLayout->addWidget(teamLabel);

        // Ajouter un séparateur
        QFrame *line = new QFrame();
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);
        frameLayout->addWidget(line);

        // Bouton Export PDF
        QHBoxLayout *toolbarLayout = new QHBoxLayout();
        QPushButton *exportButton = new QPushButton("Export PDF");
        connect(exportButton, &QPushButton::clicked, [this, joueurId = currentDisplayedPlayerId]() {
            exportPlayerToPDF(joueurId);
        });
        QString buttonStyle = "QPushButton { padding: 5px 10px; border-radius: 3px; background-color: #4a86e8; color: white; }";
        buttonStyle += "QPushButton:hover { background-color: #3a76d8; }";
        exportButton->setStyleSheet(buttonStyle);
        toolbarLayout->addWidget(exportButton);
        toolbarLayout->addStretch();
        frameLayout->addLayout(toolbarLayout);

        // Create title label
        QLabel *titleLabel = new QLabel("Player Details");
        QFont titleFont = titleLabel->font();
        titleFont.setBold(true);
        titleFont.setPointSize(titleFont.pointSize() + 2);
        titleLabel->setFont(titleFont);
        titleLabel->setAlignment(Qt::AlignCenter);
        frameLayout->addWidget(titleLabel);
        
        // Create a horizontal layout for the form and image
        QHBoxLayout *contentLayout = new QHBoxLayout();
        
        // Create form layout for player details
        QFormLayout *formLayout = new QFormLayout();
        
        formLayout->addRow("ID:", new QLabel(query.value("id_player").toString()));
        formLayout->addRow("Team:", new QLabel(query.value("team_name").toString()));
        formLayout->addRow("First Name:", new QLabel(query.value("first_name").toString()));
        formLayout->addRow("Last Name:", new QLabel(query.value("last_name").toString()));
        formLayout->addRow("Position:", new QLabel(query.value("position").toString()));
        formLayout->addRow("Jersey Number:", new QLabel(query.value("jersey_nb").toString()));
        formLayout->addRow("Date of Birth:", new QLabel(query.value("date_of_birth").toDate().toString("dd/MM/yyyy")));
        formLayout->addRow("Nationality:", new QLabel(query.value("nationality").toString()));
        formLayout->addRow("Goals:", new QLabel(query.value("goals").toString()));
        formLayout->addRow("Assists:", new QLabel(query.value("assists").toString()));
        
        QString injured = query.value("injured").toInt() == 1 ? "Yes" : "No";
        formLayout->addRow("Injured:", new QLabel(injured));
        
        formLayout->addRow("Yellow Cards:", new QLabel(query.value("yellow_card").toString()));
        formLayout->addRow("Red Cards:", new QLabel(query.value("red_card").toString()));
        
        // Convert status to text
        int status = query.value("status").toInt();
        QString statusText;
        switch(status) {
            case 0: statusText = "Active"; break;
            case 1: statusText = "Injured"; break;
            case 2: statusText = "Suspended"; break;
            case 3: statusText = "Transferred"; break;
            default: statusText = "Unknown";
        }
        formLayout->addRow("Status:", new QLabel(statusText));
        
        // Add player image if available
        QLabel *imageLabel = new QLabel();
        imageLabel->setMinimumSize(150, 180);
        imageLabel->setMaximumSize(150, 180);
        imageLabel->setAlignment(Qt::AlignCenter);
        imageLabel->setFrameShape(QFrame::Box);
        QByteArray imageData = query.value("img_joueur").toByteArray();
        if (!imageData.isEmpty()) {
            QPixmap pixmap;
            pixmap.loadFromData(imageData);
            imageLabel->setPixmap(pixmap.scaled(150, 180, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        } else {
            imageLabel->setText("No Image");
        }
        
        // Add the form layout and image to the horizontal layout
        contentLayout->addLayout(formLayout, 3);  // Give the form more space
        contentLayout->addWidget(imageLabel, 1);  // Give the image less space
        
        // Add the content layout to the frame layout
        frameLayout->addLayout(contentLayout);
        
        // Make the frame visible if it's not already
        ui->formFrame->setVisible(true);
        
        // Add a "Close Details" button
        QPushButton *closeButton = new QPushButton("Hide Details");
        connect(closeButton, &QPushButton::clicked, [this]() {
            ui->formFrame->setVisible(false);
            currentDisplayedPlayerId = -1; // Reset current ID
        });
        
        frameLayout->addWidget(closeButton, 0, Qt::AlignRight);
        
        // Make sure to apply the layout
        ui->formFrame->updateGeometry();
    } else {
        QMessageBox::warning(this, "Error", "Could not retrieve player details.");
        ui->formFrame->setVisible(false);
        currentDisplayedPlayerId = -1; // Reset current ID
    }
}

void MainWindow::onTableSelectionChanged(const QItemSelection &selected, const QItemSelection &deselected)
{
    Q_UNUSED(deselected);
    
    // Only update if details are already being shown
    if (ui->formFrame->isVisible() && !selected.isEmpty()) {
        // Get the selected row index
        int row = selected.indexes().first().row();
        
        // Get the player ID from the first column
        int joueurId = ui->tableWidget->item(row, 0)->text().toInt();
        
        // Update the current displayed player ID
        currentDisplayedPlayerId = joueurId;
        
        // Refresh the details view
        refreshPlayerDetails();
    }
}

void MainWindow::onSortingChanged(int index)
{
    // Récupérer l'identifiant de tri sélectionné
    QString sortOption = ui->comboBoxTri->itemData(index).toString();
    
    // Construire la requête SQL en fonction de l'option de tri
    QString baseQuery = "SELECT j.id_player, j.first_name, j.last_name, j.position, "
                       "e.team_name, j.jersey_nb, j.status ";
    
    QString fromClause = "FROM joueur j "
                         "JOIN equipe e ON j.id_team = e.id_team ";
    
    QString orderByClause;
    
    // Déterminer la clause ORDER BY en fonction de l'option sélectionnée
    if (sortOption == "name_asc") {
        orderByClause = "ORDER BY j.last_name ASC, j.first_name ASC";
    } else if (sortOption == "name_desc") {
        orderByClause = "ORDER BY j.last_name DESC, j.first_name DESC";
    } else if (sortOption == "team") {
        orderByClause = "ORDER BY e.team_name ASC, j.last_name ASC";
    } else if (sortOption == "position") {
        orderByClause = "ORDER BY j.position ASC, j.last_name ASC";
    } else if (sortOption == "goals_desc") {
        orderByClause = "ORDER BY j.goals DESC, j.last_name ASC";
    } else if (sortOption == "goals_asc") {
        orderByClause = "ORDER BY j.goals ASC, j.last_name ASC";
    }
    // Si "none", pas de ORDER BY nécessaire
    
    // Construire la requête complète
    QString completeQuery = baseQuery + fromClause;
    if (!orderByClause.isEmpty()) {
        completeQuery += orderByClause;
    }
    
    // Effacer le tableau existant
    ui->tableWidget->clearContents();
    ui->tableWidget->setRowCount(0);
    
    // Exécuter la requête
    QSqlQuery query(completeQuery);
    
    // Remplir le tableau avec les résultats triés
    int row = 0;
    while (query.next()) {
        ui->tableWidget->insertRow(row);
        
        // Fill each column with query data (reduced set)
        ui->tableWidget->setItem(row, 0, new QTableWidgetItem(query.value(0).toString())); // id_player
        ui->tableWidget->setItem(row, 1, new QTableWidgetItem(query.value(1).toString())); // first_name
        ui->tableWidget->setItem(row, 2, new QTableWidgetItem(query.value(2).toString())); // last_name
        ui->tableWidget->setItem(row, 3, new QTableWidgetItem(query.value(3).toString())); // position
        ui->tableWidget->setItem(row, 4, new QTableWidgetItem(query.value(4).toString())); // team_name
        ui->tableWidget->setItem(row, 5, new QTableWidgetItem(query.value(5).toString())); // jersey_nb
        
        // Convert integer status to text
        int status = query.value(6).toInt();
        QString statusText;
        switch(status) {
            case 0: statusText = "Active"; break;
            case 1: statusText = "Injured"; break;
            case 2: statusText = "Suspended"; break;
            case 3: statusText = "Transferred"; break;
            default: statusText = "Unknown";
        }
        ui->tableWidget->setItem(row, 6, new QTableWidgetItem(statusText)); // status
        
        row++;
    }
    
    // Optional: resize columns to fit content
    ui->tableWidget->resizeColumnsToContents();
    
    // Update status bar with total count
    if (statusBar()) {
        statusBar()->showMessage(QString("%1 players in total").arg(row));
    }
}

QString MainWindow::generatePlayerHTML(int playerId)
{
    QSqlQuery query;
    query.prepare("SELECT j.*, e.team_name "
                 "FROM joueur j "
                 "JOIN equipe e ON j.id_team = e.id_team "
                 "WHERE j.id_player = :id");
    query.bindValue(":id", playerId);
    
    if (!query.exec() || !query.next()) {
        return "<h1>Error: Player not found</h1>";
    }
    
    // Récupérer les données du joueur
    QString firstName = query.value("first_name").toString();
    QString lastName = query.value("last_name").toString();
    QString team = query.value("team_name").toString();
    QString position = query.value("position").toString();
    int jerseyNumber = query.value("jersey_nb").toInt();
    QDate birthDate = query.value("date_of_birth").toDate();
    QString nationality = query.value("nationality").toString();
    int goals = query.value("goals").toInt();
    int assists = query.value("assists").toInt();
    bool isInjured = query.value("injured").toInt() == 1;
    int yellowCards = query.value("yellow_card").toInt();
    int redCards = query.value("red_card").toInt();
    
    // Récupérer l'image
    QByteArray imageData = query.value("img_joueur").toByteArray();
    QString imageBase64;
    if (!imageData.isEmpty()) {
        // Convertir l'image en base64 pour l'inclure dans le HTML
        imageBase64 = QString("data:image/jpeg;base64,") + imageData.toBase64();
    }
    
    // Convertir le statut en texte et définir une couleur
    int status = query.value("status").toInt();
    QString statusText;
    QString statusColor;
    
    switch(status) {
        case 0: 
            statusText = "Active"; 
            statusColor = "#28a745"; // Vert
            break;
        case 1: 
            statusText = "Injured"; 
            statusColor = "#dc3545"; // Rouge
            break;
        case 2: 
            statusText = "Suspended"; 
            statusColor = "#fd7e14"; // Orange
            break;
        case 3: 
            statusText = "Transferred"; 
            statusColor = "#6c757d"; // Gris
            break;
        default: 
            statusText = "Unknown";
            statusColor = "#6c757d"; // Gris
    }
    
    // Choisir une couleur en fonction de la position
    QString positionColor;
    if (position == "Goalkeeper") {
        positionColor = "#ffc107"; // Jaune
    } else if (position == "Defender") {
        positionColor = "#007bff"; // Bleu
    } else if (position == "Midfielder") {
        positionColor = "#28a745"; // Vert
    } else if (position == "Forward") {
        positionColor = "#dc3545"; // Rouge
    } else {
        positionColor = "#6c757d"; // Gris
    }
    
    // Construire le HTML avec des styles améliorés pour éviter les coupures de texte
    QString html = "<!DOCTYPE html><html><head><meta charset='utf-8'><style>";
    html += "* { box-sizing: border-box; }";
    html += "body { font-family: Arial, sans-serif; margin: 0 auto; padding: 10px; font-size: 10pt; line-height: 1.4; color: #333; background-color: #fff; text-align: center; max-width: 100%; word-wrap: break-word; }";
    html += "h1 { color: white; text-align: center; font-size: 22pt; margin: 0; padding: 10px 0; }";
    html += "h2 { color: #2c3e50; border-bottom: 2px solid #3498db; padding-bottom: 8px; font-size: 16pt; margin-top: 20px; text-align: center; }";
    
    // En-tête avec dégradé
    html += ".player-header { background: linear-gradient(135deg, #1a365d 0%, #2980b9 100%); color: white; padding: 10px; border-radius: 8px; text-align: center; box-shadow: 0 3px 5px rgba(0,0,0,0.1); margin: 0 auto 15px auto; width: 100%; }";
    html += ".player-header p { color: white; font-size: 12pt; margin: 8px 0 0 0; }";
    html += ".player-details { background-color: #fff; padding: 10px; border-radius: 8px; box-shadow: 0 2px 4px rgba(0,0,0,0.05); margin: 0 auto; width: 100%; }";
    
    // Tableaux stylisés avec table-layout: fixed pour éviter les coupures
    html += "table { width: 100%; border-collapse: collapse; margin: 15px auto; box-shadow: 0 2px 3px rgba(0,0,0,0.1); border-radius: 5px; overflow: hidden; table-layout: fixed; }";
    html += "th, td { padding: 8px; text-align: left; border-bottom: 1px solid #e1e1e1; word-wrap: break-word; white-space: normal; }";
    html += "th, td { padding: 8px; text-align: left; border-bottom: 1px solid #e1e1e1; word-wrap: break-word; white-space: normal; }";
    html += "th { background-color: #f8f9fa; width: 35%; font-weight: bold; color: #495057; }";
    html += "td { width: 65%; }";
    html += "tr:last-child td, tr:last-child th { border-bottom: none; }";
    html += "tr:nth-child(even) { background-color: #f8f9fa; }";
    
    // Mise en forme spéciale pour certaines informations
    html += ".status { font-weight: bold; color: " + statusColor + "; padding: 3px 8px; background-color: " + statusColor + "20; border-radius: 4px; display: inline-block; }";
    html += ".position { font-weight: bold; color: " + positionColor + "; padding: 3px 8px; background-color: " + positionColor + "20; border-radius: 4px; display: inline-block; }";
    html += ".jersey { font-weight: bold; font-size: 12pt; display: inline-block; background-color: #e9ecef; color: #495057; width: 25px; height: 25px; line-height: 25px; text-align: center; border-radius: 50%; }";
    
    // Style pour l'image du joueur
    html += ".player-image { text-align: center; margin: 8px auto; }";
    html += ".player-image img { max-width: 120px; height: auto; border-radius: 5px; box-shadow: 0 2px 4px rgba(0,0,0,0.2); }";
    
    // Statistiques avec style
    html += ".statistics { margin-top: 15px; }";
    html += ".stats-container { display: block; width: 100%; margin: 15px auto; text-align: center; }";
    html += ".stat-box { display: inline-block; width: 22%; margin: 0 1%; vertical-align: top; }";
    html += ".stat-value { font-size: 16pt; font-weight: bold; color: #2c3e50; }";
    html += ".stat-label { font-size: 9pt; color: #6c757d; margin-top: 3px; }";
    
    // Pied de page
    html += ".footer { text-align: center; margin-top: 20px; padding-top: 10px; color: #6c757d; font-size: 9pt; border-top: 1px solid #e1e1e1; }";
    html += "</style></head><body>";
    
    // En-tête du joueur
    html += "<div class='player-header'>";
    html += QString("<h1>%1 %2</h1>").arg(firstName, lastName);
    html += QString("<p><span class='position'>%1</span> | <span class='jersey'>#%2</span> | <strong>%3</strong></p>").arg(position, QString::number(jerseyNumber), team);
    html += "</div>";
    
    // Image du joueur
    if (!imageData.isEmpty()) {
        html += "<div class='player-image'>";
        // Spécifier la largeur et la hauteur directement dans la balise img
        html += "<img src='" + imageBase64 + "' width='150' alt='Player Image'>";
        html += "</div>";
    }
    
    // Détails du joueur
    html += "<div class='player-details'>";
    html += "<h2>Player Information</h2>";
    html += "<table>";
    html += QString("<tr><th>Player ID</th><td>%1</td></tr>").arg(playerId);
    html += QString("<tr><th>Full Name</th><td>%1 %2</td></tr>").arg(firstName, lastName);
    html += QString("<tr><th>Team</th><td>%1</td></tr>").arg(team);
    
    // Pour la position, utiliser un span avec class mais aussi réduire le padding
    html += "<tr><th>Position</th><td><span class='position' style='padding:2px 5px;'>" + position + "</span></td></tr>";
    
    html += QString("<tr><th>Jersey Number</th><td><span class='jersey'>#%1</span></td></tr>").arg(jerseyNumber);
    
    // Simplifier l'affichage de la date de naissance pour éviter les coupures
    int age = QDate::currentDate().year() - birthDate.year() - 
              (QDate::currentDate().dayOfYear() < birthDate.dayOfYear() ? 1 : 0);
    html += QString("<tr><th>Birth Date</th><td>%1 (%2 yrs)</td></tr>")
            .arg(birthDate.toString("dd/MM/yyyy"))
            .arg(age);
            
    html += QString("<tr><th>Nationality</th><td>%1</td></tr>").arg(nationality);
    html += QString("<tr><th>Status</th><td><span class='status' style='padding:2px 5px;'>%1</span></td></tr>").arg(statusText);
    html += QString("<tr><th>Injured</th><td>%1</td></tr>").arg(isInjured ? "Yes" : "No");
    html += "</table>";
    
    // Statistiques avec affichage visuel
    html += "<h2>Player Statistics</h2>";
    
    // Afficher les statistiques dans des boîtes
    html += "<div class='stats-container' style='display:block; text-align:center;'>";
    html += QString("<div class='stat-box' style='display:inline-block; width:22%; margin:0 1%;'><div class='stat-value'>%1</div><div class='stat-label'>Goals</div></div>").arg(goals);
    html += QString("<div class='stat-box' style='display:inline-block; width:22%; margin:0 1%;'><div class='stat-value'>%1</div><div class='stat-label'>Assists</div></div>").arg(assists);
    html += QString("<div class='stat-box' style='display:inline-block; width:22%; margin:0 1%;'><div class='stat-value'>%1</div><div class='stat-label'>Yellow Cards</div></div>").arg(yellowCards);
    html += QString("<div class='stat-box' style='display:inline-block; width:22%; margin:0 1%;'><div class='stat-value'>%1</div><div class='stat-label'>Red Cards</div></div>").arg(redCards);
    html += "</div>";
    
    // Table des statistiques détaillées
    html += "<table>";
    html += QString("<tr><th>Goals</th><td>%1</td></tr>").arg(goals);
    html += QString("<tr><th>Assists</th><td>%1</td></tr>").arg(assists);
    html += QString("<tr><th>Yellow Cards</th><td>%1</td></tr>").arg(yellowCards);
    html += QString("<tr><th>Red Cards</th><td>%1</td></tr>").arg(redCards);
    html += "</table>";
    html += "</div>"; // Fermeture de player-details
    
    // Pied de page
    html += "<div class='footer'>";
    html += "Generated on " + QDate::currentDate().toString("dd/MM/yyyy") + " by AL DAWRY Football Management System";
    html += "</div>";
    html += "</body></html>";
    
    return html;
}

void MainWindow::exportPlayerToPDF(int playerId)
{
    // 🔹 Récupération des informations du joueur
    QSqlQuery query;
    query.prepare("SELECT j.*, e.team_name FROM joueur j JOIN equipe e ON j.id_team = e.id_team WHERE j.id_player = :id");
    query.bindValue(":id", playerId);

    if (!query.exec() || !query.next()) {
        QMessageBox::warning(this, "Error", "Player not found");
        return;
    }

    // 🔹 Récupération des données du joueur
    QString firstName = query.value("first_name").toString();
    QString lastName = query.value("last_name").toString();
    QString team = query.value("team_name").toString();
    QString position = query.value("position").toString();
    int jerseyNumber = query.value("jersey_nb").toInt();
    QDate birthDate = query.value("date_of_birth").toDate();
    QString nationality = query.value("nationality").toString();
    int goals = query.value("goals").toInt();
    int assists = query.value("assists").toInt();
    int yellowCards = query.value("yellow_card").toInt();
    int redCards = query.value("red_card").toInt();
    bool isInjured = query.value("injured").toInt() == 1;

    // 🔹 Récupération de l'image
    QByteArray imageData = query.value("img_joueur").toByteArray();
    QPixmap playerImage;
    bool hasImage = false;
    
    if (!imageData.isEmpty()) {
        hasImage = playerImage.loadFromData(imageData);
    }

    // 🔹 Sélection du fichier PDF
    QString defaultFileName = firstName + "_" + lastName + "_Profile.pdf";
    QString fileName = QFileDialog::getSaveFileName(this, "Export PDF", QDir::homePath() + "/" + defaultFileName, "PDF Files (*.pdf)");

    if (fileName.isEmpty()) return;

    // 🔹 Création du PDF
    QPdfWriter pdfWriter(fileName);
    pdfWriter.setPageSize(QPageSize(QPageSize::A4));
    pdfWriter.setResolution(300);
    pdfWriter.setPageMargins(QMarginsF(20, 20, 20, 20));

    QPainter painter(&pdfWriter);
    painter.setRenderHint(QPainter::Antialiasing);

    // 📌 Définition des polices et couleurs
    QFont titleFont("Arial", 26, QFont::Bold);
    QFont sectionFont("Arial", 18, QFont::Bold);
    QFont normalFont("Arial", 14);
    QColor headerColor(26, 54, 93);  // Bleu foncé
    QColor lineColor(180, 180, 180); // Gris clair
    QColor backgroundColor(240, 240, 240); // Fond clair

    // 🔹 Espacement XXL entre toutes les lignes 📏
    int y = 120;
    int lineSpacing = 85; // Super espacement entre chaque ligne

    // Positions horizontales des champs et valeurs (avec plus d'espace entre eux)
    int labelX = 50;      // Position X pour les labels (ex: "Yellow Card:")
    int valueX = 550;     // Position X pour les valeurs (ex: "5") - AUGMENTÉE pour plus d'espace

    // 📌 Dessin du cadre principal
    painter.setBrush(backgroundColor);
    painter.setPen(Qt::NoPen);
    painter.drawRect(20, 20, pdfWriter.width() - 40, pdfWriter.height() - 40);

    // 📌 Titre principal (Nom du joueur)
    painter.setFont(titleFont);
    painter.setPen(headerColor);
    
    // Centrer le titre du joueur
    QString playerFullName = firstName + " " + lastName;
    QFontMetrics titleMetrics(titleFont); // Correction ici
    int titleWidth = titleMetrics.horizontalAdvance(playerFullName);
    int titleX = (pdfWriter.width() - titleWidth) / 2.2;
    
    painter.drawText(titleX, y, playerFullName);
    y += lineSpacing + 30; // ÉNORME espace après le titre

    // 📌 Image du joueur avec un cadre et une ombre
    if (hasImage) {
        QPixmap scaledImage = playerImage.scaled(180, 180, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        int imageX = (pdfWriter.width() - scaledImage.width()) / 2;
        
        // Ombre portée (effet simple)
        painter.setPen(Qt::NoPen);
        painter.setBrush(QColor(100, 100, 100, 80));
        painter.drawRect(imageX + 5, y + 5, scaledImage.width(), scaledImage.height());
        
        // Image
        painter.setBrush(Qt::NoBrush);
        painter.drawPixmap(imageX, y, scaledImage);
        
        // Cadre
        painter.setPen(QPen(Qt::black, 2));
        painter.drawRect(imageX, y, scaledImage.width(), scaledImage.height());
        
        y += scaledImage.height() + 50; // Grand espace après l'image
    } else {
        painter.setFont(normalFont);
        painter.drawText((pdfWriter.width() / 2) - 80, y, "No Image Available");
        y += lineSpacing;
    }

    // 📌 Sous-titre (position, numéro, équipe)
    painter.setFont(normalFont);
    QString subtitle = position + " | #" + QString::number(jerseyNumber) + " | " + team;
    QFontMetrics normalMetrics(normalFont); // Correction ici aussi
    int subtitleWidth = normalMetrics.horizontalAdvance(subtitle);
    int subtitleX = (pdfWriter.width() - subtitleWidth) / 2;
    
    painter.drawText(subtitleX, y, subtitle);
    y += lineSpacing;

    // 📌 Ligne de séparation décorative
    painter.setPen(QPen(lineColor, 3));
    painter.drawLine(50, y, 550, y);
    y += lineSpacing;

    // 📌 Informations du joueur
    painter.setFont(sectionFont);
    painter.setPen(headerColor);
    painter.drawText(labelX, y, "Player Information");
    y += lineSpacing;

    painter.setFont(normalFont);
    painter.setPen(Qt::black);

    QStringList labels = {"Player ID:", "Full Name:", "Team:", "Position:", "Jersey Number:", "Birth Date:", "Nationality:", "Injured:"};
    QStringList values = {QString::number(playerId), 
                          firstName + " " + lastName, 
                          team, 
                          position, 
                          "#" + QString::number(jerseyNumber), 
                          birthDate.toString("dd/MM/yyyy"), 
                          nationality, 
                          isInjured ? "Yes" : "No"};

    for (int i = 0; i < labels.size(); i++) {
        painter.drawText(labelX, y, labels[i]);
        painter.drawText(valueX, y, values[i]);
        y += lineSpacing;
    }

    // 📌 Ligne de séparation
    painter.setPen(QPen(lineColor, 3));
    painter.drawLine(50, y, 550, y);
    y += lineSpacing;

    // 📌 Statistiques du joueur
    painter.setFont(sectionFont);
    painter.setPen(headerColor);
    painter.drawText(labelX, y, "Player Statistics");
    y += lineSpacing;

    painter.setFont(normalFont);
    painter.setPen(Qt::black);

    // Ajout de sections visuelles pour les statistiques
    int statBoxWidth = 110;
    int statSpacing = 20;
    int statStartX = (pdfWriter.width() - (4 * statBoxWidth + 3 * statSpacing)) / 2;
    
    // Dessiner des boîtes pour les statistiques
    painter.setFont(QFont("Arial", 16, QFont::Bold));
    
    // Goals
    painter.setBrush(QColor(240, 240, 250));
    painter.setPen(QPen(headerColor, 1));
    painter.drawRect(statStartX, y, statBoxWidth, 80);
    painter.drawText(statStartX + 5, y + 35, QString::number(goals));
    painter.setFont(QFont("Arial", 10));
    painter.drawText(statStartX + 5, y + 60, "Goals");
    
    // Assists
    painter.setFont(QFont("Arial", 16, QFont::Bold));
    painter.setBrush(QColor(240, 250, 240));
    painter.drawRect(statStartX + statBoxWidth + statSpacing, y, statBoxWidth, 80);
    painter.drawText(statStartX + statBoxWidth + statSpacing + 5, y + 35, QString::number(assists));
    painter.setFont(QFont("Arial", 10));
    painter.drawText(statStartX + statBoxWidth + statSpacing + 5, y + 60, "Assists");
    
    // Yellow Cards
    painter.setFont(QFont("Arial", 16, QFont::Bold));
    painter.setBrush(QColor(255, 252, 230));
    painter.drawRect(statStartX + 2 * (statBoxWidth + statSpacing), y, statBoxWidth, 80);
    painter.drawText(statStartX + 2 * (statBoxWidth + statSpacing) + 5, y + 35, QString::number(yellowCards));
    painter.setFont(QFont("Arial", 10));
    painter.drawText(statStartX + 2 * (statBoxWidth + statSpacing) + 5, y + 60, "Yellow Cards");
    
    // Red Cards
    painter.setFont(QFont("Arial", 16, QFont::Bold));
    painter.setBrush(QColor(255, 230, 230));
    painter.drawRect(statStartX + 3 * (statBoxWidth + statSpacing), y, statBoxWidth, 80);
    painter.drawText(statStartX + 3 * (statBoxWidth + statSpacing) + 5, y + 35, QString::number(redCards));
    painter.setFont(QFont("Arial", 10));
    painter.drawText(statStartX + 3 * (statBoxWidth + statSpacing) + 5, y + 60, "Red Cards");
    
    y += 100; // Espace après les boîtes de statistiques
    
    // Tableau détaillé des statistiques
    painter.setFont(normalFont);
    QStringList statsLabels = {"Goals:", "Assists:", "Yellow Cards:", "Red Cards:"};
    QStringList statsValues = {QString::number(goals), QString::number(assists), QString::number(yellowCards), QString::number(redCards)};

    for (int i = 0; i < statsLabels.size(); i++) {
        painter.drawText(labelX, y, statsLabels[i]);
        painter.drawText(valueX, y, statsValues[i]);
        y += lineSpacing;
    }

    // 📌 Pied de page décoré
    painter.setPen(Qt::gray);
    painter.drawLine(50, y + 30, 550, y + 30);
    painter.setFont(QFont("Arial", 10));
    painter.drawText(50, y + 60, "Generated on " + QDate::currentDate().toString("dd/MM/yyyy") + " by AL DAWRY Football Management System");

    // 🔹 Fin du dessin
    painter.end();

    // 🔹 Message de confirmation
    QMessageBox::information(this, "Export PDF", "Player profile successfully exported to:\n" + fileName);
}
