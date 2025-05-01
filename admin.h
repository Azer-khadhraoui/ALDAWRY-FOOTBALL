#ifndef ADMIN_H
#define ADMIN_H

#include <QMainWindow>
#include "stats.h"

class MainWindow; // Forward declaration

namespace Ui {
class MainWindow;
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
    void handleProfileButtonClicked() ;

private:
    Ui::MainWindow *ui;
    MainWindow *mainWindowParent; // Pointer to the parent MainWindow (login window)
    Stats *stats;
};

#endif // ADMIN_H
