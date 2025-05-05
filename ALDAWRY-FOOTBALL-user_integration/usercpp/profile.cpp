#include "../userheaders/profile.h"
#include "ui_profile.h"
#include "../userheaders/sessionmanager.h"
#include <QDebug>

Profile::Profile(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Profile)
{
    ui->setupUi(this);
    setWindowTitle("User Profile");
    loadUserProfile();
}

Profile::~Profile()
{
    delete ui;
}

void Profile::loadUserProfile()
{
    const Employee& currentUser = SessionManager::instance().getCurrentUser();

    // Set employee details
    ui->firstNameValue->setText(currentUser.getFirstName());
    ui->lastNameValue->setText(currentUser.getLastName());
    ui->emailValue->setText(currentUser.getEmail());
    ui->mobileValue->setText(currentUser.getMobileNumber());
    ui->dobValue->setText(currentUser.getDateOfBirth().toString("yyyy-MM-dd"));
    ui->roleValue->setText(currentUser.getRole());

    // Check if a photo exists

}

void Profile::on_closeButton_clicked()
{
    this->close();
}
