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
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QLabel>
#include <QTableWidget>
#include <QHeaderView>
#include <QPushButton>
#include "joueur.h"
#include "deletejoueur.h"
#include "modifyjoueur.h"
#include <QItemSelection>
#include <QGraphicsOpacityEffect>   // Ajouter cette ligne 
#include <QPropertyAnimation>       // Ajouter cette ligne
#include <QPainterPath>
#include <QTimer>
#include <QPainter>
#include <QFileDialog>
#include <QScrollArea> 
#include <QPdfWriter>
#include <QTextDocument>
#include <QMouseEvent>

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
    /*connect(comboBoxCompetition, QOverload<int>::of(&QComboBox::currentIndexChanged), 
    this, &MainWindow::refreshBestPlayer);*/
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

    // Ajouter ceci pour initialiser l'onglet statistiques
    setupStatisticsTab();
    setupBestPlayerTab();
    setupTeamOfCompetitionTab();

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
//qrcode
QString qrText = QString("ID: %1\nName: %2\nTeam: %3\nPosition: %4\nJersey: %5\nStatus: %6")
.arg(query.value("id_player").toString())
.arg(playerFullName)

.arg(query.value("team_name").toString())
.arg(query.value("position").toString())
.arg(query.value("jersey_nb").toString())
.arg(statusText);  // Ajout du statut
QPixmap qrCode = generateQRCode(qrText);

QLabel *qrLabel = new QLabel();

qrLabel->setPixmap(qrCode.scaled(100, 100, Qt::KeepAspectRatio, Qt::SmoothTransformation));  // Taille réduite
qrLabel->setAlignment(Qt::AlignCenter);

        // Add the form layout and image to the horizontal layout
        contentLayout->addLayout(formLayout, 3);  // Give the form more space
        contentLayout->addWidget(imageLabel, 1);  // Give the image less space


        // Add the content layout to the frame layout
        frameLayout->addLayout(contentLayout);
        frameLayout->addWidget(qrLabel);
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
    
    // Récupérer le statut du joueur et le convertir en texte
    int statusInt = query.value("status").toInt();
    QString statusText;
    switch(statusInt) {
        case 0: statusText = "Active"; break;
        case 1: statusText = "Injured"; break;
        case 2: statusText = "Suspended"; break;
        case 3: statusText = "Transferred"; break;
        default: statusText = "Unknown";
    }

    // 🔹 Récupération de l'image
    QByteArray imageData = query.value("img_joueur").toByteArray();
    QPixmap playerImage;
    bool hasImage = false;

    if (!imageData.isEmpty()) {
        hasImage = playerImage.loadFromData(imageData);
    }
// Générer le QR code
QString qrText = QString("ID: %1\nName: %2 %3\nTeam: %4\nPosition: %5\nJersey: %6\nStatus: %7")
.arg(playerId).arg(firstName).arg(lastName).arg(team).arg(position).arg(jerseyNumber).arg(statusText);
QPixmap qrCode = generateQRCode(qrText);
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
    int titleX = (pdfWriter.width() - titleWidth) / 2.58;

    painter.drawText(titleX, y, playerFullName);
    y += lineSpacing + 30; // ÉNORME espace après le titre

    // 📌 Image du joueur avec un cadre et une ombre
    if (hasImage) {
        QPixmap scaledImage = playerImage.scaled(500, 500, Qt::KeepAspectRatio, Qt::SmoothTransformation);
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

        y += scaledImage.height() + 55; // Grand espace après l'image
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
    int subtitleX = (pdfWriter.width() - subtitleWidth) / 2.47;

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
    int statBoxWidth = 230;
    int statSpacing = 100;
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

    y += 300; // Espace après les boîtes de statistiques

    // Tableau détaillé des statistiques
    painter.setFont(normalFont);
    QStringList statsLabels = {"Goals:", "Assists:", "Yellow Cards:", "Red Cards:"};
    QStringList statsValues = {QString::number(goals), QString::number(assists), QString::number(yellowCards), QString::number(redCards)};

    for (int i = 0; i < statsLabels.size(); i++) {
        painter.drawText(labelX, y, statsLabels[i]);
        painter.drawText(valueX, y, statsValues[i]);
        y += lineSpacing;
    }
    QPixmap scaledQrCode = qrCode.scaled(200, 200, Qt::KeepAspectRatio, Qt::SmoothTransformation);  // Taille réduite
    int qrX = (pdfWriter.width() - scaledQrCode.width()) / 2;
    painter.drawPixmap(qrX, y, scaledQrCode);
    y += scaledQrCode.height() + 50;

    painter.setPen(Qt::gray);
    painter.drawLine(50, y + 30, 550, y + 30);
    painter.setFont(QFont("Arial", 10));
    painter.drawText(50, y + 80, "Generated on " + QDate::currentDate().toString("dd/MM/yyyy") + " by AL DAWRY Football Management System");

    // 🔹 Fin du dessin
    painter.end();

    // 🔹 Message de confirmation
    QMessageBox::information(this, "Export PDF", "Player profile successfully exported to:\n" + fileName);
}

QFrame* MainWindow::createStatsCard(const QString &title, const QString &value, const QString &style)
{
    QFrame *card = new QFrame();
    card->setFrameShape(QFrame::Box);
    card->setFrameShadow(QFrame::Raised);
    card->setLineWidth(1);
    card->setStyleSheet("QFrame { border-radius: 8px; padding: 15px; " + style + " }");

    QVBoxLayout *layout = new QVBoxLayout(card);

    QLabel *valueLabel = new QLabel(value);
    QFont valueFont = valueLabel->font();
    valueFont.setPointSize(24);
    valueFont.setBold(true);
    valueLabel->setFont(valueFont);
    valueLabel->setAlignment(Qt::AlignCenter);

    QLabel *titleLabel = new QLabel(title);
    titleLabel->setAlignment(Qt::AlignCenter);

    layout->addWidget(valueLabel);
    layout->addWidget(titleLabel);

    return card;
}

void MainWindow::setupStatisticsTab()
{
    // Création de l'onglet statistiques
    QWidget *statTab = new QWidget();
    QVBoxLayout *mainLayout = new QVBoxLayout(statTab);

    // Titre principal
    QLabel *titleLabel = new QLabel("Player Statistics");
    QFont titleFont = titleLabel->font();
    titleFont.setPointSize(16);
    titleFont.setBold(true);
    titleLabel->setFont(titleFont);
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setStyleSheet("color:rgb(193, 224, 255); margin-bottom: 15px;");
    mainLayout->addWidget(titleLabel);

    // Section résumé
    QHBoxLayout *summaryLayout = new QHBoxLayout();

    // Carte du nombre total de joueurs
    QFrame *totalPlayersCard = createStatsCard("Total Players", QString::number(joueur::getTotalPlayers()), "background:rgb(6, 243, 97);");
    summaryLayout->addWidget(totalPlayersCard);

    // Cartes du total des cartes
    QMap<QString, int> cardStats = joueur::getCardStats();
    QFrame *yellowCardCard = createStatsCard("Yellow Cards", QString::number(cardStats["Jaunes"]), "background:rgb(243, 219, 3);");
    QFrame *redCardCard = createStatsCard("Red Cards", QString::number(cardStats["Rouges"]), "background:rgb(224, 3, 25);");
    summaryLayout->addWidget(yellowCardCard);
    summaryLayout->addWidget(redCardCard);

    mainLayout->addLayout(summaryLayout);

    // Conteneur pour les tableaux de statistiques
    QHBoxLayout *tablesLayout = new QHBoxLayout();

 // Dans setupStatisticsTab(), modifiez les tableaux

// Tableau des meilleurs buteurs
QGroupBox *topScorersGroup = new QGroupBox("Top Goalscorers");
topScorersGroup->setStyleSheet("QGroupBox { font-weight: bold; }");
QVBoxLayout *scorersLayout = new QVBoxLayout(topScorersGroup);
QTableWidget *scorersTable = new QTableWidget(0, 3); // 3 colonnes au lieu de 2
scorersTable->setObjectName("scorersTable");
scorersTable->setHorizontalHeaderLabels({"Photo", "Player", "Goals"});
scorersTable->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Fixed);
scorersTable->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
scorersTable->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Fixed);
scorersTable->setColumnWidth(0, 50);
scorersTable->setColumnWidth(2, 60);
scorersTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
scorersTable->setSelectionBehavior(QAbstractItemView::SelectRows);
scorersTable->setAlternatingRowColors(false);
scorersTable->verticalHeader()->setVisible(false);
scorersTable->verticalHeader()->setDefaultSectionSize(50); // Hauteur des lignes
scorersLayout->addWidget(scorersTable);
tablesLayout->addWidget(topScorersGroup);

