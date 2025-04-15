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
    void on_resetButton_clicked();
    void on_pushButton_clicked(); // For the AI button
    void on_pushButton_2_clicked(); // For the "Add Team" button
    void on_pushButton_3_clicked(); // For the "Chat" button
    void on_pushButton_4_clicked(); // Slot for pushButton_4
    void on_pushButton_5_clicked(); // Slot for pushButton_5
    void on_pushButton_6_clicked(); // Slot for pushButton_6
    void onPieSliceHovered(bool state); // Add this declaration

private:
    Ui::MainWindow *ui;
    QByteArray teamLogo;


    void setupBudgetPieChart();  // New method to set up the pie chart
    void updateBudgetPieChart(); // Method to update the pie chart

    QPieSeries *budgetSeries;  // Pie series for the chart
    QChartView *chartView;     // Chart view for the pie chart

    QMediaPlayer *mediaPlayer;  // Media player for the video
    QVideoWidget *videoWidget; // Video widget to display the video
};

#endif // MAINWINDOW_H
