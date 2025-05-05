#ifndef CONNECTION_H
#define CONNECTION_H
#include <QSqlDatabase>
#include <QSqlError>

class Connection {
public:
    Connection();
    bool createconnect();
    QSqlError lastError() const { return db.lastError(); } // Add this

private:
    QSqlDatabase db;
};

#endif // CONNECTION_H
