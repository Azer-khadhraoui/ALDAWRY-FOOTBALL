#include "../userheaders/displaymatch_coach.h"
#include "ui_displaymatch_coach.h"
#include <QStandardItemModel>
#include <QSqlQuery>
#include <QPixmap>
#include <QAbstractItemView>
#include <QHeaderView>
#include "../matchheaders/match.h"
#include "../userheaders/sessionmanager.h"
#include "../teamheaders/team.h"
#include <QMenu>
#include <QAction>
#include <QMessageBox>
#include <QsqlError>
#include <QSqlQueryModel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QFormLayout>

displaymatch_coach::displaymatch_coach(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::displaymatch_coach),
    ascendingOrder(true) // Initialize sorting order to ascending
{
    ui->setupUi(this);
    loadCurrentCoachMatches();
    // Connect the header click signal to the sorting slot
    connect(ui->allmatches->horizontalHeader(), &QHeaderView::sectionClicked, this, &displaymatch_coach::on_headers_Clicked_coach);
    // Connect the search bar text changed signal to the search slot
    connect(ui->search, &QLineEdit::textChanged, this, &displaymatch_coach::on_search_textChanged_coach);
    //right click menu
    ui->allmatches->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->allmatches, &QTableView::customContextMenuRequested, this, &displaymatch_coach::on_menurequest);
}

displaymatch_coach::~displaymatch_coach()
{
    delete ui;
}

void displaymatch_coach::loadcoachmatches(int idteam)
{
    QList<Match> allMatches = Match::readAllMatches();
    QList<Match> matches;
    for (const Match& match : allMatches) {
        if (match.getTeamA() == idteam || match.getTeamB() == idteam) {
            matches.append(match);
        }
    }
    QStandardItemModel *model = new QStandardItemModel(matches.size(), 7, this);
    model->setHorizontalHeaderLabels({"ID ▲▼", "Team 1 ▲▼", "Team 2 ▲▼", "Date ▲▼", "Time ▲▼", "Competition ▲▼", "Status ▲▼"});
    for (int row = 0; row < matches.size(); ++row) {
        const Match &match = matches.at(row);
        QString teamAName = match.getTeamAName().isEmpty() ? "Team 1" : match.getTeamAName();
        QString teamBName = match.getTeamBName().isEmpty() ? "Team 2" : match.getTeamBName();
        QPixmap teamALogo, teamBLogo;
        QSqlQuery logoQuery;
        logoQuery.prepare("SELECT TEAM_LOGO FROM EQUIPE WHERE TEAM_NAME = :teamName");
        logoQuery.bindValue(":teamName", teamAName);
        if (logoQuery.exec() && logoQuery.next()) {
            QByteArray logoData = logoQuery.value("TEAM_LOGO").toByteArray();
            teamALogo.loadFromData(logoData);
        }
        logoQuery.bindValue(":teamName", teamBName);
        if (logoQuery.exec() && logoQuery.next()) {
            QByteArray logoData = logoQuery.value("TEAM_LOGO").toByteArray();
            teamBLogo.loadFromData(logoData);
        }
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
        model->setItem(row, 0, new QStandardItem(QString::number(match.getId())));
        model->setItem(row, 1, teamAItem);
        model->setItem(row, 2, teamBItem);
        model->setItem(row, 3, new QStandardItem(match.getMatchDateTime().date().toString("yyyy-MM-dd")));
        model->setItem(row, 4, new QStandardItem(match.getMatchDateTime().time().toString("HH:mm:ss")));
        model->setItem(row, 5, new QStandardItem(match.getCompetitionName()));
        QString status = match.getStatus();
        if (status == "Scheduled") {
            status = "⏳ " + status;
        } else if (status == "Played") {
            status = "✅ " + status;
        } else if (status == "Playing") {
            status = "⚽ " + status;
        }
        model->setItem(row, 6, new QStandardItem(status));
    }
    ui->allmatches->setModel(model);
    ui->allmatches->hideColumn(0);
    ui->allmatches->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->allmatches->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->allmatches->setSelectionBehavior(QAbstractItemView::SelectRows);
}

