#include "tableau1.h"
#include "ui_tableau1.h"

TableauDialog::TableauDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::TableauDialog)
{
    ui->setupUi(this);
    ui->test->setModel(c.show_competitions());
    ui->yearComboBox->clear();
    for (int year = 2000; year <= 2500; ++year) {
        ui->yearComboBox->addItem(QString::number(year));
    }
    ui->yearComboBox->setCurrentText(QString::number(QDate::currentDate().year()));
    connect(ui->yearComboBox, &QComboBox::currentTextChanged, this, &TableauDialog::onYearChanged);
    connect(ui->januaryButton, &QPushButton::clicked, this, [this]() { onMonthClicked(1); });
    connect(ui->februaryButton, &QPushButton::clicked, this, [this]() { onMonthClicked(2); });
    connect(ui->marchButton, &QPushButton::clicked, this, [this]() { onMonthClicked(3); });
    connect(ui->aprilButton, &QPushButton::clicked, this, [this]() { onMonthClicked(4); });
    connect(ui->mayButton, &QPushButton::clicked, this, [this]() { onMonthClicked(5); });
    connect(ui->juneButton, &QPushButton::clicked, this, [this]() { onMonthClicked(6); });
    connect(ui->julyButton, &QPushButton::clicked, this, [this]() { onMonthClicked(7); });
    connect(ui->augustButton, &QPushButton::clicked, this, [this]() { onMonthClicked(8); });
    connect(ui->septemberButton, &QPushButton::clicked, this, [this]() { onMonthClicked(9); });
    connect(ui->octoberButton, &QPushButton::clicked, this, [this]() { onMonthClicked(10); });
    connect(ui->novemberButton, &QPushButton::clicked, this, [this]() { onMonthClicked(11); });
    connect(ui->decemberButton, &QPushButton::clicked, this, [this]() { onMonthClicked(12); });
    connect(ui->lineEdit, &QLineEdit::textChanged, this, &TableauDialog::on_searchTextChanged);
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
    if (mainwindow_id == -1) {
        ui->comp_name->setText("No competition selected.");
        ui->team_name->setText("No team selected.");
    } else {
        prediction(mainwindow_id);
    }
}

void TableauDialog::updateCalendar()
{
    if (mainwindow_id == -1) {
        ui->yearComboBox->setCurrentText(QString::number(QDate::currentDate().year()));
        updateMonthButtonsForYear(ui->yearComboBox->currentText().toInt());
        return;
    }

    competition selectedComp = c.get_competition(mainwindow_id);
    QDate startDate = selectedComp.get_date_debut();
    QDate endDate = selectedComp.get_date_fin();

    if (startDate.isValid() && endDate.isValid() && startDate <= endDate) {
        ui->yearComboBox->setCurrentText(QString::number(startDate.year()));
        updateMonthButtonsForYear(startDate.year());
    } else {
        qDebug() << "Invalid or no date range for competition ID:" << mainwindow_id;
        ui->yearComboBox->setCurrentText(QString::number(QDate::currentDate().year()));
        updateMonthButtonsForYear(ui->yearComboBox->currentText().toInt());
    }
}

void TableauDialog::updateMonthButtonsForYear(int year)
{
    QList<QPushButton*> monthButtons = {
        ui->januaryButton, ui->februaryButton, ui->marchButton, ui->aprilButton,
        ui->mayButton, ui->juneButton, ui->julyButton, ui->augustButton,
        ui->septemberButton, ui->octoberButton, ui->novemberButton, ui->decemberButton
    };

    QString defaultStyle = "background-color: #3e4d64; color: #FFFFFF; border: 2px solid white; border-radius: 8px;";
    QString highlightStyle = "background-color: #5a7091; color: #FFFFFF; border: 2px solid white; border-radius: 8px;";

    for (QPushButton* button : monthButtons) {
        button->setStyleSheet(defaultStyle);
        button->setEnabled(true);
    }

    if (mainwindow_id == -1) {
        return;
    }

    competition selectedComp = c.get_competition(mainwindow_id);
    QDate startDate = selectedComp.get_date_debut();
    QDate endDate = selectedComp.get_date_fin();

    if (!startDate.isValid() || !endDate.isValid() || startDate > endDate) {
        return;
    }

    int startYear = startDate.year();
    int endYear = endDate.year();
    int startMonth = startDate.month();
    int endMonth = endDate.month();

    if (year == startYear && year == endYear) {
        for (int i = startMonth - 1; i < endMonth; ++i) {
            monthButtons[i]->setStyleSheet(highlightStyle);
        }
    } else if (year == startYear) {
        for (int i = startMonth - 1; i < 12; ++i) {
            monthButtons[i]->setStyleSheet(highlightStyle);
        }
    } else if (year == endYear) {
        for (int i = 0; i < endMonth; ++i) {
            monthButtons[i]->setStyleSheet(highlightStyle);
        }
    } else if (year > startYear && year < endYear) {
        for (QPushButton* button : monthButtons) {
            button->setStyleSheet(highlightStyle);
        }
    }
}

