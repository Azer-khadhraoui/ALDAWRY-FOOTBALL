#ifndef NEWPASSWORD_H
#define NEWPASSWORD_H

#include <QDialog>
#include <QMessageBox> // Include for QMessageBox

QT_BEGIN_NAMESPACE
namespace Ui { class NewPasswordDialog; }
QT_END_NAMESPACE

class NewPasswordDialog : public QDialog {
    Q_OBJECT

public:
    explicit NewPasswordDialog(QWidget *parent = nullptr);
    ~NewPasswordDialog();

private slots:
    void on_reset_password_button_clicked();
    void on_pushButton_clicked(); // Login button

private:
    Ui::NewPasswordDialog *ui;

    void styleMessageBox(QMessageBox *msgBox); // Declare the method for styling notifications
};

#endif // NEWPASSWORD_H
