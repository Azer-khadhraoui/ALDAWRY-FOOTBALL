#include "../userheaders/stats.h"
#include <QDebug>
#include <cmath>
#include <QVBoxLayout>
#include <QPushButton>
#include <QMessageBox>
#include <QPdfWriter>
#include <QFileDialog>
#include <QMouseEvent>
#include <QToolTip>
#include <QPainter>
#include <QPen>
#include "../userheaders/user.h"

Stats::Stats(QWidget *parent)
    : QWidget(parent),
    hoveredAgeSlice(""),
    hoveredRoleSlice(""),
    selectedAgeSlice(""),
    selectedRoleSlice(""),
    sortColumn(-1),
    sortAscending(true),
    totalEmployees(0),
    hoveredRow(-1) {
    setMouseTracking(true);

    for (int i = 0; i < 4; ++i) ageSliceScale[i] = 1.0;
    for (int i = 0; i < 10; ++i) roleSliceScale[i] = 1.0;

    computeStatistics();

    animationTimer = new QTimer(this);
    connect(animationTimer, &QTimer::timeout, this, &Stats::updateSliceScales);
    animationTimer->start(50);

    QVBoxLayout *layout = new QVBoxLayout(this);
    QPushButton *exportButton = new QPushButton("Export to PDF", this);
    exportButton->setStyleSheet("background-color: #4CAF50; color: white; padding: 5px; border-radius: 3px;");
    connect(exportButton, &QPushButton::clicked, this, &Stats::exportToPDF);
    layout->addWidget(exportButton, 0, Qt::AlignRight);
    layout->addStretch();
}

Stats::~Stats() {
    delete animationTimer;
}

void Stats::computeStatistics() {
    totalEmployees = 0;
    ageCategories.clear();
    roleCount.clear();
    roleByAge.clear();

    QList<Employee> employees = Employee::getAllEmployees();
    qDebug() << "Number of employees fetched for stats:" << employees.size();

    totalEmployees = employees.size();
    if (totalEmployees == 0) {
        qDebug() << "No employees found in the database.";
        return;
    }

    ageCategories["<20"] = 0;
    ageCategories["20-30"] = 0;
    ageCategories["30-40"] = 0;
    ageCategories[">40"] = 0;

    QStringList roles = {"Admin", "Coach", "Employee"};
    for (const QString &ageCat : ageCategories.keys()) {
        for (const QString &role : roles) {
            roleByAge[ageCat][role] = 0;
        }
    }

    int invalidAgeCount = 0;
    for (const Employee &emp : employees) {
        int age = emp.getAge();
        qDebug() << "Employee ID:" << emp.getId() << "DOB:" << emp.getDateOfBirth().toString("yyyy-MM-dd") << "Age:" << age;

        QString ageCat;
        if (age == -1) {
            qDebug() << "Employee ID:" << emp.getId() << "has invalid DOB:" << emp.getDateOfBirth().toString("yyyy-MM-dd");
            invalidAgeCount++;
            continue;
        } else if (age < 20) {
            ageCat = "<20";
        } else if (age >= 20 && age <= 30) {
            ageCat = "20-30";
        } else if (age > 30 && age <= 40) {
            ageCat = "30-40";
        } else {
            ageCat = ">40";
        }

        ageCategories[ageCat]++;
        QString role = emp.getRole();
        roleCount[role]++;
        roleByAge[ageCat][role]++;
        qDebug() << "Employee ID:" << emp.getId() << "Category:" << ageCat << "Role:" << role;
    }

    if (invalidAgeCount > 0) {
        qDebug() << "Warning:" << invalidAgeCount << "employees have invalid DOBs and were excluded.";
        QMessageBox::warning(this, "Data Issue", QString("%1 employees have invalid dates of birth and were excluded from statistics.").arg(invalidAgeCount));
    }

    qDebug() << "Age Categories:" << ageCategories;
    qDebug() << "Role Counts:" << roleCount;
    qDebug() << "Role by Age:" << roleByAge;
}

