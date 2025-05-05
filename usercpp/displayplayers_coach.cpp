#include "../userheaders/displayplayers_coach.h"
#include "ui_displayplayers_coach.h"
#include "../userheaders/sessionmanager.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QMessageBox>
#include <QVBoxLayout>
#include <QScrollArea>
#include <QLabel>
#include <QFrame>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QPainter>
#include <QPainterPath>
#include <QPushButton>
#include <QIcon>
#include <QPdfWriter>
#include <QFileDialog>
#include <QFontMetrics>
#include <QPen>
#include <QBrush>
#include <QGraphicsDropShadowEffect>
#include <QTextEdit>
#include <QTimer>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QEventLoop>
#include <QScrollBar> // Added for QScrollBar
#include "../userheaders/qrcodegen.hpp"

displayplayers_coach::displayplayers_coach(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::displayplayers_coach)
{
    ui->setupUi(this);
    // Connect comboBoxTri for sorting
    connect(ui->comboBoxTri, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &displayplayers_coach::on_comboBoxTri_currentIndexChanged);
    // Populate comboBoxTri with sorting options
    ui->comboBoxTri->addItems({"Default", "First Name", "Last Name", "Position", "Jersey Number"});
    // Connect tableWidget selection
    connect(ui->tableWidget, &QTableWidget::itemSelectionChanged,
            this, &displayplayers_coach::on_tableWidget_itemSelectionChanged);
    connect(ui->lineEdit_10, &QLineEdit::textChanged,
            this, &displayplayers_coach::onSearchTextChanged);
    ui->lineEdit_10->setPlaceholderText("Search players by name, nationality, position...");
    loadPlayers(); // Load players when the window opens
}

displayplayers_coach::~displayplayers_coach()
{
    delete ui;
}
void displayplayers_coach::onSearchTextChanged(const QString &text)
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


    } else {
        qDebug() << "Search query error: " << query.lastError().text();
    }
}
void displayplayers_coach::loadPlayers()
{
    // Get the current coach from SessionManager
    const Employee& currentUser = SessionManager::instance().getCurrentUser();
    int coachId = currentUser.getId();
    QString role = currentUser.getRole().trimmed().toLower();

    if (role != "coach") {
        qDebug() << "Error: Non-coach user attempted to access player display.";
        QMessageBox::critical(this, "Access Error", "Only coaches can view players.");
        close();
        return;
    }

    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isOpen()) {
        qDebug() << "Database connection is not open!";
        QMessageBox::critical(this, "Database Error", "Database connection is not open.");
        return;
    }

    // Fetch the team ID for the coach
    QSqlQuery teamQuery;
    teamQuery.prepare("SELECT ID_TEAM FROM HOTSTUFF.COACH WHERE ID_EMP = :coachId");
    teamQuery.bindValue(":coachId", coachId);

    if (!teamQuery.exec()) {
        qDebug() << "Failed to fetch team ID:" << teamQuery.lastError().text();
        QMessageBox::critical(this, "Database Error", "Failed to fetch team data: " + teamQuery.lastError().text());
        return;
    }

    if (!teamQuery.next()) {
        qDebug() << "No team found for coach ID:" << coachId;
        QMessageBox::warning(this, "No Team", "You are not assigned to any team.");
        return;
    }

    int teamId = teamQuery.value(0).toInt();
    qDebug() << "Coach ID:" << coachId << "is assigned to Team ID:" << teamId;

    // Fetch players for the team with team name
    QSqlQuery playerQuery;
    playerQuery.prepare(
        "SELECT j.ID_PLAYER, j.FIRST_NAME, j.LAST_NAME, j.POSITION, e.TEAM_NAME, j.JERSEY_NB, j.STATUS "
        "FROM HOTSTUFF.JOUEUR j "
        "JOIN HOTSTUFF.EQUIPE e ON j.ID_TEAM = e.ID_TEAM "
        "WHERE j.ID_TEAM = :teamId");
    playerQuery.bindValue(":teamId", teamId);

    if (!playerQuery.exec()) {
        qDebug() << "Failed to fetch players:" << playerQuery.lastError().text();
        QMessageBox::critical(this, "Database Error", "Failed to fetch players: " + playerQuery.lastError().text());
        return;
    }

    // Configure tableWidget
    ui->tableWidget->clearContents();
    ui->tableWidget->setRowCount(0);
    ui->tableWidget->setColumnCount(7);
    ui->tableWidget->setHorizontalHeaderLabels({
        "ID", "First Name", "Last Name", "Position", "Team", "Jersey", "Status"
    });
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

    // Populate table with players
    int row = 0;
    while (playerQuery.next()) {
        ui->tableWidget->insertRow(row);
        ui->tableWidget->setItem(row, 0, new QTableWidgetItem(playerQuery.value("ID_PLAYER").toString()));
        ui->tableWidget->setItem(row, 1, new QTableWidgetItem(playerQuery.value("FIRST_NAME").toString()));
        ui->tableWidget->setItem(row, 2, new QTableWidgetItem(playerQuery.value("LAST_NAME").toString()));
        ui->tableWidget->setItem(row, 3, new QTableWidgetItem(playerQuery.value("POSITION").toString()));
        ui->tableWidget->setItem(row, 4, new QTableWidgetItem(playerQuery.value("TEAM_NAME").toString()));
        ui->tableWidget->setItem(row, 5, new QTableWidgetItem(playerQuery.value("JERSEY_NB").toString()));

        // Convert integer status to text
        int status = playerQuery.value("STATUS").toInt();
        QString statusText;
        switch (status) {
            case 0: statusText = "Active"; break;
            case 1: statusText = "Injured"; break;
            case 2: statusText = "Suspended"; break;
            case 3: statusText = "Transferred"; break;
            default: statusText = "Unknown";
        }
        ui->tableWidget->setItem(row, 6, new QTableWidgetItem(statusText));

        row++;
    }

    if (row == 0) {
        qDebug() << "No players found for Team ID:" << teamId;
        QMessageBox::information(this, "No Players", "No players are assigned to your team.");
    } else {
        qDebug() << "Loaded" << row << "players for Team ID:" << teamId;
    }

    // Resize columns to content
    ui->tableWidget->resizeColumnsToContents();
}

