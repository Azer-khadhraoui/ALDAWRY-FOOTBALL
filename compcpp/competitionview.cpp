#include "../compheaders/competitionview.h"
#include "ui_competitionview.h"
#include "../userheaders/sessionmanager.h"
#include <QstackedWidget>
#include "../teamheaders/teamwindow.h"
#include "../playerheaders/playerwindow.h"
#include "../userheaders/mainwindow.h"
#include "../matchheaders/matchview.h"

competitionview::competitionview(QStackedWidget *stackedWidget, QWidget *parent)
    : QWidget(parent),
    ui(new Ui::competitionview),
    mainwindow_id(-1)
{
    ui->setupUi(this);
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
    // Set username and role
    ui->dashboard_9->setText(currentUser.getFirstName() + " " + currentUser.getLastName());
    ui->dashboard_8->setText(currentUser.getRole());
    connect(ui->userbutton, &QPushButton::clicked, this, &competitionview::on_userbutton_clicked);


    // Connect playerButton to show playerwindow
    connect(ui->playerButton, &QPushButton::clicked, this, [this]() {
        QStackedWidget *stackedWidget = qobject_cast<QStackedWidget*>(parentWidget());
        if (stackedWidget) {
            // Assuming the team window is at index 1 in the stacked widget
            stackedWidget->setCurrentIndex(2);
        }
    });
    // Connect teamButton to show teamwindow
    connect(ui->teamButton, &QPushButton::clicked, this, [this]() {
        QStackedWidget *stackedWidget = qobject_cast<QStackedWidget*>(parentWidget());
        if (stackedWidget) {
            // Assuming the team window is at index 1 in the stacked widget
            stackedWidget->setCurrentIndex(1);
        }
    });
    // Connect matchButton to show matchview
    connect(ui->matchButton, &QPushButton::clicked, this, [this]() {
        QStackedWidget *stackedWidget = qobject_cast<QStackedWidget*>(parentWidget());
        if (stackedWidget) {
            // Assuming the match view is at index 3 in the stacked widget
            stackedWidget->setCurrentIndex(4);
        }
    });

    // Connect logout button
    connect(ui->logout, &QPushButton::clicked, this, &competitionview::on_logoutButton_clicked);
}

void competitionview::on_logoutButton_clicked()
{
    qDebug() << "Logout button clicked.";
    // Clear the session to log out the user
    SessionManager::instance().clearSession();

    // Update the photo label to indicate no user
    ui->currentUserPhotoLabel->setText("No User");
    ui->dashboard_9->setText("User name");
    ui->dashboard_8->setText("Role");

    // Re-show the parent MainWindow if it exists
    QWidget *parent = parentWidget();
    MainWindow *mainWindow = qobject_cast<MainWindow*>(parent);
    if (mainWindow) {
        mainWindow->show();
    } else {
        qDebug() << "No parent MainWindow found, creating a new one.";
        MainWindow *loginWindow = new MainWindow();
        loginWindow->show();
    }

    // Close all parent windows up the chain (including stacked widgets)
    QWidget *w = this;
    while (w) {
        QWidget *parent = w->parentWidget();
        w->close();
        w = parent;
    }
}

competitionview::~competitionview()
{
    delete ui;
}

void competitionview::on_pushButton_3_clicked()
{
    AddCompetitionWindow a;
    if (a.exec() == QDialog::Accepted) {
    }
}

void competitionview::on_pushButton_4_clicked()
{
    statistics s;
    if (s.exec() == QDialog::Accepted) {
    }
}

void competitionview::on_pushButton_6_clicked()
{
    TableauDialog t;
    if (t.exec() == QDialog::Accepted) {
    }
}

void competitionview::on_userbutton_clicked()
{
    QStackedWidget *stackedWidget = qobject_cast<QStackedWidget*>(parentWidget());
    if (stackedWidget) {
        stackedWidget->setCurrentIndex(0);
        return;
    }

    QString role = SessionManager::instance().getCurrentUser().getRole();
    if (role.toLower() == "admin" && stackedWidget) {
        stackedWidget->setCurrentIndex(0);
        return;
    }
}
