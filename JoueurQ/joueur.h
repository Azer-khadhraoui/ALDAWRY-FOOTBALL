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
    int status;
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
    int getStatus() const;
    QByteArray getImgJoueur() const;

    // Méthode statique pour supprimer un joueur par son ID
    static bool supprimer(int id);
    
    // Méthode statique pour modifier complètement un joueur
    static bool modifier(int id_player, int id_team, const QString& first_name, const QString& last_name,
                         const QString& position, int jersey_nb, const QDate& date_of_birth, 
                         const QString& nationality, int goals, int assists, int injured,
                         int yellow_card, int red_card, int status, const QByteArray& img_joueur = QByteArray());
   
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
    void setStatus(int status);
    void setImgJoueur(QByteArray img);

    QString toString() const;

    bool ajouterDansBD();
};

#endif // JOUEUR_H