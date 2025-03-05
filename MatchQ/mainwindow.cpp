#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "match.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QMessageBox>
#include <QDebug>
#include <QDateTime>
#include <QSqlTableModel>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Set the minimum date and time to the current date and time to prevent past selections
    ui->Date->setMinimumDateTime(QDateTime::currentDateTime());

    // Attempt to connect to the database
    if (dbConnection.createconnect()) {
        qDebug() << "Database connected successfully in MainWindow";
        // Load teams and competitions into combo boxes
        Match::loadTeamsIntoComboBoxes(ui->team1, ui->team2);
        Match::loadCompetitionsIntoComboBox(ui->Comp);
        
    } else {
        qDebug() << "Failed to connect to database in MainWindow";
        // Disable combo boxes and show an error message
        ui->team1->setEnabled(false);
        ui->team2->setEnabled(false);
        ui->Comp->setEnabled(false);
        QMessageBox::critical(this, "Error", "Database connection failed. Teams and competitions cannot be loaded.");
    }

    // Set the current date and time in the Date QDateTimeEdit
    ui->Date->setDateTime(QDateTime::currentDateTime());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_Confirm_clicked()
{
    // Retrieve values from UI widgets
    int team1Id = ui->team1->currentData().toInt();
    int team2Id = ui->team2->currentData().toInt();
    QString stadium = ui->Stadium->text();
    QString referee = ui->Referee_name->text();
    int compId = ui->Comp->currentData().toInt();
    QDateTime matchDate = ui->Date->dateTime();

    // Validate inputs: teams must be different and stadium/referee cannot be empty
    if (team1Id == team2Id) {
        QMessageBox::warning(this, "Error", "Teams must be different!");
        return;
    }
    if (stadium.isEmpty() || referee.isEmpty()) {
        QMessageBox::warning(this, "Error", "Stadium and Referee name are required!");
        return;
    }

    // Validate that the selected date and time is not in the past
    if (matchDate < QDateTime::currentDateTime()) {
        QMessageBox::warning(this, "Error", "The selected date and time cannot be in the past!");
        return;
    }

    // Create a new Match object and set its properties
    Match match;
    match.setId(Match::generateNewMatchId());
    match.setTeamA(team1Id);
    match.setTeamB(team2Id);
    match.setStadium(stadium);
    match.setReferee(referee);
    match.setCompetitionId(compId);
    match.setStatus("Scheduled");
    // If you later add a date field to Match, you can set it here:
    // match.setDate(matchDate);

    // Attempt to add the match to the database
    if (match.addMatch()) {
        QMessageBox::information(this, "Success", "Match added successfully!");
        // Clear/reset fields after success
        ui->Referee_name->clear();
        ui->Stadium->clear();
        ui->Date->setDateTime(QDateTime::currentDateTime());
    } else {
        QMessageBox::critical(this, "Error", "Failed to add match!");
    }
}