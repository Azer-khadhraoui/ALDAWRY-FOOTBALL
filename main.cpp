#include "mainwindow.h"
#include "qapplication.h"
#include "connection.h"
#include <QSqlError>
#include <QSqlDatabase>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Use the Connection class for ODBC
    Connection conn;
    if (!conn.createconnect()) {
        return -1; // Exit if connection fails
    }

    MainWindow w;
    w.show();
    int result = a.exec();

    conn.closeconnect(); // Close the connection when the application exits
    return result;
}
