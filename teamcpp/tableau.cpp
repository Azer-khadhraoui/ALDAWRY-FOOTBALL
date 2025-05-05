#include "../teamheaders/tableau.h"
#include "ui_tableau.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QPixmap>
#include <QDebug>
#include <QFileDialog>
#include <QPdfWriter>
#include <QPainter>
#include <QMessageBox>
#include "../teamheaders/modifyteam.h" // Include the ModifyTeam class

Tableau::Tableau(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Tableau)
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

    // Load teams into the table
    loadTeams();

    // Connect the search bar to the search functionality
    connect(ui->searchBar, &QLineEdit::textChanged, this, &Tableau::on_searchBar_textChanged);




}

Tableau::~Tableau()
{
    delete ui;
}

void Tableau::loadTeams()
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

void Tableau::on_searchBar_textChanged(const QString &text)
{
    for (int i = 0; i < ui->tableWidget->rowCount(); ++i) {
        bool match = ui->tableWidget->item(i, 0)->text().contains(text, Qt::CaseInsensitive);
        ui->tableWidget->setRowHidden(i, !match);
    }
}

void Tableau::on_downloadButton_clicked()
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


void Tableau::on_deleteButton_clicked()
{
    int currentRow = ui->tableWidget->currentRow();
    if (currentRow >= 0) {
        QString teamName = ui->tableWidget->item(currentRow, 0)->text();

        // Remove the team from the database
        QSqlQuery query;
        query.prepare("DELETE FROM HOTSTUFF.EQUIPE WHERE TEAM_NAME = :teamName");
        query.bindValue(":teamName", teamName);
        if (query.exec()) {
            ui->tableWidget->removeRow(currentRow);
            QMessageBox::information(this, "Success", "Team deleted successfully!");
        } else {
            QMessageBox::critical(this, "Error", "Failed to delete team from the database.");
        }
    } else {
        QMessageBox::warning(this, "Warning", "Please select a team to delete.");
    }
}

void Tableau::on_modifyButton_clicked()
{
    // Create an instance of the ModifyTeam dialog
    ModifyTeam *modifyTeamDialog = new ModifyTeam(this);

    // Connect the signal to update the table
    connect(modifyTeamDialog, &ModifyTeam::teamModified, this, &Tableau::updateTeamInTable);

    // Show the dialog as a modal window
    modifyTeamDialog->exec();
}

void Tableau::updateTeamInTable(const QString &teamName, const QString &homeStadium, int budget, const QString &teamABV)
{
    int currentRow = ui->tableWidget->currentRow();
    if (currentRow >= 0) {
        // Update the selected row with the new data
        ui->tableWidget->item(currentRow, 0)->setText(teamName);
        ui->tableWidget->item(currentRow, 1)->setText(homeStadium);
        ui->tableWidget->item(currentRow, 2)->setText(QString::number(budget));
        ui->tableWidget->item(currentRow, 3)->setText(teamABV);

        QMessageBox::information(this, "Success", "Team updated successfully!");
    } else {
        QMessageBox::warning(this, "Warning", "No row selected to update.");
    }
}
