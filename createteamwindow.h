#ifndef CREATETEAMWINDOW_H
#define CREATETEAMWINDOW_H

#include <QMainWindow>
#include "team.h"

namespace Ui {
class CreateTeamWindow;
}

class CreateTeamWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit CreateTeamWindow(QWidget *parent = nullptr);
    ~CreateTeamWindow();

private slots:
    void on_createButton_clicked();

private:
    Ui::CreateTeamWindow *ui;
};

#endif // CREATETEAMWINDOW_H