// Tableau des meilleurs passeurs
QGroupBox *topAssistsGroup = new QGroupBox("Top Assists");
topAssistsGroup->setStyleSheet("QGroupBox { font-weight: bold; }");
QVBoxLayout *assistsLayout = new QVBoxLayout(topAssistsGroup);
QTableWidget *assistsTable = new QTableWidget(0, 3); // 3 colonnes au lieu de 2
assistsTable->setObjectName("assistsTable");
assistsTable->setHorizontalHeaderLabels({"Photo", "Player", "Assists"});
assistsTable->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Fixed);
assistsTable->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
assistsTable->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Fixed);
assistsTable->setColumnWidth(0, 50);
assistsTable->setColumnWidth(2, 60);
assistsTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
assistsTable->setSelectionBehavior(QAbstractItemView::SelectRows);
assistsTable->setAlternatingRowColors(false);
assistsTable->verticalHeader()->setVisible(false);
assistsTable->verticalHeader()->setDefaultSectionSize(50); // Hauteur des lignes
assistsLayout->addWidget(assistsTable);
tablesLayout->addWidget(topAssistsGroup);

    // Tableau des joueurs par position
    QGroupBox *positionsGroup = new QGroupBox("Players by Position");
    positionsGroup->setStyleSheet("QGroupBox { font-weight: bold; }");
    QVBoxLayout *positionsLayout = new QVBoxLayout(positionsGroup);
    QTableWidget *positionsTable = new QTableWidget(0, 2);
    positionsTable->setObjectName("positionsTable");
    positionsTable->setHorizontalHeaderLabels({"Position", "Count"});
    positionsTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    positionsTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    positionsTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    positionsTable->setAlternatingRowColors(false);
    positionsTable->verticalHeader()->setVisible(false);
    positionsLayout->addWidget(positionsTable);
    tablesLayout->addWidget(positionsGroup);

    mainLayout->addLayout(tablesLayout);

    // Ajouter un filtre d'équipe
    QHBoxLayout *filterLayout = new QHBoxLayout();
    QLabel *filterLabel = new QLabel("Filter by team:");
    QComboBox *teamFilterComboBox = new QComboBox();
    teamFilterComboBox->setObjectName("teamFilterComboBox");
    teamFilterComboBox->addItem("All Teams", "all");

    // Remplir avec les équipes disponibles
    QSqlQuery teamsQuery("SELECT team_name FROM equipe ORDER BY team_name");
    while (teamsQuery.next()) {
        QString teamName = teamsQuery.value(0).toString();
        teamFilterComboBox->addItem(teamName, teamName);
    }

    filterLayout->addWidget(filterLabel);
    filterLayout->addWidget(teamFilterComboBox);
    filterLayout->addStretch();

    // Connexion du changement de filtre
    connect(teamFilterComboBox, &QComboBox::currentIndexChanged, this, &MainWindow::refreshStatistics);

    mainLayout->addLayout(filterLayout);

    // Bouton de rafraîchissement
    QPushButton *refreshBtn = new QPushButton("Refresh Statistics");
    refreshBtn->setStyleSheet("QPushButton { background-color: #4a86e8; color: white; padding: 8px; border-radius: 4px; }"
                             "QPushButton:hover { background-color: #3a76d8; }");
    mainLayout->addWidget(refreshBtn);

    // Ajouter l'onglet
    ui->tabWidget->addTab(statTab, "Statistics");

    // Connexion du signal pour rafraîchir les statistiques
    connect(refreshBtn, &QPushButton::clicked, this, &MainWindow::refreshStatistics);

    // Initialiser les statistiques
    refreshStatistics();
}

void MainWindow::refreshStatistics()
{
    // Obtenir le filtre d'équipe sélectionné
    QComboBox *teamFilterComboBox = ui->tabWidget->findChild<QComboBox*>("teamFilterComboBox");
    QString teamFilter = "all";
    if (teamFilterComboBox) {
        teamFilter = teamFilterComboBox->currentData().toString();
    }

    // Modifier la requête SQL pour inclure les images des joueurs
    QString queryStr = "SELECT j.id_player, j.first_name, j.last_name, j.position, "
                      "e.team_name, j.jersey_nb, j.status, j.goals, j.assists, j.yellow_card, j.red_card, j.img_joueur "
                      "FROM joueur j "
                      "JOIN equipe e ON j.id_team = e.id_team";

    if (teamFilter != "all") {
        queryStr += " WHERE e.team_name = :team_name";
    }

    QSqlQuery query;
    query.prepare(queryStr);

    if (teamFilter != "all") {
        query.bindValue(":team_name", teamFilter);
    }

    if (!query.exec()) {
        qDebug() << "Erreur de requête:" << query.lastError().text();
        return;
    }

    // Structures pour stocker les statistiques avec les images
    struct PlayerStat {
        QString name;
        int value;
        QByteArray imageData;
    };
    QList<PlayerStat> scorersList;
    QList<PlayerStat> assistsList;
    QMap<QString, int> positionMap;
    int totalYellowCards = 0;
    int totalRedCards = 0;
    int playerCount = 0;

    // Parcourir les résultats pour extraire les statistiques
    while (query.next()) {
        playerCount++;

        // Information du joueur
        QString firstName = query.value("first_name").toString();
        QString lastName = query.value("last_name").toString();
        QString fullName = firstName + " " + lastName;
        QString position = query.value("position").toString();
        QByteArray imageData = query.value("img_joueur").toByteArray();

        // Stats
        int goals = query.value("goals").toInt();
        int assists = query.value("assists").toInt();
        int yellowCards = query.value("yellow_card").toInt();
        int redCards = query.value("red_card").toInt();

        // Ajouter aux listes avec les images
        if (goals > 0) {
            PlayerStat scorer;
            scorer.name = fullName;
            scorer.value = goals;
            scorer.imageData = imageData;
            scorersList.append(scorer);
        }

        if (assists > 0) {
            PlayerStat assister;
            assister.name = fullName;
            assister.value = assists;
            assister.imageData = imageData;
            assistsList.append(assister);
        }

        // Ajouter à la carte des positions
        if (positionMap.contains(position)) {
            positionMap[position]++;
        } else {
            positionMap[position] = 1;
        }

        // Cumuler les cartons
        totalYellowCards += yellowCards;
        totalRedCards += redCards;
    }

    // Trier les joueurs par buts (du plus au moins)
    std::sort(scorersList.begin(), scorersList.end(),
              [](const PlayerStat& a, const PlayerStat& b) {
                  return a.value > b.value;
              });

    // Trier les joueurs par passes (du plus au moins)
    std::sort(assistsList.begin(), assistsList.end(),
              [](const PlayerStat& a, const PlayerStat& b) {
                  return a.value > b.value;
              });

    // Limiter les listes aux 10 premiers
    while (scorersList.size() > 10) scorersList.removeLast();
    while (assistsList.size() > 10) assistsList.removeLast();

    // 1. Meilleurs buteurs
    QTableWidget *scorersTable = ui->tabWidget->findChild<QTableWidget*>("scorersTable");
    if (scorersTable) {
        // Mettre à jour les colonnes pour inclure les photos
        scorersTable->setColumnCount(3);
        scorersTable->setHorizontalHeaderLabels({"Photo", "Player", "Goals"});
        scorersTable->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Fixed);
        scorersTable->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
        scorersTable->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Fixed);
        scorersTable->setColumnWidth(0, 50);
        scorersTable->setColumnWidth(2, 60);

        scorersTable->clearContents();
        scorersTable->setRowCount(scorersList.size());
        scorersTable->verticalHeader()->setDefaultSectionSize(50); // Hauteur des lignes

        for (int i = 0; i < scorersList.size(); i++) {
            // Image du joueur
            QTableWidgetItem *photoItem = new QTableWidgetItem();
            if (!scorersList[i].imageData.isEmpty()) {
                QPixmap pixmap;
                pixmap.loadFromData(scorersList[i].imageData);
                photoItem->setData(Qt::DecorationRole, pixmap.scaled(40, 40, Qt::KeepAspectRatio, Qt::SmoothTransformation));
            }

            QTableWidgetItem *nameItem = new QTableWidgetItem(scorersList[i].name);
            QTableWidgetItem *goalsItem = new QTableWidgetItem(QString::number(scorersList[i].value));
            goalsItem->setTextAlignment(Qt::AlignCenter);

            scorersTable->setItem(i, 0, photoItem);
            scorersTable->setItem(i, 1, nameItem);
            scorersTable->setItem(i, 2, goalsItem);

            // Appliquer les couleurs UNIQUEMENT aux 3 premiers
            if (i < 3) {
                QColor color;
                switch (i) {
                    case 0: color = QColor(255, 215, 0, 100); break; // Or
                    case 1: color = QColor(192, 192, 192, 150); break; // Argent
                    case 2: color = QColor(205, 127, 50, 100); break; // Bronze
                }
                photoItem->setBackground(color);
                nameItem->setBackground(color);
                goalsItem->setBackground(color);
            }
        }
    }

    // 2. Meilleurs passeurs
    QTableWidget *assistsTable = ui->tabWidget->findChild<QTableWidget*>("assistsTable");
    if (assistsTable) {
        // Mettre à jour les colonnes pour inclure les photos
        assistsTable->setColumnCount(3);
        assistsTable->setHorizontalHeaderLabels({"Photo", "Player", "Assists"});
        assistsTable->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Fixed);
        assistsTable->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
        assistsTable->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Fixed);
        assistsTable->setColumnWidth(0, 50);
        assistsTable->setColumnWidth(2, 60);

        assistsTable->clearContents();
        assistsTable->setRowCount(assistsList.size());
        assistsTable->verticalHeader()->setDefaultSectionSize(50); // Hauteur des lignes

        for (int i = 0; i < assistsList.size(); i++) {
            // Image du joueur
            QTableWidgetItem *photoItem = new QTableWidgetItem();
            if (!assistsList[i].imageData.isEmpty()) {
                QPixmap pixmap;
                pixmap.loadFromData(assistsList[i].imageData);
                photoItem->setData(Qt::DecorationRole, pixmap.scaled(40, 40, Qt::KeepAspectRatio, Qt::SmoothTransformation));
            }

            QTableWidgetItem *nameItem = new QTableWidgetItem(assistsList[i].name);
            QTableWidgetItem *assistsItem = new QTableWidgetItem(QString::number(assistsList[i].value));
            assistsItem->setTextAlignment(Qt::AlignCenter);

            assistsTable->setItem(i, 0, photoItem);
            assistsTable->setItem(i, 1, nameItem);
            assistsTable->setItem(i, 2, assistsItem);

            // Appliquer les couleurs UNIQUEMENT aux 3 premiers
            if (i < 3) {
                QColor color;
                switch (i) {
                    case 0: color = QColor(255, 215, 0, 100); break; // Or
                    case 1: color = QColor(192, 192, 192, 100); break; // Argent
                    case 2: color = QColor(205, 127, 50, 100); break; // Bronze
                }
                photoItem->setBackground(color);
                nameItem->setBackground(color);
                assistsItem->setBackground(color);
            }
        }
    }

    // 3. Joueurs par position
    QTableWidget *positionsTable = ui->tabWidget->findChild<QTableWidget*>("positionsTable");
    if (positionsTable) {
        positionsTable->clearContents();
        positionsTable->setRowCount(positionMap.size());

        int row = 0;
        QMapIterator<QString, int> i(positionMap);
        while (i.hasNext()) {
            i.next();

            QTableWidgetItem *posItem = new QTableWidgetItem(i.key());
            QTableWidgetItem *countItem = new QTableWidgetItem(QString::number(i.value()));
            countItem->setTextAlignment(Qt::AlignCenter);

            positionsTable->setItem(row, 0, posItem);
            positionsTable->setItem(row, 1, countItem);

            // Couleurs différentes selon la position
            QColor color;
            if (i.key() == "Goalkeeper") {
                color = QColor(255, 255, 150, 80);
            } else if (i.key() == "Defender") {
                color = QColor(150, 150, 255, 80);
            } else if (i.key() == "Midfielder") {
                color = QColor(150, 255, 150, 80);
            } else if (i.key() == "Forward") {
                color = QColor(255, 150, 150, 80);
            }

            posItem->setBackground(color);
            countItem->setBackground(color);

            row++;
        }
    }

    // 4. Mise à jour des cartes de statistiques
    QList<QFrame*> cards = ui->tabWidget->findChildren<QFrame*>();
    for (QFrame* card : cards) {
        QList<QLabel*> labels = card->findChildren<QLabel*>();
        if (labels.size() == 2) {
            QString title = labels[1]->text();
            QLabel* valueLabel = labels[0];

            if (title == "Joueurs Total") {
                valueLabel->setText(QString::number(playerCount));
            } else if (title == "Cartons Jaunes") {
                valueLabel->setText(QString::number(totalYellowCards));
            } else if (title == "Cartons Rouges") {
                valueLabel->setText(QString::number(totalRedCards));
            }
        }
    }
}

