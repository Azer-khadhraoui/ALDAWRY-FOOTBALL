#include "match.h"
#include <QSqlQuery>
#include <QVariant>
#include <QSqlError>
#include <QDebug>

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
                  "JOIN EQUIPE T1 ON M.ID_TEAMA = T1.ID_TEAM "
                  "JOIN EQUIPE T2 ON M.ID_TEAMB = T2.ID_TEAM "
                  "JOIN COMPETITION C ON M.ID_COMPETITION = C.ID_COMPETITION");
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
        match.setCompetitionName(query.value("COMPETITION_NAME").toString()); // Add this line

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

    // Prepare and execute the SQL query with a LIKE clause for filtering
    QSqlQuery query;
    query.prepare("SELECT M.ID_MATCH, M.ID_COMPETITION, M.ID_TEAMA, M.ID_TEAMB, M.STADIUM, "
                  "M.REFEREE_NAME, M.SCOREA, M.SCOREB, M.STATUS_M, M.METEO, M.MATCH_DATETIME, "
                  "T1.TEAM_NAME AS TEAM_A_NAME, T2.TEAM_NAME AS TEAM_B_NAME, "
                  "C.COMP_NAME AS COMPETITION_NAME "
                  "FROM Match M "
                  "JOIN EQUIPE T1 ON M.ID_TEAMA = T1.ID_TEAM "
                  "JOIN EQUIPE T2 ON M.ID_TEAMB = T2.ID_TEAM "
                  "JOIN COMPETITION C ON M.ID_COMPETITION = C.ID_COMPETITION "
                  "WHERE T1.TEAM_NAME LIKE :text OR T2.TEAM_NAME LIKE :text OR C.COMP_NAME LIKE :text OR M.REFEREE_NAME LIKE :text OR M.STADIUM LIKE :text OR M.MATCH_DATETIME LIKE :text");
    query.bindValue(":text", "%" + text + "%");

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
                  "REFEREE_NAME = :referee, SCOREA = :scoreA, SCOREB = :scoreB, MATCH_DATETIME = :matchDateTime "
                  "WHERE ID_MATCH = :id");
    query.bindValue(":teamA", id_teamA);
    query.bindValue(":teamB", id_teamB);
    query.bindValue(":stadium", stadium);
    query.bindValue(":referee", referee_name);
    query.bindValue(":scoreA", scoreA);
    query.bindValue(":scoreB", scoreB);
    query.bindValue(":matchDateTime", matchDateTime);
    query.bindValue(":id", id_match);

    if (!query.exec()) {
        qDebug() << "Error modifying match:" << query.lastError().text();
        return false;
    }
    return true;
}

QList<Match> Match::sortMatches(bool ascending) {
    QList<Match> matches = readAllMatches(); // Use readAllMatches to get data

    // Sort the matches based on the date and time
    std::sort(matches.begin(), matches.end(), [ascending](const Match &a, const Match &b) {
        if (ascending) {
            return a.getMatchDateTime() < b.getMatchDateTime();
        } else {
            return a.getMatchDateTime() > b.getMatchDateTime();
        }
    });

    return matches; // Return the sorted list of matches
}

QList<Match> Match::sortMatchesByDateTime(bool ascending) {
    QList<Match> matches = readAllMatches(); // Use readAllMatches to get data

    // Sort the matches based on the date and time
    std::sort(matches.begin(), matches.end(), [ascending](const Match &a, const Match &b) {
        if (ascending) {
            return a.getMatchDateTime() < b.getMatchDateTime();
        } else {
            return a.getMatchDateTime() > b.getMatchDateTime();
        }
    });

    return matches; // Return the sorted list of matches
}