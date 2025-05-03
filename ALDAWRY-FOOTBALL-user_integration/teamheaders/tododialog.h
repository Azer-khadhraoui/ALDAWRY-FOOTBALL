#ifndef TODODIALOG_H
#define TODODIALOG_H

#include <QDialog>
#include <QSqlQuery>
#include <QComboBox>
#include <QLineEdit>
#include <QDateTimeEdit>
#include <QPushButton>

namespace Ui {
class TodoDialog;
}

class TodoDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TodoDialog(QWidget *parent = nullptr);
    ~TodoDialog();

signals:
    void todoAdded(); // Signal to notify MainWindow to update any related UI

private slots:
    void on_saveButton_clicked();
    void on_cancelButton_clicked();

private:
    Ui::TodoDialog *ui;
    void populateTeamComboBox();
};

#endif // TODODIALOG_H
