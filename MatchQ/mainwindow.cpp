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
#include <QPdfWriter>
#include <QPainter>
#include <QFileDialog>
#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QValueAxis>
#include <QToolTip>
#include <QMenu>
#include <QSet>
#include <functional>
#include <QStackedLayout>
#include <QPropertyAnimation>
#include <QTimeLine>
#include <QParallelAnimationGroup>
#include "fieldwidget.h"
#include <QTimer>
#include <algorithm>
#include "watchmatchdialog.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , matchModel(new QSqlTableModel(this)) // Initialize matchModel
    , ascendingOrder(true) // Initialize ascendingOrder
{
    ui->setupUi(this);
    Match::updateMatchStatuses();

    // Set the minimum date and time to the current date and time to prevent past selections
    ui->Date->setMinimumDateTime(QDateTime::currentDateTime());

    // Attempt to connect to the database
    if (dbConnection.createconnect()) {
        qDebug() << "Database connected successfully in MainWindow";
        // Load teams and competitions into combo boxes
        Match::loadTeamsIntoComboBoxes(ui->team1, ui->team2);
        Match::loadCompetitionsIntoComboBox(ui->Comp);
        connect(ui->chartOptionComboBox, &QComboBox::currentTextChanged, 
            this, &MainWindow::chart);
            connect(ui->refresh, &QPushButton::clicked, this, &MainWindow::setupMatchTable);
        
        
        setupMatchTable();
        updateMatchSummary(); // Display the match summary when the app opens
        updateRefereeAnalysis(); // Display the referee analysis when the app opens
        chart();
        weatherImpactChart();
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

    // Apply the new stylesheet to Matches_sum
    ui->Matches_sum->setStyleSheet(
        "QTableView#Matches_sum {"
        "    background-color: #1E2633;" /* Match tab pane and form widget */
        "    border: 2px solid #2A3A4A;" /* Subtle blue-gray border */
        "    gridline-color: #3A4A5A;" /* Light grid lines */
        "    alternate-background-color: #252A38;" /* Alternating row color */
        "    color: #FFFFFF;" /* White text */
        "    selection-background-color: #00FF7F;" /* Green selection */
        "    selection-color: #1A2633;" /* Dark blue text on selection */
        "    border-radius: 5px;"
        "}"
        "QTableView#Matches_sum::item {"
        "    padding: 5px;"
        "    border: none;" /* Remove individual cell borders */
        "}"
        "QTableView#Matches_sum::item:focus {"
        "    outline: none;" /* Remove focus outline */
        "}"
        "QHeaderView::section {"
        "    background-color: #252A38;" /* Match alternating row color */
        "    color: #FFFFFF;" /* White text */
        "    border: 1px solid #2A3A4A;"
        "    padding: 4px;"
        "    font-weight: bold;"
        "    border-radius: 0;"
        "}"
        "QTableView#Matches_sum QTableCornerButton::section {"
        "    background-color: #252A38;"
        "    border: 1px solid #2A3A4A;"
        "}"
    );

    // Connect the search line edit to the search slot
    connect(ui->search, &QLineEdit::textChanged, this, &MainWindow::on_search_textChanged);

    // Connect the header click signal to the sorting slot
    connect(ui->allmatches->horizontalHeader(), &QHeaderView::sectionClicked, this, &MainWindow::on_headerClicked);

    // Connect the double-click signal to the slot
    connect(ui->allmatches, &QTableView::doubleClicked, this, &MainWindow::on_matchDoubleClicked);

    ui->allmatches->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->allmatches, &QTableView::customContextMenuRequested, this, &MainWindow::on_allmatchesContextMenuRequested);
    statusUpdateTimer = new QTimer(this);
connect(statusUpdateTimer, &QTimer::timeout, this, []() {
    Match::updateMatchStatuses();
});
statusUpdateTimer->start(3600000); // Check every hour (3600000 ms)
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
        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setWindowTitle("Error");
        msgBox.setText("Teams must be different!");
        msgBox.setStyleSheet("QMessageBox { background-color: #1E1E2F; color: #FFFFFF; font-family: 'Segoe UI'; border-radius: 10px; }"
                             "QLabel { color: #FFFFFF; font-size: 14px; }"
                             "QPushButton { background-color: #2D89EF; color: #FFFFFF; border-radius: 5px; padding: 8px; font-size: 12px; }"
                             "QPushButton:hover { background-color: #1C6DD0; }");
        msgBox.exec();
        return;
    }
    if (stadium.isEmpty() || referee.isEmpty()) {
        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setWindowTitle("Error");
        msgBox.setText("Stadium and Referee name are required!");
        msgBox.setStyleSheet("QMessageBox { background-color: #1E1E2F; color: #FFFFFF; font-family: 'Segoe UI'; border-radius: 10px; }"
                             "QLabel { color: #FFFFFF; font-size: 14px; }"
                             "QPushButton { background-color: #2D89EF; color: #FFFFFF; border-radius: 5px; padding: 8px; font-size: 12px; }"
                             "QPushButton:hover { background-color: #1C6DD0; }");
        msgBox.exec();
        return;
    }

    // Validate that the selected date and time is not in the past
    if (matchDate < QDateTime::currentDateTime()) {
        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setWindowTitle("Error");
        msgBox.setText("The selected date and time cannot be in the past!");
        msgBox.setStyleSheet("QMessageBox { background-color: #1E1E2F; color: #FFFFFF; font-family: 'Segoe UI'; border-radius: 10px; }"
                             "QLabel { color: #FFFFFF; font-size: 14px; }"
                             "QPushButton { background-color: #2D89EF; color: #FFFFFF; border-radius: 5px; padding: 8px; font-size: 12px; }"
                             "QPushButton:hover { background-color: #1C6DD0; }");
        msgBox.exec();
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
        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Information);
        msgBox.setWindowTitle("Success");
        msgBox.setText("Match added successfully!");
        msgBox.setStyleSheet("QMessageBox { background-color: #1E1E2F; color: #FFFFFF; font-family: 'Segoe UI'; border-radius: 10px; }"
                             "QLabel { color: #FFFFFF; font-size: 14px; }"
                             "QPushButton { background-color: #2D89EF; color: #FFFFFF; border-radius: 5px; padding: 8px; font-size: 12px; }"
                             "QPushButton:hover { background-color: #1C6DD0; }");
        msgBox.exec();

        // Clear/reset fields after success
        ui->Referee_name->clear();
        ui->Stadium->clear();
        ui->Date->setDateTime(QDateTime::currentDateTime());
        setupMatchTable(); // Refresh the table
        updateMatchSummary(); // Update the summary
        updateRefereeAnalysis();
        chart(); // Update the chart
        weatherImpactChart();
        Match::updateMatchStatuses();
    } else {
        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.setWindowTitle("Error");
        msgBox.setText("Failed to add match!");
        msgBox.setStyleSheet("QMessageBox { background-color: #1E1E2F; color: #FFFFFF; font-family: 'Segoe UI'; border-radius: 10px; }"
                             "QLabel { color: #FFFFFF; font-size: 14px; }"
                             "QPushButton { background-color: #2D89EF; color: #FFFFFF; border-radius: 5px; padding: 8px; font-size: 12px; }"
                             "QPushButton:hover { background-color: #1C6DD0; }");
        msgBox.exec();
    }
}

void MainWindow::setupMatchTable() {
    // Retrieve all matches from the database
    QList<Match> matches = Match::readAllMatches();

    // Create a QStandardItemModel to hold the match data
    QStandardItemModel *model = new QStandardItemModel(matches.size(), 7, this); // Add one more column
    model->setHorizontalHeaderLabels({"ID ▲▼", "Team 1 ▲▼", "Team 2 ▲▼", "Date ▲▼", "Time ▲▼", "Competition ▲▼", "Status ▲▼"}); // Add sorting indicators ▲▼ to the column headers

    // Populate the model with match data
    for (int row = 0; row < matches.size(); ++row) {
        const Match &match = matches.at(row);

        QString teamAName = match.getTeamAName().isEmpty() ? "Team 1" : match.getTeamAName(); // Handle null team A
        QString teamBName = match.getTeamBName().isEmpty() ? "Team 2" : match.getTeamBName(); // Handle null team B

        // Fetch team logos from the EQUIPE table
        QPixmap teamALogo, teamBLogo;
        QSqlQuery logoQuery;
        logoQuery.prepare("SELECT TEAM_LOGO FROM EQUIPE WHERE TEAM_NAME = :teamName");
        
        // Fetch Team A logo
        logoQuery.bindValue(":teamName", teamAName);
        if (logoQuery.exec() && logoQuery.next()) {
            QByteArray logoData = logoQuery.value("TEAM_LOGO").toByteArray();
            teamALogo.loadFromData(logoData);
        }

        // Fetch Team B logo
        logoQuery.bindValue(":teamName", teamBName);
        if (logoQuery.exec() && logoQuery.next()) {
            QByteArray logoData = logoQuery.value("TEAM_LOGO").toByteArray();
            teamBLogo.loadFromData(logoData);
        }

        // Create items with logos and names
        QStandardItem *teamAItem = new QStandardItem();
        if (!teamALogo.isNull()) {
            teamAItem->setData(QVariant(teamALogo.scaled(24, 24, Qt::KeepAspectRatio, Qt::SmoothTransformation)), Qt::DecorationRole);
        }
        teamAItem->setText(teamAName);

        QStandardItem *teamBItem = new QStandardItem();
        if (!teamBLogo.isNull()) {
            teamBItem->setData(QVariant(teamBLogo.scaled(24, 24, Qt::KeepAspectRatio, Qt::SmoothTransformation)), Qt::DecorationRole);
        }
        teamBItem->setText(teamBName);

        model->setItem(row, 0, new QStandardItem(QString::number(match.getId()))); // ID
        model->setItem(row, 1, teamAItem); // Team 1 with logo
        model->setItem(row, 2, teamBItem); // Team 2 with logo
        model->setItem(row, 3, new QStandardItem(match.getMatchDateTime().date().toString("yyyy-MM-dd"))); // Date
        model->setItem(row, 4, new QStandardItem(match.getMatchDateTime().time().toString("HH:mm:ss"))); // Time
        model->setItem(row, 5, new QStandardItem(match.getCompetitionName())); // Competition
        QString status = match.getStatus();
        if (status == "Scheduled") {
            status = "⏳ " + status;
        } else if (status == "Played") {
            status = "✅ " + status;
        } else if (status == "Playing") {
            status = "⚽ " + status;
        }
        model->setItem(row, 6, new QStandardItem(status)); // Status
    }

    // Set the model to the QTableView
    ui->allmatches->setModel(model);

    // Configure the table view
    ui->allmatches->hideColumn(0); // Hide the ID column
    ui->allmatches->setEditTriggers(QAbstractItemView::NoEditTriggers); // Disable editing
    ui->allmatches->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch); // Stretch columns for visibility
    ui->allmatches->setSelectionBehavior(QAbstractItemView::SelectRows); // Enable row selection
}
void MainWindow::on_Delete_clicked() {
    QModelIndexList selectedRows = ui->allmatches->selectionModel()->selectedRows();
    if (selectedRows.isEmpty()) {
        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setWindowTitle("⚠️ Error");
        msgBox.setText("No match selected!");
        msgBox.setStyleSheet("QMessageBox { background-color: #1E1E2F; color: #FFFFFF; font-family: 'Segoe UI'; border-radius: 10px; }"
                             "QLabel { color: #FFFFFF; font-size: 14px; }"
                             "QPushButton { background-color: #2D89EF; color: #FFFFFF; border-radius: 5px; padding: 8px; font-size: 12px; }"
                             "QPushButton:hover { background-color: #1C6DD0; }");
        msgBox.exec();
        return;
    }

    bool allDeleted = true;
    for (const QModelIndex &index : selectedRows) {
        int matchId = index.sibling(index.row(), 0).data().toInt();
        if (matchId <= 0 || !Match::deleteMatch(matchId)) {
            allDeleted = false;
        }
    }

    QMessageBox msgBox;
    msgBox.setIcon(allDeleted ? QMessageBox::Information : QMessageBox::Critical);
    msgBox.setWindowTitle(allDeleted ? "✅ Success" : "❌ Error");
    msgBox.setText(allDeleted ? "Selected matches deleted successfully!" : "Failed to delete some matches!");
    msgBox.setStyleSheet("QMessageBox { background-color: #1E1E2F; color: #FFFFFF; font-family: 'Segoe UI'; border-radius: 10px; }"
                         "QLabel { color: #FFFFFF; font-size: 14px; }"
                         "QPushButton { background-color: #2D89EF; color: #FFFFFF; border-radius: 5px; padding: 8px; font-size: 12px; }"
                         "QPushButton:hover { background-color: #1C6DD0; }");
    msgBox.exec();

    setupMatchTable(); // Refresh the table
    updateMatchSummary(); // Update the summary
    updateRefereeAnalysis();
    chart(); // Update the chart
    weatherImpactChart();
    Match::updateMatchStatuses();
}

