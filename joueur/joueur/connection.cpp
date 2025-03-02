#include "connection.h"
#include <QSqlError>
#include <QDebug>

Connection::Connection() {}

bool Connection::createconnect() {
    bool test = false;
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("ALDAWRY"); // insérer le nom de la source de données
    db.setUserName("hotstuff"); // insérer nom de l'utilisateur
    db.setPassword("hotstuff"); // insérer mot de passe de cet utilisateur

    if (db.open()) {
        test = true;
    } else {
        qDebug() << "Erreur: Impossible de se connecter à la base de données." << db.lastError();
    }

    return test;
}
