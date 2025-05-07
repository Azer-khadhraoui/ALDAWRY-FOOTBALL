#include "../matchheaders/viewmatch.h"
#include "ui_viewmatch.h"
#include "../matchheaders/match.h"
#include "../matchheaders/watchmatchdialog.h"
#include <QSqlQuery>
#include <QStandardItemModel>
#include <QPixmap>
#include <QMessageBox>
#include <QDateTime>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QComboBox>
#include <QLineEdit>
#include <QDateTimeEdit>
#include <QSpinBox>
#include <QSqlError>
#include <QFileDialog>
#include <QSortFilterProxyModel>
#include <QHeaderView>
#include <QMenu>
#include <QAction>
#include "../matchheaders/fieldwidget.h"


viewMatch::viewMatch(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::viewMatch),
    ascendingOrder(true) // Initialize ascendingOrder
{
    ui->setupUi(this);
    viewmatchlist(); // Call the function to set up the match table
    // Connect the header click signal to the sorting slot
    connect(ui->allmatches->horizontalHeader(), &QHeaderView::sectionClicked, this, &viewMatch::on_headers_Clicked);

    //right click menu
    ui->allmatches->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->allmatches, &QTableView::customContextMenuRequested, this, &viewMatch::on_allmatchesContextMenuRequested);

}
viewMatch::~viewMatch()
{
    delete ui;
}
void viewMatch::viewmatchlist()
{
    // Retrieve all matches from the database
    QList<Match> matches = Match::readAllMatches();

    // Create a QStandardItemModel to hold the match data
    QStandardItemModel *model = new QStandardItemModel(matches.size(), 7, this); // Add one more column
    model->setHorizontalHeaderLabels({"ID ▲▼", "Team 1 ▲▼", "Team 2 ▲▼", "Date ▲▼", "Time ▲▼", "Competition ▲▼", "Status ▲▼"}); // Add sorting indicators ▲▼ to the column headers

    // Populate the model with match data
    for (int row = 0; row < matches.size(); ++row) {
        const Match &match = matches.at(row);

        QString teamAName = match.getTeamAName().isEmpty() ? "Team 1" : match.getTeamAName(); // Handle null team A
        QString teamBName = match.getTeamBName().isEmpty() ? "Team 2" : match.getTeamBName(); // Handle null team B

        // Fetch team logos from the EQUIPE table
        QPixmap teamALogo, teamBLogo;
        QSqlQuery logoQuery;
        logoQuery.prepare("SELECT TEAM_LOGO FROM EQUIPE WHERE TEAM_NAME = :teamName");
        
        // Fetch Team A logo
        logoQuery.bindValue(":teamName", teamAName);
        if (logoQuery.exec() && logoQuery.next()) {
            QByteArray logoData = logoQuery.value("TEAM_LOGO").toByteArray();
            teamALogo.loadFromData(logoData);
        }

        // Fetch Team B logo
        logoQuery.bindValue(":teamName", teamBName);
        if (logoQuery.exec() && logoQuery.next()) {
            QByteArray logoData = logoQuery.value("TEAM_LOGO").toByteArray();
            teamBLogo.loadFromData(logoData);
        }

        // Create items with logos and names
        QStandardItem *teamAItem = new QStandardItem();
        if (!teamALogo.isNull()) {
            teamAItem->setData(QVariant(teamALogo.scaled(24, 24, Qt::KeepAspectRatio, Qt::SmoothTransformation)), Qt::DecorationRole);
        }
        teamAItem->setText(teamAName);

        QStandardItem *teamBItem = new QStandardItem();
        if (!teamBLogo.isNull()) {
            teamBItem->setData(QVariant(teamBLogo.scaled(24, 24, Qt::KeepAspectRatio, Qt::SmoothTransformation)), Qt::DecorationRole);
        }
        teamBItem->setText(teamBName);

        model->setItem(row, 0, new QStandardItem(QString::number(match.getId()))); // ID
        model->setItem(row, 1, teamAItem); // Team 1 with logo
        model->setItem(row, 2, teamBItem); // Team 2 with logo
        model->setItem(row, 3, new QStandardItem(match.getMatchDateTime().date().toString("yyyy-MM-dd"))); // Date
        model->setItem(row, 4, new QStandardItem(match.getMatchDateTime().time().toString("HH:mm:ss"))); // Time
        model->setItem(row, 5, new QStandardItem(match.getCompetitionName())); // Competition
        QString status = match.getStatus();
        if (status == "Scheduled") {
            status = "⏳ " + status;
        } else if (status == "Played") {
            status = "✅ " + status;
        } else if (status == "Playing") {
            status = "⚽ " + status;
        }
        model->setItem(row, 6, new QStandardItem(status)); // Status
    }

    // Set the model to the QTableView
    ui->allmatches->setModel(model);

    // Configure the table view
    ui->allmatches->hideColumn(0); // Hide the ID column
    ui->allmatches->setEditTriggers(QAbstractItemView::NoEditTriggers); // Disable editing
    ui->allmatches->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch); // Stretch columns for visibility
    ui->allmatches->setSelectionBehavior(QAbstractItemView::SelectRows); // Enable row selection
}
void viewMatch::on_search_textChanged(const QString &text) 
{
    if (text.isEmpty()) {
        viewmatchlist();
        return;
    }

    QList<Match> matches = Match::searchMatches(text); // Retrieve filtered matches

    // Create a QStandardItemModel to hold the filtered data
    QStandardItemModel *model = new QStandardItemModel(matches.size(), 6, this);
    model->setHorizontalHeaderLabels({"ID ▲▼", "Team 1 ▲▼", "Team 2 ▲▼", "Date ▲▼", "Time ▲▼", "Competition ▲▼", "Status ▲▼"}); // Set headers

    for (int row = 0; row < matches.size(); ++row) {
        const Match &match = matches.at(row);

        QString teamAName = match.getTeamAName().isEmpty() ? "Team 1" : match.getTeamAName(); // Handle null team A
        QString teamBName = match.getTeamBName().isEmpty() ? "Team 2" : match.getTeamBName(); // Handle null team B

        // Fetch team logos from the EQUIPE table
        QPixmap teamALogo, teamBLogo;
        QSqlQuery logoQuery;
        logoQuery.prepare("SELECT TEAM_LOGO FROM EQUIPE WHERE TEAM_NAME = :teamName");
        
        // Fetch Team A logo
        logoQuery.bindValue(":teamName", teamAName);
        if (logoQuery.exec() && logoQuery.next()) {
            QByteArray logoData = logoQuery.value("TEAM_LOGO").toByteArray();
            teamALogo.loadFromData(logoData);
        }

        // Fetch Team B logo
        logoQuery.bindValue(":teamName", teamBName);
        if (logoQuery.exec() && logoQuery.next()) {
            QByteArray logoData = logoQuery.value("TEAM_LOGO").toByteArray();
            teamBLogo.loadFromData(logoData);
        }

        // Create items with logos and names
        QStandardItem *teamAItem = new QStandardItem();
        if (!teamALogo.isNull()) {
            teamAItem->setData(QVariant(teamALogo.scaled(24, 24, Qt::KeepAspectRatio, Qt::SmoothTransformation)), Qt::DecorationRole);
        }
        teamAItem->setText(teamAName);

        QStandardItem *teamBItem = new QStandardItem();
        if (!teamBLogo.isNull()) {
            teamBItem->setData(QVariant(teamBLogo.scaled(24, 24, Qt::KeepAspectRatio, Qt::SmoothTransformation)), Qt::DecorationRole);
        }
        teamBItem->setText(teamBName);

        model->setItem(row, 0, new QStandardItem(QString::number(match.getId()))); // ID
        model->setItem(row, 1, teamAItem); // Team 1 with logo
        model->setItem(row, 2, teamBItem); // Team 2 with logo
        model->setItem(row, 3, new QStandardItem(match.getMatchDateTime().date().toString("yyyy-MM-dd"))); // Date
        model->setItem(row, 4, new QStandardItem(match.getMatchDateTime().time().toString("HH:mm:ss"))); // Time
        model->setItem(row, 5, new QStandardItem(match.getCompetitionName())); // Competition
        QString status = match.getStatus();
        if (status == "Scheduled") {
            status = "⏳ " + status;
        } else if (status == "Played") {
            status = "✅ " + status;
        } else if (status == "Playing") {
            status = "⚽ " + status;
        }
        model->setItem(row, 6, new QStandardItem(status)); // Status
    }

    ui->allmatches->setModel(model); // Set the filtered model temporarily
}
void viewMatch::on_headers_Clicked(int logicalIndex) 
{
    QList<Match> matches = Match::readAllMatches(); // Get all matches

    // Sort based on the clicked column
    std::sort(matches.begin(), matches.end(), [logicalIndex, this](const Match &a, const Match &b) {
        switch (logicalIndex) {
            case 1: // Team 1 column
                return ascendingOrder ? a.getTeamAName() < b.getTeamAName() : a.getTeamAName() > b.getTeamAName();
            case 2: // Team 2 column
                return ascendingOrder ? a.getTeamBName() < b.getTeamBName() : a.getTeamBName() > b.getTeamBName();
            case 3: // Date column
                return ascendingOrder ? a.getMatchDateTime().date() < b.getMatchDateTime().date() : a.getMatchDateTime().date() > b.getMatchDateTime().date();
            case 4: // Time column
                return ascendingOrder ? a.getMatchDateTime().time() < b.getMatchDateTime().time() : a.getMatchDateTime().time() > b.getMatchDateTime().time();
            case 5: // Competition column
                return ascendingOrder ? a.getCompetitionName() < b.getCompetitionName() : a.getCompetitionName() > b.getCompetitionName();
            case 6: // Status column
                return ascendingOrder ? a.getStatus() < b.getStatus() : a.getStatus() > b.getStatus();
            default:
                return false; // No sorting for invalid columns
        }
    });

    ascendingOrder = !ascendingOrder; // Toggle sorting order

    // Create a QStandardItemModel to hold the sorted data
    QStandardItemModel *model = new QStandardItemModel(matches.size(), 7, this); // Update column count
    model->setHorizontalHeaderLabels({"ID ▲▼", "Team 1 ▲▼", "Team 2 ▲▼", "Date ▲▼", "Time ▲▼", "Competition ▲▼", "Status ▲▼"}); // Add "Status" column

    // Populate the model with sorted data
    for (int row = 0; row < matches.size(); ++row) {
        const Match &match = matches.at(row);

        QString teamAName = match.getTeamAName().isEmpty() ? "Team 1" : match.getTeamAName(); // Handle null team A
        QString teamBName = match.getTeamBName().isEmpty() ? "Team 2" : match.getTeamBName(); // Handle null team B

        // Fetch team logos from the EQUIPE table
        QPixmap teamALogo, teamBLogo;
        QSqlQuery logoQuery;
        logoQuery.prepare("SELECT TEAM_LOGO FROM EQUIPE WHERE TEAM_NAME = :teamName");
        
        // Fetch Team A logo
        logoQuery.bindValue(":teamName", teamAName);
        if (logoQuery.exec() && logoQuery.next()) {
            QByteArray logoData = logoQuery.value("TEAM_LOGO").toByteArray();
            teamALogo.loadFromData(logoData);
        }

        // Fetch Team B logo
        logoQuery.bindValue(":teamName", teamBName);
        if (logoQuery.exec() && logoQuery.next()) {
            QByteArray logoData = logoQuery.value("TEAM_LOGO").toByteArray();
            teamBLogo.loadFromData(logoData);
        }

        // Create items with logos and names
        QStandardItem *teamAItem = new QStandardItem();
        if (!teamALogo.isNull()) {
            teamAItem->setData(QVariant(teamALogo.scaled(24, 24, Qt::KeepAspectRatio, Qt::SmoothTransformation)), Qt::DecorationRole);
        }
        teamAItem->setText(teamAName);

        QStandardItem *teamBItem = new QStandardItem();
        if (!teamBLogo.isNull()) {
            teamBItem->setData(QVariant(teamBLogo.scaled(24, 24, Qt::KeepAspectRatio, Qt::SmoothTransformation)), Qt::DecorationRole);
        }
        teamBItem->setText(teamBName);

        model->setItem(row, 0, new QStandardItem(QString::number(match.getId()))); // ID
        model->setItem(row, 1, teamAItem); // Team 1 with logo
        model->setItem(row, 2, teamBItem); // Team 2 with logo
        model->setItem(row, 3, new QStandardItem(match.getMatchDateTime().date().toString("yyyy-MM-dd"))); // Date
        model->setItem(row, 4, new QStandardItem(match.getMatchDateTime().time().toString("HH:mm:ss"))); // Time
        model->setItem(row, 5, new QStandardItem(match.getCompetitionName())); // Competition
        QString status = match.getStatus();
        if (status == "Scheduled") {
            status = "⏳ " + status;
        } else if (status == "Played") {
            status = "✅ " + status;
        } else if (status == "Playing") {
            status = "⚽ " + status;
        }
        model->setItem(row, 6, new QStandardItem(status)); // Status
    }

    // Set the model to the QTableView
    ui->allmatches->setModel(model);
    ui->allmatches->hideColumn(0); // Hide the ID column
    ui->allmatches->setEditTriggers(QAbstractItemView::NoEditTriggers); // Disable editing
    ui->allmatches->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch); // Stretch columns for visibility
}
void viewMatch::on_allmatchesContextMenuRequested(const QPoint &pos) {
    QModelIndex index = ui->allmatches->indexAt(pos);
    if (!index.isValid()) {
        return;
    }

    // Get match ID and status
    int matchId = index.sibling(index.row(), 0).data().toInt(); // ID in hidden column 0
    QString status = index.sibling(index.row(), 6).data().toString(); // Status in column 6
    status = status.remove(QRegularExpression("^[⏳✅⚽]\\s*")); // Remove status icons

    QMenu contextMenu(this);
    contextMenu.setStyleSheet(
        "QMenu {"
        "    background-color: #2A2A3A;"
        "    color: #FFFFFF;"
        "    border: 1px solid #4A4A5A;"
        "    padding: 5px;"
        "    font-family: 'Segoe UI';"
        "    font-size: 12px;"
        "}"
        "QMenu::item {"
        "    background-color: transparent;"
        "    color: #FFFFFF;"
        "    padding: 8px 20px;"
        "}"
        "QMenu::item:selected {"
        "    background-color: #4A90E2;"
        "    color: #FFFFFF;"
        "}"
    );
    QAction *showFullLineupAction = contextMenu.addAction("Show Full Lineup");
    QAction *watchAction = contextMenu.addAction("Watch Match");
    watchAction->setEnabled(status == "Playing"); // Enable only for "Playing" status

    connect(showFullLineupAction, &QAction::triggered, this, &viewMatch::on_showFullLineupTriggered);
    connect(watchAction, &QAction::triggered, this, [this, matchId]() {
        WatchMatchDialog *dialog = new WatchMatchDialog(matchId, this);
        dialog->exec();
    });

    contextMenu.exec(ui->allmatches->viewport()->mapToGlobal(pos));
}