void MainWindow::on_Modify_clicked() {
    QModelIndexList selectedRows = ui->allmatches->selectionModel()->selectedRows();
    if (selectedRows.isEmpty()) {
        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setWindowTitle("⚠️ Error");
        msgBox.setText("No match selected!");
        msgBox.setStyleSheet("QMessageBox { background-color: #1E1E2F; color: #FFFFFF; font-family: 'Segoe UI'; border-radius: 10px; }"
                             "QLabel { color: #FFFFFF; font-size: 14px; }"
                             "QPushButton { background-color: #2D89EF; color: #FFFFFF; border-radius: 5px; padding: 8px; font-size: 12px; }"
                             "QPushButton:hover { background-color: #1C6DD0; }");
        msgBox.exec();
        return;
    }

    QModelIndex index = selectedRows.first();
    int matchId = index.sibling(index.row(), 0).data().toInt();

    Match match;
    for (const Match &m : Match::readAllMatches()) {
        if (m.getId() == matchId) {
            match = m;
            break;
        }
    }

    QDialog dialog(this);
    dialog.setWindowTitle("Modify Match");
    dialog.setStyleSheet(
        "QDialog { background-color: #1E1E2F; color: #FFFFFF; font-family: 'Segoe UI'; font-size: 12px; border-radius: 10px; padding: 15px; }"
        "QLabel, QLineEdit, QComboBox, QDateTimeEdit, QSpinBox { color: #FFFFFF; font-size: 14px; }"
        "QComboBox QAbstractItemView { color: #FFFFFF; }"
        "QPushButton { background-color: #2D89EF; color: #FFFFFF; border-radius: 5px; padding: 8px; font-size: 12px; }"
        "QPushButton:hover { background-color: #1C6DD0; }"
        "QFormLayout { margin: 10px; }"
    );

    QVBoxLayout *mainLayout = new QVBoxLayout(&dialog);
    QLabel *titleLabel = new QLabel("Modify Match");
    titleLabel->setAlignment(Qt::AlignCenter);
    QFont titleFont("Segoe UI", 16, QFont::Bold);
    titleLabel->setFont(titleFont);
    mainLayout->addWidget(titleLabel);

    QFormLayout *formLayout = new QFormLayout();

    QComboBox *team1Box = new QComboBox(&dialog);
    QComboBox *team2Box = new QComboBox(&dialog);
    Match::loadTeamsIntoComboBoxes(team1Box, team2Box);
    team1Box->setCurrentText(match.getTeamAName());
    team2Box->setCurrentText(match.getTeamBName());
    formLayout->addRow("Team 1:", team1Box);
    formLayout->addRow("Team 2:", team2Box);

    QLineEdit *stadiumEdit = new QLineEdit(&dialog);
    stadiumEdit->setText(match.getStadium());
    formLayout->addRow("Stadium:", stadiumEdit);

    QLineEdit *refereeEdit = new QLineEdit(&dialog);
    refereeEdit->setText(match.getReferee());
    formLayout->addRow("Referee:", refereeEdit);

    QDateTimeEdit *dateTimeEdit = new QDateTimeEdit(&dialog);
    dateTimeEdit->setDateTime(match.getMatchDateTime());
    dateTimeEdit->setCalendarPopup(true);
    formLayout->addRow("Date & Time:", dateTimeEdit);

    QSpinBox *scoreAEdit = new QSpinBox(&dialog);
    scoreAEdit->setRange(0, 100);
    scoreAEdit->setValue(match.getScoreA());
    formLayout->addRow("Score A:", scoreAEdit);

    QSpinBox *scoreBEdit = new QSpinBox(&dialog);
    scoreBEdit->setRange(0, 100);
    scoreBEdit->setValue(match.getScoreB());
    formLayout->addRow("Score B:", scoreBEdit);

    QComboBox *compBox = new QComboBox(&dialog);
    Match::loadCompetitionsIntoComboBox(compBox);
    compBox->setCurrentText(match.getCompetitionName());
    formLayout->addRow("Competition:", compBox);

    QComboBox *statusBox = new QComboBox(&dialog);
    statusBox->addItem("Scheduled");
    statusBox->addItem("Playing");
    statusBox->addItem("Played");
    statusBox->setCurrentText(match.getStatus());
    formLayout->addRow("Status:", statusBox);

    QComboBox *weatherBox = new QComboBox(&dialog);
    weatherBox->addItem("Sunny", 0);
    weatherBox->addItem("Rainy", 1);
    int meteo = match.getMeteo();
    weatherBox->setCurrentIndex((meteo == 0 || meteo == 1) ? meteo : 0); // Default to Sunny if invalid
    formLayout->addRow("Weather:", weatherBox);

    mainLayout->addLayout(formLayout);

    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, &dialog);
    connect(buttonBox, &QDialogButtonBox::accepted, &dialog, &QDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);
    mainLayout->addWidget(buttonBox);

    if (dialog.exec() == QDialog::Accepted) {
        // Logical Input Control
        // 1. Check if teams are different
        if (team1Box->currentData().toInt() == team2Box->currentData().toInt()) {
            QMessageBox msgBox;
            msgBox.setIcon(QMessageBox::Warning);
            msgBox.setWindowTitle("Error");
            msgBox.setText("Teams must be different!");
            msgBox.setStyleSheet("QMessageBox { background-color: #1E1E2F; color: #FFFFFF; font-family: 'Segoe UI'; border-radius: 10px; }"
                                 "QLabel { color: #FFFFFF; font-size: 14px; }"
                                 "QPushButton { background-color: #2D89EF; color: #FFFFFF; border-radius: 5px; padding: 8px; font-size: 12px; }"
                                 "QPushButton:hover { background-color: #1C6DD0; }");
            msgBox.exec();
            return;
        }

        // 2. Check if stadium and referee are non-empty
        QString stadium = stadiumEdit->text().trimmed();
        QString referee = refereeEdit->text().trimmed();
        if (stadium.isEmpty() || referee.isEmpty()) {
            QMessageBox msgBox;
            msgBox.setIcon(QMessageBox::Warning);
            msgBox.setWindowTitle("Error");
            msgBox.setText("Stadium and Referee name are required!");
            msgBox.setStyleSheet("QMessageBox { background-color: #1E1E2F; color: #FFFFFF; font-family: 'Segoe UI'; border-radius: 10px; }"
                                 "QLabel { color: #FFFFFF; font-size: 14px; }"
                                 "QPushButton { background-color: #2D89EF; color: #FFFFFF; border-radius: 5px; padding: 8px; font-size: 12px; }"
                                 "QPushButton:hover { background-color: #1C6DD0; }");
            msgBox.exec();
            return;
        }

        // 3. Validate referee name (minimum length and basic format)
        if (referee.length() < 2 || !referee.contains(QRegularExpression("^[a-zA-Z\\s]+$"))) {
            QMessageBox msgBox;
            msgBox.setIcon(QMessageBox::Warning);
            msgBox.setWindowTitle("Error");
            msgBox.setText("Referee name must be at least 2 characters and contain only letters and spaces!");
            msgBox.setStyleSheet("QMessageBox { background-color: #1E1E2F; color: #FFFFFF; font-family: 'Segoe UI'; border-radius: 10px; }"
                                 "QLabel { color: #FFFFFF; font-size: 14px; }"
                                 "QPushButton { background-color: #2D89EF; color: #FFFFFF; border-radius: 5px; padding: 8px; font-size: 12px; }"
                                 "QPushButton:hover { background-color: #1C6DD0; }");
            msgBox.exec();
            return;
        }

        // 4. Validate date and time based on match status
        QString selectedStatus = statusBox->currentText();
        QDateTime selectedDateTime = dateTimeEdit->dateTime();
        QDateTime currentDateTime = QDateTime::currentDateTime();

        if (selectedStatus == "Scheduled" && selectedDateTime < currentDateTime) {
            QMessageBox msgBox;
            msgBox.setIcon(QMessageBox::Warning);
            msgBox.setWindowTitle("Error");
            msgBox.setText("The selected date and time must be in the future for a Scheduled match!");
            msgBox.setStyleSheet("QMessageBox { background-color: #1E1E2F; color: #FFFFFF; font-family: 'Segoe UI'; border-radius: 10px; }"
                                 "QLabel { color: #FFFFFF; font-size: 14px; }"
                                 "QPushButton { background-color: #2D89EF; color: #FFFFFF; border-radius: 5px; padding: 8px; font-size: 12px; }"
                                 "QPushButton:hover { background-color: #1C6DD0; }");
            msgBox.exec();
            return;
        }
        if (selectedStatus == "Played" && selectedDateTime > currentDateTime) {
            QMessageBox msgBox;
            msgBox.setIcon(QMessageBox::Warning);
            msgBox.setWindowTitle("Error");
            msgBox.setText("The selected date and time must be in the past for a Played match!");
            msgBox.setStyleSheet("QMessageBox { background-color: #1E1E2F; color: #FFFFFF; font-family: 'Segoe UI'; border-radius: 10px; }"
                                 "QLabel { color: #FFFFFF; font-size: 14px; }"
                                 "QPushButton { background-color: #2D89EF; color: #FFFFFF; border-radius: 5px; padding: 8px; font-size: 12px; }"
                                 "QPushButton:hover { background-color: #1C6DD0; }");
            msgBox.exec();
            return;
        }
        if (selectedStatus == "Playing") {
            QDateTime lowerBound = currentDateTime.addSecs(-30 * 60); // 30 minutes before
            QDateTime upperBound = currentDateTime.addSecs(30 * 60);  // 30 minutes after
            if (selectedDateTime < lowerBound || selectedDateTime > upperBound) {
                QMessageBox msgBox;
                msgBox.setIcon(QMessageBox::Warning);
                msgBox.setWindowTitle("Error");
                msgBox.setText("The selected date and time for a Playing match must be within 30 minutes of the current time!");
                msgBox.setStyleSheet("QMessageBox { background-color: #1E1E2F; color: #FFFFFF; font-family: 'Segoe UI'; border-radius: 10px; }"
                                     "QLabel { color: #FFFFFF; font-size: 14px; }"
                                     "QPushButton { background-color: #2D89EF; color: #FFFFFF; border-radius: 5px; padding: 8px; font-size: 12px; }"
                                     "QPushButton:hover { background-color: #1C6DD0; }");
                msgBox.exec();
                return;
            }
        }

        // 5. Validate weather selection
        if (weatherBox->currentIndex() == -1) {
            QMessageBox msgBox;
            msgBox.setIcon(QMessageBox::Warning);
            msgBox.setWindowTitle("Error");
            msgBox.setText("Weather condition must be selected!");
            msgBox.setStyleSheet("QMessageBox { background-color: #1E1E2F; color: #FFFFFF; font-family: 'Segoe UI'; border-radius: 10px; }"
                                 "QLabel { color: #FFFFFF; font-size: 14px; }"
                                 "QPushButton { background-color: #2D89EF; color: #FFFFFF; border-radius: 5px; padding: 8px; font-size: 12px; }"
                                 "QPushButton:hover { background-color: #1C6DD0; }");
            msgBox.exec();
            return;
        }

        // 6. Validate match date is within competition dates
        int compId = compBox->currentData().toInt();
        QSqlQuery compQuery;
        compQuery.prepare("SELECT START_DATE, END_DATE FROM COMPETITION WHERE ID_COMPETITION = :compId");
        compQuery.bindValue(":compId", compId);
        if (!compQuery.exec()) {
            QMessageBox msgBox;
            msgBox.setIcon(QMessageBox::Critical);
            msgBox.setWindowTitle("Error");
            msgBox.setText("Failed to validate competition dates: " + compQuery.lastError().text());
            msgBox.setStyleSheet("QMessageBox { background-color: #1E1E2F; color: #FFFFFF; font-family: 'Segoe UI'; border-radius: 10px; }"
                                 "QLabel { color: #FFFFFF; font-size: 14px; }"
                                 "QPushButton { background-color: #2D89EF; color: #FFFFFF; border-radius: 5px; padding: 8px; font-size: 12px; }"
                                 "QPushButton:hover { background-color: #1C6DD0; }");
            msgBox.exec();
            return;
        }
        if (compQuery.next()) {
            QDateTime compStartDate = compQuery.value("START_DATE").toDateTime();
            QDateTime compEndDate = compQuery.value("END_DATE").toDateTime();
            if (selectedDateTime < compStartDate || selectedDateTime > compEndDate) {
                QMessageBox msgBox;
                msgBox.setIcon(QMessageBox::Warning);
                msgBox.setWindowTitle("Error");
                msgBox.setText("Match date and time must be within the competition's start and end dates!");
                msgBox.setStyleSheet("QMessageBox { background-color: #1E1E2F; color: #FFFFFF; font-family: 'Segoe UI'; border-radius: 10px; }"
                                     "QLabel { color: #FFFFFF; font-size: 14px; }"
                                     "QPushButton { background-color: #2D89EF; color: #FFFFFF; border-radius: 5px; padding: 8px; font-size: 12px; }"
                                     "QPushButton:hover { background-color: #1C6DD0; }");
                msgBox.exec();
                return;
            }
        } else {
            QMessageBox msgBox;
            msgBox.setIcon(QMessageBox::Critical);
            msgBox.setWindowTitle("Error");
            msgBox.setText("Competition not found!");
            msgBox.setStyleSheet("QMessageBox { background-color: #1E1E2F; color: #FFFFFF; font-family: 'Segoe UI'; border-radius: 10px; }"
                                 "QLabel { color: #FFFFFF; font-size: 14px; }"
                                 "QPushButton { background-color: #2D89EF; color: #FFFFFF; border-radius: 5px; padding: 8px; font-size: 12px; }"
                                 "QPushButton:hover { background-color: #1C6DD0; }");
            msgBox.exec();
            return;
        }

        // All validations passed, proceed with updating the match
        match.setTeamA(team1Box->currentData().toInt());
        match.setTeamB(team2Box->currentData().toInt());
        match.setStadium(stadium);
        match.setReferee(referee);
        match.setMatchDateTime(selectedDateTime);
        match.setScoreA(scoreAEdit->value());
        match.setScoreB(scoreBEdit->value());
        match.setCompetitionId(compBox->currentData().toInt());
        match.setStatus(selectedStatus);
        match.setMeteo(weatherBox->currentData().toInt());

        if (!match.modifyMatch()) {
            QMessageBox msgBox;
            msgBox.setIcon(QMessageBox::Critical);
            msgBox.setWindowTitle("Error");
            msgBox.setText("Failed to update match!");
            msgBox.setStyleSheet("QMessageBox { background-color: #1E1E2F; color: #FFFFFF; font-family: 'Segoe UI'; border-radius: 10px; }"
                                 "QLabel { color: #FFFFFF; font-size: 14px; }"
                                 "QPushButton { background-color: #2D89EF; color: #FFFFFF; border-radius: 5px; padding: 8px; font-size: 12px; }"
                                 "QPushButton:hover { background-color: #1C6DD0; }");
            msgBox.exec();
            return;
        }

        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Information);
        msgBox.setWindowTitle("Success");
        msgBox.setText("Match updated successfully!");
        msgBox.setStyleSheet("QMessageBox { background-color: #1E1E2F; color: #FFFFFF; font-family: 'Segoe UI'; border-radius: 10px; }"
                             "QLabel { color: #FFFFFF; font-size: 14px; }"
                             "QPushButton { background-color: #2D89EF; color: #FFFFFF; border-radius: 5px; padding: 8px; font-size: 12px; }"
                             "QPushButton:hover { background-color: #1C6DD0; }");
        msgBox.exec();
        setupMatchTable();
        updateMatchSummary();
        updateRefereeAnalysis();
        chart();
        weatherImpactChart();
        Match::updateMatchStatuses();
    }
}

