#ifndef MODIFYUSER_H
#define MODIFYUSER_H

#include <QDialog>
#include "ui_modifyUser.h"
#include "user.h"
#include <QByteArray>

class ModifyUser : public QDialog {
    Q_OBJECT

public:
    explicit ModifyUser(int userId, QWidget *parent = nullptr);
    ~ModifyUser();

private slots:
    void on_pushButton_2_clicked(); // Confirm button
    void on_modifyUploadPhotoButton_clicked(); // Upload photo button

private:
    void loadUserData();
    bool validateInputs();
    bool checkUniqueFields(const QString& email, const QString& mobileNumber);
    bool validateStrongPassword(const QString& password);

    Ui::Form *ui;
    int userId;
    QByteArray photoData;
    Employee *employee;
};

#endif // MODIFYUSER_H