void displayplayers_coach::on_comboBoxTri_currentIndexChanged(int index)
{
    // Sort table based on comboBoxTri selection
    if (index == 0) { // Default (no sorting)
        ui->tableWidget->sortByColumn(-1, Qt::AscendingOrder);
    } else {
        // Map comboBox index to column (1=First Name, 2=Last Name, 3=Position, 4=Jersey)
        int column = index; // First Name=1, Last Name=2, Position=3, Jersey=4
        ui->tableWidget->sortByColumn(column, Qt::AscendingOrder);
    }
}

void displayplayers_coach::on_tableWidget_itemSelectionChanged()
{
    // Get selected row
    QList<QTableWidgetSelectionRange> selectedRanges = ui->tableWidget->selectedRanges();
    if (selectedRanges.isEmpty()) {
        currentDisplayedPlayerId = -1;
        ui->formFrame->setVisible(false);
        return;
    }

    int row = selectedRanges.first().topRow();
    QTableWidgetItem *idItem = ui->tableWidget->item(row, 0); // ID column
    if (idItem) {
        currentDisplayedPlayerId = idItem->text().toInt();
        qDebug() << "Selected player ID:" << currentDisplayedPlayerId;
        refreshPlayerDetails();
    } else {
        currentDisplayedPlayerId = -1;
        ui->formFrame->setVisible(false);
    }
}

