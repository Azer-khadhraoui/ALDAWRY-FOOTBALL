#include "../compheaders/tableau1.h"
#include "ui_tableau1.h"
#include <QSqlQuery>
#include <QVariant>
#include <QSqlError>
#include <QDebug>
#include <QPdfWriter>
#include <QPainter>
#include <QFileDialog>
#include <QRandomGenerator> // Add this include for QRandomGenerator
#include <QMessageBox>
#include <algorithm>

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
// auto generate matches

QList<QList<QPair<int, int>>> TableauDialog::generateRoundRobinFixture(const QList<int>& teamIds)
{
    QList<QList<QPair<int, int>>> rounds;
    int numTeams = teamIds.size();

    if (numTeams < 2) {
        qDebug() << "Fixture generation failed: At least 2 teams required.";
        return rounds;
    }

    // Handle odd number of teams by adding a dummy team
    QList<int> teams = teamIds;
    bool hasBye = false;
    if (numTeams % 2 != 0) {
        teams.append(-1); // Dummy team
        numTeams++;
        hasBye = true;
    }

    // Create a list for scheduling
    QList<int> schedule;
    for (int i = 0; i < numTeams; ++i) {
        schedule.append(i); // Indices into teams list
    }

    // Generate first round-robin (numTeams - 1 rounds)
    for (int round = 0; round < numTeams - 1; ++round) {
        QList<QPair<int, int>> roundMatches;

        // Pair teams: 1 vs. n, 2 vs. n-1, ..., n/2 vs. n/2+1
        for (int i = 0; i < numTeams / 2; ++i) {
            int team1Idx = schedule[i];
            int team2Idx = schedule[numTeams - 1 - i];
            int team1Id = teams[team1Idx];
            int team2Id = teams[team2Idx];

            // Skip invalid pairs (shouldn't happen)
            if (team1Id == -1 && team2Id == -1) {
                continue;
            }

            // Alternate home/away for balance
            if (round % 2 == 0) {
                roundMatches.append(qMakePair(team1Id, team2Id)); // team1 home
            } else {
                roundMatches.append(qMakePair(team2Id, team1Id)); // team2 home
            }
        }
        rounds.append(roundMatches);

        // Rotate: Keep team 0 fixed, rotate others clockwise
        // Move last team to position 1, shift others right
        int last = schedule[numTeams - 1];
        for (int i = numTeams - 1; i > 1; --i) {
            schedule[i] = schedule[i - 1];
        }
        schedule[1] = last;
    }

    // Generate second round-robin (reverse home/away)
    for (int round = 0; round < numTeams - 1; ++round) {
        QList<QPair<int, int>> roundMatches;
        for (const auto& match : rounds[round]) {
            roundMatches.append(qMakePair(match.second, match.first)); // Swap home/away
        }
        rounds.append(roundMatches);
    }

    return rounds;
}
QList<QList<QPair<int, int>>> TableauDialog::generateKnockoutFixture(const QList<int>& teamIds)
{
    QList<QList<QPair<int, int>>> rounds;
    int numTeams = teamIds.size();

    if (numTeams < 2) {
        qDebug() << "Knockout fixture generation failed: At least 2 teams required.";
        return rounds;
    }

    // Calculate rounds: ceil(log2(numTeams))
    int roundsNeeded = qCeil(qLn(numTeams) / qLn(2));
    int teamsInFirstRound = 1 << roundsNeeded; // Next power of 2
    int byes = teamsInFirstRound - numTeams;

    // Shuffle teams for random pairing
    QList<int> currentTeams = teamIds;
    std::random_shuffle(currentTeams.begin(), currentTeams.end(), [](int max) {
        return QRandomGenerator::global()->bounded(max);
    });

    // First round: pair teams, assign byes
    QList<QPair<int, int>> firstRound;
    int matches = (numTeams - byes) / 2;
    int teamIndex = 0;

    // Actual matches
    for (int i = 0; i < matches && teamIndex + 1 < numTeams; ++i) {
        firstRound.append(qMakePair(currentTeams[teamIndex], currentTeams[teamIndex + 1]));
        teamIndex += 2;
    }

    // Byes
    for (int i = 0; i < byes && teamIndex < numTeams; ++i) {
        firstRound.append(qMakePair(currentTeams[teamIndex], -1));
        teamIndex++;
    }

    rounds.append(firstRound);

    // Subsequent rounds: placeholders (-2)
    int teamsRemaining = teamsInFirstRound / 2;
    for (int round = 1; round < roundsNeeded; ++round) {
        QList<QPair<int, int>> nextRound;
        for (int i = 0; i < teamsRemaining / 2; ++i) {
            nextRound.append(qMakePair(-2, -2));
        }
        rounds.append(nextRound);
        teamsRemaining /= 2;
    }

    return rounds;
}

