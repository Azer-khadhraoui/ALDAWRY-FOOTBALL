#include "../matchheaders/addmatch.h"
#include <QMessageBox>
#include <QDateTime>
#include "../matchheaders/match.h"

addMatch::addMatch(QWidget *parent) : QDialog(parent), ui(new Ui::addMatch) {
    ui->setupUi(this);
    ui->Date->setMinimumDateTime(QDateTime::currentDateTime());
    ui->Date->setDateTime(QDateTime::currentDateTime());
    // Load teams and competitions into combo boxes
    Match::loadTeamsIntoComboBoxes(ui->team1, ui->team2);
    Match::loadCompetitionsIntoComboBox(ui->Comp);
    // Connect the Confirm button to the slot
}
addMatch::~addMatch() {
    delete ui;
}
void addMatch::on_Confirm_clicked() {
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
    if (matchDate < QDateTime::currentDateTime()) {
        QMessageBox::warning(this, "Error", "The selected date and time cannot be in the past!");
        return;
    }
    Match match;
    match.setId(Match::generateNewMatchId());
    match.setTeamA(team1Id);
    match.setTeamB(team2Id);
    match.setStadium(stadium);
    match.setReferee(referee);
    match.setCompetitionId(compId);
    match.setStatus("Scheduled");
    match.setMatchDateTime(matchDate);
    if (match.addMatch()) {
        QMessageBox::information(this, "Success", "Match added successfully!");
        ui->Referee_name->clear();
        ui->Stadium->clear();
        ui->Date->setDateTime(QDateTime::currentDateTime());
        emit matchAdded();
        this->close();
    } else {
        QMessageBox::critical(this, "Error", "Failed to add match!");
    }
}
