#ifndef STATSWIDGET_H
#define STATSWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include <QTimer>
#include <QToolTip>
#include <QPdfWriter>
#include <QFileDialog>
#include <QMessageBox> // Added for QMessageBox

class UserWindow; // Forward declare

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
    QString hoveredAgeSlice;  // Track hovered age category
    QString hoveredRoleSlice; // Track hovered role
    QString selectedAgeSlice; // Track clicked age category
    QString selectedRoleSlice;// Track clicked role
    QRect agePieRect;        // Store pie chart rectangle for age
    QRect rolePieRect;       // Store pie chart rectangle for role
    QRect tableRect;         // Store table rectangle
    QMap<QString, QLinearGradient> ageGradients; // Gradients for age slices
    QMap<QString, QLinearGradient> roleGradients;// Gradients for role slices
    QTimer *animationTimer;  // For hover/click animations
    float ageSliceScale[4];  // Scale factors for age slices (<25, 25-35, 36-45, >45)
    float roleSliceScale[10]; // Scale factors for role slices (up to 10 roles)
    int sortColumn;          // Track table sorting column
    bool sortAscending;      // Track sort order

    bool isPointInSlice(const QPoint &point, const QRect &pieRect, double startAngle, double spanAngle);
    void updateSliceScales();
    void exportToPDF();
    void sortTableData(QList<QMap<QString, QString>> &tableData);
};

#endif // STATSWIDGET_H