void Stats::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // Set background gradient
    QLinearGradient bgGradient(0, 0, 0, height());
    bgGradient.setColorAt(0, QColor(20, 20, 30));
    bgGradient.setColorAt(1, QColor(40, 40, 50));
    painter.fillRect(rect(), bgGradient);

    // If no employees, display message and return
    if (totalEmployees == 0) {
        painter.setFont(QFont("Segoe UI", 14));
        painter.setPen(Qt::white);
        painter.drawText(rect(), Qt::AlignCenter, "No employee data available to display statistics.");
        return;
    }

    // Layout constants
    int chartWidth = 300; // Fixed width for charts
    int chartHeight = chartWidth;
    int legendWidth = 80;
    int tableWidth = 400; // Fixed width for the table
    int rowHeight = 40;
    int yPos = 60;
    int sectionSpacing = 80;

    int totalChartWidth = chartWidth + legendWidth + 5;
    int totalWidth = totalChartWidth * 2 + tableWidth + sectionSpacing * 2;
    int leftOffset = (width() - totalWidth) / 2;

    // Font settings
    QFont titleFont("Segoe UI", 16, QFont::Bold);
    QFont subtitleFont("Segoe UI", 11, QFont::Bold);
    QFont textFont("Segoe UI", 10);
    QFont legendFont("Segoe UI", 8);
    QFont labelFont("Segoe UI", 8, QFont::Bold);

    // Age category order and colors
    QStringList ageOrder = {"<20", ">40", "30-40", "20-30"};
    QList<QColor> baseColors = {
        QColor("#00CED1"), // Cyan for "20-30"
        QColor("#FF69B4"), // Pink for "30-40"
        QColor("#FFD700"), // Gold for ">40"
        QColor("#FF4500")  // Orange for "<20"
    };

    // Initialize age gradients
    ageGradients.clear();
    int colorIndex = 0;
    for (const QString &cat : ageOrder) {
        QColor base = baseColors[colorIndex % baseColors.size()];
        QLinearGradient gradient(0, 0, chartWidth, chartHeight);
        gradient.setColorAt(0, base.lighter(110));
        gradient.setColorAt(1, base.darker(110));
        ageGradients[cat] = gradient;
        colorIndex++;
    }

    // Initialize role gradients
    roleGradients.clear();
    colorIndex = 0;
    QStringList roleOrder = {"Employee", "Coach", "Admin"};
    for (const QString &role : roleOrder) {
        if (!roleCount.contains(role) || roleCount[role] == 0) continue;
        QColor base = baseColors[colorIndex % baseColors.size()];
        QLinearGradient gradient(0, 0, chartWidth, chartHeight);
        gradient.setColorAt(0, base.lighter(110));
        gradient.setColorAt(1, base.darker(110));
        roleGradients[role] = gradient;
        colorIndex++;
    }

    // Draw title
    painter.setFont(titleFont);
    painter.setPen(QColor("#00CED1"));
    painter.drawText(QRect(0, yPos - 40, width(), 30), Qt::AlignCenter, "Employee Statistics");
    painter.setFont(QFont("Segoe UI", 12, QFont::Bold));
    painter.setPen(Qt::white);
    painter.drawText(QRect(0, yPos - 20, width(), 30), Qt::AlignCenter,
                     QString("(Total: %1)").arg(totalEmployees));
    yPos += 10;

    // Draw Age Distribution Pie Chart
    painter.setFont(subtitleFont);
    painter.drawText(leftOffset, yPos, "Age Distribution");
    yPos += 20;

    agePieRect = QRect(leftOffset, yPos, chartWidth, chartHeight);
    double startAngle = 0;

    // Draw shadow for age pie chart
    painter.setPen(Qt::NoPen);
    painter.setBrush(QColor(0, 0, 0, 50));
    painter.drawEllipse(agePieRect.adjusted(3, 3, 3, 3));

    QMap<QString, double> ageAngles;
    QMap<QString, int> ageIndices;
    int ageIndex = 0;
    for (const QString &cat : ageOrder) {
        int value = ageCategories[cat];
        if (value == 0) continue;

        ageIndices[cat] = ageIndex;
        ageAngles[cat] = startAngle;
        double spanAngle = 360.0 * value / totalEmployees;
        painter.setBrush(ageGradients[cat]);
        painter.setPen(Qt::black);

        bool isHovered = (cat == hoveredAgeSlice);
        bool isSelected = (cat == selectedAgeSlice);
        QRect drawRect = agePieRect;
        float scale = ageSliceScale[ageIndex];
        if (isHovered || isSelected) {
            double midAngle = (startAngle + spanAngle / 2) * M_PI / 180.0;
            int offset = isSelected ? 10 : 8;
            drawRect.translate(offset * cos(midAngle), offset * sin(midAngle));
            drawRect = drawRect.adjusted(-scale * chartWidth / 12, -scale * chartHeight / 12,
                                         scale * chartWidth / 12, scale * chartHeight / 12);
        }

        painter.drawPie(drawRect, startAngle * 16, spanAngle * 16);

        double percentage = (value * 100.0) / totalEmployees;
        QString label = QString("%1%").arg(percentage, 0, 'f', 1);
        QPointF labelPos = getSliceCenterPoint(drawRect, startAngle, spanAngle);
        painter.setFont(labelFont);
        painter.setPen(Qt::white);
        painter.drawText(QRectF(labelPos.x() - 20, labelPos.y() - 8, 40, 16), Qt::AlignCenter, label);

        startAngle += spanAngle;
        ageIndex++;
    }

    // Draw center hole for age pie chart
    painter.setBrush(QColor(20, 20, 30));
    painter.setPen(Qt::NoPen);
    int holeSize = chartWidth * 0.35;
    QRect holeRect(agePieRect.center().x() - holeSize / 2, agePieRect.center().y() - holeSize / 2, holeSize, holeSize);
    painter.drawEllipse(holeRect);

    painter.setFont(textFont);
    painter.setPen(Qt::white);
    painter.drawText(holeRect, Qt::AlignCenter, QString::number(totalEmployees));

    // Draw age legend
    ageLegendRects.clear();
    startAngle = 0;
    colorIndex = 0;
    int ageLegendY = yPos;
    int ageLegendX = leftOffset + chartWidth + 5;
    painter.setFont(legendFont);
    for (const QString &cat : ageOrder) {
        int value = ageCategories[cat];
        double spanAngle = 360.0 * value / totalEmployees;

        painter.setBrush(ageGradients[cat]);
        painter.setPen(Qt::white);
        QRect legendSquare(ageLegendX, ageLegendY, 10, 10);
        painter.drawRoundedRect(legendSquare, 3, 3);
        painter.drawText(ageLegendX + 15, ageLegendY + 9, cat);
        ageLegendRects[cat] = QRect(ageLegendX, ageLegendY, 80, 10);
        ageLegendY += 15;

        startAngle += spanAngle;
        colorIndex++;
    }

    // Draw Role by Age Category Table
    int tableX = leftOffset + totalChartWidth + sectionSpacing;
    int tableY = 60;
    painter.setFont(subtitleFont);
    painter.drawText(tableX, tableY, "Role by Age Category");
    tableY += 20;

    int colWidth = tableWidth / 3;
    int maxRows = ageOrder.size() * roleOrder.size() + 1; // Calculate total rows
    tableRect = QRect(tableX, tableY, tableWidth, rowHeight * maxRows);

    // Draw table shadow
    painter.setPen(Qt::NoPen);
    painter.setBrush(QColor(0, 0, 0, 100));
    painter.drawRoundedRect(tableX + 5, tableY + 5, colWidth * 3, rowHeight * maxRows, 8, 8);

    // Draw table header
    QLinearGradient headerGradient(tableX, tableY, tableX, tableY + rowHeight);
    headerGradient.setColorAt(0, QColor(120, 120, 140));
    headerGradient.setColorAt(1, QColor(90, 90, 110));
    painter.setBrush(headerGradient);
    painter.setPen(QPen(QColor(150, 150, 170), 1));
    painter.drawRoundedRect(tableX, tableY, colWidth * 3, rowHeight, 5, 5);
    painter.setFont(QFont("Segoe UI", 12, QFont::Bold));
    painter.setPen(Qt::white);
    painter.drawText(tableX, tableY, colWidth, rowHeight, Qt::AlignCenter, "Age Category");
    painter.drawText(tableX + colWidth, tableY, colWidth, rowHeight, Qt::AlignCenter, "Role");
    painter.drawText(tableX + 2 * colWidth, tableY, colWidth, rowHeight, Qt::AlignCenter, "Count");
    tableY += rowHeight;

    // Prepare table data
    QList<QMap<QString, QString>> tableData;
    for (const QString &ageCat : ageOrder) {
        for (const QString &role : roleOrder) {
            QMap<QString, QString> row;
            row["Age Category"] = ageCat;
            row["Role"] = role;
            int count = roleByAge[ageCat].value(role, 0);
            row["Count"] = QString::number(count);
            tableData.append(row);
        }
    }

    sortTableData(tableData);

    // Draw table rows (remove filtering to ensure all rows are drawn)
    bool alternate = false;
    int rowIndex = 0;
    for (const auto &row : tableData) {
        // Removed filtering to draw all rows, even with count 0
        // if (selectedAgeSlice != "" && selectedAgeSlice != row["Age Category"]) continue;
        // if (selectedRoleSlice != "" && selectedRoleSlice != row["Role"]) continue;
        bool skipRow = false;
        if (selectedAgeSlice != "" && selectedAgeSlice != row["Age Category"]) {
            skipRow = true;
        }
        if (selectedRoleSlice != "" && selectedRoleSlice != row["Role"]) {
            skipRow = true;
        }
        if (skipRow) continue;

        QLinearGradient rowGradient(tableX, tableY, tableX, tableY + rowHeight);
        if (rowIndex == hoveredRow) {
            rowGradient.setColorAt(0, QColor(90, 90, 110));
            rowGradient.setColorAt(1, QColor(70, 70, 90));
        } else {
            rowGradient.setColorAt(0, alternate ? QColor(60, 60, 70) : QColor(50, 50, 60));
            rowGradient.setColorAt(1, alternate ? QColor(50, 50, 60) : QColor(40, 40, 50));
        }
        painter.setBrush(rowGradient);
        painter.setPen(QPen(QColor(150, 150, 170), 1));
        painter.drawRoundedRect(tableX, tableY, colWidth * 3, rowHeight, 5, 5);

        // Draw table grid lines
        painter.setPen(QPen(QColor(80, 80, 90), 1));
        painter.drawLine(tableX, tableY, tableX + colWidth * 3, tableY);
        if (rowIndex == 0) {
            painter.drawLine(tableX + colWidth, tableY - rowHeight, tableX + colWidth, tableY);
            painter.drawLine(tableX + 2 * colWidth, tableY - rowHeight, tableX + 2 * colWidth, tableY);
        }
        painter.drawLine(tableX + colWidth, tableY, tableX + colWidth, tableY + rowHeight);
        painter.drawLine(tableX + 2 * colWidth, tableY, tableX + 2 * colWidth, tableY + rowHeight);

        // Draw table content
        painter.setPen(Qt::white);
        painter.setFont(textFont);
        painter.drawText(tableX, tableY, colWidth, rowHeight, Qt::AlignCenter, row["Age Category"]);
        painter.drawText(tableX + colWidth, tableY, colWidth, rowHeight, Qt::AlignCenter, row["Role"]);
        painter.drawText(tableX + 2 * colWidth, tableY, colWidth, rowHeight, Qt::AlignCenter, row["Count"]);

        tableY += rowHeight;
        alternate = !alternate;
        rowIndex++;
    }

    // Draw table border
    painter.setPen(QPen(QColor(150, 150, 170), 1));
    painter.setBrush(Qt::NoBrush);
    painter.drawRoundedRect(tableX, tableY - rowHeight * rowIndex, colWidth * 3, rowHeight * (rowIndex + 1), 5, 5);

    // Add extra spacing after the table
    tableY += 100;

    // Draw Role Distribution Pie Chart
    int roleChartX = tableX + tableWidth + sectionSpacing;
    yPos = 60;
    painter.setFont(subtitleFont);
    painter.drawText(roleChartX, yPos, "Role Distribution");
    yPos += 20;

    rolePieRect = QRect(roleChartX, yPos, chartWidth, chartHeight);
    startAngle = 0;

    // Draw shadow for role pie chart
    painter.setPen(Qt::NoPen);
    painter.setBrush(QColor(0, 0, 0, 50));
    painter.drawEllipse(rolePieRect.adjusted(3, 3, 3, 3));

    QMap<QString, double> roleAngles;
    QMap<QString, int> roleIndices;
    int roleIndex = 0;
    for (const QString &role : roleOrder) {
        if (!roleCount.contains(role) || roleCount[role] == 0) continue;

        roleIndices[role] = roleIndex;
        int value = roleCount[role];
        roleAngles[role] = startAngle;
        double spanAngle = 360.0 * value / totalEmployees;
        painter.setBrush(roleGradients[role]);
        painter.setPen(Qt::black);

        bool isHovered = (role == hoveredRoleSlice);
        bool isSelected = (role == selectedRoleSlice);
        QRect drawRect = rolePieRect;
        float scale = roleSliceScale[roleIndex];
        if (isHovered || isSelected) {
            double midAngle = (startAngle + spanAngle / 2) * M_PI / 180.0;
            int offset = isSelected ? 10 : 8;
            drawRect.translate(offset * cos(midAngle), offset * sin(midAngle));
            drawRect = drawRect.adjusted(-scale * chartWidth / 12, -scale * chartHeight / 12,
                                         scale * chartWidth / 12, scale * chartHeight / 12);
        }

        painter.drawPie(drawRect, startAngle * 16, spanAngle * 16);

        double percentage = (value * 100.0) / totalEmployees;
        QString label = QString("%1%").arg(percentage, 0, 'f', 1);
        QPointF labelPos = getSliceCenterPoint(drawRect, startAngle, spanAngle);
        painter.setFont(labelFont);
        painter.setPen(Qt::white);
        painter.drawText(QRectF(labelPos.x() - 20, labelPos.y() - 8, 40, 16), Qt::AlignCenter, label);

        startAngle += spanAngle;
        roleIndex++;
    }

    // Draw center hole for role pie chart
    painter.setBrush(QColor(20, 20, 30));
    painter.setPen(Qt::NoPen);
    painter.drawEllipse(holeRect.translated(roleChartX - leftOffset, 0));

    painter.setFont(textFont);
    painter.setPen(Qt::white);
    painter.drawText(holeRect.translated(roleChartX - leftOffset, 0), Qt::AlignCenter, QString::number(totalEmployees));

    // Draw role legend
    roleLegendRects.clear();
    startAngle = 0;
    colorIndex = 0;
    int roleLegendY = yPos;
    int roleLegendX = roleChartX + chartWidth + 5;
    painter.setFont(legendFont);
    for (const QString &role : roleOrder) {
        if (!roleCount.contains(role) || roleCount[role] == 0) continue;

        int value = roleCount[role];
        double spanAngle = 360.0 * value / totalEmployees;

        painter.setBrush(roleGradients[role]);
        painter.setPen(Qt::white);
        QRect legendSquare(roleLegendX, roleLegendY, 10, 10);
        painter.drawRoundedRect(legendSquare, 3, 3);
        painter.drawText(roleLegendX + 15, roleLegendY + 9, role);
        roleLegendRects[role] = QRect(roleLegendX, roleLegendY, 80, 10);
        roleLegendY += 15;

        startAngle += spanAngle;
        colorIndex++;
    }

    // Update the widget's minimum height to accommodate all content
    int totalHeight = qMax(yPos + chartHeight + 150, tableY + 150);
    qDebug() << "Stats widget totalHeight:" << totalHeight; // Debug output
    setMinimumHeight(totalHeight);
}

