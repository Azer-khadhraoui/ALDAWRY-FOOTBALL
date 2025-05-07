#include "../userheaders/coach.h"
#include "ui_coach.h"
#include "../userheaders/displayplayers_coach.h"
#include <QDebug>
#include "../userheaders/sessionmanager.h"
#include "../userheaders/mainwindow.h"
#include <QLineEdit> // Include QLineEdit header
#include "../userheaders/displaymatch_coach.h"
#include "../teamheaders/team.h"

CoachWindow::CoachWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::CoachWindow)
{
    ui->setupUi(this);
    connect(ui->Viewplayers, &QPushButton::clicked, this, &CoachWindow::on_viewplayer_clicked);
    connect(ui->logout, &QPushButton::clicked, this, &CoachWindow::logout); // Connect logout button to close the window
    connect(ui->MatchesButton, &QPushButton::clicked, this, &CoachWindow::on_MatchesButton_clicked); // Connect match button

    
    // Load current user's photo and details
    const Employee& currentUser = SessionManager::instance().getCurrentUser();
    if (!currentUser.getFace().isEmpty()) {
        QPixmap pixmap;
        if (pixmap.loadFromData(currentUser.getFace())) {
            ui->currentUserPhotoLabel->setPixmap(pixmap.scaled(ui->currentUserPhotoLabel->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
        } else {
            qDebug() << "Failed to load user photo from data.";
            ui->currentUserPhotoLabel->setText("No Photo");
        }
    } else {
        ui->currentUserPhotoLabel->setText("No Photo");
    }

    // for the label_3 set it to the team logo of the current user
    int coachId = currentUser.getId();
    Team* team = Team::getTeamByCoachId(coachId);
    if (team) {
        QString teamName = team->getTeamName();
        QSqlQuery logoQuery;
        logoQuery.prepare("SELECT TEAM_LOGO FROM EQUIPE WHERE TEAM_NAME = :teamName");
        logoQuery.bindValue(":teamName", teamName);
        if (logoQuery.exec() && logoQuery.next()) {
            QByteArray logoData = logoQuery.value("TEAM_LOGO").toByteArray();
            QPixmap teamLogo;
            if (teamLogo.loadFromData(logoData)) {
                ui->label_3->setPixmap(teamLogo.scaled(ui->label_3->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
            } else {
                ui->label_3->setText("No Logo");
            }
        } else {
            ui->label_3->setText("No Logo");
        }
        delete team;
    } else {
        ui->label_3->setText("No Logo");
    }

    // Set username and role
    ui->dashboard_9->setText(currentUser.getFirstName() + " " + currentUser.getLastName());
    ui->dashboard_8->setText(currentUser.getRole());
    // Set window title
    setWindowTitle("Coach Dashboard");

}

CoachWindow::~CoachWindow()
{
    delete ui;
}

void CoachWindow::on_viewplayer_clicked()
{
    qDebug() << "ViewButton clicked, opening displayplayers_coach...";
    displayplayers_coach *displayPlayersWindow = new displayplayers_coach(this); // Set parent to this
    displayPlayersWindow->setAttribute(Qt::WA_DeleteOnClose); // Auto-delete when closed
    displayPlayersWindow->show();
}
void CoachWindow::on_MatchesButton_clicked()
{
    qDebug() << "Match button clicked, opening displaymatch_coach...";
    displaymatch_coach *displayMatchWindow = new displaymatch_coach(this); // Set parent to this
    displayMatchWindow->setAttribute(Qt::WA_DeleteOnClose); // Auto-delete when closed
    displayMatchWindow->show();
}
// logout function 
void CoachWindow::logout()
{
    qDebug() << "Logout button clicked.";

    // Clear the session to log out the user
    SessionManager::instance().clearSession();

    // Update the photo label to indicate no user
    ui->currentUserPhotoLabel->setText("No User");
    ui->dashboard_9->setText("User name"); // Reset username label
    ui->dashboard_8->setText("Role");      // Reset role label

    qDebug() << "No parent MainWindow found, creating a new one.";
    MainWindow *loginWindow = new MainWindow();
    loginWindow->show();

    // Close the current AdminWindow
    this->close();
}
