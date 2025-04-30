#ifndef WATCHMATCHDIALOG_H
#define WATCHMATCHDIALOG_H

#include <QDialog>
#include <QTimer>
#include <QDateTime>
#include <QPropertyAnimation>
#include <QWidget>
#include <QPainter>
#include <QVector>
#include <QTime>
#include <cstdlib>
#include <ctime>
#include <QStackedWidget>
#include "arduino.h"

class QLabel;
class QTextEdit;

class SkyWidget : public QWidget {
    Q_OBJECT
public:
    SkyWidget(QWidget *parent = nullptr, bool isDay = true) 
        : QWidget(parent), isDay(isDay), sunMoonOpacity(0.5) {
        setAttribute(Qt::WA_TransparentForMouseEvents);
        srand(static_cast<unsigned>(time(nullptr)));
        
        if (isDay) {
            clouds.resize(5);
            for (auto &cloud : clouds) {
                cloud.x = rand() % width();
                cloud.y = (rand() % (height() / 2)) + (height() / 4);
                cloud.size = (rand() % 30) + 20;
                cloud.speed = (rand() % 5) + 2;
                cloud.opacity = (rand() % 50) + 50;
                cloud.scale = 1.0;
                cloud.scaleDirection = (rand() % 2) ? 1 : -1;
            }
            rays.resize(8);
            for (auto &ray : rays) {
                ray.angle = (rand() % 360);
                ray.opacity = 0;
                ray.opacityDirection = (rand() % 2) ? 1 : -1;
            }
        } else {
            stars.resize(50);
            for (auto &star : stars) {
                star.x = rand() % width();
                star.y = rand() % (height() * 3 / 4);
                star.size = (rand() % 3) + 1;
                star.opacity = (rand() % 100) + 50;
                star.twinkleSpeed = (rand() % 5) + 1;
                star.twinkleDirection = (rand() % 2) ? 1 : -1;
            }
        }
        opacityDirection = 1;
    }

protected:
    void paintEvent(QPaintEvent *) override {
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing);

        int celestialRadius = width() / 2;
        QPoint center(width() / 2, height() / 3);

        if (isDay) {
            QRadialGradient sunGradient(center, celestialRadius);
            sunGradient.setColorAt(0, QColor(255, 255, 100, sunMoonOpacity * 255));
            sunGradient.setColorAt(0.2, QColor(255, 215, 0, sunMoonOpacity * 255 * 0.6));
            sunGradient.setColorAt(0.4, QColor(255, 165, 0, sunMoonOpacity * 255 * 0.4));
            sunGradient.setColorAt(1, Qt::transparent);
            painter.setBrush(sunGradient);
            painter.setPen(Qt::NoPen);
            painter.drawEllipse(center, celestialRadius, celestialRadius);

            QRadialGradient haloGradient(center, celestialRadius * 1.2);
            haloGradient.setColorAt(0, Qt::transparent);
            haloGradient.setColorAt(0.8, QColor(255, 215, 0, sunMoonOpacity * 255 * 0.2));
            haloGradient.setColorAt(1, Qt::transparent);
            painter.setBrush(haloGradient);
            painter.drawEllipse(center, static_cast<int>(celestialRadius * 1.2), static_cast<int>(celestialRadius * 1.2));

            for (const auto &ray : rays) {
                painter.setPen(QPen(QColor(255, 255, 100, ray.opacity), 1));
                double rad = ray.angle * M_PI / 180.0;
                int x1 = center.x() + static_cast<int>(cos(rad) * celestialRadius);
                int y1 = center.y() + static_cast<int>(sin(rad) * celestialRadius);
                int x2 = center.x() + static_cast<int>(cos(rad) * celestialRadius * 1.5);
                int y2 = center.y() + static_cast<int>(sin(rad) * celestialRadius * 1.5);
                painter.drawLine(x1, y1, x2, y2);
            }

            for (const auto &cloud : clouds) {
                painter.setPen(Qt::NoPen);
                painter.setBrush(QColor(240, 240, 245, cloud.opacity));
                int scaledSize = static_cast<int>(cloud.size * cloud.scale);
                painter.drawEllipse(cloud.x, cloud.y, scaledSize, static_cast<int>(scaledSize * 0.6));
                painter.drawEllipse(cloud.x + static_cast<int>(scaledSize * 0.5), cloud.y - static_cast<int>(scaledSize * 0.2), static_cast<int>(scaledSize * 0.8), static_cast<int>(scaledSize * 0.5));
                painter.drawEllipse(cloud.x - static_cast<int>(scaledSize * 0.5), cloud.y + static_cast<int>(scaledSize * 0.1), static_cast<int>(scaledSize * 0.7), static_cast<int>(scaledSize * 0.4));
            }
        } else {
            QRadialGradient moonGradient(center, celestialRadius);
            moonGradient.setColorAt(0, QColor(220, 220, 220, sunMoonOpacity * 255));
            moonGradient.setColorAt(0.2, QColor(200, 200, 200, sunMoonOpacity * 255 * 0.8));
            moonGradient.setColorAt(0.4, QColor(180, 180, 180, sunMoonOpacity * 255 * 0.5));
            moonGradient.setColorAt(1, Qt::transparent);
            painter.setBrush(moonGradient);
            painter.setPen(Qt::NoPen);
            painter.drawEllipse(center, celestialRadius, celestialRadius);

            QRadialGradient glowGradient(center, celestialRadius * 1.2);
            glowGradient.setColorAt(0, Qt::transparent);
            glowGradient.setColorAt(0.8, QColor(200, 200, 200, sunMoonOpacity * 255 * 0.3));
            glowGradient.setColorAt(1, Qt::transparent);
            painter.setBrush(glowGradient);
            painter.drawEllipse(center, static_cast<int>(celestialRadius * 1.2), static_cast<int>(celestialRadius * 1.2));

            for (const auto &star : stars) {
                painter.setPen(Qt::NoPen);
                painter.setBrush(QColor(255, 255, 255, star.opacity));
                painter.drawEllipse(star.x, star.y, star.size, star.size);
            }
        }
    }

