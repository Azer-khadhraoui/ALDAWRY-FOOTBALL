#include "../teamheaders/modifyTeam.h"
#include "ui_modifyTeam.h"
#include <QFileDialog>
#include <QFile>
#include <QMessageBox>
#include <QDebug>
#include <QSqlError>
#include <QRegularExpression>

ModifyTeam::ModifyTeam(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::modifyTeam)
{
    ui->setupUi(this);


}

ModifyTeam::~ModifyTeam()
{
    delete ui;
}

void ModifyTeam::setTeamData(const QString &teamName, const QString &homeStadium, int budget, const QString &teamABV, const QByteArray &teamLogo)
{
    ui->l1_2->setText(teamName);
    ui->cb_2->setText(homeStadium);
    ui->l2_3->setText(QString::number(budget));
    ui->l2_4->setText(teamABV);
    this->teamLogo = teamLogo;
    ui->label_3->setText(teamLogo.isEmpty() ? "insert logo here" : "Logo loaded (" + QString::number(teamLogo.size()) + " bytes)");
    originalTeamName = teamName;  // Store the original team name
}

void ModifyTeam::on_toolButton_2_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Select Team Logo"),
                                                    "C:/",
                                                    tr("Images (*.png *.jpg *.jpeg *.bmp)"));
    if (!fileName.isEmpty()) {
        QFile file(fileName);
        if (file.open(QIODevice::ReadOnly)) {
            teamLogo = file.readAll();
            file.close();
            ui->label_3->setText(QFileInfo(fileName).fileName());
            qDebug() << "Image loaded, size:" << teamLogo.size() << "bytes";
        } else {
            QMessageBox::warning(this, "File Error", "Could not open the selected image.");
            ui->label_3->setText("insert logo here");
        }
    }
}

void ModifyTeam::on_button1_2_clicked()
{
    // Input validation
    QString teamName = ui->l1_2->text().trimmed();
    QString homeStadium = ui->cb_2->text().trimmed();
    QString budgetText = ui->l2_3->text().trimmed();
    QString teamABV = ui->l2_4->text().trimmed();

    // Check if any field is empty
    if (teamName.isEmpty() || homeStadium.isEmpty() || budgetText.isEmpty() || teamABV.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "All fields must be filled out.");
        return;
    }

    // Validate budget (must be a positive integer)
    bool ok;
    int budget = budgetText.toInt(&ok);
    if (!ok || budget <= 0) {
        QMessageBox::warning(this, "Input Error", "Budget must be a positive number.");
        return;
    }

    // Validate team abbreviation (must be 3 uppercase letters)
    QRegularExpression regex("^[A-Z]{3}$");
    if (!regex.match(teamABV).hasMatch()) {
        QMessageBox::warning(this, "Input Error", "Team abbreviation must be exactly 3 uppercase letters.");
        return;
    }

    // Update the database with the new data
    QSqlQuery query;
    query.prepare("UPDATE HOTSTUFF.EQUIPE SET HOME_STADIUM = :homeStadium, BUDG = :budget, TEAM_ABV = :teamABV WHERE TEAM_NAME = :teamName");
    query.bindValue(":homeStadium", homeStadium);
    query.bindValue(":budget", budget);
    query.bindValue(":teamABV", teamABV);
    query.bindValue(":teamName", teamName);

    if (query.exec()) {
        // Emit the signal with the updated team details
        emit teamModified(teamName, homeStadium, budget, teamABV);

        // Close the dialog
        QMessageBox::information(this, "Success", "Team updated successfully!");
        this->accept();
    } else {
        QMessageBox::critical(this, "Database Error", "Failed to update the team in the database: " + query.lastError().text());
    }
}

bool ModifyTeam::updateTeamInDatabase()
{
    // Input validation
    QString teamName = ui->l1_2->text().trimmed();
    QString homeStadium = ui->cb_2->text().trimmed();
    QString budgetText = ui->l2_3->text().trimmed();
    QString teamABV = ui->l2_4->text().trimmed();

    if (teamName.isEmpty() || homeStadium.isEmpty() || budgetText.isEmpty() || teamABV.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "All fields must be filled out.");
        return false;
    }

    bool ok;
    int budget = budgetText.toInt(&ok);
    if (!ok || budget <= 0) {
        QMessageBox::warning(this, "Input Error", "Budget must be a positive number.");
        return false;
    }

    QRegularExpression regex("^[A-Z]{3}$");
    if (!regex.match(teamABV).hasMatch()) {
        QMessageBox::warning(this, "Input Error", "Team abbreviation must be exactly 3 uppercase letters.");
        return false;
    }

    // Database update
    QSqlQuery query;
    query.prepare("UPDATE HOTSTUFF.EQUIPE SET TEAM_NAME = :team_name, HOME_STADIUM = :home_stadium, BUDG = :budget, TEAM_ABV = :team_abv, TEAM_LOGO = :team_logo WHERE TEAM_NAME = :original_team_name");
    query.bindValue(":team_name", teamName);
    query.bindValue(":home_stadium", homeStadium);
    query.bindValue(":budget", budget);
    query.bindValue(":team_abv", teamABV);
    query.bindValue(":team_logo", teamLogo);
    query.bindValue(":original_team_name", originalTeamName);

    if (!query.exec()) {
        qDebug() << "Update failed:" << query.lastError().text();
        return false;
    }

    qDebug() << "Update executed successfully, rows affected:" << query.numRowsAffected();
    return true;
}

void ModifyTeam::on_confirmButton_clicked()
{
    QString teamName = ui->l1_2->text(); // Correct widget for team name
    QString homeStadium = ui->cb_2->text(); // Correct widget for home stadium
    int budget = ui->l2_3->text().toInt(); // Correct widget for budget
    QString teamABV = ui->l2_4->text(); // Correct widget for team abbreviation

    // Emit the signal with the updated team details
    emit teamModified(teamName, homeStadium, budget, teamABV);

    // Close the dialog
    this->accept();
}
