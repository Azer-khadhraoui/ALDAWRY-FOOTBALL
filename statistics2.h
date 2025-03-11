#ifndef STATISTICS2_H
#define STATISTICS2_H
#include <QDialog>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>

namespace Ui {
class statistics2;
}

class statistics2 : public QDialog
{
    Q_OBJECT
public:
    explicit statistics2(QWidget *parent = nullptr);
    ~statistics2();

private slots:
    void on_exportButton_clicked();

    void on_previousButton_clicked();

    void on_nextButton_clicked();

private:
    Ui::statistics2 *ui;
    QChart *chart;
};

#endif // STATISTICS2_H
