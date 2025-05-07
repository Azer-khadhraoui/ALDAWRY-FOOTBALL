#ifndef PLAYERWINDOW_H
#define PLAYERWINDOW_H

#include <QMainWindow>
#include <QMap>
#include <QByteArray>
#include <QPixmap>
#include <QItemSelection>
#include <QFrame>
#include <QComboBox>
#include <QSqlQuery>
#include <QLabel>
#include <QGraphicsEffect>
#include <QPropertyAnimation>
#include <QJsonObject>
#include <QNetworkAccessManager>
#include "../userheaders/qrcodegen.hpp"
#include "formationpopup.h"
//add stackedwidget
#include <QStackedWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class playerwindow; }
QT_END_NAMESPACE

class playerwindow : public QMainWindow
{
    Q_OBJECT

public:
    // Accept QStackedWidget* for navigation
    explicit playerwindow(QStackedWidget *stackedWidget = nullptr, QWidget *parent = nullptr);
    ~playerwindow();

private slots:


    void on_buttonDelete_clicked();
    void on_buttonModify_clicked();
    void onSearchTextChanged(const QString &text);
    void on_buttonViewDetails_clicked();
    void onTableSelectionChanged(const QItemSelection &selected, const QItemSelection &deselected);
    void onSortingChanged(int index);
    void refreshStatistics();
    void refreshBestPlayer();
    void onGenerateReportClicked();
    void displayReport(const QString &reportText);
    void openAddPlayer();
    void updateCompetitionStats(const QString &competitionName);
    void on_userbutton_clicked();
    void handleLogoutButtonClicked();
    void on_aboutButton_clicked();

private:
    Ui::playerwindow *ui;
    QMap<QString, int> teamMap;
    int currentDisplayedPlayerId;
    QComboBox *comboBoxCompetition;
    void loadTeams();
    void loadPlayers();
    bool validateTableSelection();
    void refreshPlayerDetails();
    void exportPlayerToPDF(int playerId);
    void setupStatisticsTab();
    void setupBestPlayerTab();
    void displayBestPlayer();
    void updatePlayerInfo(QSqlQuery query, QLabel *nameLabel, QLabel *teamLabel, QLabel *statsLabel, QLabel *imageLabel);
    QFrame* createStatsCard(const QString &title, const QString &value, const QString &style);
    QPixmap generateQRCode(const QString &text);
    void setupTeamOfCompetitionTab();
   
void loadBestPlayersByPosition(const QString &competitionName);
    QFrame* createPositionWidget(const QString &position);
    void displayTeamOfCompetition(const QString &competitionName);
    void displayPlayerDetails(int playerId, const QString &position);
    bool eventFilter(QObject *obj, QEvent *event) override;
    QJsonObject collectPlayerData(int playerId);
    QString generateReport(const QJsonObject &data);
};

#endif // PLAYERWINDOW_H


