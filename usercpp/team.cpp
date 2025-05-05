#include "../userheaders/team.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QSqlDatabase>

Team::Team() : id(0), goals(0), budget(0) {}

Team::Team(int id, QString name, QString stadium, int goals, int budget)
    : id(id), name(name), stadium(stadium), goals(goals), budget(budget) {}

bool Team::addTeam() {
    // Check if the database connection is open
    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isOpen()) {
        qDebug() << "Database is not open!";
        return false;
    }

    // Validate inputs
    if (name.isEmpty() || stadium.isEmpty()) {
        qDebug() << "Validation failed: Team name and stadium must be non-empty.";
        return false;
    }

    if (name.length() > 20 || stadium.length() > 20) {
        qDebug() << "Validation failed: Team name or stadium exceeds 20 characters.";
        return false;
    }

    if (goals < 0 || budget < 0) {
        qDebug() << "Validation failed: Goals and budget must be non-negative.";
        return false;
    }

    QSqlQuery query;
    // Use prepared statement with placeholder bindings
    query.prepare("INSERT INTO EQUIPE (TEAM_NAME, HOME_STADIUM, GOALS_TEAM, BUDG) "
                  "VALUES (:team_name, :home_stadium, :goals, :budget)");
    query.bindValue(":team_name", getTeamName());
    query.bindValue(":home_stadium", getHomeStadium());
    query.bindValue(":budget", getBudget());
    query.bindValue(":goals",getGoals());



    // Debug all bound values
    qDebug() << "Bound values:";
    qDebug() << "  :team_name =" << query.boundValue(":team_name").toString();
    qDebug() << "  :home_stadium =" << query.boundValue(":home_stadium").toString();
    qDebug() << "  :goals =" << query.boundValue(":goals").toInt();
    qDebug() << "  :budget =" << query.boundValue(":budget").toInt();

    // Execute the query
    bool success = query.exec();
    if (!success) {
        qDebug() << "Add team error:" << query.lastError().text();
        qDebug() << "Query executed:" << query.executedQuery();
        qDebug() << "Database error:" << QSqlDatabase::database().lastError().text();
    } else {
        qDebug() << "Team added successfully: " << getTeamName();
    }

    return success;
}

Team* Team::getTeamByCoachId(int coachId) {
    QSqlQuery query;
    query.prepare("SELECT T.ID_TEAM, T.TEAM_NAME, T.HOME_STADIUM, T.GOALS_TEAM, T.BUDG "
                  "FROM EQUIPE T "
                  "JOIN COACH C ON T.ID_TEAM = C.ID_TEAM "
                  "WHERE C.ID_EMP = :coachId");
    query.bindValue(":coachId", coachId);

    if (query.exec() && query.next()) {
        Team* team = new Team();
        team->setId(query.value(0).toInt());
        team->setTeamName(query.value(1).toString());
        team->setHomeStadium(query.value(2).toString());
        team->setGoals(query.value(3).toInt());
        team->setBudget(query.value(4).toInt());
        return team;
    }
    return nullptr;  // No team found
}