void Stats::mouseMoveEvent(QMouseEvent *event) {
    QString newAgeSlice, newRoleSlice;
    double startAngle = 0;
    QString tooltip;

    QStringList ageOrder = {"<20", "20-30", "30-40", ">40"};
    for (const QString &cat : ageOrder) {
        int value = ageCategories[cat];
        if (value == 0) continue;
        double spanAngle = 360.0 * value / totalEmployees;
        if (isPointInSlice(event->pos(), agePieRect, startAngle, spanAngle)) {
            newAgeSlice = cat;
            tooltip = QString("Age %1: %2 employees, %3%")
                          .arg(cat)
                          .arg(value)
                          .arg(value * 100.0 / totalEmployees, 0, 'f', 1);
            break;
        }
        startAngle += spanAngle;
    }

    if (newAgeSlice.isEmpty()) {
        for (const QString &cat : ageOrder) {
            if (!ageLegendRects.contains(cat)) continue;
            if (ageLegendRects[cat].contains(event->pos())) {
                newAgeSlice = cat;
                int value = ageCategories[cat];
                tooltip = QString("Age %1: %2 employees, %3%")
                              .arg(cat)
                              .arg(value)
                              .arg(value * 100.0 / totalEmployees, 0, 'f', 1);
                break;
            }
        }
    }

    startAngle = 0;
    QStringList roleOrder = {"Admin", "Coach", "Employee"};
    for (const QString &role : roleOrder) {
        if (!roleCount.contains(role) || roleCount[role] == 0) continue;
        int value = roleCount[role];
        double spanAngle = 360.0 * value / totalEmployees;
        if (isPointInSlice(event->pos(), rolePieRect, startAngle, spanAngle)) {
            newRoleSlice = role;
            tooltip = QString("Role %1: %2 employees, %3%")
                          .arg(role)
                          .arg(value)
                          .arg(value * 100.0 / totalEmployees, 0, 'f', 1);
            break;
        }
        startAngle += spanAngle;
    }

    if (newRoleSlice.isEmpty()) {
        for (const QString &role : roleOrder) {
            if (!roleLegendRects.contains(role)) continue;
            if (roleLegendRects[role].contains(event->pos())) {
                newRoleSlice = role;
                int value = roleCount[role];
                tooltip = QString("Role %1: %2 employees, %3%")
                              .arg(role)
                              .arg(value)
                              .arg(value * 100.0 / totalEmployees, 0, 'f', 1);
                break;
            }
        }
    }

    int rowHeight = 40;
    int rowIndex = -1;
    if (tableRect.contains(event->pos())) {
        int yOffset = event->pos().y() - tableRect.y();
        if (yOffset > rowHeight) {
            rowIndex = (yOffset - rowHeight) / rowHeight;
        }
    }
    if (rowIndex != hoveredRow) {
        hoveredRow = rowIndex;
        update();
    }

    if (!tooltip.isEmpty()) {
        QToolTip::showText(event->globalPosition().toPoint(), tooltip, this);
    } else {
        QToolTip::hideText();
    }

    if (newAgeSlice != hoveredAgeSlice || newRoleSlice != hoveredRoleSlice) {
        hoveredAgeSlice = newAgeSlice;
        hoveredRoleSlice = newRoleSlice;
        update();
    }

    QWidget::mouseMoveEvent(event);
}

