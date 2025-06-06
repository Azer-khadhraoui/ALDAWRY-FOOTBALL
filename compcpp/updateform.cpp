#include "../compheaders/updateform.h"
#include "ui_updateform.h"
#include <QWidget>
#include "../compheaders/competition.h"
#include <QMessageBox>
#include <QDate>
#include "../compheaders/competitionview.h"

updateform::updateform(QWidget *parent, int id) :
QDialog(parent),
ui(new Ui::updateform),
m_id(id)
{
    ui->setupUi(this);
    

    ui->lineEdit_id->setText(QString::number(m_id));
    int idd = ui->lineEdit_id->text().toInt();
    competition c1;
        c1=c1.get_competition(idd);
        ui->lineEdit_id->setReadOnly(true);
        ui->lineEdit_comp_name->setText(c1.get_name());
        ui->comboBox_comp_type->setCurrentText(c1.get_type());
        ui->dateEdit_start_date->setDate(c1.get_date_debut());
        ui->dateEdit_end_date->setDate(c1.get_date_fin());
        ui->spinBox_numbers_teams->setValue(c1.get_nb_teams());
        ui->lineEdit_reward->setText(c1.get_reward());
}
updateform::~updateform()
{
    delete ui;
}




void updateform::on_pushButton_submit_clicked()
{
    QString name = ui->lineEdit_comp_name->text();
    QString type = ui->comboBox_comp_type->currentText();
    QDate date_debut = ui->dateEdit_start_date->date();
    QDate date_fin = ui->dateEdit_end_date->date();
    int nb_teams = ui->spinBox_numbers_teams->value();
    QString reward = ui->lineEdit_reward->text();
    int id = ui->lineEdit_id->text().toInt();

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
    competition c1(id, name, type, date_debut, date_fin, nb_teams, reward);
    if(c1.update_competition(id)) {
        QMessageBox::information(this, "Success", "Competition updated successfully");
        this->close();
    } else {
        QMessageBox::warning(this, "Error", "Failed to update competition.");
    }
}

