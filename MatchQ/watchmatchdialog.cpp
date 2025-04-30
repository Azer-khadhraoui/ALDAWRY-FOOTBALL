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
#include <QStackedWidget>
#include <QScrollArea>
#include <QProcess>
#include <QFile>
#include <QTextStream>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QEventLoop>

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
      skyTimer(new QTimer(this)), 
      skyWidget(nullptr), 
      scoreAnimation(nullptr), 
      rainDetected(false), 
      noRainDetected(false), 
      isHalfTime(false),
      stackedWidget(new QStackedWidget(this)),
      matchWidget(new QWidget(this)),
      lineupWidget(new QWidget(this)) {
    setWindowTitle("Live Match");
    setFixedSize(1000, 1000);
    setStyleSheet(
        "QDialog {"
        "    background-color: transparent;"
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
        "    border: 2px solid #FF0000;"
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

    rainWidget = new RainWidget(this);
    rainWidget->setFixedSize(1000, 1000);
    rainWidget->lower();
    rainWidget->hide();
    connect(rainTimer, &QTimer::timeout, rainWidget, &RainWidget::updateRaindrops);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setSpacing(10);
    mainLayout->setContentsMargins(0, 0, 0, 0);

    QScrollArea *scrollArea = new QScrollArea(this);
    scrollArea->setWidgetResizable(true);
    scrollArea->setStyleSheet(
        "QScrollArea {"
        "    background-color: transparent;"
        "    border: none;"
        "}"
        "QScrollBar:vertical {"
        "    background: #1C2526;"
        "    width: 10px;"
        "    margin: 0px;"
        "}"
        "QScrollBar::handle:vertical {"
        "    background: #FF0000;"
        "    border-radius: 5px;"
        "}"
        "QScrollBar::add-line:vertical, QScrollBar::sub-line:vertical {"
        "    background: none;"
        "}"
    );

    QWidget *contentWidget = new QWidget();
    contentWidget->setStyleSheet("background-color: transparent;");
    QVBoxLayout *contentLayout = new QVBoxLayout(contentWidget);
    contentLayout->setSpacing(10);

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

    int initialScoreA = 0, initialScoreB = 0;

    if (!query.exec() || !query.next()) {
        QString errorMsg = "Failed to load match details: " + query.lastError().text();
        qDebug() << "SQL Error:" << errorMsg << "\nQuery:" << query.lastQuery();
        QMessageBox::critical(this, "Error", errorMsg);
        close();
        return;
    }

    teamAId = query.value("ID_TEAMA").toInt();
    teamBId = query.value("ID_TEAMB").toInt();
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
    initialScoreA = query.value("SCOREA").toInt();
    initialScoreB = query.value("SCOREB").toInt();
    matchStartTime = query.value("MATCH_DATETIME").toDateTime();
    QByteArray logo1Data = query.value("TEAM1_LOGO").toByteArray();
    QByteArray logo2Data = query.value("TEAM2_LOGO").toByteArray();

    updateBackground(weatherCode);

    QLabel *dateLabel = new QLabel(matchStartTime.toString("dd.MM.yyyy HH:mm"));
    dateLabel->setStyleSheet(
        "font-size: 16px; color: #B0BEC5; font-weight: bold;"
        "text-shadow: 1px 1px 2px #000000;"
    );
    contentLayout->addWidget(dateLabel, 0, Qt::AlignCenter);

    matchTimeLabel = new QLabel("0:00");
    matchTimeLabel->setStyleSheet(
        "font-size: 24px; font-weight: bold; color: #FFFFFF;"
        "background-color: #FF0000; padding: 5px 10px; border-radius: 5px;"
        "text-shadow: 1px 1px 2px #000000;"
    );
    contentLayout->addWidget(matchTimeLabel, 0, Qt::AlignCenter);
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
            "font-size: 18px;"
            "background-color: transparent;"
        );
    }
    team1Label = new QLabel(team1Name);
    team1Label->setStyleSheet(
        "font-size: 22px; font-weight: bold;"
        "background-color: transparent;"
        "text-shadow: 1px 1px 2px #000000;"
    );
    team1Layout->addWidget(team1Logo, 0, Qt::AlignCenter);
    team1Layout->addWidget(team1Label, 0, Qt::AlignCenter);

    QVBoxLayout *scoreLayout = new QVBoxLayout();
    QLabel *scoreLabel = new QLabel(QString("%1 - %2").arg(initialScoreA).arg(initialScoreB));
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
            "font-size: 18px;"
            "background-color: transparent;"
        );
    }
    team2Label = new QLabel(team2Name);
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
    contentLayout->addLayout(scoreboardLayout);

    QHBoxLayout *tabLayout = new QHBoxLayout();
    tabLayout->setSpacing(10);
    QLabel *matchTab = new QLabel("<a href='#match'>MATCH</a>");
    matchTab->setObjectName("matchTab");
    matchTab->setStyleSheet(
        "font-size: 16px; font-weight: bold; color: #FFFFFF;"
        "border-bottom: 2px solid #FF0000; padding: 5px;"
        "background-color: transparent;"
        "text-shadow: 1px 1px 2px #000000;"
    );
    matchTab->setTextFormat(Qt::RichText);
    matchTab->setTextInteractionFlags(Qt::TextBrowserInteraction);
    matchTab->setOpenExternalLinks(false);
    connect(matchTab, &QLabel::linkActivated, this, &WatchMatchDialog::showMatchView);

    QLabel *lineupTab = new QLabel("<a href='#lineup'>LINEUP</a>");
    lineupTab->setObjectName("lineupTab");
    lineupTab->setStyleSheet(
        "font-size: 16px; font-weight: bold; color: #666666; padding: 5px;"
        "background-color: transparent;"
        "text-shadow: 1px 1px 2px #000000;"
    );
    lineupTab->setTextFormat(Qt::RichText);
    lineupTab->setTextInteractionFlags(Qt::TextBrowserInteraction);
    lineupTab->setOpenExternalLinks(false);
    connect(lineupTab, &QLabel::linkActivated, this, &WatchMatchDialog::showLineupView);

    tabLayout->addStretch();
    tabLayout->addWidget(matchTab);
    tabLayout->addWidget(lineupTab);
    tabLayout->addStretch();
    contentLayout->addLayout(tabLayout);

    QVBoxLayout *matchLayout = new QVBoxLayout(matchWidget);
    matchLayout->setSpacing(10);
    matchWidget->setStyleSheet("background-color: transparent;");

    QLabel *commentaryHeader = new QLabel("COMMENTARY");
    commentaryHeader->setStyleSheet(
        "font-size: 16px; font-weight: bold; margin-top: 10px;"
        "background-color: transparent;"
        "text-shadow: 1px 1px 2px #000000;"
    );
    matchLayout->addWidget(commentaryHeader);

    commentaryTextEdit = new QTextEdit();
    commentaryTextEdit->setReadOnly(true);
    commentaryTextEdit->append("<span style='color:#FF0000'>0:00</span> - Match started!");
    commentaryTimer->start(10000);
    connect(commentaryTimer, &QTimer::timeout, this, &WatchMatchDialog::updateCommentary);
    matchLayout->addWidget(commentaryTextEdit);

    QPushButton *recordButton = new QPushButton("Record");
    recordButton->setStyleSheet(
        "background-color: transparent;"
        "color: #FFFFFF;"
        "border: 2px solid #FF0000;"
        "border-radius: 8px;"
        "padding: 10px;"
        "font-size: 16px;"
        "font-weight: bold;"
    );
    connect(recordButton, &QPushButton::clicked, this, &WatchMatchDialog::runPythonScript);
    matchLayout->addWidget(recordButton, 0, Qt::AlignCenter);

    setupLineupView();

    stackedWidget->addWidget(matchWidget);
    stackedWidget->addWidget(lineupWidget);
    stackedWidget->setStyleSheet("background-color: transparent;");
    contentLayout->addWidget(stackedWidget);

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
        "font-size: 14px;"
        "background-color: transparent;"
        "text-shadow: 1px 1px 2px #000000;"
    );
    goalStatusLabel = new QLabel("Goal Sensor: Connecting to Arduino...");
    goalStatusLabel->setStyleSheet(
        "font-size: 14px;"
        "background-color: transparent;"
        "text-shadow: 1px 1px 2px #000000;"
    );
    statusLayout->addWidget(weatherLabel);
    statusLayout->addStretch();
    statusLayout->addWidget(sensorStatusLabel);
    statusLayout->addWidget(goalStatusLabel);
    contentLayout->addLayout(statusLayout);

    QPushButton *okButton = new QPushButton("Exit Match");
    connect(okButton, &QPushButton::clicked, this, &QDialog::accept);
    contentLayout->addWidget(okButton, 0, Qt::AlignCenter);

    contentLayout->addStretch();

    scrollArea->setWidget(contentWidget);
    mainLayout->addWidget(scrollArea);

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
        sendScoreToArduino(initialScoreA, initialScoreB); // Send initial score
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
    // Disconnect timers
    disconnect(sensorTimer, &QTimer::timeout, this, &WatchMatchDialog::readSensorData);
    disconnect(goalTimer, &QTimer::timeout, this, &WatchMatchDialog::readGoalData);
    disconnect(timeTimer, &QTimer::timeout, this, &WatchMatchDialog::updateMatchTime);
    disconnect(commentaryTimer, &QTimer::timeout, this, &WatchMatchDialog::updateCommentary);
    disconnect(rainTimer, &QTimer::timeout, rainWidget, &RainWidget::updateRaindrops);
    if (skyWidget) {
        disconnect(skyTimer, &QTimer::timeout, skyWidget, &SkyWidget::updateSky);
    }
    sensorTimer->stop();
    goalTimer->stop();
    timeTimer->stop();
    commentaryTimer->stop();
    rainTimer->stop();
    skyTimer->stop();

    // Send reset command to goal Arduino
    if (goalArduino->getSerial()->isOpen()) {
        goalArduino->write_to_arduino("RESET\n");
        qDebug() << "Sent to Goal Arduino: RESET (on destroy)";
        QThread::msleep(100); // Allow time for command to be processed
    }

    // Send servo off command to weather Arduino
    if (weatherArduino->getSerial()->isOpen()) {
        weatherArduino->write_to_arduino("SERVO:0\n");
        qDebug() << "Sent to Weather Arduino: SERVO:0 (on destroy)";
        QThread::msleep(100);
    }

    // Close Arduino connections
    weatherArduino->close_arduino();
    goalArduino->close_arduino();
    QThread::msleep(1000); // Ensure connections are fully closed

    // Clean up
    delete weatherArduino;
    delete goalArduino;
    delete scoreAnimation;
}

