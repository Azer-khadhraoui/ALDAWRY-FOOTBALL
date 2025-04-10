#include "match.h"
#include <QSqlQuery>
#include <QVariant>
#include <QSqlError>
#include <QDebug>
#include <QPdfWriter>
#include <QPainter>
#include <QFileDialog>
#include <QRandomGenerator> // Add this include for QRandomGenerator
#include <QMessageBox>

Match::Match() : 
    id_match(0), id_competition(0), id_teamA(0), id_teamB(0),
    scoreA(0), scoreB(0), status("Scheduled"), meteo(0)
{
}

Match::Match(int id, int compId, int teamA, int teamB, 
             const QString& stad, const QString& ref, const QDateTime& dateTime) :
    id_match(id), id_competition(compId), id_teamA(teamA), 
    id_teamB(teamB), stadium(stad), referee_name(ref),
    scoreA(0), scoreB(0), status("Scheduled"), meteo(0), matchDateTime(dateTime)
{
}

bool Match::addMatch() {
    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isOpen()) {
        qDebug() << "Database not open when adding match";
        return false;
    }

    QSqlQuery query;
    query.prepare("INSERT INTO Match (ID_MATCH, ID_COMPETITION, ID_TEAMA, ID_TEAMB, "
                  "STADIUM, REFEREE_NAME, SCOREA, SCOREB, STATUS_M, METEO, MATCH_DATETIME) "
                  "VALUES (:id, :comp, :teamA, :teamB, :stadium, :referee, :scoreA, "
                  ":scoreB, :status, :meteo, :matchDateTime)");
    
    query.bindValue(":id", id_match);
    query.bindValue(":comp", id_competition);
    query.bindValue(":teamA", id_teamA);
    query.bindValue(":teamB", id_teamB);
    query.bindValue(":stadium", stadium);
    query.bindValue(":referee", referee_name);
    query.bindValue(":scoreA", scoreA);
    query.bindValue(":scoreB", scoreB);
    query.bindValue(":status", status);
    query.bindValue(":meteo", meteo);
    query.bindValue(":matchDateTime", matchDateTime);

    if (!query.exec()) {
        qDebug() << "Error adding match:" << query.lastError().text();
        return false;
    }
    return true;
}

int Match::generateNewMatchId() {
    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isOpen()) {
        qDebug() << "Database not open when generating new match ID";
        return -1;  // Return an invalid ID to indicate failure
    }

    QSqlQuery query("SELECT MAX(ID_MATCH) FROM Match");
    if (query.next()) {
        return query.value(0).toInt() + 1;
    }
    return 1;  // Start with 1 if no matches exist
}

void Match::loadTeamsIntoComboBoxes(QComboBox* team1Box, QComboBox* team2Box) {
    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isOpen()) {
        qDebug() << "Database not open when loading teams";
        return;
    }

    QSqlQuery query;
    query.exec("SELECT ID_TEAM, TEAM_NAME FROM EQUIPE ORDER BY TEAM_NAME");
    
    team1Box->clear();
    team2Box->clear();
    
    while (query.next()) {
        int id = query.value(0).toInt();
        QString name = query.value(1).toString();
        team1Box->addItem(name, id);
        team2Box->addItem(name, id);
    }
}

void Match::loadCompetitionsIntoComboBox(QComboBox* compBox) {
    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isOpen()) {
        qDebug() << "Database not open when loading competitions";
        return;
    }

    QSqlQuery query;
    query.exec("SELECT ID_COMPETITION, COMP_NAME FROM COMPETITION ORDER BY COMP_NAME");
    
    compBox->clear();
    
    while (query.next()) {
        int id = query.value(0).toInt();
        QString name = query.value(1).toString();
        compBox->addItem(name, id);
    }
}