void displayplayers_coach::refreshPlayerDetails()
{
    // If no player is selected
    if (currentDisplayedPlayerId <= 0) {
        ui->formFrame->setVisible(false);
        return;
    }

    // Clear any existing content in the formFrame
    qDeleteAll(ui->formFrame->findChildren<QWidget*>(QString(), Qt::FindDirectChildrenOnly));

    // Create a layout for the frame if it doesn't already have one
    QLayout *existingLayout = ui->formFrame->layout();
    if (existingLayout) {
        delete existingLayout; // Remove any existing layout
    }

    // Create new layout for the frame
    QVBoxLayout *frameLayout = new QVBoxLayout(ui->formFrame);
    frameLayout->setContentsMargins(0, 0, 0, 0);
    ui->formFrame->setLayout(frameLayout);

    // Apply modern style to the main frame
    ui->formFrame->setStyleSheet(
        "QFrame {"
        "   background-color: rgba(45, 48, 56, 0.92);"
        "   border-radius: 12px;"
        "   border: 1px solid rgba(255, 255, 255, 0.15);"
        "}"
    );

    // Create a scroll area
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

    // Create a container widget for all content
    QWidget *contentWidget = new QWidget();
    contentWidget->setStyleSheet("background: transparent;");
    QVBoxLayout *contentLayout = new QVBoxLayout(contentWidget);
    contentLayout->setSpacing(10);
    contentLayout->setContentsMargins(10, 10, 10, 10);

    // Query all player details
    QSqlQuery query;
    query.prepare(
        "SELECT j.*, e.TEAM_NAME "
        "FROM HOTSTUFF.JOUEUR j "
        "JOIN HOTSTUFF.EQUIPE e ON j.ID_TEAM = e.ID_TEAM "
        "WHERE j.ID_PLAYER = :id");
    query.bindValue(":id", currentDisplayedPlayerId);

    if (query.exec() && query.next()) {
        // Prepare data
        QString playerFullName = query.value("FIRST_NAME").toString() + " " + query.value("LAST_NAME").toString();
        QString teamName = query.value("TEAM_NAME").toString();
        QString position = query.value("POSITION").toString();
        QString jerseyNumber = "#" + query.value("JERSEY_NB").toString();
        QString nationality = query.value("NATIONALITY").toString();
        QDate dateOfBirth = query.value("DATE_OF_BIRTH").toDate();
        int goals = query.value("GOALS").toInt();
        int assists = query.value("ASSISTS").toInt();
        int yellowCards = query.value("YELLOW_CARD").toInt();
        int redCards = query.value("RED_CARD").toInt();
        bool injured = query.value("INJURED").toInt() == 1;
        int status = query.value("STATUS").toInt();
        QString statusText;
        switch(status) {
            case 0: statusText = "Active"; break;
            case 1: statusText = "Injured"; break;
            case 2: statusText = "Suspended"; break;
            case 3: statusText = "Transferred"; break;
            default: statusText = "Unknown";
        }
        QByteArray imageData = query.value("IMG_JOUEUR").toByteArray();

        // Player Image
        if (!imageData.isEmpty()) {
            QLabel *playerImageLabel = new QLabel();
            playerImageLabel->setFixedSize(250, 250);
            playerImageLabel->setAlignment(Qt::AlignCenter);

            QPixmap originalPixmap;
            originalPixmap.loadFromData(imageData);

            // Create a circular image
            QPixmap circularPixmap(250, 250);
            circularPixmap.fill(Qt::transparent);

            QPainter painter(&circularPixmap);
            painter.setRenderHint(QPainter::Antialiasing, true);
            painter.setRenderHint(QPainter::SmoothPixmapTransform, true);

            QPainterPath path;
            path.addEllipse(15, 15, 220, 220);
            painter.setClipPath(path);

            QPixmap scaledPixmap = originalPixmap.scaled(220, 220,
                Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);

            int x = scaledPixmap.width() > 220 ? (scaledPixmap.width() - 220) / 2 : 0;
            int y = scaledPixmap.height() > 220 ? (scaledPixmap.height() - 220) / 2 : 0;

            painter.drawPixmap(15, 15, scaledPixmap, x, y, 220, 220);

            painter.setClipping(false);
            QPen borderPen(Qt::white, 3);
            painter.setPen(borderPen);
            painter.drawEllipse(15, 15, 220, 220);

            painter.end();

            playerImageLabel->setPixmap(circularPixmap);
            playerImageLabel->setStyleSheet("background: transparent;");
            contentLayout->addWidget(playerImageLabel, 0, Qt::AlignHCenter);
        } else {
            QLabel *playerImageLabel = new QLabel();
            playerImageLabel->setFixedSize(250, 250);
            playerImageLabel->setAlignment(Qt::AlignCenter);

            QPixmap circularPixmap(250, 250);
            circularPixmap.fill(Qt::transparent);

            QPainter painter(&circularPixmap);
            painter.setRenderHint(QPainter::Antialiasing, true);

            painter.setPen(Qt::NoPen);
            painter.setBrush(QColor(200, 200, 200, 180));
            painter.drawEllipse(15, 15, 220, 220);

            painter.setPen(QPen(Qt::white, 3));
            painter.drawEllipse(15, 15, 220, 220);

            painter.setPen(Qt::white);
            QFont font = painter.font();
            font.setPointSize(64);
            font.setBold(true);
            painter.setFont(font);

            QString initials;
            if (!query.value("FIRST_NAME").toString().isEmpty() && !query.value("LAST_NAME").toString().isEmpty()) {
                initials = QString(query.value("FIRST_NAME").toString()[0]) +
                           QString(query.value("LAST_NAME").toString()[0]);
            } else {
                initials = "?";
            }

            painter.drawText(QRect(15, 15, 220, 220), Qt::AlignCenter, initials);
            painter.end();

            playerImageLabel->setPixmap(circularPixmap);
            contentLayout->addWidget(playerImageLabel, 0, Qt::AlignHCenter);
        }

        // Header Section
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

        QString statusStyle;
        if (status == 0) {
            statusStyle = "background-color: #2ecc71;";
        } else if (status == 1) {
            statusStyle = "background-color: #f1c40f;";
        } else if (status == 2) {
            statusStyle = "background-color: #e74c3c;";
        } else {
            statusStyle = "background-color: #95a5a6;";
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

        // Stats Section
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

        QFrame *goalsWidget = createStatWidget(QString::number(goals), "GOALS", "rgba(46, 204, 113, 0.8)");
        QFrame *assistsWidget = createStatWidget(QString::number(assists), "ASSISTS", "rgba(52, 152, 219, 0.8)");
        QFrame *yellowWidget = createStatWidget(QString::number(yellowCards), "YELLOW", "rgba(241, 196, 15, 0.8)");
        QFrame *redWidget = createStatWidget(QString::number(redCards), "RED", "rgba(231, 76, 60, 0.8)");

        statsLayout->addWidget(goalsWidget);
        statsLayout->addWidget(assistsWidget);
        statsLayout->addWidget(yellowWidget);
        statsLayout->addWidget(redWidget);

        contentLayout->addWidget(statsFrame);

        // Details Section
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

        addInfoRow(0, "Nationality:", nationality);
        addInfoRow(1, "Date of Birth:", dateOfBirth.toString("dd MMM yyyy"));
        addInfoRow(2, "Age:", QString::number(QDate::currentDate().year() - dateOfBirth.year()));
        addInfoRow(3, "Injured:", injured ? "Yes" : "No");

        contentLayout->addWidget(detailsFrame);

        // QR Code
        QString qrText = QString("ID: %1\nName: %2\nTeam: %3\nPosition: %4\nJersey: %5\nStatus: %6")
            .arg(query.value("ID_PLAYER").toString()).arg(playerFullName)
            .arg(teamName).arg(position).arg(jerseyNumber).arg(statusText);

        QPixmap qrCode = generateQRCode(qrText);
        QLabel *qrLabel = new QLabel();
        qrLabel->setPixmap(qrCode.scaled(80, 80, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        qrLabel->setAlignment(Qt::AlignCenter);
        qrLabel->setStyleSheet("background: transparent;");

        contentLayout->addWidget(qrLabel, 0, Qt::AlignHCenter);

        // Buttons Section
        QHBoxLayout *buttonLayout = new QHBoxLayout();
        buttonLayout->setSpacing(8);

        QString buttonStyle =
            "QPushButton {"
            "   background-color: #3498db;"
            "   color: white;"
            "   border-radius: 4px;"
            "   font-weight: bold;"
            "   padding: 6px 12px;"
            "   font-size: 11px;"
            "   text-align: left;"
            "   padding-left: 30px;"
            "}"
            "QPushButton:hover {"
            "   background-color: #2980b9;"
            "}"
            "QPushButton:pressed {"
            "   background-color: #1c5a85;"
            "}";

        // Export PDF Button
        QPushButton *exportButton = new QPushButton("Export PDF");
        exportButton->setStyleSheet(buttonStyle);
        QIcon pdfIcon(":/img/pdfIcon.png");
        exportButton->setIcon(pdfIcon);
        exportButton->setIconSize(QSize(16, 16));
        connect(exportButton, &QPushButton::clicked, [this, playerId = currentDisplayedPlayerId]() {
            exportPlayerToPDF(playerId);
        });

        // Generate Report Button
        QPushButton *reportButton = new QPushButton("Generate Report");
        reportButton->setStyleSheet(buttonStyle);
        QIcon aiIcon(":/img/reportIcon.png");
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

        // Close Button
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
            "   padding-left: 30px;"
            "}"
            "QPushButton:hover {"
            "   background-color: #7f8c8d;"
            "}"
        );
        QIcon hideIcon(":/img/hideIcon.png");
        closeButton->setIcon(hideIcon);
        closeButton->setIconSize(QSize(16, 16));
        connect(closeButton, &QPushButton::clicked, [this]() {
            ui->formFrame->setVisible(false);
            currentDisplayedPlayerId = -1;
        });

        buttonLayout->addWidget(exportButton);
        buttonLayout->addWidget(reportButton);
        buttonLayout->addStretch();
        buttonLayout->addWidget(closeButton);

        contentLayout->addLayout(buttonLayout);

        // Add spacing at the bottom
        contentLayout->addSpacing(5);

        // Configure scroll area
        scrollArea->setWidget(contentWidget);
        frameLayout->addWidget(scrollArea);

        // Make the frame visible
        ui->formFrame->setVisible(true);
        ui->formFrame->updateGeometry();
    } else {
        qDebug() << "Failed to retrieve player details for ID:" << currentDisplayedPlayerId;
        QMessageBox::warning(this, "Error", "Could not retrieve player details.");
        ui->formFrame->setVisible(false);
        currentDisplayedPlayerId = -1;
    }
}

void displayplayers_coach::exportPlayerToPDF(int playerId)
{
    // Retrieve player information
    QSqlQuery query;
    query.prepare(
        "SELECT j.*, e.TEAM_NAME "
        "FROM HOTSTUFF.JOUEUR j "
        "JOIN HOTSTUFF.EQUIPE e ON j.ID_TEAM = e.ID_TEAM "
        "WHERE j.ID_PLAYER = :id");
    query.bindValue(":id", playerId);

    if (!query.exec() || !query.next()) {
        QMessageBox::warning(this, "Error", "Player not found");
        return;
    }

    // Retrieve player data
    QString firstName = query.value("FIRST_NAME").toString();
    QString lastName = query.value("LAST_NAME").toString();
    QString team = query.value("TEAM_NAME").toString();
    QString position = query.value("POSITION").toString();
    int jerseyNumber = query.value("JERSEY_NB").toInt();
    QDate birthDate = query.value("DATE_OF_BIRTH").toDate();
    QString nationality = query.value("NATIONALITY").toString();
    int goals = query.value("GOALS").toInt();
    int assists = query.value("ASSISTS").toInt();
    int yellowCards = query.value("YELLOW_CARD").toInt();
    int redCards = query.value("RED_CARD").toInt();
    bool isInjured = query.value("INJURED").toInt() == 1;

    // Convert status to text
    int statusInt = query.value("STATUS").toInt();
    QString statusText;
    switch(statusInt) {
        case 0: statusText = "Active"; break;
        case 1: statusText = "Injured"; break;
        case 2: statusText = "Suspended"; break;
        case 3: statusText = "Transferred"; break;
        default: statusText = "Unknown";
    }

    // Retrieve image
    QByteArray imageData = query.value("IMG_JOUEUR").toByteArray();
    QPixmap playerImage;
    bool hasImage = false;

    if (!imageData.isEmpty()) {
        hasImage = playerImage.loadFromData(imageData);
    }

    // Generate QR code
    QString qrText = QString("ID: %1\nName: %2 %3\nTeam: %4\nPosition: %5\nJersey: %6\nStatus: %7")
        .arg(playerId).arg(firstName).arg(lastName).arg(team).arg(position).arg(jerseyNumber).arg(statusText);
    QPixmap qrCode = generateQRCode(qrText);

    // Select PDF file
    QString defaultFileName = firstName + "_" + lastName + "_Profile.pdf";
    QString fileName = QFileDialog::getSaveFileName(this, "Export PDF", QDir::homePath() + "/" + defaultFileName, "PDF Files (*.pdf)");

    if (fileName.isEmpty()) return;

    // Create PDF
    QPdfWriter pdfWriter(fileName);
    pdfWriter.setPageSize(QPageSize(QPageSize::A4));
    pdfWriter.setResolution(300);
    pdfWriter.setPageMargins(QMarginsF(20, 20, 20, 20));

    QPainter painter(&pdfWriter);
    painter.setRenderHint(QPainter::Antialiasing);

    // Define fonts and colors
    QFont titleFont("Arial", 26, QFont::Bold);
    QFont sectionFont("Arial", 18, QFont::Bold);
    QFont normalFont("Arial", 14);
    QColor headerColor(26, 54, 93);  // Dark blue
    QColor lineColor(180, 180, 180); // Light gray
    QColor backgroundColor(240, 240, 240); // Light background

    // Spacing between lines
    int y = 120;
    int lineSpacing = 85; // Large spacing between lines

    // Horizontal positions for labels and values
    int labelX = 50;      // X position for labels (e.g., "Yellow Card:")
    int valueX = 550;     // X position for values (e.g., "5")

    // Draw main frame
    painter.setBrush(backgroundColor);
    painter.setPen(Qt::NoPen);
    painter.drawRect(20, 20, pdfWriter.width() - 40, pdfWriter.height() - 40);

    // Draw main title (player name)
    painter.setFont(titleFont);
    painter.setPen(headerColor);

    QString playerFullName = firstName + " " + lastName;
    QFontMetrics titleMetrics(titleFont);
    int titleWidth = titleMetrics.horizontalAdvance(playerFullName);
    int titleX = (pdfWriter.width() - titleWidth) / 2.58;

    painter.drawText(titleX, y, playerFullName);
    y += lineSpacing + 30; // Large space after title

    // Draw player image with frame and shadow
    if (hasImage) {
        QPixmap scaledImage = playerImage.scaled(500, 500, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        int imageX = (pdfWriter.width() - scaledImage.width()) / 2;

        // Shadow effect
        painter.setPen(Qt::NoPen);
        painter.setBrush(QColor(100, 100, 100, 80));
        painter.drawRect(imageX + 5, y + 5, scaledImage.width(), scaledImage.height());

        // Image
        painter.setBrush(Qt::NoBrush);
        painter.drawPixmap(imageX, y, scaledImage);

        // Frame
        painter.setPen(QPen(Qt::black, 2));
        painter.drawRect(imageX, y, scaledImage.width(), scaledImage.height());

        y += scaledImage.height() + 55; // Large space after image
    } else {
        painter.setFont(normalFont);
        painter.drawText((pdfWriter.width() / 2) - 80, y, "No Image Available");
        y += lineSpacing;
    }

    // Draw subtitle (position, jersey number, team)
    painter.setFont(normalFont);
    QString subtitle = position + " | #" + QString::number(jerseyNumber) + " | " + team;
    QFontMetrics normalMetrics(normalFont);
    int subtitleWidth = normalMetrics.horizontalAdvance(subtitle);
    int subtitleX = (pdfWriter.width() - subtitleWidth) / 2.47;

    painter.drawText(subtitleX, y, subtitle);
    y += lineSpacing;

    // Draw decorative separation line
    painter.setPen(QPen(lineColor, 3));
    painter.drawLine(50, y, 550, y);
    y += lineSpacing;

    // Draw player information
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

    // Draw separation line
    painter.setPen(QPen(lineColor, 3));
    painter.drawLine(50, y, 550, y);
    y += lineSpacing;

    // Draw player statistics
    painter.setFont(sectionFont);
    painter.setPen(headerColor);
    painter.drawText(labelX, y, "Player Statistics");
    y += lineSpacing;

    painter.setFont(normalFont);
    painter.setPen(Qt::black);

    // Draw stat boxes
    int statBoxWidth = 230;
    int statSpacing = 100;
    int statStartX = (pdfWriter.width() - (4 * statBoxWidth + 3 * statSpacing)) / 2;

    // Goals
    painter.setFont(QFont("Arial", 16, QFont::Bold));
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

    y += 300; // Space after stat boxes

    // Detailed statistics table
    painter.setFont(normalFont);
    QStringList statsLabels = {"Goals:", "Assists:", "Yellow Cards:", "Red Cards:"};
    QStringList statsValues = {QString::number(goals), QString::number(assists), QString::number(yellowCards), QString::number(redCards)};

    for (int i = 0; i < statsLabels.size(); i++) {
        painter.drawText(labelX, y, statsLabels[i]);
        painter.drawText(valueX, y, statsValues[i]);
        y += lineSpacing;
    }

    // Draw QR code
    QPixmap scaledQrCode = qrCode.scaled(200, 200, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    int qrX = (pdfWriter.width() - scaledQrCode.width()) / 2;
    painter.drawPixmap(qrX, y, scaledQrCode);
    y += scaledQrCode.height() + 50;

    // Draw footer
    painter.setPen(Qt::gray);
    painter.drawLine(50, y + 30, 550, y + 30);
    painter.setFont(QFont("Arial", 10));
    painter.drawText(50, y + 80, "Generated on " + QDate::currentDate().toString("dd/MM/yyyy") + " by AL DAWRY Football Management System");

    // End painting
    painter.end();

    // Confirmation message
    QMessageBox::information(this, "Export PDF", "Player profile successfully exported to:\n" + fileName);
}

QPixmap displayplayers_coach::generateQRCode(const QString &text)
{
    using namespace qrcodegen;

    // Generate QR code
    QrCode qr = QrCode::encodeText(text.toUtf8().constData(), QrCode::Ecc::MEDIUM);

    // Size of QR code (number of modules)
    int size = qr.getSize();
    int scale = 10;  // Scale to enlarge image (10 pixels per module)
    int border = 4;  // Border around QR code (in modules)
    int imgSize = (size + 2 * border) * scale;

    // Create QPixmap
    QPixmap pixmap(imgSize, imgSize);
    pixmap.fill(Qt::white);  // White background

    QPainter painter(&pixmap);
    painter.setPen(Qt::NoPen);
    painter.setBrush(Qt::black);  // Color for black modules

    // Draw QR code modules
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

QJsonObject displayplayers_coach::collectPlayerData(int playerId)
{
    // Placeholder: Collect player data into JSON
    QJsonObject data;
    QSqlQuery query;
    query.prepare("SELECT * FROM HOTSTUFF.JOUEUR WHERE ID_PLAYER = :id");
    query.bindValue(":id", playerId);
    if (query.exec() && query.next()) {
        data["id"] = query.value("ID_PLAYER").toInt();
        data["first_name"] = query.value("FIRST_NAME").toString();
        data["last_name"] = query.value("LAST_NAME").toString();
        data["position"] = query.value("POSITION").toString();
        // Add other fields as needed
    }
    return data;
}

void displayplayers_coach::onGenerateReportClicked() {
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
void displayplayers_coach::displayReport(const QString &reportText) {
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
QString displayplayers_coach::generateReport(const QJsonObject &data) {
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
bool displayplayers_coach::validateTableSelection()
{
    QModelIndexList selection = ui->tableWidget->selectionModel()->selectedRows();
    if (selection.isEmpty()) {
        QMessageBox::warning(this, "Error", "Please select a player from the table first.");
        return false;
    }
    return true;
}