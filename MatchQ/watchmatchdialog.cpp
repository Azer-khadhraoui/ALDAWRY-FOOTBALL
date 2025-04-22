#include "watchmatchdialog.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPixmap>
#include <QPushButton>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QDebug>
#include <QRegularExpression>
#include <QThread>
#include <QTime>

WatchMatchDialog::WatchMatchDialog(int matchId, QWidget *parent) 
    : QDialog(parent), matchId(matchId), arduino(new Arduino), sensorTimer(new QTimer(this)), rainDetected(false), noRainDetected(false) {
    setWindowTitle("Watch Match");
    setFixedSize(400, 350);
    setStyleSheet(
        "QDialog {"
        "    background-color: #2A2A3A;"
        "    color: #FFFFFF;"
        "    font-family: 'Segoe UI';"
        "    font-size: 12px;"
        "    border: 1px solid #4A4A5A;"
        "    border-radius: 8px;"
        "    padding: 15px;"
        "}"
        "QLabel {"
        "    color: #FFFFFF;"
        "    font-size: 14px;"
        "}"
        "QPushButton {"
        "    background-color: #4A90E2;"
        "    color: #FFFFFF;"
        "    border-radius: 5px;"
        "    padding: 8px;"
        "    font-size: 12px;"
        "}"
        "QPushButton:hover {"
        "    background-color: #357ABD;"
        "}"
    );

    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    // Fetch match details
    QSqlQuery query;
    query.prepare(
        "SELECT m.ID_TEAMA, m.ID_TEAMB, m.METEO, m.SCOREA, m.SCOREB, "
        "e1.TEAM_NAME AS TEAM1_NAME, e2.TEAM_NAME AS TEAM2_NAME, "
        "e1.TEAM_LOGO AS TEAM1_LOGO, e2.TEAM_LOGO AS TEAM2_LOGO "
        "FROM HOTSTUFF.MATCH m "
        "JOIN HOTSTUFF.EQUIPE e1 ON m.ID_TEAMA = e1.ID_TEAM "
        "JOIN HOTSTUFF.EQUIPE e2 ON m.ID_TEAMB = e2.ID_TEAM "
        "WHERE m.ID_MATCH = :matchId"
    );
    query.bindValue(":matchId", matchId);

    if (!query.exec() || !query.next()) {
        QString errorMsg = "Failed to load match details: " + query.lastError().text();
        qDebug() << "SQL Error:" << errorMsg << "\nQuery:" << query.lastQuery();
        QMessageBox::critical(this, "Error", errorMsg);
        close();
        return;
    }

    QString team1Name = query.value("TEAM1_NAME").toString();
    QString team2Name = query.value("TEAM2_NAME").toString();
    int weatherCode = query.value("METEO").toInt();
    QString weather;
    switch (weatherCode) {
        case 0: weather = "Sunny"; break;
        case 1: weather = "Rainy"; break;
        case 2: weather = "Cloudy"; break;
        case 3: weather = "Snowy"; break;
        default: weather = "Unknown"; break;
    }
    int score1 = query.value("SCOREA").toInt();
    int score2 = query.value("SCOREB").toInt();
    QByteArray logo1Data = query.value("TEAM1_LOGO").toByteArray();
    QByteArray logo2Data = query.value("TEAM2_LOGO").toByteArray();

    // Teams layout
    QHBoxLayout *teamsLayout = new QHBoxLayout();
    QLabel *team1Logo = new QLabel();
    QPixmap pixmap1;
    if (!logo1Data.isEmpty() && pixmap1.loadFromData(logo1Data)) {
        team1Logo->setPixmap(pixmap1.scaled(50, 50, Qt::KeepAspectRatio));
    } else {
        team1Logo->setText("No Logo");
    }
    QLabel *team1Label = new QLabel(team1Name);
    QLabel *vsLabel = new QLabel("vs");
    vsLabel->setStyleSheet("font-weight: bold; font-size: 16px;");
    QLabel *team2Logo = new QLabel();
    QPixmap pixmap2;
    if (!logo2Data.isEmpty() && pixmap2.loadFromData(logo2Data)) {
        team2Logo->setPixmap(pixmap2.scaled(50, 50, Qt::KeepAspectRatio));
    } else {
        team2Logo->setText("No Logo");
    }
    QLabel *team2Label = new QLabel(team2Name);

    teamsLayout->addWidget(team1Logo);
    teamsLayout->addWidget(team1Label);
    teamsLayout->addWidget(vsLabel);
    teamsLayout->addWidget(team2Label);
    teamsLayout->addWidget(team2Logo);

    // Score
    QLabel *scoreLabel = new QLabel(QString("Score: %1 - %2").arg(score1).arg(score2));

    // Weather
    QLabel *weatherLabel = new QLabel("Weather: " + weather);
    weatherLabel->setObjectName("weatherLabel");

    // Sensor Status
    sensorStatusLabel = new QLabel("Sensor: Connecting to Arduino...");
    sensorStatusLabel->setStyleSheet("color: #FFD700;");

    // Add to main layout
    mainLayout->addLayout(teamsLayout);
    mainLayout->addWidget(scoreLabel);
    mainLayout->addWidget(weatherLabel);
    mainLayout->addWidget(sensorStatusLabel);
    mainLayout->addStretch();

    // OK button
    QPushButton *okButton = new QPushButton("OK");
    connect(okButton, &QPushButton::clicked, this, &QDialog::accept);
    mainLayout->addWidget(okButton);

    // Initialize Arduino
    if (arduino->connect_arduino() == 0) {
        qDebug() << "Arduino connected successfully on port:" << arduino->getArduino_port_name();
        // Send servo command based on METEO
        QString servoCommand = (weatherCode == 1) ? "SERVO:1\n" : "SERVO:0\n";
        arduino->write_to_arduino(servoCommand.toUtf8());
        qDebug() << "Initial servo command sent:" << servoCommand.trimmed();
        QThread::msleep(100);  // Delay to ensure Arduino processes command

        sensorTimer->start(1000);
        connect(sensorTimer, &QTimer::timeout, this, &WatchMatchDialog::readSensorData);
    } else {
        sensorStatusLabel->setText("Sensor: Arduino not connected");
        sensorStatusLabel->setStyleSheet("color: #FF4500;");
        qDebug() << "Failed to connect to Arduino";
    }
}