void MainWindow::on_search_textChanged(const QString &text) {
    filterMatches(text);
}

void MainWindow::filterMatches(const QString &text) {
    if (text.isEmpty()) {
        setupMatchTable(); // Reload all matches if the search bar is cleared
        return;
    }

    QList<Match> matches = Match::searchMatches(text); // Retrieve filtered matches

    // Create a QStandardItemModel to hold the filtered data
    QStandardItemModel *model = new QStandardItemModel(matches.size(), 6, this);
    model->setHorizontalHeaderLabels({"ID ▲▼", "Team 1 ▲▼", "Team 2 ▲▼", "Date ▲▼", "Time ▲▼", "Competition ▲▼", "Status ▲▼"}); // Set headers

    for (int row = 0; row < matches.size(); ++row) {
        const Match &match = matches.at(row);

        QString teamAName = match.getTeamAName().isEmpty() ? "Team 1" : match.getTeamAName(); // Handle null team A
        QString teamBName = match.getTeamBName().isEmpty() ? "Team 2" : match.getTeamBName(); // Handle null team B

        // Fetch team logos from the EQUIPE table
        QPixmap teamALogo, teamBLogo;
        QSqlQuery logoQuery;
        logoQuery.prepare("SELECT TEAM_LOGO FROM EQUIPE WHERE TEAM_NAME = :teamName");
        
        // Fetch Team A logo
        logoQuery.bindValue(":teamName", teamAName);
        if (logoQuery.exec() && logoQuery.next()) {
            QByteArray logoData = logoQuery.value("TEAM_LOGO").toByteArray();
            teamALogo.loadFromData(logoData);
        }

        // Fetch Team B logo
        logoQuery.bindValue(":teamName", teamBName);
        if (logoQuery.exec() && logoQuery.next()) {
            QByteArray logoData = logoQuery.value("TEAM_LOGO").toByteArray();
            teamBLogo.loadFromData(logoData);
        }

        // Create items with logos and names
        QStandardItem *teamAItem = new QStandardItem();
        if (!teamALogo.isNull()) {
            teamAItem->setData(QVariant(teamALogo.scaled(24, 24, Qt::KeepAspectRatio, Qt::SmoothTransformation)), Qt::DecorationRole);
        }
        teamAItem->setText(teamAName);

        QStandardItem *teamBItem = new QStandardItem();
        if (!teamBLogo.isNull()) {
            teamBItem->setData(QVariant(teamBLogo.scaled(24, 24, Qt::KeepAspectRatio, Qt::SmoothTransformation)), Qt::DecorationRole);
        }
        teamBItem->setText(teamBName);

        model->setItem(row, 0, new QStandardItem(QString::number(match.getId()))); // ID
        model->setItem(row, 1, teamAItem); // Team 1 with logo
        model->setItem(row, 2, teamBItem); // Team 2 with logo
        model->setItem(row, 3, new QStandardItem(match.getMatchDateTime().date().toString("yyyy-MM-dd"))); // Date
        model->setItem(row, 4, new QStandardItem(match.getMatchDateTime().time().toString("HH:mm:ss"))); // Time
        model->setItem(row, 5, new QStandardItem(match.getCompetitionName())); // Competition
        QString status = match.getStatus();
        if (status == "Scheduled") {
            status = "⏳ " + status;
        } else if (status == "Played") {
            status = "✅ " + status;
        } else if (status == "Playing") {
            status = "⚽ " + status;
        }
        model->setItem(row, 6, new QStandardItem(status)); // Status
    }

    ui->allmatches->setModel(model); // Set the filtered model temporarily
    updateMatchSummary();
    chart();
    weatherImpactChart();
    Match::updateMatchStatuses();
    updateRefereeAnalysis();
}

void MainWindow::sortMatches() {
    QList<Match> matches = Match::sortMatches(ascendingOrder); // Use sortMatches to get sorted data

    // Create a QStandardItemModel to hold the sorted data
    QStandardItemModel *model = new QStandardItemModel(matches.size(), 6, this);
    model->setHorizontalHeaderLabels({"ID", "Team 1", "Team 2", "Date", "Time", "Competition"}); // Explicitly set headers

    // Populate the model with sorted data
    for (int row = 0; row < matches.size(); ++row) {
        const Match &match = matches.at(row);
        model->setItem(row, 0, new QStandardItem(QString::number(match.getId()))); // ID
        model->setItem(row, 1, new QStandardItem(match.getTeamAName())); // Team 1
        model->setItem(row, 2, new QStandardItem(match.getTeamBName())); // Team 2
        model->setItem(row, 3, new QStandardItem(match.getMatchDateTime().date().toString("yyyy-MM-dd"))); // Date
        model->setItem(row, 4, new QStandardItem(match.getMatchDateTime().time().toString("HH:mm:ss"))); // Time
        model->setItem(row, 5, new QStandardItem(match.getCompetitionName())); // Competition
    }

    // Set the model to the QTableView
    ui->allmatches->setModel(model);
    ui->allmatches->hideColumn(0); // Hide the ID column
    ui->allmatches->setEditTriggers(QAbstractItemView::NoEditTriggers); // Disable editing
}

