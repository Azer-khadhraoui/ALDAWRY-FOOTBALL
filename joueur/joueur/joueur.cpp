#include "joueur.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

joueur::joueur() {}

joueur::joueur(int id_player, int id_team, QString first_name, QString last_name,
               QString position, int jersey_nb, QDate date_of_birth, QString nationality,
               int goals, int assists, int injured, int yellow_card, int red_card,
               QString status, QByteArray img_joueur)
    : id_player(id_player), id_team(id_team), first_name(first_name), last_name(last_name),
      position(position), jersey_nb(jersey_nb), date_of_birth(date_of_birth), nationality(nationality),
      goals(goals), assists(assists), injured(injured), yellow_card(yellow_card),
      red_card(red_card), status(status), img_joueur(img_joueur) {}

bool joueur::ajouterDansBD() {
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("ALDAWRY");
    db.setUserName("hotstuff");
    db.setPassword("hotstuff");

    if (!db.open()) {
        qDebug() << "Erreur: Impossible de se connecter à la base de données." << db.lastError();
        return false;
    }

    QSqlQuery query;
    query.prepare("INSERT INTO joueurs (id_player, id_team, first_name, last_name, position, jersey_nb, date_of_birth, nationality, goals, assists, injured, yellow_card, red_card, status, img_joueur) "
                  "VALUES (:id_player, :id_team, :first_name, :last_name, :position, :jersey_nb, :date_of_birth, :nationality, :goals, :assists, :injured, :yellow_card, :red_card, :status, :img_joueur)");
    query.bindValue(":id_player", id_player);
    query.bindValue(":id_team", id_team);
    query.bindValue(":first_name", first_name);
    query.bindValue(":last_name", last_name);
    query.bindValue(":position", position);
    query.bindValue(":jersey_nb", jersey_nb);
    query.bindValue(":date_of_birth", date_of_birth);
    query.bindValue(":nationality", nationality);
    query.bindValue(":goals", goals);
    query.bindValue(":assists", assists);
    query.bindValue(":injured", injured);
    query.bindValue(":yellow_card", yellow_card);
    query.bindValue(":red_card", red_card);
    query.bindValue(":status", status);
    query.bindValue(":img_joueur", img_joueur);

    if (!query.exec()) {
        qDebug() << "Erreur: Impossible d'ajouter le joueur dans la base de données." << query.lastError();
        return false;
    }

    db.close();
    return true;
}
