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

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Set up table widget columns
    ui->tableWidget->setColumnCount(5);
    QStringList headers = {"Team Name", "Home Stadium", "Budget", "Team ABV", "Team Logo"};
    ui->tableWidget->setHorizontalHeaderLabels(headers);

    ui->tableWidget->setIconSize(QSize(30, 30));
    ui->tableWidget->setColumnWidth(0, 150);
    ui->tableWidget->setColumnWidth(1, 200);
    ui->tableWidget->setColumnWidth(2, 100);
    ui->tableWidget->setColumnWidth(3, 100);
    ui->tableWidget->setColumnWidth(4, 120);

    ui->tableWidget->setSortingEnabled(true);
    connect(ui->tableWidget->horizontalHeader(), &QHeaderView::sectionClicked, this, &MainWindow::on_tableWidget_sectionClicked);


    loadTeams();
    if (!QSqlDatabase::database().isOpen()) {
        qDebug() << "Database connection failed to open in MainWindow!";
        QMessageBox::critical(this, "Error", "Database connection is not open!");
    }

    // Set up the pie chart in the Stats tab
    setupBudgetPieChart();

    // Connect the Confirm button to the slot
    connect(ui->button1, &QPushButton::clicked, this, &MainWindow::on_addButtonclicked);

    connect(ui->tableWidget->model(), &QAbstractItemModel::rowsInserted, this, &MainWindow::updateBudgetPieChart);
    connect(ui->tableWidget->model(), &QAbstractItemModel::rowsRemoved, this, &MainWindow::updateBudgetPieChart);
    connect(ui->tableWidget, &QTableWidget::itemChanged, this, &MainWindow::updateBudgetPieChart);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_toolButton_clicked()
{
    qDebug() << "on_toolButton_clicked called";

    // Open file dialog starting at "This PC" (approximated by "C:/")
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Select Team Logo"),
                                                    "C:/",  // Start at C:/ to approximate "This PC"
                                                    tr("Images (*.png *.jpg *.jpeg *.bmp)"));
    if (!fileName.isEmpty()) {
        QFile file(fileName);
        if (file.open(QIODevice::ReadOnly)) {
            teamLogo = file.readAll();  // Store the image data in the member variable
            file.close();
            ui->label_2->setText(QFileInfo(fileName).fileName());
            qDebug() << "Image loaded, size:" << teamLogo.size() << "bytes";
        } else {
            QMessageBox::warning(this, "File Error", "Could not open the selected image.");
            ui->label_2->setText("insert logo here");
        }
    } else {
        ui->label_2->setText("insert logo here");
    }
}

void MainWindow::on_addButtonclicked()
{
    QString teamName = ui->l1->text();
    QString homeStadium = ui->cb->currentText();
    QString budgetText = ui->l2->text();
    QString teamABV = ui->l2_2->text();

    // Validate required fields
    if (teamName.isEmpty() || homeStadium.isEmpty() || budgetText.isEmpty() || teamABV.isEmpty() || teamLogo.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Please fill in all required fields and select a team logo.");
        return;
    }

    // Validate Team Name (only alphabets)
    QRegularExpression reAlpha("^[A-Za-z]+$");
    if (!reAlpha.match(teamName).hasMatch()) {
        QMessageBox::warning(this, "Input Error", "Team Name must contain only alphabets.");
        return;
    }

    // Validate Budget (only numbers)
    bool ok;
    int budget = budgetText.toInt(&ok);
    if (!ok) {
        QMessageBox::warning(this, "Input Error", "Budget must be a valid integer.");
        return;
    }

    // Validate Team ABV (only uppercase alphabets)
    QRegularExpression reUpperAlpha("^[A-Z]+$");
    if (!reUpperAlpha.match(teamABV).hasMatch()) {
        QMessageBox::warning(this, "Input Error", "Team ABV must contain only uppercase alphabets.");
        return;
    }

    // Create a new team using setters
    Team newTeam;
    newTeam.setTeamName(teamName);
    newTeam.setHomeStadium(homeStadium);
    newTeam.setBudget(budget);
    newTeam.setTeamABV(teamABV);
    newTeam.setTeamLogo(teamLogo);  // Use the stored logo data

    if (newTeam.Ajouter()) {
        QMessageBox::information(this, "Success", "Team added successfully!");

        // Clear input fields
        ui->l1->clear();
        ui->l2->clear();
        ui->l2_2->clear();
        ui->label_2->setText("insert logo here");
        teamLogo.clear();  // Clear the stored logo data
        ui->cb->setCurrentIndex(0);

        // Add the new team to the table widget
        int row = ui->tableWidget->rowCount();
        ui->tableWidget->insertRow(row);
        ui->tableWidget->setItem(row, 0, new QTableWidgetItem(teamName));
        ui->tableWidget->setItem(row, 1, new QTableWidgetItem(homeStadium));
        ui->tableWidget->setItem(row, 2, new QTableWidgetItem(QString::number(budget)));
        ui->tableWidget->setItem(row, 3, new QTableWidgetItem(teamABV));

        // Set the logo as an icon in the table widget
        QTableWidgetItem *logoItem = new QTableWidgetItem();
        QPixmap pixmap;
        pixmap.loadFromData(teamLogo);
        logoItem->setIcon(QIcon(pixmap));
        ui->tableWidget->setItem(row, 4, logoItem);

        // Update the pie chart
        updateBudgetPieChart();
    } else {
        QMessageBox::critical(this, "Error", "Failed to add team to the database.");
    }
}

