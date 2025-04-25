#include "connection.h"
#include <QDebug>

Connection::Connection()
{
    db = QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("ALDAWRY");
    db.setUserName("hotstuff");
    db.setPassword("hotstuff");
}

bool Connection::createconnect()
{
    if (db.open()) {
        qDebug() << "Database connected successfully";
        return true;
    }
    qDebug() << "Database Error:" << db.lastError().text();
    return false;
}

void Connection::closeconnect()
{
    if (db.isOpen()) {
        db.close();
    }
}

QSqlDatabase Connection::getDatabase()
{
    return QSqlDatabase::database();
}

