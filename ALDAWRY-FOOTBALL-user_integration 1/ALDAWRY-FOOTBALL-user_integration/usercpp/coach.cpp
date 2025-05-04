#include "../userheaders/coach.h"
#include "ui_coach.h"
#include "../userheaders/displayplayers_coach.h"
#include <QDebug>
#include "../userheaders/sessionmanager.h"
#include "../userheaders/mainwindow.h"
#include <QLineEdit> // Include QLineEdit header

CoachWindow::CoachWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::CoachWindow)
    , mainWindowParent(qobject_cast<MainWindow*>(parent)) // Initialize mainWindowParent
{
    ui->setupUi(this);
    connect(ui->Viewplayers, &QPushButton::clicked, this, &CoachWindow::on_viewplayer_clicked);
    connect(ui->logout, &QPushButton::clicked, this, &CoachWindow::logout); // Connect logout button to close the window

    
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

    // Close the current CoachWindow
    this->close();
}