void Stats::mousePressEvent(QMouseEvent *event) {
    double startAngle = 0;

    QStringList ageOrder = {"<20", "20-30", "30-40", ">40"};
    for (const QString &cat : ageOrder) {
        int value = ageCategories[cat];
        if (value == 0) continue;
        double spanAngle = 360.0 * value / totalEmployees;
        if (isPointInSlice(event->pos(), agePieRect, startAngle, spanAngle)) {
            selectedAgeSlice = (selectedAgeSlice == cat) ? "" : cat;
            update();
            break;
        }
        startAngle += spanAngle;
    }

    startAngle = 0;
    QStringList roleOrder = {"Admin", "Coach", "Employee"};
    for (const QString &role : roleOrder) {
        if (!roleCount.contains(role) || roleCount[role] == 0) continue;
        int value = roleCount[role];
        double spanAngle = 360.0 * value / totalEmployees;
        if (isPointInSlice(event->pos(), rolePieRect, startAngle, spanAngle)) {
            selectedRoleSlice = (selectedRoleSlice == role) ? "" : role;
            update();
            break;
        }
        startAngle += spanAngle;
    }

    if (tableRect.contains(event->pos())) {
        int colWidth = tableRect.width() / 3;
        int col = (event->pos().x() - tableRect.x()) / colWidth;
        if (event->pos().y() < tableRect.y() + 30) {
            if (sortColumn == col) {
                sortAscending = !sortAscending;
            } else {
                sortColumn = col;
                sortAscending = true;
            }
            update();
        }
    }
}

