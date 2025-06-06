#include "../userheaders/mainwindow.h"
#include <QApplication>
#include <QMessageBox>
#include "../userheaders/connection.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    Connection c;
    bool test=c.createconnect();
    /*QPalette palette = a.palette();
    palette.setColor(QPalette::WindowText, Qt::white);
    a.setPalette(palette);*/
    if(test)
    {w.show();
        QMessageBox::information(nullptr, QObject::tr("database is open"),
                                 QObject::tr("connection successful.\n"
                                             "Click Cancel to exit."), QMessageBox::Cancel);

    }
    else
        QMessageBox::critical(nullptr, QObject::tr("database is not open"),
                              QObject::tr("connection failed.\n"
                                          "Click Cancel to exit."), QMessageBox::Cancel);




    return a.exec();
}
