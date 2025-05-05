#include "../teamheaders/team.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

Team::Team() : Id(0), Budget(0) {}

Team::Team(const QString &teamName, const QString &homeStadium, int budget, const QString &teamABV, const QByteArray &teamLogo)
    : Id(0), Budget(budget)
{
    setTeamName(teamName);
    setHomeStadium(homeStadium);
    setBudget(budget);
    setTeamABV(teamABV);
    setTeamLogo(teamLogo);
}

bool Team::Ajouter() {
    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isOpen()) {
        qDebug() << "Database is not open!";
        return false;
    }

    QSqlQuery query;
    // Include all columns, with ID_TEAM auto-incremented and GOALS_TEAM set to 0
    query.prepare("INSERT INTO HOTSTUFF.EQUIPE (TEAM_NAME, HOME_STADIUM, BUDG, GOALS_TEAM, TEAM_ABV, TEAM_LOGO) "
                  "VALUES (:team_name, :home_stadium, :budget, 0, :team_abv, :team_logo)");
    query.bindValue(":team_name", getTeamName());
    query.bindValue(":home_stadium", getHomeStadium());
    query.bindValue(":budget", getBudget());
    query.bindValue(":team_abv", getTeamABV());
    query.bindValue(":team_logo", getTeamLogo());

    // Debug all bound values
    qDebug() << "Bound values:";
    qDebug() << "  :team_name =" << query.boundValue(":team_name").toString();
    qDebug() << "  :home_stadium =" << query.boundValue(":home_stadium").toString();
    qDebug() << "  :budget =" << query.boundValue(":budget").toInt();
    qDebug() << "  :team_abv =" << query.boundValue(":team_abv").toString();
    qDebug() << "  :team_logo =" << query.boundValue(":team_logo").toByteArray().size() << "bytes";

    bool success = query.exec();
    if (!success) {
        qDebug() << "Ajouter team error:" << query.lastError().text();
        qDebug() << "Query executed:" << query.executedQuery();
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
        team->setBudget(query.value(4).toInt());
        return team;
    }
    return nullptr;  // No team found
}