void viewMatch::on_showFullLineupTriggered() 
{
    // Step 1: Check if a match is selected
    QModelIndexList selectedRows = ui->allmatches->selectionModel()->selectedRows();
    if (selectedRows.isEmpty()) {
        QMessageBox::warning(this, "Error", "No match selected!");
        return;
    }

    int matchId = selectedRows.first().sibling(selectedRows.first().row(), 0).data().toInt();
    Match match;
    for (const Match &m : Match::readAllMatches()) {
        if (m.getId() == matchId) {
            match = m;
            break;
        }
    }

    // Step 2: Get team IDs from the match
    int teamAId = match.getTeamA();
    int teamBId = match.getTeamB();

    // Step 3: Check if both teams have exactly 11 players
    QSqlQuery teamAQuery;
    teamAQuery.prepare(
        "SELECT COUNT(*) "
        "FROM HOTSTUFF.TACHKILA t "
        "JOIN HOTSTUFF.JOUEUR j ON t.ID_PLAYER = j.ID_PLAYER "
        "WHERE t.ID_MATCH = :matchId AND j.ID_TEAM = :teamId"
    );
    teamAQuery.bindValue(":matchId", matchId);
    teamAQuery.bindValue(":teamId", teamAId);
    if (!teamAQuery.exec() || !teamAQuery.next()) {
        QMessageBox::critical(this, "Database Error", "Failed to check Team A lineup: " + teamAQuery.lastError().text());
        return;
    }
    int teamAPlayerCount = teamAQuery.value(0).toInt();

    QSqlQuery teamBQuery;
    teamBQuery.prepare(
        "SELECT COUNT(*) "
        "FROM HOTSTUFF.TACHKILA t "
        "JOIN HOTSTUFF.JOUEUR j ON t.ID_PLAYER = j.ID_PLAYER "
        "WHERE t.ID_MATCH = :matchId AND j.ID_TEAM = :teamId"
    );
    teamBQuery.bindValue(":matchId", matchId);
    teamBQuery.bindValue(":teamId", teamBId);
    if (!teamBQuery.exec() || !teamBQuery.next()) {
        QMessageBox::critical(this, "Database Error", "Failed to check Team B lineup: " + teamBQuery.lastError().text());
        return;
    }
    int teamBPlayerCount = teamBQuery.value(0).toInt();

    if (teamAPlayerCount != 11 || teamBPlayerCount != 11) {
        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setWindowTitle("⚠️ Lineup Incomplete");
        msgBox.setText(
            QString("The full lineup is not set!\n\n"
                    "Team A: %1 players\n"
                    "Team B: %2 players\n\n"
                    "Each team must have exactly 11 players to proceed.")
            .arg(teamAPlayerCount).arg(teamBPlayerCount)
        );
        msgBox.setStyleSheet(
            "QMessageBox { background-color: #2A2A3A; color: #FFFFFF; font-family: 'Segoe UI'; border-radius: 10px; }"
            "QLabel { color: #FFFFFF; font-size: 14px; }"
            "QPushButton { background-color: #E94E77; color: #FFFFFF; border-radius: 5px; padding: 8px; font-size: 12px; }"
            "QPushButton:hover { background-color: #C94063; }"
        );
        msgBox.exec();
        return;
    }

    // Step 4: Fetch Team A lineup with image data and positions
    QSqlQuery teamALineupQuery;
    teamALineupQuery.prepare(
        "SELECT j.FIRST_NAME, j.LAST_NAME, j.IMG_JOUEUR, j.POSITION, t.FORMATION "
        "FROM HOTSTUFF.TACHKILA t "
        "JOIN HOTSTUFF.JOUEUR j ON t.ID_PLAYER = j.ID_PLAYER "
        "WHERE t.ID_MATCH = :matchId AND j.ID_TEAM = :teamId "
        "ORDER BY CASE j.POSITION "
        "   WHEN 'Goalkeeper' THEN 1 "
        "   WHEN 'Defender' THEN 2 "
        "   WHEN 'Midfielder' THEN 3 "
        "   WHEN 'Forward' THEN 4 "
        "   ELSE 5 END"
    );
    teamALineupQuery.bindValue(":matchId", matchId);
    teamALineupQuery.bindValue(":teamId", teamAId);
    if (!teamALineupQuery.exec()) {
        QMessageBox::critical(this, "Database Error", "Failed to fetch Team A lineup: " + teamALineupQuery.lastError().text());
        return;
    }

    // Step 5: Fetch Team B lineup with image data and positions
    QSqlQuery teamBLineupQuery;
    teamBLineupQuery.prepare(
        "SELECT j.FIRST_NAME, j.LAST_NAME, j.IMG_JOUEUR, j.POSITION, t.FORMATION "
        "FROM HOTSTUFF.TACHKILA t "
        "JOIN HOTSTUFF.JOUEUR j ON t.ID_PLAYER = j.ID_PLAYER "
        "WHERE t.ID_MATCH = :matchId AND j.ID_TEAM = :teamId "
        "ORDER BY CASE j.POSITION "
        "   WHEN 'Goalkeeper' THEN 1 "
        "   WHEN 'Defender' THEN 2 "
        "   WHEN 'Midfielder' THEN 3 "
        "   WHEN 'Forward' THEN 4 "
        "   ELSE 5 END"
    );
    teamBLineupQuery.bindValue(":matchId", matchId);
    teamBLineupQuery.bindValue(":teamId", teamBId);
    if (!teamBLineupQuery.exec()) {
        QMessageBox::critical(this, "Database Error", "Failed to fetch Team B lineup: " + teamBLineupQuery.lastError().text());
        return;
    }

    // Step 6: Create the dialog
    QDialog *lineupDialog = new QDialog(this);
    lineupDialog->setWindowTitle("Full Lineup - Match ID: " + QString::number(matchId));
    lineupDialog->setFixedSize(1200, 800);

    // Create the field widget (semi-transparent overlay)
    FieldWidget *fieldWidget = new FieldWidget(lineupDialog);
    fieldWidget->setGeometry(0, 120, 1200, 580); // Adjusted to make space for the taller header
    fieldWidget->setStyleSheet(
        "background: rgba(0, 0, 0, 0.3);" // Semi-transparent overlay
    );

    // Get formations
    QString teamAFormation = "Unknown";
    if (teamALineupQuery.next()) {
        teamAFormation = teamALineupQuery.value("FORMATION").toString();
        teamALineupQuery.seek(-1);
    }
    QString teamBFormation = "Unknown";
    if (teamBLineupQuery.next()) {
        teamBFormation = teamBLineupQuery.value("FORMATION").toString();
        teamBLineupQuery.seek(-1);
    }

    // Parse formations to determine the number of players in each position
    QStringList teamAFormationParts = teamAFormation.split("-");
    QStringList teamBFormationParts = teamBFormation.split("-");

    int teamAMidfielders = teamAFormationParts.size() > 1 ? teamAFormationParts[1].toInt() : 4;
    int teamAForwards = teamAFormationParts.size() > 2 ? teamAFormationParts[2].toInt() : 2;

    int teamBMidfielders = teamBFormationParts.size() > 1 ? teamBFormationParts[1].toInt() : 3;
    int teamBForwards = teamBFormationParts.size() > 2 ? teamBFormationParts[2].toInt() : 3;

    // Fetch team logos from the EQUIPE table
    QSqlQuery teamALogoQuery;
    teamALogoQuery.prepare("SELECT TEAM_LOGO FROM HOTSTUFF.EQUIPE WHERE ID_TEAM = :teamId");
    teamALogoQuery.bindValue(":teamId", teamAId);
    QByteArray teamALogoData;
    if (teamALogoQuery.exec() && teamALogoQuery.next()) {
        teamALogoData = teamALogoQuery.value("TEAM_LOGO").toByteArray();
    } else {
        QMessageBox::warning(this, "Database Warning", "Failed to fetch Team A logo: " + teamALogoQuery.lastError().text());
    }

    QSqlQuery teamBLogoQuery;
    teamBLogoQuery.prepare("SELECT TEAM_LOGO FROM HOTSTUFF.EQUIPE WHERE ID_TEAM = :teamId");
    teamBLogoQuery.bindValue(":teamId", teamBId);
    QByteArray teamBLogoData;
    if (teamBLogoQuery.exec() && teamBLogoQuery.next()) {
        teamBLogoData = teamBLogoQuery.value("TEAM_LOGO").toByteArray();
    } else {
        QMessageBox::warning(this, "Database Warning", "Failed to fetch Team B logo: " + teamBLogoQuery.lastError().text());
    }

    // Team logos, names, and formations at the top
    QHBoxLayout *topLayout = new QHBoxLayout();

    // Add a background to the top layout for a premium look
    QWidget *topWidget = new QWidget(lineupDialog);
    topWidget->setStyleSheet(
        "background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #1C2526, stop:1 #2A3435);" // Subtle dark gradient
        "border-bottom: 1px solid #444;" // Thin border to separate from the field
    );
    topWidget->setLayout(topLayout);

    // Team A (Left side: Logo, Name, Formation)
    QVBoxLayout *teamALayout = new QVBoxLayout();

    // Team A Logo
    QLabel *teamALogoLabel = new QLabel(lineupDialog);
    if (!teamALogoData.isEmpty()) {
        QPixmap teamALogoPixmap;
        teamALogoPixmap.loadFromData(teamALogoData);
        teamALogoLabel->setPixmap(teamALogoPixmap.scaled(40, 40, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    } else {
        teamALogoLabel->setText("No Logo");
    }
    teamALogoLabel->setFixedSize(40, 40);
    teamALogoLabel->setStyleSheet("background: transparent;");
    teamALogoLabel->setAlignment(Qt::AlignCenter);
    teamALayout->addWidget(teamALogoLabel, 0, Qt::AlignCenter);

    // Team A Name
    QLabel *teamANameLabel = new QLabel(match.getTeamAName(), lineupDialog);
    teamANameLabel->setStyleSheet(
        "color: #FFFFFF;" // Pure white for clarity
        "font-size: 20px;"
        "font-weight: bold;"
        "font-family: 'Montserrat', 'Arial', sans-serif;" // Modern, professional font
        "text-transform: uppercase;" // Uppercase for a bold look
        "letter-spacing: 1px;" // Slight spacing for readability
        "background: transparent;"
    );
    teamANameLabel->setAlignment(Qt::AlignCenter);
    teamALayout->addWidget(teamANameLabel, 0, Qt::AlignCenter);

    // Team A Formation
    QLabel *teamAFormationLabel = new QLabel(teamAFormation, lineupDialog);
    teamAFormationLabel->setStyleSheet(
        "color: #FFFFFF;" // White text
        "font-size: 16px;"
        "font-weight: bold;"
        "font-family: 'Roboto Condensed', 'Arial', sans-serif;" // Clean, condensed font
        "background: rgba(0, 0, 0, 0.7);" // Semi-transparent black background
        "padding: 8px;"
        "border: 1px solid #D4AF37;" // Subtle gold border for a classy touch
        "border-radius: 5px;"
        "box-shadow: 0px 2px 4px rgba(0, 0, 0, 0.2);" // Subtle shadow for depth
        "text-align: center;"
        "text-transform: uppercase;"
        "letter-spacing: 1px;"
    );
    teamAFormationLabel->setFixedWidth(100); // Consistent width for alignment
    teamAFormationLabel->setAlignment(Qt::AlignCenter);
    teamALayout->addWidget(teamAFormationLabel, 0, Qt::AlignCenter);

    topLayout->addLayout(teamALayout);
    topLayout->addStretch(); // Space between Team A and "vs"

    // "vs" Label
    QLabel *vsLabel = new QLabel("VS", lineupDialog);
    vsLabel->setStyleSheet(
        "color: #D4AF37;" // Muted gold for a classy accent
        "font-size: 18px;"
        "font-weight: bold;"
        "font-family: 'Montserrat', 'Arial', sans-serif;"
        "background: transparent;"
        "padding: 5px;"
        "text-transform: uppercase;"
    );
    vsLabel->setAlignment(Qt::AlignCenter);
    topLayout->addWidget(vsLabel, 0, Qt::AlignCenter);
    topLayout->addStretch(); // Space between "vs" and Team B

    // Team B (Right side: Logo, Name, Formation)
    QVBoxLayout *teamBLayout = new QVBoxLayout();

    // Team B Logo
    QLabel *teamBLogoLabel = new QLabel(lineupDialog);
    if (!teamBLogoData.isEmpty()) {
        QPixmap teamBLogoPixmap;
        teamBLogoPixmap.loadFromData(teamBLogoData);
        teamBLogoLabel->setPixmap(teamBLogoPixmap.scaled(40, 40, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    } else {
        teamBLogoLabel->setText("No Logo");
    }
    teamBLogoLabel->setFixedSize(40, 40);
    teamBLogoLabel->setStyleSheet("background: transparent;");
    teamBLogoLabel->setAlignment(Qt::AlignCenter);
    teamBLayout->addWidget(teamBLogoLabel, 0, Qt::AlignCenter);

    // Team B Name
    QLabel *teamBNameLabel = new QLabel(match.getTeamBName(), lineupDialog);
    teamBNameLabel->setStyleSheet(
        "color: #FFFFFF;" // Pure white for clarity
        "font-size: 20px;"
        "font-weight: bold;"
        "font-family: 'Montserrat', 'Arial', sans-serif;" // Modern, professional font
        "text-transform: uppercase;" // Uppercase for a bold look
        "letter-spacing: 1px;" // Slight spacing for readability
        "background: transparent;"
    );
    teamBNameLabel->setAlignment(Qt::AlignCenter);
    teamBLayout->addWidget(teamBNameLabel, 0, Qt::AlignCenter);

    // Team B Formation
    QLabel *teamBFormationLabel = new QLabel(teamBFormation, lineupDialog);
    teamBFormationLabel->setStyleSheet(
        "color: #FFFFFF;" // White text
        "font-size: 16px;"
        "font-weight: bold;"
        "font-family: 'Roboto Condensed', 'Arial', sans-serif;" // Clean, condensed font
        "background: rgba(0, 0, 0, 0.7);" // Semi-transparent black background
        "padding: 8px;"
        "border: 1px solid #D4AF37;" // Subtle gold border for a classy touch
        "border-radius: 5px;"
        "box-shadow: 0px 2px 4px rgba(0, 0, 0, 0.2);" // Subtle shadow for depth
        "text-align: center;"
        "text-transform: uppercase;"
        "letter-spacing: 1px;"
    );
    teamBFormationLabel->setFixedWidth(100); // Consistent width for alignment
    teamBFormationLabel->setAlignment(Qt::AlignCenter);
    teamBLayout->addWidget(teamBFormationLabel, 0, Qt::AlignCenter);

    topLayout->addLayout(teamBLayout);

    QVBoxLayout *dialogLayout = new QVBoxLayout(lineupDialog);
    dialogLayout->addWidget(topWidget); // Add the top widget with the gradient background
    dialogLayout->addStretch();

    // Position players for Team A (facing right)
    int currentDefender = 0, currentMidfielder = 0, currentForward = 0;
    teamALineupQuery.seek(-1);
    while (teamALineupQuery.next()) {
        QString position = teamALineupQuery.value("POSITION").toString();
        QString playerName = teamALineupQuery.value("LAST_NAME").toString();
        QByteArray imageData = teamALineupQuery.value("IMG_JOUEUR").toByteArray();

        // Create the player image
        QLabel *playerImage = new QLabel(fieldWidget);
        if (!imageData.isEmpty()) {
            QPixmap pixmap;
            pixmap.loadFromData(imageData);
            playerImage->setPixmap(pixmap.scaled(50, 50, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        } else {
            playerImage->setPixmap(QPixmap(":/user.png").scaled(50, 50, Qt::KeepAspectRatio));
        }
        playerImage->setStyleSheet(
            "border-radius: 25px;" // Round image
            "background: transparent;" // Transparent background
        );
        playerImage->setAlignment(Qt::AlignCenter);
        playerImage->setFixedSize(50, 50);

        // Create the player name label
        QLabel *playerLabel = new QLabel(playerName, fieldWidget);
        playerLabel->setStyleSheet(
            "color: white; font-size: 10px;" // Plain white text, no background
        );
        playerLabel->setAlignment(Qt::AlignCenter);
        playerLabel->setWordWrap(true);
        playerLabel->setFixedWidth(60); // Slightly wider than the image for longer names

        // Position players on the field (Team A, facing right, 4-4-2 formation)
        int xPos = 0, yPos = 0;
        if (position == "Goalkeeper") {
            xPos = 60;
            yPos = 280; // Closer to the goal line
        } else if (position == "Defender" && currentDefender < 4) {
            switch (currentDefender) {
            case 0: xPos = 150; yPos = 340; break; // Right center-back
            case 1: xPos = 150; yPos = 200; break; // Left center-back
            case 2: xPos = 190; yPos = 90; break; // Left full-back
            case 3: xPos = 190; yPos = 450; break; // Right full-back
            }
            currentDefender++;
        } else if (position == "Midfielder" && currentMidfielder < teamAMidfielders) {
            if (teamAMidfielders == 4) {
                switch (currentMidfielder) {
                case 0: xPos = 300; yPos = 200; break; // Left midfielder cassado
                case 1: xPos = 300; yPos = 340; break; // Right midfielder pedri
                case 2: xPos = 370; yPos = 90; break; // Top midfielder dejong
                case 3: xPos = 370; yPos = 450; break; // Bottom midfielder gavi
                }
            } else { // 3 midfielders (fallback, not used in 4-4-2)
                switch (currentMidfielder) {
                case 0: xPos = 360; yPos = 130; break;
                case 1: xPos = 360; yPos = 370; break;
                case 2: xPos = 300; yPos = 250; break;
                }
            }
            currentMidfielder++;
        } else if (position == "Forward" && currentForward < teamAForwards) {
            if (teamAForwards == 2) {
                switch (currentForward) {
                case 0: xPos = 500; yPos = 200; break; // Left forward
                case 1: xPos = 500; yPos = 340; break; // Right forward
                }
            } else { // 3 forwards (fallback, not used in 4-4-2)
                switch (currentForward) {
                case 0: xPos = 505; yPos = 130; break;
                case 1: xPos = 505; yPos = 370; break;
                case 2: xPos = 530; yPos = 250; break;
                }
            }
            currentForward++;
        }

        // Position the image and label directly on the field
        playerImage->move(xPos, yPos);
        playerLabel->move(xPos - 5, yPos + 50); // Position the label just below the image (50 is the image height)
    }

    // Position players for Team B (facing left, 4-3-3 formation)
    currentDefender = 0, currentMidfielder = 0, currentForward = 0;
    teamBLineupQuery.seek(-1);
    while (teamBLineupQuery.next()) {
        QString position = teamBLineupQuery.value("POSITION").toString();
        QString playerName = teamBLineupQuery.value("LAST_NAME").toString();
        QByteArray imageData = teamBLineupQuery.value("IMG_JOUEUR").toByteArray();

        // Create the player image
        QLabel *playerImage = new QLabel(fieldWidget);
        if (!imageData.isEmpty()) {
            QPixmap pixmap;
            pixmap.loadFromData(imageData);
            playerImage->setPixmap(pixmap.scaled(50, 50, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        } else {
            playerImage->setPixmap(QPixmap(":/user.png").scaled(50, 50, Qt::KeepAspectRatio));
        }
        playerImage->setStyleSheet(
            "border-radius: 25px;" // Round image
            "background: transparent;" // Transparent background
        );
        playerImage->setAlignment(Qt::AlignCenter);
        playerImage->setFixedSize(50, 50);

        // Create the player name label
        QLabel *playerLabel = new QLabel(playerName, fieldWidget);
        playerLabel->setStyleSheet(
            "color: white; font-size: 10px;" // Plain white text, no background
        );
        playerLabel->setAlignment(Qt::AlignCenter);
        playerLabel->setWordWrap(true);
        playerLabel->setFixedWidth(60); // Slightly wider than the image for longer names

        // Position players on the field (Team B, facing left, 4-3-3 formation)
        int xPos = 0, yPos = 0;
        if (position == "Goalkeeper") {
            xPos = 1080;
            yPos = 280; // Closer to the goal line
        } else if (position == "Defender" && currentDefender < 4) {
            switch (currentDefender) {
            case 0: xPos = 990; yPos = 200; break; // Right center-back
            case 1: xPos = 990; yPos = 340; break; // Right full-back
            case 2: xPos = 960; yPos = 450; break; // Left full-back
            case 3: xPos = 960; yPos = 90; break; // Left center-back
            }
            currentDefender++;
        } else if (position == "Midfielder" && currentMidfielder < teamBMidfielders) {
            if (teamBMidfielders == 4) { // Fallback, not used in 4-3-3
                switch (currentMidfielder) {
                case 0: xPos = 800; yPos = 340; break;  
                case 1: xPos = 800; yPos = 200; break; 
                case 2: xPos = 730; yPos = 450; break; 
                case 3: xPos = 730; yPos = 90; break; 
                }
            } else { // 3 midfielders, triangle formation
                switch (currentMidfielder) {
                case 0: xPos = 800; yPos = 370; break; // Left midfielder (defensive)
                case 1: xPos = 800; yPos = 130; break; // Top midfielder (attacking)
                case 2: xPos = 840; yPos = 250; break; // Right midfielder (defensive)
                }
            }
            currentMidfielder++;
        } else if (position == "Forward" && currentForward < teamBForwards) {
            if (teamBForwards == 2) { // Fallback, not used in 4-3-3
                switch (currentForward) {
                case 0: xPos = 640; yPos = 340; break;
                case 1: xPos = 640; yPos = 200; break;
                }
            } else { // 3 forwards
                switch (currentForward) {
                case 0: xPos = 655; yPos = 370; break; // Left winger
                case 1: xPos = 655; yPos = 130; break; // Right winger
                case 2: xPos = 620; yPos = 250; break; // Center forward
                }
            }
            currentForward++;
        }

        // Position the image and label directly on the field
        playerImage->move(xPos, yPos);
        playerLabel->move(xPos - 5, yPos + 50); // Position the label just below the image (50 is the image height)
    }

    // Show the dialog
    lineupDialog->exec();
}