void WatchMatchDialog::accept() {
    // Disconnect timers
    disconnect(sensorTimer, &QTimer::timeout, this, &WatchMatchDialog::readSensorData);
    disconnect(goalTimer, &QTimer::timeout, this, &WatchMatchDialog::readGoalData);
    disconnect(timeTimer, &QTimer::timeout, this, &WatchMatchDialog::updateMatchTime);
    disconnect(commentaryTimer, &QTimer::timeout, this, &WatchMatchDialog::updateCommentary);
    disconnect(rainTimer, &QTimer::timeout, rainWidget, &RainWidget::updateRaindrops);
    if (skyWidget) {
        disconnect(skyTimer, &QTimer::timeout, skyWidget, &SkyWidget::updateSky);
    }
    sensorTimer->stop();
    goalTimer->stop();
    timeTimer->stop();
    commentaryTimer->stop();
    rainTimer->stop();
    skyTimer->stop();
    
    // Send reset command to goal Arduino
    if (goalArduino->getSerial()->isOpen()) {
        goalArduino->write_to_arduino("RESET\n");
        qDebug() << "Sent to Goal Arduino: RESET (on accept)";
        QThread::msleep(100); // Allow time for command to be processed
    }

    // Send servo off command to weather Arduino
    if (weatherArduino->getSerial()->isOpen()) {
        weatherArduino->write_to_arduino("SERVO:0\n");
        qDebug() << "Sent to Weather Arduino: SERVO:0 (on accept)";
        QThread::msleep(100);
    }
    
    // Close Arduino connections
    weatherArduino->close_arduino();
    goalArduino->close_arduino();
    QThread::msleep(1000); // Ensure connections are fully closed
    
    QDialog::accept();
}

