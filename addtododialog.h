#ifndef ADDTODODIALOG_H
#define ADDTODODIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QDateTimeEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>

class AddTodoDialog : public QDialog {
    Q_OBJECT

public:
    explicit AddTodoDialog(QWidget *parent = nullptr);
    QString getTask() const;
    QDateTime getDate() const;

private:
    QLineEdit *taskEdit;
    QDateTimeEdit *dateEdit;
    QPushButton *saveButton;
    QPushButton *cancelButton;
};

#endif // ADDTODODIALOG_H
