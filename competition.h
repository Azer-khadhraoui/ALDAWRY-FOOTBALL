#ifndef COMPETITION_H
#define COMPETITION_H
#include <QString>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QDate>
#include <QSqlError>


class competition
{
public:
    competition(){}
    competition(int, QString, QString, QDate, QDate, int, QString);

    // Getters
    int get_id() { return id; }
    QString get_name() { return name; }
    QString get_type() { return type; }
    QDate get_date_debut() { return date_debut; }
    QDate get_date_fin() { return date_fin; }
    int get_nb_teams() { return nb_teams; }
    QString get_reward() { return reward; }

    // Setters
    void set_id(int id) { this->id = id; }
    void set_name(QString name) { this->name = name; }
    void set_type(QString type) { this->type = type; }
    void set_date_debut(QDate date_debut) { this->date_debut = date_debut; }
    void set_date_fin(QDate date_fin) { this->date_fin = date_fin; }
    void set_nb_teams(int nb_teams) { this->nb_teams = nb_teams; }
    void set_reward(QString reward) { this->reward = reward; }

    // CRUD methods
    bool add_competition();
    bool update_competition(int);
    bool delete_competition(int);
    QSqlQueryModel* show_competitions();
    competition get_competition(int);
    bool exist_competition(int);
    QSqlQueryModel* show_competitions_by_name(QString);
    QSqlQueryModel* show_competitions_by_date();
    QSqlQueryModel* show_competitions_by_nb_teams();
    QSqlQueryModel* show_competitions_by_type(QString);
private:
    int id;
    QString name;
    QString type;
    QDate date_debut;
    QDate date_fin;
    int nb_teams;
    QString reward;
    
};

#endif // COMPETITION_H
