#include "../userheaders/statswidget.h"
#include "../userheaders/userwindow.h"
#include <QDebug>
#include <cmath>
#include <QVBoxLayout>
#include <QPushButton>
#include <QMessageBox>

statsWidget::statsWidget(UserWindow *parent)
    : QWidget(parent), userWindow(parent), hoveredAgeSlice(""), hoveredRoleSlice(""),
    selectedAgeSlice(""), selectedRoleSlice(""), sortColumn(-1), sortAscending(true) {
    setMouseTracking(true); // Enable mouse move events

    // Initialize scale factors
    for (int i = 0; i < 4; ++i) ageSliceScale[i] = 1.0;
    for (int i = 0; i < 10; ++i) roleSliceScale[i] = 1.0;

    // Set up animation timer
    animationTimer = new QTimer(this);
    connect(animationTimer, &QTimer::timeout, this, &statsWidget::updateSliceScales);
    animationTimer->start(50); // Update every 50ms

    // Add export button
    QVBoxLayout *layout = new QVBoxLayout(this);
    QPushButton *exportButton = new QPushButton("Export to PDF", this);
    exportButton->setStyleSheet("background-color: #4CAF50; color: white; padding: 5px; border-radius: 3px;");
    connect(exportButton, &QPushButton::clicked, this, &statsWidget::exportToPDF);
    layout->addWidget(exportButton, 0, Qt::AlignRight);
    layout->addStretch();
}