void MainWindow::on_deleteButton_clicked()
{
    int currentRow = ui->tableWidget->currentRow();
    if (currentRow >= 0) {
        QString teamName = ui->tableWidget->item(currentRow, 0)->text();

        // Remove the team from the database
        QSqlQuery query;
        query.prepare("DELETE FROM HOTSTUFF.EQUIPE WHERE TEAM_NAME = :team_name");
        query.bindValue(":team_name", teamName);
        if (query.exec()) {
            // Remove the row from the table widget
            ui->tableWidget->removeRow(currentRow);
            QMessageBox::information(this, "Success", "Team deleted successfully!");

            // Update the pie chart
            updateBudgetPieChart();
        } else {
            qDebug() << "Failed to delete team from the database:" << query.lastError().text();
            QMessageBox::critical(this, "Error", "Failed to delete team from the database.");
        }
    } else {
        QMessageBox::warning(this, "Selection Error", "Please select a row to delete.");
    }
}

void MainWindow::on_deleteButton_2_clicked()
{
    if (ui->tableWidget->rowCount() == 0) {
        QMessageBox::information(this, "No Data", "The table is already empty.");
        return;
    }

    // Confirm deletion
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Delete All", "Are you sure you want to delete all rows?",
                                  QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        // Clear the table widget
        ui->tableWidget->setRowCount(0);

        // Clear the database table
        QSqlQuery query;
        if (query.exec("DELETE FROM HOTSTUFF.EQUIPE")) {
            QMessageBox::information(this, "Success", "All teams have been deleted successfully!");

            // Update the pie chart
            updateBudgetPieChart();
        } else {
            QMessageBox::critical(this, "Error", "Failed to delete teams from the database: " + query.lastError().text());
        }
    }
}

void MainWindow::loadTeams()
{
    QSqlQuery query("SELECT TEAM_NAME, HOME_STADIUM, BUDG, TEAM_ABV, TEAM_LOGO FROM HOTSTUFF.EQUIPE");
    qDebug() << "Loading teams from database...";
    while (query.next()) {
        QString teamName = query.value(0).toString();
        QString homeStadium = query.value(1).toString();
        int budget = query.value(2).toInt();
        QString teamABV = query.value(3).toString();
        QByteArray teamLogo = query.value(4).toByteArray();

        int row = ui->tableWidget->rowCount();
        ui->tableWidget->insertRow(row);
        ui->tableWidget->setItem(row, 0, new QTableWidgetItem(teamName));
        ui->tableWidget->setItem(row, 1, new QTableWidgetItem(homeStadium));
        ui->tableWidget->setItem(row, 2, new QTableWidgetItem(QString::number(budget)));
        ui->tableWidget->setItem(row, 3, new QTableWidgetItem(teamABV));

        // Set the logo as an icon in the table widget
        QTableWidgetItem *logoItem = new QTableWidgetItem();
        QPixmap pixmap;
        pixmap.loadFromData(teamLogo);
        logoItem->setIcon(QIcon(pixmap));
        ui->tableWidget->setItem(row, 4, logoItem);
        qDebug() << "Loaded team:" << teamName << homeStadium << budget << teamABV;
    }
    qDebug() << "Finished loading teams, total rows:" << ui->tableWidget->rowCount();
}

