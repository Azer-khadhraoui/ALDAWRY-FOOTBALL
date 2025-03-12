#ifndef TEAM_H
#define TEAM_H

#include <QString>
#include <QByteArray>
#include <QMetaType>

// Register QByteArray with QMetaType to avoid deprecation warnings
Q_DECLARE_METATYPE(QByteArray)

class Team
{
public:
    Team();
    Team(const QString &teamName, const QString &homeStadium, int budget, const QString &teamABV, const QByteArray &teamLogo);
    bool Ajouter();

    // Getters
    int getId() const { return Id; }
    QString getTeamName() const { return TeamName; }
    QString getHomeStadium() const { return HomeStadium; }
    int getBudget() const { return Budget; }
    QString getTeamABV() const { return TeamABV; }
    QByteArray getTeamLogo() const { return TeamLogo; }

    // Setters
    void setId(int id) { Id = id; }
    void setTeamName(const QString &teamName) { TeamName = teamName; }
    void setHomeStadium(const QString &homeStadium) { HomeStadium = homeStadium; }
    void setBudget(int budget) { Budget = budget; }
    void setTeamABV(const QString &teamABV) { TeamABV = teamABV; }
    void setTeamLogo(const QByteArray &teamLogo) { TeamLogo = teamLogo; }

private:
    int Id;
    QString TeamName;
    QString HomeStadium;
    int Budget;
    QString TeamABV;
    QByteArray TeamLogo;
};

#endif // TEAM_H
