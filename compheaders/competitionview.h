#ifndef COMPETITIONVIEW_H
#define COMPETITIONVIEW_H

#include <QWidget>
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
#include <QStackedWidget>

#include "ui_competitionview.h"
#include "competition.h"
//#include "../userheaders/connection.h"
#include "addcompetitionwindow.h"
#include "deletewindow.h"
#include "updateform.h"
#include "statistics.h"
#include "matchesdialog.h"
#include "tableau1.h"

namespace Ui {
class competitionview;
}

class competitionview : public QWidget
{
    Q_OBJECT

public:
    explicit competitionview(QStackedWidget *stackedWidget = nullptr, QWidget *parent = nullptr);
    ~competitionview();

private slots:
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_6_clicked();
    void on_userbutton_clicked();
    void on_logoutButton_clicked();
    void on_aboutButton_clicked();

private:
    Ui::competitionview *ui;
    competition c;             // Competition object
    int mainwindow_id;

    // Helper methods
    void updateTableView();
    void updateMonthButtonsForYear(int year);
};

#endif // COMPETITIONVIEW_H