void statsWidget::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // Draw background gradient
    QLinearGradient bgGradient(0, 0, 0, height());
    bgGradient.setColorAt(0, QColor(20, 20, 30));
    bgGradient.setColorAt(1, QColor(40, 40, 50));
    painter.fillRect(rect(), bgGradient);

    if (userWindow->totalEmployees == 0) {
        painter.setFont(QFont("Segoe UI", 14));
        painter.setPen(Qt::white);
        painter.drawText(rect(), Qt::AlignCenter, "No employee data available to display statistics.");
        return;
    }

    // Dynamic sizing based on widget dimensions
    int margin = 30;
    int chartWidth = width() / 5; // 20% of widget width
    int chartHeight = chartWidth;
    int legendWidth = 120;
    int tableWidth = width() / 4; // 25% of widget width
    int rowHeight = 30;
    int yPos = 70;
    int sectionSpacing = 40;

    int totalChartWidth = chartWidth + legendWidth + 20; // Space for chart + legend
    int leftOffset = (width() - (totalChartWidth + tableWidth + margin)) / 2; // Center the content

    QFont titleFont("Segoe UI", 18, QFont::Bold);
    QFont subtitleFont("Segoe UI", 12, QFont::Bold);
    QFont textFont("Segoe UI", 10);
    QFont legendFont("Segoe UI", 8);
    QFont labelFont("Segoe UI", 8, QFont::Bold);

    // Define color palette to match the image (blue and pink)
    QList<QColor> baseColors = {
        QColor("#00CED1"), // Blue for "25-35" and "Coach"
        QColor("#FF69B4")  // Pink for "<25" and "employee"
    };

    // Initialize gradients for age categories
    ageGradients.clear();
    int colorIndex = 0;
    QStringList ageOrder = {"25-35", "<25"}; // Explicit order to match image
    for (const QString &cat : ageOrder) {
        if (!userWindow->ageCategories.contains(cat) || userWindow->ageCategories[cat] == 0) continue;
        QColor base = baseColors[colorIndex % baseColors.size()];
        QLinearGradient gradient(0, 0, chartWidth, chartHeight);
        gradient.setColorAt(0, base.lighter(110));
        gradient.setColorAt(1, base.darker(110));
        ageGradients[cat] = gradient;
        colorIndex++;
    }

    // Initialize gradients for roles
    roleGradients.clear();
    colorIndex = 0;
    QStringList roleOrder = {"Coach", "employee"}; // Explicit order to match image
    for (const QString &role : roleOrder) {
        if (!userWindow->roleCount.contains(role) || userWindow->roleCount[role] == 0) continue;
        QColor base = baseColors[colorIndex % baseColors.size()];
        QLinearGradient gradient(0, 0, chartWidth, chartHeight);
        gradient.setColorAt(0, base.lighter(110));
        gradient.setColorAt(1, base.darker(110));
        roleGradients[role] = gradient;
        colorIndex++;
    }

    // Title (Split into two lines)
    painter.setFont(titleFont);
    painter.setPen(Qt::white);
    painter.drawText(QRect(0, yPos - 50, width(), 30), Qt::AlignCenter, "Employee Statistics");
    painter.setFont(QFont("Segoe UI", 14, QFont::Bold));
    painter.drawText(QRect(0, yPos - 25, width(), 30), Qt::AlignCenter,
                     QString("(Total: %1)").arg(userWindow->totalEmployees));
    yPos += 20;

    // Age Distribution Pie Chart
    painter.setFont(subtitleFont);
    painter.drawText(leftOffset, yPos, "Age Distribution");
    yPos += 25;

    agePieRect = QRect(leftOffset, yPos, chartWidth, chartHeight);
    double startAngle = 0;
    int ageIndex = 0;

    // Draw shadow for age pie chart
    painter.setPen(Qt::NoPen);
    painter.setBrush(QColor(0, 0, 0, 50));
    painter.drawEllipse(agePieRect.adjusted(5, 5, 5, 5));

    // Draw pie slices with percentage labels
    QMap<QString, double> ageAngles; // Store start angles for each age category
    for (const QString &cat : ageOrder) {
        if (!userWindow->ageCategories.contains(cat) || userWindow->ageCategories[cat] == 0) continue;

        int value = userWindow->ageCategories[cat];
        ageAngles[cat] = startAngle;
        double spanAngle = 360.0 * value / userWindow->totalEmployees;
        painter.setBrush(ageGradients[cat]);
        painter.setPen(Qt::black);

        bool isHovered = (cat == hoveredAgeSlice);
        bool isSelected = (cat == selectedAgeSlice);
        QRect drawRect = agePieRect;
        float scale = ageSliceScale[ageIndex];
        if (isHovered || isSelected) {
            double midAngle = (startAngle + spanAngle / 2) * M_PI / 180.0;
            int offset = isSelected ? 15 : 10;
            drawRect.translate(offset * cos(midAngle), offset * sin(midAngle));
            drawRect = drawRect.adjusted(-scale * chartWidth / 10, -scale * chartHeight / 10,
                                         scale * chartWidth / 10, scale * chartHeight / 10);
        }

        painter.drawPie(drawRect, startAngle * 16, spanAngle * 16);

        // Add percentage label
        double percentage = (value * 100.0) / userWindow->totalEmployees;
        QString label = QString("%1%").arg(percentage, 0, 'f', 1);
        QPointF labelPos = getSliceCenterPoint(drawRect, startAngle, spanAngle);
        painter.setFont(labelFont);
        painter.setPen(Qt::white);
        painter.drawText(QRectF(labelPos.x() - 30, labelPos.y() - 10, 60, 20), Qt::AlignCenter, label);

        startAngle += spanAngle;
        ageIndex++;
    }

    // Draw inner circle for donut effect
    painter.setBrush(QColor(20, 20, 30));
    painter.setPen(Qt::NoPen);
    int holeSize = chartWidth * 0.35;
    QRect holeRect(agePieRect.center().x() - holeSize / 2, agePieRect.center().y() - holeSize / 2, holeSize, holeSize);
    painter.drawEllipse(holeRect);

    // Draw total in center
    painter.setFont(textFont);
    painter.setPen(Qt::white);
    painter.drawText(holeRect, Qt::AlignCenter, QString::number(userWindow->totalEmployees));

    // Draw legend for Age Distribution
    startAngle = 0;
    colorIndex = 0;
    int legendY = yPos;
    int legendX = leftOffset + chartWidth + 10;
    painter.setFont(legendFont);
    for (const QString &cat : ageOrder) {
        if (!userWindow->ageCategories.contains(cat) || userWindow->ageCategories[cat] == 0) continue;

        int value = userWindow->ageCategories[cat];
        double spanAngle = 360.0 * value / userWindow->totalEmployees;

        // Legend
        painter.setBrush(ageGradients[cat]);
        painter.setPen(Qt::white);
        QRect legendSquare(legendX, legendY, 12, 12);
        painter.drawRoundedRect(legendSquare, 3, 3);
        painter.drawText(legendX + 18, legendY + 10, cat);
        legendY += 18;

        startAngle += spanAngle;
        colorIndex++;
    }

    yPos += chartHeight + sectionSpacing;

    // Role Distribution Pie Chart
    painter.setFont(subtitleFont);
    painter.drawText(leftOffset, yPos, "Role Distribution");
    yPos += 25;

    rolePieRect = QRect(leftOffset, yPos, chartWidth, chartHeight);
    startAngle = 0;
    int roleIndex = 0;

    // Draw shadow for role pie chart
    painter.setPen(Qt::NoPen);
    painter.setBrush(QColor(0, 0, 0, 50));
    painter.drawEllipse(rolePieRect.adjusted(5, 5, 5, 5));

    // Draw pie slices with percentage labels
    QMap<QString, double> roleAngles; // Store start angles for each role
    for (const QString &role : roleOrder) {
        if (!userWindow->roleCount.contains(role) || userWindow->roleCount[role] == 0) continue;

        int value = userWindow->roleCount[role];
        roleAngles[role] = startAngle;
        double spanAngle = 360.0 * value / userWindow->totalEmployees;
        painter.setBrush(roleGradients[role]);
        painter.setPen(Qt::black);

        bool isHovered = (role == hoveredRoleSlice);
        bool isSelected = (role == selectedRoleSlice);
        QRect drawRect = rolePieRect;
        float scale = roleSliceScale[roleIndex];
        if (isHovered || isSelected) {
            double midAngle = (startAngle + spanAngle / 2) * M_PI / 180.0;
            int offset = isSelected ? 15 : 10;
            drawRect.translate(offset * cos(midAngle), offset * sin(midAngle));
            drawRect = drawRect.adjusted(-scale * chartWidth / 10, -scale * chartHeight / 10,
                                         scale * chartWidth / 10, scale * chartHeight / 10);
        }

        painter.drawPie(drawRect, startAngle * 16, spanAngle * 16);

        // Add percentage label
        double percentage = (value * 100.0) / userWindow->totalEmployees;
        QString label = QString("%1%").arg(percentage, 0, 'f', 1);
        QPointF labelPos = getSliceCenterPoint(drawRect, startAngle, spanAngle);
        painter.setFont(labelFont);
        painter.setPen(Qt::white);
        painter.drawText(QRectF(labelPos.x() - 30, labelPos.y() - 10, 60, 20), Qt::AlignCenter, label);

        startAngle += spanAngle;
        roleIndex++;
    }

    // Draw inner circle for donut effect
    painter.setBrush(QColor(20, 20, 30));
    painter.setPen(Qt::NoPen);
    painter.drawEllipse(holeRect.translated(0, rolePieRect.y() - agePieRect.y()));

    // Draw total in center
    painter.setFont(textFont);
    painter.setPen(Qt::white);
    painter.drawText(holeRect.translated(0, rolePieRect.y() - agePieRect.y()), Qt::AlignCenter, QString::number(userWindow->totalEmployees));

    // Draw legend for Role Distribution
    startAngle = 0;
    colorIndex = 0;
    legendY = yPos;
    legendX = leftOffset + chartWidth + 10;
    painter.setFont(legendFont);
    for (const QString &role : roleOrder) {
        if (!userWindow->roleCount.contains(role) || userWindow->roleCount[role] == 0) continue;

        int value = userWindow->roleCount[role];
        double spanAngle = 360.0 * value / userWindow->totalEmployees;

        // Legend
        painter.setBrush(roleGradients[role]);
        painter.setPen(Qt::white);
        QRect legendSquare(legendX, legendY, 12, 12);
        painter.drawRoundedRect(legendSquare, 3, 3);
        painter.drawText(legendX + 18, legendY + 10, role);
        legendY += 18;

        startAngle += spanAngle;
        colorIndex++;
    }

    // Role by Age Table
    int tableX = leftOffset + totalChartWidth + 20;
    int tableY = 70; // Align with top title
    painter.setFont(subtitleFont);
    painter.drawText(tableX, tableY, "Role by Age Category");
    tableY += 25;

    int colWidth = tableWidth / 3;
    tableRect = QRect(tableX, tableY, tableWidth, rowHeight * (userWindow->roleByAge.size() * userWindow->roleCount.size() + 1));

    // Draw table header with shadow
    painter.setPen(Qt::NoPen);
    painter.setBrush(QColor(0, 0, 0, 50));
    painter.drawRoundedRect(tableX + 5, tableY + 5, colWidth * 3, rowHeight, 5, 5);
    painter.setBrush(QColor(50, 50, 50));
    painter.setPen(Qt::white);
    painter.drawRoundedRect(tableX, tableY, colWidth, rowHeight, 5, 5);
    painter.drawRoundedRect(tableX + colWidth, tableY, colWidth, rowHeight, 5, 5);
    painter.drawRoundedRect(tableX + 2 * colWidth, tableY, colWidth, rowHeight, 5, 5);
    painter.setFont(subtitleFont);
    painter.drawText(tableX, tableY, colWidth, rowHeight, Qt::AlignCenter, "Age Category");
    painter.drawText(tableX + colWidth, tableY, colWidth, rowHeight, Qt::AlignCenter, "Role");
    painter.drawText(tableX + 2 * colWidth, tableY, colWidth, rowHeight, Qt::AlignCenter, "Count");
    tableY += rowHeight;

    // Prepare table data for sorting
    QList<QMap<QString, QString>> tableData;
    for (auto ageIt = userWindow->roleByAge.constBegin(); ageIt != userWindow->roleByAge.constEnd(); ++ageIt) {
        QString ageCat = ageIt.key();
        if (selectedAgeSlice != "" && selectedAgeSlice != ageCat) continue;
        for (auto roleIt = ageIt.value().constBegin(); roleIt != ageIt.value().constEnd(); ++roleIt) {
            QString role = roleIt.key();
            if (selectedRoleSlice != "" && selectedRoleSlice != role) continue;
            QMap<QString, QString> row;
            row["Age Category"] = ageCat;
            row["Role"] = role;
            row["Count"] = QString::number(roleIt.value());
            tableData.append(row);
        }
    }

    // Sort table data
    sortTableData(tableData);

    // Draw table rows
    bool alternate = false;
    for (const auto &row : tableData) {
        painter.setBrush(alternate ? QColor(40, 40, 40) : QColor(30, 30, 30));
        painter.drawRoundedRect(tableX, tableY, colWidth, rowHeight, 5, 5);
        painter.drawRoundedRect(tableX + colWidth, tableY, colWidth, rowHeight, 5, 5);
        painter.drawRoundedRect(tableX + 2 * colWidth, tableY, colWidth, rowHeight, 5, 5);
        painter.setFont(textFont);
        painter.drawText(tableX, tableY, colWidth, rowHeight, Qt::AlignCenter, row["Age Category"]);
        painter.drawText(tableX + colWidth, tableY, colWidth, rowHeight, Qt::AlignCenter, row["Role"]);
        painter.drawText(tableX + 2 * colWidth, tableY, colWidth, rowHeight, Qt::AlignCenter, row["Count"]);
        tableY += rowHeight;
        alternate = !alternate;
    }
}

