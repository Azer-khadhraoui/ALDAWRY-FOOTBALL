#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "connection.h"
#include <QSqlTableModel>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_Confirm_clicked();
    void on_Delete_clicked();
    void on_Modify_clicked();
    void on_search_textChanged(const QString &text);
    void on_sort_clicked(); // Add this line

private:
    Ui::MainWindow *ui;
    QSqlTableModel *matchModel;
    Connection dbConnection;
    void setupMatchTable();
    void filterMatches(const QString &text);
    void sortMatches(); // Add this line
    bool ascendingOrder; // Add this line
};

#endif // MAINWINDOW_H