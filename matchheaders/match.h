#ifndef MATCH_H
#define MATCH_H

#include <QString>
#include <QComboBox>
#include <QList>
#include <QDateTime>
#include <QStandardItemModel> // Include this for QStandardItemModel

class Match {
private:
    int id_match;        // Unique identifier for the match
    int id_competition;  // Identifier for the competition
    int id_teamA;        // Identifier for the first team
    int id_teamB;        // Identifier for the second team
    QString stadium;     // Name of the stadium
    QString referee_name;// Name of the referee
    int scoreA;          // Score of team A
    int scoreB;          // Score of team B
    QString status;      // Status of the match (e.g., "Scheduled", "Completed")
    int meteo;           // Weather condition code (placeholder)
    QDateTime matchDateTime; // Date and time of the match
    QString teamAName;   // Name of team A
    QString teamBName;   // Name of team B
    QString competitionName; // Name of the competition

public:
    // Constructors
    Match();
    Match(int id, int compId, int teamA, int teamB, 
          const QString& stad, const QString& ref, const QDateTime& dateTime);
    static bool setLineup(int matchId, int teamId, const QString& formation, const QList<int>& playerIds);
    static QList<QString> getLineup(int matchId, int teamId, QString& formation);

    // Getters
    int getId() const { return id_match; }
    int getCompetitionId() const { return id_competition; }
    int getTeamA() const { return id_teamA; }
    int getTeamB() const { return id_teamB; }
    QString getStadium() const { return stadium; }
    QString getReferee() const { return referee_name; }
    int getScoreA() const { return scoreA; }
    int getScoreB() const { return scoreB; }
    QString getStatus() const { return status; }
    int getMeteo() const { return meteo; }
    QDateTime getMatchDateTime() const { return matchDateTime; }
    QString getTeamAName() const { return teamAName; }
    QString getTeamBName() const { return teamBName; }
    QString getCompetitionName() const { return competitionName; }

    // Setters
    void setId(int id) { id_match = id; }
    void setCompetitionId(int id) { id_competition = id; }
    void setTeamA(int id) { id_teamA = id; }
    void setTeamB(int id) { id_teamB = id; }
    void setStadium(const QString& stad) { stadium = stad; }
    void setReferee(const QString& ref) { referee_name = ref; }
    void setScoreA(int score) { scoreA = score; }
    void setScoreB(int score) { scoreB = score; }
    void setStatus(const QString& stat) { status = stat; }
    void setMeteo(int met) { meteo = met; }
    void setMatchDateTime(const QDateTime& dateTime) { matchDateTime = dateTime; }
    void setTeamAName(const QString& name) { teamAName = name; }
    void setTeamBName(const QString& name) { teamBName = name; }
    void setCompetitionName(const QString& name) { competitionName = name; }
    
    bool operator==(const Match& other) const;

    // Database operations
    bool addMatch();
    static int generateNewMatchId();
    static bool deleteMatch(int id);
    bool modifyMatch();
    static QList<Match> searchMatches(const QString &text);
    static QList<Match> sortMatches(bool ascending);
    static QList<Match> sortMatchesByDateTime(bool ascending); // Add this line
    static void generatePDF(const QString &filePath); // Add this line

    // Function to generate match dates for a competition
    static bool generateMatchDates(int competitionId, const QString &competitionType, const QDate &startDate, const QDate &endDate, int nbTeams);

    // Static methods to populate UI combo boxes
    static void loadTeamsIntoComboBoxes(QComboBox* team1Box, QComboBox* team2Box);
    static void loadCompetitionsIntoComboBox(QComboBox* compBox);
    static QList<Match> readAllMatches();

    // Add the declaration for getMatchSummary
    static QStandardItemModel* getMatchSummary(QObject* parent);
    static void updateMatchStatuses();
    static QList<QList<QPair<int, int>>> generateRoundRobinFixture(const QList<int>& teamIds);
    static QList<QList<QPair<int, int>>> generateKnockoutFixture(const QList<int>& teamIds);

    
};

#endif // MATCH_H