void statsWidget::mouseMoveEvent(QMouseEvent *event) {
    QString newAgeSlice, newRoleSlice;
    double startAngle = 0;
    QString tooltip;

    // Check age pie chart
    int ageIndex = 0;
    for (auto it = userWindow->ageCategories.constBegin(); it != userWindow->ageCategories.constEnd(); ++it) {
        int value = it.value();
        if (value == 0) continue;
        double spanAngle = 360.0 * value / userWindow->totalEmployees;
        if (isPointInSlice(event->pos(), agePieRect, startAngle, spanAngle)) {
            newAgeSlice = it.key();
            tooltip = QString("Age %1: %2 employees, %3%")
                          .arg(it.key())
                          .arg(value)
                          .arg(value * 100.0 / userWindow->totalEmployees, 0, 'f', 1);
            break;
        }
        startAngle += spanAngle;
        ageIndex++;
    }

    // Check role pie chart
    startAngle = 0;
    int roleIndex = 0;
    for (auto it = userWindow->roleCount.constBegin(); it != userWindow->roleCount.constEnd(); ++it) {
        int value = it.value();
        if (value == 0) continue;
        double spanAngle = 360.0 * value / userWindow->totalEmployees;
        if (isPointInSlice(event->pos(), rolePieRect, startAngle, spanAngle)) {
            newRoleSlice = it.key();
            tooltip = QString("Role %1: %2 employees, %3%")
                          .arg(it.key())
                          .arg(value)
                          .arg(value * 100.0 / userWindow->totalEmployees, 0, 'f', 1);
            break;
        }
        startAngle += spanAngle;
        roleIndex++;
    }

    // Show tooltip
    if (!tooltip.isEmpty()) {
        QToolTip::showText(event->globalPos(), tooltip, this);
    } else {
        QToolTip::hideText();
    }

    // Update if hover state changed
    if (newAgeSlice != hoveredAgeSlice || newRoleSlice != hoveredRoleSlice) {
        hoveredAgeSlice = newAgeSlice;
        hoveredRoleSlice = newRoleSlice;
        update(); // Redraw to show hover effect
    }

    QWidget::mouseMoveEvent(event);
}

