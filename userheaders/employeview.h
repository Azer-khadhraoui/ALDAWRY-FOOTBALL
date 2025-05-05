#ifndef EMPLOYEVIEW_H
#define EMPLOYEVIEW_H

#include <QMainWindow>
#include "stats.h"

class MainWindow; // Forward declaration

namespace Ui {
class EmployeeWindow; // Changed from EmployeeView to EmployeeWindow to match employeview.ui
}

class EmployeeWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit EmployeeWindow(MainWindow *mainWindowParent = nullptr, QWidget *parent = nullptr);
    ~EmployeeWindow();

private slots:
    void handleCoachButtonClicked();
    void handleEmployeeButtonClicked();
    void handleLogoutButtonClicked();
    void handleAddUserButtonClicked();
    void handleProfileButtonClicked();

private:
    Ui::EmployeeWindow *ui; // Changed from EmployeeView to EmployeeWindow
    MainWindow *mainWindowParent;
    Stats *stats;
};

#endif // EMPLOYEVIEW_H
