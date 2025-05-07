#include "../playerheaders/playerwindow.h"
#include "ui_playerwindow.h"
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
#include "../playerheaders/joueur.h"
#include "../playerheaders/deletejoueur.h"
#include "../playerheaders/modifyjoueur.h"
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
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QEventLoop>
#include <QTextEdit>
#include <QScrollBar>
#include "../playerheaders/addplayer.h"
#include "../userheaders/sessionmanager.h"	
#include "../userheaders/mainwindow.h"
#include "../userheaders/admin.h"
#include "../userheaders/employeview.h"
#include "../compheaders/competitionview.h" // Ensure this header is included
#include <QstackedWidget>
#include "../about.h"



playerwindow::playerwindow(QStackedWidget *stackedWidget, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::playerwindow)
    , currentDisplayedPlayerId(-1)
{
    ui->setupUi(this);

    //load the name and role of the current user
    // Load current user's photo and details
    const Employee& currentUser = SessionManager::instance().getCurrentUser();
    if (!currentUser.getFace().isEmpty()) {
        QPixmap pixmap;
        if (pixmap.loadFromData(currentUser.getFace())) {
            ui->currentUserPhotoLabel->setPixmap(pixmap.scaled(ui->currentUserPhotoLabel->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
        } else {
            qDebug() << "Failed to load user photo from data.";
            ui->currentUserPhotoLabel->setText("No Photo");
        }
    } else {
        ui->currentUserPhotoLabel->setText("No Photo");
    }

    // Set username and role
    ui->dashboard_9->setText(currentUser.getFirstName() + " " + currentUser.getLastName());
    ui->dashboard_8->setText(currentUser.getRole());
    
    // Initialize positions combobox (keep if used elsewhere, otherwise remove)


    // Initialize sorting options
    ui->comboBoxTri->clear();
    ui->comboBoxTri->addItem("Default (No Sorting)", "none");
    ui->comboBoxTri->addItem("Name (A-Z)", "name_asc");
    ui->comboBoxTri->addItem("Name (Z-A)", "name_desc");
    ui->comboBoxTri->addItem("Team", "team");
    ui->comboBoxTri->addItem("Position", "position");
    ui->comboBoxTri->addItem("Goals (High-Low)", "goals_desc");
    ui->comboBoxTri->addItem("Goals (Low-High)", "goals_asc");

    // Connect buttons

    connect(ui->userbutton, &QPushButton::clicked, this, &playerwindow::on_userbutton_clicked);
    connect(ui->pushButton_3, &QPushButton::clicked, this, &playerwindow::on_buttonDelete_clicked);
    connect(ui->lineEdit_10, &QLineEdit::textChanged, this, &playerwindow::onSearchTextChanged);
    connect(ui->buttonViewDetails, &QPushButton::clicked, this, &playerwindow::on_buttonViewDetails_clicked);
    connect(ui->comboBoxTri, &QComboBox::currentIndexChanged, this, &playerwindow::onSortingChanged);
    connect(ui->pushButton_2, &QPushButton::clicked, this, &playerwindow::openAddPlayer);
    // connect to logout button
    connect(ui->logout, &QPushButton::clicked, this, &playerwindow::handleLogoutButtonClicked);

    //connect to team button 
    connect(ui->teamButton, &QPushButton::clicked, this, [this]() {
        QStackedWidget *stackedWidget = qobject_cast<QStackedWidget*>(parentWidget());
        if (stackedWidget) {
            // Assuming the team window is at index 1 in the stacked widget
            stackedWidget->setCurrentIndex(1);
        }
    });
    //connect to competition button
    connect(ui->compButton, &QPushButton::clicked, this, [this]() {
        QStackedWidget *stackedWidget = qobject_cast<QStackedWidget*>(parentWidget());
        if (stackedWidget) {
            // Replace 2 with the correct index for your competition window if needed
            stackedWidget->setCurrentIndex(3);
        }
    });
    //connect to match button
    connect(ui->matchButton, &QPushButton::clicked, this, [this]() {
        QStackedWidget *stackedWidget = qobject_cast<QStackedWidget*>(parentWidget());
        if (stackedWidget) {
            // Replace 3 with the correct index for your match window if needed
            stackedWidget->setCurrentIndex(4);
        }
    });

    // Set placeholder text for search field
    ui->lineEdit_10->setPlaceholderText("Search players by name, nationality, position...");

    // Set up table
    ui->tableWidget->setColumnCount(14);
    ui->tableWidget->setHorizontalHeaderLabels({
        "ID Player", "ID Team", "First Name", "Last name", "Position", "Jersey Number", "Date of Birth",
        "Nationality", "Goals", "Assists", "Injury", "Yellow Card", "Red Card", "Status"
    });
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

    loadTeams();
    loadPlayers();

    setupStatisticsTab();
    setupBestPlayerTab();
    setupTeamOfCompetitionTab();

    connect(ui->tableWidget->selectionModel(), &QItemSelectionModel::selectionChanged,
            this, &playerwindow::onTableSelectionChanged);
}

void playerwindow::on_userbutton_clicked()
{
    QStackedWidget *stackedWidget = qobject_cast<QStackedWidget*>(parentWidget());
    if (stackedWidget) {
    stackedWidget->setCurrentIndex(0); // or setCurrentWidget(adminDashboard);
}
    
}

void playerwindow::handleLogoutButtonClicked()
{
    qDebug() << "Logout button clicked.";
    // Clear the session to log out the user
    SessionManager::instance().clearSession();

    // Update the photo label to indicate no user
    ui->currentUserPhotoLabel->setText("No User");
    ui->dashboard_9->setText("User name"); // Reset username label
    ui->dashboard_8->setText("Role");      // Reset role label

    // Try to get the parent MainWindow
    QWidget *parent = parentWidget();
    MainWindow *mainWindow = qobject_cast<MainWindow*>(parent);
    if (mainWindow) {
        // Clear the email and password fields in MainWindow
        QLineEdit *emailField = mainWindow->findChild<QLineEdit*>("lineEdit");
        QLineEdit *passwordField = mainWindow->findChild<QLineEdit*>("lineEdit_2");
        if (emailField && passwordField) {
            emailField->clear();
            passwordField->clear();
        } else {
            qDebug() << "Failed to find email or password fields in MainWindow.";
        }
        mainWindow->showMaximized();
    } else {
        // Fallback: Create a new MainWindow
        qDebug() << "No parent MainWindow found, creating a new one.";
        MainWindow *loginWindow = new MainWindow();
        loginWindow->showMaximized();
    }

    // Close all parent windows up the chain (including stacked widgets)
    QWidget *w = this;
    while (w) {
        QWidget *parent = w->parentWidget();
        w->close();
        w = parent;
    }
}
void playerwindow::on_aboutButton_clicked()
{
    qDebug() << "About button clicked.";
    About *aboutDialog = new About(this);
    aboutDialog->exec();
    delete aboutDialog;
}

void playerwindow::openAddPlayer()
{
    // Solution garantie avec gestion de la mémoire
    AddPlayer *addPlayerWindow = new AddPlayer(this);
    addPlayerWindow->setAttribute(Qt::WA_DeleteOnClose);

    // Méthode alternative pour afficher comme popup
    addPlayerWindow->setWindowModality(Qt::ApplicationModal);
    addPlayerWindow->setWindowFlags(Qt::Dialog | Qt::WindowCloseButtonHint);

    addPlayerWindow->show();
}
playerwindow::~playerwindow()
{
    delete ui;
}

void playerwindow::loadTeams()
{
    // Clear combobox and map

    teamMap.clear();

    // Load all teams from database
    QSqlQuery query("SELECT id_team, team_name FROM equipe ORDER BY team_name");

    while (query.next()) {
        int id = query.value(0).toInt();
        QString name = query.value(1).toString();

        // Add to combobox and map

        teamMap[name] = id;
    }


}

void playerwindow::loadPlayers()
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

void playerwindow::onSearchTextChanged(const QString &text)
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



void playerwindow::on_buttonDelete_clicked()
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

void playerwindow::on_buttonModify_clicked()
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

bool playerwindow::validateTableSelection()
{
    QModelIndexList selection = ui->tableWidget->selectionModel()->selectedRows();
    if (selection.isEmpty()) {
        QMessageBox::warning(this, "Error", "Please select a player from the table first.");
        return false;
    }
    return true;
}

void playerwindow::on_buttonViewDetails_clicked()
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

void playerwindow::refreshPlayerDetails()
{
    // Si no player is selected to display
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
    frameLayout->setContentsMargins(0, 0, 0, 0); // Minimiser les marges
    ui->formFrame->setLayout(frameLayout);
    
    // Appliquer le style moderne au cadre principal
    ui->formFrame->setStyleSheet(
        "QFrame {"
        "   background-color: rgba(45, 48, 56, 0.92);"
        "   border-radius: 12px;"
        "   border: 1px solid rgba(255, 255, 255, 0.15);"
        "}"
    );

    // Créer un widget de défilement
    QScrollArea *scrollArea = new QScrollArea();
    scrollArea->setFrameShape(QFrame::NoFrame);
    scrollArea->setWidgetResizable(true);
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    scrollArea->setStyleSheet(
        "QScrollArea { background: transparent; border: none; }"
        "QScrollBar:vertical {"
        "   background: rgba(0, 0, 0, 0.2);"
        "   width: 8px;"
        "   margin: 0px;"
        "}"
        "QScrollBar::handle:vertical {"
        "   background: rgba(255, 255, 255, 0.3);"
        "   min-height: 20px;"
        "   border-radius: 4px;"
        "}"
        "QScrollBar::add-line:vertical, QScrollBar::sub-line:vertical {"
        "   border: none;"
        "   background: none;"
        "   height: 0px;"
        "}"
    );

    // Créer un widget conteneur pour tout le contenu
    QWidget *contentWidget = new QWidget();
    contentWidget->setStyleSheet("background: transparent;");
    QVBoxLayout *contentLayout = new QVBoxLayout(contentWidget);
    contentLayout->setSpacing(10);
    contentLayout->setContentsMargins(10, 10, 10, 10);

    // Query all player details
    QSqlQuery query;
    query.prepare("SELECT j.*, e.team_name "
                  "FROM joueur j "
                  "JOIN equipe e ON j.id_team = e.id_team "
                  "WHERE j.id_player = :id");
    query.bindValue(":id", currentDisplayedPlayerId);

    if (query.exec() && query.next()) {
        // Préparation des données
        QString playerFullName = query.value("first_name").toString() + " " + query.value("last_name").toString();
        QString teamName = query.value("team_name").toString();
        QString position = query.value("position").toString();
        QString jerseyNumber = "#" + query.value("jersey_nb").toString();
        QString nationality = query.value("nationality").toString();
        QDate dateOfBirth = query.value("date_of_birth").toDate();
        int goals = query.value("goals").toInt();
        int assists = query.value("assists").toInt();
        int yellowCards = query.value("yellow_card").toInt();
        int redCards = query.value("red_card").toInt();
        bool injured = query.value("injured").toInt() == 1;
        int status = query.value("status").toInt();
        QString statusText;
        switch(status) {
            case 0: statusText = "Active"; break;
            case 1: statusText = "Injured"; break;
            case 2: statusText = "Suspended"; break;
            case 3: statusText = "Transferred"; break;
            default: statusText = "Unknown";
        }
        QByteArray imageData = query.value("img_joueur").toByteArray();

// ===== IMAGE DU JOUEUR GRANDE ET CENTRÉE =====
if (!imageData.isEmpty()) {
    QLabel *playerImageLabel = new QLabel();
    playerImageLabel->setFixedSize(250, 250);
    playerImageLabel->setAlignment(Qt::AlignCenter);
    
    QPixmap originalPixmap;
    originalPixmap.loadFromData(imageData);
    
    // Créer une image circulaire sans dégradé
    QPixmap circularPixmap(250, 250);
    circularPixmap.fill(Qt::transparent);
    
    QPainter painter(&circularPixmap);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setRenderHint(QPainter::SmoothPixmapTransform, true);
    
    // Créer un chemin circulaire pour découper l'image
    QPainterPath path;
    path.addEllipse(15, 15, 220, 220);
    painter.setClipPath(path);
    
    // Redimensionner et centrer l'image
    QPixmap scaledPixmap = originalPixmap.scaled(220, 220, 
                           Qt::KeepAspectRatioByExpanding, 
                           Qt::SmoothTransformation);
    
    // Centrer l'image dans le cercle
    int x = scaledPixmap.width() > 220 ? (scaledPixmap.width() - 220) / 2 : 0;
    int y = scaledPixmap.height() > 220 ? (scaledPixmap.height() - 220) / 2 : 0;
    
    painter.drawPixmap(15, 15, scaledPixmap, x, y, 220, 220);
    
    // Enlever le clipping pour dessiner la bordure
    painter.setClipping(false);
    
    // Dessiner une bordure blanche simple
    QPen borderPen(Qt::white, 3);
    painter.setPen(borderPen);
    painter.drawEllipse(15, 15, 220, 220);
    
    painter.end();
    
    playerImageLabel->setPixmap(circularPixmap);
    playerImageLabel->setStyleSheet("background: transparent;");
    
    // Ajouter l'image au début du layout
    contentLayout->addWidget(playerImageLabel, 0, Qt::AlignHCenter);
} else {
    // Image par défaut avec initiales, également sans dégradé
    QLabel *playerImageLabel = new QLabel();
    playerImageLabel->setFixedSize(250, 250);
    playerImageLabel->setAlignment(Qt::AlignCenter);
    
    // Créer une image avec les initiales
    QPixmap circularPixmap(250, 250);
    circularPixmap.fill(Qt::transparent);
    
    QPainter painter(&circularPixmap);
    painter.setRenderHint(QPainter::Antialiasing, true);
    
    // Fond gris clair neutre sans dégradé
    painter.setPen(Qt::NoPen);
    painter.setBrush(QColor(200, 200, 200, 180));
    painter.drawEllipse(15, 15, 220, 220);
    
    // Bordure blanche
    painter.setPen(QPen(Qt::white, 3));
    painter.drawEllipse(15, 15, 220, 220);
    
    // Afficher les initiales
    painter.setPen(Qt::white);
    QFont font = painter.font();
    font.setPointSize(64);
    font.setBold(true);
    painter.setFont(font);
    
    // Initiales
    QString initials;
    if (!query.value("first_name").toString().isEmpty() && !query.value("last_name").toString().isEmpty()) {
        initials = QString(query.value("first_name").toString()[0]) + 
                   QString(query.value("last_name").toString()[0]);
    } else {
        initials = "?";
    }
    
    painter.drawText(QRect(15, 15, 220, 220), Qt::AlignCenter, initials);
    painter.end();
    
    playerImageLabel->setPixmap(circularPixmap);
    
    // Ajouter au début du layout
    contentLayout->addWidget(playerImageLabel, 0, Qt::AlignHCenter);
}

        // ===== SECTION EN-TÊTE =====
        QFrame *headerFrame = new QFrame();
        headerFrame->setStyleSheet(
            "QFrame {"
            "   background: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 #2c3e50, stop:1 #34495e);"
            "   border-radius: 8px;"
            "   padding: 10px;"
            "   margin-bottom: 10px;"
            "}"
        );
        QVBoxLayout *headerLayout = new QVBoxLayout(headerFrame);
        
        // Information du joueur
        QLabel *nameLabel = new QLabel(playerFullName);
        nameLabel->setAlignment(Qt::AlignCenter);
        nameLabel->setStyleSheet(
            "color: white;"
            "font-size: 18px;"
            "font-weight: bold;"
            "margin-bottom: 5px;"
        );
        
        QLabel *teamPositionLabel = new QLabel(position + " | " + teamName);
        teamPositionLabel->setAlignment(Qt::AlignCenter);
        teamPositionLabel->setStyleSheet(
            "color: #3498db;"
            "font-size: 14px;"
            "font-weight: bold;"
        );
        
        QHBoxLayout *statusLayout = new QHBoxLayout();
        statusLayout->setAlignment(Qt::AlignCenter);
        
        QLabel *jerseyLabel = new QLabel(jerseyNumber);
        jerseyLabel->setFixedSize(32, 32);
        jerseyLabel->setAlignment(Qt::AlignCenter);
        jerseyLabel->setStyleSheet(
            "background-color: #e74c3c;"
            "color: white;"
            "font-size: 14px;"
            "font-weight: bold;"
            "border-radius: 16px;"
            "margin-right: 8px;"
        );
        
        QLabel *statusLabel = new QLabel(statusText);
        statusLabel->setAlignment(Qt::AlignCenter);
        
        // Style différent selon le statut
        QString statusStyle;
        if (status == 0) {
            statusStyle = "background-color: #2ecc71;"; // Vert pour Actif
        } else if (status == 1) {
            statusStyle = "background-color: #f1c40f;"; // Jaune pour Blessé
        } else if (status == 2) {
            statusStyle = "background-color: #e74c3c;"; // Rouge pour Suspendu
        } else {
            statusStyle = "background-color: #95a5a6;"; // Gris pour Transféré
        }
        
        statusLabel->setStyleSheet(
            "color: white;"
            "font-size: 12px;"
            "font-weight: bold;"
            "border-radius: 10px;"
            + statusStyle +
            "padding: 3px 8px;"
        );
        
        statusLayout->addWidget(jerseyLabel);
        statusLayout->addWidget(statusLabel);
        
        headerLayout->addWidget(nameLabel);
        headerLayout->addWidget(teamPositionLabel);
        headerLayout->addLayout(statusLayout);
        
        contentLayout->addWidget(headerFrame);
        
        // ===== SECTION STATISTIQUES =====
        QFrame *statsFrame = new QFrame();
        statsFrame->setStyleSheet(
            "QFrame {"
            "   background-color: rgba(255, 255, 255, 0.05);"
            "   border-radius: 8px;"
            "   padding: 12px;"
            "   margin-bottom: 10px;"
            "}"
        );
        QHBoxLayout *statsLayout = new QHBoxLayout(statsFrame);
        statsLayout->setSpacing(8);
        
        // Fonction pour créer un widget de statistique
        auto createStatWidget = [](const QString &value, const QString &label, const QString &color) {
            QFrame *statFrame = new QFrame();
            statFrame->setStyleSheet(
                "QFrame {"
                "   background-color: " + color + ";"
                "   border-radius: 8px;"
                "   padding: 8px;"
                "}"
            );
            
            QVBoxLayout *statLayout = new QVBoxLayout(statFrame);
            statLayout->setSpacing(2);
            statLayout->setContentsMargins(5, 5, 5, 5);
            
            QLabel *valueLabel = new QLabel(value);
            valueLabel->setAlignment(Qt::AlignCenter);
            valueLabel->setStyleSheet(
                "color: white;"
                "font-size: 18px;"
                "font-weight: bold;"
                "background: transparent;"
            );
            
            QLabel *titleLabel = new QLabel(label);
            titleLabel->setAlignment(Qt::AlignCenter);
            titleLabel->setStyleSheet(
                "color: rgba(255, 255, 255, 0.8);"
                "font-size: 10px;"
                "background: transparent;"
            );
            
            statLayout->addWidget(valueLabel);
            statLayout->addWidget(titleLabel);
            
            return statFrame;
        };
        
        // Créer les widgets de stats
        QFrame *goalsWidget = createStatWidget(QString::number(goals), "GOALS", "rgba(46, 204, 113, 0.8)");
        QFrame *assistsWidget = createStatWidget(QString::number(assists), "ASSISTS", "rgba(52, 152, 219, 0.8)");
        QFrame *yellowWidget = createStatWidget(QString::number(yellowCards), "YELLOW", "rgba(241, 196, 15, 0.8)");
        QFrame *redWidget = createStatWidget(QString::number(redCards), "RED", "rgba(231, 76, 60, 0.8)");
        
        statsLayout->addWidget(goalsWidget);
        statsLayout->addWidget(assistsWidget);
        statsLayout->addWidget(yellowWidget);
        statsLayout->addWidget(redWidget);
        
        contentLayout->addWidget(statsFrame);
        
        // ===== SECTION DÉTAILS =====
        QFrame *detailsFrame = new QFrame();
        detailsFrame->setStyleSheet(
            "QFrame {"
            "   background-color: rgba(255, 255, 255, 0.05);"
            "   border-radius: 8px;"
            "   padding: 15px;"
            "   margin-bottom: 10px;"
            "}"
        );
        QGridLayout *detailsLayout = new QGridLayout(detailsFrame);
        detailsLayout->setVerticalSpacing(8);
        detailsLayout->setHorizontalSpacing(15);
        
        // Fonction pour créer une ligne d'information
        auto addInfoRow = [&detailsLayout](int row, const QString &label, const QString &value) {
            QLabel *labelWidget = new QLabel(label);
            labelWidget->setStyleSheet(
                "color: #bdc3c7;"
                "font-size: 12px;"
            );
            
            QLabel *valueWidget = new QLabel(value);
            valueWidget->setStyleSheet(
                "color: white;"
                "font-size: 12px;"
                "font-weight: bold;"
            );
            
            detailsLayout->addWidget(labelWidget, row, 0);
            detailsLayout->addWidget(valueWidget, row, 1);
        };
        
        // Ajouter les détails en colonnes
        addInfoRow(0, "Nationality:", nationality);
        addInfoRow(1, "Date of Birth:", dateOfBirth.toString("dd MMM yyyy"));
        addInfoRow(2, "Age:", QString::number(QDate::currentDate().year() - dateOfBirth.year()));
        addInfoRow(3, "Injured:", injured ? "Yes" : "No");
        
        contentLayout->addWidget(detailsFrame);
        
        // Ajouter un QR code
        QString qrText = QString("ID: %1\nName: %2\nTeam: %3\nPosition: %4\nJersey: %5\nStatus: %6")
            .arg(query.value("id_player").toString()).arg(playerFullName)
            .arg(teamName).arg(position).arg(jerseyNumber).arg(statusText);
        
        QPixmap qrCode = generateQRCode(qrText);
        QLabel *qrLabel = new QLabel();
        qrLabel->setPixmap(qrCode.scaled(80, 80, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        qrLabel->setAlignment(Qt::AlignCenter);
        qrLabel->setStyleSheet("background: transparent;");
        
        contentLayout->addWidget(qrLabel, 0, Qt::AlignHCenter);
        
      // ===== SECTION BOUTONS =====
QHBoxLayout *buttonLayout = new QHBoxLayout();
buttonLayout->setSpacing(8);

// Style commun pour les boutons
QString buttonStyle = 
    "QPushButton {"
    "   background-color: #3498db;"
    "   color: white;"
    "   border-radius: 4px;"
    "   font-weight: bold;"
    "   padding: 6px 12px;"
    "   font-size: 11px;"
    "   text-align: left;"
    "   padding-left: 30px;" // Espace pour l'icône
    "}"
    "QPushButton:hover {"
    "   background-color: #2980b9;"
    "}"
    "QPushButton:pressed {"
    "   background-color: #1c5a85;"
    "}";

// Bouton Export PDF avec icône
QPushButton *exportButton = new QPushButton("Export PDF");
exportButton->setStyleSheet(buttonStyle);
// Ajouter l'icône PDF
QIcon pdfIcon(QPixmap("C:/Users/wiki/Desktop/ALDAWRY-FOOTBALL/ALDAWRY-FOOTBALL-gestion_joueurs2/ALDAWRY-FOOTBALL-gestion_joueurs2/ALDAWRY-FOOTBALL-gestion_joueurs2/JoueurQ/pdfIcon.png"));
exportButton->setIcon(pdfIcon);
exportButton->setIconSize(QSize(16, 16));
connect(exportButton, &QPushButton::clicked, [this, playerId = currentDisplayedPlayerId]() {
    exportPlayerToPDF(playerId);
});

// Bouton Generate Report avec icône
QPushButton *reportButton = new QPushButton("Generate Report");
reportButton->setStyleSheet(buttonStyle);
// Ajouter l'icône AI
QIcon aiIcon(QPixmap("C:/Users/wiki/Desktop/ALDAWRY-FOOTBALL/ALDAWRY-FOOTBALL-gestion_joueurs2/ALDAWRY-FOOTBALL-gestion_joueurs2/ALDAWRY-FOOTBALL-gestion_joueurs2/JoueurQ/Group 1.png"));
reportButton->setIcon(aiIcon);
reportButton->setIconSize(QSize(16, 16));
connect(reportButton, &QPushButton::clicked, [this, playerId = currentDisplayedPlayerId]() {
    QJsonObject playerData = collectPlayerData(playerId);
    if (!playerData.isEmpty()) {
        QString reportText = generateReport(playerData);
        displayReport(reportText);
    } else {
        QMessageBox::warning(this, "Error", "Could not collect player data.");
    }
});

// Bouton Fermer avec icône
QPushButton *closeButton = new QPushButton("Hide Details");
closeButton->setStyleSheet(
    "QPushButton {"
    "   background-color: #95a5a6;"
    "   color: white;"
    "   border-radius: 4px;"
    "   font-weight: bold;"
    "   padding: 6px 12px;"
    "   font-size: 11px;"
    "   text-align: left;"
    "   padding-left: 30px;" // Espace pour l'icône
    "}"
    "QPushButton:hover {"
    "   background-color: #7f8c8d;"
    "}"
);
// Ajouter l'icône Hide
QIcon hideIcon(QPixmap("C:/Users/wiki/Desktop/ALDAWRY-FOOTBALL/ALDAWRY-FOOTBALL-gestion_joueurs2/ALDAWRY-FOOTBALL-gestion_joueurs2/ALDAWRY-FOOTBALL-gestion_joueurs2/JoueurQ/Vectorrrr.png"));
closeButton->setIcon(hideIcon);
closeButton->setIconSize(QSize(16, 16));
connect(closeButton, &QPushButton::clicked, [this]() {
    ui->formFrame->setVisible(false);
    currentDisplayedPlayerId = -1; // Reset current ID
});

buttonLayout->addWidget(exportButton);
buttonLayout->addWidget(reportButton);
buttonLayout->addStretch();
buttonLayout->addWidget(closeButton);

contentLayout->addLayout(buttonLayout);

        // Ajouter un petit espace au fond pour améliorer l'apparence du défilement
        contentLayout->addSpacing(5);
        
        // Configurer le widget de défilement
        scrollArea->setWidget(contentWidget);
        frameLayout->addWidget(scrollArea);
        
        // Make the frame visible if it's not already
        ui->formFrame->setVisible(true);
        
        // Make sure to apply the layout
        ui->formFrame->updateGeometry();
    } else {
        QMessageBox::warning(this, "Error", "Could not retrieve player details.");
        ui->formFrame->setVisible(false);
        currentDisplayedPlayerId = -1; // Reset current ID
    }
}
void playerwindow::onTableSelectionChanged(const QItemSelection &selected, const QItemSelection &deselected)
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

void playerwindow::onSortingChanged(int index)
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



void playerwindow::exportPlayerToPDF(int playerId)
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

QFrame* playerwindow::createStatsCard(const QString &title, const QString &value, const QString &style)
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

void playerwindow::setupStatisticsTab()
{
    // Création de l'onglet statistiques
    QWidget *statTab = new QWidget();
    
    // Ajouter un QScrollArea comme conteneur principal
    QScrollArea *scrollArea = new QScrollArea();
    scrollArea->setWidgetResizable(true);
    scrollArea->setFrameShape(QFrame::NoFrame);
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    scrollArea->setStyleSheet(
        "QScrollArea { background: transparent; border: none; }"
        "QScrollBar:vertical {"
        "   background: rgba(0, 0, 0, 0.2);"
        "   width: 8px;"
        "   margin: 0px;"
        "}"
        "QScrollBar::handle:vertical {"
        "   background: rgba(255, 255, 255, 0.3);"
        "   min-height: 20px;"
        "   border-radius: 4px;"
        "}"
        "QScrollBar::add-line:vertical, QScrollBar::sub-line:vertical {"
        "   border: none;"
        "   background: none;"
        "   height: 0px;"
        "}"
    );
    
    // Créer un widget conteneur pour tout le contenu
    QWidget *contentWidget = new QWidget();
    QVBoxLayout *mainLayout = new QVBoxLayout(contentWidget);
    mainLayout->setSpacing(15);
    contentWidget->setStyleSheet("background:rgb(20, 22, 38);"); // Fond foncé pour tout le contenu

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

    // Tableau des meilleurs buteurs
    QGroupBox *topScorersGroup = new QGroupBox("Top Goalscorers");
    topScorersGroup->setStyleSheet("QGroupBox { font-weight: bold; }");
    QVBoxLayout *scorersLayout = new QVBoxLayout(topScorersGroup);
    QTableWidget *scorersTable = new QTableWidget(0, 3);
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
    scorersTable->verticalHeader()->setDefaultSectionSize(50);
    scorersLayout->addWidget(scorersTable);
    tablesLayout->addWidget(topScorersGroup);

    // Tableau des meilleurs passeurs
    QGroupBox *topAssistsGroup = new QGroupBox("Top Assists");
    topAssistsGroup->setStyleSheet("QGroupBox { font-weight: bold; }");
    QVBoxLayout *assistsLayout = new QVBoxLayout(topAssistsGroup);
    QTableWidget *assistsTable = new QTableWidget(0, 3);
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
    assistsTable->verticalHeader()->setDefaultSectionSize(50);
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
    filterLabel->setStyleSheet("color: white;");
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
    connect(teamFilterComboBox, &QComboBox::currentIndexChanged, this, &playerwindow::refreshStatistics);

    mainLayout->addLayout(filterLayout);

    // Bouton de rafraîchissement
    QPushButton *refreshBtn = new QPushButton("Refresh Statistics");
    refreshBtn->setStyleSheet("QPushButton { background-color: #4a86e8; color: white; padding: 8px; border-radius: 4px; }"
                             "QPushButton:hover { background-color: #3a76d8; }");
    mainLayout->addWidget(refreshBtn);

    // Configurer le QScrollArea avec le widget de contenu
    scrollArea->setWidget(contentWidget);
    
    // Ajouter le QScrollArea à l'onglet
    QVBoxLayout *tabLayout = new QVBoxLayout(statTab);
    tabLayout->setContentsMargins(0, 0, 0, 0);
    tabLayout->addWidget(scrollArea);

    // Ajouter l'onglet
    ui->tabWidget->addTab(statTab, "Statistics");

    // Connexion du signal pour rafraîchir les statistiques
    connect(refreshBtn, &QPushButton::clicked, this, &playerwindow::refreshStatistics);

    // Initialiser les statistiques
    refreshStatistics();
}

void playerwindow::refreshStatistics()
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

QPixmap playerwindow::generateQRCode(const QString &text)
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
void playerwindow::refreshBestPlayer()
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
                      "JOIN competition c ON p.id_comp = c.id_competition "
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
void playerwindow::updatePlayerInfo(QSqlQuery query, QLabel *nameLabel, QLabel *teamLabel, QLabel *statsLabel, QLabel *imageLabel)
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
                      "JOIN competition c ON p.id_comp = c.id_competition "
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
            
            // Fond dégradé
            QRadialGradient gradient(90, 90, 90);
            gradient.setColorAt(0, QColor(41, 128, 185, 200));  // Bleu clair au centre
            gradient.setColorAt(1, QColor(44, 62, 80, 200));    // Bleu foncé à l'extérieur
            
            painter.setBrush(gradient);
            painter.setPen(QPen(Qt::white, 2));
            painter.drawEllipse(5, 5, 170, 170);
            
            // Initiales du joueur
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
void playerwindow::setupBestPlayerTab()
{
    qDebug() << "Setting up Best Player tab...";
    
    // Créer un nouvel onglet
    QWidget *bestPlayerTab = new QWidget();
    
    // Ajouter un QScrollArea comme conteneur principal
    QScrollArea *scrollArea = new QScrollArea();
    scrollArea->setWidgetResizable(true);
    scrollArea->setFrameShape(QFrame::NoFrame);
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    scrollArea->setStyleSheet(
        "QScrollArea { background: transparent; border: none; }"
        "QScrollBar:vertical {"
        "   background: rgba(0, 0, 0, 0.2);"
        "   width: 8px;"
        "   margin: 0px;"
        "}"
        "QScrollBar::handle:vertical {"
        "   background: rgba(255, 255, 255, 0.3);"
        "   min-height: 20px;"
        "   border-radius: 4px;"
        "}"
        "QScrollBar::add-line:vertical, QScrollBar::sub-line:vertical {"
        "   border: none;"
        "   background: none;"
        "   height: 0px;"
        "}"
    );
    
    // Créer un widget conteneur pour tout le contenu
    QWidget *contentWidget = new QWidget();
    contentWidget->setStyleSheet("background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 #0f2027, stop:0.5 #203a43, stop:1 #2c5364);");
    
    // Utiliser un GridLayout pour un meilleur contrôle du positionnement
    QGridLayout *mainLayout = new QGridLayout(contentWidget);
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
    connect(refreshButton, &QPushButton::clicked, this, &playerwindow::refreshBestPlayer);

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
    
    // Configurer le QScrollArea avec le widget de contenu
    scrollArea->setWidget(contentWidget);
    
    // Ajouter le QScrollArea à l'onglet
    QVBoxLayout *tabLayout = new QVBoxLayout(bestPlayerTab);
    tabLayout->setContentsMargins(0, 0, 0, 0);
    tabLayout->addWidget(scrollArea);
    
    // Ajouter l'onglet à l'interface
    ui->tabWidget->addTab(bestPlayerTab, "Star Player");
    
    // Connecter le combobox pour mettre à jour les données quand la sélection change
    connect(comboBoxCompetition, QOverload<int>::of(&QComboBox::currentIndexChanged), 
            this, &playerwindow::refreshBestPlayer);
    
    // Utiliser QTimer pour charger les données après que l'interface soit affichée
    QTimer::singleShot(500, this, &playerwindow::refreshBestPlayer);
}
void playerwindow::setupTeamOfCompetitionTab()
{
    QWidget *teamOfCompTab = new QWidget();
    
    // Ajouter un QScrollArea comme conteneur principal
    QScrollArea *scrollArea = new QScrollArea();
    scrollArea->setWidgetResizable(true);
    scrollArea->setFrameShape(QFrame::NoFrame);
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    scrollArea->setStyleSheet(
        "QScrollArea { background: transparent; border: none; }"
        "QScrollBar:vertical {"
        "   background: rgba(0, 0, 0, 0.2);"
        "   width: 8px;"
        "   margin: 0px;"
        "}"
        "QScrollBar::handle:vertical {"
        "   background: rgba(255, 255, 255, 0.3);"
        "   min-height: 20px;"
        "   border-radius: 4px;"
        "}"
        "QScrollBar::add-line:vertical, QScrollBar::sub-line:vertical {"
        "   border: none;"
        "   background: none;"
        "   height: 0px;"
        "}"
    );
    
    // Créer un widget conteneur pour tout le contenu
    QWidget *contentWidget = new QWidget();
    contentWidget->setStyleSheet(
        "background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 #0A1931, stop:0.5 #150E56, stop:1 #0E185F);"
    );

    QVBoxLayout *mainLayout = new QVBoxLayout(contentWidget);
    mainLayout->setSpacing(15);
    mainLayout->setContentsMargins(25, 25, 25, 25);

    // En-tête amélioré avec ombre et style moderne
    QFrame *headerFrame = new QFrame();
    headerFrame->setStyleSheet(
        "background-color: rgba(255, 255, 255, 0.05);"
        "border-radius: 15px;"
        "border: 1px solid rgba(255, 255, 255, 0.1);"
        "padding: 15px;"
    );
    
    // Ajouter une ombre à l'en-tête
    QGraphicsDropShadowEffect *shadowEffect = new QGraphicsDropShadowEffect();
    shadowEffect->setBlurRadius(15);
    shadowEffect->setColor(QColor(0, 0, 0, 80));
    shadowEffect->setOffset(0, 5);
    headerFrame->setGraphicsEffect(shadowEffect);
    
    QVBoxLayout *headerLayout = new QVBoxLayout(headerFrame);
    headerLayout->setSpacing(10);
    
    // Titre plus élégant
    QLabel *titleLabel = new QLabel("TEAM OF THE COMPETITION");
    QFont titleFont("Segoe UI", 16, QFont::Bold);
    titleLabel->setFont(titleFont);
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setStyleSheet(
        "color: white; "
        "text-shadow: 2px 2px 4px rgba(0, 0, 0, 0.5);"
        "background: transparent;"
        "border: none;"
        "padding: 5px;"
    );
    headerLayout->addWidget(titleLabel);

    // Sélecteur de compétition avec nouveau design
    QHBoxLayout *selectorLayout = new QHBoxLayout();
    selectorLayout->setSpacing(15);
    
    QLabel *competitionLabel = new QLabel("Competition:");
    competitionLabel->setStyleSheet("color: rgba(255, 255, 255, 0.8); font-size: 14px; background: transparent;");

    QComboBox *teamCompComboBox = new QComboBox();
    teamCompComboBox->setObjectName("teamCompComboBox");
    teamCompComboBox->setStyleSheet(
        "QComboBox { "
        "   background-color: rgba(255, 255, 255, 0.1); "
        "   color: white; "
        "   padding: 8px 15px; "
        "   border: 1px solid rgba(255, 255, 255, 0.2); "
        "   border-radius: 8px; "
        "   font-size: 14px; "
        "   min-height: 25px; "
        "}"
        "QComboBox::drop-down {"
        "   subcontrol-origin: padding;"
        "   subcontrol-position: right;"
        "   width: 25px;"
        "   border-left: 1px solid rgba(255, 255, 255, 0.1);"
        "}"
    );

    QSqlQuery competitionQuery("SELECT comp_name FROM competition");
    while (competitionQuery.next()) {
        QString compName = competitionQuery.value(0).toString();
        teamCompComboBox->addItem(compName);
    }

    QPushButton *refreshButton = new QPushButton("Show");
    refreshButton->setCursor(Qt::PointingHandCursor);
    refreshButton->setStyleSheet(
        "QPushButton { "
        "   background-color: #3498db; "
        "   color: white; "
        "   border-radius: 8px; "
        "   font-size: 13px; "
        "   font-weight: bold; "
        "   border: none; "
        "   padding: 8px 15px; "
        "}"
        "QPushButton:hover { background-color: #2980b9; }"
    );
    
    // MISE EN VALEUR: Bouton de formation avec effet spécial
    QPushButton *showFormationButton = new QPushButton("Show Formation");
    showFormationButton->setCursor(Qt::PointingHandCursor);
    showFormationButton->setStyleSheet(
        "QPushButton { "
        "   background: qlineargradient(x1:0, y1:0, x2:1, y2:0, "
        "                              stop:0 #16a085, stop:1 #2ecc71); "
        "   color: white; "
        "   border-radius: 8px; "
        "   font-size: 14px; "
        "   font-weight: bold; "
        "   border: none; "
        "   padding: 10px 20px; "
        "   min-width: 180px; "
        "   box-shadow: 0 4px 6px rgba(0, 0, 0, 0.1); "
        "}"
        "QPushButton:hover { "
        "   background: qlineargradient(x1:0, y1:0, x2:1, y2:0, "
        "                              stop:0 #1abc9c, stop:1 #27ae60); "
        "}"
    );
    
    // Ajouter une icône au bouton de formation
    QIcon formationIcon = QIcon("C:/Users/wiki/Desktop/ALDAWRY-FOOTBALL/ALDAWRY-FOOTBALL-gestion_joueurs2/ALDAWRY-FOOTBALL-gestion_joueurs2/ALDAWRY-FOOTBALL-gestion_joueurs2/JoueurQ/position.png");
    showFormationButton->setIcon(formationIcon);
    showFormationButton->setIconSize(QSize(20, 20));
    
    // Connecter le bouton au slot qui affichera le popup
    connect(showFormationButton, &QPushButton::clicked, [=]() {
        QString selectedCompetition = teamCompComboBox->currentText();
        FormationPopup *popup = new FormationPopup(selectedCompetition, this);
        popup->setAttribute(Qt::WA_DeleteOnClose);
        popup->exec();
    });

    selectorLayout->addWidget(competitionLabel);
    selectorLayout->addWidget(teamCompComboBox, 1);
    selectorLayout->addWidget(refreshButton);
    selectorLayout->addWidget(showFormationButton);
    headerLayout->addLayout(selectorLayout);
    
    mainLayout->addWidget(headerFrame);

    // SECTION AMÉLIORÉE: Meilleurs joueurs par poste avec design premium
    QFrame *bestPlayersFrame = new QFrame();
    bestPlayersFrame->setStyleSheet(
        "background-color: rgba(20, 30, 48, 0.7);"
        "border-radius: 15px;"
        "border: 1px solid rgba(52, 152, 219, 0.3);"
        "padding: 20px;"
    );
    
    // Ajouter une ombre subtile
    QGraphicsDropShadowEffect *cardsShadow = new QGraphicsDropShadowEffect();
    cardsShadow->setBlurRadius(20);
    cardsShadow->setColor(QColor(0, 0, 0, 60));
    cardsShadow->setOffset(0, 5);
    bestPlayersFrame->setGraphicsEffect(cardsShadow);
    
    QVBoxLayout *bestPlayersLayout = new QVBoxLayout(bestPlayersFrame);
    bestPlayersLayout->setSpacing(20);
    
    QLabel *bestPlayersTitle = new QLabel("TOP PLAYERS BY POSITION");
    bestPlayersTitle->setStyleSheet(
        "color: white; "
        "font-size: 16px; "
        "font-weight: bold; "
        "text-transform: uppercase; "
        "letter-spacing: 2px; "
        "border-bottom: 2px solid rgba(52, 152, 219, 0.5); "
        "padding-bottom: 10px; "
        "background: transparent;"
    );
    bestPlayersTitle->setAlignment(Qt::AlignCenter);
    bestPlayersLayout->addWidget(bestPlayersTitle);
    
    // Grid pour afficher les meilleurs joueurs par poste avec plus d'espace
    QGridLayout *positionsGrid = new QGridLayout();
    positionsGrid->setSpacing(25); // Plus d'espace entre les cartes
    
    // Fonction locale pour créer un widget de position avec design amélioré
    auto createPositionCard = [](const QString &position) {
        QFrame *card = new QFrame();
        card->setObjectName("bestPos_" + position);
        card->setMinimumHeight(220); // Augmenter la hauteur
        card->setStyleSheet(
            "background-color: rgba(52, 152, 219, 0.1);"
            "border-radius: 12px;"
            "border: 1px solid rgba(52, 152, 219, 0.3);"
            "padding: 15px;"
        );
        
        QVBoxLayout *cardLayout = new QVBoxLayout(card);
        cardLayout->setContentsMargins(10, 10, 10, 10);
        cardLayout->setSpacing(10);
        
        // Position en haut avec style distinctif
        QLabel *posLabel = new QLabel(position);
        posLabel->setStyleSheet(
            "color: #3498db; "
            "font-weight: bold; "
            "font-size: 14px; "
            "background-color: rgba(52, 152, 219, 0.1); "
            "border-radius: 10px; "
            "padding: 5px 10px; "
            "border: 1px solid rgba(52, 152, 219, 0.3);"
        );
        posLabel->setAlignment(Qt::AlignCenter);
        
        // Image du joueur plus grande et élégante
     // Dans createPositionCard

QLabel *playerImage = new QLabel();
playerImage->setObjectName("bestPosImg_" + position);
playerImage->setFixedSize(120, 120); // Taille augmentée
playerImage->setScaledContents(false);
playerImage->setAlignment(Qt::AlignCenter);
playerImage->setStyleSheet(
    "background-color: transparent;"
    "border-radius: 60px;" // Moitié de la taille (120/2)
    "border: none;"
);
        // Ajout d'une ombre à l'image
        QGraphicsDropShadowEffect *imageShadow = new QGraphicsDropShadowEffect();
        imageShadow->setBlurRadius(15);
        imageShadow->setColor(QColor(0, 0, 0, 100));
        imageShadow->setOffset(0, 5);
        playerImage->setGraphicsEffect(imageShadow);
        
        // Nom du joueur avec meilleur style
        QLabel *playerName = new QLabel("Loading...");
        playerName->setObjectName("bestPosName_" + position);
        playerName->setStyleSheet(
            "color: white; "
            "font-size: 16px; "
            "font-weight: bold; "
            "background: transparent; "
            "border: none;"
        );
        playerName->setAlignment(Qt::AlignCenter);
        playerName->setWordWrap(true);
        
        // Statistiques du joueur avec meilleur style
        QLabel *playerStats = new QLabel("");
        playerStats->setObjectName("bestPosStats_" + position);
        playerStats->setStyleSheet(
            "color: rgba(255, 255, 255, 0.7); "
            "font-size: 13px; "
            "background: transparent; "
            "border: none;"
        );
        playerStats->setAlignment(Qt::AlignCenter);
        
        cardLayout->addWidget(posLabel, 0, Qt::AlignCenter);
        cardLayout->addWidget(playerImage, 0, Qt::AlignCenter);
        cardLayout->addWidget(playerName);
        cardLayout->addWidget(playerStats);
        
        return card;
    };
    
    // Ajouter les cartes pour chaque position
    QStringList positions = {"Goalkeeper", "Defender", "Midfielder", "Forward"};
    
    for (int i = 0; i < positions.size(); i++) {
        QFrame *posCard = createPositionCard(positions[i]);
        positionsGrid->addWidget(posCard, i / 2, i % 2);
    }
    
    bestPlayersLayout->addLayout(positionsGrid);
    mainLayout->addWidget(bestPlayersFrame);
    
    // Ajouter un panneau d'informations innovant sur l'équipe avec design amélioré
    QFrame *teamInfoFrame = new QFrame();
    teamInfoFrame->setObjectName("teamInfoFrame");
    teamInfoFrame->setStyleSheet(
        "QFrame#teamInfoFrame {"
        "   background-color: rgba(45, 52, 54, 0.7);"
        "   border-radius: 15px;"
        "   border: 1px solid rgba(255, 255, 255, 0.1);"
        "   padding: 20px;"
        "}"
    );
    
    // Ajouter une ombre
    QGraphicsDropShadowEffect *statsShadow = new QGraphicsDropShadowEffect();
    statsShadow->setBlurRadius(15);
    statsShadow->setColor(QColor(0, 0, 0, 60));
    statsShadow->setOffset(0, 5);
    teamInfoFrame->setGraphicsEffect(statsShadow);
    
    QVBoxLayout *teamInfoLayout = new QVBoxLayout(teamInfoFrame);
    
    QLabel *teamInfoTitle = new QLabel("Competition Stats");
    teamInfoTitle->setStyleSheet(
        "color: white; "
        "font-size: 16px; "
        "font-weight: bold; "
        "text-transform: uppercase; "
        "letter-spacing: 2px; "
        "border-bottom: 2px solid rgba(255, 255, 255, 0.2); "
        "padding-bottom: 10px;"
    );
    teamInfoTitle->setAlignment(Qt::AlignCenter);
    
    // Graphiques de statistiques améliorés
    QHBoxLayout *statsLayout = new QHBoxLayout();
    statsLayout->setSpacing(20);
    
    // Widget pour les statistiques de l'équipe
    for (int i = 0; i < 3; i++) {
        QFrame *statFrame = new QFrame();
        statFrame->setStyleSheet(
            "background-color: rgba(255, 255, 255, 0.05);"
            "border-radius: 12px;"
            "padding: 15px;"
            "border: 1px solid rgba(255, 255, 255, 0.1);"
        );
        
        QVBoxLayout *statLayout = new QVBoxLayout(statFrame);
        
        QLabel *statTitle = new QLabel(i == 0 ? "Goals" : (i == 1 ? "Players" : "Teams"));
        statTitle->setStyleSheet("color: rgba(255, 255, 255, 0.7); font-size: 14px; font-weight: bold;");
        statTitle->setAlignment(Qt::AlignCenter);
        
        QLabel *statValue = new QLabel(i == 0 ? "0" : (i == 1 ? "0" : "0"));
        statValue->setObjectName(i == 0 ? "goalsLabel" : (i == 1 ? "playersLabel" : "teamsLabel"));
        statValue->setStyleSheet(
            "color: " + QString(i == 0 ? "#2ecc71" : (i == 1 ? "#3498db" : "#e74c3c")) + ";"
            "font-size: 32px;"
            "font-weight: bold;"
        );
        statValue->setAlignment(Qt::AlignCenter);
        
        statLayout->addWidget(statValue);
        statLayout->addWidget(statTitle);
        
        statsLayout->addWidget(statFrame);
    }
    
    teamInfoLayout->addWidget(teamInfoTitle);
    teamInfoLayout->addLayout(statsLayout);
    
    // Ajouter une description avec style amélioré
    QLabel *descriptionLabel = new QLabel("Click on \"Show Formation\" to see the optimal team formation based on player statistics.");
    descriptionLabel->setStyleSheet(
        "color: rgba(255, 255, 255, 0.6); "
        "font-size: 13px; "
        "font-style: italic; "
        "background-color: rgba(0, 0, 0, 0.2); "
        "padding: 10px; "
        "border-radius: 8px;"
    );
    descriptionLabel->setWordWrap(true);
    descriptionLabel->setAlignment(Qt::AlignCenter);
    
    teamInfoLayout->addWidget(descriptionLabel);
    
    mainLayout->addWidget(teamInfoFrame);
    
    // Configurer le QScrollArea avec le widget de contenu
    scrollArea->setWidget(contentWidget);
    
    // Ajouter le QScrollArea à l'onglet
    QVBoxLayout *tabLayout = new QVBoxLayout(teamOfCompTab);
    tabLayout->setContentsMargins(0, 0, 0, 0);
    tabLayout->addWidget(scrollArea);

    ui->tabWidget->addTab(teamOfCompTab, "Team of Competition");

    // Connexions pour les actions
    connect(refreshButton, &QPushButton::clicked, [=]() {
        displayTeamOfCompetition(teamCompComboBox->currentText());
        updateCompetitionStats(teamCompComboBox->currentText());
        loadBestPlayersByPosition(teamCompComboBox->currentText());
    });

    QTimer::singleShot(500, [=]() {
        if (teamCompComboBox->count() > 0) {
            displayTeamOfCompetition(teamCompComboBox->currentText());
            updateCompetitionStats(teamCompComboBox->currentText());
            loadBestPlayersByPosition(teamCompComboBox->currentText());
        }
    });
}

void playerwindow::loadBestPlayersByPosition(const QString &competitionName)
{
    QStringList positions = {"Goalkeeper", "Defender", "Midfielder", "Forward"};
    
    // Carte de correspondance des positions
    QMap<QString, QStringList> positionMatches;
    positionMatches["Goalkeeper"] = QStringList({"Goalkeeper", "Goal Keeper", "GK", "Keeper"});
    positionMatches["Defender"] = QStringList({"Defender", "Center Back", "Left Back", "Right Back", "Full Back", "CB", "LB", "RB", "Defense"});
    positionMatches["Midfielder"] = QStringList({"Midfielder", "Central Midfielder", "Defensive Midfielder", "Attacking Midfielder", "Left Midfielder", "Right Midfielder", "CM", "CDM", "CAM", "LM", "RM", "Midfield"});
    positionMatches["Forward"] = QStringList({"Forward", "Striker", "Left Winger", "Right Winger", "Center Forward", "CF", "ST", "LW", "RW", "Attack", "Attacker"});
    
    // Préparer une liste pour stocker tous les joueurs et leurs statistiques
    struct PlayerInfo {
        int id;
        QString firstName;
        QString lastName;
        QString teamName;
        int goals;
        int assists;
        int totalScore;
        QByteArray imageData;
        QString actualPosition;
    };
    
    // Liste des joueurs par catégorie de position (carte qui stocke des listes de joueurs)
    QMap<QString, QList<PlayerInfo>> playersByPosition;
    
    // Récupérer tous les joueurs de la compétition
    QSqlQuery allPlayersQuery;
    allPlayersQuery.prepare(
        "SELECT j.id_player, j.first_name, j.last_name, j.position, "
        "j.goals, j.assists, j.img_joueur, e.team_name "
        "FROM joueur j "
        "JOIN equipe e ON j.id_team = e.id_team "
        "JOIN participation p ON e.id_team = p.id_team "
        "JOIN competition c ON p.id_comp = c.id_competition "
        "WHERE c.comp_name = :competition_name "
        "ORDER BY (j.goals + j.assists) DESC"
    );
    allPlayersQuery.bindValue(":competition_name", competitionName);
    
    if (allPlayersQuery.exec()) {
        while (allPlayersQuery.next()) {
            PlayerInfo player;
            player.id = allPlayersQuery.value("id_player").toInt();
            player.firstName = allPlayersQuery.value("first_name").toString();
            player.lastName = allPlayersQuery.value("last_name").toString();
            player.teamName = allPlayersQuery.value("team_name").toString();
            player.goals = allPlayersQuery.value("goals").toInt();
            player.assists = allPlayersQuery.value("assists").toInt();
            player.totalScore = player.goals + player.assists; // Utiliser goals + assists comme critère
            player.imageData = allPlayersQuery.value("img_joueur").toByteArray();
            player.actualPosition = allPlayersQuery.value("position").toString();
            
            // Déterminer la catégorie de position pour ce joueur
            QString positionCategory = "";
            for (auto it = positionMatches.constBegin(); it != positionMatches.constEnd(); ++it) {
                const QString &category = it.key();
                const QStringList &keywords = it.value();
                
                for (const QString &keyword : keywords) {
                    if (player.actualPosition.contains(keyword, Qt::CaseInsensitive)) {
                        positionCategory = category;
                        break;
                    }
                }
                
                if (!positionCategory.isEmpty()) break;
            }
            
            // Si aucune correspondance n'est trouvée, utiliser la première partie de la position
            if (positionCategory.isEmpty()) {
                if (player.actualPosition.contains("Goal", Qt::CaseInsensitive)) {
                    positionCategory = "Goalkeeper";
                } else if (player.actualPosition.contains("Def", Qt::CaseInsensitive) || 
                           player.actualPosition.contains("Back", Qt::CaseInsensitive)) {
                    positionCategory = "Defender";
                } else if (player.actualPosition.contains("Mid", Qt::CaseInsensitive)) {
                    positionCategory = "Midfielder";
                } else {
                    positionCategory = "Forward"; // Par défaut
                }
            }
            
            // Ajouter le joueur à sa catégorie
            playersByPosition[positionCategory].append(player);
        }
        
        // Trier chaque liste par score total (goals + assists)
        for (auto it = playersByPosition.begin(); it != playersByPosition.end(); ++it) {
            std::sort(it.value().begin(), it.value().end(), [](const PlayerInfo &a, const PlayerInfo &b) {
                return a.totalScore > b.totalScore; // Tri décroissant
            });
        }
        
        // Maintenant mettre à jour les widgets pour chaque position
        for (const QString &position : positions) {
            QLabel *nameLabel = ui->tabWidget->findChild<QLabel*>("bestPosName_" + position);
            QLabel *statsLabel = ui->tabWidget->findChild<QLabel*>("bestPosStats_" + position);
            QLabel *imageLabel = ui->tabWidget->findChild<QLabel*>("bestPosImg_" + position);
            
            if (!nameLabel || !statsLabel || !imageLabel) {
                qDebug() << "Labels non trouvés pour la position:" << position;
                continue;
            }
            
            // Vérifier si nous avons des joueurs pour cette position
            if (playersByPosition.contains(position) && !playersByPosition[position].isEmpty()) {
                PlayerInfo bestPlayer = playersByPosition[position].first();
                
                // Mettre à jour le nom
                nameLabel->setText(bestPlayer.firstName + " " + bestPlayer.lastName);
                
                // Mettre à jour les stats avec Rich Text
                statsLabel->setText(QString("<span style='color:#f39c12;'>%1</span> | <span style='color:#2ecc71;'>%2 G, %3 A (%4)</span>")
                                   .arg(bestPlayer.teamName)
                                   .arg(bestPlayer.goals)
                                   .arg(bestPlayer.assists)
                                   .arg(bestPlayer.totalScore));
                statsLabel->setTextFormat(Qt::RichText);
                
                // Mettre à jour l'image
                if (!bestPlayer.imageData.isEmpty()) {
                    QPixmap playerPix;
                    if (playerPix.loadFromData(bestPlayer.imageData)) {
                        // Créer un masque circulaire
                        QPixmap circularPix(120, 120);
                        circularPix.fill(Qt::transparent);
                        
                        QPainter painter(&circularPix);
                        painter.setRenderHint(QPainter::Antialiasing);
                        painter.setRenderHint(QPainter::SmoothPixmapTransform);
                        
                        // Créer un chemin circulaire pour le masque
                        QPainterPath path;
                        path.addEllipse(0, 0, 120, 120);
                        painter.setClipPath(path);
                        
                        // Dessiner l'image
                        QPixmap scaledPix = playerPix.scaled(120, 120, Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);
                        
                        // Centrer l'image
                        int x = (scaledPix.width() - 120) / 2;
                        int y = (scaledPix.height() - 120) / 2;
                        if (x < 0) x = 0;
                        if (y < 0) y = 0;
                        
                        painter.drawPixmap(0, 0, scaledPix, x, y, 120, 120);
                        
                        imageLabel->setPixmap(circularPix);
                        imageLabel->setStyleSheet("background-color: transparent; border-radius: 60px; border: none;");
                    }
                } else {
                    // Image avec initiales
                    QPixmap defaultPix(120, 120);
                    defaultPix.fill(Qt::transparent);
                    
                    QPainter painter(&defaultPix);
                    painter.setRenderHint(QPainter::Antialiasing);
                    
                    // Fond gris neutre
                    painter.setPen(Qt::NoPen);
                    painter.setBrush(QColor(150, 150, 150, 200));
                    painter.drawEllipse(0, 0, 120, 120);
                    
                    // Initiales
                    painter.setPen(Qt::white);
                    QFont font("Arial", 36, QFont::Bold);
                    painter.setFont(font);
                    
                    QString initials;
                    if (!bestPlayer.firstName.isEmpty()) initials += bestPlayer.firstName[0];
                    if (!bestPlayer.lastName.isEmpty()) initials += bestPlayer.lastName[0];
                    
                    painter.drawText(QRect(0, 0, 120, 120), Qt::AlignCenter, initials);
                    
                    imageLabel->setPixmap(defaultPix);
                    imageLabel->setStyleSheet("background-color: transparent; border-radius: 60px; border: none;");
                }
            } else {
                // Afficher "No player found" si aucun joueur n'est disponible pour cette position
                nameLabel->setText("No player found");
                statsLabel->setText("No data available");
                
                // Image par défaut
                QPixmap defaultPix(120, 120);
                defaultPix.fill(Qt::transparent);
                
                QPainter painter(&defaultPix);
                painter.setRenderHint(QPainter::Antialiasing);
                
                // Fond gris neutre
                painter.setPen(Qt::NoPen);
                painter.setBrush(QColor(150, 150, 150, 200));
                painter.drawEllipse(0, 0, 120, 120);
                
                // Texte position
                painter.setPen(Qt::white);
                QFont font("Arial", 20, QFont::Bold);
                painter.setFont(font);
                painter.drawText(QRect(0, 0, 120, 120), Qt::AlignCenter, position.left(4));
                
                imageLabel->setPixmap(defaultPix);
                imageLabel->setStyleSheet("background-color: transparent; border-radius: 60px; border: none;");
            }
        }
    } else {
        qDebug() << "Erreur SQL:" << allPlayersQuery.lastError().text();
        
        // Afficher l'erreur sur l'interface
        for (const QString &position : positions) {
            QLabel *nameLabel = ui->tabWidget->findChild<QLabel*>("bestPosName_" + position);
            QLabel *statsLabel = ui->tabWidget->findChild<QLabel*>("bestPosStats_" + position);
            QLabel *imageLabel = ui->tabWidget->findChild<QLabel*>("bestPosImg_" + position);
            
            if (nameLabel) nameLabel->setText("SQL Error");
            if (statsLabel) statsLabel->setText(allPlayersQuery.lastError().text().left(30) + "...");
            
            if (imageLabel) {
                QPixmap errorPix(120, 120);
                errorPix.fill(Qt::transparent);
                
                QPainter painter(&errorPix);
                painter.setRenderHint(QPainter::Antialiasing);
                
                // Fond rouge pour l'erreur
                painter.setPen(Qt::NoPen);
                painter.setBrush(QColor(200, 60, 60, 200));
                painter.drawEllipse(0, 0, 120, 120);
                
                // Symbole d'erreur
                painter.setPen(QPen(Qt::white, 4));
                painter.drawLine(40, 40, 80, 80);
                painter.drawLine(40, 80, 80, 40);
                
                imageLabel->setPixmap(errorPix);
                imageLabel->setStyleSheet("background-color: transparent; border-radius: 60px; border: none;");
            }
        }
    }
}
// Ajouter cette nouvelle méthode dans la classe playerwindow
void playerwindow::updateCompetitionStats(const QString &competitionName)
{
    // Rechercher les labels dans l'interface
    QLabel *goalsLabel = ui->tabWidget->findChild<QLabel*>("goalsLabel");
    QLabel *playersLabel = ui->tabWidget->findChild<QLabel*>("playersLabel");
    QLabel *teamsLabel = ui->tabWidget->findChild<QLabel*>("teamsLabel");
    
    if (!goalsLabel || !playersLabel || !teamsLabel) {
        qDebug() << "Labels de statistiques non trouvés";
        return;
    }
    
    // Requête SQL pour obtenir les statistiques de la compétition
    QSqlQuery query;
    
    // Total des buts
    query.prepare(
        "SELECT SUM(j.goals) as total_goals "
        "FROM joueur j "
        "JOIN equipe e ON j.id_team = e.id_team "
        "JOIN participation p ON e.id_team = p.id_team "
        "JOIN competition c ON p.id_comp = c.id_competition "
        "WHERE c.comp_name = :competition_name"
    );
    query.bindValue(":competition_name", competitionName);
    
    if (query.exec() && query.next()) {
        int totalGoals = query.value("total_goals").toInt();
        goalsLabel->setText(QString::number(totalGoals));
    } else {
        goalsLabel->setText("0");
    }
    
    // Nombre de joueurs
    query.prepare(
        "SELECT COUNT(DISTINCT j.id_player) as total_players "
        "FROM joueur j "
        "JOIN equipe e ON j.id_team = e.id_team "
        "JOIN participation p ON e.id_team = p.id_team "
        "JOIN competition c ON p.id_comp = c.id_competition "
        "WHERE c.comp_name = :competition_name"
    );
    query.bindValue(":competition_name", competitionName);
    
    if (query.exec() && query.next()) {
        int totalPlayers = query.value("total_players").toInt();
        playersLabel->setText(QString::number(totalPlayers));
    } else {
        playersLabel->setText("0");
    }
    
    // Nombre d'équipes
    query.prepare(
        "SELECT COUNT(DISTINCT e.id_team) as total_teams "
        "FROM equipe e "
        "JOIN participation p ON e.id_team = p.id_team "
        "JOIN competition c ON p.id_comp = c.id_competition "
        "WHERE c.comp_name = :competition_name"
    );
    query.bindValue(":competition_name", competitionName);
    
    if (query.exec() && query.next()) {
        int totalTeams = query.value("total_teams").toInt();
        teamsLabel->setText(QString::number(totalTeams));
    } else {
        teamsLabel->setText("0");
    }
}
// Modification de createPositionWidget pour enlever les cercles bleus autour des images
QFrame* playerwindow::createPositionWidget(const QString &position)
{
    QFrame *posFrame = new QFrame();
    posFrame->setObjectName("position_" + position);
    posFrame->setFixedSize(150, 150); // Taille légèrement réduite (était 160x160)
    posFrame->setStyleSheet(
        "background-color: rgba(255, 255, 255, 0.3);"
        "border-radius: 75px;" // Rayon ajusté pour rester circulaire
        "border: 3px solid white;" // Bordure blanche
    );

    QVBoxLayout *posLayout = new QVBoxLayout(posFrame);
    posLayout->setContentsMargins(10, 10, 10, 10);

    // Image du joueur (à remplir dynamiquement) - SUPPRESSION DU FOND BLEU
    QLabel *playerImage = new QLabel();
    playerImage->setObjectName("image_" + position);
    playerImage->setFixedSize(120, 120); // Taille légèrement réduite (était 130x130)
    playerImage->setAlignment(Qt::AlignCenter);
    playerImage->setStyleSheet(
        "background-color: transparent;" // SUPPRESSION DU FOND BLEU
        "color: white;"
        "font-size: 32px;"
        "font-weight: bold;"
        "border-radius: 60px;" // Rayon ajusté
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
// Fonction pour créer un widget de position de joueur
/*QFrame* playerwindow::createPositionWidget(const QString &position)
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
*/
// Implémenter l'événement de clic sur une position
bool playerwindow::eventFilter(QObject *watched, QEvent *event)
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
        painter.drawRect(goalBoxX, field->height() - goalBoxHeight - 30, goalBoxHeight, goalBoxHeight);
        
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
    
    return playerwindow::eventFilter(watched, event);
}


void playerwindow::displayPlayerDetails(int playerId, const QString &position)
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

void playerwindow::displayTeamOfCompetition(const QString &competitionName)
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
        "JOIN competition c ON p.id_comp = c.id_competition "
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
QJsonObject playerwindow::collectPlayerData(int playerId) {
    QJsonObject data;
    QSqlQuery query;
    query.prepare("SELECT j.*, e.team_name "
                  "FROM joueur j "
                  "JOIN equipe e ON j.id_team = e.id_team "
                  "WHERE j.id_player = :id");
    query.bindValue(":id", playerId);
    
    if (query.exec() && query.next()) {
        data["id_player"] = query.value("id_player").toInt();
        data["first_name"] = query.value("first_name").toString();
        data["last_name"] = query.value("last_name").toString();
        data["team_name"] = query.value("team_name").toString();
        data["position"] = query.value("position").toString();
        data["jersey_nb"] = query.value("jersey_nb").toInt();
        data["date_of_birth"] = query.value("date_of_birth").toDate().toString("yyyy-MM-dd");
        data["nationality"] = query.value("nationality").toString();
        data["goals"] = query.value("goals").toInt();
        data["assists"] = query.value("assists").toInt();
        data["yellow_card"] = query.value("yellow_card").toInt();
        data["red_card"] = query.value("red_card").toInt();
        data["injured"] = query.value("injured").toInt() == 1;
        int status = query.value("status").toInt();
        QString statusText;
        switch(status) {
            case 0: statusText = "Active"; break;
            case 1: statusText = "Injured"; break;
            case 2: statusText = "Suspended"; break;
            case 3: statusText = "Transferred"; break;
            default: statusText = "Unknown";
        }
        data["status"] = statusText;
    } else {
        qDebug() << "Error collecting player data:" << query.lastError().text();
    }
    return data;
}
QString playerwindow::generateReport(const QJsonObject &data) {
    qDebug() << "Entering generateReport"; // Log pour vérifier
    
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    QUrl url("https://api.cohere.ai/v1/generate");
    QNetworkRequest request(url);
    
    // Configurer les en-têtes
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    QString apiKey = "GmzfYDb3sg1arIayokcJi2GiTi49XxgzfcxRV0Ff"; // Remplace par ta vraie clé Cohere
    qDebug() << "API Key used:" << apiKey;
    
    if (apiKey.isEmpty()) {
        qDebug() << "Error: API key not set";
        QMessageBox::critical(this, "Configuration Error", "Cohere API key is not set.");
        return "Error: API key not configured.";
    }
    request.setRawHeader("Authorization", ("Bearer " + apiKey.trimmed()).toUtf8());
    
    // Créer le prompt
    QString prompt = QString("Generate a detailed performance report for a football player with the following details:\n"
                            "Name: %1 %2\n"
                            "Team: %3\n"
                            "Position: %4\n"
                            "Jersey Number: %5\n"
                            "Goals: %6\n"
                            "Assists: %7\n"
                            "Yellow Cards: %8\n"
                            "Red Cards: %9\n"
                            "Injured: %10\n"
                            "Status: %11\n"
                            "Provide insights on their performance, strengths, and areas for improvement.")
                            .arg(data["first_name"].toString())
                            .arg(data["last_name"].toString())
                            .arg(data["team_name"].toString())
                            .arg(data["position"].toString())
                            .arg(data["jersey_nb"].toInt())
                            .arg(data["goals"].toInt())
                            .arg(data["assists"].toInt())
                            .arg(data["yellow_card"].toInt())
                            .arg(data["red_card"].toInt())
                            .arg(data["injured"].toBool() ? "Yes" : "No")
                            .arg(data["status"].toString());
    
    QJsonObject payload;
    payload["prompt"] = prompt;
    payload["max_tokens"] = 200; // Limite pour un rapport court
    QJsonDocument doc(payload);
    QByteArray dataPayload = doc.toJson();
    qDebug() << "Request payload:" << QString(dataPayload);
    
    // Envoyer la requête
    QNetworkReply *reply = manager->post(request, dataPayload);
    
    // Attendre la réponse
    QEventLoop loop;
    connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();
    
    // Traiter la réponse
    QString reportText;
    if (reply->error() == QNetworkReply::NoError) {
        QByteArray responseData = reply->readAll();
        qDebug() << "Raw API response:" << responseData;
        QJsonDocument responseDoc = QJsonDocument::fromJson(responseData);
        if (!responseDoc.isNull()) {
            QJsonObject responseObj = responseDoc.object();
            QJsonArray generations = responseObj["generations"].toArray();
            if (!generations.isEmpty()) {
                reportText = generations[0].toObject()["text"].toString();
            } else {
                reportText = "Error: Empty response from API.";
            }
        } else {
            reportText = "Error: Invalid JSON response.";
        }
    } else {
        reportText = "Error generating report: " + reply->errorString();
        qDebug() << "API error:" << reply->errorString();
        QMessageBox::warning(this, "API Error", reportText);
    }
    
    reply->deleteLater();
    return reportText;
}
void playerwindow::onGenerateReportClicked() {
    // Vérifier si un joueur est sélectionné
    if (!validateTableSelection()) {
        QMessageBox::warning(this, "Selection Error", "Please select a player.");
        return;
    }
    
    // Obtenir l'ID du joueur sélectionné
    int row = ui->tableWidget->selectionModel()->selectedRows().first().row();
    int playerId = ui->tableWidget->item(row, 0)->text().toInt();
    
    // Collecter les données
    QJsonObject playerData = collectPlayerData(playerId);
    if (playerData.isEmpty()) {
        QMessageBox::warning(this, "Error", "Could not collect player data.");
        return;
    }
    
    // Générer le rapport
    QString reportText = generateReport(playerData);
    
    // Afficher le rapport
    displayReport(reportText);
}
void playerwindow::displayReport(const QString &reportText) {
    // Créer un widget pour afficher le rapport
    QWidget *reportTab = new QWidget();
    
    // Ajouter un QScrollArea comme conteneur principal pour rendre TOUT l'onglet scrollable
    QScrollArea *scrollArea = new QScrollArea();
    scrollArea->setWidgetResizable(true);
    scrollArea->setFrameShape(QFrame::NoFrame);
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    scrollArea->setStyleSheet(
        "QScrollArea { background: transparent; border: none; }"
        "QScrollBar:vertical {"
        "   background: rgba(0, 0, 0, 0.2);"
        "   width: 10px;"
        "   margin: 0px;"
        "}"
        "QScrollBar::handle:vertical {"
        "   background: rgba(52, 152, 219, 0.7);"
        "   min-height: 20px;"
        "   border-radius: 5px;"
        "}"
        "QScrollBar::add-line:vertical, QScrollBar::sub-line:vertical {"
        "   border: none;"
        "   background: none;"
        "   height: 0px;"
        "}"
    );
    
    // Contenu qui sera scrollable
    QWidget *contentWidget = new QWidget();
    contentWidget->setStyleSheet("background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 #0A2647, stop:0.5 #144272, stop:1 #205295);");
    
    QVBoxLayout *mainLayout = new QVBoxLayout(contentWidget);
    mainLayout->setContentsMargins(20, 20, 20, 20);
    mainLayout->setSpacing(15);
    
    // En-tête avec le logo personnalisé
    QFrame *headerFrame = new QFrame();
    headerFrame->setFixedHeight(70);
    headerFrame->setStyleSheet(
        "QFrame {"
        "    background-color: rgba(255, 255, 255, 0.15);"
        "    border-radius: 15px;"
        "    border: 1px solid rgba(255, 255, 255, 0.3);"
        "}"
    );
    QHBoxLayout *headerLayout = new QHBoxLayout(headerFrame);
    headerLayout->setContentsMargins(15, 5, 15, 5);
    
    // Logo personnalisé
    QLabel *logoLabel = new QLabel();
    QString logoPath = "C:/Users/wiki/Desktop/ALDAWRY-FOOTBALL/ALDAWRY-FOOTBALL-gestion_joueurs2/ALDAWRY-FOOTBALL-gestion_joueurs2/ALDAWRY-FOOTBALL-gestion_joueurs2/JoueurQ/logo football.png";
    QPixmap logoPix(logoPath);
    
    if (!logoPix.isNull()) {
        // Redimensionner le logo si nécessaire
        logoPix = logoPix.scaled(50, 50, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        logoLabel->setPixmap(logoPix);
    } else {
        // Utiliser un logo de secours si le fichier n'est pas trouvé
        QPixmap backupLogo(50, 50);
        backupLogo.fill(Qt::transparent);
        QPainter painter(&backupLogo);
        painter.setRenderHint(QPainter::Antialiasing);
        
        QRadialGradient gradient(25, 25, 25);
        gradient.setColorAt(0, QColor(255, 215, 0));
        gradient.setColorAt(1, QColor(230, 126, 34));
        
        painter.setBrush(gradient);
        painter.setPen(QPen(Qt::white, 2));
        painter.drawEllipse(5, 5, 40, 40);
        painter.setPen(QPen(Qt::white, 2));
        painter.drawText(QRect(0, 0, 50, 50), Qt::AlignCenter, "AL\nD");
        painter.end();
        
        logoLabel->setPixmap(backupLogo);
        qDebug() << "Logo not found at:" << logoPath;
    }
    
    logoLabel->setMaximumWidth(50);
    logoLabel->setMaximumHeight(50);
    
    // Texte de titre
    QVBoxLayout *titleLayout = new QVBoxLayout();
    titleLayout->setSpacing(2);
    
    QLabel *titleLabel = new QLabel("PLAYER PERFORMANCE ANALYSIS");
    titleLabel->setStyleSheet(
        "font-size: 18px;"
        "font-weight: bold;"
        "color: white;"
        "letter-spacing: 1px;"
        "text-shadow: 1px 1px 2px rgba(0, 0, 0, 0.5);"
    );
    
    QLabel *subtitleLabel = new QLabel("AI-Powered Insights");
    subtitleLabel->setStyleSheet(
        "font-size: 12px;"
        "font-style: italic;"
        "color: #9DE5FF;"
    );
    
    titleLayout->addWidget(titleLabel);
    titleLayout->addWidget(subtitleLabel);
    
    headerLayout->addWidget(logoLabel);
    headerLayout->addLayout(titleLayout, 1);
    
    mainLayout->addWidget(headerFrame);
    
    // Corps du rapport
    QFrame *reportFrame = new QFrame();
    reportFrame->setStyleSheet(
        "QFrame {"
        "    background-color: rgba(255, 255, 255, 0.92);"
        "    border-radius: 15px;"
        "    border: none;"
        "}"
    );
    
    // Ombre légère
    QGraphicsDropShadowEffect *shadowEffect = new QGraphicsDropShadowEffect();
    shadowEffect->setBlurRadius(10);
    shadowEffect->setColor(QColor(0, 0, 0, 50));
    shadowEffect->setOffset(0, 2);
    reportFrame->setGraphicsEffect(shadowEffect);
    
    QVBoxLayout *reportLayout = new QVBoxLayout(reportFrame);
    reportLayout->setContentsMargins(0, 0, 0, 0);
    
    // En-tête du rapport
    QFrame *reportHeaderFrame = new QFrame();
    reportHeaderFrame->setFixedHeight(40);
    reportHeaderFrame->setStyleSheet(
        "background-color: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 #3498db, stop:1 #2980b9);"
        "border-top-left-radius: 15px;"
        "border-top-right-radius: 15px;"
        "border-bottom-left-radius: 0px;"
        "border-bottom-right-radius: 0px;"
    );
    QHBoxLayout *reportHeaderLayout = new QHBoxLayout(reportHeaderFrame);
    reportHeaderLayout->setContentsMargins(15, 0, 15, 0);
    
    QLabel *reportHeaderLabel = new QLabel("OFFICIAL PERFORMANCE REPORT");
    reportHeaderLabel->setStyleSheet(
        "color: white;"
        "font-size: 14px;"
        "font-weight: bold;"
    );
    
    QLabel *dateLabel = new QLabel(QDate::currentDate().toString("dd MMM yyyy"));
    dateLabel->setStyleSheet("color: white; font-size: 12px;");
    
    reportHeaderLayout->addWidget(reportHeaderLabel);
    reportHeaderLayout->addWidget(dateLabel, 0, Qt::AlignRight);
    
    // Zone de texte du rapport
    QTextEdit *reportTextEdit = new QTextEdit();
    reportTextEdit->setReadOnly(true);
    reportTextEdit->setFrameStyle(QFrame::NoFrame);
    reportTextEdit->setMinimumHeight(400);
    
    reportTextEdit->setStyleSheet(
        "QTextEdit {"
        "   background-color: white;"
        "   color: #333333;"
        "   font-size: 16px;"
        "   line-height: 1.6;"
        "   padding: 20px 25px;"
        "   border: none;"
        "}"
        // Styles de la barre de défilement maintenant gérés par le QScrollArea parent
    );
    
    // Formater le texte du rapport
    QString formattedText = "<!DOCTYPE HTML><html><body style='font-family: Arial, sans-serif;'>";
    formattedText += "<h2 style='color: #2c3e50; border-bottom: 1px solid #ecf0f1; padding-bottom: 10px; font-size: 24px;'>Player Assessment</h2>";
    
    // Segmenter le rapport en paragraphes et ajouter du style
    QStringList paragraphs = reportText.split("\n\n");
    for (const QString &paragraph : paragraphs) {
        if (paragraph.trimmed().isEmpty()) continue;
        
        if (paragraph.contains("strengths", Qt::CaseInsensitive) || 
            paragraph.contains("strong points", Qt::CaseInsensitive)) {
            formattedText += "<h3 style='color: #27ae60; margin-top: 20px; font-size: 20px;'>Strengths Analysis</h3>";
        } else if (paragraph.contains("weaknesses", Qt::CaseInsensitive) || 
                   paragraph.contains("areas for improvement", Qt::CaseInsensitive) ||
                   paragraph.contains("could improve", Qt::CaseInsensitive)) {
            formattedText += "<h3 style='color: #e67e22; margin-top: 20px; font-size: 20px;'>Areas for Improvement</h3>";
        } else if (paragraph.contains("conclusion", Qt::CaseInsensitive) || 
                  paragraph.contains("summary", Qt::CaseInsensitive) ||
                  paragraph.contains("overall", Qt::CaseInsensitive)) {
            formattedText += "<h3 style='color: #2980b9; margin-top: 20px; font-size: 20px;'>Overall Assessment</h3>";
        }
        
        // Mettre en évidence les mots clés
        QString enhancedParagraph = paragraph;
        enhancedParagraph.replace("goals", "<span style='color: #3498db; font-weight: bold;'>goals</span>");
        enhancedParagraph.replace("assists", "<span style='color: #2ecc71; font-weight: bold;'>assists</span>");
        enhancedParagraph.replace("cards", "<span style='color: #e74c3c; font-weight: bold;'>cards</span>");
        enhancedParagraph.replace("yellow card", "<span style='color: #f39c12; font-weight: bold;'>yellow card</span>");
        enhancedParagraph.replace("red card", "<span style='color: #c0392b; font-weight: bold;'>red card</span>");
        enhancedParagraph.replace("performance", "<span style='color: #8e44ad; font-weight: bold;'>performance</span>");
        
        formattedText += "<p style='text-align: justify; margin: 12px 0; font-size: 16px; line-height: 1.6;'>" + enhancedParagraph + "</p>";
    }
    
    formattedText += "<div style='text-align: center; color: #bdc3c7; padding: 20px 0;'>--- End of Report ---</div>";
    formattedText += "</body></html>";
    
    reportTextEdit->setHtml(formattedText);
    
    // Pied de page
    QFrame *footerFrame = new QFrame();
    footerFrame->setFixedHeight(30);
    footerFrame->setStyleSheet(
        "background-color: #ecf0f1;"
        "border-bottom-left-radius: 15px;"
        "border-bottom-right-radius: 15px;"
        "border-top: 1px solid #bdc3c7;"
    );
    QHBoxLayout *footerLayout = new QHBoxLayout(footerFrame);
    footerLayout->setContentsMargins(15, 0, 15, 0);
    
    QLabel *disclaimerLabel = new QLabel("© AL DAWRY Football Management");
    disclaimerLabel->setStyleSheet("color: #7f8c8d; font-size: 10px; font-style: italic;");
    
    footerLayout->addWidget(disclaimerLabel, 0, Qt::AlignCenter);
    
    // Assembler le corps du rapport
    reportLayout->addWidget(reportHeaderFrame);
    reportLayout->addWidget(reportTextEdit, 1);
    reportLayout->addWidget(footerFrame);
    
    mainLayout->addWidget(reportFrame, 1);
    
    // Bouton de fermeture
    QPushButton *closeBtn = new QPushButton("Close Report");
    closeBtn->setCursor(Qt::PointingHandCursor);
    closeBtn->setFixedSize(120, 30);
    closeBtn->setStyleSheet(
        "QPushButton {"
        "   background-color: #7f8c8d;"
        "   color: white;"
        "   border: none;"
        "   border-radius: 5px;"
        "   font-weight: bold;"
        "   font-size: 12px;"
        "   padding: 5px 10px;"
        "}"
        "QPushButton:hover { background-color: #95a5a6; }"
    );
    
    mainLayout->addWidget(closeBtn, 0, Qt::AlignRight);
    
    // Ajouter de l'espace en bas pour assurer un défilement complet
    mainLayout->addSpacing(10);
    
    // Configurer le QScrollArea avec le widget de contenu
    scrollArea->setWidget(contentWidget);
    
    // Ajouter le QScrollArea à l'onglet
    QVBoxLayout *tabLayout = new QVBoxLayout(reportTab);
    tabLayout->setContentsMargins(0, 0, 0, 0);
    tabLayout->addWidget(scrollArea);
    
    // Ajouter l'onglet et passer à celui-ci
    int tabIndex = ui->tabWidget->addTab(reportTab, "Player Report");
    ui->tabWidget->setCurrentIndex(tabIndex);
    
    // Connexion pour fermer l'onglet
    connect(closeBtn, &QPushButton::clicked, [=]() {
        int idx = ui->tabWidget->indexOf(reportTab);
        if (idx != -1) {
            ui->tabWidget->removeTab(idx);
        }
    });
    
    // S'assurer que le scrollArea commence au début
    QTimer::singleShot(100, [=]() {
        scrollArea->verticalScrollBar()->setValue(0);
    });
}
