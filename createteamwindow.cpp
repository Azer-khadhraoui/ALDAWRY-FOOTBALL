#include "createteamwindow.h"
#include "ui_create_team.h"
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include "sessionmanager.h"

CreateTeamWindow::CreateTeamWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::CreateTeamWindow) {
    qDebug() << "CreateTeamWindow constructor called";
    ui->setupUi(this);
    qDebug() << "CreateTeamWindow UI setup complete.";
}

CreateTeamWindow::~CreateTeamWindow() {
    qDebug() << "CreateTeamWindow destructor called.";
    delete ui;
}

void CreateTeamWindow::on_createButton_clicked() {
    qDebug() << "Create button clicked.";
    QString teamName = ui->teamNameEdit->text().trimmed();
    QString stadium = ui->stadiumEdit->text().trimmed();
    QString goalsStr = ui->goalsEdit->text().trimmed();
    QString budgetStr = ui->budgetEdit->text().trimmed();

    qDebug() << "Input values - Team Name:" << teamName << "Stadium:" << stadium
             << "Goals:" << goalsStr << "Budget:" << budgetStr;

    bool ok;
    int goals = goalsStr.toInt(&ok);
    if (!ok || goals < 0) {
        qDebug() << "Goals validation failed.";
        QMessageBox::critical(this, "Error", "Goals must be a non-negative number.");
        return;
    }

    int budget = budgetStr.toInt(&ok);
    if (!ok || budget < 0) {
        qDebug() << "Budget validation failed.";
        QMessageBox::critical(this, "Error", "Budget must be a non-negative number.");
        return;
    }

    // Check for duplicate team name
    qDebug() << "Checking for duplicate team name...";
    QSqlQuery checkQuery;
    checkQuery.prepare("SELECT COUNT(*) FROM EQUIPE WHERE TEAM_NAME = :name");
    checkQuery.bindValue(":name", teamName);
    if (!checkQuery.exec() || !checkQuery.next()) {
        qDebug() << "Failed to check for duplicate team names:" << checkQuery.lastError().text();
        QMessageBox::critical(this, "Error", "Failed to check for duplicate team names: " + checkQuery.lastError().text());
        return;
    }

    if (checkQuery.value(0).toInt() > 0) {
        qDebug() << "Duplicate team name found.";
        QMessageBox::critical(this, "Error", "A team with the name '" + teamName + "' already exists.");
        return;
    }

    // Create the team
    qDebug() << "Creating Team object...";
    Team team(0, teamName, stadium, goals, budget);
    qDebug() << "Calling addTeam()...";
    if (!team.addTeam()) {
        qDebug() << "Failed to create team:" << QSqlDatabase::database().lastError().text();
        QMessageBox::critical(this, "Error", "Failed to create team: " + QSqlDatabase::database().lastError().text());
        return;
    }

    // Get the newly created team's ID
    qDebug() << "Retrieving team ID...";
    QSqlQuery query;
    query.prepare("SELECT ID_TEAM FROM EQUIPE WHERE TEAM_NAME = :name AND HOME_STADIUM = :stadium");
    query.bindValue(":name", teamName);
    query.bindValue(":stadium", stadium);
    if (!query.exec() || !query.next()) {
        qDebug() << "Failed to retrieve team ID:" << query.lastError().text();
        QMessageBox::critical(this, "Error", "Failed to retrieve team ID: " + query.lastError().text());
        return;
    }

    int teamId = query.value(0).toInt();
    qDebug() << "Team ID retrieved:" << teamId;

    // Get the coach ID from SessionManager
    int coachId = SessionManager::instance().getCurrentUser().getId();
    qDebug() << "Using coach ID from SessionManager:" << coachId;

    // Insert into COACH table to link the coach and team
    qDebug() << "Inserting into COACH table...";
    query.prepare("INSERT INTO COACH (ID_EMP, ID_TEAM) VALUES (:empId, :teamId)");
    query.bindValue(":empId", coachId);
    query.bindValue(":teamId", teamId);
    if (!query.exec()) {
        qDebug() << "Failed to link coach to team:" << query.lastError().text();
        QMessageBox::critical(this, "Error", "Failed to link coach to team: " + query.lastError().text());
        return;
    }

    qDebug() << "Team created successfully!";
    QMessageBox::information(this, "Success", "Team created successfully!");
    this->close();
}
