#ifndef STATSWIDGET_H
#define STATSWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include <QTimer>
#include <QToolTip>
#include <QPdfWriter>
#include <QFileDialog>
#include <QMessageBox>

class UserWindow;

class statsWidget : public QWidget {
public:
    explicit statsWidget(UserWindow *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;

private:
    UserWindow *userWindow;
    QString hoveredAgeSlice;
    QString hoveredRoleSlice;
    QString selectedAgeSlice;
    QString selectedRoleSlice;
    QRect agePieRect;
    QRect rolePieRect;
    QRect tableRect;
    QMap<QString, QLinearGradient> ageGradients;
    QMap<QString, QLinearGradient> roleGradients;
    QTimer *animationTimer;
    float ageSliceScale[4];
    float roleSliceScale[10];
    int sortColumn;
    bool sortAscending;

    bool isPointInSlice(const QPoint &point, const QRect &pieRect, double startAngle, double spanAngle);
    void updateSliceScales();
    void exportToPDF();
    void sortTableData(QList<QMap<QString, QString>> &tableData);
    QPointF getSliceCenterPoint(const QRect &rect, double startAngle, double spanAngle); // Add this declaration
};

#endif // STATSWIDGET_H
