#include "addPlayer.h"
#include "ui_addPlayer.h"
#include <QSqlQuery>
#include <QMessageBox>
#include <QFileDialog>
#include <QFile>
#include <QPixmap>
#include <QRegularExpression>

AddPlayer::AddPlayer(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addPlayer)
{
    ui->setupUi(this);

    // Initialisation existante
    ui->comboBoxPosition->clear();
    ui->comboBoxPosition->addItems({"Goalkeeper", "Defender", "Midfielder", "Forward"});

    loadTeams();

    // Connexions existantes
   
    connect(ui->toolButtonImage, &QToolButton::clicked, this, &AddPlayer::on_toolButtonImage_clicked);
}

AddPlayer::~AddPlayer()
{
    delete ui;
}

void AddPlayer::loadTeams()
{
    ui->comboBoxTeam->clear();
    teamMap.clear();

    QSqlQuery query("SELECT id_team, team_name FROM equipe ORDER BY team_name");
    while (query.next()) {
        int id = query.value(0).toInt();
        QString name = query.value(1).toString();
        ui->comboBoxTeam->addItem(name);
        teamMap[name] = id;
    }
}

bool AddPlayer::validateInput()
{
    // Validation existante sans modifications
    if (ui->comboBoxTeam->currentIndex() < 0) {
        QMessageBox::warning(this, "Error", "Please select a team.");
        return false;
    }

    QString first_name = ui->lineEditFirstName->text().trimmed();
    QString last_name = ui->lineEditLastName->text().trimmed();
    QString nationality = ui->lineEditNationality->text().trimmed();

    if (first_name.isEmpty() || last_name.isEmpty() || nationality.isEmpty()) {
        QMessageBox::warning(this, "Error", "Please fill all required fields.");
        return false;
    }

    QRegularExpression nameRegex("^[A-Za-z\\s'-]+$");
    if (!nameRegex.match(first_name).hasMatch()) {
        QMessageBox::warning(this, "Error", "Invalid first name format.");
        ui->lineEditFirstName->setFocus();
        return false;
    }

    if (!nameRegex.match(last_name).hasMatch()) {
        QMessageBox::warning(this, "Error", "Invalid last name format.");
        ui->lineEditLastName->setFocus();
        return false;
    }

    bool ok;
    int jersey_nb = ui->lineEditJersey->text().toInt(&ok);
    if (!ok || jersey_nb <= 0 || jersey_nb > 99) {
        QMessageBox::warning(this, "Error", "Jersey number must be 1-99.");
        ui->lineEditJersey->setFocus();
        return false;
    }

    QDate dob = ui->dateEdit->date();
    QDate minDate = QDate::currentDate().addYears(-50);
    QDate maxDate = QDate::currentDate().addYears(-16);

    if (dob < minDate || dob > maxDate) {
        QMessageBox::warning(this, "Error", "Player must be 16-50 years old.");
        ui->dateEdit->setFocus();
        return false;
    }

    return true;
}

void AddPlayer::on_addButton_clicked()
{
    if (!validateInput()) return;

    QString teamName = ui->comboBoxTeam->currentText();
    int id_team = teamMap[teamName];

    joueur newPlayer(
        id_team,
        ui->lineEditFirstName->text().trimmed(),
        ui->lineEditLastName->text().trimmed(),
        ui->comboBoxPosition->currentText(),
        ui->lineEditJersey->text().toInt(),
        ui->dateEdit->date(),
        ui->lineEditNationality->text().trimmed(),
        img_joueur
        );

    if (newPlayer.ajouterDansBD()) {
        QMessageBox::information(this, "Success", "Player added successfully.");
        accept();
    } else {
        QMessageBox::critical(this, "Error", "Failed to add player.");
    }
}

void AddPlayer::on_toolButtonImage_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Select Image", "", "Images (*.png *.jpg *.jpeg *.bmp)");
    if (fileName.isEmpty()) return;

    QFile file(fileName);
    if (file.open(QIODevice::ReadOnly)) {
        img_joueur = file.readAll();
        file.close();

        QPixmap pixmap;
        if (pixmap.loadFromData(img_joueur)) {
            ui->labelImage->setPixmap(pixmap.scaled(ui->labelImage->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
        }
    } else {
        QMessageBox::critical(this, "Error", "Cannot read image file.");
    }
}