void Stats::resizeEvent(QResizeEvent *event) {
    update();
    QWidget::resizeEvent(event);
}

void Stats::updateSliceScales() {
    QStringList ageOrder = {"<20", "20-30", "30-40", ">40"};
    int ageIndex = 0;
    for (const QString &cat : ageOrder) {
        if (ageCategories[cat] == 0) continue;
        bool isHovered = (cat == hoveredAgeSlice);
        bool isSelected = (cat == selectedAgeSlice);
        float targetScale = (isHovered || isSelected) ? 1.1 : 1.0;
        ageSliceScale[ageIndex] += (targetScale - ageSliceScale[ageIndex]) * 0.2;
        ageIndex++;
    }

    QStringList roleOrder = {"Admin", "Coach", "Employee"};
    int roleIndex = 0;
    for (const QString &role : roleOrder) {
        if (!roleCount.contains(role) || roleCount[role] == 0) continue;
        bool isHovered = (role == hoveredRoleSlice);
        bool isSelected = (role == selectedRoleSlice);
        float targetScale = (isHovered || isSelected) ? 1.1 : 1.0;
        roleSliceScale[roleIndex] += (targetScale - roleSliceScale[roleIndex]) * 0.2;
        roleIndex++;
    }

    update();
}

bool Stats::isPointInSlice(const QPoint &point, const QRect &pieRect, double startAngle, double spanAngle) {
    QPoint center = pieRect.center();
    double radius = qMin(pieRect.width(), pieRect.height()) / 2.0;
    double holeRadius = radius * 0.35;

    double dx = point.x() - center.x();
    double dy = point.y() - center.y();
    double distance = sqrt(dx * dx + dy * dy);
    if (distance > radius || distance < holeRadius) return false;

    double mouseAngle = atan2(dy, dx) * 180 / M_PI;
    if (mouseAngle < 0) mouseAngle += 360;

    double qtStartAngle = startAngle;
    double qtEndAngle = startAngle + spanAngle;
    if (qtEndAngle >= 360) qtEndAngle -= 360;

    if (qtStartAngle <= qtEndAngle) {
        return mouseAngle >= qtStartAngle && mouseAngle <= qtEndAngle;
    } else {
        return mouseAngle >= qtStartAngle || mouseAngle <= qtEndAngle;
    }
}