int TableauDialog::generateNewMatchId_comp() {
    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isOpen()) {
        qDebug() << "Database not open when generating new match ID";
        return -1;  // Return an invalid ID to indicate failure
    }

    QSqlQuery query("SELECT MAX(ID_MATCH) FROM Match");
    if (query.next()) {
        return query.value(0).toInt() + 1;
    }
    return 1;  // Start with 1 if no matches exist
}

bool TableauDialog::generateMatchDates(int competitionId, const QString &competitionType, const QDate &startDate, const QDate &endDate, int /*nbTeams*/)
{
    // Validate competition type
    QString compTypeLower = competitionType.toLower();
    if (compTypeLower != "league" && compTypeLower != "knockout") {
        QString errorMessage = "Match generation failed: Only 'league' or 'knockout' competitions supported.";
        qDebug() << errorMessage;
        QMessageBox::critical(nullptr, "Error", errorMessage);
        return false;
    }

    // Step 1: Fetch teams and stadiums
    QSqlQuery teamQuery;
    teamQuery.prepare("SELECT P.ID_TEAM, E.HOME_STADIUM "
                      "FROM PARTICIPATION P "
                      "JOIN EQUIPE E ON P.ID_TEAM = E.ID_TEAM "
                      "WHERE P.ID_COMP = :compId");
    teamQuery.bindValue(":compId", competitionId);

    if (!teamQuery.exec()) {
        QString errorMessage = "Match generation failed: Unable to fetch teams: " + teamQuery.lastError().text();
        qDebug() << errorMessage;
        QMessageBox::critical(nullptr, "Error", errorMessage);
        return false;
    }

    QList<int> teamIds;
    QMap<int, QString> teamStadiums;
    while (teamQuery.next()) {
        int teamId = teamQuery.value("ID_TEAM").toInt();
        QString stadium = teamQuery.value("HOME_STADIUM").toString();
        teamIds.append(teamId);
        teamStadiums[teamId] = stadium;
    }

    int numTeams = teamIds.size();
    if (numTeams < 2) {
        QString errorMessage = "Match generation failed: At least 2 teams required.";
        qDebug() << errorMessage;
        QMessageBox::critical(nullptr, "Error", errorMessage);
        return false;
    }

    // Step 2: Generate fixture based on competition type
    QList<QList<QPair<int, int>>> rounds;
    if (compTypeLower == "league") {
        rounds = generateRoundRobinFixture(teamIds);
    } else { // knockout
        rounds = generateKnockoutFixture(teamIds);
    }
    int totalRounds = rounds.size();

    // Step 3: Validate date range
    QDate expectedEndDate = startDate.addDays(totalRounds * 7);
    if (expectedEndDate > endDate) {
        QString errorMessage = "Match generation failed: End date exceeded. Requires " +
                               QString::number(totalRounds) + " weeks.";
        qDebug() << errorMessage;
        QMessageBox::critical(nullptr, "Error", errorMessage);
        return false;
    }

    // Step 4: Referees
    QStringList referees = {"Pierluigi Collina", "Howard Webb", "Markus Merk", "Massimo Busacca", "Viktor Kassai"};

    // Step 5: Prepare insert queries
    QSqlQuery ligueFirstRoundQuery;
    ligueFirstRoundQuery.prepare("INSERT INTO Match (ID_MATCH, ID_COMPETITION, ID_TEAMA, ID_TEAMB, "
                                 "STADIUM, REFEREE_NAME, MATCH_DATETIME, STATUS_M) "
                                 "VALUES (:id, :compId, :teamA, :teamB, :stadium, :referee, :dateTime, :status)");

    QSqlQuery knockoutLaterRoundQuery;
    knockoutLaterRoundQuery.prepare("INSERT INTO Match (ID_MATCH, ID_COMPETITION, STADIUM, REFEREE_NAME, "
                                    "MATCH_DATETIME, STATUS_M) "
                                    "VALUES (:id, :compId, :stadium, :referee, :dateTime, :status)");

    QDate currentRoundDate = startDate;
    bool isFirstRound = true;

    for (const auto& round : rounds) {
        int matchesScheduled = 0; // Matches per day
        int dayOffset = 0; // Days within round
        QTime matchStartTime(14, 0); // Start at 14:00

        for (const auto& match : round) {
            int homeTeamId = match.first;
            int awayTeamId = match.second;

            // Skip byes (-1)
            if (homeTeamId == -1 || awayTeamId == -1) {
                continue;
            }

            // Check if day is full (4 matches: 14:00, 16:00, 18:00, 20:00)
            if (matchesScheduled >= 4) {
                dayOffset++;
                matchStartTime = QTime(14, 0);
                matchesScheduled = 0;
            }

            int newMatchId = generateNewMatchId_comp();
            QDate matchDate = currentRoundDate.addDays(dayOffset);
            QDateTime matchDateTime(matchDate, matchStartTime);
            QString referee = referees.at(QRandomGenerator::global()->bounded(referees.size()));

            if (compTypeLower == "league" || (compTypeLower == "knockout" && isFirstRound && homeTeamId != -2 && awayTeamId != -2)) {
                // Ligue or knockout first round: full data
                ligueFirstRoundQuery.bindValue(":id", newMatchId);
                ligueFirstRoundQuery.bindValue(":compId", competitionId);
                ligueFirstRoundQuery.bindValue(":teamA", homeTeamId);
                ligueFirstRoundQuery.bindValue(":teamB", awayTeamId);
                ligueFirstRoundQuery.bindValue(":stadium", teamStadiums.value(homeTeamId, "Unknown Stadium"));
                ligueFirstRoundQuery.bindValue(":referee", referee);
                ligueFirstRoundQuery.bindValue(":dateTime", matchDateTime);
                ligueFirstRoundQuery.bindValue(":status", "Scheduled");

                if (!ligueFirstRoundQuery.exec()) {
                    QString errorMessage = "Match insertion failed for ID " + QString::number(newMatchId) +
                                           ": " + ligueFirstRoundQuery.lastError().text();
                    qDebug() << errorMessage;
                    QMessageBox::critical(nullptr, "Error", errorMessage);
                    return false;
                }
            } else {
                // Knockout later rounds: omit ID_TEAMA, ID_TEAMB
                knockoutLaterRoundQuery.bindValue(":id", newMatchId);
                knockoutLaterRoundQuery.bindValue(":compId", competitionId);
                knockoutLaterRoundQuery.bindValue(":stadium", QString("TBD"));
                knockoutLaterRoundQuery.bindValue(":referee", referee);
                knockoutLaterRoundQuery.bindValue(":dateTime", matchDateTime);
                knockoutLaterRoundQuery.bindValue(":status", "Scheduled");

                if (!knockoutLaterRoundQuery.exec()) {
                    QString errorMessage = "Match insertion failed for ID " + QString::number(newMatchId) +
                                           ": " + knockoutLaterRoundQuery.lastError().text();
                    qDebug() << errorMessage;
                    QMessageBox::critical(nullptr, "Error", errorMessage);
                    return false;
                }
            }

            matchesScheduled++;
            matchStartTime = matchStartTime.addSecs(2 * 60 * 60); // 2 hours
        }

        // Next round: 7 days from start
        currentRoundDate = currentRoundDate.addDays(7);
        isFirstRound = false;
    }

    return true;
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

    competition selectedComp = c.get_competition(mainwindow_id);
    QString competitionType = selectedComp.get_type();
    QDate startDate = selectedComp.get_date_debut();
    QDate endDate = selectedComp.get_date_fin();

    if (!startDate.isValid() || !endDate.isValid() || startDate > endDate) {
        QMessageBox::warning(this, "Date Error", "Invalid competition start or end date.");
        return;
    }

    // Use generateMatchDates to generate and insert matches
    if (generateMatchDates(mainwindow_id, competitionType, startDate, endDate, 0)) {
        QMessageBox::information(this, "Fixtures Generated", "Fixtures have been successfully generated with dates and stadiums.");
    }
}
