#ifndef MAINWINDOW_H
#define MAINWINDOW_H

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

private:
    Ui::MainWindow *ui;
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
    QFrame* createPositionWidget(const QString &position);
    void displayTeamOfCompetition(const QString &competitionName);
    void displayPlayerDetails(int playerId, const QString &position);
    bool eventFilter(QObject *obj, QEvent *event) override;
    QJsonObject collectPlayerData(int playerId);
    QString generateReport(const QJsonObject &data);
};

#endif // MAINWINDOW_H