void MainWindow::on_resetButton_clicked()
{
    // Clear input fields
    ui->l1->clear();
    ui->l2->clear();
    ui->l2_2->clear();
    ui->label_2->setText("insert logo here");
    teamLogo.clear();  // Clear the stored logo data
    ui->cb->setCurrentIndex(0);
}

void MainWindow::on_searchBar_textChanged(const QString &text)
{
    for (int i = 0; i < ui->tableWidget->rowCount(); ++i) {
        bool match = ui->tableWidget->item(i, 0)->text().contains(text, Qt::CaseInsensitive);
        ui->tableWidget->setRowHidden(i, !match);
    }
}

void MainWindow::on_tableWidget_sectionClicked(int logicalIndex)
{
    if (logicalIndex == 2) {  // Assuming the budget column is the third column (index 2)
        ui->tableWidget->sortItems(logicalIndex, Qt::AscendingOrder);
    } else {
        ui->tableWidget->sortItems(logicalIndex);
    }
}

void MainWindow::on_modifyButton_clicked()
{
    int currentRow = ui->tableWidget->currentRow();
    if (currentRow >= 0) {
        QString teamName = ui->tableWidget->item(currentRow, 0)->text();
        QString homeStadium = ui->tableWidget->item(currentRow, 1)->text();
        int budget = ui->tableWidget->item(currentRow, 2)->text().toInt();
        QString teamABV = ui->tableWidget->item(currentRow, 3)->text();

        QSqlQuery query;
        query.prepare("SELECT TEAM_LOGO FROM HOTSTUFF.EQUIPE WHERE TEAM_NAME = :team_name");
        query.bindValue(":team_name", teamName);
        if (query.exec() && query.next()) {
            QByteArray teamLogo = query.value(0).toByteArray();

            ModifyTeam modifyTeamDialog(this);
            modifyTeamDialog.setTeamData(teamName, homeStadium, budget, teamABV, teamLogo);

            if (modifyTeamDialog.exec() == QDialog::Accepted) {
                // Refresh the table
                ui->tableWidget->clearContents();
                ui->tableWidget->setRowCount(0);
                loadTeams();
                qDebug() << "Table refreshed after modification.";
            }
        } else {
            qDebug() << "Failed to fetch team logo:" << query.lastError().text();
            QMessageBox::critical(this, "Error", "Failed to fetch team logo from the database.");
        }
    } else {
        QMessageBox::warning(this, "Selection Error", "Please select a team to modify.");
    }
}