QPixmap MainWindow::generateQRCode(const QString &text)
{
    using namespace qrcodegen;

    // Générer le QR code
    QrCode qr = QrCode::encodeText(text.toUtf8().constData(), QrCode::Ecc::MEDIUM);

    // Taille du QR code (nombre de modules)
    int size = qr.getSize();
    int scale = 10;  // Échelle pour agrandir l'image (10 pixels par module)
    int border = 4;  // Bordure autour du QR code (en modules)
    int imgSize = (size + 2 * border) * scale;

    // Créer une image QPixmap
    QPixmap pixmap(imgSize, imgSize);
    pixmap.fill(Qt::white);  // Fond blanc

    QPainter painter(&pixmap);
    painter.setPen(Qt::NoPen);
    painter.setBrush(Qt::black);  // Couleur des modules noirs

    // Dessiner les modules du QR code
    for (int y = 0; y < size; y++) {
        for (int x = 0; x < size; x++) {
            if (qr.getModule(x, y)) {
                painter.drawRect((x + border) * scale, (y + border) * scale, scale, scale);
            }
        }
    }

    painter.end();
    return pixmap;
}
void MainWindow::refreshBestPlayer()
{
    qDebug() << "Refreshing Best Player info...";
    
    if (!comboBoxCompetition) {
        qDebug() << "comboBoxCompetition is null";
        return;
    }
    
    // Récupérer la compétition sélectionnée
    QString competitionName = comboBoxCompetition->currentText();
    qDebug() << "Competition selected:" << competitionName;
    
    // Requête SQL avec ROWNUM pour Oracle
    QString queryStr = "SELECT * FROM ("
                      "SELECT j.id_player, j.first_name, j.last_name, j.position, "
                      "e.team_name, j.goals, j.assists, j.img_joueur, c.comp_name "
                      "FROM joueur j "
                      "JOIN equipe e ON j.id_team = e.id_team "
                      "JOIN participation p ON e.id_team = p.id_team "
                      "JOIN competition c ON p.id_competition = c.id_competition "
                      "WHERE c.comp_name = :competition_name "
                      "ORDER BY (j.goals * 2 + j.assists) DESC"
                      ") WHERE ROWNUM <= 1";
    
    QSqlQuery query;
    query.prepare(queryStr);
    query.bindValue(":competition_name", competitionName);
    
    if (!query.exec()) {
        qDebug() << "Erreur de requête :" << query.lastError().text();
        return;
    }
    
    // Récupérer les widgets de l'interface
    QLabel *playerNameLabel = ui->tabWidget->findChild<QLabel*>("playerNameLabel");
    QLabel *playerTeamLabel = ui->tabWidget->findChild<QLabel*>("playerTeamLabel");
    QLabel *playerStatsLabel = ui->tabWidget->findChild<QLabel*>("playerStatsLabel");
    QLabel *playerImageLabel = ui->tabWidget->findChild<QLabel*>("playerImageLabel");
    QFrame *playerCard = ui->tabWidget->findChild<QFrame*>("playerCard");
    
    // Animation de transition
    if (playerCard) {
        QGraphicsOpacityEffect *effect = new QGraphicsOpacityEffect(playerCard);
        playerCard->setGraphicsEffect(effect);
        QPropertyAnimation *animation = new QPropertyAnimation(effect, "opacity");
        animation->setDuration(500);
        animation->setStartValue(1);
        animation->setEndValue(0.3);
        animation->start();
        
        // Connecter la fin de l'animation pour rafraîchir les données
        QObject::connect(animation, &QPropertyAnimation::finished, [=]() {
            // Suite du traitement après l'animation
            updatePlayerInfo(query, playerNameLabel, playerTeamLabel, playerStatsLabel, playerImageLabel);
            
            // Animation de retour
            QGraphicsOpacityEffect *returnEffect = new QGraphicsOpacityEffect(playerCard);
            playerCard->setGraphicsEffect(returnEffect);
            QPropertyAnimation *returnAnimation = new QPropertyAnimation(returnEffect, "opacity");
            returnAnimation->setDuration(500);
            returnAnimation->setStartValue(0.3);
            returnAnimation->setEndValue(1);
            returnAnimation->setEasingCurve(QEasingCurve::OutCubic);
            returnAnimation->start(QAbstractAnimation::DeleteWhenStopped);
        });
    } else {
        // Si pas d'animation, mettre à jour directement
        updatePlayerInfo(query, playerNameLabel, playerTeamLabel, playerStatsLabel, playerImageLabel);
    }
}