void displaymatch_coach::loadCurrentCoachMatches() {
    const Employee& currentUser = SessionManager::instance().getCurrentUser();
    int coachId = currentUser.getId();
    Team* team = Team::getTeamByCoachId(coachId);
    if (team) {
        int teamId = team->getId();
        loadcoachmatches(teamId);
        delete team;
    } else {
        // Optionally clear the table or show a message
        QStandardItemModel *emptyModel = new QStandardItemModel(0, 7, this);
        emptyModel->setHorizontalHeaderLabels({"ID ▲▼", "Team 1 ▲▼", "Team 2 ▲▼", "Date ▲▼", "Time ▲▼", "Competition ▲▼", "Status ▲▼"});
        ui->allmatches->setModel(emptyModel);
    }
}
void displaymatch_coach::on_headers_Clicked_coach(int logicalIndex)
{
    // Get current coach's team ID
    const Employee& currentUser = SessionManager::instance().getCurrentUser();
    int coachId = currentUser.getId();
    Team* team = Team::getTeamByCoachId(coachId);
    int teamId = team ? team->getId() : -1;
    delete team;

    // Get all matches for this team
    QList<Match> allMatches = Match::readAllMatches();
    QList<Match> matches;
    for (const Match& match : allMatches) {
        if (match.getTeamA() == teamId || match.getTeamB() == teamId) {
            matches.append(match);
        }
    }

    // Sort based on the clicked column
    static bool ascendingOrder = true;
    std::sort(matches.begin(), matches.end(), [logicalIndex, ascendingOrder](const Match &a, const Match &b) {
        switch (logicalIndex) {
            case 1: return ascendingOrder ? a.getTeamAName() < b.getTeamAName() : a.getTeamAName() > b.getTeamAName();
            case 2: return ascendingOrder ? a.getTeamBName() < b.getTeamBName() : a.getTeamBName() > b.getTeamBName();
            case 3: return ascendingOrder ? a.getMatchDateTime().date() < b.getMatchDateTime().date() : a.getMatchDateTime().date() > b.getMatchDateTime().date();
            case 4: return ascendingOrder ? a.getMatchDateTime().time() < b.getMatchDateTime().time() : a.getMatchDateTime().time() > b.getMatchDateTime().time();
            case 5: return ascendingOrder ? a.getCompetitionName() < b.getCompetitionName() : a.getCompetitionName() > b.getCompetitionName();
            case 6: return ascendingOrder ? a.getStatus() < b.getStatus() : a.getStatus() > b.getStatus();
            default: return false;
        }
    });
    ascendingOrder = !ascendingOrder;

    // Create a QStandardItemModel to hold the sorted data
    QStandardItemModel *model = new QStandardItemModel(matches.size(), 7, this);
    model->setHorizontalHeaderLabels({"ID ▲▼", "Team 1 ▲▼", "Team 2 ▲▼", "Date ▲▼", "Time ▲▼", "Competition ▲▼", "Status ▲▼"});

    // Populate the model with sorted data
    for (int row = 0; row < matches.size(); ++row) {
        const Match &match = matches.at(row);
        QString teamAName = match.getTeamAName().isEmpty() ? "Team 1" : match.getTeamAName();
        QString teamBName = match.getTeamBName().isEmpty() ? "Team 2" : match.getTeamBName();

        // Fetch team logos from the EQUIPE table
        QPixmap teamALogo, teamBLogo;
        QSqlQuery logoQuery;
        logoQuery.prepare("SELECT TEAM_LOGO FROM EQUIPE WHERE TEAM_NAME = :teamName");
        logoQuery.bindValue(":teamName", teamAName);
        if (logoQuery.exec() && logoQuery.next()) {
            QByteArray logoData = logoQuery.value("TEAM_LOGO").toByteArray();
            teamALogo.loadFromData(logoData);
        }
        logoQuery.bindValue(":teamName", teamBName);
        if (logoQuery.exec() && logoQuery.next()) {
            QByteArray logoData = logoQuery.value("TEAM_LOGO").toByteArray();
            teamBLogo.loadFromData(logoData);
        }

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

        model->setItem(row, 0, new QStandardItem(QString::number(match.getId())));
        model->setItem(row, 1, teamAItem);
        model->setItem(row, 2, teamBItem);
        model->setItem(row, 3, new QStandardItem(match.getMatchDateTime().date().toString("yyyy-MM-dd")));
        model->setItem(row, 4, new QStandardItem(match.getMatchDateTime().time().toString("HH:mm:ss")));
        model->setItem(row, 5, new QStandardItem(match.getCompetitionName()));
        QString status = match.getStatus();
        if (status == "Scheduled") status = "⏳ " + status;
        else if (status == "Played") status = "✅ " + status;
        else if (status == "Playing") status = "⚽ " + status;
        model->setItem(row, 6, new QStandardItem(status));
    }

    ui->allmatches->setModel(model);
    ui->allmatches->hideColumn(0);
    ui->allmatches->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->allmatches->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->allmatches->setSelectionBehavior(QAbstractItemView::SelectRows);
}
void displaymatch_coach::on_search_textChanged_coach(const QString &text)
{
    QStandardItemModel *model = qobject_cast<QStandardItemModel *>(ui->allmatches->model());
    if (!model) return;

    for (int row = 0; row < model->rowCount(); ++row) {
        bool matchFound = false;
        for (int column = 0; column < model->columnCount(); ++column) {
            QStandardItem *item = model->item(row, column);
            if (item && item->text().contains(text, Qt::CaseInsensitive)) {
                matchFound = true;
                break;
            }
        }
        ui->allmatches->setRowHidden(row, !matchFound);
    }
}
void displaymatch_coach::on_menurequest(const QPoint &pos)
{
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
    QAction *setLineupAction = contextMenu.addAction("Set Lineup");

    // Use a lambda to call on_setLineupTriggered
    connect(setLineupAction, &QAction::triggered, this, [this]() {
        on_setLineupTriggered();
    });

    contextMenu.exec(ui->allmatches->viewport()->mapToGlobal(pos));
}
void displaymatch_coach::setupLineupWidget(int matchId, int teamId, const QString& lineup) {
    ui->line_up_widget->hide();

    // Clear player lists
    allGoalkeepers.clear();
    allDefenders.clear();
    allMidfielders.clear();
    allForwards.clear();

    // Populate player lists by position with status
    QSqlQuery query;
    query.prepare("SELECT ID_PLAYER, FIRST_NAME, LAST_NAME, POSITION, STATUS FROM JOUEUR WHERE ID_TEAM = :teamId");
    query.bindValue(":teamId", teamId);
    if (!query.exec()) {
        qDebug() << "Error fetching players:" << query.lastError().text();
        QMessageBox::critical(this, "Database Error", "Failed to load players: " + query.lastError().text());
        return;
    }

    while (query.next()) {
        int id = query.value("ID_PLAYER").toInt();
        QString name = query.value("LAST_NAME").toString();
        QString position = query.value("POSITION").toString();
        int status = query.value("STATUS").toInt();
        QString displayName = (status == 0) ? "✅ " + name : "❌ " + name;

        if (position == "Goalkeeper") {
            allGoalkeepers.append({id, displayName, status});
        } else if (position == "Defender") {
            allDefenders.append({id, displayName, status});
        } else if (position == "Midfielder") {
            allMidfielders.append({id, displayName, status});
        } else if (position == "Forward") {
            allForwards.append({id, displayName, status});
        }
    }

    qDebug() << "Players loaded - GK:" << allGoalkeepers.size() << "DF:" << allDefenders.size()
             << "MF:" << allMidfielders.size() << "FW:" << allForwards.size();

    struct Position {
        int x, y, w, h;
    };

    Position pos433[] = {
        {540, 510, 72, 24}, {470, 440, 72, 24}, {610, 440, 72, 24}, {330, 390,72, 24}, {750, 390, 72, 24},
        {370, 270, 72, 24}, {710, 270, 72, 24}, {540, 330, 72, 24}, {380, 150, 72, 24}, {700, 150, 72, 24}, {540, 110, 72, 24}
    };

    Position pos442[] = {
        {540, 510, 72, 24}, {470, 440, 72, 24}, {610, 440, 72, 24}, {330, 390, 72, 24}, {750, 390, 72, 24},
        {460, 330, 72, 24}, {620, 330, 72, 24}, {340, 260, 72, 24}, {740, 260, 72, 24}, {460, 120, 72, 24}, {620, 120, 72, 24}
    };

    Position* positions = (lineup == "4-3-3") ? pos433 : pos442;
    int totalPlayers = 11;

    // Create and position combo boxes with enhanced stylesheet
    for (int i = 0; i < totalPlayers; ++i) {
        QComboBox* box = new QComboBox(ui->line_up_widget);
        box->setGeometry(positions[i].x, positions[i].y, positions[i].w, positions[i].h);
        box->setStyleSheet(
            "QComboBox {"
            "  background-color: #3A3A4A;"
            "  color: #FFFFFF;"
            "  border: 1px solid #5A5A6A;"
            "  border-radius: 4px;"
            "  padding: 4px;"
            "  font-size: 12px;"
            "}"
            "QComboBox:hover {"
            "  border: 1px solid #7A7A8A;"
            "}"
            "QComboBox::drop-down {"
            "  border-left: 1px solid #5A5A6A;"
            "  width: 20px;"
            "}"
            "QComboBox QAbstractItemView {"
            "  background-color: #3A3A4A;"
            "  color: #FFFFFF;"
            "  selection-background-color: #5A5A6A;"
            "  border: 1px solid #5A5A6A;"
            "}"
        );

        QString pos;
        if (i == 0) pos = "Goalkeeper";
        else if (i >= 1 && i <= 4) pos = "Defender";
        else if (i >= 5 && i < (lineup == "4-3-3" ? 8 : 9)) pos = "Midfielder";
        else pos = "Forward";

        positionBoxes.append({box, pos});
    }

    // Initial population
    updateAvailablePlayers();

    // Add "Save Lineup" button
    QPushButton* saveButton = new QPushButton("Save Lineup", ui->line_up_widget);
    saveButton->setGeometry(90, 200, 100, 30);
    saveButton->setStyleSheet(
        "QPushButton {"
        "  background-color: #4CAF50;"
        "  color: #FFFFFF;"
        "  border: none;"
        "  border-radius: 4px;"
        "  padding: 6px;"
        "  font-size: 13px;"
        "  font-weight: bold;"
        "}"
        "QPushButton:hover {"
        "  background-color: #45A049;"
        "}"
        "QPushButton:pressed {"
        "  background-color: #3D8B40;"
        "}"
    );

    // Add "Cancel" button
    QPushButton* cancelButton = new QPushButton("Cancel", ui->line_up_widget);
    cancelButton->setGeometry(90, 280, 100, 30);
    cancelButton->setStyleSheet(
        "QPushButton {"
        "  background-color: #E94E77;"
        "  color: #FFFFFF;"
        "  border: none;"
        "  border-radius: 4px;"
        "  padding: 6px;"
        "  font-size: 13px;"
        "  font-weight: bold;"
        "}"
        "QPushButton:hover {"
        "  background-color: #C94063;"
        "}"
        "QPushButton:pressed {"
        "  background-color: #A83352;"
        "}"
    );

    // Connect "Save Lineup" with cancelButton cleanup
    connect(saveButton, &QPushButton::clicked, this, [this, matchId, teamId, lineup, saveButton, cancelButton]() {
        qDebug() << "Save Lineup clicked";
        QList<int> selectedPlayers;
        for (const auto& [box, _] : positionBoxes) {
            int playerId = box->currentData().toInt();
            if (playerId == -1) {
                QMessageBox msgBox;
                msgBox.setIcon(QMessageBox::Warning);
                msgBox.setWindowTitle("⚠️ Incomplete Lineup");
                msgBox.setText("All positions must be filled before saving the lineup!");
                msgBox.setStyleSheet(
                    "QMessageBox { background-color: #2A2A3A; color: #FFFFFF; font-family: 'Segoe UI'; border-radius: 10px; }"
                    "QLabel { color: #FFFFFF; font-size: 14px; }"
                    "QPushButton { background-color: #E94E77; color: #FFFFFF; border-radius: 5px; padding: 8px; font-size: 12px; }"
                    "QPushButton:hover { background-color: #C94063; }"
                );
                msgBox.exec();
                return;
            }
            selectedPlayers.append(playerId);
        }

        bool hasDuplicates = false;
        QSet<int> seenPlayers;
        for (int id : selectedPlayers) {
            if (seenPlayers.contains(id)) {
                hasDuplicates = true;
                break;
            }
            seenPlayers.insert(id);
        }

        if (selectedPlayers.size() != 11 || hasDuplicates) {
            QMessageBox::warning(this, "Error", "Please select exactly 11 unique players!");
            return;
        }

        if (Match::setLineup(matchId, teamId, lineup, selectedPlayers)) {
            QMessageBox msgBox;
            msgBox.setIcon(QMessageBox::Information);
            msgBox.setWindowTitle("✅ Success");
            msgBox.setText("Lineup set successfully!");
            msgBox.setStyleSheet(
            "QMessageBox { background-color: #1E1E2F; color: #FFFFFF; font-family: 'Segoe UI'; border-radius: 10px; }"
            "QLabel { color: #FFFFFF; font-size: 14px; }"
            "QPushButton { background-color: #4CAF50; color: #FFFFFF; border-radius: 5px; padding: 8px; font-size: 12px; }"
            "QPushButton:hover { background-color: #45A049; }"
            );
            msgBox.exec();

            for (const auto& [box, _] : positionBoxes) {
            if (box) box->deleteLater();
            }
            positionBoxes.clear();
            if (saveButton) saveButton->deleteLater();
            if (cancelButton) cancelButton->deleteLater(); // Added cleanup for cancelButton

        } else {
            QMessageBox msgBox;
            msgBox.setIcon(QMessageBox::Critical);
            msgBox.setWindowTitle("❌ Error");
            msgBox.setText("Failed to set lineup!");
            msgBox.setStyleSheet(
            "QMessageBox { background-color: #1E1E2F; color: #FFFFFF; font-family: 'Segoe UI'; border-radius: 10px; }"
            "QLabel { color: #FFFFFF; font-size: 14px; }"
            "QPushButton { background-color: #E94E77; color: #FFFFFF; border-radius: 5px; padding: 8px; font-size: 12px; }"
            "QPushButton:hover { background-color: #C94063; }"
            );
            msgBox.exec();
        }
    });

    // Connect "Cancel" button
    connect(cancelButton, &QPushButton::clicked, this, [this, cancelButton, saveButton]() {
        qDebug() << "Cancel clicked";
        for (const auto& [box, _] : positionBoxes) {
            if (box) {
                qDebug() << "Deleting combo box:" << box;
                box->deleteLater();
            }
        }
        positionBoxes.clear();
        if (cancelButton) {
            qDebug() << "Deleting cancelButton:" << cancelButton;
            cancelButton->deleteLater();
        }
        if (saveButton) {
            qDebug() << "Deleting saveButton:" << saveButton;
            saveButton->deleteLater();
        }
        
        qDebug() << "Cancel cleanup complete";
    });

    ui->line_up_widget->show();
}

