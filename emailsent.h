#ifndef EMAILSENT_H
#define EMAILSENT_H

#include <QDialog>
#include <QMessageBox> // Include for QMessageBox

QT_BEGIN_NAMESPACE
namespace Ui { class EmailSentDialog; }
QT_END_NAMESPACE

class EmailSentDialog : public QDialog {
    Q_OBJECT

public:
    explicit EmailSentDialog(QWidget *parent = nullptr);
    ~EmailSentDialog();

    void disableCodeInput();

private slots:
    void on_verify_code_button_clicked();
    void on_pushButton_clicked(); // Resend email
    void on_pushButton_2_clicked(); // Change email address

private:
    Ui::EmailSentDialog *ui;
    bool isProcessing; // Flag to prevent multiple dialog openings

    void styleMessageBox(QMessageBox *msgBox); // Declare the method
};

#endif // EMAILSENT_H