void MainWindow::on_downloadButton_clicked()
{
    int selectedRow = ui->tableWidget->currentRow();
    if (selectedRow < 0) {
        QMessageBox::warning(this, "Selection Error", "Please select a row to download its data.");
        return;
    }

    if (ui->tableWidget->rowCount() == 0) {
        QMessageBox::warning(this, "No Data", "The table is empty. There is nothing to download.");
        return;
    }

    QString teamName = ui->tableWidget->item(selectedRow, 0)->text(); // Team Name (column 0)
    QTableWidgetItem *logoItem = ui->tableWidget->item(selectedRow, 4); // Team Logo (column 4)
    QString fileName = QFileDialog::getSaveFileName(this, "Save " + teamName + " Data", "", "PDF Files (*.pdf);;All Files (*)");
    if (fileName.isEmpty()) {
        return;
    }

    // Set up PDF writer
    QPdfWriter pdfWriter(fileName);
    pdfWriter.setPageSize(QPageSize(QPageSize::A4));
    pdfWriter.setPageMargins(QMarginsF(30, 30, 30, 30));
    pdfWriter.setResolution(300);

    QPainter painter(&pdfWriter);
    painter.setRenderHint(QPainter::Antialiasing);

    // Define dimensions
    const int pageWidth = pdfWriter.width();
    const int pageHeight = pdfWriter.height();
    const int margin = 100;
    const int logoSize = 150; // Smaller logo size to match form
    const int rowHeight = 80; // Increased row height for more spacing
    const int labelWidth = 250; // Increased from 200 to 250 to fit "HOME STADIUM"
    const int valueWidth = pageWidth - 2 * margin - labelWidth - 20; // Adjusted width for values

    // Parchment-like background
    painter.setBrush(QColor(245, 235, 200)); // Light beige parchment color
    painter.setPen(Qt::NoPen);
    painter.drawRect(0, 0, pageWidth, pageHeight);

    // Border to mimic the form's edge
    painter.setPen(QPen(QColor(139, 69, 19), 10)); // Brown border
    painter.drawRect(0, 0, pageWidth, pageHeight);

    // Centered team logo at the top
    int logoX = (pageWidth - logoSize) / 2;
    int logoY = margin;
    if (logoItem && !logoItem->icon().isNull()) {
        QPixmap pixmap = logoItem->icon().pixmap(QSize(logoSize, logoSize));
        painter.drawPixmap(logoX, logoY, pixmap);
    }

    // Title and team name with increased spacing
    painter.setFont(QFont("Arial", 16, QFont::Bold));
    painter.setPen(Qt::black);
    QString title = teamName.toUpper() + " FOOTBALL CLUB";
    int titleWidth = painter.fontMetrics().horizontalAdvance(title);
    painter.drawText((pageWidth - titleWidth) / 2, logoY + logoSize + 60, title);

    painter.setFont(QFont("Arial", 12, QFont::Bold));
    QString subtitle = "Team Profile - " + QDateTime::currentDateTime().toString("yyyy");
    int subtitleWidth = painter.fontMetrics().horizontalAdvance(subtitle);
    painter.drawText((pageWidth - subtitleWidth) / 2, logoY + logoSize + 100, subtitle);

    // Data section (excluding Team Name and Team Logo) with increased spacing
    int y = logoY + logoSize + 180; // Start lower to add space after subtitle
    QStringList headers = {"Home Stadium", "Budget", "Team ABV"};
    for (int col = 1; col < ui->tableWidget->columnCount() - 1; ++col) { // Skip col 0 and 4
        QTableWidgetItem *item = ui->tableWidget->item(selectedRow, col);
        QString value = item ? item->text() : "";

        // Draw label with wrapping to ensure full text appears
        QRect labelRect(margin, y, labelWidth, rowHeight);
        painter.setBrush(Qt::transparent);
        painter.setPen(Qt::black);
        painter.setFont(QFont("Arial", 10, QFont::Bold));
        painter.drawText(labelRect.adjusted(10, 0, -10, 0), Qt::AlignVCenter | Qt::AlignLeft | Qt::TextWordWrap, headers[col - 1].toUpper());

        // Draw value with underline (form-like), allow wrapping
        QRect valueRect(margin + labelWidth + 20, y, valueWidth, rowHeight);
        painter.setFont(QFont("Arial", 10));
        painter.drawText(valueRect.adjusted(10, 0, -10, 0), Qt::AlignVCenter | Qt::AlignLeft | Qt::TextWordWrap, value);
        painter.setPen(QPen(Qt::black, 1));
        painter.drawLine(valueRect.left() + 10, valueRect.bottom() - 10, valueRect.right() - 10, valueRect.bottom() - 10);

        y += rowHeight + 20; // Increased spacing between data rows
    }

    // Footer section (mimicking the form's consent and signature) with more spacing
    y += 40; // Increased space before consent text
    painter.setFont(QFont("Arial", 8));
    painter.setPen(Qt::black);
    QString consentText = "I hereby confirm the accuracy of the above team information and agree to abide by the rules.";
    QRect consentRect(margin, y, pageWidth - 2 * margin, 60);
    painter.drawText(consentRect, Qt::AlignLeft | Qt::TextWordWrap, consentText);

    y += 100; // Increased space before signature
    painter.setFont(QFont("Arial", 10, QFont::Bold));
    painter.drawText(margin, y, "Team Manager Signature: ___________________________");

    // Add current date to the "Date" field, moved to the left
    QString currentDate = QDateTime::currentDateTime().toString("dd/MM/yyyy");
    painter.drawText(pageWidth - margin - 300, y, "Date: " + currentDate);

    // Add a decorative football line with more spacing
    y += 60; // Increased space before the line
    painter.setPen(QPen(Qt::black, 2));
    painter.drawLine(margin, y, pageWidth - margin, y);
    
    QFont footerFont("Arial", 8);
    footerFont.setItalic(true);
    painter.setFont(footerFont);
    painter.drawText(margin, y + 30, "Official Team Document"); // Increased space after the line

    painter.end();

    QMessageBox::information(this, "Download Complete", QString("The data for '%1' has been downloaded successfully as a PDF.").arg(teamName));
}