void TableauDialog::onYearChanged(const QString &yearText)
{
    updateMonthButtonsForYear(yearText.toInt());
}

void TableauDialog::on_searchTextChanged(const QString &search)
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

void TableauDialog::reconnectSelectionModel()
{
    disconnect(ui->test->selectionModel(), &QItemSelectionModel::currentRowChanged, this, nullptr);
    connect(ui->test->selectionModel(), &QItemSelectionModel::currentRowChanged, this, [=](const QModelIndex &current, const QModelIndex &previous) {
        if (current.isValid()) {
            mainwindow_id = current.sibling(current.row(), 0).data().toInt();
            qDebug() << "Selected competition ID:" << mainwindow_id;
            if (mainwindow_id == -1) {
                ui->comp_name->setText("No competition selected.");
                ui->team_name->setText("No team selected.");
            } else {
                prediction(mainwindow_id);
            }
            updateCalendar();
        }
    });
}

void TableauDialog::updateTableView()
{
    ui->test->setModel(c.show_competitions());
    reconnectSelectionModel();
    updateCalendar();
}

void TableauDialog::prediction(int id)
{
    if (id == -1) {
        ui->comp_name->setText("No competition selected.");
        ui->team_name->setText("No team selected.");
        ui->team_logo->clear();
        return;
    }

    QSqlQuery query;
    query.prepare("SELECT comp_name FROM competition WHERE id_competition = :id");
    query.bindValue(":id", id);
    if (!query.exec() || !query.next()) {
        qDebug() << "Error fetching competition name:" << query.lastError().text();
        ui->comp_name->setText("Unknown Competition");
        return;
    }
    QString competitionName = query.value(0).toString();
    ui->comp_name->setText("The potential winner for " + competitionName + " is:");

    query.prepare("SELECT ID_TEAM FROM participation WHERE id_comp = :id");
    query.bindValue(":id", id);
    if (!query.exec()) {
        qDebug() << "Error fetching participating teams:" << query.lastError().text();
        return;
    }

    QMap<int, double> teamStats;
    while (query.next()) {
        int teamId = query.value(0).toInt();
        QSqlQuery statsQuery;
        statsQuery.prepare("SELECT wins, draws, losses, goals_team FROM equipe WHERE id_team = :teamId");
        statsQuery.bindValue(":teamId", teamId);
        if (!statsQuery.exec() || !statsQuery.next()) {
            qDebug() << "Error fetching stats for team ID:" << teamId << statsQuery.lastError().text();
            continue;
        }

        int wins = statsQuery.value(0).toInt();
        int draws = statsQuery.value(1).toInt();
        int losses = statsQuery.value(2).toInt();
        int goalsTeam = statsQuery.value(3).toInt();
        double performanceScore = wins * 3 + draws - losses + goalsTeam * 0.5;
        teamStats[teamId] = performanceScore;
    }

    if (teamStats.isEmpty()) {
        ui->team_name->setText("No teams in this competition");
        ui->team_logo->clear();
        QMessageBox::warning(this, "Prediction Error", "No valid predictions could be made.");
        return;
    }

    int winningTeamId = -1;
    double maxScore = -1;
    for (auto it = teamStats.cbegin(); it != teamStats.cend(); ++it) {
        if (it.value() > maxScore) {
            maxScore = it.value();
            winningTeamId = it.key();
        }
    }

    if (winningTeamId == -1) {
        QMessageBox::information(this, "Prediction", "Unable to predict a winning team.");
        ui->team_logo->clear();
        return;
    }

    if (winningTeamId != -1) {
        QSqlQuery teamQuery;
        teamQuery.prepare("SELECT team_name FROM equipe WHERE id_team = :teamId");
        teamQuery.bindValue(":teamId", winningTeamId);

        if (teamQuery.exec() && teamQuery.next()) {
            QString winningTeamName = teamQuery.value(0).toString();
            qDebug() << "Predicted winning team:" << winningTeamName;
            ui->team_name->setText(winningTeamName);

            QSqlQuery logoQuery;
            logoQuery.prepare("SELECT team_logo FROM equipe WHERE id_team = :teamId");
            logoQuery.bindValue(":teamId", winningTeamId);

            if (logoQuery.exec() && logoQuery.next()) {
                QByteArray logoData = logoQuery.value(0).toByteArray();
                QPixmap teamLogo;
                if (teamLogo.loadFromData(logoData)) {
                    ui->team_logo->setPixmap(teamLogo.scaled(ui->team_logo->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
                } else {
                    qDebug() << "Failed to load team logo for team ID:" << winningTeamId;
                    ui->team_logo->clear();
                }
            } else {
                qDebug() << "Failed to fetch team logo:" << logoQuery.lastError().text();
                ui->team_logo->clear();
            }
        } else {
            qDebug() << "Failed to fetch winning team name:" << teamQuery.lastError().text();
        }
    } else {
        QMessageBox::information(this, "Prediction", "Unable to predict a winning team.");
    }
}

void TableauDialog::onMonthClicked(int month)
{
    int year = ui->yearComboBox->currentText().toInt();

    QList<QPushButton*> monthButtons = {
        ui->januaryButton, ui->februaryButton, ui->marchButton, ui->aprilButton,
        ui->mayButton, ui->juneButton, ui->julyButton, ui->augustButton,
        ui->septemberButton, ui->octoberButton, ui->novemberButton, ui->decemberButton
    };
    QPushButton* clickedButton = monthButtons[month - 1];

    bool isHighlighted = clickedButton->styleSheet().contains("#5a7091");

    if (isHighlighted && mainwindow_id != -1) {
        CalendarDialog *dialog = new CalendarDialog(mainwindow_id, year, month, this);
        dialog->exec();
        delete dialog;
    } else {
        QMessageBox::information(this, "No Matches",
                                 QString("No matches available for %1 %2.").arg(QLocale().monthName(month)).arg(year),
                                 QMessageBox::Ok);
    }
}

TableauDialog::~TableauDialog()
{
    delete ui;
}

void TableauDialog::on_pushButton_clicked()
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

void TableauDialog::on_pushButton_2_clicked()
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

void TableauDialog::on_pushButton_5_clicked()
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
    QString competitionType = selectedComp.get_type();
    QDate startDate = selectedComp.get_date_debut();
    QDate endDate = selectedComp.get_date_fin();

    if (!startDate.isValid() || !endDate.isValid() || startDate > endDate) {
        QMessageBox::warning(this, "Date Error", "Invalid competition start or end date.");
        return;
    }

    QSqlQuery insertQuery;

    int matchId;
    QSqlQuery maxIdQuery;
    maxIdQuery.prepare("SELECT MAX(id_match) FROM match");
    if (!maxIdQuery.exec() || !maxIdQuery.next()) {
        QMessageBox::warning(this, "Database Error", "Failed to fetch last match ID.");
        return;
    }
    matchId = maxIdQuery.value(0).isNull() ? 1 : maxIdQuery.value(0).toInt() + 1;

    QVector<QDate> matchDates;
    int totalDays = startDate.daysTo(endDate);
    if (totalDays < teamIds.size() - 1) {
        QMessageBox::warning(this, "Date Range Error", "Not enough days to schedule all matches.");
        return;
    }

    for (int i = 0; i <= totalDays; ++i) {
        matchDates.append(startDate.addDays(i));
    }

    QMap<int, QString> teamStadiums;
    for (int teamId : teamIds) {
        QSqlQuery stadiumQuery;
        stadiumQuery.prepare("SELECT home_stadium FROM equipe WHERE id_team = :teamId");
        stadiumQuery.bindValue(":teamId", teamId);

        if (stadiumQuery.exec() && stadiumQuery.next()) {
            QString stadium = stadiumQuery.value(0).toString();
            if (!stadium.isEmpty()) {
                teamStadiums[teamId] = stadium;
            }
        } else {
            QMessageBox::warning(this, "Database Error", "Failed to fetch stadium for team ID: " + QString::number(teamId));
            return;
        }
    }

    if (teamStadiums.isEmpty()) {
        QMessageBox::warning(this, "No Stadiums", "No valid stadiums found for the participating teams.");
        return;
    }

    int dateIndex = 0;
    int matchesPerDay = totalDays / (teamIds.size() * (teamIds.size() - 1) / 2);
    matchesPerDay = qMax(1, matchesPerDay);

    if (competitionType == "League") {
        for (int i = 0; i < teamIds.size(); ++i) {
            for (int j = i + 1; j < teamIds.size(); ++j) {
                insertQuery.prepare("INSERT INTO match (id_match, id_competition, id_teama, id_teamb, date_m, stadium) VALUES (:id_match, :id_competition, :id_teama, :id_teamb, TO_DATE(:match_date, 'YYYY-MM-DD'), :stadium)");
                insertQuery.bindValue(":id_match", matchId++);
                insertQuery.bindValue(":id_competition", mainwindow_id);
                insertQuery.bindValue(":id_teama", teamIds[i]);
                insertQuery.bindValue(":id_teamb", teamIds[j]);
                insertQuery.bindValue(":match_date", matchDates[dateIndex].toString("yyyy-MM-dd"));
                insertQuery.bindValue(":stadium", teamStadiums[teamIds[i]]);

                if (!insertQuery.exec()) {
                    QMessageBox::warning(this, "Database Error", "Failed to insert match: " + insertQuery.lastError().text());
                    return;
                }

                dateIndex = (dateIndex + matchesPerDay) % matchDates.size();

                insertQuery.prepare("INSERT INTO match (id_match, id_competition, id_teama, id_teamb, date_m, stadium) VALUES (:id_match, :id_competition, :id_teama, :id_teamb, TO_DATE(:match_date, 'YYYY-MM-DD'), :stadium)");
                insertQuery.bindValue(":id_match", matchId++);
                insertQuery.bindValue(":id_competition", mainwindow_id);
                insertQuery.bindValue(":id_teama", teamIds[j]);
                insertQuery.bindValue(":id_teamb", teamIds[i]);
                insertQuery.bindValue(":match_date", matchDates[dateIndex].toString("yyyy-MM-dd"));
                insertQuery.bindValue(":stadium", teamStadiums[teamIds[j]]);

                if (!insertQuery.exec()) {
                    QMessageBox::warning(this, "Database Error", "Failed to insert match: " + insertQuery.lastError().text());
                    return;
                }

                dateIndex = (dateIndex + matchesPerDay) % matchDates.size();
            }
        }
    } else if (competitionType == "Tournament") {
        std::random_shuffle(teamIds.begin(), teamIds.end());

        for (int i = 0; i < teamIds.size(); i += 2) {
            if (i + 1 < teamIds.size()) {
                insertQuery.prepare("INSERT INTO match (id_match, id_competition, id_teama, id_teamb, date_m, stadium) VALUES (:id_match, :id_competition, :id_teama, :id_teamb, TO_DATE(:match_date, 'YYYY-MM-DD'), :stadium)");
                insertQuery.bindValue(":id_match", matchId++);
                insertQuery.bindValue(":id_competition", mainwindow_id);
                insertQuery.bindValue(":id_teama", teamIds[i]);
                insertQuery.bindValue(":id_teamb", teamIds[i + 1]);
                insertQuery.bindValue(":match_date", matchDates[dateIndex].toString("yyyy-MM-dd"));
                insertQuery.bindValue(":stadium", teamStadiums[teamIds[i]]);

                if (!insertQuery.exec()) {
                    QMessageBox::warning(this, "Database Error", "Failed to insert match: " + insertQuery.lastError().text());
                    return;
                }

                dateIndex = (dateIndex + matchesPerDay) % matchDates.size();
            }
        }
    } else {
        QMessageBox::warning(this, "Unknown Type", "The competition type is unknown.");
        return;
    }

    QMessageBox::information(this, "Fixtures Generated", "Fixtures have been successfully generated with dates and stadiums.");
}
