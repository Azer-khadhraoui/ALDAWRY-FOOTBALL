#include "../playerheaders/addplayer.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

joueur::joueur() {}

joueur::joueur(int id_team, QString first_name, QString last_name,
               QString position, int jersey_nb, QDate date_of_birth, QString nationality,
               QByteArray img_joueur)
    : id_team(id_team), first_name(first_name), last_name(last_name),
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

QList<QPair<QString, int>> joueur::getTopScorers(int limit)
{
    QList<QPair<QString, int>> result;
    QSqlQuery query;
    
    // Nous utilisons une requête plus simple et nous affichons tous les joueurs, même avec 0 buts
    query.prepare("SELECT first_name, last_name, goals FROM joueur ORDER BY goals DESC LIMIT :limit");
    query.bindValue(":limit", limit);
    
    qDebug() << "Executing top scorers query...";
    if (!query.exec()) {
        qDebug() << "Error retrieving top scorers:" << query.lastError().text();
        return result;
    }
    
    while (query.next()) {
        QString playerName = query.value(0).toString() + " " + query.value(1).toString();
        int goals = query.value(2).toInt();
        qDebug() << "Top scorer:" << playerName << "with" << goals << "goals";
        result.append(qMakePair(playerName, goals));
    }
    
    qDebug() << "Found" << result.size() << "top scorers";
    return result;
}

QList<QPair<QString, int>> joueur::getTopAssists(int limit)
{
    QList<QPair<QString, int>> result;
    QSqlQuery query;
    
    // Nous utilisons une requête plus simple et nous affichons tous les joueurs, même avec 0 passes
    query.prepare("SELECT first_name, last_name, assists FROM joueur ORDER BY assists DESC LIMIT :limit");
    query.bindValue(":limit", limit);
    
    qDebug() << "Executing top assists query...";
    if (!query.exec()) {
        qDebug() << "Error retrieving top assists:" << query.lastError().text();
        return result;
    }
    
    while (query.next()) {
        QString playerName = query.value(0).toString() + " " + query.value(1).toString();
        int assists = query.value(2).toInt();
        qDebug() << "Top assist maker:" << playerName << "with" << assists << "assists";
        result.append(qMakePair(playerName, assists));
    }
    
    qDebug() << "Found" << result.size() << "top assist makers";
    return result;
}

QMap<QString, int> joueur::getPositionStats()
{
    QMap<QString, int> result;
    QSqlQuery query;
    
    qDebug() << "Executing position stats query...";
    if (!query.exec("SELECT position, COUNT(*) FROM joueur GROUP BY position")) {
        qDebug() << "Error retrieving position stats:" << query.lastError().text();
        return result;
    }
    
    while (query.next()) {
        QString position = query.value(0).toString();
        int count = query.value(1).toInt();
        qDebug() << "Position:" << position << "with" << count << "players";
        result.insert(position, count);
    }
    
    return result;
}

QMap<QString, int> joueur::getCardStats()
{
    QMap<QString, int> result;
    QSqlQuery query;
    
    qDebug() << "Calculating card statistics...";
    
    // Récupérer le total des cartes jaunes
    if (query.exec("SELECT SUM(yellow_card) FROM joueur") && query.next()) {
        int yellowCards = query.value(0).isNull() ? 0 : query.value(0).toInt();
        result.insert("Jaunes", yellowCards);
        qDebug() << "Total yellow cards:" << yellowCards;
    }
    
    // Récupérer le total des cartes rouges
    if (query.exec("SELECT SUM(red_card) FROM joueur") && query.next()) {
        int redCards = query.value(0).isNull() ? 0 : query.value(0).toInt();
        result.insert("Rouges", redCards);
        qDebug() << "Total red cards:" << redCards;
    }
    
    return result;
}

int joueur::getTotalPlayers()
{
    QSqlQuery query("SELECT COUNT(*) FROM joueur");
    if (query.next()) {
        int count = query.value(0).toInt();
        qDebug() << "Total players found:" << count;
        return count;
    }
    qDebug() << "Error retrieving total players count";
    return 0;
}