void MainWindow::setupBudgetPieChart()
{
    // Create a pie series
    budgetSeries = new QPieSeries();
    budgetSeries->setHoleSize(0.35);  // Optional: Adds a donut effect

    // Fetch budget data from the database
    QSqlQuery query("SELECT TEAM_NAME, BUDG FROM HOTSTUFF.EQUIPE");
    while (query.next()) {
        QString teamName = query.value(0).toString();
        int budget = query.value(1).toInt();
        QPieSlice *slice = budgetSeries->append(teamName, budget);  // Add each team's budget to the pie series

        // Connect the hovered signal to a slot
        connect(slice, &QPieSlice::hovered, this, &MainWindow::onPieSliceHovered);
    }

    // Customize the pie slices (optional)
    for (QPieSlice *slice : budgetSeries->slices()) {
        slice->setLabel(QString("%1\n%2%").arg(slice->label()).arg(slice->percentage() * 100, 0, 'f', 1));
        slice->setLabelVisible(true);
        slice->setLabelPosition(QPieSlice::LabelOutside);
    }

    // Create a chart and add the series
    QChart *chart = new QChart();
    chart->addSeries(budgetSeries);
    chart->setTitle("Team Budget Distribution");
    chart->setTheme(QChart::ChartThemeDark);  // Matches the dark UI theme
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignRight);

    // Enable animations for the chart
    chart->setAnimationOptions(QChart::SeriesAnimations);  // Animates the pie slices

    // Create a chart view and set it in the Stats tab
    chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    // Add the chart view to the Stats tab layout
    QVBoxLayout *layout = new QVBoxLayout(ui->tab_3);
    layout->addWidget(chartView);
    ui->tab_3->setLayout(layout);
}

void MainWindow::updateBudgetPieChart()
{
    if (!budgetSeries) return;  // Ensure the series is initialized

    // Clear the existing data
    budgetSeries->clear();

    // Fetch updated budget data from the database
    QSqlQuery query("SELECT TEAM_NAME, BUDG FROM HOTSTUFF.EQUIPE");
    while (query.next()) {
        QString teamName = query.value(0).toString();
        int budget = query.value(1).toInt();
        budgetSeries->append(teamName, budget);  // Add each team's budget to the pie series
    }

    // Update the labels for the slices
    for (QPieSlice *slice : budgetSeries->slices()) {
        slice->setLabel(QString("%1\n%2%").arg(slice->label()).arg(slice->percentage() * 100, 0, 'f', 1));
        slice->setLabelVisible(true);
        slice->setLabelPosition(QPieSlice::LabelOutside);
    }
}

void MainWindow::onPieSliceHovered(bool state)
{
    QPieSlice *slice = qobject_cast<QPieSlice *>(sender());
    if (slice) {
        if (state) {
            slice->setExploded(true);                // Make the slice pop out
            slice->setExplodeDistanceFactor(0.15);   // Adjust the distance it pops out
            slice->setLabelFont(QFont("Arial", 12, QFont::Bold)); // Highlight the label
        } else {
            slice->setExploded(false);              // Reset the slice
            slice->setExplodeDistanceFactor(0.0);   // Reset the explode distance
            slice->setLabelFont(QFont("Arial", 10)); // Reset the label font
        }
    }
}

void MainWindow::on_pushButton_clicked()
{
    ChatDialog *chatDialog = new ChatDialog(this);
    chatDialog->setModal(false); // Non-modal so you can still interact with the main window
    chatDialog->show();
}
