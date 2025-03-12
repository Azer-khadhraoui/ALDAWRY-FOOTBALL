#include "modifyTeam.h"
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

    connect(ui->toolButton_2, &QToolButton::clicked, this, &ModifyTeam::on_toolButton_2_clicked);
}

ModifyTeam::~ModifyTeam()
{
    delete ui;
}

void ModifyTeam::setTeamData(const QString &teamName, const QString &homeStadium, int budget, const QString &teamABV, const QByteArray &teamLogo)
{
    ui->l1_2->setText(teamName);
    ui->cb_2->setCurrentText(homeStadium);
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
    QString teamName = ui->l1_2->text();
    QString homeStadium = ui->cb_2->currentText();
    QString budgetText = ui->l2_3->text();
    QString teamABV = ui->l2_4->text();

    if (teamName.isEmpty() || homeStadium.isEmpty() || budgetText.isEmpty() || teamABV.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Please fill in all required fields.");
        return;
    }

    QRegularExpression reAlpha("^[A-Za-z]+$");
    if (!reAlpha.match(teamName).hasMatch()) {
        QMessageBox::warning(this, "Input Error", "Team Name must contain only alphabets.");
        return;
    }

    bool ok;
    int budget = budgetText.toInt(&ok);
    if (!ok) {
        QMessageBox::warning(this, "Input Error", "Budget must be a valid integer.");
        return;
    }

    QRegularExpression reUpperAlpha("^[A-Z]+$");
    if (!reUpperAlpha.match(teamABV).hasMatch()) {
        QMessageBox::warning(this, "Input Error", "Team ABV must contain only uppercase alphabets.");
        return;
    }

    if (updateTeamInDatabase()) {
        QMessageBox::information(this, "Success", "Team updated successfully!");
        accept();
    } else {
        QMessageBox::critical(this, "Error", "Failed to update team in the database.");
    }
}

bool ModifyTeam::updateTeamInDatabase()
{
    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isOpen()) {
        qDebug() << "Database connection is closed!";
        return false;
    }

    QSqlQuery query(db);
    query.prepare("UPDATE HOTSTUFF.EQUIPE SET TEAM_NAME = :team_name, HOME_STADIUM = :home_stadium, BUDG = :budget, TEAM_ABV = :team_abv, TEAM_LOGO = :team_logo WHERE TEAM_NAME = :original_team_name");
    query.bindValue(":team_name", ui->l1_2->text());  // New team name
    query.bindValue(":home_stadium", ui->cb_2->currentText());
    query.bindValue(":budget", ui->l2_3->text().toInt());
    query.bindValue(":team_abv", ui->l2_4->text());
    query.bindValue(":team_logo", teamLogo);
    query.bindValue(":original_team_name", originalTeamName);  // Use original team name for WHERE clause

    qDebug() << "Executing update with values:"
             << "TEAM_NAME=" << ui->l1_2->text()
             << "HOME_STADIUM=" << ui->cb_2->currentText()
             << "BUDG=" << ui->l2_3->text().toInt()
             << "TEAM_ABV=" << ui->l2_4->text()
             << "TEAM_LOGO size=" << teamLogo.size()
             << "ORIGINAL_TEAM_NAME=" << originalTeamName;

    if (!query.exec()) {
        qDebug() << "Update failed:" << query.lastError().text();
        return false;
    }

    qDebug() << "Update executed successfully, rows affected:" << query.numRowsAffected();
    return true;
}
