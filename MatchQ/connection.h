#ifndef CONNECTION_H
#define CONNECTION_H
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

class Connection
{
public:
    Connection();
    bool createconnect();
    void closeconnect();
    static QSqlDatabase getDatabase(); // Add this method

private:
    QSqlDatabase db; // Add database as member variable
};

#endif // CONNECTION_H
