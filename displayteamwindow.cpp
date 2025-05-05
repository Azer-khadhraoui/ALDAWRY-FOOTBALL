#include "displayteamwindow.h"
#include "ui_display_team.h"

DisplayTeamWindow::DisplayTeamWindow(Team* team, QWidget *parent)
    : QMainWindow(parent), ui(new Ui::DisplayTeamWindow) {
    qDebug() << "DisplayTeamWindow constructor called";
    ui->setupUi(this);
    qDebug() << "UI setup complete";

    if (team == nullptr) {
        qDebug() << "Team is nullptr, cannot display info";
        return;
    }

    // Log the values before setting them
    qDebug() << "Setting team details - Name:" << team->getTeamName()
             << "Stadium:" << team->getHomeStadium()
             << "Goals:" << team->getGoals()
             << "Budget:" << team->getBudget();

    // Populate the UI with team details
    ui->teamNameDisplay->setText(team->getTeamName());
    ui->stadiumDisplay->setText(team->getHomeStadium());
    ui->goalsDisplay->setText(QString::number(team->getGoals()));
    ui->budgetDisplay->setText(QString::number(team->getBudget()));

    // Log the text of the labels after setting them
    qDebug() << "Team Name Display text after set:" << ui->teamNameDisplay->text();
    qDebug() << "Stadium Display text after set:" << ui->stadiumDisplay->text();
    qDebug() << "Goals Display text after set:" << ui->goalsDisplay->text();
    qDebug() << "Budget Display text after set:" << ui->budgetDisplay->text();

    // Verify the UI elements exist
    if (!ui->teamNameDisplay || !ui->stadiumDisplay || !ui->goalsDisplay || !ui->budgetDisplay) {
        qDebug() << "One or more UI elements are null!";
    } else {
        qDebug() << "All UI elements found, values set";
    }

    // Ensure widgets are visible
    ui->teamNameDisplay->setVisible(true);
    ui->stadiumDisplay->setVisible(true);
    ui->goalsDisplay->setVisible(true);
    ui->budgetDisplay->setVisible(true);

    // Force a minimum size for the labels
    ui->teamNameDisplay->setMinimumSize(100, 20);
    ui->stadiumDisplay->setMinimumSize(100, 20);
    ui->goalsDisplay->setMinimumSize(100, 20);
    ui->budgetDisplay->setMinimumSize(100, 20);

    // Force the window to update
    this->update();
    this->repaint();
}

DisplayTeamWindow::~DisplayTeamWindow() {
    delete ui;
}

