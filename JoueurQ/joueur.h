#ifndef JOUEUR_H
#define JOUEUR_H

#include <QString>
#include <QDate>

class joueur {
private:
    int id_player;
    int id_team;
    QString first_name;
    QString last_name;
    QString position;
    int jersey_nb;
    QDate date_of_birth;
    QString nationality;
    int goals;
    int assists;
    int injured;
    int yellow_card;
    int red_card;
    QString status;
    QByteArray img_joueur;

public:
    joueur();
    joueur(int id_team, QString first_name, QString last_name,
           QString position, int jersey_nb, QDate date_of_birth, QString nationality,
           QByteArray img_joueur = QByteArray());

    int getIdPlayer() const;
    int getIdTeam() const;
    QString getFirstName() const;
    QString getLastName() const;
    QString getPosition() const;
    int getJerseyNb() const;
    QDate getDateOfBirth() const;
    QString getNationality() const;
    int getGoals() const;
    int getAssists() const;
    int isInjured() const;
    int getYellowCard() const;
    int getRedCard() const;
    QString getStatus() const;
    QByteArray getImgJoueur() const;

   
    void setIdTeam(int id);
    void setFirstName(QString first_name);
    void setLastName(QString last_name);
    void setPosition(QString position);
    void setJerseyNb(int jersey_nb);
    void setDateOfBirth(QDate date_of_birth);
    void setNationality(QString nationality);
    void setGoals(int goals);
    void setAssists(int assists);
    void setInjured(int injured);
    void setYellowCard(int yellow_card);
    void setRedCard(int red_card);
    void setStatus(QString status);
    void setImgJoueur(QByteArray img);

    QString toString() const;

    bool ajouterDansBD();
};

#endif // JOUEUR_H