#include "../userheaders/mainwindow.h"
#include <QApplication>
#include <QMessageBox>
#include "../userheaders/connection.h"
#include "../videointrowidget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Create database connection
    Connection c;
    bool test = c.createconnect();

    // Show video intro first
    VideoIntroWidget videoIntro;
    videoIntro.show();

    /*// If database connection is successful, prepare MainWindow but don't show it yet
    if (test) {
        // MainWindow will be shown by VideoIntroWidget when video finishes
        QMessageBox::information(nullptr, QObject::tr("database is open"),
                                 QObject::tr("connection successful.\n"
                                             "Click Cancel to exit."), QMessageBox::Cancel);
    } else {
        QMessageBox::critical(nullptr, QObject::tr("database is not open"),
                              QObject::tr("connection failed.\n"
                                          "Click Cancel to exit."), QMessageBox::Cancel);
        return 1; // Exit if database connection fails
    }*/

    return a.exec();
}
