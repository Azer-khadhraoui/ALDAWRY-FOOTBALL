#ifndef RECOVERPASSWORD_H
#define RECOVERPASSWORD_H

#include <QDialog>
#include <QMap>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class RecoverPasswordDialog; }
QT_END_NAMESPACE

class RecoverPasswordDialog : public QDialog {
    Q_OBJECT

public:
    explicit RecoverPasswordDialog(QWidget *parent = nullptr);
    ~RecoverPasswordDialog();

private slots:
    void on_send_code_button_clicked();
    void on_verify_code_button_clicked();
    void on_reset_password_button_clicked();

private:
    Ui::RecoverPasswordDialog *ui;
    QMap<QString, QString> recoveryCodes; // email -> code
    QTimer *codeTimer;
    QString currentEmail;

    void sendRecoveryEmail(const QString &email, const QString &code);
};

#endif // RECOVERPASSWORD_H
