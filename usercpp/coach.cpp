#include "../userheaders/coach.h"
#include "ui_coach.h"
#include "../userheaders/displayplayers_coach.h"
#include <QDebug>
#include "../userheaders/sessionmanager.h"
#include "../userheaders/mainwindow.h"
#include <QLineEdit>
#include "../userheaders/displaymatch_coach.h"
#include "../teamheaders/team.h"
#include "addtododialog.h"
#include <QSqlError>
#include <QMessageBox>
#include <QMimeData>
#include <QHBoxLayout>
#include <QLabel>
#include <QDrag>
#include <QGraphicsDropShadowEffect>
#include "../about.h"

CoachWindow::CoachWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::CoachWindow)
{
    ui->setupUi(this);

    // Connect buttons
    connect(ui->Viewplayers, &QPushButton::clicked, this, &CoachWindow::on_viewplayer_clicked);
    connect(ui->logout, &QPushButton::clicked, this, &CoachWindow::logout);


    // Initialize models
    pendingModel = new QStandardItemModel(this);
    doingModel = new QStandardItemModel(this);
    doneModel = new QStandardItemModel(this);

    // Create Kanban board layout
    QWidget *kanbanWidget = new QWidget(this);
    kanbanWidget->setStyleSheet(R"(
        QWidget {
            background: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 #22252D, stop:1 #1F2633);
            border: 2px solid #F5A623;
            border-radius: 12px;
            padding: 15px;
        }
    )");

    // Add shadow effect
    QGraphicsDropShadowEffect *shadowEffect = new QGraphicsDropShadowEffect(kanbanWidget);
    shadowEffect->setBlurRadius(20);
    shadowEffect->setColor(QColor(0, 0, 0, 100));
    shadowEffect->setOffset(0, 5);
    kanbanWidget->setGraphicsEffect(shadowEffect);

    QHBoxLayout *kanbanLayout = new QHBoxLayout(kanbanWidget);
    kanbanLayout->setSpacing(15);
    kanbanLayout->setContentsMargins(10, 10, 10, 10);

    // Pending column
    pendingListView = new TodoListView(kanbanWidget);
    pendingListView->setModel(pendingModel);
    pendingListView->setProperty("status", "Pending");
    QLabel *pendingLabel = new QLabel("Pending", kanbanWidget);
    pendingLabel->setStyleSheet(R"(
        color: #FFFFFF;
        font: 16pt "Segoe UI";
        background: transparent;
        border-bottom: 2px solid #F5A623;
        padding-bottom: 5px;
        margin-bottom: 10px;
    )");
    QVBoxLayout *pendingLayout = new QVBoxLayout();
    pendingLayout->addWidget(pendingLabel);
    pendingLayout->addWidget(pendingListView);
    pendingLayout->setSpacing(5);
    kanbanLayout->addLayout(pendingLayout);
    kanbanLayout->setStretch(0, 1);

    // Doing column
    doingListView = new TodoListView(kanbanWidget);
    doingListView->setModel(doingModel);
    doingListView->setProperty("status", "Doing");
    QLabel *doingLabel = new QLabel("Doing", kanbanWidget);
    doingLabel->setStyleSheet(R"(
        color: #FFFFFF;
        font: 16pt "Segoe UI";
        background: transparent;
        border-bottom: 2px solid #3B82F6;
        padding-bottom: 5px;
        margin-bottom: 10px;
    )");
    QVBoxLayout *doingLayout = new QVBoxLayout();
    doingLayout->addWidget(doingLabel);
    doingLayout->addWidget(doingListView);
    doingLayout->setSpacing(5);
    kanbanLayout->addLayout(doingLayout);
    kanbanLayout->setStretch(1, 1);

    // Done column
    doneListView = new TodoListView(kanbanWidget);
    doneListView->setModel(doneModel);
    doneListView->setProperty("status", "Done");
    QLabel *doneLabel = new QLabel("Done", kanbanWidget);
    doneLabel->setStyleSheet(R"(
        color: #FFFFFF;
        font: 16pt "Segoe UI";
        background: transparent;
        border-bottom: 2px solid #10B981;
        padding-bottom: 5px;
        margin-bottom: 10px;
    )");
    QVBoxLayout *doneLayout = new QVBoxLayout();
    doneLayout->addWidget(doneLabel);
    doneLayout->addWidget(doneListView);
    doneLayout->setSpacing(5);
    kanbanLayout->addLayout(doneLayout);
    kanbanLayout->setStretch(2, 1);

    // Replace original listView
    if (ui->listView->parentWidget()) {
        kanbanWidget->setGeometry(ui->listView->geometry());
        kanbanWidget->setParent(ui->listView->parentWidget());
        ui->listView->setVisible(false);
        kanbanWidget->show();
        delete ui->listView;
        ui->listView = pendingListView; // For compatibility
    } else {
        qDebug() << "Error: listView has no parent widget.";
        kanbanWidget->setParent(ui->centralwidget);
        kanbanWidget->setGeometry(QRect(270, 580, 1000, 411));
        kanbanWidget->show();
        delete ui->listView;
        ui->listView = pendingListView;
    }

    // Connect click handlers
    connect(pendingListView, &QListView::clicked, this, &CoachWindow::on_todoItemClicked);
    connect(doingListView, &QListView::clicked, this, &CoachWindow::on_todoItemClicked);
    connect(doneListView, &QListView::clicked, this, &CoachWindow::on_todoItemClicked);

    // Connect dataChanged signals to refresh UI
    connect(pendingModel, &QStandardItemModel::dataChanged, this, &CoachWindow::updateTodoList);
    connect(doingModel, &QStandardItemModel::dataChanged, this, &CoachWindow::updateTodoList);
    connect(doneModel, &QStandardItemModel::dataChanged, this, &CoachWindow::updateTodoList);

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

    // Load team logo
    int coachId = currentUser.getId();
    Team* team = Team::getTeamByCoachId(coachId);
    if (team) {
        QString teamName = team->getTeamName();
        QSqlQuery logoQuery;
        logoQuery.prepare("SELECT TEAM_LOGO FROM EQUIPE WHERE TEAM_NAME = :teamName");
        logoQuery.bindValue(":teamName", teamName);
        if (logoQuery.exec() && logoQuery.next()) {
            QByteArray logoData = logoQuery.value("TEAM_LOGO").toByteArray();
            QPixmap teamLogo;
            if (teamLogo.loadFromData(logoData)) {
                ui->label_3->setPixmap(teamLogo.scaled(ui->label_3->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
            } else {
                ui->label_3->setText("No Logo");
            }
        } else {
            ui->label_3->setText("No Logo");
        }
        delete team;
    } else {
        ui->label_3->setText("No Logo");
    }

    // Set username and role
    ui->dashboard_9->setText(currentUser.getFirstName() + " " + currentUser.getLastName());
    ui->dashboard_8->setText(currentUser.getRole());
    setWindowTitle("Coach Dashboard");

    // Load to-do list
    loadTodoList();
}

CoachWindow::~CoachWindow()
{
    delete ui;
}



void CoachWindow::loadTodoList()
{
    pendingModel->clear();
    doingModel->clear();
    doneModel->clear();

    int teamId = getCoachTeamId();
    if (teamId == -1) {
        qDebug() << "No team found for coach.";
        return;
    }

    QSqlQuery query;
    query.prepare("SELECT IDTODO, TODO, STATS, DATETODO FROM HOTSTUFF.TODO WHERE IDTEAM = :idteam ORDER BY DATETODO");
    query.bindValue(":idteam", teamId);
    if (!query.exec()) {
        qDebug() << "Failed to load tasks:" << query.lastError().text();
        return;
    }

    while (query.next()) {
        int idTodo = query.value("IDTODO").toInt();
        QString task = query.value("TODO").toString();
        QString status = query.value("STATS").toString();
        QDateTime date = query.value("DATETODO").toDateTime();

        QString statusIndicator;
        if (status == "Pending") {
            statusIndicator = "🔶 ";
        } else if (status == "Doing") {
            statusIndicator = "🔵 ";
        } else {
            statusIndicator = "✅ ";
        }
        QStandardItem *item = new QStandardItem(statusIndicator + task + "\nDue: " + date.toString("yyyy-MM-dd hh:mm"));
        item->setData(idTodo, Qt::UserRole);
        item->setData(status, Qt::UserRole + 1);
        item->setDragEnabled(true);
        item->setData(QString::number(idTodo).toUtf8(), Qt::UserRole + 2);

        if (status == "Pending") {
            pendingModel->appendRow(item);
        } else if (status == "Doing") {
            doingModel->appendRow(item);
        } else if (status == "Done") {
            doneModel->appendRow(item);
        }
    }
}

void CoachWindow::updateTodoList()
{
    loadTodoList();
}

void CoachWindow::on_aboutButton_clicked()
{
    qDebug() << "About button clicked.";
    About *aboutDialog = new About(this);
    aboutDialog->exec();
    delete aboutDialog;
}

int CoachWindow::getCoachTeamId()
{
    const Employee& currentUser = SessionManager::instance().getCurrentUser();
    int coachId = currentUser.getId();
    QSqlQuery query;
    query.prepare("SELECT ID_TEAM FROM coach WHERE id_emp = :coachId");
    query.bindValue(":coachId", coachId);
    if (query.exec() && query.next()) {
        return query.value("ID_TEAM").toInt();
    }
    return -1;
}

void CoachWindow::on_viewplayer_clicked()
{
    qDebug() << "ViewButton clicked, opening displayplayers_coach...";
    displayplayers_coach *displayPlayersWindow = new displayplayers_coach(this);
    displayPlayersWindow->setAttribute(Qt::WA_DeleteOnClose);
    displayPlayersWindow->show();
}

void CoachWindow::on_MatchesButton_clicked()
{
    qDebug() << "Match button clicked, opening displaymatch_coach...";
    displaymatch_coach *displayMatchWindow = new displaymatch_coach(this);
    displayMatchWindow->setAttribute(Qt::WA_DeleteOnClose);
    displayMatchWindow->show();
}

void CoachWindow::on_add_todo_clicked()
{
    AddTodoDialog dialog(this);
    if (dialog.exec() == QDialog::Accepted) {
        QString task = dialog.getTask();
        QDateTime date = dialog.getDate();
        if (task.isEmpty()) {
            QMessageBox::warning(this, "Input Error", "Task description cannot be empty.");
            return;
        }

        int teamId = getCoachTeamId();
        if (teamId == -1) {
            QMessageBox::critical(this, "Error", "No team found for the coach.");
            return;
        }

        QSqlQuery query;
        query.prepare("INSERT INTO HOTSTUFF.TODO (IDTEAM, TODO, STATS, DATETODO) "
                      "VALUES (:idteam, :todo, :stats, :datetodo)");
        query.bindValue(":idteam", teamId);
        query.bindValue(":todo", task);
        query.bindValue(":stats", "Pending");
        query.bindValue(":datetodo", date);

        if (!query.exec()) {
            qDebug() << "Failed to add task:" << query.lastError().text();
            QMessageBox::critical(this, "Database Error", "Failed to add task: " + query.lastError().text());
            return;
        }

        updateTodoList();
    }
}

void CoachWindow::on_delete_todo_clicked()
{
    QModelIndex currentIndex = pendingListView->currentIndex();
    TodoListView *selectedListView = pendingListView;
    if (!currentIndex.isValid()) {
        currentIndex = doingListView->currentIndex();
        selectedListView = doingListView;
    }
    if (!currentIndex.isValid()) {
        currentIndex = doneListView->currentIndex();
        selectedListView = doneListView;
    }

    if (!currentIndex.isValid()) {
        QMessageBox::warning(this, "Selection Error", "Please select a task to delete.");
        return;
    }

    int idTodo = currentIndex.data(Qt::UserRole).toInt();
    QSqlQuery query;
    query.prepare("DELETE FROM HOTSTUFF.TODO WHERE IDTODO = :idtodo");
    query.bindValue(":idtodo", idTodo);

    if (!query.exec()) {
        qDebug() << "Failed to delete task:" << query.lastError().text();
        QMessageBox::critical(this, "Database Error", "Failed to delete task: " + query.lastError().text());
        return;
    }

    updateTodoList();
}

void CoachWindow::on_todoItemClicked(const QModelIndex &index)
{
    if (!index.isValid()) return;

    int idTodo = index.data(Qt::UserRole).toInt();
    QString currentStatus = index.data(Qt::UserRole + 1).toString();
    QString newStatus;

    if (currentStatus == "Pending") {
        newStatus = "Doing";
    } else if (currentStatus == "Doing") {
        newStatus = "Done";
    } else {
        newStatus = "Pending";
    }

    QSqlQuery query;
    query.prepare("UPDATE HOTSTUFF.TODO SET STATS = :stats WHERE IDTODO = :idtodo");
    query.bindValue(":stats", newStatus);
    query.bindValue(":idtodo", idTodo);

    if (!query.exec()) {
        qDebug() << "Failed to update task status:" << query.lastError().text();
        QMessageBox::critical(this, "Database Error", "Failed to update task status: " + query.lastError().text());
        return;
    }

    updateTodoList();
}

void CoachWindow::logout()
{
    qDebug() << "Logout button clicked.";
    SessionManager::instance().clearSession();
    ui->currentUserPhotoLabel->setText("No User");
    ui->dashboard_9->setText("User name");
    ui->dashboard_8->setText("Role");

    MainWindow *loginWindow = new MainWindow();
    loginWindow->showMaximized();
    this->close();
}