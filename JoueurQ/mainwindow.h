#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMap>
#include <QByteArray>
#include <QPixmap>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_button1_clicked();
    void on_toolButtonImage_clicked();
    void on_buttonDelete_clicked();
    void on_buttonModify_clicked();

private:
    Ui::MainWindow *ui;
    QMap<QString, int> teamMap;
    QByteArray img_joueur; // Variable pour stocker l'image du joueur

    void loadTeams();
    void loadPlayers();
    bool validateTableSelection();
};

#endif // MAINWINDOW_H