QList<Match> Match::readAllMatches() {
    QList<Match> matches; // List to store all match objects

    // Get the default database connection
    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isOpen()) {
        qDebug() << "Database not open when reading all matches";
        return matches; // Return empty list if database is not open
    }

    // Prepare and execute the SQL query
    QSqlQuery query;
    query.prepare("SELECT M.ID_MATCH, M.ID_COMPETITION, M.ID_TEAMA, M.ID_TEAMB, M.STADIUM, "
                  "M.REFEREE_NAME, M.SCOREA, M.SCOREB, M.STATUS_M, M.METEO, M.MATCH_DATETIME, "
                  "T1.TEAM_NAME AS TEAM_A_NAME, T2.TEAM_NAME AS TEAM_B_NAME, "
                  "C.COMP_NAME AS COMPETITION_NAME "
                  "FROM Match M "
                  "LEFT JOIN EQUIPE T1 ON M.ID_TEAMA = T1.ID_TEAM "
                  "LEFT JOIN EQUIPE T2 ON M.ID_TEAMB = T2.ID_TEAM "
                  "LEFT JOIN COMPETITION C ON M.ID_COMPETITION = C.ID_COMPETITION");
    if (!query.exec()) {
        qDebug() << "Error reading matches:" << query.lastError().text();
        return matches; // Return empty list if query fails
    }

    // Process each row in the result set
    while (query.next()) {
        Match match; // Create a new Match object for each row

        // Populate the Match object using setters
        match.setId(query.value("ID_MATCH").toInt());
        match.setCompetitionId(query.value("ID_COMPETITION").toInt());
        match.setTeamA(query.value("ID_TEAMA").isNull() ? 0 : query.value("ID_TEAMA").toInt()); // Handle null team A
        match.setTeamB(query.value("ID_TEAMB").isNull() ? 0 : query.value("ID_TEAMB").toInt()); // Handle null team B
        match.setStadium(query.value("STADIUM").toString());
        match.setReferee(query.value("REFEREE_NAME").toString());
        match.setScoreA(query.value("SCOREA").toInt());
        match.setScoreB(query.value("SCOREB").toInt());
        match.setStatus(query.value("STATUS_M").toString());
        match.setMeteo(query.value("METEO").toInt()); // Retrieve the meteo value
        match.setMatchDateTime(query.value("MATCH_DATETIME").toDateTime());
        match.setTeamAName(query.value("TEAM_A_NAME").isNull() ? "Team 1" : query.value("TEAM_A_NAME").toString()); // Handle null team A name
        match.setTeamBName(query.value("TEAM_B_NAME").isNull() ? "Team 2" : query.value("TEAM_B_NAME").toString()); // Handle null team B name
        match.setCompetitionName(query.value("COMPETITION_NAME").toString());

        // Add the populated Match object to the list
        matches.append(match);
    }

    return matches; // Return the list of all matches
}

QList<Match> Match::searchMatches(const QString &text) {
    QList<Match> matches; // List to store filtered match objects

    // Get the default database connection
    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isOpen()) {
        qDebug() << "Database not open when searching matches";
        return matches; // Return empty list if database is not open
    }

    // Determine the meteo status based on the input text
    int meteoStatus = -1;
    if (text.toLower() == "sunny") {
        meteoStatus = 0;
    } else if (text.toLower() == "rainy") {
        meteoStatus = 1;
    }

    // Prepare and execute the SQL query with a LIKE clause for filtering
    QSqlQuery query;
    query.prepare("SELECT M.ID_MATCH, M.ID_COMPETITION, M.ID_TEAMA, M.ID_TEAMB, M.STADIUM, "
                  "M.REFEREE_NAME, M.SCOREA, M.SCOREB, M.STATUS_M, M.METEO, M.MATCH_DATETIME, "
                  "T1.TEAM_NAME AS TEAM_A_NAME, T2.TEAM_NAME AS TEAM_B_NAME, "
                  "C.COMP_NAME AS COMPETITION_NAME "
                  "FROM Match M "
                  "LEFT JOIN EQUIPE T1 ON M.ID_TEAMA = T1.ID_TEAM "
                  "LEFT JOIN EQUIPE T2 ON M.ID_TEAMB = T2.ID_TEAM "
                  "LEFT JOIN COMPETITION C ON M.ID_COMPETITION = C.ID_COMPETITION "
                  "WHERE T1.TEAM_NAME LIKE :text OR T2.TEAM_NAME LIKE :text OR "
                  "C.COMP_NAME LIKE :text OR M.REFEREE_NAME LIKE :text OR "
                  "M.STATUS_M LIKE :text OR (M.METEO = :meteoStatus AND :meteoStatus != -1)");
    query.bindValue(":text", "%" + text + "%");
    query.bindValue(":meteoStatus", meteoStatus);

    if (!query.exec()) {
        qDebug() << "Error searching matches:" << query.lastError().text();
        return matches; // Return empty list if query fails
    }

    // Process each row in the result set
    while (query.next()) {
        Match match; // Create a new Match object for each row

        // Populate the Match object using setters
        match.setId(query.value("ID_MATCH").toInt());
        match.setCompetitionId(query.value("ID_COMPETITION").toInt());
        match.setTeamA(query.value("ID_TEAMA").toInt());
        match.setTeamB(query.value("ID_TEAMB").toInt());
        match.setStadium(query.value("STADIUM").toString());
        match.setReferee(query.value("REFEREE_NAME").toString());
        match.setScoreA(query.value("SCOREA").toInt());
        match.setScoreB(query.value("SCOREB").toInt());
        match.setStatus(query.value("STATUS_M").toString());
        match.setMeteo(query.value("METEO").toInt());
        match.setMatchDateTime(query.value("MATCH_DATETIME").toDateTime());
        match.setTeamAName(query.value("TEAM_A_NAME").toString());
        match.setTeamBName(query.value("TEAM_B_NAME").toString());
        match.setCompetitionName(query.value("COMPETITION_NAME").toString());

        // Add the populated Match object to the list
        matches.append(match);
    }

    return matches; // Return the list of filtered matches
}