public slots:
    void updateSky() {
        sunMoonOpacity += opacityDirection * 0.01;
        if (sunMoonOpacity >= 0.6) {
            sunMoonOpacity = 0.6;
            opacityDirection = -1;
        } else if (sunMoonOpacity <= 0.4) {
            sunMoonOpacity = 0.4;
            opacityDirection = 1;
        }

        if (isDay) {
            for (auto &ray : rays) {
                ray.opacity += ray.opacityDirection * 5;
                if (ray.opacity >= 100) {
                    ray.opacity = 100;
                    ray.opacityDirection = -1;
                } else if (ray.opacity <= 0) {
                    ray.opacity = 0;
                    ray.opacityDirection = 1;
                }
            }

            for (auto &cloud : clouds) {
                cloud.x += cloud.speed;
                cloud.y += (rand() % 3) - 1;
                cloud.scale += cloud.scaleDirection * 0.005;
                if (cloud.scale >= 1.2) {
                    cloud.scale = 1.2;
                    cloud.scaleDirection = -1;
                } else if (cloud.scale <= 0.8) {
                    cloud.scale = 0.8;
                    cloud.scaleDirection = 1;
                }
                if (cloud.x > width()) {
                    cloud.x = -cloud.size * 1.5;
                    cloud.y = (rand() % (height() / 2)) + (height() / 4);
                    cloud.size = (rand() % 30) + 20;
                    cloud.speed = (rand() % 5) + 2;
                    cloud.opacity = (rand() % 50) + 50;
                    cloud.scale = 1.0;
                    cloud.scaleDirection = (rand() % 2) ? 1 : -1;
                }
            }
        } else {
            for (auto &star : stars) {
                star.opacity += star.twinkleDirection * star.twinkleSpeed;
                if (star.opacity >= 200) {
                    star.opacity = 200;
                    star.twinkleDirection = -1;
                } else if (star.opacity <= 50) {
                    star.opacity = 50;
                    star.twinkleDirection = 1;
                }
            }
        }
        update();
    }

private:
    bool isDay;
    struct Cloud {
        int x, y;
        int size;
        int speed;
        int opacity;
        double scale;
        int scaleDirection;
    };
    struct Ray {
        int angle;
        int opacity;
        int opacityDirection;
    };
    struct Star {
        int x, y;
        int size;
        int opacity;
        int twinkleSpeed;
        int twinkleDirection;
    };
    QVector<Cloud> clouds;
    QVector<Ray> rays;
    QVector<Star> stars;
    double sunMoonOpacity;
    int opacityDirection;
};

class RainWidget : public QWidget {
    Q_OBJECT
public:
    RainWidget(QWidget *parent = nullptr) : QWidget(parent) {
        setAttribute(Qt::WA_TransparentForMouseEvents);
        srand(static_cast<unsigned>(time(nullptr)));
        raindrops.resize(150);
        for (auto &drop : raindrops) {
            drop.x = rand() % 1000;
            drop.y = -(rand() % height());
            drop.speed = (rand() % 20) + 20;
            drop.length = (rand() % 15) + 5;
            drop.thickness = (rand() % 3) + 1;
            drop.opacity = (rand() % 80) + 50;
            drop.angle = 0;
            drop.layer = (rand() % 2);
        }
    }

protected:
    void paintEvent(QPaintEvent *) override {
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing);

