#ifndef CHARTMATCH_H
#define CHARTMATCH_H

#include <QDialog>
#include <QByteArray>
#include <Qwidget>


namespace Ui {
class chartMatch;
}

class chartMatch : public QDialog
{
    Q_OBJECT
public:
    explicit chartMatch(QWidget *parent = nullptr);
    ~chartMatch();
private slots:
    void chart();
private:
    Ui::chartMatch *ui;
};

class ChartWheelZoomHandler_chart : public QObject
{
public:
    ChartWheelZoomHandler_chart(QObject* parent = nullptr) : QObject(parent) {}
};

#endif // CHARTMATCH_H
