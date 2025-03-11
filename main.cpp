#include "mainwindow.h"
#include <QApplication>
#include <QWidget>
#include <QMessageBox>
#include <iostream>
#include "connection.h"
#include "competition.h"
int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    MainWindow w;
    Connection c;
    competition comp;
    //bool test=c.createconnect();*/
    bool test = true;
    if(test)
    {
        w.show();
        QMessageBox::information(nullptr, QObject::tr("database is open"),
                                 QObject::tr("connection successful.\n"
                                             "Click Cancel to exit."), QMessageBox::Cancel);
    }
    else
    {
        QMessageBox::critical(nullptr, QObject::tr("database is not open"),
                              QObject::tr("connection failed.\n"
                                          "Click Cancel to exit."), QMessageBox::Cancel);
    }




    return a.exec();
}
