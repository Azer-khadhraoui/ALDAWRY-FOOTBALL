#include "../matchheaders/match.h"
#include <QSqlQuery>
#include <QVariant>
#include <QSqlError>
#include <QDebug>
#include <QPdfWriter>
#include <QPainter>
#include <QFileDialog>
#include <QRandomGenerator> // Add this include for QRandomGenerator
#include <QMessageBox>
#include <algorithm>

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

    // Set PDF metadata
    pdfWriter.setTitle("Aldawry Match Schedule");
    pdfWriter.setCreator("Aldawry");

    QPainter painter(&pdfWriter);
    painter.setRenderHint(QPainter::Antialiasing);

    // Fonts
    QFont titleFont("Verdana", 22, QFont::Bold);
    QFont headerFont("Verdana", 12, QFont::Bold);
    QFont contentFont("Arial", 11);
    contentFont.setLetterSpacing(QFont::PercentageSpacing, 110);
    QFont footerFont("Arial", 9);
    footerFont.setItalic(true);

    // Colors and Gradients
    QLinearGradient headerGradient(0, 0, 0, 50);
    headerGradient.setColorAt(0, QColor(46, 125, 50)); // Dark green (pitch)
    headerGradient.setColorAt(1, QColor(76, 175, 80)); // Lighter green
    QLinearGradient pageGradient(0, 0, 0, 200);
    pageGradient.setColorAt(0, Qt::white); // White at top
    pageGradient.setColorAt(1, QColor(245, 245, 245)); // Light gray
    QLinearGradient titleGradient(0, 0, 0, 40);
    titleGradient.setColorAt(0, QColor(33, 33, 33));
    titleGradient.setColorAt(1, Qt::black);
    QLinearGradient footerGradient(0, 0, 0, 20);
    footerGradient.setColorAt(0, QColor(46, 125, 50));
    footerGradient.setColorAt(1, QColor(76, 175, 80));
    QColor textColor(33, 33, 33); // Dark gray for content
    QColor headerTextColor(Qt::white);
    QColor tableBgColor(255, 255, 255, 230); // Semi-transparent white
    QColor rowColor(232, 245, 233); // Very light green for all rows (#E8F5E9)
    QColor fieldColor(46, 125, 50); // Green for field outline
    QColor footerColor(46, 125, 50); // Dark green for footer

    // Page dimensions
    int pageWidth = pdfWriter.width();
    int pageHeight = pdfWriter.height();
    int margin = 40; // Increased for spaciousness

    // Load logo
    QImage logo(":/logo football.png");

    // Calculate pages
    QList<Match> matches = readAllMatches();
    std::sort(matches.begin(), matches.end(), [](const Match &a, const Match &b) {
        return a.getMatchDateTime() < b.getMatchDateTime();
    });
    int rowsPerPage = (pageHeight - 280) / 40;
    int totalPages = matches.isEmpty() ? 1 : (matches.size() + rowsPerPage - 1) / rowsPerPage;
    int currentPage = 1;

    // Drawing parameters
    int y = 80;
    int rowHeight = 40;
    int headerHeight = 45;
    const int colWidths[] = {140, 140, 110, 140};
    const int totalWidth = colWidths[0] + colWidths[1] + colWidths[2] + colWidths[3];
    bool firstPage = true;

    auto drawPage = [&](int pageNum) {
        if (!firstPage) {
            pdfWriter.newPage();
            y = 80;
        }
        firstPage = false;

        // Page background with gradient
        painter.setBrush(pageGradient);
        painter.setPen(Qt::NoPen);
        painter.drawRect(0, 0, pageWidth, pageHeight);

        // Logo with shadow (smaller size)
        if (!logo.isNull()) {
            int maxLogoWidth = pageWidth / 4;
            int logoHeight = logo.height() * maxLogoWidth / logo.width();
            int logoX = (pageWidth - maxLogoWidth) / 2;
            // Shadow effect
            painter.setOpacity(0.2);
            painter.setBrush(Qt::black);
            painter.drawRect(logoX + 5, 20 + 5, maxLogoWidth, logoHeight);
            painter.setOpacity(1.0);
            painter.drawImage(QRect(logoX, 20, maxLogoWidth, logoHeight), logo);
            y = 20 + logoHeight + 20;
        } else {
            painter.setFont(titleFont);
            painter.setPen(textColor);
            painter.drawText(0, 40, pageWidth, 40, Qt::AlignCenter, "Aldawry");
            y = 80;
        }

        // Title with gradient
        painter.setFont(titleFont);
        painter.setPen(QColor(0, 0, 0, 50)); // Shadow
        painter.drawText(2, y + 2, pageWidth, 40, Qt::AlignCenter, "Match Schedule");
        painter.setPen(QPen(titleGradient, 0));
        painter.drawText(0, y, pageWidth, 40, Qt::AlignCenter, "Match Schedule");
        y += 80; // Increased margin for professional look

        // Football field outline behind table
        int tableHeight = headerHeight + (matches.size() < rowsPerPage ? matches.size() : rowsPerPage) * rowHeight + 10;
        painter.setOpacity(0.1);
        painter.setBrush(fieldColor);
        painter.setPen(QPen(Qt::white, 1));
        // Main field
        painter.drawRect(margin - 20, y - 20, totalWidth + 40, tableHeight + 40);
        // Center line
        painter.drawLine(margin - 20, y - 20 + (tableHeight + 40) / 2, margin + totalWidth + 20, y - 20 + (tableHeight + 40) / 2);
        // Center circle
        painter.drawEllipse(QPoint(margin + totalWidth / 2 + 20, y - 20 + (tableHeight + 40) / 2), 30, 30);
        // Penalty areas
        painter.drawRect(margin - 20, y - 20, 60, 80); // Left
        painter.drawRect(margin + totalWidth - 40, y - 20, 60, 80); // Right
        // Goalposts
        painter.setPen(QPen(Qt::white, 2));
        painter.drawLine(margin - 20, y - 20 + 30, margin - 20, y - 20 + 50); // Left goalpost
        painter.drawLine(margin - 20, y - 20 + 30, margin - 30, y - 20 + 30);
        painter.drawLine(margin - 20, y - 20 + 50, margin - 30, y - 20 + 50);
        painter.drawLine(margin + totalWidth + 20, y - 20 + 30, margin + totalWidth + 20, y - 20 + 50); // Right goalpost
        painter.drawLine(margin + totalWidth + 20, y - 20 + 30, margin + totalWidth + 30, y - 20 + 30);
        painter.drawLine(margin + totalWidth + 20, y - 20 + 50, margin + totalWidth + 30, y - 20 + 50);
        painter.setOpacity(1.0);

        // Table background with inner shadow
        painter.setPen(Qt::NoPen);
        painter.setBrush(QColor(0, 0, 0, 50));
        painter.drawRect(margin - 5 + 3, y - 5 + 3, totalWidth + 10, tableHeight);
        painter.setBrush(tableBgColor);
        painter.setPen(QPen(fieldColor, 1, Qt::DashLine));
        painter.drawRect(margin - 5, y - 5, totalWidth + 10, tableHeight);

        // Draw table headers
        painter.setFont(headerFont);
        painter.setBrush(headerGradient);
        painter.drawRect(margin, y, totalWidth, headerHeight);

        painter.setPen(headerTextColor);
        int colX = margin;
        QStringList headers = {"Team 1", "Team 2", "Date & Time", "Competition"};
        for (int i = 0; i < headers.size(); ++i) {
            if (i < 2) { // Add football icon for team columns
                painter.setPen(Qt::NoPen);
                painter.setBrush(Qt::black);
                painter.drawEllipse(colX + 10, y + 15, 10, 10); // Football shape
                painter.setBrush(Qt::white);
                painter.drawEllipse(colX + 10, y + 15, 8, 8); // Inner white
                painter.setPen(headerTextColor);
                painter.drawText(colX + 25, y + 32, headers[i]);
                painter.drawLine(colX + 25, y + 35, colX + 25 + painter.fontMetrics().horizontalAdvance(headers[i]), y + 35); // Underline
            } else {
                painter.drawText(colX + 15, y + 32, headers[i]);
                painter.drawLine(colX + 15, y + 35, colX + 15 + painter.fontMetrics().horizontalAdvance(headers[i]), y + 35);
            }
            colX += colWidths[i];
        }

        // Header lines
        painter.setPen(QPen(Qt::black, 1));
        colX = margin;
        for (int i = 0; i <= headers.size(); ++i) {
            painter.drawLine(colX, y, colX, y + headerHeight);
            colX += colWidths[i];
        }
        painter.drawLine(margin, y + headerHeight, margin + totalWidth, y + headerHeight);
        y += headerHeight;

        // Footer with adjusted positioning
        painter.setFont(footerFont);
        painter.setPen(QPen(footerColor, 1, Qt::DashLine));
        painter.drawLine(margin, pageHeight - 80, pageWidth - margin, pageHeight - 80); // Moved up to pageHeight - 80
        // Football icons (10px below the line)
        painter.setPen(Qt::NoPen);
        painter.setBrush(footerColor);
        painter.drawEllipse(pageWidth / 2 - 100, pageHeight - 70, 8, 8); // Moved to pageHeight - 70
        painter.setBrush(Qt::white);
        painter.drawEllipse(pageWidth / 2 - 100, pageHeight - 70, 6, 6);
        painter.setBrush(footerColor);
        painter.drawEllipse(pageWidth / 2 + 90, pageHeight - 70, 8, 8);
        painter.setBrush(Qt::white);
        painter.drawEllipse(pageWidth / 2 + 90, pageHeight - 70, 6, 6);
        // Footer text (10px below the icons)
        painter.setPen(QPen(footerGradient, 0));
        QString footerText = QString("Generated on %1 by Aldawry | For the Love of Football | Page %2 of %3")
                                .arg(QDate::currentDate().toString("yyyy-MM-dd"))
                                .arg(pageNum)
                                .arg(totalPages);
        painter.drawText(0, pageHeight - 60, pageWidth, 20, Qt::AlignCenter, footerText); // Moved to pageHeight - 60
    };

    if (matches.isEmpty()) {
        drawPage(currentPage);
        painter.setFont(contentFont);
        painter.setPen(textColor);
        painter.drawText(margin, y + 20, "No matches scheduled. Kick off with Aldawry!");
        painter.end();
        return;
    }

    int matchIndex = 0;
    QDateTime now = QDateTime::currentDateTime();
    while (matchIndex < matches.size()) {
        drawPage(currentPage++);

        // Draw matches
        while (matchIndex < matches.size() && y + rowHeight <= pageHeight - 80) {
            const Match &match = matches[matchIndex];

            // Draw row with consistent border color
            painter.setBrush(rowColor); // Use the same light green for all rows
            painter.setPen(QPen(Qt::black, 1)); // Consistent black border for all rows
            painter.drawRect(margin, y, totalWidth, rowHeight);

            // Draw cell content (centered)
            int colX = margin;
            painter.setPen(textColor);
            painter.setFont(QFont("Arial", 11, QFont::DemiBold)); // Bolder team names
            QString team1 = painter.fontMetrics().elidedText(match.getTeamAName(), Qt::ElideRight, colWidths[0] - 10);
            QString team2 = painter.fontMetrics().elidedText(match.getTeamBName(), Qt::ElideRight, colWidths[1] - 10);
            painter.drawText(colX, y, colWidths[0], rowHeight, Qt::AlignCenter, team1);
            colX += colWidths[0];
            painter.drawText(colX, y, colWidths[1], rowHeight, Qt::AlignCenter, team2);
            colX += colWidths[1];
            painter.setFont(contentFont);
            QString dateTime = match.getMatchDateTime().toString("yyyy-MM-dd HH:mm");
            QString competition = painter.fontMetrics().elidedText(match.getCompetitionName(), Qt::ElideRight, colWidths[3] - 10);
            painter.drawText(colX, y, colWidths[2], rowHeight, Qt::AlignCenter, dateTime);
            colX += colWidths[2];
            painter.drawText(colX, y, colWidths[3], rowHeight, Qt::AlignCenter, competition);

            // Cell lines
            colX = margin;
            painter.setPen(QPen(Qt::black, 1));
            for (int j = 0; j <= 4; ++j) {
                painter.drawLine(colX, y, colX, y + rowHeight);
                colX += colWidths[j];
            }
            painter.drawLine(margin, y + rowHeight, margin + totalWidth, y + rowHeight);

            y += rowHeight;
            matchIndex++;
        }
    }

    painter.end();
}

