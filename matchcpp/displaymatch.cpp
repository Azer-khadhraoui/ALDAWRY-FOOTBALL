#include "../matchheaders/displaymatch.h"
#include "ui_displaymatch.h"
#include "../matchheaders/match.h"
#include <QSqlQuery>
#include <QStandardItemModel>
#include <QPixmap>
#include <QMessageBox>
#include <QDateTime>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QComboBox>
#include <QLineEdit>
#include <QDateTimeEdit>
#include <QSpinBox>
#include <QSqlError>
#include <QFileDialog>



displayMatch::displayMatch (QWidget *parent) :
    QDialog(parent), 
    ui(new Ui::displayMatch),
    ascendingOrder(true) // Initialize ascendingOrder
{
    ui->setupUi(this);
    setupMatchTable(); // Call the function to set up the match table
    // Set up the UI components and layout here
    connect(ui->search, &QLineEdit::textChanged, this, &displayMatch::filterMatches);
    // Connect the header click signal to the sorting slot
    connect(ui->allmatches->horizontalHeader(), &QHeaderView::sectionClicked, this, &displayMatch::on_headerClicked);
    // Connect the double-click signal to the slot
    connect(ui->allmatches, &QTableView::doubleClicked, this, &displayMatch::on_matchDoubleClicked);
}
displayMatch::~displayMatch() {
    delete ui;
}
void displayMatch::setupMatchTable() {
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

void displayMatch::on_Delete_clicked() 
{
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
    setupMatchTable(); // Refresh the match table after deletion
}

void displayMatch::on_Modify_clicked() {
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
    dialog.setFixedWidth(420);
    dialog.setStyleSheet(
        "QDialog {"
        "  background-color: #23283b;"
        "  color: #FFFFFF;"
        "  border-radius: 16px;"
        "  padding: 24px;"
        "  font-family: 'Segoe UI', Arial, sans-serif;"
        "}"
        "QLabel {"
        "  color: #D0D0D0;"
        "  font-size: 15px;"
        "  font-weight: 500;"
        "  margin-bottom: 4px;"
        "}"
        "QLineEdit, QComboBox, QDateTimeEdit, QSpinBox {"
        "  background-color: #2A3240;"
        "  border: 1px solid #3A4A5A;"
        "  border-radius: 7px;"
        "  padding: 7px;"
        "  color: #E0E6ED;"
        "  font-size: 14px;"
        "  margin-bottom: 12px;"
        "}"
        "QComboBox QAbstractItemView {"
        "  background-color: #23283b;"
        "  color: #E0E6ED;"
        "}"
        "QPushButton {"
        "  background-color: #4A90E2;"
        "  color: #FFFFFF;"
        "  border-radius: 7px;"
        "  padding: 8px 18px;"
        "  font-size: 14px;"
        "  font-weight: bold;"
        "  margin-top: 12px;"
        "}"
        "QPushButton:hover {"
        "  background-color: #357ABD;"
        "}"
        "QPushButton:pressed {"
        "  background-color: #2A6099;"
        "}"
    );

    QVBoxLayout *mainLayout = new QVBoxLayout(&dialog);
    QLabel *titleLabel = new QLabel("Modify Match");
    titleLabel->setAlignment(Qt::AlignCenter);
    QFont titleFont("Segoe UI", 18, QFont::Bold);
    titleLabel->setFont(titleFont);
    titleLabel->setStyleSheet("background-color: transparent;");
    mainLayout->addWidget(titleLabel);

    QFormLayout *formLayout = new QFormLayout();
    formLayout->setSpacing(16);

    // Helper lambda to create transparent background labels
    auto makeLabel = [](const QString &text) {
        QLabel *label = new QLabel(text);
        label->setStyleSheet("background-color: transparent; color: #D0D0D0; font-size: 15px; font-weight: 500; margin-bottom: 4px;");
        return label;
    };

    QComboBox *team1Box = new QComboBox(&dialog);
    QComboBox *team2Box = new QComboBox(&dialog);
    Match::loadTeamsIntoComboBoxes(team1Box, team2Box);
    team1Box->setCurrentText(match.getTeamAName());
    team2Box->setCurrentText(match.getTeamBName());
    formLayout->addRow(makeLabel("Team 1:"), team1Box);
    formLayout->addRow(makeLabel("Team 2:"), team2Box);

    QLineEdit *stadiumEdit = new QLineEdit(&dialog);
    stadiumEdit->setText(match.getStadium());
    formLayout->addRow(makeLabel("Stadium:"), stadiumEdit);

    QLineEdit *refereeEdit = new QLineEdit(&dialog);
    refereeEdit->setText(match.getReferee());
    formLayout->addRow(makeLabel("Referee:"), refereeEdit);

    QDateTimeEdit *dateTimeEdit = new QDateTimeEdit(&dialog);
    dateTimeEdit->setDateTime(match.getMatchDateTime());
    dateTimeEdit->setCalendarPopup(true);
    formLayout->addRow(makeLabel("Date & Time:"), dateTimeEdit);

    QSpinBox *scoreAEdit = new QSpinBox(&dialog);
    scoreAEdit->setRange(0, 100);
    scoreAEdit->setValue(match.getScoreA());
    formLayout->addRow(makeLabel("Score A:"), scoreAEdit);

    QSpinBox *scoreBEdit = new QSpinBox(&dialog);
    scoreBEdit->setRange(0, 100);
    scoreBEdit->setValue(match.getScoreB());
    formLayout->addRow(makeLabel("Score B:"), scoreBEdit);

    QComboBox *compBox = new QComboBox(&dialog);
    Match::loadCompetitionsIntoComboBox(compBox);
    compBox->setCurrentText(match.getCompetitionName());
    formLayout->addRow(makeLabel("Competition:"), compBox);

    QComboBox *statusBox = new QComboBox(&dialog);
    statusBox->addItem("Scheduled");
    statusBox->addItem("Playing");
    statusBox->addItem("Played");
    statusBox->setCurrentText(match.getStatus());
    formLayout->addRow(makeLabel("Status:"), statusBox);

    QComboBox *weatherBox = new QComboBox(&dialog);
    weatherBox->addItem("Sunny", 0);
    weatherBox->addItem("Rainy", 1);
    int meteo = match.getMeteo();
    weatherBox->setCurrentIndex((meteo == 0 || meteo == 1) ? meteo : 0);
    formLayout->addRow(makeLabel("Weather:"), weatherBox);

    mainLayout->addLayout(formLayout);

    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, &dialog);
    mainLayout->addWidget(buttonBox);
    connect(buttonBox, &QDialogButtonBox::accepted, &dialog, &QDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);

    dialog.setLayout(mainLayout);
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
        setupMatchTable(); // Refresh the match table after modification
        
    }
}

void displayMatch::filterMatches(const QString &text) {
    if (text.isEmpty()) {
        setupMatchTable();
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
}

void displayMatch::on_headerClicked(int logicalIndex) {
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
void displayMatch::on_pdf_clicked() {
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
void displayMatch::on_matchDoubleClicked(const QModelIndex &index) {
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
