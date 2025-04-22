#ifndef WATCHMATCHDIALOG_H
#define WATCHMATCHDIALOG_H

#include <QDialog>
#include <QTimer>
#include "arduino.h"

class QLabel;

class WatchMatchDialog : public QDialog
{
    Q_OBJECT

public:
    WatchMatchDialog(int matchId, QWidget *parent = nullptr);
    ~WatchMatchDialog();

protected:
    void accept() override; // Override accept to handle Arduino cleanup

private slots:
    void readSensorData();

private:
    int matchId;
    Arduino *arduino;
    QTimer *sensorTimer;
    QLabel *sensorStatusLabel;
    bool rainDetected;
    bool noRainDetected;
};

#endif // WATCHMATCHDIALOG_H