void WatchMatchDialog::updateBackground(int meteo) {
    if (skyWidget) {
        skyWidget->hide();
    }
    rainWidget->hide();
    skyTimer->stop();
    rainTimer->stop();

    int hour = matchStartTime.time().hour();
    bool isDay = (hour >= 6 && hour < 18);
    QString backgroundColor = isDay ? "#87CEEB" : "#1C2526";
    QString textColor = isDay ? "#000000" : "#FFFFFF";

    qDebug() << "Updating background: Hour =" << hour << ", isDay =" << isDay << ", meteo =" << meteo;

    if (skyWidget) {
        disconnect(skyTimer, &QTimer::timeout, skyWidget, &SkyWidget::updateSky);
        delete skyWidget;
    }
    skyWidget = new SkyWidget(this, isDay);
    skyWidget->setFixedSize(1000, 1000);
    skyWidget->lower();
    connect(skyTimer, &QTimer::timeout, skyWidget, &SkyWidget::updateSky);

    skyWidget->setStyleSheet(QString("background-color: %1;").arg(backgroundColor));
    rainWidget->setStyleSheet(QString("background-color: %1;").arg(backgroundColor));

    setStyleSheet(
        QString(
            "QDialog {"
            "    background-color: %1;"
            "    color: %2;"
            "    font-family: 'Roboto Condensed', 'Arial', sans-serif;"
            "    font-size: 14px;"
            "    border: 1px solid #FFFFFF;"
            "    border-radius: 10px;"
            "    padding: 15px;"
            "}"
            "QLabel {"
            "    color: %2;"
            "    background-color: transparent;"
            "}"
            "QPushButton {"
            "    background-color: transparent;"
            "    color: %2;"
            "    border: 2px solid #FF0000;"
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
            "    color: %2;"
            "    border: none;"
            "    padding: 10px;"
            "    font-size: 14px;"
            "}"
        ).arg(backgroundColor).arg(textColor)
    );

    if (meteo == 0) {
        skyWidget->show();
        skyTimer->start(50);
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
            sendScoreToArduino(score1, score2); // Send updated score to Arduino
        }

        commentaryTextEdit->append(
            "<span style='color:#FF0000'>" + matchTimeLabel->text() + "</span> - ⚽ GOAL for " + team1Label->text() + "!"
        );
        commentaryTextEdit->verticalScrollBar()->setValue(commentaryTextEdit->verticalScrollBar()->maximum());
    } else if (dataStr == "GOAL_B") {
        QSqlQuery query;
        query.prepare(
            "UPDATE HOTSTUFF.MATCH "
            "SET SCOREB = SCOREB + 1 "
            "WHERE ID_MATCH = :matchId"
        );
        query.bindValue(":matchId", matchId);
        if (!query.exec()) {
            qDebug() << "Failed to update SCOREB:" << query.lastError().text();
            QMessageBox::warning(this, "Error", "Failed to update score: " + query.lastError().text());
            return;
        }

        query.prepare(
            "UPDATE HOTSTUFF.EQUIPE "
            "SET GOALS_TEAM = GOALS_TEAM + 1 "
            "WHERE ID_TEAM = :teamId"
        );
        query.bindValue(":teamId", teamBId);
        if (!query.exec()) {
            qDebug() << "Failed to update GOALS_TEAM:" << query.lastError().text();
            QMessageBox::warning(this, "Error", "Failed to update team goals: " + query.lastError().text());
            return;
        }

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
            sendScoreToArduino(score1, score2); // Send updated score to Arduino
        }

        commentaryTextEdit->append(
            "<span style='color:#FF0000'>" + matchTimeLabel->text() + "</span> - ⚽ GOAL for " + team2Label->text() + "!"
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
    } else if (totalMinutes >= 45 && totalMinutes < 60) {
        if (!isHalfTime) {
            isHalfTime = true;
            commentaryTextEdit->append(
                "<span style='color:#FF0000'>45:00</span> 🔔 - Referee has ended the first half."
            );
        }
        matchTimeLabel->setText("45:00");
        halfTimeLabel->setVisible(true);
    } else if (totalMinutes >= 60 && totalMinutes < 105) {
        if (isHalfTime) {
            isHalfTime = false;
            commentaryTextEdit->append(
                "<span style='color:#FF0000'>45:00</span> - Second Half started!"
            );
        }
        qint64 matchMinutes = totalMinutes - 15;
        matchTimeLabel->setText(QString("%1:%2").arg(matchMinutes).arg(seconds, 2, 10, QChar('0')));
        halfTimeLabel->setVisible(false);
    } else {
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

void WatchMatchDialog::showMatchView() {
    stackedWidget->setCurrentWidget(matchWidget);
    QLabel *matchTab = findChild<QLabel*>("matchTab");
    QLabel *lineupTab = findChild<QLabel*>("lineupTab");
    if (matchTab) {
        matchTab->setStyleSheet(
            "font-size: 16px; font-weight: bold; color: #FFFFFF;"
            "border-bottom: 2px solid #FF0000; padding: 5px;"
            "background-color: transparent;"
            "text-shadow: 1px 1px 2px #000000;"
        );
    }
    if (lineupTab) {
        lineupTab->setStyleSheet(
            "font-size: 16px; font-weight: bold; color: #666666; padding: 5px;"
            "background-color: transparent;"
            "text-shadow: 1px 1px 2px #000000;"
        );
    }
}

void WatchMatchDialog::showLineupView() {
    stackedWidget->setCurrentWidget(lineupWidget);
    QLabel *matchTab = findChild<QLabel*>("matchTab");
    QLabel *lineupTab = findChild<QLabel*>("lineupTab");
    if (matchTab) {
        matchTab->setStyleSheet(
            "font-size: 16px; font-weight: bold; color: #666666; padding: 5px;"
            "background-color: transparent;"
            "text-shadow: 1px 1px 2px #000000;"
        );
    }
    if (lineupTab) {
        lineupTab->setStyleSheet(
            "font-size: 16px; font-weight: bold; color: #FFFFFF;"
            "border-bottom: 2px solid #FF0000; padding: 5px;"
            "background-color: transparent;"
            "text-shadow: 1px 1px 2px #000000;"
        );
    }
}

void WatchMatchDialog::setupLineupView() {
    QVBoxLayout *lineupLayout = new QVBoxLayout(lineupWidget);
    lineupLayout->setSpacing(10);
    lineupWidget->setStyleSheet("background-color: transparent;");

    QHBoxLayout *teamsLayout = new QHBoxLayout();
    teamsLayout->setSpacing(20);

    QSqlQuery query;
    query.prepare(
        "SELECT t.ID_PLAYER, j.FIRST_NAME, j.LAST_NAME, j.POSITION, j.JERSEY_NB, j.ID_TEAM, t.FORMATION "
        "FROM HOTSTUFF.TACHKILA t "
        "JOIN HOTSTUFF.JOUEUR j ON t.ID_PLAYER = j.ID_PLAYER "
        "WHERE t.ID_MATCH = :matchId "
        "ORDER BY j.ID_TEAM, j.POSITION"
    );
    query.bindValue(":matchId", matchId);

    if (!query.exec()) {
        qDebug() << "Failed to load lineup: " << query.lastError().text();
        QLabel *errorLabel = new QLabel("Failed to load lineup: " + query.lastError().text());
        errorLabel->setStyleSheet(
            "font-size: 14px; color: #FF4500;"
            "background-color: transparent;"
        );
        lineupLayout->addWidget(errorLabel, 0, Qt::AlignCenter);
        return;
    }

    QWidget *team1Widget = new QWidget();
    QWidget *team2Widget = new QWidget();
    QVBoxLayout *team1Lineup = new QVBoxLayout(team1Widget);
    QVBoxLayout *team2Lineup = new QVBoxLayout(team2Widget);
    team1Lineup->setSpacing(5);
    team2Lineup->setSpacing(5);
    team1Widget->setStyleSheet("background-color: transparent;");
    team2Widget->setStyleSheet("background-color: transparent;");

    QString team1Formation, team2Formation;

    while (query.next()) {
        int playerTeamId = query.value("ID_TEAM").toInt();
        QString playerName = query.value("FIRST_NAME").toString() + " " + query.value("LAST_NAME").toString();
        QString position = query.value("POSITION").toString();
        int jerseyNb = query.value("JERSEY_NB").toInt();
        QString formation = query.value("FORMATION").toString();

        QTextEdit *playerLabel = new QTextEdit();
        playerLabel->setReadOnly(true);
        playerLabel->setText(QString("%1. %2 (%3)").arg(jerseyNb).arg(playerName).arg(position));
        playerLabel->setStyleSheet(
            "font-size: 14px;"
            "background-color: transparent;"
            "border: none;"
            "padding: 5px;"
        );
        playerLabel->setFixedHeight(40);
        playerLabel->setFrameStyle(QFrame::NoFrame);
        playerLabel->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        playerLabel->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

        if (playerTeamId == teamAId) {
            team1Lineup->addWidget(playerLabel);
            team1Formation = formation;
        } else if (playerTeamId == teamBId) {
            team2Lineup->addWidget(playerLabel);
            team2Formation = formation;
        }
    }

    QLabel *team1Header = new QLabel(team1Label->text() + " (" + team1Formation + ")");
    team1Header->setStyleSheet(
        "font-size: 16px; font-weight: bold;"
        "background-color: transparent;"
        "text-shadow: 1px 1px 2px #000000;"
    );
    team1Lineup->insertWidget(0, team1Header);

    QLabel *team2Header = new QLabel(team2Label->text() + " (" + team2Formation + ")");
    team2Header->setStyleSheet(
        "font-size: 16px; font-weight: bold;"
        "background-color: transparent;"
        "text-shadow: 1px 1px 2px #000000;"
    );
    team2Lineup->insertWidget(0, team2Header);

    teamsLayout->addWidget(team1Widget);
    teamsLayout->addStretch();
    teamsLayout->addWidget(team2Widget);
    lineupLayout->addLayout(teamsLayout);
    lineupLayout->addStretch();
}

void WatchMatchDialog::runPythonScript() {
    QProcess process;
    QString pythonScript = "D:/projet app desktop/MatchQ/speech_to_text.py";
    process.start("python", QStringList() << pythonScript);
    process.waitForFinished(-1);
    if (process.exitStatus() == QProcess::NormalExit && process.exitCode() == 0) {
        qDebug() << "Python script executed successfully";
        updateTranscription();
    } else {
        QString error = process.readAllStandardError();
        qDebug() << "Python script failed:" << error;
        commentaryTextEdit->append("<span style='color:#FF0000'>" + matchTimeLabel->text() + "</span> - Error: Failed to run Python script");
    }
}

void WatchMatchDialog::updateTranscription() {
    QString filePath = "D:/projet app desktop/MatchQ/transcription.txt";
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Failed to open file:" << file.errorString();
        commentaryTextEdit->append("<span style='color:#FF0000'>" + matchTimeLabel->text() + "</span> - Error: Could not read transcription");
        return;
    }

    QTextStream in(&file);
    QString transcription = in.readAll();
    file.close();
    commentaryTextEdit->append("<span style='color:#FF0000'>" + matchTimeLabel->text() + "</span> - Transcription: " + transcription);
    commentaryTextEdit->verticalScrollBar()->setValue(commentaryTextEdit->verticalScrollBar()->maximum());

    if (transcription.isEmpty()) {
        qDebug() << "No transcription available for processing.";
        commentaryTextEdit->append("<span style='color:#FF0000'>" + matchTimeLabel->text() + "</span> - No transcription available");
        return;
    }

    qDebug() << "Transcription content:" << transcription;

    QString apiKey = "AIzaSyDm1OCBufbaP1k-ClMoPTCubMABaVtl3zg";
    if (apiKey.isEmpty()) {
        qDebug() << "Gemini API key is missing.";
        commentaryTextEdit->append("<span style='color:#FF0000'>" + matchTimeLabel->text() + "</span> - Error: Gemini API key is missing");
        return;
    }

    QNetworkAccessManager manager;
    QNetworkRequest request(QUrl("https://generativelanguage.googleapis.com/v1beta/models/gemini-2.0-flash:generateContent?key=" + apiKey));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QJsonObject json;
    QJsonArray parts;
    QJsonObject part;
    part["text"] = "Based on this transcription: \"" + transcription + "\", generate a valid Oracle SQL query to update the database. The database has a table 'joueur' with columns id_player, id_team, first_name, last_name, position, jersey_nb, red_card, yellow_card, and a table 'equipe' with columns id_team, team_name, etc. Provide only the SQL query, without any explanation or additional text.";
    parts.append(part);
    json["contents"] = QJsonArray{QJsonObject{{"parts", parts}}};
    json["generationConfig"] = QJsonObject{{"maxOutputTokens", 500}};

    QNetworkReply *reply = manager.post(request, QJsonDocument(json).toJson());
    QEventLoop loop;
    connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();

    if (reply->error() == QNetworkReply::NoError) {
        QByteArray responseData = reply->readAll();
        qDebug() << "Raw API Response:" << responseData;
        QJsonDocument responseDoc = QJsonDocument::fromJson(responseData);
        QJsonObject responseObj = responseDoc.object();
        qDebug() << "Parsed API Response:" << responseObj;

        if (responseObj.contains("candidates") && responseObj["candidates"].isArray()) {
            QJsonArray candidates = responseObj["candidates"].toArray();
            if (!candidates.isEmpty() && candidates[0].isObject()) {
                QJsonObject contentObj = candidates[0].toObject()["content"].toObject();
                if (contentObj.contains("parts") && contentObj["parts"].isArray()) {
                    QJsonArray partsArray = contentObj["parts"].toArray();
                    if (!partsArray.isEmpty() && partsArray[0].isObject()) {
                        QString sqlQuery = partsArray[0].toObject()["text"].toString().trimmed();

                        if (sqlQuery.startsWith("```sql")) {
                            sqlQuery.remove(0, 6);
                        }
                        if (sqlQuery.endsWith("```")) {
                            sqlQuery.chop(3);
                        }
                        sqlQuery = sqlQuery.trimmed();

                        if (sqlQuery.isEmpty()) {
                            commentaryTextEdit->append("<span style='color:#FF0000'>" + matchTimeLabel->text() + "</span> - No valid SQL query was generated");
                        } else {
                            qDebug() << "Generated SQL Query:" << sqlQuery;
                            QString lastName;
                            int jerseyNb = -1;
                            bool isYellowCard = sqlQuery.contains("yellow_card", Qt::CaseInsensitive);
                            bool isRedCard = sqlQuery.contains("red_card", Qt::CaseInsensitive);

                            QRegularExpression rx("jersey_nb\\s*=\\s*(\\d+)", QRegularExpression::CaseInsensitiveOption);
                            QRegularExpression teamRx("team_name\\s*=\\s*'([^']+)'", QRegularExpression::CaseInsensitiveOption);
                            QRegularExpressionMatch jerseyMatch = rx.match(sqlQuery);
                            QRegularExpressionMatch teamMatch = teamRx.match(sqlQuery);
                            QString playerJerseyNb;
                            QString teamName;

                            if (jerseyMatch.hasMatch()) {
                                playerJerseyNb = jerseyMatch.captured(1);
                            } else {
                                qDebug() << "Could not extract JERSEY_NB from SQL query.";
                            }

                            if (teamMatch.hasMatch()) {
                                teamName = teamMatch.captured(1);
                            } else {
                                qDebug() << "Could not extract team_name from SQL query.";
                            }

                            if (!playerJerseyNb.isEmpty() && !teamName.isEmpty()) {
                                QSqlQuery playerQuery;
                                playerQuery.prepare(
                                    "SELECT j.LAST_NAME, j.JERSEY_NB "
                                    "FROM HOTSTUFF.JOUEUR j "
                                    "JOIN HOTSTUFF.EQUIPE e ON j.ID_TEAM = e.ID_TEAM "
                                    "WHERE j.JERSEY_NB = :jerseyNb AND e.TEAM_NAME = :teamName"
                                );
                                playerQuery.bindValue(":jerseyNb", playerJerseyNb.toInt());
                                playerQuery.bindValue(":teamName", teamName);
                                if (playerQuery.exec() && playerQuery.next()) {
                                    lastName = playerQuery.value("LAST_NAME").toString();
                                    jerseyNb = playerQuery.value("JERSEY_NB").toInt();
                                } else {
                                    qDebug() << "Failed to fetch player details:" << playerQuery.lastError().text();
                                    lastName = "Unknown";
                                    jerseyNb = playerJerseyNb.toInt();
                                }
                            } else {
                                lastName = "Unknown";
                                jerseyNb = 0;
                            }

                            QSqlQuery query;
                            if (!query.exec(sqlQuery)) {
                                qDebug() << "Failed to execute SQL query:" << query.lastError().text();
                                commentaryTextEdit->append("<span style='color:#FF0000'>" + matchTimeLabel->text() + "</span> - Error: Failed to execute the SQL query");
                            } else {
                                qDebug() << "SQL query executed successfully.";
                                if (isYellowCard) {
                                    commentaryTextEdit->append(
                                        QString("<span style='color:#FF0000'>%1</span> - %2 %3 Yellow Card 🟨 !")
                                            .arg(matchTimeLabel->text())
                                            .arg(lastName)
                                            .arg(jerseyNb)
                                    );
                                } else if (isRedCard) {
                                    commentaryTextEdit->append(
                                        QString("<span style='color:#FF0000'>%1</span> - %2 %3 Red Card 🟥 !")
                                            .arg(matchTimeLabel->text())
                                            .arg(lastName)
                                            .arg(jerseyNb)
                                    );
                                }
                            }
                        }
                    } else {
                        qDebug() << "No valid parts in response.";
                        commentaryTextEdit->append("<span style='color:#FF0000'>" + matchTimeLabel->text() + "</span> - No valid SQL query was generated");
                    }
                } else {
                    qDebug() << "No valid content in response.";
                    commentaryTextEdit->append("<span style='color:#FF0000'>" + matchTimeLabel->text() + "</span> - No valid SQL query was generated");
                }
            } else {
                qDebug() << "No valid candidates in response.";
                commentaryTextEdit->append("<span style='color:#FF0000'>" + matchTimeLabel->text() + "</span> - No valid SQL query was generated");
            }
        } else {
            qDebug() << "Invalid API response format.";
            commentaryTextEdit->append("<span style='color:#FF0000'>" + matchTimeLabel->text() + "</span> - Invalid API response format");
        }
    } else {
        qDebug() << "API request failed:" << reply->errorString() << reply->readAll();
        commentaryTextEdit->append("<span style='color:#FF0000'>" + matchTimeLabel->text() + "</span> - Error: Failed to call the API");
    }

    reply->deleteLater();
}

void WatchMatchDialog::sendScoreToArduino(int scoreA, int scoreB) {
    if (goalArduino->getSerial()->isOpen()) {
        QString scoreCommand = QString("SCORE:%1,%2\n").arg(scoreA).arg(scoreB);
        goalArduino->write_to_arduino(scoreCommand.toUtf8());
        qDebug() << "Sent to Goal Arduino:" << scoreCommand.trimmed();
        QThread::msleep(100);
    } else {
        qDebug() << "Goal Arduino port is closed, cannot send score";
    }
}