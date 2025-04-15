#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "team.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QFile>
#include <QBuffer>
#include <QDir>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QRegularExpression>
#include <QPixmap>
#include <QIcon>
#include <QTextStream>
#include <QPdfWriter>
#include <QPainter>
#include <QMediaPlayer>
#include <QVideoWidget>
#include "formadd.h"
#include "chatdialog.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSpacerItem>
#include "tableau.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setMinimumSize(1000, 700); // 👈 Add it right here!



    if (!QSqlDatabase::database().isOpen()) {
        qDebug() << "Database connection failed to open in MainWindow!";
        QMessageBox::critical(this, "Error", "Database connection is not open!");
    }

    setupBudgetPieChart();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupBudgetPieChart()
{
    budgetSeries = new QPieSeries();
    budgetSeries->setHoleSize(0.40);  // Slightly larger donut effect for a modern look

    // Fetch budget data and categorize into intervals
    QSqlQuery query("SELECT BUDG FROM HOTSTUFF.EQUIPE");
    int lowBudgetCount = 0;    // < 10000
    int midBudgetCount = 0;    // 10000 to 20000
    int highBudgetCount = 0;   // > 20000
    int totalTeams = 0;

    while (query.next()) {
        int budget = query.value(0).toInt();
        if (budget < 10000) {
            lowBudgetCount++;
        } else if (budget <= 20000) {
            midBudgetCount++;
        } else {
            highBudgetCount++;
        }
        totalTeams++;
    }

    // Calculate percentages and append slices with updated green gradient colors
    QList<QColor> colors = {QColor("#34C759"), QColor("#28A745"), QColor("#1E7E34")}; // Green shades matching the theme
    if (totalTeams > 0) {
        // Low budget slice
        double lowPercentage = (lowBudgetCount * 100.0) / totalTeams;
        QPieSlice *lowSlice = budgetSeries->append("Low Budget", lowBudgetCount);
        lowSlice->setColor(colors[0]);
        lowSlice->setLabel(QString("Low Budget\n%1%").arg(lowPercentage, 0, 'f', 1));
        connect(lowSlice, &QPieSlice::hovered, this, &MainWindow::onPieSliceHovered);

        // Mid budget slice
        double midPercentage = (midBudgetCount * 100.0) / totalTeams;
        QPieSlice *midSlice = budgetSeries->append("Mid Budget", midBudgetCount);
        midSlice->setColor(colors[1]);
        midSlice->setLabel(QString("Mid Budget\n%1%").arg(midPercentage, 0, 'f', 1));
        connect(midSlice, &QPieSlice::hovered, this, &MainWindow::onPieSliceHovered);

        // High budget slice
        double highPercentage = (highBudgetCount * 100.0) / totalTeams;
        QPieSlice *highSlice = budgetSeries->append("High Budget", highBudgetCount);
        highSlice->setColor(colors[2]);
        highSlice->setLabel(QString("High Budget\n%1%").arg(highPercentage, 0, 'f', 1));
        connect(highSlice, &QPieSlice::hovered, this, &MainWindow::onPieSliceHovered);
    }

    // Customize the pie slices
    for (QPieSlice *slice : budgetSeries->slices()) {
        slice->setLabelVisible(true);
        slice->setLabelPosition(QPieSlice::LabelOutside);
        slice->setLabelColor(QColor("#E0E0E0")); // Light gray labels for better contrast
        slice->setBorderColor(QColor("#2D3748")); // Dark border matching the background
        slice->setBorderWidth(2); // Slightly thicker border for emphasis
    }

    // Create a chart and add the series
    QChart *chart = new QChart();
    chart->addSeries(budgetSeries);
    chart->setTitle("Team Budget Intervals");
    chart->setTitleBrush(QBrush(QColor("#34C759"))); // Green title to match the theme
    chart->setTitleFont(QFont("Montserrat", 16, QFont::Bold)); // Modern font, larger size
    chart->setBackgroundBrush(QBrush(QColor("#1A2526"))); // Darker background to match the app
    chart->setPlotAreaBackgroundBrush(QBrush(QColor("#1A2526")));
    chart->setPlotAreaBackgroundVisible(true);
    chart->setTheme(QChart::ChartThemeDark);
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignRight);
    chart->legend()->setLabelColor(QColor("#E0E0E0")); // Light gray legend text
    chart->legend()->setFont(QFont("Montserrat", 12)); // Modern font for legend
    chart->setAnimationOptions(QChart::SeriesAnimations);

    // Create a chart view
    chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setFixedSize(600, 450); // Keep the size consistent
    chartView->setStyleSheet("background-color: #1A2526; border: 2px solid #2D3748; border-radius: 15px;"); // Updated styling to match the theme

    // Add the chart view to the layout
    QVBoxLayout *mainLayout = new QVBoxLayout(ui->widget_2);

    // Create a horizontal layout to shift the chart to the right
    QHBoxLayout *chartLayout = new QHBoxLayout();
    chartLayout->addStretch(5);
    chartLayout->addWidget(chartView);
    chartLayout->addStretch(1);

    mainLayout->addSpacing(280); // Move chart down by 200px
    mainLayout->addLayout(chartLayout);

    mainLayout->setContentsMargins(10, 0, 10, 10); // Minimal margins
    mainLayout->setSpacing(5); // Small spacing to avoid overlap
    ui->widget_2->setLayout(mainLayout);
}

