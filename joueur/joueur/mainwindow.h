#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QComboBox>
#include <QMap>

namespace Ui { class MainWindow; }

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_button1_clicked();
    void loadTeams(); // Méthode pour charger les équipes

private:
    Ui::MainWindow *ui;
    QMap<QString, int> teamMap; // Stocke les noms d'équipes et leurs IDs
};

#endif // MAINWINDOW_H