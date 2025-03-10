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
    
    // Construire le HTML avec des styles améliorés
    QString html = "<html><head><style>";
    html += "body { font-family: Arial, sans-serif; margin: 0; padding: 20px; font-size: 14pt; line-height: 1.5; color: #333; background-color: #fff; }";
    html += "h1 { color: white; text-align: center; font-size: 28pt; margin: 0; padding: 10px 0; }";
    html += "h2 { color: #2c3e50; border-bottom: 2px solid #3498db; padding-bottom: 8px; font-size: 22pt; margin-top: 30px; margin-bottom: 15px; }";
    
    // En-tête avec dégradé
    html += ".player-header { background: linear-gradient(135deg, #1a365d 0%, #2980b9 100%); color: white; padding: 20px; border-radius: 8px; text-align: center; box-shadow: 0 4px 6px rgba(0,0,0,0.1); margin-bottom: 30px; }";
    html += ".player-header p { color: white; font-size: 16pt; margin: 10px 0 0 0; }";
    html += ".player-details { background-color: #fff; padding: 20px; border-radius: 8px; box-shadow: 0 2px 4px rgba(0,0,0,0.05); }";
    
    // Tableaux stylisés
    html += "table { width: 100%; border-collapse: collapse; margin: 25px 0; box-shadow: 0 2px 3px rgba(0,0,0,0.1); border-radius: 5px; overflow: hidden; }";
    html += "th, td { padding: 15px; text-align: left; border-bottom: 1px solid #e1e1e1; }";
    html += "th { background-color: #f8f9fa; width: 35%; font-weight: bold; color: #495057; }";
    html += "tr:last-child td, tr:last-child th { border-bottom: none; }";
    html += "tr:nth-child(even) { background-color: #f8f9fa; }";
    
    // Mise en forme spéciale pour certaines informations
    html += ".status { font-weight: bold; color: " + statusColor + "; padding: 5px 10px; background-color: " + statusColor + "20; border-radius: 4px; display: inline-block; }";
    html += ".position { font-weight: bold; color: " + positionColor + "; padding: 5px 10px; background-color: " + positionColor + "20; border-radius: 4px; display: inline-block; }";
    html += ".jersey { font-weight: bold; font-size: 16pt; display: inline-block; background-color: #e9ecef; color: #495057; width: 40px; height: 40px; line-height: 40px; text-align: center; border-radius: 50%; }";
    
    // Statistiques avec style
    html += ".statistics { margin-top: 30px; }";
    html += ".stats-container { display: flex; justify-content: space-between; margin: 20px 0; }";
    html += ".stat-box { text-align: center; flex: 1; padding: 15px; background-color: #f8f9fa; border-radius: 8px; margin: 0 5px; box-shadow: 0 2px 4px rgba(0,0,0,0.05); }";
    html += ".stat-value { font-size: 24pt; font-weight: bold; color: #2c3e50; }";
    html += ".stat-label { font-size: 12pt; color: #6c757d; margin-top: 5px; }";
    
    // Pied de page
    html += ".footer { text-align: center; margin-top: 40px; padding-top: 20px; color: #6c757d; font-size: 11pt; border-top: 1px solid #e1e1e1; }";
    html += "</style></head><body>";
    
    // En-tête du joueur
    html += "<div class='player-header'>";
    html += QString("<h1>%1 %2</h1>").arg(firstName, lastName);
    html += QString("<p><span class='position'>%1</span> | <span class='jersey'>#%2</span> | <strong>%3</strong></p>").arg(position, QString::number(jerseyNumber), team);
    html += "</div>";
    
    // Détails du joueur
    html += "<div class='player-details'>";
    html += "<h2>Player Information</h2>";
    html += "<table>";
    html += QString("<tr><th>Player ID</th><td>%1</td></tr>").arg(playerId);
    html += QString("<tr><th>Full Name</th><td>%1 %2</td></tr>").arg(firstName, lastName);
    html += QString("<tr><th>Team</th><td>%1</td></tr>").arg(team);
    html += QString("<tr><th>Position</th><td><span class='position'>%1</span></td></tr>").arg(position);
    html += QString("<tr><th>Jersey Number</th><td><span class='jersey'>#%1</span></td></tr>").arg(jerseyNumber);
    html += QString("<tr><th>Date of Birth</th><td>%1 (%2 years old)</td></tr>")
            .arg(birthDate.toString("dd/MM/yyyy"))
            .arg(QDate::currentDate().year() - birthDate.year() - (QDate::currentDate().dayOfYear() < birthDate.dayOfYear() ? 1 : 0));
    html += QString("<tr><th>Nationality</th><td>%1</td></tr>").arg(nationality);
    html += QString("<tr><th>Status</th><td><span class='status'>%1</span></td></tr>").arg(statusText);
    html += QString("<tr><th>Currently Injured</th><td>%1</td></tr>").arg(isInjured ? "<span style='color:#dc3545; font-weight:bold;'>Yes</span>" : "No");
    html += "</table>";
    
    // Statistiques avec affichage visuel
    html += "<h2>Player Statistics</h2>";
    
    // Afficher les statistiques dans des boîtes
    html += "<div class='stats-container'>";
    html += QString("<div class='stat-box'><div class='stat-value'>%1</div><div class='stat-label'>Goals</div></div>").arg(goals);
    html += QString("<div class='stat-box'><div class='stat-value'>%1</div><div class='stat-label'>Assists</div></div>").arg(assists);
    html += QString("<div class='stat-box'><div class='stat-value'>%1</div><div class='stat-label'>Yellow Cards</div></div>").arg(yellowCards);
    html += QString("<div class='stat-box'><div class='stat-value'>%1</div><div class='stat-label'>Red Cards</div></div>").arg(redCards);
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
    QString html = generatePlayerHTML(playerId);
    
    // Demander à l'utilisateur où enregistrer le PDF
    QSqlQuery query;
    query.prepare("SELECT first_name, last_name FROM joueur WHERE id_player = :id");
    query.bindValue(":id", playerId);
    
    QString playerName = "player";
    if (query.exec() && query.next()) {
        playerName = query.value("first_name").toString() + "_" + query.value("last_name").toString();
    }
    
    QString defaultFileName = playerName + "_profile.pdf";
    QString fileName = QFileDialog::getSaveFileName(this, "Export PDF", 
                                               QDir::homePath() + "/" + defaultFileName, 
                                               "PDF Files (*.pdf)");
    
    if (fileName.isEmpty()) {
        return;  // L'utilisateur a annulé
    }
    
    // Créer le PDF
    QPdfWriter pdfWriter(fileName);
    pdfWriter.setPageSize(QPageSize(QPageSize::A4));
    
    // Augmenter la résolution à 600 DPI pour une meilleure qualité
    pdfWriter.setResolution(600);
    
    // Réduire les marges pour maximiser l'espace
    pdfWriter.setPageMargins(QMarginsF(15, 15, 15, 15));
    
    QPainter painter(&pdfWriter);
    
    // Créer un document HTML pour le rendu
    QTextDocument document;
    
    // La clé est d'ajuster la taille de base et le style avant de définir le HTML
    document.setDefaultFont(QFont("Arial", 11));
    
    // Définir le contenu HTML après avoir configuré la police par défaut
    document.setHtml(html);
    
    // Configurer la taille de page pour qu'elle corresponde au PDF
    QPageLayout pageLayout = pdfWriter.pageLayout();
    qreal pageWidth = pageLayout.paintRect().width();
    
    // Définir la taille du document pour qu'il s'adapte à la largeur de page
    // Ne PAS définir la hauteur pour permettre au contenu de s'étendre naturellement
    document.setPageSize(QSizeF(pageWidth, -1));
    
    // Dessiner le document sur le PDF - ceci est la partie clé
    document.drawContents(&painter);
    
    // Fermer le peintre pour finaliser l'écriture
    painter.end();
    
    // Informer l'utilisateur que l'export est terminé
    QMessageBox::information(this, "Export PDF", "Player profile has been exported to:\n" + fileName);
}