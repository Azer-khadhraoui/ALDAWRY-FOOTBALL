#include "watchmatchdialog.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPixmap>
#include <QPushButton>
#include <QTextEdit>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QDebug>
#include <QRegularExpression>
#include <QThread>
#include <QTime>
#include <QDateTime>
#include <QScrollBar>
#include <QPropertyAnimation>

WatchMatchDialog::WatchMatchDialog(int matchId, QWidget *parent) 
    : QDialog(parent), 
      matchId(matchId), 
      weatherArduino(new Arduino(Arduino::WeatherArduino)), 
      goalArduino(new Arduino(Arduino::GoalArduino)), 
      sensorTimer(new QTimer(this)), 
      goalTimer(new QTimer(this)), 
      timeTimer(new QTimer(this)), 
      commentaryTimer(new QTimer(this)), 
      rainTimer(new QTimer(this)), 
      sunTimer(new QTimer(this)), 
      scoreAnimation(nullptr), 
      rainDetected(false), 
      noRainDetected(false), 
      isHalfTime(false) {
    setWindowTitle("Live Match");
    setFixedSize(700, 800);
    setStyleSheet(
        "QDialog {"
        "    background-color: #1C2526;"
        "    color: #FFFFFF;"
        "    font-family: 'Roboto Condensed', 'Arial', sans-serif;"
        "    font-size: 14px;"
        "    border: 1px solid #FFFFFF;"
        "    border-radius: 10px;"
        "    padding: 15px;"
        "}"
        "QLabel {"
        "    color: #FFFFFF;"
        "    background-color: transparent;"
        "}"
        "QPushButton {"
        "    background-color: transparent;"
        "    color: #FFFFFF;"
        "    seta 2px solid #FF0000;"
        "    border-radius: 8px;"
        "    padding: 10px;"
        "    font-size: 16px;"
        "    font-weight: bold;"
        "}"
        "QPushButton:hover {"
        "    background-color: #FF0000;"
        "}"
        "QTextEdit {"
        "    background-color: transparent;"
        "    color: #FFFFFF;"
        "    border: none;"
        "    padding: 10px;"
        "    font-size: 14px;"
        "}"
    );

    sunWidget = new SunWidget(this);
    sunWidget->setFixedSize(700, 800);
    sunWidget->lower();
    sunWidget->hide();
    connect(sunTimer, &QTimer::timeout, sunWidget, &SunWidget::updateSunAndClouds);

    rainWidget = new RainWidget(this);
    rainWidget->setFixedSize(700, 800);
    rainWidget->lower();
    rainWidget->hide();
    connect(rainTimer, &QTimer::timeout, rainWidget, &RainWidget::updateRaindrops);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setSpacing(10);

    QSqlQuery query;
    query.prepare(
        "SELECT m.ID_TEAMA, m.ID_TEAMB, m.METEO, m.SCOREA, m.SCOREB, m.MATCH_DATETIME, "
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

    teamAId = query.value("ID_TEAMA").toInt();
    QString team1Name = query.value("TEAM1_NAME").toString();
    QString team2Name = query.value("TEAM2_NAME").toString();
    int weatherCode = query.value("METEO").toInt();
    QString weather;
    QString weatherIcon;
    switch (weatherCode) {
        case 0: weather = "Sunny"; weatherIcon = "🟡 "; break;
        case 1: weather = "Rainy"; weatherIcon = "🌧️ "; break;
        case 2: weather = "Cloudy"; weatherIcon = "☁️ "; break;
        case 3: weather = "Snowy"; weatherIcon = "❄️ "; break;
        default: weather = "Unknown"; weatherIcon = "❓ "; break;
    }
    int score1 = query.value("SCOREA").toInt();
    int score2 = query.value("SCOREB").toInt();
    matchStartTime = query.value("MATCH_DATETIME").toDateTime();
    QByteArray logo1Data = query.value("TEAM1_LOGO").toByteArray();
    QByteArray logo2Data = query.value("TEAM2_LOGO").toByteArray();

    updateBackground(weatherCode);

    QLabel *dateLabel = new QLabel(matchStartTime.toString("dd.MM.yyyy HH:mm"));
    dateLabel->setStyleSheet(
        "font-size: 16px; color: #B0BEC5; font-weight: bold;"
        "text-shadow: 1px 1px 2px #000000;"
    );
    mainLayout->addWidget(dateLabel, 0, Qt::AlignCenter);

    matchTimeLabel = new QLabel("0:00");
    matchTimeLabel->setStyleSheet(
        "font-size: 24px; font-weight: bold; color: #FFFFFF;"
        "background-color: #FF0000; padding: 5px 10px; border-radius: 5px;"
        "text-shadow: 1px 1px 2px #000000;"
    );
    mainLayout->addWidget(matchTimeLabel, 0, Qt::AlignCenter);
    timeTimer->start(1000);
    connect(timeTimer, &QTimer::timeout, this, &WatchMatchDialog::updateMatchTime);

    QVBoxLayout *scoreboardLayout = new QVBoxLayout();
    scoreboardLayout->setSpacing(5);

    halfTimeLabel = new QLabel("HALF TIME");
    halfTimeLabel->setStyleSheet(
        "font-size: 18px; font-weight: bold; color: #FF0000;"
        "padding: 5px;"
        "text-shadow: 1px 1px 2px #000000;"
    );
    halfTimeLabel->setVisible(false);
    scoreboardLayout->addWidget(halfTimeLabel, 0, Qt::AlignCenter);

    QHBoxLayout *teamsLayout = new QHBoxLayout();
    teamsLayout->setSpacing(20);

    QVBoxLayout *team1Layout = new QVBoxLayout();
    QLabel *team1Logo = new QLabel();
    QPixmap pixmap1;
    if (!logo1Data.isEmpty() && pixmap1.loadFromData(logo1Data)) {
        team1Logo->setPixmap(pixmap1.scaled(120, 120, Qt::KeepAspectRatio));
        team1Logo->setStyleSheet(
            "background-color: transparent;"
            "box-shadow: 2px 2px 5px rgba(0,0,0,0.5);"
        );
    } else {
        team1Logo->setText("No Logo");
        team1Logo->setStyleSheet(
            "font-size: 18px; color: #FFFFFF;"
            "background-color: transparent;"
        );
    }
    team1Label = new QLabel(team1Name); // Store Team A name
    team1Label->setStyleSheet(
        "font-size: 22px; font-weight: bold;"
        "background-color: transparent;"
        "text-shadow: 1px 1px 2px #000000;"
    );
    team1Layout->addWidget(team1Logo, 0, Qt::AlignCenter);
    team1Layout->addWidget(team1Label, 0, Qt::AlignCenter);

    QVBoxLayout *scoreLayout = new QVBoxLayout();
    QLabel *scoreLabel = new QLabel(QString("%1 - %2").arg(score1).arg(score2));
    scoreLabel->setObjectName("scoreLabel");
    scoreLabel->setStyleSheet(
        "font-size: 48px; font-weight: bold; color: #FF0000;"
        "background-color: transparent;"
        "text-shadow: 2px 2px 4px #000000;"
    );
    scoreAnimation = new QPropertyAnimation(scoreLabel, "opacity");
    scoreAnimation->setDuration(1000);
    scoreAnimation->setStartValue(0.3);
    scoreAnimation->setEndValue(1.0);
    scoreAnimation->start();
    scoreLayout->addWidget(scoreLabel, 0, Qt::AlignCenter);

    QVBoxLayout *team2Layout = new QVBoxLayout();
    QLabel *team2Logo = new QLabel();
    QPixmap pixmap2;
    if (!logo2Data.isEmpty() && pixmap2.loadFromData(logo2Data)) {
        team2Logo->setPixmap(pixmap2.scaled(120, 120, Qt::KeepAspectRatio));
        team2Logo->setStyleSheet(
            "background-color: transparent;"
            "box-shadow: 2px 2px 5px rgba(0,0,0,0.5);"
        );
    } else {
        team2Logo->setText("No Logo");
        team2Logo->setStyleSheet(
            "font-size: 18px; color: #FFFFFF;"
            "background-color: transparent;"
        );
    }
    QLabel *team2Label = new QLabel(team2Name);
    team2Label->setStyleSheet(
        "font-size: 22px; font-weight: bold;"
        "background-color: transparent;"
        "text-shadow: 1px 1px 2px #000000;"
    );
    team2Layout->addWidget(team2Logo, 0, Qt::AlignCenter);
    team2Layout->addWidget(team2Label, 0, Qt::AlignCenter);

    teamsLayout->addStretch();
    teamsLayout->addLayout(team1Layout);
    teamsLayout->addLayout(scoreLayout);
    teamsLayout->addLayout(team2Layout);
    teamsLayout->addStretch();
    scoreboardLayout->addLayout(teamsLayout);
    mainLayout->addLayout(scoreboardLayout);

    QHBoxLayout *tabLayout = new QHBoxLayout();
    tabLayout->setSpacing(10);
    QLabel *matchTab = new QLabel("MATCH");
    matchTab->setStyleSheet(
        "font-size: 16px; font-weight: bold; color: #FFFFFF;"
        "border-bottom: 2px solid #FF0000; padding: 5px;"
        "background-color: transparent;"
        "text-shadow: 1px 1px 2px #000000;"
    );
    QLabel *summaryTab = new QLabel("SUMMARY");
    summaryTab->setStyleSheet(
        "font-size: 16px; font-weight: bold; color: #666666; padding: 5px;"
        "background-color: transparent;"
        "text-shadow: 1px 1px 2px #000000;"
    );
    QLabel *statsTab = new QLabel("STATS");
    statsTab->setStyleSheet(
        "font-size: 16px; font-weight: bold; color: #666666; padding: 5px;"
        "background-color: transparent;"
        "text-shadow: 1px 1px 2px #000000;"
    );
    tabLayout->addStretch();
    tabLayout->addWidget(matchTab);
    tabLayout->addWidget(summaryTab);
    tabLayout->addWidget(statsTab);
    tabLayout->addStretch();
    mainLayout->addLayout(tabLayout);

    QLabel *commentaryHeader = new QLabel("COMMENTARY");
    commentaryHeader->setStyleSheet(
        "font-size: 16px; font-weight: bold; color: #FFFFFF; margin-top: 10px;"
        "background-color: transparent;"
        "text-shadow: 1px 1px 2px #000000;"
    );
    mainLayout->addWidget(commentaryHeader);

    commentaryTextEdit = new QTextEdit();
    commentaryTextEdit->setReadOnly(true);
    commentaryTextEdit->append("<span style='color:#FF0000'>0:00</span> - Match started!");
    commentaryTimer->start(10000);
    connect(commentaryTimer, &QTimer::timeout, this, &WatchMatchDialog::updateCommentary);
    mainLayout->addWidget(commentaryTextEdit);

    QHBoxLayout *statusLayout = new QHBoxLayout();
    QLabel *weatherLabel = new QLabel(weatherIcon + "Weather: " + weather);
    weatherLabel->setObjectName("weatherLabel");
    weatherLabel->setStyleSheet(
        "font-size: 14px; color: #B0BEC5;"
        "background-color: transparent;"
        "text-shadow: 1px 1px 2px #000000;"
    );
    sensorStatusLabel = new QLabel("Weather Sensor: Connecting to Arduino...");
    sensorStatusLabel->setStyleSheet(
        "font-size: 14px; color: #FFFFFF;"
        "background-color: transparent;"
        "text-shadow: 1px 1px 2px #000000;"
    );
    goalStatusLabel = new QLabel("Goal Sensor: Connecting to Arduino...");
    goalStatusLabel->setStyleSheet(
        "font-size: 14px; color: #FFFFFF;"
        "background-color: transparent;"
        "text-shadow: 1px 1px 2px #000000;"
    );
    statusLayout->addWidget(weatherLabel);
    statusLayout->addStretch();
    statusLayout->addWidget(sensorStatusLabel);
    statusLayout->addWidget(goalStatusLabel);
    mainLayout->addLayout(statusLayout);

    QPushButton *okButton = new QPushButton("Exit Match");
    connect(okButton, &QPushButton::clicked, this, &QDialog::accept);
    mainLayout->addWidget(okButton, 0, Qt::AlignCenter);

    if (weatherArduino->connect_arduino() == 0) {
        qDebug() << "Weather Arduino connected successfully on port:" << weatherArduino->getArduino_port_name();
        QString servoCommand = (weatherCode == 1) ? "SERVO:1\n" : "SERVO:0\n";
        weatherArduino->write_to_arduino(servoCommand.toUtf8());
        qDebug() << "Initial servo command sent:" << servoCommand.trimmed();
        QThread::msleep(100);

        sensorTimer->start(1000);
        connect(sensorTimer, &QTimer::timeout, this, &WatchMatchDialog::readSensorData);
    } else {
        sensorStatusLabel->setText("Weather Sensor: Arduino not connected");
        sensorStatusLabel->setStyleSheet(
            "font-size: 14px; color: #FF4500;"
            "background-color: transparent;"
            "text-shadow: 1px 1px 2px #000000;"
        );
        qDebug() << "Failed to connect to Weather Arduino";
    }

    if (goalArduino->connect_goal_arduino() == 0) {
        qDebug() << "Goal Arduino connected successfully on port:" << goalArduino->getArduino_port_name();
        goalStatusLabel->setText("Goal Sensor: Connected");
        goalTimer->start(500);
        connect(goalTimer, &QTimer::timeout, this, &WatchMatchDialog::readGoalData);
    } else {
        goalStatusLabel->setText("Goal Sensor: Arduino not connected");
        goalStatusLabel->setStyleSheet(
            "font-size: 14px; color: #FF4500;"
            "background-color: transparent;"
            "text-shadow: 1px 1px 2px #000000;"
        );
        qDebug() << "Failed to connect to Goal Arduino";
    }
}

WatchMatchDialog::~WatchMatchDialog() {
    disconnect(sensorTimer, &QTimer::timeout, this, &WatchMatchDialog::readSensorData);
    disconnect(goalTimer, &QTimer::timeout, this, &WatchMatchDialog::readGoalData);
    disconnect(timeTimer, &QTimer::timeout, this, &WatchMatchDialog::updateMatchTime);
    disconnect(commentaryTimer, &QTimer::timeout, this, &WatchMatchDialog::updateCommentary);
    disconnect(rainTimer, &QTimer::timeout, rainWidget, &RainWidget::updateRaindrops);
    disconnect(sunTimer, &QTimer::timeout, sunWidget, &SunWidget::updateSunAndClouds);
    sensorTimer->stop();
    goalTimer->stop();
    timeTimer->stop();
    commentaryTimer->stop();
    rainTimer->stop();
    sunTimer->stop();
    weatherArduino->close_arduino();
    goalArduino->close_arduino();
    delete weatherArduino;
    delete goalArduino;
    delete scoreAnimation;
    QThread::msleep(1000);
}

void WatchMatchDialog::accept() {
    disconnect(sensorTimer, &QTimer::timeout, this, &WatchMatchDialog::readSensorData);
    disconnect(goalTimer, &QTimer::timeout, this, &WatchMatchDialog::readGoalData);
    disconnect(timeTimer, &QTimer::timeout, this, &WatchMatchDialog::updateMatchTime);
    disconnect(commentaryTimer, &QTimer::timeout, this, &WatchMatchDialog::updateCommentary);
    disconnect(rainTimer, &QTimer::timeout, rainWidget, &RainWidget::updateRaindrops);
    disconnect(sunTimer, &QTimer::timeout, sunWidget, &SunWidget::updateSunAndClouds);
    sensorTimer->stop();
    goalTimer->stop();
    timeTimer->stop();
    commentaryTimer->stop();
    rainTimer->stop();
    sunTimer->stop();
    
    weatherArduino->write_to_arduino("SERVO:0\n");
    qDebug() << "Sent to Weather Arduino: SERVO:0 (on close)";
    QThread::msleep(100);
    
    weatherArduino->close_arduino();
    goalArduino->close_arduino();
    QThread::msleep(1000);
    
    QDialog::accept();
}

void WatchMatchDialog::updateBackground(int meteo) {
    sunWidget->hide();
    rainWidget->hide();
    sunTimer->stop();
    rainTimer->stop();

    if (meteo == 0) {
        sunWidget->show();
        sunTimer->start(50);
    } else if (meteo == 1) {
        rainWidget->show();
        rainTimer->start(30);
    }
}

void WatchMatchDialog::readSensorData() {
    QByteArray data = weatherArduino->read_from_arduino();
    qDebug() << "Raw data from Weather Arduino:" << data << "at time:" << QTime::currentTime().toString();
    if (data.isEmpty()) {
        sensorStatusLabel->setText("Weather Sensor: Waiting for data...");
        sensorStatusLabel->setStyleSheet(
            "font-size: 14px; color: #FFFFFF;"
            "background-color: transparent;"
            "text-shadow: 1px 1px 2px #000000;"
        );
        qDebug() << "No data available from Weather Arduino";
        return;
    }

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
                sensorStatusLabel->setText("Weather Sensor: Rain Detected");
                sensorStatusLabel->setStyleSheet(
                    "font-size: 14px; color: #00FF00;"
                    "background-color: transparent;"
                    "text-shadow: 1px 1px 2px #000000;"
                );
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
                            weatherLabel->setText("🌧️ Weather: Rainy");
                        }
                        updateBackground(1);
                        weatherArduino->write_to_arduino("SERVO:1\n");
                        qDebug() << "Sent to Weather Arduino: SERVO:1 (rain detected)";
                        QThread::msleep(100);
                        commentaryTextEdit->append(
                            "<span style='color:#FF0000'>" + matchTimeLabel->text() + "</span> - Rain detected! Match conditions updated."
                        );
                    }
                }
            } else {
                sensorStatusLabel->setText("Weather Sensor: No Rain");
                sensorStatusLabel->setStyleSheet(
                    "font-size: 14px; color: #FFFFFF;"
                    "background-color: transparent;"
                    "text-shadow: 1px 1px 2px #000000;"
                );
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
                            weatherLabel->setText("🟡 Weather: Sunny");
                        }
                        updateBackground(0);
                        weatherArduino->write_to_arduino("SERVO:0\n");
                        qDebug() << "Sent to Weather Arduino: SERVO:0 (no rain)";
                        QThread::msleep(100);
                        commentaryTextEdit->append(
                            "<span style='color:#FF0000'>" + matchTimeLabel->text() + "</span> - Weather cleared. Sunny conditions."
                        );
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

