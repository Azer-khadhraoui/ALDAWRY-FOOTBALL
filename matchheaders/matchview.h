#ifndef MATCHVIEW_H
#define MATCHVIEW_H

#include <QMainWindow>
#include "../userheaders/connection.h"
#include <QSqlTableModel>
#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QValueAxis>
#include <QComboBox>
#include "ui_matchview.h"
#include <QStackedWidget>


QT_BEGIN_NAMESPACE
namespace Ui { class matchview; }
QT_END_NAMESPACE

class matchview : public QMainWindow
{
    Q_OBJECT

public:
    matchview(QStackedWidget *stackedWidget = nullptr, QWidget *parent = nullptr);
    ~matchview();
    

private slots:
    // new slots for the new design
    void on_addmatch_clicked();
    void on_displaymatch_clicked();
    void on_statsbutton_clicked();
    void on_chartbutton_clicked();
    void on_viewallmatches_clicked();
    void showSoonestMatchDetails();
    void on_watchmatch_clicked();
    void on_userbutton_clicked();
    void on_playerButton_clicked();
    void on_compButton_clicked();
    void on_teamButton_clicked();
    void on_logout_clicked();


private:
    Ui::matchview *ui;
    QSqlTableModel *matchModel;
    Connection dbConnection;
    QTimer *statusUpdateTimer;
    QStackedWidget *m_stackedWidget = nullptr;
    

    bool ascendingOrder;
};


#endif // MATCHVIEW_H