void MainWindow::updateBudgetPieChart()
{
    if (!budgetSeries) return;

    budgetSeries->clear();

    QSqlQuery query("SELECT BUDG FROM HOTSTUFF.EQUIPE");
    int lowBudgetCount = 0;    // < 10000
    int midBudgetCount = 0;    // 10000 to 20000
    int highBudgetCount = 0;   // > 20000
    int totalTeams = 0;

    while (query.next()) {
        int budget = query.value(0).toInt();
        if (budget < 10000) {
            lowBudgetCount++;
        } else if (budget <= 20000) {
            midBudgetCount++;
        } else {
            highBudgetCount++;
        }
        totalTeams++;
    }

    QList<QColor> colors = {QColor("#34C759"), QColor("#28A745"), QColor("#1E7E34")};
    if (totalTeams > 0) {
        double lowPercentage = (lowBudgetCount * 100.0) / totalTeams;
        QPieSlice *lowSlice = budgetSeries->append("Low Budget", lowBudgetCount);
        lowSlice->setColor(colors[0]);
        lowSlice->setLabel(QString("Low Budget\n%1%").arg(lowPercentage, 0, 'f', 1));

        double midPercentage = (midBudgetCount * 100.0) / totalTeams;
        QPieSlice *midSlice = budgetSeries->append("Mid Budget", midBudgetCount);
        midSlice->setColor(colors[1]);
        midSlice->setLabel(QString("Mid Budget\n%1%").arg(midPercentage, 0, 'f', 1));

        double highPercentage = (highBudgetCount * 100.0) / totalTeams;
        QPieSlice *highSlice = budgetSeries->append("High Budget", highBudgetCount);
        highSlice->setColor(colors[2]);
        highSlice->setLabel(QString("High Budget\n%1%").arg(highPercentage, 0, 'f', 1));
    }

    for (QPieSlice *slice : budgetSeries->slices()) {
        slice->setLabelVisible(true);
        slice->setLabelPosition(QPieSlice::LabelOutside);
        slice->setLabelColor(QColor("#E0E0E0"));
        slice->setBorderColor(QColor("#2D3748"));
        slice->setBorderWidth(2);
    }
}

void MainWindow::onPieSliceHovered(bool state)
{
    QPieSlice *slice = qobject_cast<QPieSlice *>(sender());
    if (slice) {
        if (state) {
            slice->setExploded(true);
            slice->setExplodeDistanceFactor(0.15);
            slice->setLabelFont(QFont("Montserrat", 14, QFont::Bold));
            slice->setColor(slice->color().lighter(120)); // Slightly brighter on hover
        } else {
            slice->setExploded(false);
            slice->setExplodeDistanceFactor(0.0);
            slice->setLabelFont(QFont("Montserrat", 12));
            // Reset to original colors
            if (slice->label().startsWith("Low Budget")) {
                slice->setColor(QColor("#34C759"));
            } else if (slice->label().startsWith("Mid Budget")) {
                slice->setColor(QColor("#28A745"));
            } else {
                slice->setColor(QColor("#1E7E34"));
            }
        }
    }
}

void MainWindow::on_pushButton_clicked()
{
    ChatDialog *chatDialog = new ChatDialog(this);
    chatDialog->setModal(false);
    chatDialog->show();
}

void MainWindow::on_pushButton_2_clicked()
{
    FormAdd *formAdd = new FormAdd(this);
    connect(formAdd, &FormAdd::teamAdded, this, [=]() {
        updateBudgetPieChart();
    });
    formAdd->show();
}

void MainWindow::on_pushButton_3_clicked()
{
    ChatDialog *chatDialog = new ChatDialog(this);
    chatDialog->setModal(false);
    chatDialog->show();
}

void MainWindow::on_pushButton_4_clicked()
{
    Tableau *tableau = new Tableau(this);
    tableau->exec();
}

void MainWindow::on_pushButton_5_clicked()
{
    Tableau *tableau = new Tableau(this);
    tableau->exec();
}

void MainWindow::on_pushButton_6_clicked()
{
    Tableau *tableau = new Tableau(this);
    tableau->exec();
}

void MainWindow::on_toolButton_clicked()
{
    FormAdd *formAdd = new FormAdd(this);
    formAdd->exec();
}

void MainWindow::on_resetButton_clicked()
{
    updateBudgetPieChart();
}
