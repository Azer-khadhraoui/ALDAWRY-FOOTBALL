#include "statistics.h"
#include "ui_statistics.h"
#include <QtCharts/QChart>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QValueAxis>
#include <QFileDialog>
#include <QMessageBox>
#include <QPainter>
#include "competition.h"
#include <QDebug>
#include <QDateTime>
#include "statistics2.h"

statistics::statistics(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::statistics)
{
    ui->setupUi(this);
    competition c;
    // Extract data from the database
    QStringList categories;
    QList<qreal> teams;
    competition::extractDataFromDatabase(categories, teams);

    // Debug: Print extracted data
    qDebug() << "Categories:" << categories;
    qDebug() << "Teams:" << teams;

    // Create bar set
    QBarSet *set = new QBarSet("Teams");

    // Check the size of the teams list before accessing its elements
    for (int i = 0; i < teams.size() && i < 10; ++i) {
        *set << teams[i];
    }

    set->setBrush(QBrush(QColor("#3D8B7A")));
    set->setPen(QPen(QColor("#3D8B7A")));

    // Create bar series
    QBarSeries *series = new QBarSeries();
    series->append(set);

    // Create chart
    chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Number of Teams per Competition");
    chart->setAnimationOptions(QChart::SeriesAnimations);
    chart->setBackgroundBrush(QBrush(QColor("#1A3C34")));

    // Customize title
    QFont titleFont = chart->titleFont();
    titleFont.setPointSize(12);
    chart->setTitleFont(titleFont);
    chart->setTitleBrush(QBrush(QColor("#E0E0E0")));

    // X-axis (categories)
    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(categories);
    axisX->setTitleText("Competitions");
    axisX->setLabelsColor(QColor("#E0E0E0"));
    axisX->setTitleBrush(QBrush(QColor("#E0E0E0")));
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    // Y-axis (values)
    QValueAxis *axisY = new QValueAxis();
    axisY->setRange(0, 30);
    axisY->setTitleText("Number of Teams");
    axisY->setLabelsColor(QColor("#E0E0E0"));
    axisY->setTitleBrush(QBrush(QColor("#E0E0E0")));
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    // Set chart to the chart view
    ui->chartWidget->setChart(chart);
    ui->chartWidget->setRenderHint(QPainter::Antialiasing);
    connect(ui->comboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), [=](int index) {
        if (index == 0) {
            ui->chartWidget->setChart(chart);
        } else if (index == 1) {
            QStringList categoriesType;
            QList<qreal> teamsType;
            competition::extractDataFromDatabaseType(categoriesType, teamsType, "League");

            QBarSet *setType = new QBarSet("Teams");

            for (int i = 0; i < teamsType.size() && i < 10; ++i) {
                *setType << teamsType[i];
            }

            setType->setBrush(QBrush(QColor("#3D8B7A")));
            setType->setPen(QPen(QColor("#3D8B7A")));

            QBarSeries *seriesType = new QBarSeries();
            seriesType->append(setType);

            QChart *chartType = new QChart();
            chartType->addSeries(seriesType);
            chartType->setTitle("Number of Teams per Competition (League)");
            chartType->setAnimationOptions(QChart::SeriesAnimations);
            chartType->setBackgroundBrush(QBrush(QColor("#1A3C34")));

            QFont titleFontType = chartType->titleFont();
            titleFontType.setPointSize(12);
            chartType->setTitleFont(titleFontType);
            chartType->setTitleBrush(QBrush(QColor("#E0E0E0")));

            QBarCategoryAxis *axisXType = new QBarCategoryAxis();
            axisXType->append(categoriesType);
            axisXType->setTitleText("Competitions");
            axisXType->setLabelsColor(QColor("#E0E0E0"));
            axisXType->setTitleBrush(QBrush(QColor("#E0E0E0")));
            chartType->addAxis(axisXType, Qt::AlignBottom);
            seriesType->attachAxis(axisXType);

            QValueAxis *axisYType = new QValueAxis();
            axisYType->setRange(0, 30);
            axisYType->setTitleText("Number of Teams");
            axisYType->setLabelsColor(QColor("#E0E0E0"));
            axisYType->setTitleBrush(QBrush(QColor("#E0E0E0")));
            chartType->addAxis(axisYType, Qt::AlignLeft);
            seriesType->attachAxis(axisYType);

            ui->chartWidget->setChart(chartType);
        } else if (index == 2) {
            QStringList categoriesType;
            QList<qreal> teamsType;
            competition::extractDataFromDatabaseType(categoriesType, teamsType, "Tournament");

            QBarSet *setType = new QBarSet("Teams");

            for (int i = 0; i < teamsType.size() && i < 10; ++i) {
                *setType << teamsType[i];
            }

            setType->setBrush(QBrush(QColor("#3D8B7A")));
            setType->setPen(QPen(QColor("#3D8B7A")));

            QBarSeries *seriesType = new QBarSeries();
            seriesType->append(setType);

            QChart *chartType = new QChart();
            chartType->addSeries(seriesType);
            chartType->setTitle("Number of Teams per Competition (Tournament)");
            chartType->setAnimationOptions(QChart::SeriesAnimations);
            chartType->setBackgroundBrush(QBrush(QColor("#1A3C34")));

            QFont titleFontType = chartType->titleFont();
            titleFontType.setPointSize(12);
            chartType->setTitleFont(titleFontType);
            chartType->setTitleBrush(QBrush(QColor("#E0E0E0")));

            QBarCategoryAxis *axisXType = new QBarCategoryAxis();
            axisXType->append(categoriesType);
            axisXType->setTitleText("Competitions");
            axisXType->setLabelsColor(QColor("#E0E0E0"));
            axisXType->setTitleBrush(QBrush(QColor("#E0E0E0")));
            chartType->addAxis(axisXType, Qt::AlignBottom);
            seriesType->attachAxis(axisXType);

            QValueAxis *axisYType = new QValueAxis();
            axisYType->setRange(0, 30);
            axisYType->setTitleText("Number of Teams");
            axisYType->setLabelsColor(QColor("#E0E0E0"));
            axisYType->setTitleBrush(QBrush(QColor("#E0E0E0")));
            chartType->addAxis(axisYType, Qt::AlignLeft);
            seriesType->attachAxis(axisYType);

            ui->chartWidget->setChart(chartType);
        }
    });
}

statistics::~statistics()
{
    delete ui;
}

void statistics::on_exportButton_clicked()
{
    QString filePath = QFileDialog::getSaveFileName(this, "Save Chart", "", "PNG Files (*.png)");
    if (!filePath.isEmpty()) {
        QPixmap pixmap(ui->chartWidget->size());
        QPainter painter(&pixmap);
        ui->chartWidget->render(&painter);

        //QPainter painter(&pixmap);
        painter.setPen(Qt::black);
        painter.setFont(QFont("Arial", 10));

        QString dateTime = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
        painter.drawText(pixmap.rect(), Qt::AlignBottom | Qt::AlignRight, dateTime);

        if (pixmap.save(filePath)) {
            QMessageBox::information(this, "Export Successful", "Chart has been saved successfully.");
        } else {
            QMessageBox::warning(this, "Export Failed", "Failed to save the chart.");
        }
    }
}




void statistics::on_previousButton_clicked()
{
    statistics2 *s = new statistics2();
    s->show();
    this->close();
}


void statistics::on_nextButton_clicked()
{
    statistics2 *s = new statistics2();
    s->show();
    this->close();
}