// Add this after the constructors or anywhere in the Match class implementation
bool Match::operator==(const Match& other) const {
    return this->id_match == other.id_match;
}
QList<QList<QPair<int, int>>> Match::generateRoundRobinFixture(const QList<int>& teamIds)
{
    QList<QList<QPair<int, int>>> rounds;
    int numTeams = teamIds.size();

    if (numTeams < 2) {
        qDebug() << "Fixture generation failed: At least 2 teams required.";
        return rounds;
    }

    // Handle odd number of teams by adding a dummy team
    QList<int> teams = teamIds;
    bool hasBye = false;
    if (numTeams % 2 != 0) {
        teams.append(-1); // Dummy team
        numTeams++;
        hasBye = true;
    }

    // Create a list for scheduling
    QList<int> schedule;
    for (int i = 0; i < numTeams; ++i) {
        schedule.append(i); // Indices into teams list
    }

    // Generate first round-robin (numTeams - 1 rounds)
    for (int round = 0; round < numTeams - 1; ++round) {
        QList<QPair<int, int>> roundMatches;

        // Pair teams: 1 vs. n, 2 vs. n-1, ..., n/2 vs. n/2+1
        for (int i = 0; i < numTeams / 2; ++i) {
            int team1Idx = schedule[i];
            int team2Idx = schedule[numTeams - 1 - i];
            int team1Id = teams[team1Idx];
            int team2Id = teams[team2Idx];

            // Skip invalid pairs (shouldn't happen)
            if (team1Id == -1 && team2Id == -1) {
                continue;
            }

            // Alternate home/away for balance
            if (round % 2 == 0) {
                roundMatches.append(qMakePair(team1Id, team2Id)); // team1 home
            } else {
                roundMatches.append(qMakePair(team2Id, team1Id)); // team2 home
            }
        }
        rounds.append(roundMatches);

        // Rotate: Keep team 0 fixed, rotate others clockwise
        // Move last team to position 1, shift others right
        int last = schedule[numTeams - 1];
        for (int i = numTeams - 1; i > 1; --i) {
            schedule[i] = schedule[i - 1];
        }
        schedule[1] = last;
    }

    // Generate second round-robin (reverse home/away)
    for (int round = 0; round < numTeams - 1; ++round) {
        QList<QPair<int, int>> roundMatches;
        for (const auto& match : rounds[round]) {
            roundMatches.append(qMakePair(match.second, match.first)); // Swap home/away
        }
        rounds.append(roundMatches);
    }

    return rounds;
}
QList<QList<QPair<int, int>>> Match::generateKnockoutFixture(const QList<int>& teamIds)
{
    QList<QList<QPair<int, int>>> rounds;
    int numTeams = teamIds.size();

    if (numTeams < 2) {
        qDebug() << "Knockout fixture generation failed: At least 2 teams required.";
        return rounds;
    }

    // Calculate rounds: ceil(log2(numTeams))
    int roundsNeeded = qCeil(qLn(numTeams) / qLn(2));
    int teamsInFirstRound = 1 << roundsNeeded; // Next power of 2
    int byes = teamsInFirstRound - numTeams;

    // Shuffle teams for random pairing
    QList<int> currentTeams = teamIds;
    std::random_shuffle(currentTeams.begin(), currentTeams.end(), [](int max) {
        return QRandomGenerator::global()->bounded(max);
    });

    // First round: pair teams, assign byes
    QList<QPair<int, int>> firstRound;
    int matches = (numTeams - byes) / 2;
    int teamIndex = 0;

    // Actual matches
    for (int i = 0; i < matches && teamIndex + 1 < numTeams; ++i) {
        firstRound.append(qMakePair(currentTeams[teamIndex], currentTeams[teamIndex + 1]));
        teamIndex += 2;
    }

    // Byes
    for (int i = 0; i < byes && teamIndex < numTeams; ++i) {
        firstRound.append(qMakePair(currentTeams[teamIndex], -1));
        teamIndex++;
    }

    rounds.append(firstRound);

    // Subsequent rounds: placeholders (-2)
    int teamsRemaining = teamsInFirstRound / 2;
    for (int round = 1; round < roundsNeeded; ++round) {
        QList<QPair<int, int>> nextRound;
        for (int i = 0; i < teamsRemaining / 2; ++i) {
            nextRound.append(qMakePair(-2, -2));
        }
        rounds.append(nextRound);
        teamsRemaining /= 2;
    }

    return rounds;
}

