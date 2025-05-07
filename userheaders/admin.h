#ifndef ADMIN_H
#define ADMIN_H

#include <QMainWindow>
#include <QStackedWidget>
#include "../teamheaders/teamwindow.h"
#include "../playerheaders/playerwindow.h"
#include "stats.h"
#include "../matchheaders/matchview.h"

class MainWindow; // Forward declaration

namespace Ui {
class AdminWindow;
}

class AdminWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit AdminWindow(MainWindow *mainWindowParent = nullptr, QWidget *parent = nullptr);
    ~AdminWindow();

private slots:
    void handleAdminButtonClicked();
    void handleCoachButtonClicked();
    void handleEmployeeButtonClicked();
    void handleLogoutButtonClicked();
    void handleAddUserButtonClicked(); // Slot for add_user button
    void handleProfileButtonClicked();
    void on_aboutButton_clicked(); // Slot for about button

private:
    Ui::AdminWindow *ui;
    MainWindow *mainWindowParent; // Pointer to the parent MainWindow (login window)
    Stats *stats;
    QStackedWidget *stackedWidget;
    teamwindow *teamWindow;
    playerwindow *playerWindow; // Add playerwindow pointer
    QWidget *adminDashboard;
    matchview *matchView; // Add matchview pointer
};

#endif // ADMIN_H
