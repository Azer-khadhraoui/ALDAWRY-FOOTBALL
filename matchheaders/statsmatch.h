#ifndef STATSMATCH_H
#define STATSMATCH_H

#include <QDialog>
#include <QByteArray>

namespace Ui {
class statsMatch;
}

class statsMatch : public QDialog
{
    Q_OBJECT
public:
    explicit statsMatch(QWidget *parent = nullptr);
    ~statsMatch();
private slots:
    void updateMatchSummary();
    void updateRefereeAnalysis();
    void weatherImpactChart();
private:
    Ui::statsMatch *ui;
};
class ChartWheelZoomHandler : public QObject
{
public:
    ChartWheelZoomHandler(QObject* parent = nullptr) : QObject(parent) {}
    
protected:
    bool eventFilter(QObject* obj, QEvent* event) override;
};
#endif // STATSMATCH_H
