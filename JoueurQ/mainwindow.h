#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMap>
#include <QByteArray>
#include <QPixmap>
#include <QItemSelection>
#include <QFrame> 
#include <QComboBox> 
#include <QSqlQuery>  // Ajoutez cette ligne pour QSqlQuery
#include <QLabel>
#include <QGraphicsEffect>     // Ajouter cette ligne
#include <QPropertyAnimation>
 #include "qrcodegen.hpp"

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
    void onSearchTextChanged(const QString &text);
    void on_buttonViewDetails_clicked(); // Nouvelle méthode pour afficher les détails
    void onTableSelectionChanged(const QItemSelection &selected, const QItemSelection &deselected);
    void onSortingChanged(int index); 
    void refreshStatistics();
    void refreshBestPlayer(); 

private:
    Ui::MainWindow *ui;
    QMap<QString, int> teamMap;
    QByteArray img_joueur; // Variable pour stocker l'image du joueur
    int currentDisplayedPlayerId; // ID du joueur actuellement affiché dans les détails
    QComboBox *comboBoxCompetition;
    void loadTeams();
    void loadPlayers();
    bool validateTableSelection();
    void refreshPlayerDetails(); // Nouvelle méthode pour rafraîchir les détails
    void exportPlayerToPDF(int playerId);
    void setupStatisticsTab();
    void setupBestPlayerTab();
    void displayBestPlayer();
    // Add this to the private methods section
void updatePlayerInfo(QSqlQuery query, QLabel *nameLabel, QLabel *teamLabel, QLabel *statsLabel, QLabel *imageLabel);
    QFrame* createStatsCard(const QString &title, const QString &value, const QString &style);
    QPixmap generateQRCode(const QString &text);
    
};

#endif // MAINWINDOW_H