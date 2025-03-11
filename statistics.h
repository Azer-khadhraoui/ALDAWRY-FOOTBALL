#ifndef STATISTICS_H
#define STATISTICS_H
#include <QDialog>
#include <QtCharts/QChart>      
#include <QtCharts/QChartView>
namespace Ui {
class statistics;
}

class statistics : public QDialog
{
    Q_OBJECT
public:
    explicit statistics(QWidget *parent = nullptr);
    ~statistics();

private slots:
    void on_exportButton_clicked();

private:
    Ui::statistics *ui;
    QChart *chart;
};

#endif // STATISTICS_H
