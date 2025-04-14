#include "matchesdialog.h"
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

MatchesDialog::MatchesDialog(int comp_id, int year, int month, QWidget *parent)
    : QDialog(parent)
    , m_comp_id(comp_id)
    , m_year(year)
    , m_month(month)
    , m_matchTable(nullptr)
{
    setupUi();
    populateMatches();
}

void MatchesDialog::setupUi()
{
    QLocale locale(QLocale::English); // Use English for month names
    setWindowTitle(QString("Matches for %1 %2").arg(locale.monthName(m_month)).arg(m_year));
    setFixedSize(700, 500);
    setStyleSheet("background-color: #0d1f2d; color: #e0f7fa;");

    QVBoxLayout* layout = new QVBoxLayout(this);

    m_matchTable = new QTableWidget(this);
    m_matchTable->setStyleSheet("background-color: #1e4d4a; border: 1px solid #4dd0e1; color: #e0f7fa;");
    m_matchTable->setColumnCount(5);
    m_matchTable->setHorizontalHeaderLabels({"Date", "Team 1", "Team 2", "Score", "Predicted Score"});
    m_matchTable->horizontalHeader()->setStyleSheet("background-color: #006400; color: #ffffff;");
    m_matchTable->setSelectionMode(QAbstractItemView::NoSelection);
    m_matchTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    layout->addWidget(m_matchTable);

    QPushButton* closeButton = new QPushButton("Close", this);
    closeButton->setStyleSheet("background-color: #0288d1; color: #ffffff; border: 1px solid #4dd0e1; border-radius: 4px;");
    connect(closeButton, &QPushButton::clicked, this, &QDialog::accept);
    layout->addWidget(closeButton);
}

void MatchesDialog::populateMatches()
{
    QSqlQuery query;
    // Clear the table before populating it with new data
    m_matchTable->clearContents();
    m_matchTable->setRowCount(0); // Ensure the row count is reset

    query.prepare("SELECT m.date_m, "
                  "(SELECT team_name FROM equipe WHERE id_team = m.id_teama) AS teama, "
                  "(SELECT team_name FROM equipe WHERE id_team = m.id_teamb) AS teamb, "
                  "m.scorea, m.scoreb "
                  "FROM match m "
                  "WHERE m.id_competition = :comp_id AND EXTRACT(YEAR FROM m.date_m) = :year AND EXTRACT(MONTH FROM m.date_m) = :month");
    query.bindValue(":comp_id", m_comp_id);
    query.bindValue(":year", m_year);
    query.bindValue(":month", m_month);

    QVector<match> matches;

    if (query.exec()) {
        while (query.next()) {
            match m;
            m.date = query.value(0).toDate();
            m.teama = query.value(1).toString();
            m.teamb = query.value(2).toString();
            m.score = QString("%1 - %2").arg(query.value(3).toInt()).arg(query.value(4).toInt());
            matches.append(m);
        }
    } else {
        qWarning() << "Failed to execute query:" << query.lastError().text();
        QMessageBox::critical(this, "Database Error", "Failed to retrieve matches: " + query.lastError().text());
        return;
    }

    m_matchTable->setRowCount(matches.size());

    for (int i = 0; i < matches.size(); ++i) {
        const match& m = matches[i];
        m_matchTable->setItem(i, 0, new QTableWidgetItem(m.date.toString("yyyy-MM-dd")));
        m_matchTable->setItem(i, 1, new QTableWidgetItem(m.teama));
        m_matchTable->setItem(i, 2, new QTableWidgetItem(m.teamb));
        m_matchTable->setItem(i, 3, new QTableWidgetItem(m.score));
        m_matchTable->setItem(i, 4, new QTableWidgetItem("Predicting..."));
    }

    m_matchTable->resizeColumnsToContents();

    // Predict scores for each match
    predictScores(matches);
}