void MainWindow::on_headerClicked(int logicalIndex) {
    QList<Match> matches = Match::readAllMatches(); // Get all matches

    // Sort based on the clicked column
    std::sort(matches.begin(), matches.end(), [logicalIndex, this](const Match &a, const Match &b) {
        switch (logicalIndex) {
            case 1: // Team 1 column
                return ascendingOrder ? a.getTeamAName() < b.getTeamAName() : a.getTeamAName() > b.getTeamAName();
            case 2: // Team 2 column
                return ascendingOrder ? a.getTeamBName() < b.getTeamBName() : a.getTeamBName() > b.getTeamBName();
            case 3: // Date column
                return ascendingOrder ? a.getMatchDateTime().date() < b.getMatchDateTime().date() : a.getMatchDateTime().date() > b.getMatchDateTime().date();
            case 4: // Time column
                return ascendingOrder ? a.getMatchDateTime().time() < b.getMatchDateTime().time() : a.getMatchDateTime().time() > b.getMatchDateTime().time();
            case 5: // Competition column
                return ascendingOrder ? a.getCompetitionName() < b.getCompetitionName() : a.getCompetitionName() > b.getCompetitionName();
            case 6: // Status column
                return ascendingOrder ? a.getStatus() < b.getStatus() : a.getStatus() > b.getStatus();
            default:
                return false; // No sorting for invalid columns
        }
    });

    ascendingOrder = !ascendingOrder; // Toggle sorting order

    // Create a QStandardItemModel to hold the sorted data
    QStandardItemModel *model = new QStandardItemModel(matches.size(), 7, this); // Update column count
    model->setHorizontalHeaderLabels({"ID ▲▼", "Team 1 ▲▼", "Team 2 ▲▼", "Date ▲▼", "Time ▲▼", "Competition ▲▼", "Status ▲▼"}); // Add "Status" column

    // Populate the model with sorted data
    for (int row = 0; row < matches.size(); ++row) {
        const Match &match = matches.at(row);

        QString teamAName = match.getTeamAName().isEmpty() ? "Team 1" : match.getTeamAName(); // Handle null team A
        QString teamBName = match.getTeamBName().isEmpty() ? "Team 2" : match.getTeamBName(); // Handle null team B

        // Fetch team logos from the EQUIPE table
        QPixmap teamALogo, teamBLogo;
        QSqlQuery logoQuery;
        logoQuery.prepare("SELECT TEAM_LOGO FROM EQUIPE WHERE TEAM_NAME = :teamName");
        
        // Fetch Team A logo
        logoQuery.bindValue(":teamName", teamAName);
        if (logoQuery.exec() && logoQuery.next()) {
            QByteArray logoData = logoQuery.value("TEAM_LOGO").toByteArray();
            teamALogo.loadFromData(logoData);
        }

        // Fetch Team B logo
        logoQuery.bindValue(":teamName", teamBName);
        if (logoQuery.exec() && logoQuery.next()) {
            QByteArray logoData = logoQuery.value("TEAM_LOGO").toByteArray();
            teamBLogo.loadFromData(logoData);
        }

        // Create items with logos and names
        QStandardItem *teamAItem = new QStandardItem();
        if (!teamALogo.isNull()) {
            teamAItem->setData(QVariant(teamALogo.scaled(24, 24, Qt::KeepAspectRatio, Qt::SmoothTransformation)), Qt::DecorationRole);
        }
        teamAItem->setText(teamAName);

        QStandardItem *teamBItem = new QStandardItem();
        if (!teamBLogo.isNull()) {
            teamBItem->setData(QVariant(teamBLogo.scaled(24, 24, Qt::KeepAspectRatio, Qt::SmoothTransformation)), Qt::DecorationRole);
        }
        teamBItem->setText(teamBName);

        model->setItem(row, 0, new QStandardItem(QString::number(match.getId()))); // ID
        model->setItem(row, 1, teamAItem); // Team 1 with logo
        model->setItem(row, 2, teamBItem); // Team 2 with logo
        model->setItem(row, 3, new QStandardItem(match.getMatchDateTime().date().toString("yyyy-MM-dd"))); // Date
        model->setItem(row, 4, new QStandardItem(match.getMatchDateTime().time().toString("HH:mm:ss"))); // Time
        model->setItem(row, 5, new QStandardItem(match.getCompetitionName())); // Competition
        QString status = match.getStatus();
        if (status == "Scheduled") {
            status = "⏳ " + status;
        } else if (status == "Played") {
            status = "✅ " + status;
        } else if (status == "Playing") {
            status = "⚽ " + status;
        }
        model->setItem(row, 6, new QStandardItem(status)); // Status
    }

    // Set the model to the QTableView
    ui->allmatches->setModel(model);
    ui->allmatches->hideColumn(0); // Hide the ID column
    ui->allmatches->setEditTriggers(QAbstractItemView::NoEditTriggers); // Disable editing
    ui->allmatches->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch); // Stretch columns for visibility
}

void MainWindow::on_pdf_clicked() {
    QString filePath = QFileDialog::getSaveFileName(this, "Save PDF", "", "*.pdf");
    if (filePath.isEmpty()) {
        return; // If no file is selected, return
    }

    if (!filePath.endsWith(".pdf", Qt::CaseInsensitive)) {
        filePath += ".pdf"; // Ensure the file has a .pdf extension
    }

    Match::generatePDF(filePath); // Call the static method from Match class

    QMessageBox msgBox;
    msgBox.setIcon(QMessageBox::Information);
    msgBox.setWindowTitle("Success");
    msgBox.setText("PDF generated successfully!");
    msgBox.setStyleSheet("QMessageBox { background-color: #1E1E2F; color: #FFFFFF; font-family: 'Segoe UI'; border-radius: 10px; }"
                         "QLabel { color: #FFFFFF; font-size: 14px; }"
                         "QPushButton { background-color: #2D89EF; color: #FFFFFF; border-radius: 5px; padding: 8px; font-size: 12px; }"
                         "QPushButton:hover { background-color: #1C6DD0; }");
    msgBox.exec();
}

void MainWindow::on_auto_match_clicked() {
    // Create a dialog to select a competition
    QDialog dialog(this);
    dialog.setWindowTitle("Select Competition");
    dialog.setStyleSheet("QDialog { background-color: #1E1E2F; color: #FFFFFF; font-family: 'Segoe UI'; font-size: 12px; border-radius: 10px; padding: 15px; }"
                         "QLabel, QComboBox, QPushButton { color: #FFFFFF; }"
                         "QPushButton { background-color: #2D89EF; color: #FFFFFF; border-radius: 5px; padding: 8px; font-size: 12px; }"
                         "QPushButton:hover { background-color: #1C6DD0; }"
                         "QComboBox QAbstractItemView { color: #FFFFFF; background-color: #2A2A3A; }");

    QFormLayout form(&dialog);

    QComboBox *competitionBox = new QComboBox(&dialog);
    QSqlQuery query("SELECT ID_COMPETITION, COMP_NAME FROM COMPETITION ORDER BY COMP_NAME");
    while (query.next()) {
        competitionBox->addItem(query.value("COMP_NAME").toString(), query.value("ID_COMPETITION").toInt());
    }
    form.addRow("Competition:", competitionBox);

    QDialogButtonBox buttonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, Qt::Horizontal, &dialog);
    form.addRow(&buttonBox);
    connect(&buttonBox, &QDialogButtonBox::accepted, &dialog, &QDialog::accept);
    connect(&buttonBox, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);

    if (dialog.exec() == QDialog::Accepted) {
        int competitionId = competitionBox->currentData().toInt();
        QSqlQuery compQuery;
        compQuery.prepare("SELECT COMP_TYPE, START_DATE, END_DATE, NB_TEAMS FROM COMPETITION WHERE ID_COMPETITION = :id");
        compQuery.bindValue(":id", competitionId);
        if (compQuery.exec() && compQuery.next()) {
            QString competitionType = compQuery.value("COMP_TYPE").toString();
            QDate startDate = compQuery.value("START_DATE").toDate();
            QDate endDate = compQuery.value("END_DATE").toDate();
            int nbTeams = compQuery.value("NB_TEAMS").toInt();

            if (Match::generateMatchDates(competitionId, competitionType, startDate, endDate, nbTeams)) {
            QMessageBox msgBox;
            msgBox.setIcon(QMessageBox::Information);
            msgBox.setWindowTitle("✅ Success");
            msgBox.setText("Match dates generated successfully!");
            msgBox.setStyleSheet(
                "QMessageBox { background-color: #1E1E2F; color: #FFFFFF; font-family: 'Segoe UI'; border-radius: 10px; }"
                "QLabel { color: #FFFFFF; font-size: 14px; }"
                "QPushButton { background-color: #4CAF50; color: #FFFFFF; border-radius: 5px; padding: 8px; font-size: 12px; }"
                "QPushButton:hover { background-color: #45A049; }"
            );
            msgBox.exec();
            } else {
            QMessageBox msgBox;
            msgBox.setIcon(QMessageBox::Critical);
            msgBox.setWindowTitle("❌ Error");
            msgBox.setText("Failed to generate match dates!");
            msgBox.setStyleSheet(
                "QMessageBox { background-color: #1E1E2F; color: #FFFFFF; font-family: 'Segoe UI'; border-radius: 10px; }"
                "QLabel { color: #FFFFFF; font-size: 14px; }"
                "QPushButton { background-color: #E94E77; color: #FFFFFF; border-radius: 5px; padding: 8px; font-size: 12px; }"
                "QPushButton:hover { background-color: #C94063; }"
            );
            msgBox.exec();
            }
        } else {
            QMessageBox msgBox;
            msgBox.setIcon(QMessageBox::Critical);
            msgBox.setWindowTitle("❌ Error");
            msgBox.setText("Failed to retrieve competition details!");
            msgBox.setStyleSheet(
            "QMessageBox { background-color: #1E1E2F; color: #FFFFFF; font-family: 'Segoe UI'; border-radius: 10px; }"
            "QLabel { color: #FFFFFF; font-size: 14px; }"
            "QPushButton { background-color: #E94E77; color: #FFFFFF; border-radius: 5px; padding: 8px; font-size: 12px; }"
            "QPushButton:hover { background-color: #C94063; }"
            );
            msgBox.exec();
        }
    }
    setupMatchTable(); // Refresh the table after generating matches
    updateMatchSummary(); // Update the summary
    updateRefereeAnalysis(); // Update the referee analysis
    weatherImpactChart();
    Match::updateMatchStatuses();
}