// Nouvelle méthode pour mettre à jour les informations du joueur
void MainWindow::updatePlayerInfo(QSqlQuery query, QLabel *nameLabel, QLabel *teamLabel, QLabel *statsLabel, QLabel *imageLabel)
{
        Q_UNUSED(query);
    
    if (!nameLabel || !teamLabel || !statsLabel || !imageLabel) {
        qDebug() << "Labels not found in interface";
        return;
    }
    
    // Au lieu de copier l'objet QSqlQuery, nous allons exécuter une nouvelle requête avec les mêmes paramètres
    QSqlQuery freshQuery;
    // Récupérer la compétition depuis le combobox
    QString competitionName = comboBoxCompetition->currentText();
    
    QString queryStr = "SELECT * FROM ("
                      "SELECT j.id_player, j.first_name, j.last_name, j.position, "
                      "e.team_name, j.goals, j.assists, j.img_joueur, c.comp_name "
                      "FROM joueur j "
                      "JOIN equipe e ON j.id_team = e.id_team "
                      "JOIN participation p ON e.id_team = p.id_team "
                      "JOIN competition c ON p.id_competition = c.id_competition "
                      "WHERE c.comp_name = :competition_name "
                      "ORDER BY (j.goals * 2 + j.assists) DESC"
                      ") WHERE ROWNUM <= 1";
    
    freshQuery.prepare(queryStr);
    freshQuery.bindValue(":competition_name", competitionName);
    
    if (!freshQuery.exec()) {
        qDebug() << "Erreur lors de la requête:" << freshQuery.lastError().text();
        return;
    }
    
    if (freshQuery.next()) {
        // Récupérer les informations du meilleur joueur avec un style amélioré
        QString firstName = freshQuery.value("first_name").toString();
        QString lastName = freshQuery.value("last_name").toString();
        QString fullName = firstName + " " + lastName;
        QString teamName = freshQuery.value("team_name").toString();
        QString position = freshQuery.value("position").toString();
        int goals = freshQuery.value("goals").toInt();
        int assists = freshQuery.value("assists").toInt();
        QByteArray imageData = freshQuery.value("img_joueur").toByteArray();
        
        qDebug() << "Joueur trouvé :" << firstName << lastName 
                << " - Team:" << teamName
                << " - Goals:" << goals
                << " - Assists:" << assists;
        
        // *** CORRECTION - S'assurer que le texte est visible et bien positionné ***
        // Rendre le texte visible avec un fond opaque
        nameLabel->setStyleSheet(
            "color: white;"
            "font-size: 28px;"
            "font-weight: bold;"
            "padding: 5px;"
            "background-color: transparent;" // Fond transparent pour voir le texte
        );
        
        // Mettre à jour le nom du joueur avec un style plus visible
        nameLabel->setText(fullName.toUpper());
        
        // Style plus visible pour l'équipe et la position
        teamLabel->setStyleSheet(
            "color: #3498db;"
            "font-size: 18px;"
            "font-weight: bold;"
            "background-color: rgba(45, 52, 54, 0.7);" // Fond semi-transparent
            "border-radius: 5px;"
            "padding: 3px 10px;"
        );
        
        teamLabel->setText(position + " | " + teamName);
        
        // Statistiques avec un design plus visible
        statsLabel->setStyleSheet(
            "color: white;"
            "font-size: 18px;"
            "background-color: rgba(0, 0, 0, 0.7);" // Fond noir semi-transparent
            "border-radius: 10px;"
            "padding: 15px;"
            "margin: 0px 30px;"
        );
        
        QString statsHtml = QString(
            "<table width='100%' cellspacing='10'>"
            "  <tr>"
            "    <td align='center' width='50%' style='border-right: 1px solid rgba(255,255,255,0.4);'>"
            "      <div style='font-size: 36px; color: #f9ca24; font-weight: bold;'>%1</div>"
            "      <div style='font-size: 14px; color: white; margin-top: 5px;'>GOALS</div>"
            "    </td>"
            "    <td align='center' width='50%'>"
            "      <div style='font-size: 36px; color: #2ecc71; font-weight: bold;'>%2</div>"
            "      <div style='font-size: 14px; color: white; margin-top: 5px;'>ASSISTS</div>"
            "    </td>"
            "  </tr>"
            "</table>"
        ).arg(goals).arg(assists);
        
        statsLabel->setText(statsHtml);
        
        // Image du joueur dans un cadre circulaire avec effet brillant
        if (!imageData.isEmpty()) {
            QPixmap originalPixmap;
            originalPixmap.loadFromData(imageData);
            
            // Créer une version circulaire de l'image avec un effet de bordure brillante
            QPixmap circularPixmap(180, 180);
            circularPixmap.fill(Qt::transparent);
            
            QPainter painter(&circularPixmap);
            painter.setRenderHint(QPainter::Antialiasing, true);
            painter.setRenderHint(QPainter::SmoothPixmapTransform, true);
            
            // Dessiner un cercle brillant comme fond
            QRadialGradient gradient(90, 90, 95);
            gradient.setColorAt(0, QColor(255, 215, 0, 180)); // Or à l'intérieur
            gradient.setColorAt(1, QColor(243, 156, 18, 240)); // Orange à l'extérieur
            
            painter.setBrush(gradient);
            painter.setPen(Qt::NoPen);
            painter.drawEllipse(0, 0, 180, 180);
            
            // Dessiner l'image en forme de cercle
            QPainterPath path;
            path.addEllipse(5, 5, 170, 170);  // Un peu plus petit pour avoir une bordure
            painter.setClipPath(path);
            
            // Redimensionner et centrer l'image
            QPixmap scaledPixmap = originalPixmap.scaled(170, 170, Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);
            
            // Centrer l'image
            int x = scaledPixmap.width() > 170 ? (scaledPixmap.width() - 170) / 2 : 0;
            int y = scaledPixmap.height() > 170 ? (scaledPixmap.height() - 170) / 2 : 0;
            
            painter.drawPixmap(5, 5, scaledPixmap, x, y, 170, 170);
            painter.end();
            
            imageLabel->setPixmap(circularPixmap);
            imageLabel->setStyleSheet("background: transparent;"); // Effacer le style précédent
        } else {
            // Image par défaut si pas de photo avec un effet spécial
            QPixmap defaultPixmap(180, 180);
            defaultPixmap.fill(Qt::transparent);
            
            QPainter painter(&defaultPixmap);
            painter.setRenderHint(QPainter::Antialiasing, true);
            
            // Dessiner un fond circulaire dégradé
            QRadialGradient gradient(90, 90, 90);
            gradient.setColorAt(0, QColor(41, 128, 185, 200));  // Bleu clair au centre
            gradient.setColorAt(1, QColor(44, 62, 80, 200));    // Bleu foncé à l'extérieur
            
            painter.setBrush(gradient);
            painter.setPen(QPen(Qt::white, 2));
            painter.drawEllipse(5, 5, 170, 170);
            
            // Dessiner les initiales du joueur
            painter.setPen(Qt::white);
            QFont font = painter.font();
            font.setPointSize(40);
            font.setBold(true);
            painter.setFont(font);
            
            QString initials;
            if (!firstName.isEmpty() && !lastName.isEmpty()) {
                initials = QString(firstName[0]) + QString(lastName[0]);
            } else {
                initials = "?";
            }
            
            painter.drawText(QRect(0, 0, 180, 180), Qt::AlignCenter, initials);
            painter.end();
            
            imageLabel->setPixmap(defaultPixmap);
            imageLabel->setStyleSheet("background: transparent;"); // Effacer le style précédent
        }
    } else {
        // Cas où aucun joueur n'est trouvé
        // Code similaire à ce que vous aviez déjà, avec quelques améliorations visuelles
        qDebug() << "Aucun joueur trouvé pour cette compétition";
        
        nameLabel->setStyleSheet(
            "color: #e74c3c;"
            "font-size: 28px;"
            "font-weight: bold;"
            "text-shadow: 1px 1px 2px #000;"
            "padding: 5px;"
            "background-color: transparent;"
        );
        nameLabel->setText("NO PLAYER FOUND");
        
        teamLabel->setStyleSheet(
            "color: #bdc3c7;"
            "font-size: 18px;"
            "background-color: rgba(45, 52, 54, 0.7);"
            "border-radius: 5px;"
            "padding: 3px 10px;"
        );
        teamLabel->setText("Competition: " + competitionName);
        
        statsLabel->setStyleSheet(
            "color: #bdc3c7;"
            "font-size: 18px;"
            "background-color: rgba(0, 0, 0, 0.7);"
            "border-radius: 10px;"
            "padding: 15px;"
            "margin: 0px 30px;"
        );
        
        statsLabel->setText("No statistics available for this competition");
        
        // Image par défaut plus attrayante
        QPixmap defaultPixmap(180, 180);
        defaultPixmap.fill(Qt::transparent);
        
        QPainter painter(&defaultPixmap);
        painter.setRenderHint(QPainter::Antialiasing, true);
        
        // Fond dégradé
        QRadialGradient gradient(90, 90, 90);
        gradient.setColorAt(0, QColor(192, 57, 43, 200));  // Rouge au centre
        gradient.setColorAt(1, QColor(74, 35, 90, 200));   // Violet à l'extérieur
        
        painter.setBrush(gradient);
        painter.setPen(QPen(Qt::white, 2));
        painter.drawEllipse(5, 5, 170, 170);
        
        // Point d'interrogation
        painter.setPen(Qt::white);
        QFont font = painter.font();
        font.setPointSize(70);
        font.setBold(true);
        painter.setFont(font);
        painter.drawText(QRect(0, 0, 180, 180), Qt::AlignCenter, "?");
        painter.end();
        
        imageLabel->setPixmap(defaultPixmap);
        imageLabel->setStyleSheet("background: transparent;"); // Effacer le style précédent
    }
}
void MainWindow::setupBestPlayerTab()
{
    qDebug() << "Setting up Best Player tab...";
    
    // Créer un nouvel onglet avec un fond dégradé
    QWidget *bestPlayerTab = new QWidget();
    bestPlayerTab->setStyleSheet("background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 #0f2027, stop:0.5 #203a43, stop:1 #2c5364);");
    
    // Utiliser un GridLayout pour un meilleur contrôle du positionnement
    QGridLayout *mainLayout = new QGridLayout(bestPlayerTab);
    mainLayout->setSpacing(20);
    mainLayout->setContentsMargins(30, 30, 30, 30);

    // En-tête avec effet brillant - Rangée 0
    QLabel *titleLabel = new QLabel("⭐ STAR PLAYER ⭐");
    QFont titleFont("Segoe UI", 28, QFont::Bold);
    titleLabel->setFont(titleFont);
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setStyleSheet(
        "color: #f5f5f5; "
        "text-shadow: 2px 2px 4px #000000; "
        "padding: 15px; "
        "background: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 #141e30, stop:1 #243b55); "
        "border-radius: 15px;"
    );
    mainLayout->addWidget(titleLabel, 0, 0, 1, 2); // Rangée 0, Colonne 0, span 1 ligne, 2 colonnes

    // Sélecteur de compétition - Rangée 1
    QFrame *selectorFrame = new QFrame();
    selectorFrame->setStyleSheet(
        "background-color: rgba(255, 255, 255, 0.1); "
        "border-radius: 15px; "
        "padding: 15px;"
    );
    QHBoxLayout *selectorLayout = new QHBoxLayout(selectorFrame);
    
    QLabel *competitionLabel = new QLabel("SELECT COMPETITION");
    competitionLabel->setStyleSheet("color: #f5f5f5; font-size: 16px; font-weight: bold; background: transparent;");
    
    // ComboBox stylisé
    comboBoxCompetition = new QComboBox();
    comboBoxCompetition->setObjectName("comboBoxCompetition");
    comboBoxCompetition->setStyleSheet(
        "QComboBox {"
        "   background-color: rgba(255, 255, 255, 0.2);"
        "   color: white;"
        "   padding: 8px 15px;"
        "   border: 1px solid rgba(255, 255, 255, 0.3);"
        "   border-radius: 8px;"
        "   font-size: 15px;"
        "   min-height: 30px;"
        "}"
        "QComboBox::drop-down {"
        "   subcontrol-origin: padding;"
        "   subcontrol-position: right;"
        "   width: 30px;"
        "   border-left-width: 1px;"
        "   border-left-color: rgba(255, 255, 255, 0.3);"
        "   border-top-right-radius: 8px;"
        "   border-bottom-right-radius: 8px;"
        "}"
        "QComboBox QAbstractItemView {"
        "   background-color: #243b55;"
        "   border: 1px solid rgba(255, 255, 255, 0.3);"
        "   color: white;"
        "   selection-background-color: #3498db;"
        "}"
    );

    // Remplir le ComboBox avec les compétitions disponibles
    QSqlQuery competitionQuery("SELECT comp_name FROM competition");
    while (competitionQuery.next()) {
        QString compName = competitionQuery.value(0).toString();
        comboBoxCompetition->addItem(compName);
    }

    // Bouton de rafraîchissement
    QPushButton *refreshButton = new QPushButton("Refresh");
    refreshButton->setCursor(Qt::PointingHandCursor);
    refreshButton->setStyleSheet(
        "QPushButton {"
        "   background-color: #3498db;"
        "   color: white;"
        "   border-radius: 8px;"
        "   font-size: 14px;"
        "   font-weight: bold;"
        "   border: none;"
        "   padding: 8px 15px;"
        "}"
        "QPushButton:hover {"
        "   background-color: #2980b9;"
        "}"
        "QPushButton:pressed {"
        "   background-color: #1c5a85;"
        "}"
    );
    connect(refreshButton, &QPushButton::clicked, this, &MainWindow::refreshBestPlayer);

    selectorLayout->addWidget(competitionLabel);
    selectorLayout->addWidget(comboBoxCompetition, 1);
    selectorLayout->addWidget(refreshButton);
    
    mainLayout->addWidget(selectorFrame, 1, 0, 1, 2); // Rangée 1, Colonne 0, span 1 ligne, 2 colonnes

    // Zone d'image du joueur - Rangée 2, Colonne 0
    QFrame *imageFrame = new QFrame();
    imageFrame->setFixedSize(250, 300);
    imageFrame->setStyleSheet(
        "background-color: rgba(45, 52, 54, 0.5);"
        "border-radius: 15px;"
        "border: 1px solid rgba(255, 255, 255, 0.2);"
    );
    QVBoxLayout *imageLayout = new QVBoxLayout(imageFrame);
    imageLayout->setAlignment(Qt::AlignCenter);
    
    // Badge MVP
    QLabel *badgeLabel = new QLabel("MVP");
    badgeLabel->setAlignment(Qt::AlignCenter);
    badgeLabel->setFixedSize(60, 60);
    badgeLabel->setStyleSheet(
        "background: qradialgradient(cx:0.5, cy:0.5, radius: 0.5, fx:0.5, fy:0.5, stop:0 #f9ca24, stop:1 #f0932b);"
        "color: #2d3436;"
        "font-size: 18px;"
        "font-weight: bold;"
        "border-radius: 30px;"
        "border: 3px solid #f0932b;"
        "margin-bottom: 5px;"
    );
    imageLayout->addWidget(badgeLabel, 0, Qt::AlignHCenter);
    
    // Image du joueur
    QLabel *playerImageLabel = new QLabel();
    playerImageLabel->setObjectName("playerImageLabel");
    playerImageLabel->setFixedSize(180, 180);
    playerImageLabel->setAlignment(Qt::AlignCenter);
    playerImageLabel->setStyleSheet(
        "background-color: rgba(52, 152, 219, 0.3);"
        "border-radius: 90px;"
        "color: white;"
        "font-size: 36px;"
        "font-weight: bold;"
        "border: 5px solid qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 #f9ca24, stop:1 #f0932b);"
    );
    playerImageLabel->setText("?");
    imageLayout->addWidget(playerImageLabel, 0, Qt::AlignCenter);
    
    mainLayout->addWidget(imageFrame, 2, 0); // Rangée 2, Colonne 0

    // Informations du joueur - Rangée 2, Colonne 1
    QFrame *infoFrame = new QFrame();
    infoFrame->setStyleSheet(
        "background-color: rgba(45, 52, 54, 0.5);"
        "border-radius: 15px;"
        "border: 1px solid rgba(255, 255, 255, 0.2);"
        "padding: 15px;"
    );
    QVBoxLayout *infoLayout = new QVBoxLayout(infoFrame);
    infoLayout->setSpacing(20);
    
    // Nom du joueur
    QLabel *playerNameLabel = new QLabel("Select a competition");
    playerNameLabel->setObjectName("playerNameLabel");
    playerNameLabel->setAlignment(Qt::AlignCenter);
    playerNameLabel->setStyleSheet(
        "color: white;"
        "font-size: 24px;"
        "font-weight: bold;"
        "background-color: rgba(0, 0, 0, 0.3);"
        "border-radius: 10px;"
        "padding: 10px;"
    );
    infoLayout->addWidget(playerNameLabel);
    
    // Équipe du joueur
    QLabel *playerTeamLabel = new QLabel("");
    playerTeamLabel->setObjectName("playerTeamLabel");
    playerTeamLabel->setAlignment(Qt::AlignCenter);
    playerTeamLabel->setStyleSheet(
        "color: #3498db;"
        "font-size: 16px;"
        "font-weight: bold;"
        "background-color: rgba(0, 0, 0, 0.3);"
        "border-radius: 8px;"
        "padding: 8px;"
    );
    infoLayout->addWidget(playerTeamLabel);
    
    // Statistiques
    QLabel *playerStatsLabel = new QLabel("");
    playerStatsLabel->setObjectName("playerStatsLabel");
    playerStatsLabel->setAlignment(Qt::AlignCenter);
    playerStatsLabel->setTextFormat(Qt::RichText);
    playerStatsLabel->setStyleSheet(
        "color: white;"
        "font-size: 16px;"
        "background-color: rgba(0, 0, 0, 0.5);"
        "border-radius: 10px;"
        "padding: 15px;"
    );
    playerStatsLabel->setMinimumHeight(100);
    infoLayout->addWidget(playerStatsLabel);
    
    // Ajouter un espacement
    infoLayout->addStretch();
    
    mainLayout->addWidget(infoFrame, 2, 1); // Rangée 2, Colonne 1
    
    // Ajouter l'onglet à l'interface
    ui->tabWidget->addTab(bestPlayerTab, "Star Player");
    
    // Connecter le combobox pour mettre à jour les données quand la sélection change
    connect(comboBoxCompetition, QOverload<int>::of(&QComboBox::currentIndexChanged), 
            this, &MainWindow::refreshBestPlayer);
    
    // Utiliser QTimer pour charger les données après que l'interface soit affichée
    QTimer::singleShot(500, this, &MainWindow::refreshBestPlayer);


    // Rafraîchir les informations du meilleur joueur
    refreshBestPlayer();
}
void MainWindow::setupTeamOfCompetitionTab()
{
    QWidget *teamOfCompTab = new QWidget();
    teamOfCompTab->setStyleSheet(
        "background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 #0f0c29, stop:0.5 #302b63, stop:1 #24243e);"
        );

    QGridLayout *mainLayout = new QGridLayout(teamOfCompTab);
    mainLayout->setSpacing(10);
    mainLayout->setContentsMargins(20, 20, 20, 20);

    // Titre de l'onglet
    QLabel *titleLabel = new QLabel("TEAM OF THE COMPETITION");
    QFont titleFont("Segoe UI", 18, QFont::Bold);
    titleLabel->setFont(titleFont);
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setStyleSheet(
        "color: #f5f5f5; padding: 5px; background: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 #141e30, stop:1 #243b55);"
        "border-radius: 5px;"
        );
    mainLayout->addWidget(titleLabel, 0, 0, 1, 2);

    // Sélecteur de compétition
    QHBoxLayout *selectorLayout = new QHBoxLayout();
    QLabel *competitionLabel = new QLabel("Competition:");
    competitionLabel->setStyleSheet("color: #f5f5f5; font-size: 14px;");

    QComboBox *teamCompComboBox = new QComboBox();
    teamCompComboBox->setObjectName("teamCompComboBox");
    teamCompComboBox->setStyleSheet(
        "QComboBox { background-color: rgba(255, 255, 255, 0.2); color: white; padding: 3px 10px; "
        "border: 1px solid rgba(255, 255, 255, 0.3); border-radius: 3px; font-size: 12px; min-height: 20px; }"
        );

    QSqlQuery competitionQuery("SELECT comp_name FROM competition");
    while (competitionQuery.next()) {
        QString compName = competitionQuery.value(0).toString();
        teamCompComboBox->addItem(compName);
    }

    QPushButton *refreshButton = new QPushButton("Show");
    refreshButton->setCursor(Qt::PointingHandCursor);
    refreshButton->setStyleSheet(
        "QPushButton { background-color: #3498db; color: white; border-radius: 3px; font-size: 12px; border: none; padding: 3px 8px; }"
        );

    selectorLayout->addWidget(competitionLabel);
    selectorLayout->addWidget(teamCompComboBox, 1);
    selectorLayout->addWidget(refreshButton);
    mainLayout->addLayout(selectorLayout, 1, 0, 1, 2);

    // Conteneur du terrain
    QFrame *fieldContainer = new QFrame();
    fieldContainer->setObjectName("fieldContainer");
    fieldContainer->setStyleSheet(
        "QFrame#fieldContainer { background-color: rgba(45, 52, 54, 0.5); border-radius: 5px; border: 1px solid rgba(255, 255, 255, 0.2); padding: 5px; }"
        );

    QVBoxLayout *fieldContainerLayout = new QVBoxLayout(fieldContainer);
    fieldContainerLayout->setContentsMargins(5, 5, 5, 5);

    // Zone défilante pour le terrain
    QScrollArea *scrollArea = new QScrollArea();
    scrollArea->setWidgetResizable(true);
    scrollArea->setFrameShape(QFrame::NoFrame);
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    scrollArea->setStyleSheet(
        "QScrollArea { background: transparent; border: none; }"
        "QScrollBar:vertical { width: 8px; background: rgba(0, 0, 0, 0.2); }"
        "QScrollBar:horizontal { height: 8px; background: rgba(0, 0, 0, 0.2); }"
        "QScrollBar::handle:vertical, QScrollBar::handle:horizontal { background: rgba(255, 255, 255, 0.3); border-radius: 4px; }"
        );

    // Terrain de football
    QWidget *footballField = new QWidget();
    footballField->setObjectName("footballField");
    footballField->setMinimumSize(1000, 800);
    footballField->setStyleSheet("border: none;");

    // Fond du terrain avec bandes
    QWidget *terrainBackground = new QWidget(footballField);
    terrainBackground->setObjectName("terrainBackground");
    terrainBackground->setGeometry(0, 0, 1000, 800);
    terrainBackground->lower();
    terrainBackground->installEventFilter(this);

    // Layout du terrain pour les positions des joueurs
    QGridLayout *fieldLayout = new QGridLayout(footballField);
    fieldLayout->setSpacing(40);
    fieldLayout->setContentsMargins(40, 40, 40, 40);

    // IMPORTANT: Création et ajout des widgets de position
    // Gardien
    QFrame *goalkeeperPos = createPositionWidget("GK");
    fieldLayout->addWidget(goalkeeperPos, 12, 2, 1, 1);

    // Défenseurs
    QFrame *defenderPos1 = createPositionWidget("LB");
    fieldLayout->addWidget(defenderPos1, 9, 0, 1, 1);

    QFrame *defenderPos2 = createPositionWidget("CB");
    fieldLayout->addWidget(defenderPos2, 9, 1, 1, 1);

    QFrame *defenderPos3 = createPositionWidget("CB");
    fieldLayout->addWidget(defenderPos3, 9, 3, 1, 1);

    QFrame *defenderPos4 = createPositionWidget("RB");
    fieldLayout->addWidget(defenderPos4, 9, 4, 1, 1);

    // Milieux
    QFrame *midPos1 = createPositionWidget("LM");
    fieldLayout->addWidget(midPos1, 6, 0, 1, 1);

    QFrame *midPos2 = createPositionWidget("CM");
    fieldLayout->addWidget(midPos2, 6, 2, 1, 1);

    QFrame *midPos3 = createPositionWidget("RM");
    fieldLayout->addWidget(midPos3, 6, 4, 1, 1);

    // Attaquants
    QFrame *attPos1 = createPositionWidget("LW");
    fieldLayout->addWidget(attPos1, 3, 0, 1, 1);

    QFrame *attPos2 = createPositionWidget("ST");
    fieldLayout->addWidget(attPos2, 3, 2, 1, 1);

    QFrame *attPos3 = createPositionWidget("RW");
    fieldLayout->addWidget(attPos3, 3, 4, 1, 1);

    scrollArea->setWidget(footballField);
    fieldContainerLayout->addWidget(scrollArea);
    mainLayout->addWidget(fieldContainer, 2, 0, 1, 2);
    mainLayout->setRowStretch(2, 10);

    // Panneau de détails du joueur
    QFrame *playerDetailFrame = new QFrame();
    playerDetailFrame->setObjectName("playerDetailFrame");
    playerDetailFrame->setFixedHeight(100);
    playerDetailFrame->setStyleSheet(
        "background-color: rgba(45, 52, 54, 0.7);"
        "border-radius: 5px;"
        "border: 1px solid rgba(255, 255, 255, 0.2);"
        "padding: 5px;"
    );
    
    QHBoxLayout *playerDetailLayout = new QHBoxLayout(playerDetailFrame);
    playerDetailLayout->setContentsMargins(5, 5, 5, 5);
    
    // Image du joueur
    QLabel *detailImageLabel = new QLabel();
    detailImageLabel->setObjectName("detailImageLabel");
    detailImageLabel->setFixedSize(70, 70);
    detailImageLabel->setAlignment(Qt::AlignCenter);
    detailImageLabel->setStyleSheet(
        "background-color: rgba(52, 152, 219, 0.3);"
        "border-radius: 35px;"
        "color: white;"
        "font-size: 16px;"
        "font-weight: bold;"
        "border: 2px solid white;"
    );
    detailImageLabel->setText("?");
    
    // Informations du joueur
    QVBoxLayout *detailInfoLayout = new QVBoxLayout();
    detailInfoLayout->setSpacing(3);
    
    // Labels des détails du joueur
    QLabel *detailNameLabel = new QLabel("Select a player");
    detailNameLabel->setObjectName("detailNameLabel");
    detailNameLabel->setStyleSheet("color: white; font-size: 14px; font-weight: bold;");
    
    QLabel *detailTeamPosLabel = new QLabel("");
    detailTeamPosLabel->setObjectName("detailTeamPosLabel");
    detailTeamPosLabel->setStyleSheet("color: #3498db; font-size: 12px;");
    
    QLabel *detailStatsLabel = new QLabel("");
    detailStatsLabel->setObjectName("detailStatsLabel");
    detailStatsLabel->setStyleSheet("color: #bdc3c7; font-size: 12px;");
    
    detailInfoLayout->addWidget(detailNameLabel);
    detailInfoLayout->addWidget(detailTeamPosLabel);
    detailInfoLayout->addWidget(detailStatsLabel);
    
    playerDetailLayout->addWidget(detailImageLabel);
    playerDetailLayout->addLayout(detailInfoLayout, 1);
    
    mainLayout->addWidget(playerDetailFrame, 3, 0, 1, 2);

    ui->tabWidget->addTab(teamOfCompTab, "Team of Competition");

    // Connexions pour les actions
    connect(refreshButton, &QPushButton::clicked, [=]() {
        displayTeamOfCompetition(teamCompComboBox->currentText());
    });

    QTimer::singleShot(500, [=]() {
        if (teamCompComboBox->count() > 0) {
            displayTeamOfCompetition(teamCompComboBox->currentText());
        }
    });
}



