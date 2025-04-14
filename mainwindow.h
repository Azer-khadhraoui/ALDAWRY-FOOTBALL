#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QEventLoop>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlDatabase>
#include <QDebug>
#include <QMessageBox>
#include <QTextCharFormat>
#include <QtCore/QVariant>
#include <QtCore/QDate>

#include "ui_mainwindow.h"
#include "competition.h"
#include "connection.h"
#include "addcompetitionwindow.h"
#include "deletewindow.h"
#include "updateform.h"
#include "statistics.h"
#include "matchesdialog.h"

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
    void onYearChanged(const QString &yearText);
    void onMonthClicked(int month);
    void on_pushButton_5_clicked();

private:
    Ui::MainWindow *ui;
    competition c;             // Competition object
    int mainwindow_id;

    // Helper methods
    void updateTableView();
    void updateMonthButtonsForYear(int year);
};

#endif // MAINWINDOW_H