void MainWindow::on_matchDoubleClicked(const QModelIndex &index) {
    if (!index.isValid()) {
        return;
    }

    int matchId = index.sibling(index.row(), 0).data().toInt(); // Get the match ID from the first column

    // Retrieve the match details
    Match match;
    for (const Match &m : Match::readAllMatches()) {
        if (m.getId() == matchId) {
            match = m;
            break;
        }
    }

    // Interpret the meteo value
    QString meteoDescription = (match.getMeteo() == 0) ? "Sunny" : "Rainy";

    // Create a dialog for displaying match details
    QDialog dialog(this);
    dialog.setWindowTitle("Match Details");
    dialog.setStyleSheet(
        "QDialog { background-color: #1E1E2F; color: #FFFFFF; font-family: 'Segoe UI'; font-size: 12px; border-radius: 10px; padding: 15px; }"
        "QLabel { color: #FFFFFF; font-size: 14px; }"
        "QFrame { background-color: #252A38; border: 1px solid #3A4A5A; border-radius: 5px; padding: 10px; }"
        "QPushButton { background-color: #2D89EF; color: #FFFFFF; border-radius: 5px; padding: 8px; font-size: 12px; }"
        "QPushButton:hover { background-color: #1C6DD0; }"
    );

    QVBoxLayout *mainLayout = new QVBoxLayout(&dialog);

    // Add a title
    QLabel *titleLabel = new QLabel("Match Details");
    titleLabel->setAlignment(Qt::AlignCenter);
    QFont titleFont("Segoe UI", 16, QFont::Bold);
    titleLabel->setFont(titleFont);
    mainLayout->addWidget(titleLabel);

    // Add a frame for match details
    QFrame *detailsFrame = new QFrame(&dialog);
    QGridLayout *detailsLayout = new QGridLayout(detailsFrame);

    // Add match details
    detailsLayout->addWidget(new QLabel("Match ID:"), 0, 0);
    detailsLayout->addWidget(new QLabel(QString::number(match.getId())), 0, 1);

    detailsLayout->addWidget(new QLabel("Competition:"), 1, 0);
    detailsLayout->addWidget(new QLabel(match.getCompetitionName()), 1, 1);

    detailsLayout->addWidget(new QLabel("Team 1:"), 2, 0);
    detailsLayout->addWidget(new QLabel(match.getTeamAName()), 2, 1);

    detailsLayout->addWidget(new QLabel("Team 2:"), 3, 0);
    detailsLayout->addWidget(new QLabel(match.getTeamBName()), 3, 1);

    detailsLayout->addWidget(new QLabel("Date & Time:"), 4, 0);
    detailsLayout->addWidget(new QLabel(match.getMatchDateTime().toString("yyyy-MM-dd HH:mm:ss")), 4, 1);

    detailsLayout->addWidget(new QLabel("Stadium:"), 5, 0);
    detailsLayout->addWidget(new QLabel(match.getStadium()), 5, 1);

    detailsLayout->addWidget(new QLabel("Referee:"), 6, 0);
    detailsLayout->addWidget(new QLabel(match.getReferee()), 6, 1);

    detailsLayout->addWidget(new QLabel("Score A:"), 7, 0);
    detailsLayout->addWidget(new QLabel(QString::number(match.getScoreA())), 7, 1);

    detailsLayout->addWidget(new QLabel("Score B:"), 8, 0);
    detailsLayout->addWidget(new QLabel(QString::number(match.getScoreB())), 8, 1);

    detailsLayout->addWidget(new QLabel("Status:"), 9, 0);
    detailsLayout->addWidget(new QLabel(match.getStatus()), 9, 1);

    detailsLayout->addWidget(new QLabel("Weather:"), 10, 0);
    detailsLayout->addWidget(new QLabel(meteoDescription), 10, 1);

    detailsFrame->setLayout(detailsLayout);
    mainLayout->addWidget(detailsFrame);

    // Add a close button
    QPushButton *closeButton = new QPushButton("Close");
    connect(closeButton, &QPushButton::clicked, &dialog, &QDialog::accept);
    mainLayout->addWidget(closeButton, 0, Qt::AlignCenter);

    dialog.exec();
}
void MainWindow::updateMatchSummary() {
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

void MainWindow::updateRefereeAnalysis() {
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
void MainWindow::chart()
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
    ChartWheelZoomHandler* wheelHandler = new ChartWheelZoomHandler(chartView);
    chartView->viewport()->installEventFilter(wheelHandler);

    QVBoxLayout *layout = new QVBoxLayout(ui->goals_chart);
    layout->addWidget(chartView);
    layout->addWidget(zoomButtonsWidget);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(5);
    ui->goals_chart->setLayout(layout);
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
void MainWindow::weatherImpactChart()
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

void MainWindow::on_allmatchesContextMenuRequested(const QPoint &pos) {
    QModelIndex index = ui->allmatches->indexAt(pos);
    if (!index.isValid()) {
        return;
    }

    // Get match ID and status
    int matchId = index.sibling(index.row(), 0).data().toInt(); // ID in hidden column 0
    QString status = index.sibling(index.row(), 6).data().toString(); // Status in column 6
    status = status.remove(QRegularExpression("^[⏳✅⚽]\\s*")); // Remove status icons

    QMenu contextMenu(this);
    contextMenu.setStyleSheet(
        "QMenu {"
        "    background-color: #2A2A3A;"
        "    color: #FFFFFF;"
        "    border: 1px solid #4A4A5A;"
        "    padding: 5px;"
        "    font-family: 'Segoe UI';"
        "    font-size: 12px;"
        "}"
        "QMenu::item {"
        "    background-color: transparent;"
        "    color: #FFFFFF;"
        "    padding: 8px 20px;"
        "}"
        "QMenu::item:selected {"
        "    background-color: #4A90E2;"
        "    color: #FFFFFF;"
        "}"
    );

    QAction *modifyAction = contextMenu.addAction("Modify Match");
    QAction *setLineupAction = contextMenu.addAction("Set Lineup");
    QAction *showFullLineupAction = contextMenu.addAction("Show Full Lineup");
    QAction *watchAction = contextMenu.addAction("Watch Match");
    watchAction->setEnabled(status == "Playing"); // Enable only for "Playing" status

    connect(modifyAction, &QAction::triggered, this, &MainWindow::on_Modify_clicked);
    connect(setLineupAction, &QAction::triggered, this, &MainWindow::on_setLineupTriggered);
    connect(showFullLineupAction, &QAction::triggered, this, &MainWindow::on_showFullLineupTriggered);
    connect(watchAction, &QAction::triggered, this, [this, matchId]() {
        WatchMatchDialog *dialog = new WatchMatchDialog(matchId, this);
        dialog->exec();
    });

    contextMenu.exec(ui->allmatches->viewport()->mapToGlobal(pos));
}
void MainWindow::on_setLineupTriggered() {
    QModelIndexList selectedRows = ui->allmatches->selectionModel()->selectedRows();
    if (selectedRows.isEmpty()) {
        QMessageBox::warning(this, "Error", "No match selected!");
        return;
    }

    int matchId = selectedRows.first().sibling(selectedRows.first().row(), 0).data().toInt();
    Match match;
    for (const Match &m : Match::readAllMatches()) {
        if (m.getId() == matchId) {
            match = m;
            break;
        }
    }

    // Check if the match is already played or is currently playing
    if (match.getStatus() == "Played" || match.getStatus() == "Playing") {
        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setWindowTitle("⚠️ Error");
        msgBox.setText("You cannot set a lineup for a match that has already been played or is currently playing!");
        msgBox.setStyleSheet(
            "QMessageBox { background-color: #2A2A3A; color: #FFFFFF; font-family: 'Segoe UI'; border-radius: 10px; }"
            "QLabel { color: #FFFFFF; font-size: 14px; }"
            "QPushButton { background-color: #E94E77; color: #FFFFFF; border-radius: 5px; padding: 8px; font-size: 12px; }"
            "QPushButton:hover { background-color: #C94063; }"
        );
        msgBox.exec();
        return;
    }

    // Remove old widgets
    ui->line_up_widget->hide();
    // Remove old combo boxes
    for (const auto& [box, _] : positionBoxes) {
        if (box) {
            box->deleteLater();
        }
    }
    positionBoxes.clear();
    
    // Remove old Save Lineup and Cancel buttons if they exist
    QList<QPushButton*> buttons = ui->line_up_widget->findChildren<QPushButton*>();
    for (QPushButton* button : buttons) {
        if (button->text() == "Save Lineup" || button->text() == "Cancel") {
            button->deleteLater();
        }
    }

    // Dialog for team and lineup selection with enhanced stylesheet
    QDialog dialog(this);
    dialog.setWindowTitle("Set Team Lineup");
    dialog.setStyleSheet(
        "QDialog {"
        "  background-color: #2A2A3A;"
        "  color: #FFFFFF;"
        "  font-family: 'Segoe UI';"
        "  font-size: 14px;"
        "  border: 1px solid #4A4A5A;"
        "  border-radius: 8px;"
        "  padding: 20px;"
        "}"
        "QLabel {"
        "  color: #D0D0D0;"
        "  font-weight: bold;"
        "}"
        "QComboBox {"
        "  background-color: #3A3A4A;"
        "  color: #FFFFFF;"
        "  border: 1px solid #5A5A6A;"
        "  border-radius: 4px;"
        "  padding: 5px;"
        "  font-size: 13px;"
        "}"
        "QComboBox:hover {"
        "  border: 1px solid #7A7A8A;"
        "}"
        "QComboBox::drop-down {"
        "  border-left: 1px solid #5A5A6A;"
        "  width: 20px;"
        "}"
        "QComboBox QAbstractItemView {"
        "  background-color: #3A3A4A;"
        "  color: #FFFFFF;"
        "  selection-background-color: #5A5A6A;"
        "  border: 1px solid #5A5A6A;"
        "}"
        "QPushButton {"
        "  background-color: #4A90E2;"
        "  color: #FFFFFF;"
        "  border: none;"
        "  border-radius: 4px;"
        "  padding: 8px 16px;"
        "  font-size: 13px;"
        "  font-weight: bold;"
        "}"
        "QPushButton:hover {"
        "  background-color: #357ABD;"
        "}"
        "QPushButton:pressed {"
        "  background-color: #2A6099;"
        "}"
        "QPushButton#cancelButton {"
        "  background-color: #E94E77;"
        "}"
        "QPushButton#cancelButton:hover {"
        "  background-color: #C94063;"
        "}"
        "QPushButton#cancelButton:pressed {"
        "  background-color: #A83352;"
        "}"
    );

    QVBoxLayout *mainLayout = new QVBoxLayout(&dialog);
    QFormLayout *formLayout = new QFormLayout();

    // Team selection
    QComboBox *teamBox = new QComboBox(&dialog);
    teamBox->addItem(match.getTeamAName(), match.getTeamA());
    teamBox->addItem(match.getTeamBName(), match.getTeamB());
    formLayout->addRow("Select Team:", teamBox);

    // Lineup selection
    QComboBox *lineupBox = new QComboBox(&dialog);
    lineupBox->addItem("4-3-3");
    lineupBox->addItem("4-4-2");
    lineupBox->setCurrentText(ui->Line_up->currentText());
    formLayout->addRow("Lineup:", lineupBox);

    mainLayout->addLayout(formLayout);

    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, &dialog);
    buttonBox->button(QDialogButtonBox::Cancel)->setObjectName("cancelButton");
    connect(buttonBox, &QDialogButtonBox::accepted, &dialog, [&]() {
        int selectedTeamId = teamBox->currentData().toInt();
        QString selectedLineup = lineupBox->currentText();
        setupLineupWidget(matchId, selectedTeamId, selectedLineup);
        ui->tabWidget->setCurrentWidget(ui->line_up_widget); // Switch to the lineup widget
        dialog.accept();
    });
    connect(buttonBox, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);
    mainLayout->addWidget(buttonBox);

    dialog.exec();
}

void MainWindow::setupLineupWidget(int matchId, int teamId, const QString& lineup) {
    ui->line_up_widget->hide();

    // Clear player lists
    allGoalkeepers.clear();
    allDefenders.clear();
    allMidfielders.clear();
    allForwards.clear();

    // Populate player lists by position with status
    QSqlQuery query;
    query.prepare("SELECT ID_PLAYER, FIRST_NAME, LAST_NAME, POSITION, STATUS FROM JOUEUR WHERE ID_TEAM = :teamId");
    query.bindValue(":teamId", teamId);
    if (!query.exec()) {
        qDebug() << "Error fetching players:" << query.lastError().text();
        QMessageBox::critical(this, "Database Error", "Failed to load players: " + query.lastError().text());
        return;
    }

    while (query.next()) {
        int id = query.value("ID_PLAYER").toInt();
        QString name = query.value("LAST_NAME").toString();
        QString position = query.value("POSITION").toString();
        int status = query.value("STATUS").toInt();
        QString displayName = (status == 0) ? "✅ " + name : "❌ " + name;

        if (position == "Goalkeeper") {
            allGoalkeepers.append({id, displayName, status});
        } else if (position == "Defender") {
            allDefenders.append({id, displayName, status});
        } else if (position == "Midfielder") {
            allMidfielders.append({id, displayName, status});
        } else if (position == "Forward") {
            allForwards.append({id, displayName, status});
        }
    }

    qDebug() << "Players loaded - GK:" << allGoalkeepers.size() << "DF:" << allDefenders.size()
             << "MF:" << allMidfielders.size() << "FW:" << allForwards.size();

    struct Position {
        int x, y, w, h;
    };

    Position pos433[] = {
        {557, 470, 72, 24}, {470, 400, 72, 24}, {640, 400, 72, 24}, {350, 370,72, 24}, {750, 370, 72, 24},
        {440, 250, 72, 24}, {667, 250, 72, 24}, {554, 300, 72, 24}, {400, 120, 72, 24}, {703, 120, 72, 24}, {556, 100, 72, 24}
    };

    Position pos442[] = {
        {557, 470, 72, 24}, {470, 400, 72, 24}, {640, 400, 72, 24}, {350, 370, 72, 24}, {750, 370, 72, 24},
        {480, 290, 72, 24}, {630, 290, 72, 24}, {390, 230, 72, 24}, {720, 230, 72, 24}, {490, 120, 72, 24}, {623, 120, 72, 24}
    };

    Position* positions = (lineup == "4-3-3") ? pos433 : pos442;
    int totalPlayers = 11;

    // Create and position combo boxes with enhanced stylesheet
    for (int i = 0; i < totalPlayers; ++i) {
        QComboBox* box = new QComboBox(ui->line_up_widget);
        box->setGeometry(positions[i].x, positions[i].y, positions[i].w, positions[i].h);
        box->setStyleSheet(
            "QComboBox {"
            "  background-color: #3A3A4A;"
            "  color: #FFFFFF;"
            "  border: 1px solid #5A5A6A;"
            "  border-radius: 4px;"
            "  padding: 4px;"
            "  font-size: 12px;"
            "}"
            "QComboBox:hover {"
            "  border: 1px solid #7A7A8A;"
            "}"
            "QComboBox::drop-down {"
            "  border-left: 1px solid #5A5A6A;"
            "  width: 20px;"
            "}"
            "QComboBox QAbstractItemView {"
            "  background-color: #3A3A4A;"
            "  color: #FFFFFF;"
            "  selection-background-color: #5A5A6A;"
            "  border: 1px solid #5A5A6A;"
            "}"
        );

        QString pos;
        if (i == 0) pos = "Goalkeeper";
        else if (i >= 1 && i <= 4) pos = "Defender";
        else if (i >= 5 && i < (lineup == "4-3-3" ? 8 : 9)) pos = "Midfielder";
        else pos = "Forward";

        positionBoxes.append({box, pos});
    }

    // Initial population
    updateAvailablePlayers();

    // Add "Save Lineup" button
    QPushButton* saveButton = new QPushButton("Save Lineup", ui->line_up_widget);
    saveButton->setGeometry(90, 200, 100, 30);
    saveButton->setStyleSheet(
        "QPushButton {"
        "  background-color: #4CAF50;"
        "  color: #FFFFFF;"
        "  border: none;"
        "  border-radius: 4px;"
        "  padding: 6px 12px;"
        "  font-size: 13px;"
        "  font-weight: bold;"
        "}"
        "QPushButton:hover {"
        "  background-color: #45A049;"
        "}"
        "QPushButton:pressed {"
        "  background-color: #3D8B40;"
        "}"
    );

    // Add "Cancel" button
    QPushButton* cancelButton = new QPushButton("Cancel", ui->line_up_widget);
    cancelButton->setGeometry(90, 280, 100, 30);
    cancelButton->setStyleSheet(
        "QPushButton {"
        "  background-color: #E94E77;"
        "  color: #FFFFFF;"
        "  border: none;"
        "  border-radius: 4px;"
        "  padding: 6px 12px;"
        "  font-size: 13px;"
        "  font-weight: bold;"
        "}"
        "QPushButton:hover {"
        "  background-color: #C94063;"
        "}"
        "QPushButton:pressed {"
        "  background-color: #A83352;"
        "}"
    );

    // Connect "Save Lineup" with cancelButton cleanup
    connect(saveButton, &QPushButton::clicked, this, [this, matchId, teamId, lineup, saveButton, cancelButton]() {
        qDebug() << "Save Lineup clicked";
        QList<int> selectedPlayers;
        for (const auto& [box, _] : positionBoxes) {
            int playerId = box->currentData().toInt();
            if (playerId == -1) {
                QMessageBox msgBox;
                msgBox.setIcon(QMessageBox::Warning);
                msgBox.setWindowTitle("⚠️ Incomplete Lineup");
                msgBox.setText("All positions must be filled before saving the lineup!");
                msgBox.setStyleSheet(
                    "QMessageBox { background-color: #2A2A3A; color: #FFFFFF; font-family: 'Segoe UI'; border-radius: 10px; }"
                    "QLabel { color: #FFFFFF; font-size: 14px; }"
                    "QPushButton { background-color: #E94E77; color: #FFFFFF; border-radius: 5px; padding: 8px; font-size: 12px; }"
                    "QPushButton:hover { background-color: #C94063; }"
                );
                msgBox.exec();
                return;
            }
            selectedPlayers.append(playerId);
        }

        bool hasDuplicates = false;
        QSet<int> seenPlayers;
        for (int id : selectedPlayers) {
            if (seenPlayers.contains(id)) {
                hasDuplicates = true;
                break;
            }
            seenPlayers.insert(id);
        }

        if (selectedPlayers.size() != 11 || hasDuplicates) {
            QMessageBox::warning(this, "Error", "Please select exactly 11 unique players!");
            return;
        }

        if (Match::setLineup(matchId, teamId, lineup, selectedPlayers)) {
            QMessageBox msgBox;
            msgBox.setIcon(QMessageBox::Information);
            msgBox.setWindowTitle("✅ Success");
            msgBox.setText("Lineup set successfully!");
            msgBox.setStyleSheet(
            "QMessageBox { background-color: #1E1E2F; color: #FFFFFF; font-family: 'Segoe UI'; border-radius: 10px; }"
            "QLabel { color: #FFFFFF; font-size: 14px; }"
            "QPushButton { background-color: #4CAF50; color: #FFFFFF; border-radius: 5px; padding: 8px; font-size: 12px; }"
            "QPushButton:hover { background-color: #45A049; }"
            );
            msgBox.exec();

            for (const auto& [box, _] : positionBoxes) {
            if (box) box->deleteLater();
            }
            positionBoxes.clear();
            if (saveButton) saveButton->deleteLater();
            if (cancelButton) cancelButton->deleteLater(); // Added cleanup for cancelButton

        } else {
            QMessageBox msgBox;
            msgBox.setIcon(QMessageBox::Critical);
            msgBox.setWindowTitle("❌ Error");
            msgBox.setText("Failed to set lineup!");
            msgBox.setStyleSheet(
            "QMessageBox { background-color: #1E1E2F; color: #FFFFFF; font-family: 'Segoe UI'; border-radius: 10px; }"
            "QLabel { color: #FFFFFF; font-size: 14px; }"
            "QPushButton { background-color: #E94E77; color: #FFFFFF; border-radius: 5px; padding: 8px; font-size: 12px; }"
            "QPushButton:hover { background-color: #C94063; }"
            );
            msgBox.exec();
        }
    });

    // Connect "Cancel" button
    connect(cancelButton, &QPushButton::clicked, this, [this, cancelButton, saveButton]() {
        qDebug() << "Cancel clicked";
        for (const auto& [box, _] : positionBoxes) {
            if (box) {
                qDebug() << "Deleting combo box:" << box;
                box->deleteLater();
            }
        }
        positionBoxes.clear();
        if (cancelButton) {
            qDebug() << "Deleting cancelButton:" << cancelButton;
            cancelButton->deleteLater();
        }
        if (saveButton) {
            qDebug() << "Deleting saveButton:" << saveButton;
            saveButton->deleteLater();
        }
        
        qDebug() << "Cancel cleanup complete";
    });

    ui->line_up_widget->show();
}

void MainWindow::updateAvailablePlayers() {
    if (updating) {
        qDebug() << "Skipping update due to recursion guard";
        return;
    }
    updating = true;
    qDebug() << "Starting updateAvailablePlayers...";

    // Disconnect all signals to prevent recursion
    for (const auto& [box, _] : positionBoxes) {
        disconnect(box, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &MainWindow::updateAvailablePlayers);
    }

    // Collect current selections
    QMap<QComboBox*, int> currentSelections;
    for (const auto& [box, _] : positionBoxes) {
        int id = box->currentData().toInt();
        currentSelections[box] = id;
        qDebug() << "Box:" << box << "Current ID:" << id;
    }

    // Update each combobox
    for (const auto& [box, pos] : positionBoxes) {
        qDebug() << "Updating box:" << box << "Position:" << pos;
        int currentId = currentSelections[box];
        QList<int> selectedIds;
        for (const auto& [otherBox, _] : positionBoxes) {
            if (otherBox != box) {
                int id = currentSelections[otherBox];
                if (id != -1) selectedIds.append(id);
            }
        }

        box->clear();
        qDebug() << "Cleared box:" << box;
        box->addItem("Select Player", -1);

        // Use a QList with status
        using PlayerInfo = std::tuple<int, QString, int>; // id, name, status
        const QList<PlayerInfo>* playerList = nullptr;
        if (pos == "Goalkeeper") playerList = &allGoalkeepers;
        else if (pos == "Defender") playerList = &allDefenders;
        else if (pos == "Midfielder") playerList = &allMidfielders;
        else if (pos == "Forward") playerList = &allForwards;

        if (playerList) {
            for (const auto& player : *playerList) {
                int playerId = std::get<0>(player);
                QString playerName = std::get<1>(player);
                int playerStatus = std::get<2>(player);

                if (!selectedIds.contains(playerId) || playerId == currentId) {
                    box->addItem(playerName, playerId);
                    int index = box->count() - 1;
                    if (playerStatus == 1) { // Player cannot play
                        // Disable the item by removing the enabled flag
                        box->model()->setData(box->model()->index(index, 0), QVariant(false), Qt::UserRole - 1);
                        box->setItemData(index, QColor("#808080"), Qt::ForegroundRole); // Gray out text
                    }
                }
            }
            qDebug() << "Populated box:" << box << "with" << (box->count() - 1) << "players";
            if (currentId != -1) {
                int index = box->findData(currentId);
                if (index != -1) {
                    // Only set the current index if the player is playable (status == 0)
                    QVariant isEnabled = box->itemData(index, Qt::UserRole - 1);
                    if (isEnabled.isNull() || isEnabled.toBool()) { // Enabled by default or explicitly true
                        box->setCurrentIndex(index);
                        qDebug() << "Restored selection for box:" << box << "to ID:" << currentId << "at index:" << index;
                    } else {
                        qDebug() << "Skipped selection for box:" << box << "ID:" << currentId << "is disabled";
                    }
                } else {
                    qDebug() << "Could not restore selection for box:" << box << "ID:" << currentId << "not found";
                }
            }
        }
    }

    // Reconnect signals
    for (const auto& [box, _] : positionBoxes) {
        connect(box, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &MainWindow::updateAvailablePlayers);
    }

    updating = false;
    qDebug() << "Update complete.";
}
void MainWindow::on_showFullLineupTriggered() {
    // Step 1: Check if a match is selected
    QModelIndexList selectedRows = ui->allmatches->selectionModel()->selectedRows();
    if (selectedRows.isEmpty()) {
        QMessageBox::warning(this, "Error", "No match selected!");
        return;
    }

    int matchId = selectedRows.first().sibling(selectedRows.first().row(), 0).data().toInt();
    Match match;
    for (const Match &m : Match::readAllMatches()) {
        if (m.getId() == matchId) {
            match = m;
            break;
        }
    }

    // Step 2: Get team IDs from the match
    int teamAId = match.getTeamA();
    int teamBId = match.getTeamB();

    // Step 3: Check if both teams have exactly 11 players
    QSqlQuery teamAQuery;
    teamAQuery.prepare(
        "SELECT COUNT(*) "
        "FROM HOTSTUFF.TACHKILA t "
        "JOIN HOTSTUFF.JOUEUR j ON t.ID_PLAYER = j.ID_PLAYER "
        "WHERE t.ID_MATCH = :matchId AND j.ID_TEAM = :teamId"
    );
    teamAQuery.bindValue(":matchId", matchId);
    teamAQuery.bindValue(":teamId", teamAId);
    if (!teamAQuery.exec() || !teamAQuery.next()) {
        QMessageBox::critical(this, "Database Error", "Failed to check Team A lineup: " + teamAQuery.lastError().text());
        return;
    }
    int teamAPlayerCount = teamAQuery.value(0).toInt();

    QSqlQuery teamBQuery;
    teamBQuery.prepare(
        "SELECT COUNT(*) "
        "FROM HOTSTUFF.TACHKILA t "
        "JOIN HOTSTUFF.JOUEUR j ON t.ID_PLAYER = j.ID_PLAYER "
        "WHERE t.ID_MATCH = :matchId AND j.ID_TEAM = :teamId"
    );
    teamBQuery.bindValue(":matchId", matchId);
    teamBQuery.bindValue(":teamId", teamBId);
    if (!teamBQuery.exec() || !teamBQuery.next()) {
        QMessageBox::critical(this, "Database Error", "Failed to check Team B lineup: " + teamBQuery.lastError().text());
        return;
    }
    int teamBPlayerCount = teamBQuery.value(0).toInt();

    if (teamAPlayerCount != 11 || teamBPlayerCount != 11) {
        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setWindowTitle("⚠️ Lineup Incomplete");
        msgBox.setText(
            QString("The full lineup is not set!\n\n"
                    "Team A: %1 players\n"
                    "Team B: %2 players\n\n"
                    "Each team must have exactly 11 players to proceed.")
            .arg(teamAPlayerCount).arg(teamBPlayerCount)
        );
        msgBox.setStyleSheet(
            "QMessageBox { background-color: #2A2A3A; color: #FFFFFF; font-family: 'Segoe UI'; border-radius: 10px; }"
            "QLabel { color: #FFFFFF; font-size: 14px; }"
            "QPushButton { background-color: #E94E77; color: #FFFFFF; border-radius: 5px; padding: 8px; font-size: 12px; }"
            "QPushButton:hover { background-color: #C94063; }"
        );
        msgBox.exec();
        return;
    }

    // Step 4: Fetch Team A lineup with image data and positions
    QSqlQuery teamALineupQuery;
    teamALineupQuery.prepare(
        "SELECT j.FIRST_NAME, j.LAST_NAME, j.IMG_JOUEUR, j.POSITION, t.FORMATION "
        "FROM HOTSTUFF.TACHKILA t "
        "JOIN HOTSTUFF.JOUEUR j ON t.ID_PLAYER = j.ID_PLAYER "
        "WHERE t.ID_MATCH = :matchId AND j.ID_TEAM = :teamId "
        "ORDER BY CASE j.POSITION "
        "   WHEN 'Goalkeeper' THEN 1 "
        "   WHEN 'Defender' THEN 2 "
        "   WHEN 'Midfielder' THEN 3 "
        "   WHEN 'Forward' THEN 4 "
        "   ELSE 5 END"
    );
    teamALineupQuery.bindValue(":matchId", matchId);
    teamALineupQuery.bindValue(":teamId", teamAId);
    if (!teamALineupQuery.exec()) {
        QMessageBox::critical(this, "Database Error", "Failed to fetch Team A lineup: " + teamALineupQuery.lastError().text());
        return;
    }

    // Step 5: Fetch Team B lineup with image data and positions
    QSqlQuery teamBLineupQuery;
    teamBLineupQuery.prepare(
        "SELECT j.FIRST_NAME, j.LAST_NAME, j.IMG_JOUEUR, j.POSITION, t.FORMATION "
        "FROM HOTSTUFF.TACHKILA t "
        "JOIN HOTSTUFF.JOUEUR j ON t.ID_PLAYER = j.ID_PLAYER "
        "WHERE t.ID_MATCH = :matchId AND j.ID_TEAM = :teamId "
        "ORDER BY CASE j.POSITION "
        "   WHEN 'Goalkeeper' THEN 1 "
        "   WHEN 'Defender' THEN 2 "
        "   WHEN 'Midfielder' THEN 3 "
        "   WHEN 'Forward' THEN 4 "
        "   ELSE 5 END"
    );
    teamBLineupQuery.bindValue(":matchId", matchId);
    teamBLineupQuery.bindValue(":teamId", teamBId);
    if (!teamBLineupQuery.exec()) {
        QMessageBox::critical(this, "Database Error", "Failed to fetch Team B lineup: " + teamBLineupQuery.lastError().text());
        return;
    }

    // Step 6: Create the dialog
    QDialog *lineupDialog = new QDialog(this);
    lineupDialog->setWindowTitle("Full Lineup - Match ID: " + QString::number(matchId));
    lineupDialog->setFixedSize(1200, 800);

    // Create the field widget (semi-transparent overlay)
    FieldWidget *fieldWidget = new FieldWidget(lineupDialog);
    fieldWidget->setGeometry(0, 120, 1200, 580); // Adjusted to make space for the taller header
    fieldWidget->setStyleSheet(
        "background: rgba(0, 0, 0, 0.3);" // Semi-transparent overlay
    );

    // Get formations
    QString teamAFormation = "Unknown";
    if (teamALineupQuery.next()) {
        teamAFormation = teamALineupQuery.value("FORMATION").toString();
        teamALineupQuery.seek(-1);
    }
    QString teamBFormation = "Unknown";
    if (teamBLineupQuery.next()) {
        teamBFormation = teamBLineupQuery.value("FORMATION").toString();
        teamBLineupQuery.seek(-1);
    }

    // Parse formations to determine the number of players in each position
    QStringList teamAFormationParts = teamAFormation.split("-");
    QStringList teamBFormationParts = teamBFormation.split("-");

    int teamAMidfielders = teamAFormationParts.size() > 1 ? teamAFormationParts[1].toInt() : 4;
    int teamAForwards = teamAFormationParts.size() > 2 ? teamAFormationParts[2].toInt() : 2;

    int teamBMidfielders = teamBFormationParts.size() > 1 ? teamBFormationParts[1].toInt() : 3;
    int teamBForwards = teamBFormationParts.size() > 2 ? teamBFormationParts[2].toInt() : 3;

    // Fetch team logos from the EQUIPE table
    QSqlQuery teamALogoQuery;
    teamALogoQuery.prepare("SELECT TEAM_LOGO FROM HOTSTUFF.EQUIPE WHERE ID_TEAM = :teamId");
    teamALogoQuery.bindValue(":teamId", teamAId);
    QByteArray teamALogoData;
    if (teamALogoQuery.exec() && teamALogoQuery.next()) {
        teamALogoData = teamALogoQuery.value("TEAM_LOGO").toByteArray();
    } else {
        QMessageBox::warning(this, "Database Warning", "Failed to fetch Team A logo: " + teamALogoQuery.lastError().text());
    }

    QSqlQuery teamBLogoQuery;
    teamBLogoQuery.prepare("SELECT TEAM_LOGO FROM HOTSTUFF.EQUIPE WHERE ID_TEAM = :teamId");
    teamBLogoQuery.bindValue(":teamId", teamBId);
    QByteArray teamBLogoData;
    if (teamBLogoQuery.exec() && teamBLogoQuery.next()) {
        teamBLogoData = teamBLogoQuery.value("TEAM_LOGO").toByteArray();
    } else {
        QMessageBox::warning(this, "Database Warning", "Failed to fetch Team B logo: " + teamBLogoQuery.lastError().text());
    }

    // Team logos, names, and formations at the top
    QHBoxLayout *topLayout = new QHBoxLayout();

    // Add a background to the top layout for a premium look
    QWidget *topWidget = new QWidget(lineupDialog);
    topWidget->setStyleSheet(
        "background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #1C2526, stop:1 #2A3435);" // Subtle dark gradient
        "border-bottom: 1px solid #444;" // Thin border to separate from the field
    );
    topWidget->setLayout(topLayout);

    // Team A (Left side: Logo, Name, Formation)
    QVBoxLayout *teamALayout = new QVBoxLayout();

    // Team A Logo
    QLabel *teamALogoLabel = new QLabel(lineupDialog);
    if (!teamALogoData.isEmpty()) {
        QPixmap teamALogoPixmap;
        teamALogoPixmap.loadFromData(teamALogoData);
        teamALogoLabel->setPixmap(teamALogoPixmap.scaled(40, 40, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    } else {
        teamALogoLabel->setText("No Logo");
    }
    teamALogoLabel->setFixedSize(40, 40);
    teamALogoLabel->setStyleSheet("background: transparent;");
    teamALogoLabel->setAlignment(Qt::AlignCenter);
    teamALayout->addWidget(teamALogoLabel, 0, Qt::AlignCenter);

    // Team A Name
    QLabel *teamANameLabel = new QLabel(match.getTeamAName(), lineupDialog);
    teamANameLabel->setStyleSheet(
        "color: #FFFFFF;" // Pure white for clarity
        "font-size: 20px;"
        "font-weight: bold;"
        "font-family: 'Montserrat', 'Arial', sans-serif;" // Modern, professional font
        "text-transform: uppercase;" // Uppercase for a bold look
        "letter-spacing: 1px;" // Slight spacing for readability
        "background: transparent;"
    );
    teamANameLabel->setAlignment(Qt::AlignCenter);
    teamALayout->addWidget(teamANameLabel, 0, Qt::AlignCenter);

    // Team A Formation
    QLabel *teamAFormationLabel = new QLabel(teamAFormation, lineupDialog);
    teamAFormationLabel->setStyleSheet(
        "color: #FFFFFF;" // White text
        "font-size: 16px;"
        "font-weight: bold;"
        "font-family: 'Roboto Condensed', 'Arial', sans-serif;" // Clean, condensed font
        "background: rgba(0, 0, 0, 0.7);" // Semi-transparent black background
        "padding: 8px;"
        "border: 1px solid #D4AF37;" // Subtle gold border for a classy touch
        "border-radius: 5px;"
        "box-shadow: 0px 2px 4px rgba(0, 0, 0, 0.2);" // Subtle shadow for depth
        "text-align: center;"
        "text-transform: uppercase;"
        "letter-spacing: 1px;"
    );
    teamAFormationLabel->setFixedWidth(100); // Consistent width for alignment
    teamAFormationLabel->setAlignment(Qt::AlignCenter);
    teamALayout->addWidget(teamAFormationLabel, 0, Qt::AlignCenter);

    topLayout->addLayout(teamALayout);
    topLayout->addStretch(); // Space between Team A and "vs"

    // "vs" Label
    QLabel *vsLabel = new QLabel("VS", lineupDialog);
    vsLabel->setStyleSheet(
        "color: #D4AF37;" // Muted gold for a classy accent
        "font-size: 18px;"
        "font-weight: bold;"
        "font-family: 'Montserrat', 'Arial', sans-serif;"
        "background: transparent;"
        "padding: 5px;"
        "text-transform: uppercase;"
    );
    vsLabel->setAlignment(Qt::AlignCenter);
    topLayout->addWidget(vsLabel, 0, Qt::AlignCenter);
    topLayout->addStretch(); // Space between "vs" and Team B

    // Team B (Right side: Logo, Name, Formation)
    QVBoxLayout *teamBLayout = new QVBoxLayout();

    // Team B Logo
    QLabel *teamBLogoLabel = new QLabel(lineupDialog);
    if (!teamBLogoData.isEmpty()) {
        QPixmap teamBLogoPixmap;
        teamBLogoPixmap.loadFromData(teamBLogoData);
        teamBLogoLabel->setPixmap(teamBLogoPixmap.scaled(40, 40, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    } else {
        teamBLogoLabel->setText("No Logo");
    }
    teamBLogoLabel->setFixedSize(40, 40);
    teamBLogoLabel->setStyleSheet("background: transparent;");
    teamBLogoLabel->setAlignment(Qt::AlignCenter);
    teamBLayout->addWidget(teamBLogoLabel, 0, Qt::AlignCenter);

    // Team B Name
    QLabel *teamBNameLabel = new QLabel(match.getTeamBName(), lineupDialog);
    teamBNameLabel->setStyleSheet(
        "color: #FFFFFF;" // Pure white for clarity
        "font-size: 20px;"
        "font-weight: bold;"
        "font-family: 'Montserrat', 'Arial', sans-serif;" // Modern, professional font
        "text-transform: uppercase;" // Uppercase for a bold look
        "letter-spacing: 1px;" // Slight spacing for readability
        "background: transparent;"
    );
    teamBNameLabel->setAlignment(Qt::AlignCenter);
    teamBLayout->addWidget(teamBNameLabel, 0, Qt::AlignCenter);

    // Team B Formation
    QLabel *teamBFormationLabel = new QLabel(teamBFormation, lineupDialog);
    teamBFormationLabel->setStyleSheet(
        "color: #FFFFFF;" // White text
        "font-size: 16px;"
        "font-weight: bold;"
        "font-family: 'Roboto Condensed', 'Arial', sans-serif;" // Clean, condensed font
        "background: rgba(0, 0, 0, 0.7);" // Semi-transparent black background
        "padding: 8px;"
        "border: 1px solid #D4AF37;" // Subtle gold border for a classy touch
        "border-radius: 5px;"
        "box-shadow: 0px 2px 4px rgba(0, 0, 0, 0.2);" // Subtle shadow for depth
        "text-align: center;"
        "text-transform: uppercase;"
        "letter-spacing: 1px;"
    );
    teamBFormationLabel->setFixedWidth(100); // Consistent width for alignment
    teamBFormationLabel->setAlignment(Qt::AlignCenter);
    teamBLayout->addWidget(teamBFormationLabel, 0, Qt::AlignCenter);

    topLayout->addLayout(teamBLayout);

    QVBoxLayout *dialogLayout = new QVBoxLayout(lineupDialog);
    dialogLayout->addWidget(topWidget); // Add the top widget with the gradient background
    dialogLayout->addStretch();

    // Position players for Team A (facing right)
    int currentDefender = 0, currentMidfielder = 0, currentForward = 0;
    teamALineupQuery.seek(-1);
    while (teamALineupQuery.next()) {
        QString position = teamALineupQuery.value("POSITION").toString();
        QString playerName = teamALineupQuery.value("LAST_NAME").toString();
        QByteArray imageData = teamALineupQuery.value("IMG_JOUEUR").toByteArray();

        // Create the player image
        QLabel *playerImage = new QLabel(fieldWidget);
        if (!imageData.isEmpty()) {
            QPixmap pixmap;
            pixmap.loadFromData(imageData);
            playerImage->setPixmap(pixmap.scaled(50, 50, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        } else {
            playerImage->setPixmap(QPixmap(":/user.png").scaled(50, 50, Qt::KeepAspectRatio));
        }
        playerImage->setStyleSheet(
            "border-radius: 25px;" // Round image
            "background: transparent;" // Transparent background
        );
        playerImage->setAlignment(Qt::AlignCenter);
        playerImage->setFixedSize(50, 50);

        // Create the player name label
        QLabel *playerLabel = new QLabel(playerName, fieldWidget);
        playerLabel->setStyleSheet(
            "color: white; font-size: 10px;" // Plain white text, no background
        );
        playerLabel->setAlignment(Qt::AlignCenter);
        playerLabel->setWordWrap(true);
        playerLabel->setFixedWidth(60); // Slightly wider than the image for longer names

        // Position players on the field (Team A, facing right, 4-4-2 formation)
        int xPos = 0, yPos = 0;
        if (position == "Goalkeeper") {
            xPos = 60;
            yPos = 280; // Closer to the goal line
        } else if (position == "Defender" && currentDefender < 4) {
            switch (currentDefender) {
            case 0: xPos = 150; yPos = 340; break; // Right center-back
            case 1: xPos = 150; yPos = 200; break; // Left center-back
            case 2: xPos = 190; yPos = 90; break; // Left full-back
            case 3: xPos = 190; yPos = 450; break; // Right full-back
            }
            currentDefender++;
        } else if (position == "Midfielder" && currentMidfielder < teamAMidfielders) {
            if (teamAMidfielders == 4) {
                switch (currentMidfielder) {
                case 0: xPos = 300; yPos = 200; break; // Left midfielder cassado
                case 1: xPos = 300; yPos = 340; break; // Right midfielder pedri
                case 2: xPos = 370; yPos = 90; break; // Top midfielder dejong
                case 3: xPos = 370; yPos = 450; break; // Bottom midfielder gavi
                }
            } else { // 3 midfielders (fallback, not used in 4-4-2)
                switch (currentMidfielder) {
                case 0: xPos = 360; yPos = 130; break;
                case 1: xPos = 360; yPos = 370; break;
                case 2: xPos = 300; yPos = 250; break;
                }
            }
            currentMidfielder++;
        } else if (position == "Forward" && currentForward < teamAForwards) {
            if (teamAForwards == 2) {
                switch (currentForward) {
                case 0: xPos = 500; yPos = 200; break; // Left forward
                case 1: xPos = 500; yPos = 340; break; // Right forward
                }
            } else { // 3 forwards (fallback, not used in 4-4-2)
                switch (currentForward) {
                case 0: xPos = 505; yPos = 130; break;
                case 1: xPos = 505; yPos = 370; break;
                case 2: xPos = 530; yPos = 250; break;
                }
            }
            currentForward++;
        }

        // Position the image and label directly on the field
        playerImage->move(xPos, yPos);
        playerLabel->move(xPos - 5, yPos + 50); // Position the label just below the image (50 is the image height)
    }

    // Position players for Team B (facing left, 4-3-3 formation)
    currentDefender = 0, currentMidfielder = 0, currentForward = 0;
    teamBLineupQuery.seek(-1);
    while (teamBLineupQuery.next()) {
        QString position = teamBLineupQuery.value("POSITION").toString();
        QString playerName = teamBLineupQuery.value("LAST_NAME").toString();
        QByteArray imageData = teamBLineupQuery.value("IMG_JOUEUR").toByteArray();

        // Create the player image
        QLabel *playerImage = new QLabel(fieldWidget);
        if (!imageData.isEmpty()) {
            QPixmap pixmap;
            pixmap.loadFromData(imageData);
            playerImage->setPixmap(pixmap.scaled(50, 50, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        } else {
            playerImage->setPixmap(QPixmap(":/user.png").scaled(50, 50, Qt::KeepAspectRatio));
        }
        playerImage->setStyleSheet(
            "border-radius: 25px;" // Round image
            "background: transparent;" // Transparent background
        );
        playerImage->setAlignment(Qt::AlignCenter);
        playerImage->setFixedSize(50, 50);

        // Create the player name label
        QLabel *playerLabel = new QLabel(playerName, fieldWidget);
        playerLabel->setStyleSheet(
            "color: white; font-size: 10px;" // Plain white text, no background
        );
        playerLabel->setAlignment(Qt::AlignCenter);
        playerLabel->setWordWrap(true);
        playerLabel->setFixedWidth(60); // Slightly wider than the image for longer names

        // Position players on the field (Team B, facing left, 4-3-3 formation)
        int xPos = 0, yPos = 0;
        if (position == "Goalkeeper") {
            xPos = 1080;
            yPos = 280; // Closer to the goal line
        } else if (position == "Defender" && currentDefender < 4) {
            switch (currentDefender) {
            case 0: xPos = 990; yPos = 200; break; // Right center-back
            case 1: xPos = 990; yPos = 340; break; // Right full-back
            case 2: xPos = 960; yPos = 450; break; // Left full-back
            case 3: xPos = 960; yPos = 90; break; // Left center-back
            }
            currentDefender++;
        } else if (position == "Midfielder" && currentMidfielder < teamBMidfielders) {
            if (teamBMidfielders == 4) { // Fallback, not used in 4-3-3
                switch (currentMidfielder) {
                case 0: xPos = 800; yPos = 340; break;  
                case 1: xPos = 800; yPos = 200; break; 
                case 2: xPos = 730; yPos = 450; break; 
                case 3: xPos = 730; yPos = 90; break; 
                }
            } else { // 3 midfielders, triangle formation
                switch (currentMidfielder) {
                case 0: xPos = 800; yPos = 370; break; // Left midfielder (defensive)
                case 1: xPos = 800; yPos = 130; break; // Top midfielder (attacking)
                case 2: xPos = 840; yPos = 250; break; // Right midfielder (defensive)
                }
            }
            currentMidfielder++;
        } else if (position == "Forward" && currentForward < teamBForwards) {
            if (teamBForwards == 2) { // Fallback, not used in 4-3-3
                switch (currentForward) {
                case 0: xPos = 640; yPos = 340; break;
                case 1: xPos = 640; yPos = 200; break;
                }
            } else { // 3 forwards
                switch (currentForward) {
                case 0: xPos = 655; yPos = 370; break; // Left winger
                case 1: xPos = 655; yPos = 130; break; // Right winger
                case 2: xPos = 620; yPos = 250; break; // Center forward
                }
            }
            currentForward++;
        }

        // Position the image and label directly on the field
        playerImage->move(xPos, yPos);
        playerLabel->move(xPos - 5, yPos + 50); // Position the label just below the image (50 is the image height)
    }

    // Show the dialog
    lineupDialog->exec();
}