// Fonction pour créer un widget de position de joueur
QFrame* MainWindow::createPositionWidget(const QString &position)
{
    QFrame *posFrame = new QFrame();
    posFrame->setObjectName("position_" + position);
    posFrame->setFixedSize(80, 80);
    posFrame->setStyleSheet(
        "background-color: rgba(255, 255, 255, 0.3);"
        "border-radius: 40px;"
        "border: 2px solid white;"
    );

    QVBoxLayout *posLayout = new QVBoxLayout(posFrame);
    posLayout->setContentsMargins(5, 5, 5, 5);

    // Image du joueur (à remplir dynamiquement)
    QLabel *playerImage = new QLabel();
    playerImage->setObjectName("image_" + position);
    playerImage->setFixedSize(60, 60);
    playerImage->setAlignment(Qt::AlignCenter);
    playerImage->setStyleSheet(
        "background-color: rgba(52, 152, 219, 0.5);"
        "color: white;"
        "font-weight: bold;"
        "border-radius: 30px;"
        "border: none;"
    );
    playerImage->setText(position);

    posLayout->addWidget(playerImage, 0, Qt::AlignCenter);

    // Stocker l'ID du joueur comme propriété
    posFrame->setProperty("playerId", -1);

    // Connecter le clic pour afficher les détails
    posFrame->setProperty("position", position);
    posFrame->installEventFilter(this);
    posFrame->setCursor(Qt::PointingHandCursor);

    return posFrame;
}

