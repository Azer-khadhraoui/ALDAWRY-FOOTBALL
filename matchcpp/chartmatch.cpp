#include "../matchheaders/chartmatch.h"
#include "ui_chartmatch.h"
#include "../matchheaders/match.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QBarSet>
#include <QBarSeries>
#include <QBarCategoryAxis>
#include <QValueAxis>
#include <QChartView>
#include <QToolTip>
#include <QDebug>
#include <QLinearGradient>
#include <QFont>
#include <QColor>
#include <QLayoutItem>
#include <QPushButton>
#include <QMenu>
#include <QVBoxLayout>
#include <QHBoxLayout>

chartMatch::chartMatch (QWidget *parent) :
    QDialog(parent),
    ui(new Ui::chartMatch)
{
    ui->setupUi(this);
    connect(ui->chartOptionComboBox, &QComboBox::currentTextChanged, 
        this, &chartMatch::chart);
    chart();
}
chartMatch::~chartMatch() {
    delete ui;
}
void chartMatch::chart()
{
    // Clear the existing layout and chart
    QLayout *existingLayout = ui->goals_chart->layout();
    if (existingLayout) {
        QLayoutItem *item;
        while ((item = existingLayout->takeAt(0)) != nullptr) {
            delete item->widget();
            delete item;
        }
        delete existingLayout;
    }

    // Get the selected option from the combo box
    QString chartOption = ui->chartOptionComboBox->currentText();

    // Query the database based on the selected option
    QSqlQuery query;
    if (chartOption == "Goals per Competition") {
        query.prepare("SELECT COMPETITION.COMP_NAME, COALESCE(SUM(Match.SCOREA + Match.SCOREB), 0) AS total_goals "
                      "FROM Match "
                      "INNER JOIN COMPETITION ON Match.ID_COMPETITION = COMPETITION.ID_COMPETITION "
                      "GROUP BY COMPETITION.COMP_NAME "
                      "ORDER BY total_goals DESC");
    } else if (chartOption == "Goals per Team") {
        query.prepare("SELECT EQUIPE.TEAM_NAME, "
                      "COALESCE(SUM(CASE WHEN Match.ID_TEAMA = EQUIPE.ID_TEAM THEN Match.SCOREA "
                      "WHEN Match.ID_TEAMB = EQUIPE.ID_TEAM THEN Match.SCOREB ELSE 0 END), 0) AS total_goals "
                      "FROM EQUIPE "
                      "LEFT JOIN Match ON EQUIPE.ID_TEAM = Match.ID_TEAMA OR EQUIPE.ID_TEAM = Match.ID_TEAMB "
                      "GROUP BY EQUIPE.ID_TEAM, EQUIPE.TEAM_NAME "
                      "ORDER BY total_goals DESC");
    }

    if (!query.exec()) {
        qDebug() << "Error retrieving data for bar chart:" << query.lastError().text();
        return;
    }

    // Create a bar set and populate it with data
    QBarSet *barSet = new QBarSet("Goals");
    QStringList categories;
    QList<qreal> values;

    // Set custom colors for the bars with gradient
    QLinearGradient barGradient(0, 0, 0, 1);
    barGradient.setCoordinateMode(QGradient::ObjectBoundingMode);
    barGradient.setColorAt(0.0, QColor(0, 169, 255));
    barGradient.setColorAt(1.0, QColor(0, 80, 170));
    barSet->setBrush(barGradient);
    barSet->setPen(QColor(0, 60, 120));

    while (query.next()) {
        QString name = query.value(0).toString();  // COMP_NAME or TEAM_NAME
        int totalGoals = query.value("total_goals").toInt();

        *barSet << totalGoals;
        values << totalGoals;
        categories << name;
    }

    if (categories.isEmpty()) {
        qDebug() << "No data available for the bar chart.";
        return;
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
    chart->setTitle(chartOption == "Goals per Competition" ? 
                    "Goals Scored Per Competition" : "Goals Scored Per Team");
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
    axisX->setLabelsAngle(-45);
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

    chartView->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(chartView, &QChartView::customContextMenuRequested, [=](const QPoint &pos) {
        QMenu contextMenu(tr("Chart Menu"), chartView);
        
        QAction resetZoomAction("Reset Zoom", chartView);
        connect(&resetZoomAction, &QAction::triggered, [=]() {
            chart->zoomReset();
        });
        contextMenu.addAction(&resetZoomAction);
        
        contextMenu.exec(chartView->mapToGlobal(pos));
    });

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
    
    QString buttonStyle = "QPushButton { background-color: #252A38; color: white; border: 1px solid #3A4A5A; border-radius: 3px; }"
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
    ChartWheelZoomHandler_chart* wheelHandler = new ChartWheelZoomHandler_chart(chartView);
    chartView->viewport()->installEventFilter(wheelHandler);

    QVBoxLayout *layout = new QVBoxLayout(ui->goals_chart);
    layout->addWidget(chartView);
    layout->addWidget(zoomButtonsWidget);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(5);
    ui->goals_chart->setLayout(layout);
}
