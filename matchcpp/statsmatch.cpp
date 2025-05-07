#include "../matchheaders/statsmatch.h"
#include "ui_statsMatch.h"
#include "../matchheaders/match.h"
#include <QStandardItemModel>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QValueAxis>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QToolTip>
#include <QLayoutItem>


statsMatch::statsMatch (QWidget *parent) :
    QDialog(parent),
    ui(new Ui::statsMatch)
{
    ui->setupUi(this);
    updateMatchSummary();
    updateRefereeAnalysis();
    weatherImpactChart(); // Call the weather impact chart function

}
statsMatch::~statsMatch() {
    delete ui;
}
void statsMatch::updateMatchSummary() {
    QStandardItemModel* summaryModel = Match::getMatchSummary(this);
    if (summaryModel) {
        ui->Matches_sum->setModel(summaryModel);

        // Hide the vertical header
        ui->Matches_sum->verticalHeader()->setVisible(false);

        // Align values center/right and bold the first column
        for (int row = 0; row < summaryModel->rowCount(); ++row) {
            for (int col = 0; col < summaryModel->columnCount(); ++col) {
                QStandardItem* item = summaryModel->item(row, col);
                if (item) {
                    if (col == 0) {
                        // Bold the first column
                        QFont font = item->font();
                        font.setBold(true);
                        item->setFont(font);
                        item->setTextAlignment(Qt::AlignCenter); // Center-align the first column
                    } else {
                        // Align other columns to the right
                        item->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
                    }
                }
            }
        }

        // Stretch columns for visibility
        ui->Matches_sum->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

        // Disable editing and selection
        ui->Matches_sum->setEditTriggers(QAbstractItemView::NoEditTriggers);
        ui->Matches_sum->setSelectionMode(QAbstractItemView::NoSelection);

        qDebug() << "Match summary updated successfully."; // Debug statement
    } else {
        qDebug() << "Failed to update match summary.";
    }
}
void statsMatch::updateRefereeAnalysis() {
    QSqlQuery query;
    query.prepare("SELECT REFEREE_NAME, COUNT(*) AS match_count "
                  "FROM Match "
                  "GROUP BY REFEREE_NAME "
                  "ORDER BY match_count DESC");

    if (!query.exec()) {
        qDebug() << "Error retrieving referee analysis:" << query.lastError().text();
        return;
    }

    // Create a model to hold the referee analysis data
    QStandardItemModel* model = new QStandardItemModel(this);
    model->setHorizontalHeaderLabels({"Referee Name", "Matches Officiated"});

    // Populate the model with query results
    int row = 0;
    while (query.next()) {
        QString refereeName = query.value("REFEREE_NAME").toString();
        int matchCount = query.value("match_count").toInt();

        model->setItem(row, 0, new QStandardItem(refereeName)); // Referee Name
        model->setItem(row, 1, new QStandardItem(QString::number(matchCount))); // Matches Officiated

        // Align the match count to the center
        model->item(row, 1)->setTextAlignment(Qt::AlignCenter);

        row++;
    }

    // Set the model to the QTableView
    ui->refrees->setModel(model);

    // Configure the table view
    ui->refrees->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch); // Stretch columns for visibility
    ui->refrees->setEditTriggers(QAbstractItemView::NoEditTriggers); // Disable editing
    ui->refrees->setSelectionMode(QAbstractItemView::NoSelection); // Disable selection
    ui->refrees->verticalHeader()->setVisible(false); // Hide the vertical header

    // Apply a professional stylesheet
    ui->refrees->setStyleSheet(
        "QTableView {"
        "    background-color: #1E2633;"
        "    border: 2px solid #2A3A4A;"
        "    gridline-color: #3A4A5A;"
        "    alternate-background-color: #252A38;"
        "    color: #FFFFFF;"
        "    selection-background-color: #00FF7F;"
        "    selection-color: #1A2633;"
        "    border-radius: 5px;"
        "}"
        "QTableView::item {"
        "    padding: 5px;"
        "    border: none;"
        "}"
        "QTableView::item:focus {"
        "    outline: none;"
        "}"
        "QHeaderView::section {"
        "    background-color: #252A38;"
        "    color: #FFFFFF;"
        "    border: 1px solid #2A3A4A;"
        "    padding: 4px;"
        "    font-weight: bold;"
        "    border-radius: 0;"
        "}"
        "QTableView QTableCornerButton::section {"
        "    background-color: #252A38;"
        "    border: 1px solid #2A3A4A;"
        "}"
    );

    qDebug() << "Referee analysis updated successfully.";
}
bool ChartWheelZoomHandler::eventFilter(QObject* obj, QEvent* event)
{
    if (event->type() == QEvent::Wheel) {
        QWheelEvent* wheelEvent = static_cast<QWheelEvent*>(event);
        QChartView* chartView = qobject_cast<QChartView*>(parent());
        if (chartView) {
            QChart* chart = reinterpret_cast<QChart*>(chartView->property("chart").value<quintptr>());
            if (chart) {
                // Zoom factor: zoom in for positive delta, out for negative
                qreal factor = (wheelEvent->angleDelta().y() > 0) ? 1.15 : 0.85;
                chart->zoom(factor);
                return true; // Event was handled
            }
        }
    }
    return QObject::eventFilter(obj, event);
}
void statsMatch::weatherImpactChart()
{
    // Clear the existing layout and chart in weather_impact widget
    QLayout *existingLayout = ui->weather_impact->layout();
    if (existingLayout) {
        QLayoutItem *item;
        while ((item = existingLayout->takeAt(0)) != nullptr) {
            delete item->widget();
            delete item;
        }
        delete existingLayout;
    }

    // Query the database for goals by weather condition
    QSqlQuery query;
    query.prepare("SELECT CASE METEO "
                  "WHEN 0 THEN 'Sunny' "
                  "WHEN 1 THEN 'Rainy' "
                  "ELSE 'Unknown' END AS Weather, "
                  "COALESCE(SUM(SCOREA + SCOREB), 0) AS total_goals "
                  "FROM Match "
                  "WHERE STATUS_M = 'Played' "
                  "GROUP BY METEO "
                  "ORDER BY total_goals DESC");

    if (!query.exec()) {
        qDebug() << "Error retrieving weather impact data:" << query.lastError().text();
        return;
    }

    QStringList categories;
    QList<qreal> values;

    while (query.next()) {
        QString weather = query.value("Weather").toString();
        int totalGoals = query.value("total_goals").toInt();

        values << totalGoals;
        categories << weather;
    }

    if (categories.isEmpty()) {
        // Display a message if no matches have been played
        QLabel *noDataLabel = new QLabel("No matches have been played yet.");
        noDataLabel->setAlignment(Qt::AlignCenter);
        noDataLabel->setStyleSheet("color: #FFFFFF; font-size: 16px; font-weight: bold;");
        QVBoxLayout *layout = new QVBoxLayout(ui->weather_impact);
        layout->addWidget(noDataLabel);
        layout->setContentsMargins(0, 0, 0, 0);
        layout->setSpacing(5);
        ui->weather_impact->setLayout(layout);
        return;
    }

    // Create a bar set and populate it with data
    QBarSet *barSet = new QBarSet("Goals");

    // Set custom colors for the bars with gradient
    QLinearGradient barGradient(0, 0, 0, 1);
    barGradient.setCoordinateMode(QGradient::ObjectBoundingMode);
    barGradient.setColorAt(0.0, QColor(255, 165, 0));   // Orange at top (for weather theme)
    barGradient.setColorAt(1.0, QColor(139, 69, 19));   // Brown at bottom
    barSet->setBrush(barGradient);
    barSet->setPen(QColor(139, 69, 19));  // Darker border for bars

    for (qreal value : values) {
        *barSet << value;
    }

    // Create a bar series and add the bar set
    QBarSeries *series = new QBarSeries();
    series->append(barSet);
    series->setLabelsVisible(true);
    series->setLabelsPosition(QAbstractBarSeries::LabelsOutsideEnd);
    series->setLabelsFormat("@value");
    series->setBarWidth(0.7);

    // Enable tooltips
    connect(series, &QBarSeries::hovered, [=](bool status, int index, QBarSet *barSet) {
        if (status && index >= 0 && index < categories.size()) {
            QToolTip::showText(QCursor::pos(),
                               QString("%1\nGoals: %2").arg(categories.at(index)).arg(barSet->at(index)),
                               nullptr);
        }
    });

    // Create the chart
    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Goals Scored by Weather Condition");
    chart->setAnimationOptions(QChart::SeriesAnimations);
    chart->setAnimationDuration(1000);
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);

    // Set chart theme and style
    chart->setTheme(QChart::ChartThemeDark);
    QLinearGradient backgroundGradient(0, 0, 0, 1);
    backgroundGradient.setCoordinateMode(QGradient::ObjectBoundingMode);
    backgroundGradient.setColorAt(0.0, QColor(26, 30, 45));
    backgroundGradient.setColorAt(1.0, QColor(30, 38, 51));
    chart->setBackgroundBrush(backgroundGradient);
    chart->setDropShadowEnabled(true);

    QFont titleFont = chart->titleFont();
    titleFont.setPointSize(12);
    titleFont.setBold(true);
    chart->setTitleFont(titleFont);
    chart->setTitleBrush(QBrush(QColor("#FFFFFF")));

    // Create the category axis for the x-axis
    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(categories);
    axisX->setLabelsAngle(0);  // Horizontal labels since weather categories are short
    QFont labelFont = axisX->labelsFont();
    labelFont.setPointSize(9);
    axisX->setLabelsFont(labelFont);
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    axisX->setGridLineVisible(false);
    axisX->setLabelsColor(QColor("#CCCCCC"));

    // Create the value axis for the y-axis
    QValueAxis *axisY = new QValueAxis();
    int maxGoals = 0;
    for (int i = 0; i < barSet->count(); ++i) {
        maxGoals = std::max(maxGoals, static_cast<int>(barSet->at(i)));
    }

    int yAxisMax = ((maxGoals / 10) + 1) * 10 + 10;
    axisY->setRange(0, yAxisMax);
    axisY->setTickCount(6);
    axisY->setLabelFormat("%d");
    axisY->setTitleText("Total Goals");

    QFont titleAxisFont = axisY->titleFont();
    titleAxisFont.setBold(true);
    axisY->setTitleFont(titleAxisFont);
    axisY->setTitleBrush(QBrush(QColor("#FFFFFF")));
    axisY->setLabelsColor(QColor("#CCCCCC"));
    axisY->setGridLineColor(QColor(60, 70, 80, 100));

    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    QRectF initialPlotArea = chart->plotArea();
    chart->setProperty("initialPlotArea", initialPlotArea);
    chart->setProperty("isZoomed", false);

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    connect(chart, &QChart::plotAreaChanged, [=](const QRectF &plotArea) {
        QRectF initialArea = chart->property("initialPlotArea").toRectF();
        bool isZoomed = chart->property("isZoomed").toBool();

        if (plotArea.width() > initialArea.width() || plotArea.height() > initialArea.height()) {
            if (!isZoomed) {
                chart->setProperty("isZoomed", true);
            } else {
                chart->zoomReset();
            }
        }
    });

    // Add zoom buttons
    QWidget* zoomButtonsWidget = new QWidget();
    QHBoxLayout* zoomButtonsLayout = new QHBoxLayout(zoomButtonsWidget);

    QPushButton* zoomInButton = new QPushButton("+");
    zoomInButton->setFixedSize(28, 28);
    zoomInButton->setToolTip("Zoom In");
    connect(zoomInButton, &QPushButton::clicked, [=]() {
        chart->zoom(1.25);
    });

    QPushButton* zoomOutButton = new QPushButton("-");
    zoomOutButton->setFixedSize(28, 28);
    zoomOutButton->setToolTip("Zoom Out");
    connect(zoomOutButton, &QPushButton::clicked, [=]() {
        QRectF currentArea = chart->plotArea();
        QRectF initialArea = chart->property("initialPlotArea").toRectF();

        qreal newWidth = currentArea.width() / 0.75;
        qreal newHeight = currentArea.height() / 0.75;

        if (newWidth <= initialArea.width() && newHeight <= initialArea.height()) {
            chart->zoom(0.75);
        } else {
            chart->zoomReset();
        }
    });

    QPushButton* resetZoomButton = new QPushButton("Reset");
    resetZoomButton->setToolTip("Reset Zoom");
    connect(resetZoomButton, &QPushButton::clicked, [=]() {
        chart->zoomReset();
    });

    QString buttonStyle = "QPushButton { background-color: #252A38; color: white; border: 1px solid #3A3A5A; border-radius: 3px; }"
                         "QPushButton:hover { background-color: #2D89EF; }";
    zoomInButton->setStyleSheet(buttonStyle);
    zoomOutButton->setStyleSheet(buttonStyle);
    resetZoomButton->setStyleSheet(buttonStyle);

    zoomButtonsLayout->addWidget(zoomInButton);
    zoomButtonsLayout->addWidget(zoomOutButton);
    zoomButtonsLayout->addWidget(resetZoomButton);
    zoomButtonsLayout->addStretch();
    zoomButtonsLayout->setContentsMargins(5, 0, 5, 0);

    // Add custom wheel zoom handler
    ChartWheelZoomHandler* wheelHandler = new ChartWheelZoomHandler(chartView);
    chartView->viewport()->installEventFilter(wheelHandler);

    // Set up the layout
    QVBoxLayout *layout = new QVBoxLayout(ui->weather_impact);
    layout->addWidget(chartView);
    layout->addWidget(zoomButtonsWidget);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(5);
    ui->weather_impact->setLayout(layout);
}
