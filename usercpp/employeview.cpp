#include "../userheaders/employeview.h"
#include "ui_employeview.h"
#include <QMessageBox>
#include <QDebug>
#include <QVBoxLayout>
#include <QGraphicsDropShadowEffect>
#include "../userheaders/sessionmanager.h"
#include "../userheaders/mainwindow.h"
#include "../userheaders/adduser.h"
#include "../userheaders/displayuser.h"
#include "../userheaders/profile.h"
#include <QScrollArea> // Added this include
#include "../teamheaders/teamwindow.h"
#include "../compheaders/competitionview.h"
#include <QStackedWidget>
#include "../playerheaders/playerwindow.h"
#include "../matchheaders/matchview.h"


EmployeeWindow::EmployeeWindow(MainWindow *mainWindowParent, QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::EmployeeWindow),
      mainWindowParent(mainWindowParent),
      stats(nullptr),
      stackedWidget(nullptr),
      teamWindow(nullptr),
      playerWindow(nullptr),
      employee(nullptr),
      matchView(nullptr) // Initialize matchView to nullptr
{
    ui->setupUi(this);
    setWindowTitle("Employee Dashboard");

    // Save the current admin dashboard widget
    employee = ui->centralwidget;

    // Create the stacked widget and add admin dashboard
    stackedWidget = new QStackedWidget(this);
    stackedWidget->addWidget(employee);
    // Create and add the teamwindow, pass stackedWidget pointer
    teamWindow = new teamwindow(stackedWidget, this);
    stackedWidget->addWidget(teamWindow);
    // Create and add the playerwindow, pass stackedWidget pointer
    playerWindow = new playerwindow(stackedWidget, this);
    stackedWidget->addWidget(playerWindow);
    // Create and add the competitionview, pass stackedWidget pointer
    competitionview *competitionView = new competitionview(stackedWidget);
    stackedWidget->addWidget(competitionView);

    // Create and add the matchview, pass stackedWidget pointer
    matchView = new matchview(stackedWidget, this);
    stackedWidget->addWidget(matchView);
    // Set stackedWidget as the central widget
    setCentralWidget(stackedWidget);
    // Show admin dashboard by default
    stackedWidget->setCurrentWidget(employee);

    // Connect button signals to slots
    connect(ui->coachButton, &QPushButton::clicked, this, &EmployeeWindow::handleCoachButtonClicked);
    connect(ui->employeeButton, &QPushButton::clicked, this, &EmployeeWindow::handleEmployeeButtonClicked);
    connect(ui->pushButton, &QPushButton::clicked, this, &EmployeeWindow::handleLogoutButtonClicked);
    connect(ui->add_user, &QPushButton::clicked, this, &EmployeeWindow::handleAddUserButtonClicked);
    connect(ui->profileButton, &QPushButton::clicked, this, &EmployeeWindow::handleProfileButtonClicked);
    connect(ui->teamButton, &QPushButton::clicked, this, [this]() {
        stackedWidget->setCurrentWidget(teamWindow);
    });
    connect(ui->playerButton, &QPushButton::clicked, this, [this]() {
        stackedWidget->setCurrentWidget(playerWindow);
    });
    
    // If you have a QPushButton for competition, use:
    connect(ui->compButton, &QPushButton::clicked, this, [this, competitionView]() {
       stackedWidget->setCurrentWidget(competitionView);
    });
    // Connect matchButton to show matchview in stackedWidget
    connect(ui->matchButton, &QPushButton::clicked, this, [this]() {
        stackedWidget->setCurrentWidget(matchView);
    });

    // Apply drop shadow effect to currentUserPhotoLabel
    QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect(this);
    shadow->setBlurRadius(10);
    shadow->setXOffset(0);
    shadow->setYOffset(4);
    shadow->setColor(QColor(0, 0, 0, 51)); // rgba(0, 0, 0, 0.2)
    ui->currentUserPhotoLabel->setGraphicsEffect(shadow);

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

EmployeeWindow::~EmployeeWindow()
{
    delete ui;
}

void EmployeeWindow::handleCoachButtonClicked()
{
    qDebug() << "Coach button clicked.";
    DisplayUser *displayUser = new DisplayUser("Coach", this);
    displayUser->setAttribute(Qt::WA_DeleteOnClose);
    displayUser->exec();
}

void EmployeeWindow::handleEmployeeButtonClicked()
{
    qDebug() << "Employee button clicked.";
    DisplayUser *displayUser = new DisplayUser("Employee", this);
    displayUser->setAttribute(Qt::WA_DeleteOnClose);
    displayUser->exec();
}

void EmployeeWindow::handleAddUserButtonClicked()
{
    qDebug() << "Add User button clicked.";
    AddUser *addUserDialog = new AddUser(this);
    addUserDialog->setModal(true);
    addUserDialog->exec();
    delete addUserDialog;
}

void EmployeeWindow::handleLogoutButtonClicked()
{
    qDebug() << "Logout button clicked.";

    // Clear the session to log out the user
    SessionManager::instance().clearSession();

    // Update the photo label to indicate no user
    ui->currentUserPhotoLabel->setText("No User");
    ui->dashboard_9->setText("User name");
    ui->dashboard_8->setText("Role");

    // Re-show the parent MainWindow if it exists
    if (mainWindowParent) {
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
        qDebug() << "No parent MainWindow found, creating a new one.";
        MainWindow *loginWindow = new MainWindow();
        loginWindow->show();
    }

    // Close the current EmployeeWindow
    this->close();
}

void EmployeeWindow::handleProfileButtonClicked()
{
    Profile *profileDialog = new Profile(this);
    profileDialog->setModal(true);
    profileDialog->exec();
    delete profileDialog;
}