void displaymatch_coach::on_setLineupTriggered() {
    QModelIndexList selectedRows = ui->allmatches->selectionModel()->selectedRows();
    if (selectedRows.isEmpty()) {
        QMessageBox::warning(nullptr, "Error", "No match selected!");
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

    // Check if the match is already played or is currently playing
    if (match.getStatus() == "Played" || match.getStatus() == "Playing") {
        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setWindowTitle("⚠️ Error");
        msgBox.setText("You cannot set a lineup for a match that has already been played or is currently playing!");
        msgBox.setStyleSheet(
            "QMessageBox { background-color: #2A2A3A; color: #FFFFFF; font-family: 'Segoe UI'; border-radius: 10px; }"
            "QLabel { color: #FFFFFF; font-size: 14px; }"
            "QPushButton { background-color: #E94E77; color: #FFFFFF; border-radius: 5px; padding: 8px; font-size: 12px; }"
            "QPushButton:hover { background-color: #C94063; }"
        );
        msgBox.exec();
        return;
    }

    // Get the current coach's team id
    const Employee& currentUser = SessionManager::instance().getCurrentUser();
    int coachId = currentUser.getId();
    Team* team = Team::getTeamByCoachId(coachId);
    int selectedTeamId = team ? team->getId() : -1;
    delete team;
    if (selectedTeamId == -1) {
        QMessageBox::warning(this, "Error", "Could not determine your team!");
        return;
    }

    // Lineup selection
    QDialog dialog(this);
    dialog.setWindowTitle("Set Lineup");
    QVBoxLayout *mainLayout = new QVBoxLayout(&dialog);
    QFormLayout *formLayout = new QFormLayout();

    QComboBox *lineupBox = new QComboBox(&dialog);
    lineupBox->addItem("4-3-3");
    lineupBox->addItem("4-4-2");
    lineupBox->setCurrentText(ui->Line_up->currentText());
    formLayout->addRow("Lineup:", lineupBox);

    mainLayout->addLayout(formLayout);

    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, &dialog);
    buttonBox->button(QDialogButtonBox::Cancel)->setObjectName("cancelButton");
    connect(buttonBox, &QDialogButtonBox::accepted, &dialog, [&]() {
        QString selectedLineup = lineupBox->currentText();
        setupLineupWidget(matchId, selectedTeamId, selectedLineup);
        ui->tabWidget->setCurrentWidget(ui->line_up_widget); // Switch to the lineup widget
        dialog.accept();
    });
    connect(buttonBox, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);
    mainLayout->addWidget(buttonBox);

    dialog.exec();
}
void displaymatch_coach::updateAvailablePlayers() {
    if (updating) {
        qDebug() << "Skipping update due to recursion guard";
        return;
    }
    updating = true;
    qDebug() << "Starting updateAvailablePlayers...";

    // Disconnect all signals to prevent recursion
    for (const auto& [box, _] : positionBoxes) {
        disconnect(box, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &displaymatch_coach::updateAvailablePlayers);
    }

    // Collect current selections
    QMap<QComboBox*, int> currentSelections;
    for (const auto& [box, _] : positionBoxes) {
        int id = box->currentData().toInt();
        currentSelections[box] = id;
        qDebug() << "Box:" << box << "Current ID:" << id;
    }

    // Update each combobox
    for (const auto& [box, pos] : positionBoxes) {
        qDebug() << "Updating box:" << box << "Position:" << pos;
        int currentId = currentSelections[box];
        QList<int> selectedIds;
        for (const auto& [otherBox, _] : positionBoxes) {
            if (otherBox != box) {
                int id = currentSelections[otherBox];
                if (id != -1) selectedIds.append(id);
            }
        }

        box->clear();
        qDebug() << "Cleared box:" << box;
        box->addItem("Select Player", -1);

        // Use a QList with status
        using PlayerInfo = std::tuple<int, QString, int>; // id, name, status
        const QList<PlayerInfo>* playerList = nullptr;
        if (pos == "Goalkeeper") playerList = &allGoalkeepers;
        else if (pos == "Defender") playerList = &allDefenders;
        else if (pos == "Midfielder") playerList = &allMidfielders;
        else if (pos == "Forward") playerList = &allForwards;

        if (playerList) {
            for (const auto& player : *playerList) {
                int playerId = std::get<0>(player);
                QString playerName = std::get<1>(player);
                int playerStatus = std::get<2>(player);

                if (!selectedIds.contains(playerId) || playerId == currentId) {
                    box->addItem(playerName, playerId);
                    int index = box->count() - 1;
                    if (playerStatus == 1) { // Player cannot play
                        // Disable the item by removing the enabled flag
                        box->model()->setData(box->model()->index(index, 0), QVariant(false), Qt::UserRole - 1);
                        box->setItemData(index, QColor("#808080"), Qt::ForegroundRole); // Gray out text
                    }
                }
            }
            qDebug() << "Populated box:" << box << "with" << (box->count() - 1) << "players";
            if (currentId != -1) {
                int index = box->findData(currentId);
                if (index != -1) {
                    // Only set the current index if the player is playable (status == 0)
                    QVariant isEnabled = box->itemData(index, Qt::UserRole - 1);
                    if (isEnabled.isNull() || isEnabled.toBool()) { // Enabled by default or explicitly true
                        box->setCurrentIndex(index);
                        qDebug() << "Restored selection for box:" << box << "to ID:" << currentId << "at index:" << index;
                    } else {
                        qDebug() << "Skipped selection for box:" << box << "ID:" << currentId << "is disabled";
                    }
                } else {
                    qDebug() << "Could not restore selection for box:" << box << "ID:" << currentId << "not found";
                }
            }
        }
    }

    // Reconnect signals
    for (const auto& [box, _] : positionBoxes) {
        connect(box, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &displaymatch_coach::updateAvailablePlayers);
    }

    updating = false;
    qDebug() << "Update complete.";
}