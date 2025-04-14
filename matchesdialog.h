#ifndef MATCHESDIALOG_H
#define MATCHESDIALOG_H

#include <QDialog>
#include <QVector>
#include <QDate>
#include <QVBoxLayout>
#include <QTableWidget>
#include <QPushButton>
#include <QLocale>
#include <QHeaderView>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QMessageBox>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QEventLoop>
#include <QDate>
#include <QVBoxLayout>
#include <QTableWidget>
#include <QPushButton>
#include <QLocale>
#include <QHeaderView>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QMessageBox>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
struct match {
    QDate date;
    QString teama;
    QString teamb;
    QString score;
    QString predicted_score;
};
class QTableWidget;

class MatchesDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MatchesDialog(int comp_id, int year, int month, QWidget *parent = nullptr);

private:
    void setupUi();
    void populateMatches();
    void predictScores(const QVector<match>&);

    int m_comp_id;
    int m_year;
    int m_month;
    QTableWidget* m_matchTable;
};

#endif // MATCHESDIALOG_H
