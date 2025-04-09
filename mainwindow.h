#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ui_mainwindow.h"
#include "competition.h"
#include "connection.h"
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QEventLoop>
#include "addcompetitionwindow.h"
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlDatabase>
#include <QDebug>
#include <QMessageBox>
#include "deletewindow.h"
#include "connection.h"
#include "updateform.h"
#include "statistics.h"
#include <QTextCharFormat>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QEventLoop>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_3_clicked();
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_4_clicked();
    void reconnectSelectionModel();
    void on_searchTextChanged(const QString &search);
    void updateCalendar();
    void prediction(int id);

    void on_pushButton_5_clicked();

private:
    Ui::MainWindow *ui;
    competition c;             // Competition object
    void updateTableView();    // Declared for completeness
    int mainwindow_id;
};

#endif // MAINWINDOW_H
