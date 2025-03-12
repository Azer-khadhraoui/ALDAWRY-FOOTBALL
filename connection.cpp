#include "connection.h"
#include <QSqlError>
#include <QDebug>

Connection::Connection() {
    // Initialize db in constructor, but don't open it yet
    db = QSqlDatabase::addDatabase("QODBC");
}

bool Connection::createconnect() {
    // Set database credentials
    db.setDatabaseName("ALDAWRY");
    db.setUserName("hotstuff");
    db.setPassword("hotstuff");

    // Try to open the connection
    if (!db.open()) {
        qDebug() << "Database connection failed:" << db.lastError().text();
        return false;
    }

    qDebug() << "Database connection successful";
    return true;
}

void Connection::closeconnect() {
    if (db.isOpen()) {
        db.close();
    }
}