// Implémenter l'événement de clic sur une position
bool MainWindow::eventFilter(QObject *watched, QEvent *event)
{
    // Gestion du dessin du terrain
    if (watched->objectName() == "terrainBackground" && event->type() == QEvent::Paint) {
        QWidget *field = qobject_cast<QWidget *>(watched);
        QPainter painter(field);
        
        // Dessiner les bandes du terrain
        int stripeHeight = 80;
        QColor darkGreen(0, 90, 0);
        QColor lightGreen(50, 180, 50);

        for (int i = 0; i < field->height() / stripeHeight + 1; ++i) {
            QColor color = (i % 2 == 0) ? darkGreen : lightGreen;
            painter.fillRect(0, i * stripeHeight, field->width(), stripeHeight, color);
        }
        
        // Dessiner les lignes du terrain
        painter.setPen(QPen(Qt::white, 3));
        
        // Rectangle du terrain
        painter.drawRect(30, 30, field->width() - 60, field->height() - 60);
        
        // Ligne médiane
        painter.drawLine(30, field->height() / 2, field->width() - 30, field->height() / 2);
        
        // Rond central
        painter.drawEllipse(field->width() / 2 - 75, field->height() / 2 - 75, 150, 150);
        
        // Surfaces de réparation
        int penaltyBoxWidth = 300;
        int penaltyBoxHeight = 150;
        int penaltyBoxX = (field->width() - penaltyBoxWidth) / 2;
        
        // Surface du haut
        painter.drawRect(penaltyBoxX, 30, penaltyBoxWidth, penaltyBoxHeight);
        // Surface du bas
        painter.drawRect(penaltyBoxX, field->height() - penaltyBoxHeight - 30, penaltyBoxWidth, penaltyBoxHeight);
        
        // Surfaces de but
        int goalBoxWidth = 150;
        int goalBoxHeight = 60;
        int goalBoxX = (field->width() - goalBoxWidth) / 2;
        
        painter.drawRect(goalBoxX, 30, goalBoxWidth, goalBoxHeight);
        painter.drawRect(goalBoxX, field->height() - goalBoxHeight - 30, goalBoxWidth, goalBoxHeight);
        
        // Points de penalty
        painter.setBrush(Qt::white);
        painter.drawEllipse(field->width() / 2 - 5, 30 + penaltyBoxHeight / 2 - 5, 10, 10);
        painter.drawEllipse(field->width() / 2 - 5, field->height() - 30 - penaltyBoxHeight / 2 - 5, 10, 10);
        
        // Point central
        painter.drawEllipse(field->width() / 2 - 5, field->height() / 2 - 5, 10, 10);
        
        return true;
    }
    
    // Gestion des clics sur les positions des joueurs
    if (event->type() == QEvent::MouseButtonPress && 
        watched->objectName().startsWith("position_")) {
        
        // Vérification du type d'événement avant conversion
        if (QMouseEvent *mouseEvent = dynamic_cast<QMouseEvent*>(event)) {
            if (mouseEvent->button() == Qt::LeftButton) {
                QFrame *frame = qobject_cast<QFrame*>(watched);
                if (frame) {
                    int playerId = frame->property("playerId").toInt();
                    QString position = frame->property("position").toString();
                    
                    if (playerId > 0) {
                        // Afficher les détails du joueur sélectionné
                        displayPlayerDetails(playerId, position);
                    }
                }
                return true;
            }
        }
    }
    
    return QMainWindow::eventFilter(watched, event);
}