void MatchesDialog::predictScores(const QVector<match>& matches)
{
    QString apiKey = "AIzaSyDm1OCBufbaP1k-ClMoPTCubMABaVtl3zg"; 
    if (apiKey.isEmpty()) {
        QMessageBox::warning(this, "API Key Missing", "Gemini API key is missing. Cannot predict scores.");
        return;
    }

    QNetworkAccessManager* manager = new QNetworkAccessManager(this);

    for (int i = 0; i < matches.size(); ++i) {
        const match& m = matches[i];

        QNetworkRequest request(QUrl("https://generativelanguage.googleapis.com/v1beta/models/gemini-1.5-flash:generateContent?key=" + apiKey));
        request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

        QJsonObject json;
        QJsonArray contents;
        QJsonObject content;
        QJsonArray parts;
        QJsonObject part;
        QSqlQuery statsQuery;
        statsQuery.prepare("SELECT wins, draws, losses FROM equipe WHERE team_name = :team_name");
        statsQuery.bindValue(":team_name", m.teama);
        int teamAWins = 0, teamADraws = 0, teamALosses = 0;
        if (statsQuery.exec() && statsQuery.next()) {
            teamAWins = statsQuery.value(0).toInt();
            teamADraws = statsQuery.value(1).toInt();
            teamALosses = statsQuery.value(2).toInt();
        }

        statsQuery.bindValue(":team_name", m.teamb);
        int teamBWins = 0, teamBDraws = 0, teamBLosses = 0;
        if (statsQuery.exec() && statsQuery.next()) {
            teamBWins = statsQuery.value(0).toInt();
            teamBDraws = statsQuery.value(1).toInt();
            teamBLosses = statsQuery.value(2).toInt();
        }

        part["text"] = QString("Predict the score for the match between %1 and %2. "
                       "Team %1 has %3 wins, %4 draws, and %5 losses. "
                       "Team %2 has %6 wins, %7 draws, and %8 losses. "
                       "Provide the result as 'X - Y'."
                       "just give me the score, nothing else."
                    "this is an imaginary match, so don't use real data.")
                   .arg(m.teama)
                   .arg(m.teamb)
                   .arg(teamAWins)
                   .arg(teamADraws)
                   .arg(teamALosses)
                   .arg(teamBWins)
                   .arg(teamBDraws)
                   .arg(teamBLosses);
       
        parts.append(part);
        content["parts"] = parts;
        contents.append(content);
        json["contents"] = contents;

        QNetworkReply* reply = manager->post(request, QJsonDocument(json).toJson());
        connect(reply, &QNetworkReply::finished, this, [=]() {
            if (reply->error() == QNetworkReply::NoError) {
                QByteArray responseData = reply->readAll();
                qDebug() << "API Response:" << responseData;
                QJsonDocument responseDoc = QJsonDocument::fromJson(responseData);
                QJsonObject responseObj = responseDoc.object();

                if (responseObj.contains("candidates") && responseObj["candidates"].isArray()) {
                    QJsonArray candidates = responseObj["candidates"].toArray();
                    if (!candidates.isEmpty() && candidates[0].isObject()) {
                        QJsonObject candidate = candidates[0].toObject();
                        if (candidate.contains("content") && candidate["content"].isObject()) {
                            QJsonObject content = candidate["content"].toObject();
                            if (content.contains("parts") && content["parts"].isArray()) {
                                QJsonArray parts = content["parts"].toArray();
                                if (!parts.isEmpty() && parts[0].isObject()) {
                                    QString predictedScore = parts[0].toObject()["text"].toString().trimmed();
                                    m_matchTable->setItem(i, 4, new QTableWidgetItem(predictedScore));
                                } else {
                                    m_matchTable->setItem(i, 4, new QTableWidgetItem("No prediction"));
                                }
                            } else {
                                m_matchTable->setItem(i, 4, new QTableWidgetItem("No parts"));
                            }
                        } else {
                            m_matchTable->setItem(i, 4, new QTableWidgetItem("No content"));
                        }
                    } else {
                        m_matchTable->setItem(i, 4, new QTableWidgetItem("No candidates"));
                    }
                } else {
                    m_matchTable->setItem(i, 4, new QTableWidgetItem("Invalid response"));
                    qWarning() << "Invalid response format:" << responseData;
                }
            } else {
                QByteArray errorResponse = reply->readAll();
                qWarning() << "Failed to predict score:" << reply->errorString() << "Response:" << errorResponse;
                m_matchTable->setItem(i, 4, new QTableWidgetItem("Error"));
            }
            reply->deleteLater();
        });
    }
}