bool Match::deleteMatch(int id) {
    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isOpen()) {
        qDebug() << "Database not open when deleting match";
        return false;
    }

    QSqlQuery query;
    query.prepare("DELETE FROM Match WHERE ID_MATCH = :id");
    query.bindValue(":id", id);

    if (!query.exec()) {
        qDebug() << "Error deleting match:" << query.lastError().text();
        return false;
    }
    return true;
}

bool Match::modifyMatch() {
    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isOpen()) {
        qDebug() << "Database not open when modifying match";
        return false;
    }

    QSqlQuery query;
    query.prepare("UPDATE Match SET ID_TEAMA = :teamA, ID_TEAMB = :teamB, STADIUM = :stadium, "
                  "REFEREE_NAME = :referee, SCOREA = :scoreA, SCOREB = :scoreB, "
                  "MATCH_DATETIME = :matchDateTime, ID_COMPETITION = :competitionId, STATUS_M = :status, "
                  "METEO = :meteo " // Include METEO in the query
                  "WHERE ID_MATCH = :id");
    query.bindValue(":teamA", id_teamA);
    query.bindValue(":teamB", id_teamB);
    query.bindValue(":stadium", stadium);
    query.bindValue(":referee", referee_name);
    query.bindValue(":scoreA", scoreA);
    query.bindValue(":scoreB", scoreB);
    query.bindValue(":matchDateTime", matchDateTime);
    query.bindValue(":competitionId", id_competition);
    query.bindValue(":status", status);
    query.bindValue(":meteo", meteo); // Bind the METEO value
    query.bindValue(":id", id_match);

    if (!query.exec()) {
        qDebug() << "Error modifying match:" << query.lastError().text();
        return false;
    }
    return true;
}

QList<Match> Match::sortMatches(bool ascending) {
    QList<Match> matches = readAllMatches(); // Use readAllMatches to get data

    // Sort the matches based on the team names (Team A)
    std::sort(matches.begin(), matches.end(), [ascending](const Match &a, const Match &b) {
        return ascending ? a.getTeamAName() < b.getTeamAName() : a.getTeamAName() > b.getTeamAName();
    });

    return matches; // Return the sorted list of matches
}

QList<Match> Match::sortMatchesByDateTime(bool ascending) {
    QList<Match> matches = readAllMatches(); // Use readAllMatches to get data

    // Sort the matches based on the date and time
    std::sort(matches.begin(), matches.end(), [ascending](const Match &a, const Match &b) {
        return ascending ? a.getMatchDateTime() < b.getMatchDateTime() : a.getMatchDateTime() > b.getMatchDateTime();
    });

    return matches; // Return the sorted list of matches
}

