#include "joueur.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

joueur::joueur() {}

joueur::joueur(int id_team, QString first_name, QString last_name,
               QString position, int jersey_nb, QDate date_of_birth, QString nationality,
               QByteArray img_joueur)
    : id_team(id_team), first_name(first_name), last_name(first_name),
      position(position), jersey_nb(jersey_nb), date_of_birth(date_of_birth), nationality(nationality),
      goals(0), assists(0), injured(0), yellow_card(0), red_card(0), status(0), img_joueur(img_joueur) {}

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

bool joueur::supprimer(int id)
{
    QSqlQuery query;
    query.prepare("DELETE FROM joueur WHERE id_player = :id");
    query.bindValue(":id", id);
    
    bool success = query.exec();
    
    if (!success) {
        qDebug() << "Erreur lors de la suppression du joueur:" << query.lastError().text();
        return false;
    }
    
    int rowsAffected = query.numRowsAffected();
    if (rowsAffected == 0) {
        qDebug() << "Aucun joueur trouvé avec l'ID:" << id;
        return false;
    }
    
    return true;
}

bool joueur::modifier(int id_player, int id_team, const QString& first_name, const QString& last_name,
                     const QString& position, int jersey_nb, const QDate& date_of_birth, 
                     const QString& nationality, int goals, int assists, int injured,
                     int yellow_card, int red_card, int status, const QByteArray& img_joueur)
{
    QSqlQuery query;
    QString queryStr;
    
    
    if (img_joueur.isEmpty()) {
        queryStr = "UPDATE joueur SET id_team = :id_team, first_name = :first_name, "
                   "last_name = :last_name, position = :position, jersey_nb = :jersey_nb, "
                   "date_of_birth = :date_of_birth, nationality = :nationality, "
                   "goals = :goals, assists = :assists, injured = :injured, "
                   "yellow_card = :yellow_card, red_card = :red_card, status = :status "
                   "WHERE id_player = :id_player";
    } else {
        queryStr = "UPDATE joueur SET id_team = :id_team, first_name = :first_name, "
                   "last_name = :last_name, position = :position, jersey_nb = :jersey_nb, "
                   "date_of_birth = :date_of_birth, nationality = :nationality, "
                   "goals = :goals, assists = :assists, injured = :injured, "
                   "yellow_card = :yellow_card, red_card = :red_card, status = :status, "
                   "img_joueur = :img_joueur WHERE id_player = :id_player";
    }
    
    query.prepare(queryStr);
    
    // Bind toutes les valeurs
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
    query.bindValue(":id_player", id_player);
    
   
    if (!img_joueur.isEmpty()) {
        query.bindValue(":img_joueur", img_joueur);
    }
    
   
    bool success = query.exec();
    
    if (!success) {
        qDebug() << "Erreur lors de la modification du joueur:" << query.lastError().text();
        return false;
    }
    
    return true;
}

void joueur::setStatus(int status)
{
    this->status = status;
}

int joueur::getStatus() const
{
    return status;
}