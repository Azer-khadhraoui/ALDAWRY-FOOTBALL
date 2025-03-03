#include "joueur.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

joueur::joueur() {}

joueur::joueur(int id_team, QString first_name, QString last_name,
               QString position, int jersey_nb, QDate date_of_birth, QString nationality,
               QByteArray img_joueur)
    : id_team(id_team), first_name(first_name), last_name(last_name),
      position(position), jersey_nb(jersey_nb), date_of_birth(date_of_birth), nationality(nationality),
      goals(0), assists(0), injured(0), yellow_card(0), red_card(0), status("active"), img_joueur(img_joueur) {}

bool joueur::ajouterDansBD() {
    QSqlQuery query;
    query.prepare("INSERT INTO joueur (id_team, first_name, last_name, position, jersey_nb, date_of_birth, nationality, img_joueur) "
                  "VALUES (:id_team, :first_name, :last_name, :position, :jersey_nb, :date_of_birth, :nationality, :img_joueur)");
    query.bindValue(":id_team", id_team);
    query.bindValue(":first_name", first_name);
    query.bindValue(":last_name", last_name);
    query.bindValue(":position", position);
    query.bindValue(":jersey_nb", jersey_nb);
    query.bindValue(":date_of_birth", date_of_birth);
    query.bindValue(":nationality", nationality);
    query.bindValue(":img_joueur", img_joueur);

    if (!query.exec()) {
        qDebug() << "Erreur: Impossible d'ajouter le joueur dans la base de données." << query.lastError();
        return false;
    }

    return true;
}