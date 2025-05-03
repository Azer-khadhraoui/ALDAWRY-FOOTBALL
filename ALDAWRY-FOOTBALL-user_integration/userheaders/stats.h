// stats.h
#ifndef STATS_H
#define STATS_H

#include <QWidget>
#include <QMap>
#include <QTimer>
#include <QStringList>

class QPaintEvent;
class QMouseEvent;

class Stats : public QWidget {
    Q_OBJECT

public:
    Stats(QWidget *parent = nullptr);
    ~Stats();
    QSize sizeHint() const override; // Add sizeHint to suggest widget size

protected:
    void paintEvent(QPaintEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;

private slots:
    void updateSliceScales();
    void exportToPDF();

private:
    QMap<QString, QRect> ageSliceRects;
    QMap<QString, QRect> roleSliceRects;
    QMap<QString, QLinearGradient> ageGradients;
    QMap<QString, QLinearGradient> roleGradients;
    QMap<QString, int> ageCategories;
    QMap<QString, int> roleCount;
    QMap<QString, QMap<QString, int>> roleByAge;
    QRect agePieRect;
    QRect rolePieRect;
    QRect tableRect;
    QString hoveredAgeSlice;
    QString hoveredRoleSlice;
    QString selectedAgeSlice;
    QString selectedRoleSlice;
    int sortColumn;
    bool sortAscending;
    int totalEmployees;
    QTimer *animationTimer;
    float ageSliceScale[4];
    float roleSliceScale[10];
    QMap<QString, QRect> ageLegendRects;
    QMap<QString, QRect> roleLegendRects;
    int hoveredRow;

    void computeStatistics();
    bool isPointInSlice(const QPoint &point, const QRect &pieRect, double startAngle, double spanAngle);
    void sortTableData(QList<QMap<QString, QString>> &tableData);
    QPointF getSliceCenterPoint(const QRect &rect, double startAngle, double spanAngle);
};

#endif // STATS_H
