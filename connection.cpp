#include "connection.h"

Connection::Connection()
{

}

bool Connection::createconnect()
{bool test=false;
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("ALDAWRY");//inserer le nom de la source de données
    db.setUserName("hotstuff");//inserer nom de l'utilisateur
    db.setPassword("hotstuff");//inserer mot de passe de cet utilisateur
    if (db.open()) {
        test = true;
        qDebug() << "Database connection successful!";
    } else {
        qDebug() << "Database connection failed:" << db.lastError().text();
    }






    return  test;
}
