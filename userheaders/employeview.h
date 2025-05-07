#ifndef EMPLOYEVIEW_H
#define EMPLOYEVIEW_H

#include <QMainWindow>
#include <QStackedWidget>
#include "../teamheaders/teamwindow.h"
#include "stats.h"
#include "../playerheaders/playerwindow.h"
#include "../matchheaders/matchview.h"
#include "../compheaders/competitionview.h"

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
    void on_aboutButton_clicked();
private:
    Ui::EmployeeWindow *ui; // Changed from EmployeeView to EmployeeWindow
    MainWindow *mainWindowParent;
    Stats *stats;
    QStackedWidget *stackedWidget;
    teamwindow *teamWindow;
    playerwindow *playerWindow; // Add playerwindow pointer
    QWidget *employee;
    matchview *matchView; // Add matchview pointer
};

#endif // EMPLOYEVIEW_H
