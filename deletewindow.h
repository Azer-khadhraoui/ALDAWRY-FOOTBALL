#ifndef DELETEWINDOW_H
#define DELETEWINDOW_H

#include <QDialog>

namespace Ui {
class deletewindow;
}

class deletewindow : public QDialog
{
    Q_OBJECT

public:
    explicit deletewindow(QWidget *parent = nullptr, int id=-1);
    ~deletewindow();

private slots:
    void on_deleteButton_clicked();

    void on_pushButton_clicked();

private:
    Ui::deletewindow *ui;
    int m_id;
};

#endif // DELETEWINDOW_H
