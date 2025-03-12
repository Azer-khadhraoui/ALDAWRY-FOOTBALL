#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "match.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QMessageBox>
#include <QDebug>
#include <QDateTime>
#include <QSqlTableModel>
#include <QStandardItemModel>
#include <QInputDialog>
#include <QFormLayout>
#include <QDialog>
#include <QDialogButtonBox>
#include <QComboBox>
#include <QLineEdit>
#include <QDateTimeEdit>
#include <QSpinBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , matchModel(new QSqlTableModel(this)) // Initialize matchModel
    , ascendingOrder(true) // Initialize ascendingOrder
{
    ui->setupUi(this);

    // Set the minimum date and time to the current date and time to prevent past selections
    ui->Date->setMinimumDateTime(QDateTime::currentDateTime());

    // Attempt to connect to the database
    if (dbConnection.createconnect()) {
        qDebug() << "Database connected successfully in MainWindow";
        // Load teams and competitions into combo boxes
        Match::loadTeamsIntoComboBoxes(ui->team1, ui->team2);
        Match::loadCompetitionsIntoComboBox(ui->Comp);
        
        setupMatchTable();
        
    } else {
        qDebug() << "Failed to connect to database in MainWindow";
        // Disable combo boxes and show an error message
        ui->team1->setEnabled(false);
        ui->team2->setEnabled(false);
        ui->Comp->setEnabled(false);
        QMessageBox::critical(this, "Error", "Database connection failed. Teams and competitions cannot be loaded.");
    }

    // Set the current date and time in the Date QDateTimeEdit
    ui->Date->setDateTime(QDateTime::currentDateTime());

    // Connect the search line edit to the search slot
    connect(ui->search, &QLineEdit::textChanged, this, &MainWindow::on_search_textChanged);

    // Connect the sort button to the sort slot
    connect(ui->sort, &QPushButton::clicked, this, &MainWindow::on_sort_clicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_Confirm_clicked()
{
    // Retrieve values from UI widgets
    int team1Id = ui->team1->currentData().toInt();
    int team2Id = ui->team2->currentData().toInt();
    QString stadium = ui->Stadium->text();
    QString referee = ui->Referee_name->text();
    int compId = ui->Comp->currentData().toInt();
    QDateTime matchDate = ui->Date->dateTime();

    // Validate inputs: teams must be different and stadium/referee cannot be empty
    if (team1Id == team2Id) {
        QMessageBox::warning(this, "Error", "Teams must be different!");
        return;
    }
    if (stadium.isEmpty() || referee.isEmpty()) {
        QMessageBox::warning(this, "Error", "Stadium and Referee name are required!");
        return;
    }

    // Validate that the selected date and time is not in the past
    if (matchDate < QDateTime::currentDateTime()) {
        QMessageBox::warning(this, "Error", "The selected date and time cannot be in the past!");
        return;
    }

    // Create a new Match object and set its properties
    Match match;
    match.setId(Match::generateNewMatchId());
    match.setTeamA(team1Id);
    match.setTeamB(team2Id);
    match.setStadium(stadium);
    match.setReferee(referee);
    match.setCompetitionId(compId);
    match.setStatus("Scheduled");
    match.setMatchDateTime(matchDate);

    // Attempt to add the match to the database
    if (match.addMatch()) {
        QMessageBox::information(this, "Success", "Match added successfully!");
        // Clear/reset fields after success
        ui->Referee_name->clear();
        ui->Stadium->clear();
        ui->Date->setDateTime(QDateTime::currentDateTime());
        setupMatchTable(); // Refresh the table
    } else {
        QMessageBox::critical(this, "Error", "Failed to add match!");
    }
}

void MainWindow::setupMatchTable() {
    QList<Match> matches = Match::readAllMatches(); // Use readAllMatches to get data

    // Create a QStandardItemModel to hold the data
    QStandardItemModel *model = new QStandardItemModel(matches.size(), 6, this); // Change column count to 6
    model->setHeaderData(0, Qt::Horizontal, tr("ID")); // Add ID column
    model->setHeaderData(1, Qt::Horizontal, tr("Team 1")); // Add Team 1 column
    model->setHeaderData(2, Qt::Horizontal, tr("Team 2")); // Add Team 2 column
    model->setHeaderData(3, Qt::Horizontal, tr("Date"));
    model->setHeaderData(4, Qt::Horizontal, tr("Time"));
    model->setHeaderData(5, Qt::Horizontal, tr("Competition")); // Add Competition column

    // Populate the model with data
    for (int row = 0; row < matches.size(); ++row) {
        const Match &match = matches.at(row);
        model->setData(model->index(row, 0), match.getId()); // Add ID data
        model->setData(model->index(row, 1), match.getTeamAName()); // Add Team 1 data
        model->setData(model->index(row, 2), match.getTeamBName()); // Add Team 2 data
        model->setData(model->index(row, 3), match.getMatchDateTime().date().toString());
        model->setData(model->index(row, 4), match.getMatchDateTime().time().toString());
        model->setData(model->index(row, 5), match.getCompetitionName()); // Add Competition data
    }

    // Set the model to the QTableView
    ui->allmatches->setModel(model);
    ui->allmatches->hideColumn(0); // Hide the ID column

    // Disable editing by setting no edit triggers
    ui->allmatches->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void MainWindow::on_Delete_clicked() {
    QModelIndexList selectedRows = ui->allmatches->selectionModel()->selectedRows();
    if (selectedRows.isEmpty()) {
        QMessageBox::warning(this, "Error", "No match selected!");
        return;
    }

    bool allDeleted = true;
    for (const QModelIndex &index : selectedRows) {
        int matchId = index.sibling(index.row(), 0).data().toInt(); // Get the ID from the hidden column
        qDebug() << "Deleting match with ID:" << matchId; // Add this line for debugging

        if (!Match::deleteMatch(matchId)) {
            allDeleted = false;
            qDebug() << "Failed to delete match with ID:" << matchId;
        }
    }

    if (allDeleted) {
        QMessageBox::information(this, "Success", "Selected matches deleted successfully!");
    } else {
        QMessageBox::critical(this, "Error", "Failed to delete some matches!");
    }

    setupMatchTable(); // Refresh the table
}

void MainWindow::on_Modify_clicked() {
    QModelIndexList selectedRows = ui->allmatches->selectionModel()->selectedRows();
    if (selectedRows.isEmpty()) {
        QMessageBox::warning(this, "Error", "No match selected!");
        return;
    }

    QModelIndex index = selectedRows.first();
    int matchId = index.sibling(index.row(), 0).data().toInt(); // Get the ID from the hidden column

    Match match;
    for (const Match &m : Match::readAllMatches()) {
        if (m.getId() == matchId) {
            match = m;
            break;
        }
    }

    // Create a dialog to edit the match details
    QDialog dialog(this);
    QFormLayout form(&dialog);

    form.addRow(new QLabel("Edit Match Details"));

    QComboBox *team1Box = new QComboBox(&dialog);
    QComboBox *team2Box = new QComboBox(&dialog);
    Match::loadTeamsIntoComboBoxes(team1Box, team2Box);
    team1Box->setCurrentText(match.getTeamAName());
    team2Box->setCurrentText(match.getTeamBName());
    form.addRow("Team 1:", team1Box);
    form.addRow("Team 2:", team2Box);

    QLineEdit *stadiumEdit = new QLineEdit(&dialog);
    stadiumEdit->setText(match.getStadium());
    form.addRow("Stadium:", stadiumEdit);

    QLineEdit *refereeEdit = new QLineEdit(&dialog);
    refereeEdit->setText(match.getReferee());
    form.addRow("Referee:", refereeEdit);

    QDateTimeEdit *dateTimeEdit = new QDateTimeEdit(&dialog);
    dateTimeEdit->setDateTime(match.getMatchDateTime());
    form.addRow("Date & Time:", dateTimeEdit);

    QSpinBox *scoreAEdit = new QSpinBox(&dialog);
    scoreAEdit->setValue(match.getScoreA());
    form.addRow("Score A:", scoreAEdit);

    QSpinBox *scoreBEdit = new QSpinBox(&dialog);
    scoreBEdit->setValue(match.getScoreB());
    form.addRow("Score B:", scoreBEdit);

    QComboBox *compBox = new QComboBox(&dialog);
    Match::loadCompetitionsIntoComboBox(compBox);
    compBox->setCurrentText(match.getCompetitionName());
    form.addRow("Competition:", compBox);

    QDialogButtonBox buttonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, Qt::Horizontal, &dialog);
    form.addRow(&buttonBox);
    QObject::connect(&buttonBox, &QDialogButtonBox::accepted, &dialog, &QDialog::accept);
    QObject::connect(&buttonBox, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);

    if (dialog.exec() == QDialog::Accepted) {
        // Validate inputs: teams must be different and stadium/referee cannot be empty
        if (team1Box->currentData().toInt() == team2Box->currentData().toInt()) {
            QMessageBox::warning(this, "Error", "Teams must be different!");
            return;
        }
        if (stadiumEdit->text().isEmpty() || refereeEdit->text().isEmpty()) {
            QMessageBox::warning(this, "Error", "Stadium and Referee name are required!");
            return;
        }

        // Validate that the selected date and time is not in the past
        if (dateTimeEdit->dateTime() < QDateTime::currentDateTime()) {
            QMessageBox::warning(this, "Error", "The selected date and time cannot be in the past!");
            return;
        }

        match.setTeamA(team1Box->currentData().toInt());
        match.setTeamB(team2Box->currentData().toInt());
        match.setStadium(stadiumEdit->text());
        match.setReferee(refereeEdit->text());
        match.setMatchDateTime(dateTimeEdit->dateTime());
        match.setScoreA(scoreAEdit->value());
        match.setScoreB(scoreBEdit->value());
        match.setCompetitionId(compBox->currentData().toInt());

        if (!match.modifyMatch()) {
            QMessageBox::critical(this, "Error", "Failed to update match!");
            return;
        }

        QMessageBox::information(this, "Success", "Match updated successfully!");
        setupMatchTable(); // Refresh the table
    }
}

void MainWindow::on_search_textChanged(const QString &text) {
    filterMatches(text);
}

void MainWindow::filterMatches(const QString &text) {
    QList<Match> matches = Match::searchMatches(text); // Use searchMatches to get filtered data

    // Create a QStandardItemModel to hold the filtered data
    QStandardItemModel *model = new QStandardItemModel(matches.size(), 6, this); // Change column count to 6
    model->setHeaderData(0, Qt::Horizontal, tr("ID")); // Add ID column
    model->setHeaderData(1, Qt::Horizontal, tr("Team 1")); // Add Team 1 column
    model->setHeaderData(2, Qt::Horizontal, tr("Team 2")); // Add Team 2 column
    model->setHeaderData(3, Qt::Horizontal, tr("Date"));
    model->setHeaderData(4, Qt::Horizontal, tr("Time"));
    model->setHeaderData(5, Qt::Horizontal, tr("Competition")); // Add Competition column

    // Populate the model with filtered data
    for (int row = 0; row < matches.size(); ++row) {
        const Match &match = matches.at(row);
        model->setData(model->index(row, 0), match.getId()); // Add ID data
        model->setData(model->index(row, 1), match.getTeamAName()); // Add Team 1 data
        model->setData(model->index(row, 2), match.getTeamBName()); // Add Team 2 data
        model->setData(model->index(row, 3), match.getMatchDateTime().date().toString());
        model->setData(model->index(row, 4), match.getMatchDateTime().time().toString());
        model->setData(model->index(row, 5), match.getCompetitionName()); // Add Competition data
    }

    // Set the model to the QTableView
    ui->allmatches->setModel(model);
    ui->allmatches->hideColumn(0); // Hide the ID column
}

void MainWindow::on_sort_clicked() {
    ascendingOrder = !ascendingOrder; // Toggle the sorting order
    sortMatches(); // Sort the matches
}

void MainWindow::sortMatches() {
    QList<Match> matches = Match::sortMatchesByDateTime(ascendingOrder); // Use sortMatchesByDateTime to get sorted data

    // Create a QStandardItemModel to hold the sorted data
    QStandardItemModel *model = new QStandardItemModel(matches.size(), 6, this); // Change column count to 6
    model->setHeaderData(0, Qt::Horizontal, tr("ID")); // Add ID column
    model->setHeaderData(1, Qt::Horizontal, tr("Team 1")); // Add Team 1 column
    model->setHeaderData(2, Qt::Horizontal, tr("Team 2")); // Add Team 2 column
    model->setHeaderData(3, Qt::Horizontal, tr("Date"));
    model->setHeaderData(4, Qt::Horizontal, tr("Time"));
    model->setHeaderData(5, Qt::Horizontal, tr("Competition")); // Add Competition column

    // Populate the model with sorted data
    for (int row = 0; row < matches.size(); ++row) {
        const Match &match = matches.at(row);
        model->setData(model->index(row, 0), match.getId()); // Add ID data
        model->setData(model->index(row, 1), match.getTeamAName()); // Add Team 1 data
        model->setData(model->index(row, 2), match.getTeamBName()); // Add Team 2 data
        model->setData(model->index(row, 3), match.getMatchDateTime().date().toString());
        model->setData(model->index(row, 4), match.getMatchDateTime().time().toString());
        model->setData(model->index(row, 5), match.getCompetitionName()); // Add Competition data
    }

    // Set the model to the QTableView
    ui->allmatches->setModel(model);
    ui->allmatches->hideColumn(0); // Hide the ID column
}
