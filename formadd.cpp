#include "formadd.h"
#include "ui_formadd.h"
#include "team.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QRegularExpression>

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
    QString homeStadium = ui->cb->currentText();
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
        this->close();    // Close the form
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
    ui->cb->setCurrentIndex(0);
}