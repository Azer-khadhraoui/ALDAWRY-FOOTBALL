#ifndef TEAM_H
#define TEAM_H

#include <QString>
#include <QDate>
#include <QSqlQueryModel>

class Team {
public:
    Team();
    Team(int id, QString name, QString stadium, int goals, int budget);

    // Getters
    int getId() const { return id; }
    QString getTeamName() const { return name; }
    QString getHomeStadium() const { return stadium; }
    int getGoals() const { return goals; }
    int getBudget() const { return budget; }

    // Setters
    void setId(int id) { this->id = id; }
    void setTeamName(const QString& name) { this->name = name; }
    void setHomeStadium(const QString& stadium) { this->stadium = stadium; }
    void setGoals(int goals) { this->goals = goals; }
    void setBudget(int budget) { this->budget = budget; }

    // Database operations
    bool addTeam();
    Team* getTeamByCoachId(int coachId);

private:
    int id;
    QString name;
    QString stadium;
    int goals;
    int budget;
};

#endif // TEAM_H
