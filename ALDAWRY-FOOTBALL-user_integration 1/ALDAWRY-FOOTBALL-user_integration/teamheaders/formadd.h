#ifndef FORMADD_H
#define FORMADD_H

#include <QDialog>
#include <QByteArray>

namespace Ui {
class FormAdd;
}

class FormAdd : public QDialog
{
    Q_OBJECT

public:
    explicit FormAdd(QWidget *parent = nullptr);
    ~FormAdd();

signals:
    void teamAdded(); // Signal to notify MainWindow when a team is added

private slots:
    void on_toolButton_clicked(); // Slot for the tool button
    void on_button1_clicked();    // Slot for the confirm button
    void on_resetButton_clicked(); // Slot for the reset button

private:
    Ui::FormAdd *ui;
    QByteArray teamLogo; // Store the team logo
};

#endif // FORMADD_H