void Match::generatePDF(const QString &filePath) {
    QPdfWriter pdfWriter(filePath);
    pdfWriter.setPageSize(QPageSize(QPageSize::A4));
    pdfWriter.setResolution(72); // Standard 72 DPI

    QPainter painter(&pdfWriter);
    painter.setRenderHint(QPainter::Antialiasing);

    // Fonts
    QFont titleFont("Arial", 16, QFont::Bold);
    QFont headerFont("Arial", 10, QFont::Bold);
    QFont contentFont("Arial", 9);

    // Title
    painter.setFont(titleFont);
    painter.drawText(0, 40, pdfWriter.width(), 40, Qt::AlignCenter, "Match Schedule");

    // Table layout
    int x = 30; // Left margin
    int y = 80; // Reduced starting position
    const int rowHeight = 25; // Standard row height
    const int headerHeight = 30; // Header height
    const int colWidths[] = {140, 140, 110, 140}; // Team 1, Team 2, Date & Time, Competition
    const int totalWidth = colWidths[0] + colWidths[1] + colWidths[2] + colWidths[3];

    // Draw table headers
    painter.setFont(headerFont);
    painter.setPen(QPen(Qt::black, 1));
    painter.setBrush(QColor(200, 200, 200)); // Light gray background for header
    painter.drawRect(x, y, totalWidth, headerHeight);

    int colX = x;
    QStringList headers = {"Team 1", "Team 2", "Date & Time", "Competition"};
    for (int i = 0; i < headers.size(); ++i) {
        painter.drawText(colX + 10, y + 20, headers[i]);
        colX += colWidths[i];
    }

    // Draw vertical lines for header
    colX = x;
    for (int i = 0; i <= headers.size(); ++i) {
        painter.drawLine(colX, y, colX, y + headerHeight);
        colX += colWidths[i];
    }
    painter.drawLine(x, y + headerHeight, x + totalWidth, y + headerHeight); // Bottom line

    y += headerHeight;

    // Draw table content
    painter.setFont(contentFont);
    painter.setBrush(Qt::NoBrush);

    // Sort matches by date and time
    QList<Match> matches = Match::readAllMatches();
    std::sort(matches.begin(), matches.end(), [](const Match &a, const Match &b) {
        return a.getMatchDateTime() < b.getMatchDateTime();
    });

    if (matches.isEmpty()) {
        painter.drawText(x, y + 15, "No matches found.");
        painter.end();
        return;
    }

    for (int i = 0; i < matches.size(); ++i) {
        const Match &match = matches[i];

        // Check for new page
        if (y + rowHeight > pdfWriter.height() - 40) {
            pdfWriter.newPage();
            y = 80; // Reset starting position

            // Redraw headers on new page
            painter.setFont(headerFont);
            painter.setBrush(QColor(200, 200, 200));
            painter.drawRect(x, y, totalWidth, headerHeight);
            colX = x;
            for (int j = 0; j < headers.size(); ++j) {
                painter.drawText(colX + 10, y + 20, headers[j]);
                colX += colWidths[j];
            }
            colX = x;
            for (int j = 0; j <= headers.size(); ++j) {
                painter.drawLine(colX, y, colX, y + headerHeight);
                colX += colWidths[j];
            }
            painter.drawLine(x, y + headerHeight, x + totalWidth, y + headerHeight);
            y += headerHeight;
            painter.setBrush(Qt::NoBrush);
        }

        // Alternating row colors
        if (i % 2 == 0) {
            painter.setBrush(QColor(240, 240, 240)); // Light gray for even rows
        } else {
            painter.setBrush(Qt::NoBrush);
        }
        painter.drawRect(x, y, totalWidth, rowHeight);

        // Draw cell content
        colX = x;
        QString team1 = painter.fontMetrics().elidedText(match.getTeamAName(), Qt::ElideRight, colWidths[0] - 20);
        QString team2 = painter.fontMetrics().elidedText(match.getTeamBName(), Qt::ElideRight, colWidths[1] - 20);
        QString dateTime = match.getMatchDateTime().toString("yyyy-MM-dd HH:mm");
        QString competition = painter.fontMetrics().elidedText(match.getCompetitionName(), Qt::ElideRight, colWidths[3] - 20);

        QStringList rowData = {team1, team2, dateTime, competition};

        for (int j = 0; j < rowData.size(); ++j) {
            painter.drawText(colX + 10, y + 15, rowData[j]);
            colX += colWidths[j];
        }

        // Draw vertical lines for cells
        colX = x;
        for (int j = 0; j <= rowData.size(); ++j) {
            painter.drawLine(colX, y, colX, y + rowHeight);
            colX += colWidths[j];
        }
        painter.drawLine(x, y + rowHeight, x + totalWidth, y + rowHeight); // Bottom line

        y += rowHeight;
    }

    painter.end();
}

// Add this after the constructors or anywhere in the Match class implementation
bool Match::operator==(const Match& other) const {
    return this->id_match == other.id_match;
}