void MainWindow::displayPlayerDetails(int playerId, const QString &position)
{
    QLabel *detailNameLabel = ui->tabWidget->findChild<QLabel*>("detailNameLabel");
    QLabel *detailTeamPosLabel = ui->tabWidget->findChild<QLabel*>("detailTeamPosLabel");
    QLabel *detailStatsLabel = ui->tabWidget->findChild<QLabel*>("detailStatsLabel");
    QLabel *detailImageLabel = ui->tabWidget->findChild<QLabel*>("detailImageLabel");

    if (!detailNameLabel || !detailTeamPosLabel || !detailStatsLabel || !detailImageLabel) {
        qDebug() << "Detail widgets not found";
        return;
    }

    // Requête pour obtenir les détails du joueur
    QSqlQuery query;
    query.prepare(
        "SELECT j.first_name, j.last_name, j.position, e.team_name, j.goals, j.assists, "
        "j.yellow_card, j.red_card, j.img_joueur "
        "FROM joueur j "
        "JOIN equipe e ON j.id_team = e.id_team "
        "WHERE j.id_player = :id"
    );
    query.bindValue(":id", playerId);

    if (query.exec() && query.next()) {
        QString firstName = query.value("first_name").toString();
        QString lastName = query.value("last_name").toString();
        QString playerPosition = query.value("position").toString();
        QString teamName = query.value("team_name").toString();
        int goals = query.value("goals").toInt();
        int assists = query.value("assists").toInt();
        int yellowCards = query.value("yellow_card").toInt();
        int redCards = query.value("red_card").toInt();
        QByteArray imageData = query.value("img_joueur").toByteArray();

        // Mettre à jour les widgets avec les informations du joueur
        detailNameLabel->setText(firstName + " " + lastName);

        // Afficher l'équipe et la position comme avant
        detailTeamPosLabel->setText(teamName + " | " + position + " (" + playerPosition + ")");

        // Statistiques en texte simple pour optimiser l'espace
        QString statsText = QString("Goals: %1  |  Assists: %2  |  YC: %3  |  RC: %4")
            .arg(goals).arg(assists).arg(yellowCards).arg(redCards);

        detailStatsLabel->setText(statsText);
        detailStatsLabel->setTextFormat(Qt::PlainText);

        // Image du joueur - version ronde dans le panneau de détails
        if (!imageData.isEmpty()) {
            QPixmap playerPixmap;
            if (playerPixmap.loadFromData(imageData)) {
                // Créer une image circulaire avec une bordure
                QPixmap circularPixmap(70, 70);
                circularPixmap.fill(Qt::transparent);

                QPainter painter(&circularPixmap);
                painter.setRenderHint(QPainter::Antialiasing);

                // Créer un chemin circulaire pour découper l'image
                QPainterPath path;
                path.addEllipse(0, 0, 70, 70);
                painter.setClipPath(path);

                QPixmap scaledPixmap = playerPixmap.scaled(70, 70, Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);

                int x = (scaledPixmap.width() - 70) / 2;
                int y = (scaledPixmap.height() - 70) / 2;
                if (x < 0) x = 0;
                if (y < 0) y = 0;

                painter.drawPixmap(0, 0, scaledPixmap, x, y, 70, 70);

                // Dessiner une bordure circulaire
                painter.setClipping(false);
                painter.setPen(QPen(QColor(255, 255, 255), 2));
                painter.drawEllipse(1, 1, 68, 68);

                detailImageLabel->setPixmap(circularPixmap);
                detailImageLabel->setText("");
                detailImageLabel->setStyleSheet("background: transparent; border: none;");
            }
        } else {
            // Image par défaut avec les initiales
            detailImageLabel->setText(firstName.isEmpty() || lastName.isEmpty() ? "?" :
                                     QString(firstName[0]) + QString(lastName[0]));
            detailImageLabel->setPixmap(QPixmap());
            detailImageLabel->setStyleSheet(
                "background-color: rgba(52, 152, 219, 0.5);"
                "color: white;"
                "font-weight: bold;"
                "border-radius: 35px;"
                "border: 2px solid white;"
            );
        }
    } else {
        qDebug() << "Error fetching player details:" << query.lastError().text();
        detailNameLabel->setText("Error loading player details");
        detailTeamPosLabel->setText("");
        detailStatsLabel->setText("");
        detailImageLabel->setText("?");
        detailImageLabel->setPixmap(QPixmap());
    }
}

