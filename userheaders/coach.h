#ifndef COACH_H
#define COACH_H

#include <QMainWindow>
#include "ui_coach.h" // Include the generated UI header file
#include "../userheaders/mainwindow.h" // Ensure MainWindow is included

QT_BEGIN_NAMESPACE
namespace Ui {
class CoachWindow; // Changed from CoachWindow to MainWindow
}
QT_END_NAMESPACE

class CoachWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit CoachWindow(QWidget *parent = nullptr);
    ~CoachWindow();
    void on_viewplayer_clicked(); // Slot for the view players button
    void logout(); // Slot for the logout button
    void on_MatchesButton_clicked(); // Slot for the match button

private:
    Ui::CoachWindow *ui; // Changed from Ui::CoachWindow to Ui::MainWindow
    MainWindow *mainWindowParent; // Add mainWindowParent member variable
};
#endif // COACH_H