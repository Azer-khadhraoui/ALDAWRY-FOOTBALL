#include "../teamheaders/formadd.h"
#include "ui_formadd.h"
#include "../teamheaders/team.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QRegularExpression>
#include "../userheaders/sessionmanager.h"
#include <QSqlQuery>
#include "../userheaders/mainwindow.h"
#include "../userheaders/coach.h"

FormAdd::FormAdd(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FormAdd)
{
    ui->setupUi(this);
}

FormAdd::~FormAdd()
{
    delete ui;
}

void FormAdd::on_toolButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Select Team Logo"),
                                                    "C:/",
                                                    tr("Images (*.png *.jpg *.jpeg *.bmp)"));
    if (!fileName.isEmpty()) {
        QFile file(fileName);
        if (file.open(QIODevice::ReadOnly)) {
            teamLogo = file.readAll(); // Store the image data
            file.close();
            ui->label_2->setText(QFileInfo(fileName).fileName());
        } else {
            QMessageBox::warning(this, "File Error", "Could not open the selected image.");
            ui->label_2->setText("Insert logo here");
        }
    } else {
        ui->label_2->setText("Insert logo here");
    }
}

void FormAdd::on_button1_clicked()
{
    QString teamName = ui->l1->text();
    QString homeStadium = ui->cb->text();
    QString budgetText = ui->l2->text();
    QString teamABV = ui->l2_2->text();

    // Validate required fields
    if (teamName.isEmpty() || homeStadium.isEmpty() || budgetText.isEmpty() || teamABV.isEmpty() || teamLogo.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Please fill in all required fields and select a team logo.");
        return;
    }

    // Validate Team Name (only alphabets)
    QRegularExpression reAlpha("^[A-Za-z]+$");
    if (!reAlpha.match(teamName).hasMatch()) {
        QMessageBox::warning(this, "Input Error", "Team Name must contain only alphabets.");
        return;
    }
    // Validate Home Stadium (only alphabets)
    if (!reAlpha.match(homeStadium).hasMatch()) {
        QMessageBox::warning(this, "Input Error", "Home Stadium must contain only alphabets.");
        return;
    }

    // Validate Budget (only numbers)
    bool ok;
    int budget = budgetText.toInt(&ok);
    if (!ok) {
        QMessageBox::warning(this, "Input Error", "Budget must be a valid integer.");
        return;
    }

    // Validate Team ABV (only uppercase alphabets)
    QRegularExpression reUpperAlpha("^[A-Z]+$");
    if (!reUpperAlpha.match(teamABV).hasMatch()) {
        QMessageBox::warning(this, "Input Error", "Team ABV must contain only uppercase alphabets.");
        return;
    }

    // Check if the team already exists in the database
    QSqlQuery checkQuery;
    checkQuery.prepare("SELECT COUNT(*) FROM HOTSTUFF.EQUIPE WHERE TEAM_NAME = :teamName");
    checkQuery.bindValue(":teamName", teamName);
    if (checkQuery.exec() && checkQuery.next() && checkQuery.value(0).toInt() > 0) {
        QMessageBox::warning(this, "Duplicate Error", "A team with the same name already exists.");
        return;
    }

    // Create a new team using setters
    Team newTeam;
    newTeam.setTeamName(teamName);
    newTeam.setHomeStadium(homeStadium);
    newTeam.setBudget(budget);
    newTeam.setTeamABV(teamABV);
    newTeam.setTeamLogo(teamLogo); // Use the stored logo data

    if (newTeam.Ajouter()) {
        QMessageBox::information(this, "Success", "Team added successfully!");
        emit teamAdded(); // Emit the signal to notify MainWindow
        // Get the newly created team's ID
        int newTeamId = -1;
        QSqlQuery getIdQuery;
        getIdQuery.prepare("SELECT ID_TEAM FROM HOTSTUFF.EQUIPE WHERE TEAM_NAME = :teamName");
        getIdQuery.bindValue(":teamName", teamName);
        if (getIdQuery.exec() && getIdQuery.next()) {
            newTeamId = getIdQuery.value(0).toInt();
        } else {
            QMessageBox::critical(this, "Error", "Failed to retrieve the new team's ID.");
            return;
        }
        // Get the coach ID from SessionManager
        int coachId = SessionManager::instance().getCurrentUser().getId();
        // Insert into COACH table to link the coach and team
        QSqlQuery query;
        query.prepare("INSERT INTO COACH (ID_EMP, ID_TEAM) VALUES (:empId, :teamId)");
        query.bindValue(":empId", coachId);
        query.bindValue(":teamId", newTeamId);
        if (!query.exec()) {
            QMessageBox::critical(this, "Error", "Failed to link coach to the team.");
        }
        // Check user role before returning to main window
        QString userRole = SessionManager::instance().getCurrentUser().getRole().toLower();
        if (userRole == "coach") {
            this->close();    // Close the form
            CoachWindow *coachWindow = new CoachWindow(this);
            coachWindow->show();
        } else {
            this->close();    // Just close the form for non-coach roles
        }
    } else {
        QMessageBox::critical(this, "Error", "Failed to add team to the database.");
    }
}

void FormAdd::on_resetButton_clicked()
{
    // Clear input fields
    ui->l1->clear();
    ui->l2->clear();
    ui->l2_2->clear();
    ui->label_2->setText("Insert logo here");
    teamLogo.clear();  // Clear the stored logo data
    ui->cb->clear();
}