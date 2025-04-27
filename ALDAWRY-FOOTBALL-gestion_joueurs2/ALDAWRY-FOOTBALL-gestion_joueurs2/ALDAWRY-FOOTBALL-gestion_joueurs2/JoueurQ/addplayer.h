#ifndef ADDPLAYER_H
#define ADDPLAYER_H

#include <QDialog>
#include <QMap>
#include <QByteArray>
#include "joueur.h"

namespace Ui {
class addPlayer;  // Doit correspondre au nom du fichier .ui (addPlayer.ui)
}

class AddPlayer : public QDialog
{
    Q_OBJECT

public:
    explicit AddPlayer(QWidget *parent = nullptr);
    ~AddPlayer();

private slots:
    void on_addButton_clicked();
    void on_toolButtonImage_clicked();

private:
    Ui::addPlayer *ui;  // Doit correspondre au namespace Ui::addPlayer
    QMap<QString, int> teamMap;
    QByteArray img_joueur;
    void loadTeams();
    bool validateInput();
};

#endif // ADDPLAYER_H