bool Match::generateMatchDates(int competitionId, const QString &competitionType, const QDate &startDate, const QDate &endDate, int /*nbTeams*/)
{
    // Validate competition type
    QString compTypeLower = competitionType.toLower();
    if (compTypeLower != "ligue" && compTypeLower != "knockout") {
        QString errorMessage = "Match generation failed: Only 'ligue' or 'knockout' competitions supported.";
        qDebug() << errorMessage;
        QMessageBox::critical(nullptr, "Error", errorMessage);
        return false;
    }

    // Step 1: Fetch teams and stadiums
    QSqlQuery teamQuery;
    teamQuery.prepare("SELECT P.ID_TEAM, E.HOME_STADIUM "
                      "FROM PARTICIPATION P "
                      "JOIN EQUIPE E ON P.ID_TEAM = E.ID_TEAM "
                      "WHERE P.ID_COMP = :compId");
    teamQuery.bindValue(":compId", competitionId);

    if (!teamQuery.exec()) {
        QString errorMessage = "Match generation failed: Unable to fetch teams: " + teamQuery.lastError().text();
        qDebug() << errorMessage;
        QMessageBox::critical(nullptr, "Error", errorMessage);
        return false;
    }

    QList<int> teamIds;
    QMap<int, QString> teamStadiums;
    while (teamQuery.next()) {
        int teamId = teamQuery.value("ID_TEAM").toInt();
        QString stadium = teamQuery.value("HOME_STADIUM").toString();
        teamIds.append(teamId);
        teamStadiums[teamId] = stadium;
    }

    int numTeams = teamIds.size();
    if (numTeams < 2) {
        QString errorMessage = "Match generation failed: At least 2 teams required.";
        qDebug() << errorMessage;
        QMessageBox::critical(nullptr, "Error", errorMessage);
        return false;
    }

    // Step 2: Generate fixture based on competition type
    QList<QList<QPair<int, int>>> rounds;
    if (compTypeLower == "ligue") {
        rounds = generateRoundRobinFixture(teamIds);
    } else { // knockout
        rounds = generateKnockoutFixture(teamIds);
    }
    int totalRounds = rounds.size();

    // Step 3: Validate date range
    QDate expectedEndDate = startDate.addDays(totalRounds * 7);
    if (expectedEndDate > endDate) {
        QString errorMessage = "Match generation failed: End date exceeded. Requires " +
                               QString::number(totalRounds) + " weeks.";
        qDebug() << errorMessage;
        QMessageBox::critical(nullptr, "Error", errorMessage);
        return false;
    }

    // Step 4: Referees
    QStringList referees = {"Pierluigi Collina", "Howard Webb", "Markus Merk", "Massimo Busacca", "Viktor Kassai"};

    // Step 5: Prepare insert queries
    QSqlQuery ligueFirstRoundQuery;
    ligueFirstRoundQuery.prepare("INSERT INTO Match (ID_MATCH, ID_COMPETITION, ID_TEAMA, ID_TEAMB, "
                                 "STADIUM, REFEREE_NAME, MATCH_DATETIME, STATUS_M) "
                                 "VALUES (:id, :compId, :teamA, :teamB, :stadium, :referee, :dateTime, :status)");

    QSqlQuery knockoutLaterRoundQuery;
    knockoutLaterRoundQuery.prepare("INSERT INTO Match (ID_MATCH, ID_COMPETITION, STADIUM, REFEREE_NAME, "
                                    "MATCH_DATETIME, STATUS_M) "
                                    "VALUES (:id, :compId, :stadium, :referee, :dateTime, :status)");

    QDate currentRoundDate = startDate;
    bool isFirstRound = true;

    for (const auto& round : rounds) {
        int matchesScheduled = 0; // Matches per day
        int dayOffset = 0; // Days within round
        QTime matchStartTime(14, 0); // Start at 14:00

        for (const auto& match : round) {
            int homeTeamId = match.first;
            int awayTeamId = match.second;

            // Skip byes (-1)
            if (homeTeamId == -1 || awayTeamId == -1) {
                continue;
            }

            // Check if day is full (4 matches: 14:00, 16:00, 18:00, 20:00)
            if (matchesScheduled >= 4) {
                dayOffset++;
                matchStartTime = QTime(14, 0);
                matchesScheduled = 0;
            }

            int newMatchId = generateNewMatchId();
            QDate matchDate = currentRoundDate.addDays(dayOffset);
            QDateTime matchDateTime(matchDate, matchStartTime);
            QString referee = referees.at(QRandomGenerator::global()->bounded(referees.size()));

            if (compTypeLower == "ligue" || (compTypeLower == "knockout" && isFirstRound && homeTeamId != -2 && awayTeamId != -2)) {
                // Ligue or knockout first round: full data
                ligueFirstRoundQuery.bindValue(":id", newMatchId);
                ligueFirstRoundQuery.bindValue(":compId", competitionId);
                ligueFirstRoundQuery.bindValue(":teamA", homeTeamId);
                ligueFirstRoundQuery.bindValue(":teamB", awayTeamId);
                ligueFirstRoundQuery.bindValue(":stadium", teamStadiums.value(homeTeamId, "Unknown Stadium"));
                ligueFirstRoundQuery.bindValue(":referee", referee);
                ligueFirstRoundQuery.bindValue(":dateTime", matchDateTime);
                ligueFirstRoundQuery.bindValue(":status", "Scheduled");

                if (!ligueFirstRoundQuery.exec()) {
                    QString errorMessage = "Match insertion failed for ID " + QString::number(newMatchId) +
                                           ": " + ligueFirstRoundQuery.lastError().text();
                    qDebug() << errorMessage;
                    QMessageBox::critical(nullptr, "Error", errorMessage);
                    return false;
                }
            } else {
                // Knockout later rounds: omit ID_TEAMA, ID_TEAMB
                knockoutLaterRoundQuery.bindValue(":id", newMatchId);
                knockoutLaterRoundQuery.bindValue(":compId", competitionId);
                knockoutLaterRoundQuery.bindValue(":stadium", QString("TBD"));
                knockoutLaterRoundQuery.bindValue(":referee", referee);
                knockoutLaterRoundQuery.bindValue(":dateTime", matchDateTime);
                knockoutLaterRoundQuery.bindValue(":status", "Scheduled");

                if (!knockoutLaterRoundQuery.exec()) {
                    QString errorMessage = "Match insertion failed for ID " + QString::number(newMatchId) +
                                           ": " + knockoutLaterRoundQuery.lastError().text();
                    qDebug() << errorMessage;
                    QMessageBox::critical(nullptr, "Error", errorMessage);
                    return false;
                }
            }

            matchesScheduled++;
            matchStartTime = matchStartTime.addSecs(2 * 60 * 60); // 2 hours
        }

        // Next round: 7 days from start
        currentRoundDate = currentRoundDate.addDays(7);
        isFirstRound = false;
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
void Match::updateMatchStatuses() {
    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isOpen()) {
        qDebug() << "Database not open when updating match statuses";
        return;
    }

    QSqlQuery query;

    // Update matches to "Playing" if the current time is within the match time
    query.prepare("UPDATE Match "
                  "SET STATUS_M = 'Playing' "
                  "WHERE MATCH_DATETIME <= :currentDateTime AND "
                  "MATCH_DATETIME > :twoHoursAgo AND STATUS_M = 'Scheduled'");
    query.bindValue(":currentDateTime", QDateTime::currentDateTime());
    query.bindValue(":twoHoursAgo", QDateTime::currentDateTime().addSecs(-2 * 60 * 60)); // 2 hours ago

    if (!query.exec()) {
        qDebug() << "Error updating matches to 'Playing':" << query.lastError().text();
    } else {
        qDebug() << "Matches updated to 'Playing' successfully.";
    }

    // Update matches to "Played" if the match ended more than 2 hours ago
    query.prepare("UPDATE Match "
                  "SET STATUS_M = 'Played' "
                  "WHERE MATCH_DATETIME <= :twoHoursAgo AND STATUS_M = 'Playing'");
    query.bindValue(":twoHoursAgo", QDateTime::currentDateTime().addSecs(-2 * 60 * 60)); // 2 hours ago

    if (!query.exec()) {
        qDebug() << "Error updating matches to 'Played':" << query.lastError().text();
    } else {
        qDebug() << "Matches updated to 'Played' successfully.";
    }
}