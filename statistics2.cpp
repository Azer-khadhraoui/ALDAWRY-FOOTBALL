#include "statistics2.h"
#include "ui_statistics2.h"
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
#include "statistics.h"

statistics2::statistics2(QWidget *parent):
    QDialog(parent),
    ui(new Ui::statistics2)
{
    ui->setupUi(this);
    competition c;
    // Extract data from the database
    QStringList categories;
    QList<qreal> matches;
    competition::extractDataFromDatabaseMatches(categories, matches);

    // Debug: Print extracted data
    qDebug() << "Categories:" << categories;
    qDebug() << "Matches:" << matches;

    // Create bar set
    QBarSet *set = new QBarSet("Matches");

    // Check the size of the matches list before accessing its elements
    for (int i = 0; i < matches.size() && i < 10; ++i) {
        *set << matches[i];
    }

    set->setBrush(QBrush(QColor("#3D8B7A")));
    set->setPen(QPen(QColor("#3D8B7A")));

    // Create bar series
    QBarSeries *series = new QBarSeries();
    series->append(set);

    // Create chart
    chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Number of Matches per Competition");
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

    // Y-axis (matches)
    QValueAxis *axisY = new QValueAxis();
    axisY->setRange(0, 30);
    axisY->setTitleText("Number of Matches");
    axisY->setLabelsColor(QColor("#E0E0E0"));
    axisY->setTitleBrush(QBrush(QColor("#E0E0E0")));
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    ui->chartWidget->setChart(chart);
    ui->chartWidget->setRenderHint(QPainter::Antialiasing);
    connect(ui->comboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), [=](int index) {
        if (index == 0) {
            QStringList categories;
            QList<qreal> matches;
            competition::extractDataFromDatabaseMatches(categories, matches);

            QBarSet *set = new QBarSet("Matches");

            for (int i = 0; i < matches.size() && i < 10; ++i) {
                *set << matches[i];
            }

            set->setBrush(QBrush(QColor("#3D8B7A")));
            set->setPen(QPen(QColor("#3D8B7A")));

            QBarSeries *series = new QBarSeries();
            series->append(set);

            QChart *chart = new QChart();
            chart->addSeries(series);
            chart->setTitle("Number of Matches per Competition");
            chart->setAnimationOptions(QChart::SeriesAnimations);
            chart->setBackgroundBrush(QBrush(QColor("#1A3C34")));

            QFont titleFont = chart->titleFont();
            titleFont.setPointSize(12);
            chart->setTitleFont(titleFont);
            chart->setTitleBrush(QBrush(QColor("#E0E0E0")));

            QBarCategoryAxis *axisX = new QBarCategoryAxis();
            axisX->append(categories);
            axisX->setTitleText("Competitions");
            axisX->setLabelsColor(QColor("#E0E0E0"));
            axisX->setTitleBrush(QBrush(QColor("#E0E0E0")));
            chart->addAxis(axisX, Qt::AlignBottom);
            series->attachAxis(axisX);

            QValueAxis *axisY = new QValueAxis();
            axisY->setRange(0, 30);
            axisY->setTitleText("Number of Matches");
            axisY->setLabelsColor(QColor("#E0E0E0"));
            axisY->setTitleBrush(QBrush(QColor("#E0E0E0")));
            chart->addAxis(axisY, Qt::AlignLeft);
            series->attachAxis(axisY);

            ui->chartWidget->setChart(chart);
        } else if (index == 1) {
            QStringList categories;
            QList<qreal> matches;
            competition::extractDataFromDatabaseMatchesType(categories, matches, "League");

            QBarSet *set = new QBarSet("Matches");

            for (int i = 0; i < matches.size() && i < 10; ++i) {
                *set << matches[i];
            }
            set->setBrush(QBrush(QColor("#3D8B7A")));
            set->setPen(QPen(QColor("#3D8B7A")));

            QBarSeries *series = new QBarSeries();
            series->append(set);

            QChart *chart = new QChart();
            chart->addSeries(series);
            chart->setTitle("Number of Matches per Competition");
            chart->setAnimationOptions(QChart::SeriesAnimations);
            chart->setBackgroundBrush(QBrush(QColor("#1A3C34")));

            QFont titleFont = chart->titleFont();
            titleFont.setPointSize(12);
            chart->setTitleFont(titleFont);
            chart->setTitleBrush(QBrush(QColor("#E0E0E0")));

            QBarCategoryAxis *axisX = new QBarCategoryAxis();
            axisX->append(categories);
            axisX->setTitleText("Competitions");
            axisX->setLabelsColor(QColor("#E0E0E0"));
            axisX->setTitleBrush(QBrush(QColor("#E0E0E0")));
            chart->addAxis(axisX, Qt::AlignBottom);
            series->attachAxis(axisX);

            QValueAxis *axisY = new QValueAxis();
            axisY->setRange(0, 30);
            axisY->setTitleText("Number of Matches");
            axisY->setLabelsColor(QColor("#E0E0E0"));
            axisY->setTitleBrush(QBrush(QColor("#E0E0E0")));
            chart->addAxis(axisY, Qt::AlignLeft);
            series->attachAxis(axisY);

            ui->chartWidget->setChart(chart);
        } else if (index == 2) {
            QStringList categories;
            QList<qreal> matches;
            competition::extractDataFromDatabaseMatchesType(categories, matches, "Tournament");

            QBarSet *set = new QBarSet("Matches");

            for (int i = 0; i < matches.size() && i < 10; ++i) {
                *set << matches[i];
            }
            set->setBrush(QBrush(QColor("#3D8B7A")));
            set->setPen(QPen(QColor("#3D8B7A")));

            QBarSeries *series = new QBarSeries();
            series->append(set);

            QChart *chart = new QChart();
            chart->addSeries(series);
            chart->setTitle("Number of Matches per Competition");
            chart->setAnimationOptions(QChart::SeriesAnimations);
            chart->setBackgroundBrush(QBrush(QColor("#1A3C34")));

            QFont titleFont = chart->titleFont();
            titleFont.setPointSize(12);
            chart->setTitleFont(titleFont);
            chart->setTitleBrush(QBrush(QColor("#E0E0E0")));

            QBarCategoryAxis *axisX = new QBarCategoryAxis();
            axisX->append(categories);
            axisX->setTitleText("Competitions");
            axisX->setLabelsColor(QColor("#E0E0E0"));
            axisX->setTitleBrush(QBrush(QColor("#E0E0E0")));
            chart->addAxis(axisX, Qt::AlignBottom);
            series->attachAxis(axisX);

            QValueAxis *axisY = new QValueAxis();
            axisY->setRange(0, 30);
            axisY->setTitleText("Number of Matches");
            axisY->setLabelsColor(QColor("#E0E0E0"));
            axisY->setTitleBrush(QBrush(QColor("#E0E0E0")));
            chart->addAxis(axisY, Qt::AlignLeft);
            series->attachAxis(axisY);

            ui->chartWidget->setChart(chart);
        }

    });
}

statistics2::~statistics2()
{
    delete ui;
}


void statistics2::on_exportButton_clicked()
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


void statistics2::on_previousButton_clicked()
{
    statistics *s = new statistics();
    s->show();
    this->close();
}


void statistics2::on_nextButton_clicked()
{
    statistics *s = new statistics();
    s->show();
    this->close();
}