void statsWidget::mousePressEvent(QMouseEvent *event) {
    double startAngle = 0;

    // Check age pie chart
    for (auto it = userWindow->ageCategories.constBegin(); it != userWindow->ageCategories.constEnd(); ++it) {
        int value = it.value();
        if (value == 0) continue;
        double spanAngle = 360.0 * value / userWindow->totalEmployees;
        if (isPointInSlice(event->pos(), agePieRect, startAngle, spanAngle)) {
            selectedAgeSlice = (selectedAgeSlice == it.key()) ? "" : it.key();
            update();
            break;
        }
        startAngle += spanAngle;
    }

    // Check role pie chart
    startAngle = 0;
    for (auto it = userWindow->roleCount.constBegin(); it != userWindow->roleCount.constEnd(); ++it) {
        int value = it.value();
        if (value == 0) continue;
        double spanAngle = 360.0 * value / userWindow->totalEmployees;
        if (isPointInSlice(event->pos(), rolePieRect, startAngle, spanAngle)) {
            selectedRoleSlice = (selectedRoleSlice == it.key()) ? "" : it.key();
            update();
            break;
        }
        startAngle += spanAngle;
    }

    // Check table header for sorting
    if (tableRect.contains(event->pos())) {
        int colWidth = tableRect.width() / 3;
        int col = (event->pos().x() - tableRect.x()) / colWidth;
        if (event->pos().y() < tableRect.y() + 30) { // Header row
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

void statsWidget::resizeEvent(QResizeEvent *event) {
    update(); // Redraw on resize
    QWidget::resizeEvent(event);
}

void statsWidget::updateSliceScales() {
    int ageIndex = 0;
    for (auto it = userWindow->ageCategories.constBegin(); it != userWindow->ageCategories.constEnd(); ++it) {
        if (it.value() == 0) continue;
        bool isHovered = (it.key() == hoveredAgeSlice);
        bool isSelected = (it.key() == selectedAgeSlice);
        float targetScale = (isHovered || isSelected) ? 1.1 : 1.0;
        ageSliceScale[ageIndex] += (targetScale - ageSliceScale[ageIndex]) * 0.2;
        ageIndex++;
    }

    int roleIndex = 0;
    for (auto it = userWindow->roleCount.constBegin(); it != userWindow->roleCount.constEnd(); ++it) {
        if (it.value() == 0) continue;
        bool isHovered = (it.key() == hoveredRoleSlice);
        bool isSelected = (it.key() == selectedRoleSlice);
        float targetScale = (isHovered || isSelected) ? 1.1 : 1.0;
        roleSliceScale[roleIndex] += (targetScale - roleSliceScale[roleIndex]) * 0.2;
        roleIndex++;
    }

    update();
}

bool statsWidget::isPointInSlice(const QPoint &point, const QRect &pieRect, double startAngle, double spanAngle) {
    QPoint center = pieRect.center();
    double radius = pieRect.width() / 2;
    double holeRadius = radius * 0.35;

    double dx = point.x() - center.x();
    double dy = point.y() - center.y();
    double distance = sqrt(dx * dx + dy * dy);
    if (distance > radius || distance < holeRadius) return false;

    double angle = atan2(dy, dx) * 180 / M_PI;
    if (angle < 0) angle += 360;
    double endAngle = startAngle + spanAngle;

    startAngle = 90 - startAngle;
    endAngle = startAngle - spanAngle;
    if (startAngle < 0) startAngle += 360;
    if (endAngle < 0) endAngle += 360;

    if (endAngle > startAngle) {
        return angle >= endAngle && angle <= startAngle;
    } else {
        return angle >= endAngle || angle <= startAngle;
    }
}

void statsWidget::sortTableData(QList<QMap<QString, QString>> &tableData) {
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

void statsWidget::exportToPDF() {
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

    // Scale the widget content to fit the PDF page
    double scale = qMin(pdfWriter.width() / (double)width(), pdfWriter.height() / (double)height());
    painter.scale(scale, scale);

    // Paint the widget directly onto the PDF
    render(&painter);

    painter.end();

    QMessageBox::information(this, "Success", "Statistics exported to PDF successfully at: " + fileName);
}

QPointF statsWidget::getSliceCenterPoint(const QRect &rect, double startAngle, double spanAngle) {
    double angle = (startAngle + spanAngle / 2) * M_PI / 180.0;
    double radius = rect.width() / 2.0;
    QPointF center = rect.center();
    return QPointF(center.x() + radius * 0.7 * std::cos(angle),
                   center.y() - radius * 0.7 * std::sin(angle)); // Y is inverted in Qt
}