bool Match::generateMatchDates(int competitionId, const QString &competitionType, const QDate &startDate, const QDate &endDate, int /*nbMatches*/)
{
    // Validate competition type
    if (competitionType.toLower() != "ligue") {
        QString errorMessage = "Match generation failed: Only 'ligue' competitions are supported.";
        qDebug() << errorMessage;
        QMessageBox::critical(nullptr, "Error", errorMessage);
        return false;
    }

    // Step 1: Fetch the number of teams from the COMPETITION table
    QSqlQuery compQuery;
    compQuery.prepare("SELECT nb_teams FROM COMPETITION WHERE ID_COMPETITION = :id");
    compQuery.bindValue(":id", competitionId);

    if (!compQuery.exec()) {
        QString errorMessage = "Match generation failed: Unable to fetch number of teams for competition: " + compQuery.lastError().text();
        qDebug() << errorMessage;
        QMessageBox::critical(nullptr, "Error", errorMessage);
        return false;
    }

    int numTeams = 0;
    if (compQuery.next()) {
        numTeams = compQuery.value("nb_teams").toInt();
    } else {
        QString errorMessage = "Match generation failed: Competition with ID " + QString::number(competitionId) + " not found.";
        qDebug() << errorMessage;
        QMessageBox::critical(nullptr, "Error", errorMessage);
        return false;
    }

    if (numTeams < 2) {
        QString errorMessage = "Match generation failed: At least 2 teams are required for a league competition.";
        qDebug() << errorMessage;
        QMessageBox::critical(nullptr, "Error", errorMessage);
        return false;
    }

    // Step 2: Calculate total matches for a double round-robin
    int totalMatches = numTeams * (numTeams - 1); // Double round-robin: each team plays (n-1) teams twice
    int matchesPerRound = numTeams / 2; // Number of matches per round
    int totalRounds = 2 * (numTeams - 1); // Total rounds in double round-robin

    // Step 3: Validate date range
    QDate expectedEndDate = startDate.addDays(totalRounds * 7); // 1 week = 7 days
    if (expectedEndDate > endDate) {
        QString errorMessage = "Match generation failed: End date exceeded. Competition requires " + QString::number(totalRounds) +
                               " weeks, but the provided end date is too early.";
        qDebug() << errorMessage;
        QMessageBox::critical(nullptr, "Error", errorMessage);
        return false;
    }

    // Step 4: List of referees
    QStringList referees = {"Pierluigi Collina", "Howard Webb", "Markus Merk", "Massimo Busacca", "Viktor Kassai"};

    // Step 5: Schedule matches with 1-week intervals between rounds
    QSqlQuery insertQuery;
    insertQuery.prepare("INSERT INTO Match (ID_MATCH, ID_COMPETITION, MATCH_DATETIME, STATUS_M, REFEREE_NAME) "
                        "VALUES (:id, :competitionId, :matchDateTime, :status, :referee)");

    QDate currentRoundDate = startDate;
    QTime matchStartTime(12, 0); // Start matches at 12:00 PM

    int matchIndex = 0;
    for (int round = 0; round < totalRounds; ++round) {
        // Schedule matches for the current round
        for (int m = 0; m < matchesPerRound && matchIndex < totalMatches; ++m, ++matchIndex) {
            // Generate match ID and datetime
            int newMatchId = Match::generateNewMatchId();
            QDateTime matchDateTime(currentRoundDate, matchStartTime);

            // Select a random referee
            QString referee = referees.at(QRandomGenerator::global()->bounded(referees.size()));

            // Bind values to the query
            insertQuery.bindValue(":id", newMatchId);
            insertQuery.bindValue(":competitionId", competitionId);
            insertQuery.bindValue(":matchDateTime", matchDateTime);
            insertQuery.bindValue(":status", "Scheduled");
            insertQuery.bindValue(":referee", referee);

            if (!insertQuery.exec()) {
                QString errorMessage = "Match generation failed: Unable to insert match with ID " + QString::number(newMatchId) +
                                       ". Error: " + insertQuery.lastError().text();
                qDebug() << errorMessage;
                QMessageBox::critical(nullptr, "Error", errorMessage);
                return false;
            }

            // Increment match time for the next match in the same round
            matchStartTime = matchStartTime.addSecs(2 * 60 * 60); // Increment by 2 hours

            // If the day is full, move to the next day within the same round
            if (matchStartTime.hour() >= 22) { // Stop scheduling after 10:00 PM
                matchStartTime = QTime(12, 0); // Reset to 12:00 PM
                currentRoundDate = currentRoundDate.addDays(1);
            }
        }

        // Move to the next round (1-week interval)
        currentRoundDate = currentRoundDate.addDays(7 - (currentRoundDate.daysTo(startDate) % 7)); // Align to the next week
        matchStartTime = QTime(12, 0); // Reset time for the new round
    }

    return true;
}

