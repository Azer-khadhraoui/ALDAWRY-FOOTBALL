#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "user.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_sign_in_clicked();
    void on_sign_in_2_clicked();
    void on_togglePasswordButton_clicked();

private:
    Ui::MainWindow *ui;
    int currentEmployeeId;
    QString currentEmployeeRole;
    bool isPasswordVisible = false;
};

#endif // MAINWINDOW_H
