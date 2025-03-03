#include <QApplication>
#include "mainwindow.h"
#include "connection.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    Connection c;
    if (!c.createconnect()) {
        return -1;
    }

    MainWindow w;
    w.show();
    return a.exec();
}