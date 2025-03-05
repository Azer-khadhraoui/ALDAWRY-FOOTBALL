#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "connection.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class QSqlRelationalTableModel;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_Confirm_clicked();

private:
    Ui::MainWindow *ui;
    QSqlRelationalTableModel *matchModel;
    Connection dbConnection;
    void setupMatchTable();
};
#endif // MAINWINDOW_H