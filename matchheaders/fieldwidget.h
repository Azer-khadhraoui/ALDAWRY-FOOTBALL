// fieldwidget.h
#ifndef FIELDWIDGET_H
#define FIELDWIDGET_H

#include <QWidget>
#include <QPainter>

class FieldWidget : public QWidget {
    Q_OBJECT
public:
    explicit FieldWidget(QWidget *parent = nullptr) : QWidget(parent) {
        setFixedSize(1200, 600);
    }

protected:
    void paintEvent(QPaintEvent *) override {
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing);

        // Draw a subtle shadow around the field for depth
        painter.setBrush(QColor(0, 0, 0, 50)); // Semi-transparent black
        painter.setPen(Qt::NoPen);
        painter.drawRect(40, 40, width() - 80, height() - 80);

        // Draw the grass (base green color)
        painter.setBrush(QColor(0, 128, 0)); // Solid green color you liked
        painter.setPen(Qt::NoPen);
        painter.drawRect(50, 50, width() - 100, height() - 100);

        // Draw subtle grass stripes (alternating shades)
        painter.setPen(Qt::NoPen);
        for (int x = 50; x < width() - 50; x += 50) {
            if ((x / 50) % 2 == 0) {
                painter.setBrush(QColor(0, 140, 0, 100)); // Lighter green stripe with slight transparency
            } else {
                painter.setBrush(Qt::NoBrush);
            }
            painter.drawRect(x, 50, 50, height() - 100);
        }

        // Draw the field lines (white, thicker for professionalism)
        painter.setPen(QPen(Qt::white, 3));
        painter.setBrush(Qt::NoBrush);

        // Outer boundary
        painter.drawRect(50, 50, width() - 100, height() - 100);

        // Halfway line
        painter.drawLine(width() / 2, 50, width() / 2, height() - 50);

        // Center circle (larger for better proportion)
        painter.drawEllipse(QPoint(width() / 2, height() / 2), 70, 70);

        // Center spot
        painter.setBrush(Qt::white);
        painter.drawEllipse(QPoint(width() / 2, height() / 2), 4, 4);

        // Center marks on the halfway line
        painter.setBrush(Qt::NoBrush);
        painter.drawLine(width() / 2 - 15, 50, width() / 2 + 15, 50); // Top mark
        painter.drawLine(width() / 2 - 15, height() - 50, width() / 2 + 15, height() - 50); // Bottom mark

        // Penalty areas (left and right, adjusted proportions)
        painter.setBrush(Qt::NoBrush);
        painter.drawRect(50, height() / 2 - 150, 150, 300); // Left penalty area (larger)
        painter.drawRect(width() - 200, height() / 2 - 150, 150, 300); // Right penalty area (larger)

        // Goal areas (left and right, adjusted proportions)
        painter.drawRect(50, height() / 2 - 75, 75, 150); // Left goal area
        painter.drawRect(width() - 125, height() / 2 - 75, 75, 150); // Right goal area

        // Penalty spots (positioned 11 meters from the goal line, scaled)
        painter.setBrush(Qt::white);
        painter.drawEllipse(QPoint(125, height() / 2), 4, 4); // Left penalty spot
        painter.drawEllipse(QPoint(width() - 125, height() / 2), 4, 4); // Right penalty spot

        // Corner flags (small orange triangles)
        painter.setBrush(QColor(255, 165, 0)); // Orange color for flags
        QPolygon topLeftFlag;
        topLeftFlag << QPoint(50, 50) << QPoint(65, 50) << QPoint(50, 65);
        painter.drawPolygon(topLeftFlag);

        QPolygon topRightFlag;
        topRightFlag << QPoint(width() - 50, 50) << QPoint(width() - 65, 50) << QPoint(width() - 50, 65);
        painter.drawPolygon(topRightFlag);

        QPolygon bottomLeftFlag;
        bottomLeftFlag << QPoint(50, height() - 50) << QPoint(65, height() - 50) << QPoint(50, height() - 65);
        painter.drawPolygon(bottomLeftFlag);

        QPolygon bottomRightFlag;
        bottomRightFlag << QPoint(width() - 50, height() - 50) << QPoint(width() - 65, height() - 50) << QPoint(width() - 50, height() - 65);
        painter.drawPolygon(bottomRightFlag);

        // Goals with a net effect
        painter.setPen(QPen(Qt::white, 2));
        painter.setBrush(Qt::white);
        QPolygon leftGoal;
        leftGoal << QPoint(50, height() / 2 - 40) // Larger goal
                 << QPoint(35, height() / 2 - 40)
                 << QPoint(35, height() / 2 + 40)
                 << QPoint(50, height() / 2 + 40);
        painter.drawPolygon(leftGoal);
        // Net effect (crosshatch pattern)
        painter.setPen(QPen(QColor(200, 200, 200), 1)); // Light gray for the net
        for (int i = 0; i < 6; i++) {
            painter.drawLine(35 + i * 3, height() / 2 - 40, 35 + i * 3, height() / 2 + 40);
            painter.drawLine(35, height() / 2 - 40 + i * 13, 50, height() / 2 - 40 + i * 13);
        }

        QPolygon rightGoal;
        rightGoal << QPoint(width() - 50, height() / 2 - 40)
                  << QPoint(width() - 35, height() / 2 - 40)
                  << QPoint(width() - 35, height() / 2 + 40)
                  << QPoint(width() - 50, height() / 2 + 40);
        painter.drawPolygon(rightGoal);
        // Net effect (crosshatch pattern)
        for (int i = 0; i < 6; i++) {
            painter.drawLine(width() - 35 - i * 3, height() / 2 - 40, width() - 35 - i * 3, height() / 2 + 40);
            painter.drawLine(width() - 50, height() / 2 - 40 + i * 13, width() - 35, height() / 2 - 40 + i * 13);
        }
    }
};

#endif // FIELDWIDGET_H