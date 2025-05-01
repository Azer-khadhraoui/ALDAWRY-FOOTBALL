#ifndef RECOVERPASSWORD_H
#define RECOVERPASSWORD_H

#include <QDialog>
#include <QMap>
#include <QTimer>
#include <QMessageBox> // Include for QMessageBox

QT_BEGIN_NAMESPACE
namespace Ui { class RecoverPasswordDialog; }
QT_END_NAMESPACE

class RecoverPasswordDialog : public QDialog {
    Q_OBJECT

public:
    explicit RecoverPasswordDialog(QWidget *parent = nullptr);
    ~RecoverPasswordDialog();

    // Static methods to access shared data
    static QMap<QString, QString>& getRecoveryCodes() { return recoveryCodes; }
    static QTimer* getCodeTimer() { return codeTimer; }
    static QString getCurrentEmail() { return currentEmail; }
    static void setCurrentEmail(const QString &email) { currentEmail = email; }

    void resendRecoveryEmail(); // Public method for resending email

private slots:
    void on_send_code_button_clicked();
    void on_pushButton_clicked(); // Login button
    void onCodeTimerTimeout(); // Handle timer expiration
    void onEmailSendFinished(); // Handle email send response

private:
    Ui::RecoverPasswordDialog *ui;
    static QMap<QString, QString> recoveryCodes; // email -> code
    static QTimer *codeTimer;
    static QString currentEmail;

    void sendRecoveryEmail(const QString &email, const QString &code);
    void styleMessageBox(QMessageBox *msgBox); // Declare the method
};

#endif // RECOVERPASSWORD_H
