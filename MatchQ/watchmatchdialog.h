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
#include <cstdlib> // For srand and rand
#include <ctime> // For time(nullptr)
#include "arduino.h"

class QLabel;
class QTextEdit;

// Custom widget for sun animation (unchanged)
class SunWidget : public QWidget {
    Q_OBJECT
public:
    SunWidget(QWidget *parent = nullptr) : QWidget(parent), sunOpacity(0.5) {
        setAttribute(Qt::WA_TransparentForMouseEvents); // Ignore mouse events
        srand(static_cast<unsigned>(time(nullptr))); // Seed random generator
        clouds.resize(5); // Reduced number of clouds for performance
        for (auto &cloud : clouds) {
            cloud.x = rand() % width();
            cloud.y = (rand() % (height() / 2)) + (height() / 4); // Clouds in middle half
            cloud.size = (rand() % 30) + 20; // Base size range 20-50
            cloud.speed = (rand() % 5) + 2; // Speed range 2-7
            cloud.opacity = (rand() % 50) + 50; // Opacity range 50-100
            cloud.scale = 1.0;
            cloud.scaleDirection = (rand() % 2) ? 1 : -1;
        }
        // Pulsating sun animation
        opacityDirection = 1;
        // Light rays
        rays.resize(8);
        for (auto &ray : rays) {
            ray.angle = (rand() % 360);
            ray.opacity = 0;
            ray.opacityDirection = (rand() % 2) ? 1 : -1;
        }
    }

protected:
    void paintEvent(QPaintEvent *) override {
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing);

        // Sun with halo and pulsating opacity
        int sunRadius = width() / 2;
        QRadialGradient sunGradient(width() / 2, height() / 3, sunRadius);
        sunGradient.setColorAt(0, QColor(255, 255, 100, sunOpacity * 255));
        sunGradient.setColorAt(0.2, QColor(255, 215, 0, sunOpacity * 255 * 0.6));
        sunGradient.setColorAt(0.4, QColor(255, 165, 0, sunOpacity * 255 * 0.4));
        sunGradient.setColorAt(1, Qt::transparent);
        painter.setBrush(sunGradient);
        painter.setPen(Qt::NoPen);
        painter.drawEllipse(QPoint(width() / 2, height() / 3), sunRadius, sunRadius);

        // Sun halo
        QRadialGradient haloGradient(width() / 2, height() / 3, sunRadius * 1.2);
        haloGradient.setColorAt(0, Qt::transparent);
        haloGradient.setColorAt(0.8, QColor(255, 215, 0, sunOpacity * 255 * 0.2));
        haloGradient.setColorAt(1, Qt::transparent);
        painter.setBrush(haloGradient);
        painter.drawEllipse(QPoint(width() / 2, height() / 3), static_cast<int>(sunRadius * 1.2), static_cast<int>(sunRadius * 1.2));

        // Light rays
        for (const auto &ray : rays) {
            painter.setPen(QPen(QColor(255, 255, 100, ray.opacity), 1));
            double rad = ray.angle * M_PI / 180.0;
            int x1 = width() / 2 + static_cast<int>(cos(rad) * sunRadius);
            int y1 = height() / 3 + static_cast<int>(sin(rad) * sunRadius);
            int x2 = width() / 2 + static_cast<int>(cos(rad) * sunRadius * 1.5);
            int y2 = height() / 3 + static_cast<int>(sin(rad) * sunRadius * 1.5);
            painter.drawLine(x1, y1, x2, y2);
        }

        // Draw clouds
        for (const auto &cloud : clouds) {
            painter.setPen(Qt::NoPen);
            painter.setBrush(QColor(240, 240, 245, cloud.opacity)); // Light grayish-white
            // Draw fluffy cloud with overlapping circles
            int scaledSize = static_cast<int>(cloud.size * cloud.scale);
            painter.drawEllipse(cloud.x, cloud.y, scaledSize, static_cast<int>(scaledSize * 0.6));
            painter.drawEllipse(cloud.x + static_cast<int>(scaledSize * 0.5), cloud.y - static_cast<int>(scaledSize * 0.2), static_cast<int>(scaledSize * 0.8), static_cast<int>(scaledSize * 0.5));
            painter.drawEllipse(cloud.x - static_cast<int>(scaledSize * 0.5), cloud.y + static_cast<int>(scaledSize * 0.1), static_cast<int>(scaledSize * 0.7), static_cast<int>(scaledSize * 0.4));
        }
    }

public slots:
    void updateSunAndClouds() {
        // Update sun opacity for pulsating effect
        sunOpacity += opacityDirection * 0.01;
        if (sunOpacity >= 0.6) {
            sunOpacity = 0.6;
            opacityDirection = -1;
        } else if (sunOpacity <= 0.4) {
            sunOpacity = 0.4;
            opacityDirection = 1;
        }

        // Update light rays
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

        // Update cloud positions and scaling
        for (auto &cloud : clouds) {
            cloud.x += cloud.speed;
            cloud.y += (rand() % 3) - 1; // Slight vertical drift
            cloud.scale += cloud.scaleDirection * 0.005;
            if (cloud.scale >= 1.2) {
                cloud.scale = 1.2;
                cloud.scaleDirection = -1;
            } else if (cloud.scale <= 0.8) {
                cloud.scale = 0.8;
                cloud.scaleDirection = 1;
            }
            if (cloud.x > width()) {
                cloud.x = -cloud.size * 1.5; // Account for cloud width
                cloud.y = (rand() % (height() / 2)) + (height() / 4);
                cloud.size = (rand() % 30) + 20;
                cloud.speed = (rand() % 5) + 2;
                cloud.opacity = (rand() % 50) + 50;
                cloud.scale = 1.0;
                cloud.scaleDirection = (rand() % 2) ? 1 : -1;
            }
        }
        update(); // Repaint
    }

