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
             const QString& stad, const QString& ref) :
    id_match(id), id_competition(compId), id_teamA(teamA), 
    id_teamB(teamB), stadium(stad), referee_name(ref),
    scoreA(0), scoreB(0), status("Scheduled"), meteo(0)
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
                  "STADIUM, REFEREE_NAME, SCOREA, SCOREB, STATUS_M, METEO) "
                  "VALUES (:id, :comp, :teamA, :teamB, :stadium, :referee, :scoreA, "
                  ":scoreB, :status, :meteo)");
    
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
    query.prepare("SELECT ID_MATCH, ID_COMPETITION, ID_TEAMA, ID_TEAMB, STADIUM, "
                  "REFEREE_NAME, SCOREA, SCOREB, STATUS_M, METEO FROM Match");
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

        // Add the populated Match object to the list
        matches.append(match);
    }

    return matches; // Return the list of all matches
}