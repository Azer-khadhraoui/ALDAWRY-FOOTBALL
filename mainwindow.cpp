#include "mainwindow.h"
#include "./ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow),
    mainwindow_id(-1)
{
    ui->setupUi(this);
    Connection conn;
    bool test = conn.createconnect();
    ui->test->setModel(c.show_competitions());

    connect(ui->lineEdit, &QLineEdit::textChanged, this, &MainWindow::on_searchTextChanged);
    connect(ui->comboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), [=](int index) {
        if (index == 0) {
            ui->test->setModel(c.show_competitions());
        } else if (index == 1) {
            ui->test->setModel(c.show_competitions_by_date());
        } else if (index == 2) {
            ui->test->setModel(c.show_competitions_by_nb_teams());
        }
        reconnectSelectionModel();
    });
    connect(ui->comboBox_2, QOverload<int>::of(&QComboBox::currentIndexChanged), [=](int index) {
        if (index == 0) {
            ui->test->setModel(c.show_competitions());
        } else if (index == 1) {
            ui->test->setModel(c.show_competitions_by_type("League"));
        } else if (index == 2) {
            ui->test->setModel(c.show_competitions_by_type("Tournament"));
        }
        reconnectSelectionModel();
    });
    reconnectSelectionModel();
    prediction(mainwindow_id); // Initialize prediction with no selection
}

void MainWindow::reconnectSelectionModel()
{
    disconnect(ui->test->selectionModel(), &QItemSelectionModel::currentRowChanged, this, nullptr); // Prevent multiple connections
    connect(ui->test->selectionModel(), &QItemSelectionModel::currentRowChanged, this, [=](const QModelIndex &current, const QModelIndex &previous) {
        if (current.isValid()) {
            mainwindow_id = current.sibling(current.row(), 0).data().toInt();
            qDebug() << "Selected competition ID:" << mainwindow_id;
            prediction(mainwindow_id);
            updateCalendar();
        }
    });
}

void MainWindow::updateCalendar()
{
    QTextCharFormat defaultFormat;
    defaultFormat.setForeground(ui->calendarWidget->palette().text().color()); // Use default text color
    ui->calendarWidget->setWeekdayTextFormat(Qt::Monday, defaultFormat);
    ui->calendarWidget->setWeekdayTextFormat(Qt::Tuesday, defaultFormat);
    ui->calendarWidget->setWeekdayTextFormat(Qt::Wednesday, defaultFormat);
    ui->calendarWidget->setWeekdayTextFormat(Qt::Thursday, defaultFormat);
    ui->calendarWidget->setWeekdayTextFormat(Qt::Friday, defaultFormat);
    ui->calendarWidget->setWeekdayTextFormat(Qt::Saturday, defaultFormat);
    ui->calendarWidget->setWeekdayTextFormat(Qt::Sunday, defaultFormat);

    QDate date = QDate::currentDate().addYears(-10);
    QDate endDate1 = QDate::currentDate().addYears(10);
    while (date <= endDate1) {
        ui->calendarWidget->setDateTextFormat(date, defaultFormat);
        date = date.addDays(1);
    }

    if (mainwindow_id == -1) {
        return;
    }

    competition selectedComp = c.get_competition(mainwindow_id);
    QDate startDate = selectedComp.get_date_debut();
    QDate endDate = selectedComp.get_date_fin();
    ui->calendarWidget->setSelectedDate(startDate);

    if (startDate.isValid() && endDate.isValid() && startDate <= endDate) {
        QTextCharFormat highlightFormat;
        highlightFormat.setBackground(QBrush(QColor(0, 100, 0)));
        highlightFormat.setForeground(Qt::white);

        QDate currentDate = startDate;
        while (currentDate <= endDate) {
            ui->calendarWidget->setDateTextFormat(currentDate, highlightFormat);
            currentDate = currentDate.addDays(1);
        }
    } else {
        qDebug() << "Invalid or no date range for competition ID:" << mainwindow_id;
    }
}