void WatchMatchDialog::readGoalData() {
    QByteArray data = goalArduino->read_from_goal_arduino();
    qDebug() << "Raw data from Goal Arduino:" << data << "at time:" << QTime::currentTime().toString();
    if (data.isEmpty()) {
        return;
    }

    QString dataStr = QString::fromUtf8(data).trimmed();
    qDebug() << "Parsed goal data string:" << dataStr;
    if (dataStr == "GOAL_A") {
        QSqlQuery query;
        // Update MATCH table
        query.prepare(
            "UPDATE HOTSTUFF.MATCH "
            "SET SCOREA = SCOREA + 1 "
            "WHERE ID_MATCH = :matchId"
        );
        query.bindValue(":matchId", matchId);
        if (!query.exec()) {
            qDebug() << "Failed to update SCOREA:" << query.lastError().text();
            QMessageBox::warning(this, "Error", "Failed to update score: " + query.lastError().text());
            return;
        }

        // Update EQUIPE table
        query.prepare(
            "UPDATE HOTSTUFF.EQUIPE "
            "SET GOALS_TEAM = GOALS_TEAM + 1 "
            "WHERE ID_TEAM = :teamId"
        );
        query.bindValue(":teamId", teamAId);
        if (!query.exec()) {
            qDebug() << "Failed to update GOALS_TEAM:" << query.lastError().text();
            QMessageBox::warning(this, "Error", "Failed to update team goals: " + query.lastError().text());
            return;
        }

        // Update UI
        query.prepare(
            "SELECT SCOREA, SCOREB "
            "FROM HOTSTUFF.MATCH "
            "WHERE ID_MATCH = :matchId"
        );
        query.bindValue(":matchId", matchId);
        if (query.exec() && query.next()) {
            int score1 = query.value("SCOREA").toInt();
            int score2 = query.value("SCOREB").toInt();
            QLabel *scoreLabel = findChild<QLabel*>("scoreLabel");
            if (scoreLabel) {
                scoreLabel->setText(QString("%1 - %2").arg(score1).arg(score2));
                scoreAnimation->start();
            }
        }

        commentaryTextEdit->append(
            "<span style='color:#FF0000'>" + matchTimeLabel->text() + "</span> - ⚽ GOAL for " + team1Label->text() + "!"
        );
        commentaryTextEdit->verticalScrollBar()->setValue(commentaryTextEdit->verticalScrollBar()->maximum());
    }
}