        for (const auto &drop : raindrops) {
            if (drop.layer == 0) {
                int adjustedOpacity = drop.opacity * 0.6;
                adjustedOpacity = qBound(0, adjustedOpacity * (drop.y + height() / 2) / (height() / 2), 255);
                QLinearGradient gradient(drop.x, drop.y, drop.x, drop.y + drop.length);
                gradient.setColorAt(0, QColor(100, 150, 200, adjustedOpacity / 3));
                gradient.setColorAt(0.3, QColor(100, 150, 200, adjustedOpacity));
                gradient.setColorAt(0.7, QColor(100, 150, 200, adjustedOpacity));
                gradient.setColorAt(1, QColor(100, 150, 200, adjustedOpacity / 3));
                painter.setPen(QPen(QBrush(gradient), drop.thickness));
                painter.drawLine(drop.x, drop.y, drop.x, drop.y + drop.length);
            }
        }

        for (const auto &drop : raindrops) {
            if (drop.layer == 1) {
                int adjustedOpacity = drop.opacity;
                adjustedOpacity = qBound(0, adjustedOpacity * (drop.y + height() / 2) / (height() / 2), 255);
                QLinearGradient gradient(drop.x, drop.y, drop.x, drop.y + drop.length);
                gradient.setColorAt(0, QColor(100, 150, 200, adjustedOpacity / 3));
                gradient.setColorAt(0.3, QColor(100, 150, 200, adjustedOpacity));
                gradient.setColorAt(0.7, QColor(100, 150, 200, adjustedOpacity));
                gradient.setColorAt(1, QColor(100, 150, 200, adjustedOpacity / 3));
                painter.setPen(QPen(QBrush(gradient), drop.thickness));
                painter.drawLine(drop.x, drop.y, drop.x, drop.y + drop.length);
            }
        }
    }

public slots:
    void updateRaindrops() {
        for (auto &drop : raindrops) {
            int adjustedSpeed = drop.speed * (drop.layer == 1 ? 1.3 : 0.8);
            drop.y += adjustedSpeed;
            if (drop.y > height()) {
                drop.y = -(rand() % height());
                drop.x = rand() % 1000;
                drop.speed = (rand() % 20) + 20;
                drop.length = (rand() % 15) + 5;
                drop.thickness = (rand() % 3) + 1;
                drop.opacity = (rand() % 80) + 50;
                drop.angle = 0;
                drop.layer = (rand() % 2);
            }
        }
        update();
    }

private:
    struct Raindrop {
        int x, y;
        int speed;
        int length;
        int thickness;
        int opacity;
        int angle;
        int layer;
    };
    QVector<Raindrop> raindrops;
};

class WatchMatchDialog : public QDialog
{
    Q_OBJECT

public:
    WatchMatchDialog(int matchId, QWidget *parent = nullptr);
    ~WatchMatchDialog();

protected:
    void accept() override;

private slots:
    void readSensorData();
    void readGoalData();
    void updateMatchTime();
    void updateCommentary();
    void updateBackground(int meteo);
    void showMatchView();
    void showLineupView();
    void runPythonScript();
    void updateTranscription();

private:
    void setupLineupView();
    void sendScoreToArduino(int scoreA, int scoreB);

    int matchId;
    Arduino *weatherArduino;
    Arduino *goalArduino;
    QTimer *sensorTimer;
    QTimer *goalTimer;
    QTimer *timeTimer;
    QTimer *commentaryTimer;
    QTimer *rainTimer;
    QTimer *skyTimer;
    QLabel *sensorStatusLabel;
    QLabel *goalStatusLabel;
    QLabel *matchTimeLabel;
    QLabel *halfTimeLabel;
    QLabel *team1Label;
    QLabel *team2Label;
    SkyWidget *skyWidget;
    RainWidget *rainWidget;
    QTextEdit *commentaryTextEdit;
    QPropertyAnimation *scoreAnimation;
    bool rainDetected;
    bool noRainDetected;
    QDateTime matchStartTime;
    bool isHalfTime;
    int teamAId;
    int teamBId;
    QStackedWidget *stackedWidget;
    QWidget *matchWidget;
    QWidget *lineupWidget;
};

#endif // WATCHMATCHDIALOG_H