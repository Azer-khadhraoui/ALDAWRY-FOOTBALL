#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "connection.h"
#include <QSqlTableModel>
#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QValueAxis>
#include <QComboBox>

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
    void on_Confirm_clicked();
    void on_Delete_clicked();
    void on_Modify_clicked();
    void on_search_textChanged(const QString &text);
    void on_headerClicked(int logicalIndex);
    void on_pdf_clicked();
    void on_auto_match_clicked();
    void on_matchDoubleClicked(const QModelIndex &index);
    void updateMatchSummary();
    void updateRefereeAnalysis(); // Add this line
    void chart();
    void weatherImpactChart();
    void on_allmatchesContextMenuRequested(const QPoint &pos);
    void on_setLineupTriggered();
    void setupLineupWidget(int matchId, int teamId, const QString& lineup);
    void updateAvailablePlayers(); // New slot
    void on_showFullLineupTriggered();
    
private:
    Ui::MainWindow *ui;
    QSqlTableModel *matchModel;
    Connection dbConnection;
    void setupMatchTable();
    void filterMatches(const QString &text);
    void sortMatches();
    QVector<QPair<QComboBox*, QString>> positionBoxes; // Store the dynamic comboboxes and their positions
    

    bool ascendingOrder;

    void generateMatchDates(int competitionId, const QString &competitionType, const QDate &startDate, const QDate &endDate, int nbTeams);
    void updateGoalsBarChart(); // Add this line
    bool updating = false; // Moved to class scope
    // Player lists moved to class scope for access in updateAvailablePlayers
    QList<std::tuple<int, QString, int>> allGoalkeepers; // id, name, status
    QList<std::tuple<int, QString, int>> allDefenders;
    QList<std::tuple<int, QString, int>> allMidfielders;
    QList<std::tuple<int, QString, int>> allForwards;
};
class ChartWheelZoomHandler : public QObject
{
public:
    ChartWheelZoomHandler(QObject* parent = nullptr) : QObject(parent) {}
    
protected:
    bool eventFilter(QObject* obj, QEvent* event) override;
};

#endif // MAINWINDOW_H