private:
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
    QVector<Cloud> clouds;
    QVector<Ray> rays;
    double sunOpacity;
    int opacityDirection;
};

// Custom widget for rain animation
class RainWidget : public QWidget {
    Q_OBJECT
public:
    RainWidget(QWidget *parent = nullptr) : QWidget(parent) {
        setAttribute(Qt::WA_TransparentForMouseEvents); // Ignore mouse events
        srand(static_cast<unsigned>(time(nullptr))); // Seed random generator
        raindrops.resize(150); // Increased for denser rain
        for (auto &drop : raindrops) {
            drop.x = rand() % 700; // Fixed width for even distribution (dialog width is 700)
            drop.y = -(rand() % height()); // Start above the screen
            drop.speed = (rand() % 20) + 20; // Speed range 20-40 for more intense rain
            drop.length = (rand() % 15) + 5; // Length range 5-20
            drop.thickness = (rand() % 3) + 1; // Thickness range 1-3
            drop.opacity = (rand() % 80) + 50; // Opacity range 50-130
            drop.angle = 0; // Perpendicular rain (straight down)
            drop.layer = (rand() % 2); // 0 for background, 1 for foreground
        }
    }

protected:
    void paintEvent(QPaintEvent *) override {
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing);

        // Draw background layer (slower, less opaque drops)
        for (const auto &drop : raindrops) {
            if (drop.layer == 0) {
                int adjustedOpacity = drop.opacity * 0.6; // Slightly less opaque for background
                adjustedOpacity = qBound(0, adjustedOpacity * (drop.y + height() / 2) / (height() / 2), 255); // Faster fade-in
                QLinearGradient gradient(drop.x, drop.y, drop.x, drop.y + drop.length);
                gradient.setColorAt(0, QColor(100, 150, 200, adjustedOpacity / 3));
                gradient.setColorAt(0.3, QColor(100, 150, 200, adjustedOpacity));
                gradient.setColorAt(0.7, QColor(100, 150, 200, adjustedOpacity));
                gradient.setColorAt(1, QColor(100, 150, 200, adjustedOpacity / 3));
                painter.setPen(QPen(QBrush(gradient), drop.thickness));
                painter.drawLine(drop.x, drop.y, drop.x, drop.y + drop.length); // Perpendicular
            }
        }

        // Draw foreground layer (faster, more opaque drops)
        for (const auto &drop : raindrops) {
            if (drop.layer == 1) {
                int adjustedOpacity = drop.opacity;
                adjustedOpacity = qBound(0, adjustedOpacity * (drop.y + height() / 2) / (height() / 2), 255); // Faster fade-in
                QLinearGradient gradient(drop.x, drop.y, drop.x, drop.y + drop.length);
                gradient.setColorAt(0, QColor(100, 150, 200, adjustedOpacity / 3));
                gradient.setColorAt(0.3, QColor(100, 150, 200, adjustedOpacity));
                gradient.setColorAt(0.7, QColor(100, 150, 200, adjustedOpacity));
                gradient.setColorAt(1, QColor(100, 150, 200, adjustedOpacity / 3));
                painter.setPen(QPen(QBrush(gradient), drop.thickness));
                painter.drawLine(drop.x, drop.y, drop.x, drop.y + drop.length); // Perpendicular
            }
        }
    }

public slots:
    void updateRaindrops() {
        for (auto &drop : raindrops) {
            int adjustedSpeed = drop.speed * (drop.layer == 1 ? 1.3 : 0.8); // Foreground faster, background slower
            drop.y += adjustedSpeed;
            if (drop.y > height()) {
                drop.y = -(rand() % height()); // Reset above the screen
                drop.x = rand() % 700; // Fixed width for even distribution (dialog width is 700)
                drop.speed = (rand() % 20) + 20; // Speed range 20-40 for more intense rain
                drop.length = (rand() % 15) + 5; // Length range 5-20
                drop.thickness = (rand() % 3) + 1; // Thickness range 1-3
                drop.opacity = (rand() % 80) + 50; // Opacity range 50-130
                drop.angle = 0; // Perpendicular rain
                drop.layer = (rand() % 2); // Reassign layer
            }
        }
        update(); // Repaint
    }

private:
    struct Raindrop {
        int x, y;
        int speed;
        int length;
        int thickness; // Variable thickness
        int opacity;
        int angle; // Set to 0 for perpendicular rain
        int layer; // 0 for background, 1 for foreground
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
    void updateMatchTime();
    void updateCommentary();
    void updateBackground(int meteo); // Update background based on METEO

private:
    int matchId;
    Arduino *arduino;
    QTimer *sensorTimer;
    QTimer *timeTimer;
    QTimer *commentaryTimer;
    QTimer *rainTimer; // For rain animation
    QTimer *sunTimer; // For sun animation
    QLabel *sensorStatusLabel;
    QLabel *matchTimeLabel;
    QLabel *halfTimeLabel;
    SunWidget *sunWidget; // For sun animation
    RainWidget *rainWidget; // For rain animation
    QTextEdit *commentaryTextEdit;
    QPropertyAnimation *scoreAnimation;
    bool rainDetected;
    bool noRainDetected;
    QDateTime matchStartTime;
    bool isHalfTime;
};

#endif // WATCHMATCHDIALOG_H