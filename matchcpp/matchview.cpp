#include "../matchheaders/matchview.h"
#include "ui_matchview.h"
#include "../matchheaders/match.h"
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
#include "../matchheaders/fieldwidget.h"
#include <QTimer>
#include <algorithm>
#include "../matchheaders/watchmatchdialog.h"
#include "../matchheaders/addmatch.h"
#include "../matchheaders/displaymatch.h"
#include "../matchheaders/statsmatch.h"
#include "../matchheaders/chartmatch.h"
#include "../matchheaders/viewmatch.h"
#include <QLabel>
#include <QPixmap>
#include <QDateTime>
#include <QSqlQuery>
#include <QSqlError>
#include <cstdlib> // For rand and srand
#include <ctime>   // For time
#include "../userheaders/sessionmanager.h"
#include "../compheaders/competitionview.h"
#include "../playerheaders/playerwindow.h"
#include "../userheaders/mainwindow.h"
#include "../about.h"

matchview::matchview(QStackedWidget *stackedWidget, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::matchview)
    , matchModel(new QSqlTableModel(this)) // Initialize matchModel
    , ascendingOrder(true) // Initialize ascendingOrder
{
    // Seed the random number generator
    srand(static_cast<unsigned int>(time(nullptr)));

    ui->setupUi(this);
    

    // Attempt to connect to the database
    if (dbConnection.createconnect()) {
        qDebug() << "Database connected successfully in MainWindow";
        // Load current user's photo and details
    const Employee& currentUser = SessionManager::instance().getCurrentUser();
    if (!currentUser.getFace().isEmpty()) {
        QPixmap pixmap;
        if (pixmap.loadFromData(currentUser.getFace())) {
            ui->currentUserPhotoLabel->setPixmap(pixmap.scaled(ui->currentUserPhotoLabel->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
        } else {
            qDebug() << "Failed to load user photo from data.";
            ui->currentUserPhotoLabel->setText("No Photo");
        }
    } else {
        ui->currentUserPhotoLabel->setText("No Photo");
    }

    // Set username and role
    ui->dashboard_9->setText(currentUser.getFirstName() + " " + currentUser.getLastName());
    ui->dashboard_8->setText(currentUser.getRole());
    
        showSoonestMatchDetails();

        
    } else {
        qDebug() << "Failed to connect to database in MainWindow";
        // Disable combo boxes and show an error message
        QMessageBox::critical(this, "Error", "Database connection failed. Teams and competitions cannot be loaded.");
    }

}

matchview::~matchview()
{
    delete ui;
}
void matchview::on_userbutton_clicked() {
    // Use parent QStackedWidget to change view
    QStackedWidget *stackedWidget = qobject_cast<QStackedWidget*>(parentWidget());
    if (stackedWidget) {
        stackedWidget->setCurrentIndex(0);
    }
}
void matchview::on_playerButton_clicked() {
    // Use parent QStackedWidget to change view
    QStackedWidget *stackedWidget = qobject_cast<QStackedWidget*>(parentWidget());
    if (stackedWidget) {
        stackedWidget->setCurrentIndex(2);
    }
}
void matchview::on_logout_clicked()
{
    // Clear the session to log out the user
    SessionManager::instance().clearSession();

    // Update the photo label to indicate no user
    ui->currentUserPhotoLabel->setText("No User");
    ui->dashboard_9->setText("User name"); // Reset username label
    ui->dashboard_8->setText("Role");      // Reset role label

    // Re-show the parent MainWindow if it exists
    QWidget *parent = parentWidget();
    MainWindow *mainWindow = qobject_cast<MainWindow*>(parent);
    if (mainWindow) {
        mainWindow->showMaximized();
    } else {
        qDebug() << "No parent MainWindow found, creating a new one.";
        MainWindow *loginWindow = new MainWindow();
        loginWindow->showMaximized();
    }

    // Close all parent windows up the chain (including stacked widgets)
    QWidget *w = this;
    while (w) {
        QWidget *parent = w->parentWidget();
        w->close();
        w = parent;
    }
}

void matchview::on_aboutButton_clicked()
{
    qDebug() << "About button clicked.";
    About *aboutDialog = new About(this);
    aboutDialog->exec();
    delete aboutDialog;
}
void matchview::on_compButton_clicked() {
    // Use parent QStackedWidget to change view
    QStackedWidget *stackedWidget = qobject_cast<QStackedWidget*>(parentWidget());
    if (stackedWidget) {
        stackedWidget->setCurrentIndex(3);
    }
}
void matchview::on_teamButton_clicked() {
    // Use parent QStackedWidget to change view
    QStackedWidget *stackedWidget = qobject_cast<QStackedWidget*>(parentWidget());
    if (stackedWidget) {
        stackedWidget->setCurrentIndex(1);
    }
}

void matchview::on_addmatch_clicked() {
    addMatch *window = new addMatch(this);
    window->show();
}

void matchview::on_displaymatch_clicked() {
    displayMatch *window = new displayMatch(this);
    window->setAttribute(Qt::WA_DeleteOnClose);
    window->show();
}

void matchview::on_statsbutton_clicked() {
    statsMatch *window = new statsMatch(this);
    window->setAttribute(Qt::WA_DeleteOnClose);
    window->show();
}
void matchview::on_chartbutton_clicked() {
    chartMatch *window = new chartMatch(this);
    window->setAttribute(Qt::WA_DeleteOnClose);
    window->show();
}

void matchview::on_viewallmatches_clicked()
{
    viewMatch *window = new viewMatch(this);
    window->setAttribute(Qt::WA_DeleteOnClose);
    window->show();
}

void matchview::on_watchmatch_clicked() {
    // Retrieve the match ID stored in the button's property
    QVariant matchIdVariant = ui->watchmatch->property("matchId");
    if (!matchIdVariant.isValid()) {
        QMessageBox::warning(this, "Error", "No match is currently being watched.");
        return;
    }

    int matchId = matchIdVariant.toInt();
    WatchMatchDialog *dialog = new WatchMatchDialog(matchId, this);
    dialog->exec();
}

void matchview::showSoonestMatchDetails() {
    // Fetch soonest match
    Match soonestMatch;
    Match playingMatch;
    QDateTime soonest = QDateTime::fromString("2999-12-31T23:59:59", Qt::ISODate);
    QList<Match> allMatches = Match::readAllMatches();

    for (const Match &m : allMatches) {
        if (m.getStatus() == "Playing") {
            playingMatch = m;
            break; // Prioritize the playing match
        }
        if (m.getMatchDateTime() > QDateTime::currentDateTime() && m.getMatchDateTime() < soonest) {
            soonest = m.getMatchDateTime();
            soonestMatch = m;
        }
    }

    // If no playing or soonest match, show a random match
    Match matchToDisplay;
    if (playingMatch.getId()) {
        matchToDisplay = playingMatch;
    } else if (soonestMatch.getId()) {
        matchToDisplay = soonestMatch;
    } else if (!allMatches.isEmpty()) {
        matchToDisplay = allMatches[rand() % allMatches.size()];
    } else {
        ui->watchmatch->setVisible(false); // Hide the button if no match to display
        return;
    }

    // Show or hide the watchmatch button based on match status
    if (matchToDisplay.getStatus() == "Playing") {
        ui->watchmatch->setVisible(true);
        ui->watchmatch->setProperty("matchId", matchToDisplay.getId()); // Store the match ID in the button
    } else {
        ui->watchmatch->setVisible(false);
    }

    // Team A logo
    QLabel *logoA = new QLabel(this);
    logoA->setGeometry(870, 710, 100, 100);
    logoA->setStyleSheet("background-color: transparent;");
    QPixmap pixA;
    QSqlQuery qA;
    qA.prepare("SELECT TEAM_LOGO FROM EQUIPE WHERE TEAM_NAME = :name");
    qA.bindValue(":name", matchToDisplay.getTeamAName());
    if (qA.exec() && qA.next())
        pixA.loadFromData(qA.value(0).toByteArray());
    logoA->setPixmap(pixA.scaled(100, 100, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    logoA->show();

    // Team B logo
    QLabel *logoB = new QLabel(this);
    logoB->setGeometry(1180, 710, 100, 100);
    logoB->setStyleSheet("background-color: transparent;");
    QPixmap pixB;
    QSqlQuery qB;
    qB.prepare("SELECT TEAM_LOGO FROM EQUIPE WHERE TEAM_NAME = :name");
    qB.bindValue(":name", matchToDisplay.getTeamBName());
    if (qB.exec() && qB.next())
        pixB.loadFromData(qB.value(0).toByteArray());
    logoB->setPixmap(pixB.scaled(100, 100, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    logoB->show();

    // Score (centered between logos)
    QLabel *scoreLabel = new QLabel(this);
    scoreLabel->setGeometry(1010, 730, 120, 60);
    scoreLabel->setStyleSheet("background-color: transparent; color: white;");
    QFont scoreFont;
    scoreFont.setPointSize(32);
    scoreFont.setBold(true);
    scoreLabel->setFont(scoreFont);
    scoreLabel->setAlignment(Qt::AlignCenter);
    scoreLabel->setText(QString::number(matchToDisplay.getScoreA()) + "  -  " + QString::number(matchToDisplay.getScoreB()));
    scoreLabel->show();

    // Date (above score)
    QLabel *dateLabel = new QLabel(this);
    dateLabel->setGeometry(975, 584, 200, 30);
    dateLabel->setStyleSheet("background-color: transparent; color: white;");
    QFont dateFont;
    dateFont.setPointSize(10);
    dateFont.setBold(true);
    dateLabel->setFont(dateFont);
    dateLabel->setAlignment(Qt::AlignCenter);
    dateLabel->setText(matchToDisplay.getMatchDateTime().toString("dddd, dd MMM yyyy - hh:mm"));
    dateLabel->show();

    // Set match status in label_17
    if (ui->label_17) {
        ui->label_17->setText(matchToDisplay.getStatus());
        ui->label_17->setAlignment(Qt::AlignCenter);
    }
}