void MainWindow::on_searchTextChanged(const QString &search)
{
    if (search.isEmpty()) {
        qDebug() << "Search field is empty.";
        ui->test->setModel(c.show_competitions());
    } else {
        qDebug() << "Search field is not empty.";
        ui->test->setModel(c.show_competitions_by_name(search));
    }
    reconnectSelectionModel();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_3_clicked()
{
    AddCompetitionWindow a;
    if (a.exec() == QDialog::Accepted) {
    }
    ui->test->setModel(c.show_competitions());
    reconnectSelectionModel();
    updateCalendar();
}

void MainWindow::on_pushButton_clicked()
{
    if (mainwindow_id == -1) {
        QMessageBox::warning(this, "Selection Error", "Please select a competition to delete.");
        return;
    }
    deletewindow d(this, mainwindow_id);
    if (d.exec() == QDialog::Accepted) {
    }
    ui->test->setModel(c.show_competitions());
    reconnectSelectionModel();
    updateCalendar();
}

void MainWindow::on_pushButton_2_clicked()
{
    if (mainwindow_id == -1) {
        QMessageBox::warning(this, "Selection Error", "Please select a competition to update.");
        return;
    }
    updateform u(this, mainwindow_id);
    if (u.exec() == QDialog::Accepted) {
    }
    ui->test->setModel(c.show_competitions());
    reconnectSelectionModel();
    updateCalendar();
}

void MainWindow::on_pushButton_4_clicked()
{
    statistics s;
    if (s.exec() == QDialog::Accepted) {
    }
    ui->test->setModel(c.show_competitions());
    reconnectSelectionModel();
    updateCalendar();
}

void MainWindow::updateTableView()
{
    ui->test->setModel(c.show_competitions());
    reconnectSelectionModel();
    updateCalendar();
}

void MainWindow::prediction(int id)
{
    if (id == -1) {
        qDebug() << "No competition selected for prediction.";
        return;
    }
    QSqlQuery query;
    query.prepare("SELECT comp_name FROM competition WHERE id_competition = :id");
    query.bindValue(":id", id);
    if (query.exec() && query.next()) {
        QString competitionName = query.value(0).toString();
        ui->comp_name->setText("The potential winner for "+ competitionName + " is:");
    } else {
        qDebug() << "Failed to fetch competition name:" << query.lastError().text();
        ui->comp_name->setText("Unknown Competition");
    }

    query.prepare("SELECT ID_TEAM FROM participation WHERE id_comp = :id");
    query.bindValue(":id", id);

    if (!query.exec()) {
        qDebug() << "Failed to fetch participating teams:" << query.lastError().text();
        return;
    }

    QMap<int, double> teamStats;

    while (query.next()) {
        int teamId = query.value(0).toInt();

        QSqlQuery statsQuery;
        statsQuery.prepare("SELECT wins, draws, losses, goals_team FROM equipe WHERE id_team = :teamId");
        statsQuery.bindValue(":teamId", teamId);

        if (!statsQuery.exec() || !statsQuery.next()) {
            qDebug() << "Failed to fetch stats for team ID:" << teamId << statsQuery.lastError().text();
            continue;
        }

        int wins = statsQuery.value(0).toInt();
        int draws = statsQuery.value(1).toInt();
        int losses = statsQuery.value(2).toInt();
        int goalsTeam = statsQuery.value(3).toInt();

        QString inputData = QString("Wins: %1, Draws: %2, Losses: %3, Goals: %4")
                                .arg(wins).arg(draws).arg(losses).arg(goalsTeam);

        QString apiKey = "AIzaSyDm1OCBufbaP1k-ClMoPTCubMABaVtl3zg"; // Consider using an environment variable
        if (apiKey.isEmpty()) {
            qDebug() << "Gemini API key is missing.";
            continue;
        }

        QNetworkAccessManager manager;
        QNetworkRequest request(QUrl("https://generativelanguage.googleapis.com/v1beta/models/gemini-2.0-flash:generateContent?key=" + apiKey));
        request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

        QJsonObject json;
        QJsonArray parts;
        QJsonObject part;
        // Refined prompt to enforce numeric output
        part["text"] = "Based on these stats: " + inputData + ", provide only a performance score as a number between 0 and 100, no explanation.";
        parts.append(part);
        json["contents"] = QJsonArray{QJsonObject{{"parts", parts}}};
        json["generationConfig"] = QJsonObject{{"maxOutputTokens", 50}}; // Increased to allow full response

        QNetworkReply *reply = manager.post(request, QJsonDocument(json).toJson());
        QEventLoop loop;
        connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
        loop.exec();

        if (reply->error() == QNetworkReply::NoError) {
            QByteArray responseData = reply->readAll();
            //qDebug() << "Gemini API Response:" << responseData;
            QJsonDocument responseDoc = QJsonDocument::fromJson(responseData);
            QJsonObject responseObj = responseDoc.object();
            if (responseObj.contains("candidates") && responseObj["candidates"].isArray()) {
                QJsonArray candidates = responseObj["candidates"].toArray();
                if (!candidates.isEmpty() && candidates[0].isObject()) {
                    QString predictedScoreText = candidates[0].toObject()["content"].toObject()["parts"].toArray()[0].toObject()["text"].toString().trimmed();
                    bool ok;
                    double predictedScore = predictedScoreText.toDouble(&ok);
                    if (ok && predictedScore >= 0 && predictedScore <= 100) {
                        teamStats[teamId] = predictedScore;
                    } else {
                        //qDebug() << "Invalid score received:" << predictedScoreText << " - Expected a number between 0 and 100.";
                    }
                } else {
                    //qDebug() << "No valid candidates in response.";
                }
            } else {
                //qDebug() << "Invalid API response format.";
            }
        } else {
            //qDebug() << "API request failed:" << reply->errorString() << reply->readAll();
        }
        reply->deleteLater();
    }

    if (teamStats.isEmpty()) {
        ui->team_name->setText("no teams in this competition");
        QMessageBox::warning(this, "Prediction Error", "No valid predictions could be made for the teams.");
        return;
    }

    int winningTeamId = -1;
    double maxScore = -1;
    for (auto it = teamStats.begin(); it != teamStats.end(); ++it) {
        if (it.value() > maxScore) {
            maxScore = it.value();
            winningTeamId = it.key();
        }
    }

    if (winningTeamId != -1) {
        QSqlQuery teamQuery;
        teamQuery.prepare("SELECT team_name FROM equipe WHERE id_team = :teamId");
        teamQuery.bindValue(":teamId", winningTeamId);

        if (teamQuery.exec() && teamQuery.next()) {
            QString winningTeamName = teamQuery.value(0).toString();
            qDebug() << "Predicted winning team:" << winningTeamName;
            ui->team_name->setText(winningTeamName);
        } else {
            qDebug() << "Failed to fetch winning team name:" << teamQuery.lastError().text();
        }
    } else {
        QMessageBox::information(this, "Prediction", "Unable to predict a winning team.");

    }
    qDebug() << "Prediction completed for competition ID:" << id;
    
}

void MainWindow::on_pushButton_5_clicked()
{
    if (mainwindow_id == -1) {
        QMessageBox::warning(this, "Selection Error", "Please select a competition.");
        return;
    }
    QSqlQuery checkQuery;
    checkQuery.prepare("SELECT COUNT(*) FROM match WHERE id_competition = :id");
    checkQuery.bindValue(":id", mainwindow_id);

    if (!checkQuery.exec() || !checkQuery.next()) {
        QMessageBox::warning(this, "Database Error", "Failed to check if fixtures are already generated.");
        return;
    }

    int matchCount = checkQuery.value(0).toInt();
    if (matchCount > 0) {
        QMessageBox::information(this, "Fixtures Already Generated", "Fixtures for this competition have already been generated.");
        return;
    }

    QSqlQuery query;
    query.prepare("SELECT id_team FROM participation WHERE id_comp = :id");
    query.bindValue(":id", mainwindow_id);

    if (!query.exec()) {
        QMessageBox::warning(this, "Database Error", "Failed to fetch participating teams.");
        return;
    }

    QVector<int> teamIds;
    while (query.next()) {
        teamIds.append(query.value(0).toInt());
    }

    if (teamIds.isEmpty()) {
        QMessageBox::warning(this, "No Teams", "No teams are participating in this competition.");
        return;
    }

    competition selectedComp = c.get_competition(mainwindow_id);
    QString competitionType = selectedComp.get_type(); // Assuming this method exists to get the competition type

    QSqlQuery insertQuery;
    int matchId = 1; // Start match ID from 1 or fetch the last ID from the database if needed

    if (competitionType == "League") {
        // Generate fixtures for a league (round-robin format with home and away matches)
        for (int i = 0; i < teamIds.size(); ++i) {
            for (int j = i + 1; j < teamIds.size(); ++j) {
                // Home match
                insertQuery.prepare("INSERT INTO match (id_match, id_competition, id_teama, id_teamb) VALUES (:id_match, :id_competition, :id_teama, :id_teamb)");
                insertQuery.bindValue(":id_match", matchId++);
                insertQuery.bindValue(":id_competition", mainwindow_id);
                insertQuery.bindValue(":id_teama", teamIds[i]);
                insertQuery.bindValue(":id_teamb", teamIds[j]);

                if (!insertQuery.exec()) {
                    QMessageBox::warning(this, "Database Error", "Failed to insert match: " + insertQuery.lastError().text());
                    return;
                }

                // Away match
                insertQuery.prepare("INSERT INTO match (id_match, id_competition, id_teama, id_teamb) VALUES (:id_match, :id_competition, :id_teama, :id_teamb)");
                insertQuery.bindValue(":id_match", matchId++);
                insertQuery.bindValue(":id_competition", mainwindow_id);
                insertQuery.bindValue(":id_teama", teamIds[j]);
                insertQuery.bindValue(":id_teamb", teamIds[i]);

                if (!insertQuery.exec()) {
                    QMessageBox::warning(this, "Database Error", "Failed to insert match: " + insertQuery.lastError().text());
                    return;
                }
            }
        }
    } else if (competitionType == "Tournament") {
        // Generate fixtures for a tournament (knockout format)
        std::random_shuffle(teamIds.begin(), teamIds.end()); // Shuffle teams for random pairing

        for (int i = 0; i < teamIds.size(); i += 2) {
            if (i + 1 < teamIds.size()) {
                insertQuery.prepare("INSERT INTO match (id_match, id_competition, id_teama, id_teamb) VALUES (:id_match, :id_competition, :id_teama, :id_teamb)");
                insertQuery.bindValue(":id_match", matchId++);
                insertQuery.bindValue(":id_competition", mainwindow_id);
                insertQuery.bindValue(":id_teama", teamIds[i]);
                insertQuery.bindValue(":id_teamb", teamIds[i + 1]);

                if (!insertQuery.exec()) {
                    QMessageBox::warning(this, "Database Error", "Failed to insert match: " + insertQuery.lastError().text());
                    return;
                }
            }
        }
    } else {
        QMessageBox::warning(this, "Unknown Type", "The competition type is unknown.");
        return;
    }

    QMessageBox::information(this, "Fixtures Generated", "Fixtures have been successfully generated and saved.");
}