void Stats::sortTableData(QList<QMap<QString, QString>> &tableData) {
    if (sortColumn == -1) return;

    std::sort(tableData.begin(), tableData.end(), [&](const QMap<QString, QString> &a, const QMap<QString, QString> &b) {
        QString key;
        if (sortColumn == 0) key = "Age Category";
        else if (sortColumn == 1) key = "Role";
        else key = "Count";

        bool ok1, ok2;
        int val1 = a[key].toInt(&ok1);
        int val2 = b[key].toInt(&ok2);

        if (sortColumn == 2 && ok1 && ok2) {
            return sortAscending ? (val1 < val2) : (val1 > val2);
        } else {
            return sortAscending ? (a[key] < b[key]) : (a[key] > b[key]);
        }
    });
}

void Stats::exportToPDF() {
    QString fileName = QFileDialog::getSaveFileName(this, "Save PDF", "", "PDF Files (*.pdf)");
    if (fileName.isEmpty()) return;

    if (!fileName.endsWith(".pdf", Qt::CaseInsensitive)) {
        fileName += ".pdf";
    }

    QPdfWriter pdfWriter(fileName);
    pdfWriter.setPageSize(QPageSize(QPageSize::A4));
    pdfWriter.setPageMargins(QMarginsF(30, 30, 30, 30));

    QPainter painter(&pdfWriter);
    painter.setRenderHint(QPainter::Antialiasing);

    double scale = qMin(pdfWriter.width() / (double)width(), pdfWriter.height() / (double)height());
    painter.scale(scale, scale);

    render(&painter);

    painter.end();

    QMessageBox::information(this, "Success", "Statistics exported to PDF successfully at: " + fileName);
}

QPointF Stats::getSliceCenterPoint(const QRect &rect, double startAngle, double spanAngle) {
    double angle = (startAngle + spanAngle / 2) * M_PI / 180.0;
    double radius = rect.width() / 2.0;
    QPointF center = rect.center();
    return QPointF(center.x() + radius * 0.7 * std::cos(angle),
                   center.y() - radius * 0.7 * std::sin(angle));
}

QSize Stats::sizeHint() const {
    // Calculate the preferred size based on content
    int chartWidth = 300;
    int chartHeight = 300;
    int tableWidth = 400;
    int rowHeight = 40;
    int sectionSpacing = 50;
    int legendWidth = 80;

    int totalChartWidth = chartWidth + legendWidth + 5;
    int totalWidth = totalChartWidth * 2 + tableWidth + sectionSpacing * 2;

    // Calculate height based on content
    int maxRows = 4 * 3 + 1; // 4 age categories * 3 roles + 1 header row
    int tableHeight = rowHeight * maxRows;
    int totalHeight = qMax(chartHeight + 150, tableHeight + 100); // Add padding

    return QSize(totalWidth, totalHeight);
}