void WatchMatchDialog::updateMatchTime() {
    QDateTime currentTime = QDateTime::currentDateTime();
    qint64 secondsElapsed = matchStartTime.secsTo(currentTime);

    if (secondsElapsed < 0) {
        matchTimeLabel->setText("0:00");
        halfTimeLabel->setVisible(false);
        return;
    }

    qint64 totalMinutes = secondsElapsed / 60;
    qint64 seconds = secondsElapsed % 60;

    if (totalMinutes < 45) {
        matchTimeLabel->setText(QString("%1:%2").arg(totalMinutes).arg(seconds, 2, 10, QChar('0')));
        halfTimeLabel->setVisible(false);
    }
    else if (totalMinutes >= 45 && totalMinutes < 60) {
        if (!isHalfTime) {
            isHalfTime = true;
            commentaryTextEdit->append(
                "<span style='color:#FF0000'>45:00</span> 🔔 - Referee has ended the first half."
            );
        }
        matchTimeLabel->setText("45:00");
        halfTimeLabel->setVisible(true);
    }
    else if (totalMinutes >= 60 && totalMinutes < 105) {
        if (isHalfTime) {
            isHalfTime = false;
            commentaryTextEdit->append(
                "<span style='color:#FF0000'>45:00</span> - Second Half started!"
            );
        }
        qint64 matchMinutes = totalMinutes - 15;
        matchTimeLabel->setText(QString("%1:%2").arg(matchMinutes).arg(seconds, 2, 10, QChar('0')));
        halfTimeLabel->setVisible(false);
    }
    else {
        matchTimeLabel->setText("90:00");
        halfTimeLabel->setVisible(false);
        timeTimer->stop();
        commentaryTextEdit->append(
            "<span style='color:#FF0000'>90:00</span> 🔔 - Full Time!"
        );
    }
}

void WatchMatchDialog::updateCommentary() {
    static int eventCount = 0;
    QStringList events = {
        "Great pass from midfield!",
        "Shot on goal, saved by the keeper!",
        "⚽ Corner kick awarded.",
        "Player down, medical team on the pitch.",
        "Goal attempt missed, just wide!"
    };
    QString timeStr = matchTimeLabel->text();
    if (timeStr != "HT" && timeStr != "0:00" && timeStr != "90:00") {
        commentaryTextEdit->append(
            "<span style='color:#FF0000'>" + timeStr + "</span> - " + events[eventCount % events.size()]
        );
        eventCount++;
        commentaryTextEdit->verticalScrollBar()->setValue(commentaryTextEdit->verticalScrollBar()->maximum());
    }
}