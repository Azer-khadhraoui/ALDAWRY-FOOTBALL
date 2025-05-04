#ifndef TABLEAU1_H
#define TABLEAU1_H

#include <QDialog>
#include "ui_tableau1.h"
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

#include "competition.h"
#include "connection.h"
#include "addcompetitionwindow.h"
#include "deletewindow.h"
#include "updateform.h"
#include "statistics.h"
#include "matchesdialog.h"
#include "calendardialog.h"

namespace Ui {
class TableauDialog;
}

class TableauDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TableauDialog(QWidget *parent = nullptr);
    ~TableauDialog();

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_5_clicked();
    void on_searchTextChanged(const QString &search);
    void updateCalendar();
    void prediction(int id);
    void onYearChanged(const QString &yearText);
    void onMonthClicked(int month);
    void reconnectSelectionModel();

private:
    Ui::TableauDialog *ui;
    competition c;
    int mainwindow_id = -1;
    void updateTableView();
    void updateMonthButtonsForYear(int year);
};

#endif // TABLEAU1_H
