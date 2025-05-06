#include "../compheaders/addcompetitionwindow.h"
#include "ui_addcompetitionwindow.h"
#include <QWidget>
#include "../compheaders/competition.h"
#include <QMessageBox>
#include <QDate>


AddCompetitionWindow::AddCompetitionWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddCompetitionForm)
{
    ui->setupUi(this);
    ui->dateEdit_start_date->setDate(QDate::currentDate());
    ui->dateEdit_end_date->setDate(QDate::currentDate());
}

AddCompetitionWindow::~AddCompetitionWindow()
{
    delete ui;

}

void AddCompetitionWindow::on_pushButton_submit_clicked()
{
    QString name = ui->lineEdit_comp_name->text();
    QString type = ui->comboBox_comp_type->currentText();
    QDate date_debut = ui->dateEdit_start_date->date();
    QDate date_fin = ui->dateEdit_end_date->date();
    int nb_teams = ui->spinBox_numbers_teams->value();
    QString reward = ui->lineEdit_reward->text();

    // Input validation
    if (name.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Competition name cannot be empty.");
        return;
    }
    if (type.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Competition type cannot be empty.");
        return;
    }
    if (date_debut < QDate::currentDate()) {
        QMessageBox::warning(this, "Input Error", "Start date cannot be before the current date.");
        return;
    }
    if (date_debut > date_fin) {
        QMessageBox::warning(this, "Input Error", "Start date cannot be after end date.");
        return;
    }
    if (nb_teams <= 0) {
        QMessageBox::warning(this, "Input Error", "Number of teams must be greater than zero.");
        return;
    }
    if (reward.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Reward cannot be empty.");
        return;
    }

    int id = 1; // Assuming id is generated or assigned elsewhere
    competition c1(id, name, type, date_debut, date_fin, nb_teams, reward);
    if(c1.add_competition()) {
        QMessageBox::information(this, "Success", "Competition added successfully");
    } else {
        QMessageBox::critical(this, "Error", "Failed to add competition");
    }
    this->close();
}