WatchMatchDialog::~WatchMatchDialog() {
    disconnect(sensorTimer, &QTimer::timeout, this, &WatchMatchDialog::readSensorData);
    sensorTimer->stop();
    arduino->close_arduino();
    delete arduino;
    QThread::msleep(1000); // Ensure port is fully released
}

void WatchMatchDialog::accept() {
    // Stop the sensor timer and disconnect its signal
    disconnect(sensorTimer, &QTimer::timeout, this, &WatchMatchDialog::readSensorData);
    sensorTimer->stop();
    
    // Send servo off command before closing
    arduino->write_to_arduino("SERVO:0\n");
    qDebug() << "Sent to Arduino: SERVO:0 (on close)";
    QThread::msleep(100);  // Delay to ensure command is processed
    
    // Close the Arduino connection
    arduino->close_arduino();
    QThread::msleep(1000); // Ensure port is fully released
    
    // Call the base class accept to close the dialog
    QDialog::accept();
}

void WatchMatchDialog::readSensorData() {
    QByteArray data = arduino->read_from_arduino();
    qDebug() << "Raw data from Arduino:" << data << "at time:" << QTime::currentTime().toString();
    if (data.isEmpty()) {
        sensorStatusLabel->setText("Sensor: Waiting for data...");
        sensorStatusLabel->setStyleSheet("color: #FFD700;");
        qDebug() << "No data available from Arduino";
        return;
    }

    // Parse sensor value (expecting "Value: <number>")
    QString dataStr = QString::fromUtf8(data).trimmed();
    qDebug() << "Parsed data string:" << dataStr;
    QRegularExpression rx("Value\\s*:\\s*(\\d+)");
    QRegularExpressionMatch match = rx.match(dataStr);
    if (match.hasMatch()) {
        bool ok;
        int value = match.captured(1).toInt(&ok);
        if (ok && value >= 0 && value <= 1023) {
            qDebug() << "Valid sensor value:" << value;
            if (value < 300) {
                sensorStatusLabel->setText("Sensor: Rain Detected");
                sensorStatusLabel->setStyleSheet("color: #00FF00;");
                if (!rainDetected) {
                    QSqlQuery updateQuery;
                    updateQuery.prepare(
                        "UPDATE HOTSTUFF.MATCH "
                        "SET METEO = 1 "
                        "WHERE ID_MATCH = :matchId"
                    );
                    updateQuery.bindValue(":matchId", matchId);
                    if (!updateQuery.exec()) {
                        qDebug() << "Failed to update METEO to 1:" << updateQuery.lastError().text();
                        QMessageBox::warning(this, "Error", "Failed to update weather: " + updateQuery.lastError().text());
                    } else {
                        rainDetected = true;
                        noRainDetected = false;
                        QLabel *weatherLabel = findChild<QLabel*>("weatherLabel");
                        if (weatherLabel) {
                            weatherLabel->setText("Weather: Rainy");
                        }
                        // Turn on servo for rainy
                        arduino->write_to_arduino("SERVO:1\n");
                        qDebug() << "Sent to Arduino: SERVO:1 (rain detected)";
                        QThread::msleep(100);  // Delay to ensure command is processed
                    }
                }
            } else {
                sensorStatusLabel->setText("Sensor: No Rain");
                sensorStatusLabel->setStyleSheet("color: #FFFFFF;");
                if (!noRainDetected) {
                    QSqlQuery updateQuery;
                    updateQuery.prepare(
                        "UPDATE HOTSTUFF.MATCH "
                        "SET METEO = 0 "
                        "WHERE ID_MATCH = :matchId"
                    );
                    updateQuery.bindValue(":matchId", matchId);
                    if (!updateQuery.exec()) {
                        qDebug() << "Failed to update METEO to 0:" << updateQuery.lastError().text();
                        QMessageBox::warning(this, "Error", "Failed to update weather: " + updateQuery.lastError().text());
                    } else {
                        noRainDetected = true;
                        rainDetected = false;
                        QLabel *weatherLabel = findChild<QLabel*>("weatherLabel");
                        if (weatherLabel) {
                            weatherLabel->setText("Weather: Sunny");
                        }
                        // Turn off servo for non-rainy
                        arduino->write_to_arduino("SERVO:0\n");
                        qDebug() << "Sent to Arduino: SERVO:0 (no rain)";
                        QThread::msleep(100);  // Delay to ensure command is processed
                    }
                }
            }
        } else {
            qDebug() << "Invalid sensor value or parsing error";
        }
    } else {
        qDebug() << "Data format mismatch, expected 'Value: <number>'";
    }
}