void MainWindow::displayTeamOfCompetition(const QString &competitionName)
{
    if (competitionName.isEmpty()) {
        qDebug() << "No competition selected";
        return;
    }
    
    qDebug() << "Loading team for competition:" << competitionName;
    
    // Structure pour stocker les joueurs par poste
    struct BestPlayer {
        int id;
        QString firstName;
        QString lastName;
        QByteArray imageData;
        int score; // score basé sur les buts et passes décisives
        QString position; // Position réelle du joueur
    };
    
    // Obtenir tous les joueurs de la compétition
    QList<BestPlayer> allPlayers;
    
    QSqlQuery query;
    query.prepare(
        "SELECT j.id_player, j.first_name, j.last_name, j.position, "
        "j.goals, j.assists, j.img_joueur "
        "FROM joueur j "
        "JOIN equipe e ON j.id_team = e.id_team "
        "JOIN participation p ON e.id_team = p.id_team "
        "JOIN competition c ON p.id_competition = c.id_competition "
        "WHERE c.comp_name = :competition_name "
        "ORDER BY (j.goals * 2 + j.assists) DESC" // Tri par score décroissant
    );
    query.bindValue(":competition_name", competitionName);
    
    if (!query.exec()) {
        qDebug() << "Error fetching players:" << query.lastError().text();
        return;
    }
    
    // Collecter tous les joueurs
    while (query.next()) {
        BestPlayer player;
        player.id = query.value("id_player").toInt();
        player.firstName = query.value("first_name").toString();
        player.lastName = query.value("last_name").toString();
        player.position = query.value("position").toString();
        player.imageData = query.value("img_joueur").toByteArray();
        int goals = query.value("goals").toInt();
        int assists = query.value("assists").toInt();
        player.score = goals * 2 + assists;
        
        allPlayers.append(player);
    }
    
    // Trier tous les joueurs par score décroissant
    std::sort(allPlayers.begin(), allPlayers.end(), [](const BestPlayer &a, const BestPlayer &b) {
        return a.score > b.score;
    });
    
    // Classification des positions et leur correspondance aux joueurs
    QMap<QString, QStringList> eligiblePositions;
    eligiblePositions["GK"] = QStringList({"Goalkeeper"});
    eligiblePositions["LB"] = QStringList({"Defender", "Left Back"});
    eligiblePositions["CB"] = QStringList({"Defender", "Center Back"});
    eligiblePositions["CB2"] = QStringList({"Defender", "Center Back"});
    eligiblePositions["RB"] = QStringList({"Defender", "Right Back"});
    eligiblePositions["LM"] = QStringList({"Midfielder", "Left Midfielder"});
    eligiblePositions["CM"] = QStringList({"Midfielder", "Central Midfielder"});
    eligiblePositions["RM"] = QStringList({"Midfielder", "Right Midfielder"});
    eligiblePositions["LW"] = QStringList({"Forward", "Left Winger"});
    eligiblePositions["ST"] = QStringList({"Forward", "Striker"});
    eligiblePositions["RW"] = QStringList({"Forward", "Right Winger"});
    
    // Map pour stocker le meilleur joueur pour chaque position
    QMap<QString, BestPlayer> selectedPlayers;
    QSet<int> usedPlayerIds; // Pour éviter les joueurs en double
    
    // Passer à travers tous les joueurs et les assigner aux positions
    // par ordre de score décroissant, en respectant le type de position
    for (const BestPlayer &player : allPlayers) {
        if (usedPlayerIds.contains(player.id)) {
            continue; // Sauter les joueurs déjà utilisés
        }
        
        // Pour éviter d'avoir des gardiens en position de joueur de champ ou vice-versa
        bool isGoalkeeper = player.position.contains("Goalkeeper");
        
        // Trouver la meilleure position pour ce joueur
        QString bestPosition;
        
        for (auto it = eligiblePositions.begin(); it != eligiblePositions.end(); ++it) {
            QString posKey = it.key();
            QStringList posTypes = it.value();
            
            // Skip cette position si elle est déjà attribuée
            if (selectedPlayers.contains(posKey)) {
                continue;
            }
            
            // Si c'est un gardien, il ne peut jouer qu'en GK
            if (isGoalkeeper && posKey != "GK") {
                continue;
            }
            
            // Si ce n'est pas un gardien, il ne peut pas jouer en GK
            if (!isGoalkeeper && posKey == "GK") {
                continue;
            }
            
            // Vérifier si le joueur correspond à cette position
            bool positionMatch = false;
            for (const QString &posType : posTypes) {
                if (player.position.contains(posType)) {
                    positionMatch = true;
                    break;
                }
            }
            
            if (positionMatch) {
                bestPosition = posKey;
                break; // Première position correspondante trouvée
            }
        }
        
        // Si une position a été trouvée, assigner le joueur
        if (!bestPosition.isEmpty()) {
            selectedPlayers[bestPosition] = player;
            usedPlayerIds.insert(player.id);
        }
    }
    
    // Deuxième passe: remplir les postes encore vides
    // avec les joueurs restants en respectant les catégories générales
    if (selectedPlayers.size() < eligiblePositions.size()) {
        // Grouper les positions par catégorie
        QMap<QString, QList<QString>> categoryPositions;
        categoryPositions["Goalkeeper"] = QList<QString>({"GK"});
        categoryPositions["Defender"] = QList<QString>({"LB", "CB", "CB2", "RB"});
        categoryPositions["Midfielder"] = QList<QString>({"LM", "CM", "RM"});
        categoryPositions["Forward"] = QList<QString>({"LW", "ST", "RW"});
        
        // Pour chaque joueur non utilisé
        for (const BestPlayer &player : allPlayers) {
            if (usedPlayerIds.contains(player.id)) {
                continue;
            }
            
            // Déterminer sa catégorie générale
            QString category;
            if (player.position.contains("Goalkeeper")) {
                category = "Goalkeeper";
            } else if (player.position.contains("Defender") || player.position.contains("Back")) {
                category = "Defender";
            } else if (player.position.contains("Midfielder")) {
                category = "Midfielder";
            } else {
                category = "Forward"; // Par défaut
            }
            
            // Chercher une position disponible dans sa catégorie
            for (const QString &pos : categoryPositions[category]) {
                if (!selectedPlayers.contains(pos)) {
                    selectedPlayers[pos] = player;
                    usedPlayerIds.insert(player.id);
                    break;
                }
            }
        }
    }
    
    // Troisième passe: si des positions sont encore vides, remplir
    // avec n'importe quel joueur disponible (sauf gardien en joueur et vice-versa)
    for (auto it = eligiblePositions.begin(); it != eligiblePositions.end(); ++it) {
        QString posKey = it.key();
        
        if (selectedPlayers.contains(posKey)) {
            continue; // Position déjà attribuée
        }
        
        // Chercher un joueur non utilisé
        for (const BestPlayer &player : allPlayers) {
            if (usedPlayerIds.contains(player.id)) {
                continue;
            }
            
            // Vérifier la compatibilité gardien/joueur
            if ((posKey == "GK" && !player.position.contains("Goalkeeper")) ||
                (posKey != "GK" && player.position.contains("Goalkeeper"))) {
                continue;
            }
            
            selectedPlayers[posKey] = player;
            usedPlayerIds.insert(player.id);
            break;
        }
    }
    
    // Mettre à jour l'interface pour toutes les positions sauf CB2
    for (auto it = selectedPlayers.begin(); it != selectedPlayers.end(); ++it) {
        QString positionKey = it.key();
        if (positionKey == "CB2") continue; // On traite CB2 séparément
        
        BestPlayer player = it.value();
        
        // Trouver le widget de position
        QFrame *posFrame = ui->tabWidget->findChild<QFrame*>("position_" + positionKey);
        if (posFrame) {
            // Stocker l'ID du joueur
            posFrame->setProperty("playerId", player.id);
            
            // Mettre à jour l'image/texte
            QLabel *playerImage = posFrame->findChild<QLabel*>("image_" + positionKey);
            if (playerImage) {
                if (!player.imageData.isEmpty()) {
                    QPixmap pixmap;
                    if (pixmap.loadFromData(player.imageData)) {
                        // Créer une version circulaire de l'image
                        QPixmap circularPixmap(60, 60);
                        circularPixmap.fill(Qt::transparent);
                        
                        QPainter painter(&circularPixmap);
                        painter.setRenderHint(QPainter::Antialiasing);
                        
                        QPainterPath path;
                        path.addEllipse(0, 0, 60, 60);
                        painter.setClipPath(path);
                        
                        QPixmap scaledPixmap = pixmap.scaled(60, 60, Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);
                        
                        int x = (scaledPixmap.width() - 60) / 2;
                        int y = (scaledPixmap.height() - 60) / 2;
                        if (x < 0) x = 0;
                        if (y < 0) y = 0;
                        
                        painter.drawPixmap(0, 0, scaledPixmap, x, y, 60, 60);
                        
                        playerImage->setPixmap(circularPixmap);
                        playerImage->setText("");
                    }
                } else {
                    // Utiliser les initiales si pas d'image
                    playerImage->setText(player.firstName.isEmpty() || player.lastName.isEmpty() ? 
                                        positionKey : 
                                        QString(player.firstName[0]) + QString(player.lastName[0]));
                }
            }
        }
    }
    
    // Traitement spécial pour le deuxième défenseur central (CB2)
    if (selectedPlayers.contains("CB2")) {
        BestPlayer player = selectedPlayers["CB2"];
        
        // Trouver tous les widgets CB
        QList<QFrame*> cbFrames = ui->tabWidget->findChildren<QFrame*>("position_CB");
        
        // Trouver un widget CB non utilisé
        for (QFrame *frame : cbFrames) {
            int framePlayerId = frame->property("playerId").toInt();
            if (framePlayerId <= 0 || !usedPlayerIds.contains(framePlayerId)) {
                // Widget trouvé, l'utiliser pour le deuxième CB
                frame->setProperty("playerId", player.id);
                
                QLabel *playerImage = frame->findChild<QLabel*>("image_CB");
                if (playerImage) {
                    if (!player.imageData.isEmpty()) {
                        QPixmap pixmap;
                        if (pixmap.loadFromData(player.imageData)) {
                            QPixmap circularPixmap(60, 60);
                            circularPixmap.fill(Qt::transparent);
                            
                            QPainter painter(&circularPixmap);
                            painter.setRenderHint(QPainter::Antialiasing);
                            
                            QPainterPath path;
                            path.addEllipse(0, 0, 60, 60);
                            painter.setClipPath(path);
                            
                            QPixmap scaledPixmap = pixmap.scaled(60, 60, Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);
                            
                            int x = (scaledPixmap.width() - 60) / 2;
                            int y = (scaledPixmap.height() - 60) / 2;
                            if (x < 0) x = 0;
                            if (y < 0) y = 0;
                            
                            painter.drawPixmap(0, 0, scaledPixmap, x, y, 60, 60);
                            
                            playerImage->setPixmap(circularPixmap);
                            playerImage->setText("");
                        }
                    } else {
                        playerImage->setText(player.firstName.isEmpty() || player.lastName.isEmpty() ? 
                                            "CB" : 
                                            QString(player.firstName[0]) + QString(player.lastName[0]));
                    }
                }
                
                break;
            }
        }
    }
    
    // Réinitialiser les positions qui n'ont pas de joueurs attribués
    QStringList allPositions = {"GK", "LB", "CB", "RB", "LM", "CM", "RM", "LW", "ST", "RW"};
    
    for (const QString &position : allPositions) {
        // Pour CB, on a plusieurs widgets
        if (position == "CB") {
            QList<QFrame*> cbFrames = ui->tabWidget->findChildren<QFrame*>("position_CB");
            
            for (QFrame *frame : cbFrames) {
                int framePlayerId = frame->property("playerId").toInt();
                
                if (framePlayerId <= 0 || !usedPlayerIds.contains(framePlayerId)) {
                    // Réinitialiser le widget
                    frame->setProperty("playerId", -1);
                    
                    QLabel *playerImage = frame->findChild<QLabel*>("image_CB");
                    if (playerImage) {
                        playerImage->setText("CB");
                        playerImage->setPixmap(QPixmap());
                    }
                }
            }
            continue;
        }
        
        // Pour les autres positions
        if (!selectedPlayers.contains(position)) {
            QFrame *posFrame = ui->tabWidget->findChild<QFrame*>("position_" + position);
            
            if (posFrame) {
                posFrame->setProperty("playerId", -1);
                
                QLabel *playerImage = posFrame->findChild<QLabel*>("image_" + position);
                if (playerImage) {
                    playerImage->setText(position);
                    playerImage->setPixmap(QPixmap());
                }
            }
        }
    }
}