QStandardItemModel* Match::getMatchSummary(QObject* parent) {
    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isOpen()) {
        qDebug() << "Database not open when calculating match summary";
        return nullptr;
    }

    QSqlQuery query;
    query.prepare("SELECT STATUS_M, COUNT(*) AS count FROM Match GROUP BY STATUS_M");

    if (!query.exec()) {
        qDebug() << "Error calculating match summary:" << query.lastError().text();
        return nullptr;
    }

    // Create a model to hold the summary data
    QStandardItemModel* model = new QStandardItemModel(2, 2, parent);
    model->setHorizontalHeaderLabels({"Status", "Count"});

    // Initialize counts
    int scheduledCount = 0;
    int playedCount = 0;

    // Process the query results
    while (query.next()) {
        QString status = query.value("STATUS_M").toString();
        int count = query.value("count").toInt();

        qDebug() << "Status:" << status << ", Count:" << count; // Debug statement

        if (status == "Scheduled") {
            scheduledCount = count;
        } else if (status == "Played") {
            playedCount = count;
        }
    }

    // Populate the model with the summary data
    model->setItem(0, 0, new QStandardItem("Scheduled"));
    model->setItem(0, 1, new QStandardItem(QString::number(scheduledCount)));
    model->setItem(1, 0, new QStandardItem("Played"));
    model->setItem(1, 1, new QStandardItem(QString::number(playedCount)));

    qDebug() << "Scheduled Count:" << scheduledCount << ", Played Count:" << playedCount; // Debug statement

    return model;
}
bool Match::setLineup(int matchId, int teamId, const QString& formation, const QList<int>& playerIds) {
    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isOpen()) {
        qDebug() << "Database not open when setting lineup";
        return false;
    }

    // Delete existing lineup for this match and team
    QSqlQuery deleteQuery;
    deleteQuery.prepare("DELETE FROM TACHKILA WHERE ID_MATCH = :matchId AND ID_PLAYER IN "
                        "(SELECT ID_PLAYER FROM JOUEUR WHERE ID_TEAM = :teamId)");
    deleteQuery.bindValue(":matchId", matchId);
    deleteQuery.bindValue(":teamId", teamId);
    if (!deleteQuery.exec()) {
        qDebug() << "Error deleting existing lineup:" << deleteQuery.lastError().text();
        return false;
    }

    // Insert new lineup
    QSqlQuery insertQuery;
    insertQuery.prepare("INSERT INTO TACHKILA (ID_MATCH, ID_PLAYER, FORMATION) "
                        "VALUES (:matchId, :playerId, :formation)");

    for (int playerId : playerIds) {
        insertQuery.bindValue(":matchId", matchId);
        insertQuery.bindValue(":playerId", playerId);
        insertQuery.bindValue(":formation", formation);
        if (!insertQuery.exec()) {
            qDebug() << "Error inserting lineup:" << insertQuery.lastError().text();
            return false;
        }
    }
    return true;
}

QList<QString> Match::getLineup(int matchId, int teamId, QString& formation) {
    QList<QString> playerNames;
    QSqlQuery query;
    query.prepare("SELECT J.PLAYER_NAME, T.FORMATION "
                  "FROM TACHKILA T "
                  "JOIN JOUEUR J ON T.ID_PLAYER = J.ID_PLAYER "
                  "WHERE T.ID_MATCH = :matchId AND J.ID_TEAM = :teamId");
    query.bindValue(":matchId", matchId);
    query.bindValue(":teamId", teamId);

    if (!query.exec()) {
        qDebug() << "Error retrieving lineup:" << query.lastError().text();
        return playerNames;
    }

    while (query.next()) {
        playerNames.append(query.value("PLAYER_NAME").toString());
        if (formation.isEmpty()) { // Set formation only once
            formation = query.value("FORMATION").toString();
        }
    }
    return playerNames;
}