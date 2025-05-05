#ifndef DISPLAYTEAMWINDOW_H
#define DISPLAYTEAMWINDOW_H

#include <QMainWindow>
#include "team.h"

namespace Ui {
class DisplayTeamWindow;
}

class DisplayTeamWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit DisplayTeamWindow(Team* team, QWidget *parent = nullptr);
    ~DisplayTeamWindow();

private:
    Ui::DisplayTeamWindow *ui;
};

#endif // DISPLAYTEAMWINDOW_H
