#include "../userheaders/admin.h"
#include "ui_adminview.h"
#include <QMessageBox>
#include <QDebug>
#include "../userheaders/sessionmanager.h"
#include "../userheaders/mainwindow.h"
#include "../userheaders/adduser.h"
#include "../userheaders/displayuser.h" // Include the new header
#include "../userheaders/profile.h" // Include the new header
#include "../teamheaders/teamwindow.h" // Include the new header
#include "../playerheaders/playerwindow.h" // Include the new header
#include "../compheaders/competitionview.h" // Include the new header
#include <QScrollArea>
#include <QStackedWidget>


AdminWindow::AdminWindow(MainWindow *mainWindowParent, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AdminWindow),
    mainWindowParent(mainWindowParent),
    stats(nullptr),
    stackedWidget(nullptr),
    teamWindow(nullptr),
    playerWindow(nullptr),
    adminDashboard(nullptr)
{
    ui->setupUi(this);
    setWindowTitle("Admin Dashboard");

    // Save the current admin dashboard widget
    adminDashboard = ui->centralwidget;

    // Create the stacked widget and add admin dashboard
    stackedWidget = new QStackedWidget(this);
    stackedWidget->addWidget(adminDashboard);
    // Create and add the teamwindow, pass stackedWidget pointer
    teamWindow = new teamwindow(stackedWidget, this);
    stackedWidget->addWidget(teamWindow);
    // Create and add the playerwindow, pass stackedWidget pointer
    playerWindow = new playerwindow(stackedWidget, this);
    stackedWidget->addWidget(playerWindow);
    // Create and add the competitionview, pass stackedWidget pointer
    competitionview *competitionView = new competitionview(stackedWidget);
    stackedWidget->addWidget(competitionView);
    // Set stackedWidget as the central widget
    setCentralWidget(stackedWidget);
    // Show admin dashboard by default
    stackedWidget->setCurrentWidget(adminDashboard);

    // Connect sidebar buttons
    connect(ui->adminButton, &QPushButton::clicked, this, &AdminWindow::handleAdminButtonClicked);
    connect(ui->coachButton, &QPushButton::clicked, this, &AdminWindow::handleCoachButtonClicked);
    connect(ui->employeeButton, &QPushButton::clicked, this, &AdminWindow::handleEmployeeButtonClicked);
    connect(ui->logout, &QPushButton::clicked, this, &AdminWindow::handleLogoutButtonClicked);
    connect(ui->add_user, &QPushButton::clicked, this, &AdminWindow::handleAddUserButtonClicked);
    connect(ui->profileButton, &QPushButton::clicked, this, &AdminWindow::handleProfileButtonClicked);
    connect(ui->teamButton, &QPushButton::clicked, this, [this]() {
        stackedWidget->setCurrentWidget(teamWindow);
    });
    connect(ui->playerButton, &QPushButton::clicked, this, [this]() {
        stackedWidget->setCurrentWidget(playerWindow);
    });
    // Connect compButton to show competitionview in stackedWidget
    connect(ui->compButton, &QPushButton::clicked, this, [this, competitionView]() {
        stackedWidget->setCurrentWidget(competitionView);
    });

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

    // Instantiate Stats widget
    stats = new Stats(this);

    // Create a QScrollArea and set the stats widget as its content
    QScrollArea *scrollArea = new QScrollArea(ui->statsWidget);
    scrollArea->setWidget(stats);
    scrollArea->setWidgetResizable(true); // Makes the stats widget resize with the scroll area
    scrollArea->setStyleSheet("QScrollArea { background: transparent; border: none; }"
                              "QScrollBar:vertical { border: none; background: #2A2D3A; width: 10px; margin: 0px; }"
                              "QScrollBar::handle:vertical { background: #4CAF50; border-radius: 5px; }"
                              "QScrollBar::add-line:vertical, QScrollBar::sub-line:vertical { height: 0px; }"
                              "QScrollBar::add-page:vertical, QScrollBar::sub-page:vertical { background: none; }");

    // Add the scroll area to the statsWidget's layout
    QVBoxLayout *layout = new QVBoxLayout(ui->statsWidget);
    layout->addWidget(scrollArea);
}

AdminWindow::~AdminWindow()
{
    delete ui;
}

void AdminWindow::handleAdminButtonClicked()
{
    qDebug() << "Admin button clicked.";
    DisplayUser *displayUser = new DisplayUser("Admin", this);
    displayUser->setAttribute(Qt::WA_DeleteOnClose); // Auto-delete when closed
    displayUser->exec(); // Change from show() to exec() for modal dialog
}

void AdminWindow::handleCoachButtonClicked()
{
    qDebug() << "Coach button clicked.";
    DisplayUser *displayUser = new DisplayUser("Coach", this);
    displayUser->setAttribute(Qt::WA_DeleteOnClose);
    displayUser->exec(); // Change from show() to exec()
}

void AdminWindow::handleEmployeeButtonClicked()
{
    qDebug() << "Employee button clicked.";
    DisplayUser *displayUser = new DisplayUser("Employee", this);
    displayUser->setAttribute(Qt::WA_DeleteOnClose);
    displayUser->exec(); // Change from show() to exec()
}


void AdminWindow::handleAddUserButtonClicked()
{
    qDebug() << "Add User button clicked.";
    AddUser *addUserDialog = new AddUser(this);
    addUserDialog->setModal(true); // Make the dialog modal
    addUserDialog->exec(); // Show the dialog and wait for it to close
    delete addUserDialog; // Clean up
}
void AdminWindow::handleLogoutButtonClicked()
{
    qDebug() << "Logout button clicked.";

    // Clear the session to log out the user
    SessionManager::instance().clearSession();

    // Update the photo label to indicate no user
    ui->currentUserPhotoLabel->setText("No User");
    ui->dashboard_9->setText("User name"); // Reset username label
    ui->dashboard_8->setText("Role");      // Reset role label

    // Re-show the parent MainWindow if it exists
    if (mainWindowParent) {
        // Clear the email and password fields in MainWindow
        QLineEdit *emailField = mainWindowParent->findChild<QLineEdit*>("lineEdit");
        QLineEdit *passwordField = mainWindowParent->findChild<QLineEdit*>("lineEdit_2");
        if (emailField && passwordField) {
            emailField->clear();
            passwordField->clear();
        } else {
            qDebug() << "Failed to find email or password fields in MainWindow.";
        }
        mainWindowParent->show();
    } else {
        // Fallback: Create a new MainWindow
        qDebug() << "No parent MainWindow found, creating a new one.";
        MainWindow *loginWindow = new MainWindow();
        loginWindow->show();
    }

    // Close the current AdminWindow
    this->close();
}

void AdminWindow::handleProfileButtonClicked() {
    Profile *profileDialog = new Profile(this);
    profileDialog->setModal(true);
    profileDialog->exec();
    delete profileDialog;
}
