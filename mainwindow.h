#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QByteArray>
#include <QTableWidgetItem>
#include "team.h"
#include "modifyTeam.h"
#include <QtCharts/QChartView>      // Add for chart view
#include <QtCharts/QPieSeries>      // Add for pie series
#include <QMediaPlayer>
#include <QVideoWidget>
#include "chatdialog.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_toolButton_clicked();
    void on_addButtonclicked();
    void on_deleteButton_clicked();
    void on_resetButton_clicked();
    void on_searchBar_textChanged(const QString &text);
    void on_tableWidget_sectionClicked(int logicalIndex);
    void on_modifyButton_clicked();
    void on_downloadButton_clicked();
    void on_deleteButton_2_clicked();
    void onPieSliceHovered(bool state);
    void on_pushButton_clicked(); // Add this for the AI button

private:
    Ui::MainWindow *ui;
    QByteArray teamLogo;

    void loadTeams();
    void setupBudgetPieChart();  // New method to set up the pie chart
    void updateBudgetPieChart(); // Method to update the pie chart

    QPieSeries *budgetSeries;  // Pie series for the chart
    QChartView *chartView;     // Chart view for the pie chart

    QMediaPlayer *mediaPlayer;  // Media player for the video
    QVideoWidget *videoWidget; // Video widget to display the video
};

#endif // MAINWINDOW_H
