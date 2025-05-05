#ifndef ADDUSER_H
#define ADDUSER_H

#include <QDialog>
#include "user.h"

namespace Ui {
class AddUser;
}

class AddUser : public QDialog {
    Q_OBJECT

public:
    explicit AddUser(QWidget *parent = nullptr);
    ~AddUser();

private slots:
    void on_button1_clicked();
    void on_uploadPhotoButton_clicked();

private:
    Ui::AddUser *ui;
    QByteArray newEmployeePhoto; // Store the photo for the new employee
    bool isProcessing; // Flag to prevent multiple clicks
    bool checkUniqueFields(const QString& email, const QString& mobileNumber);
    bool validateStrongPassword(const QString& password);
};

#endif // ADDUSER_H
