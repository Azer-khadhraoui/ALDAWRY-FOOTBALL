#include "../teamheaders/teamwindow.h"
#include "ui_teamwindow.h"
#include "../teamheaders/team.h"
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
#include "../teamheaders/formadd.h"
#include "../teamheaders/chatdialog.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSpacerItem>
#include "../teamheaders/tableau.h"
#include "../teamheaders/tododialog.h"
#include "../userheaders/sessionmanager.h"
#include "../userheaders/mainwindow.h"
#include "../userheaders/admin.h"
#include "../playerheaders/playerwindow.h"
#include "../compheaders/competitionview.h"
#include <QstackedWidget>

teamwindow::teamwindow(QStackedWidget *stackedWidget, QWidget *parent)
    : QWidget(parent), ui(new Ui::teamwindow)
{
    ui->setupUi(this);

    this->setMinimumSize(1000, 700);

    if (!QSqlDatabase::database().isOpen()) {
        qDebug() << "Database connection failed to open in teamwindow!";
        QMessageBox::critical(this, "Error", "Database connection is not open!");
    }

    setupBudgetPieChart();

    // Initialize the QListView with custom model and delegate
    todoListView = ui->listView; // Assuming added via Qt Designer
    todoModel = new ToDoModel(this);
    todoDelegate = new ToDoDelegate(this);
    todoListView->setModel(todoModel);
    todoListView->setItemDelegate(todoDelegate);
    todoListView->setStyleSheet(
        "QListView {"
        "    background-color: #1A2526;"
        "    border: 2px solid #2D3748;"
        "    border-radius: 10px;"
        "    padding: 5px;"
        "}"
        "QListView::item {"
        "    border-bottom: 1px solid #2D3748;"
        "}"
        "QListView::item:selected {"
        "    background-color: #34C759;"
        "}"
        );
    todoListView->setSpacing(2); // Space between items
    todoListView->setSelectionMode(QAbstractItemView::SingleSelection);
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

    connect(ui->logout, &QPushButton::clicked, this, &teamwindow::handleLogoutButtonClicked);
    connect(ui->userbutton, &QPushButton::clicked, this, &teamwindow::on_userbutton_cliceked);
    connect(ui->playerButton, &QPushButton::clicked, this, &teamwindow::on_playerButton_clicked);
    connect(ui->compButton, &QPushButton::clicked, this, &teamwindow::on_compButton_clicked);
    connect(ui->matchButton, &QPushButton::clicked, this, &teamwindow::on_matchButton_clicked);
    
      
    
    // Populate the list initially
    populateTodoList();
}
void teamwindow::on_compButton_clicked()
{
    QStackedWidget *stackedWidget = qobject_cast<QStackedWidget*>(parentWidget());
        if (stackedWidget) {
            // Replace 2 with the correct index for your competition window if needed
            stackedWidget->setCurrentIndex(3);
        }
}

teamwindow::~teamwindow()
{
    delete ui;
}
void teamwindow::on_matchButton_clicked()
{
    QStackedWidget *stackedWidget = qobject_cast<QStackedWidget*>(parentWidget());
        if (stackedWidget) {
            stackedWidget->setCurrentIndex(4);
        }
}

void teamwindow::setupBudgetPieChart()
{
    budgetSeries = new QPieSeries();
    budgetSeries->setHoleSize(0.40);

    QSqlQuery query("SELECT BUDG FROM HOTSTUFF.EQUIPE");
    int lowBudgetCount = 0;
    int midBudgetCount = 0;
    int highBudgetCount = 0;
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
        connect(lowSlice, &QPieSlice::hovered, this, &teamwindow::onPieSliceHovered);

        double midPercentage = (midBudgetCount * 100.0) / totalTeams;
        QPieSlice *midSlice = budgetSeries->append("Mid Budget", midBudgetCount);
        midSlice->setColor(colors[1]);
        midSlice->setLabel(QString("Mid Budget\n%1%").arg(midPercentage, 0, 'f', 1));
        connect(midSlice, &QPieSlice::hovered, this, &teamwindow::onPieSliceHovered);

        double highPercentage = (highBudgetCount * 100.0) / totalTeams;
        QPieSlice *highSlice = budgetSeries->append("High Budget", highBudgetCount);
        highSlice->setColor(colors[2]);
        highSlice->setLabel(QString("High Budget\n%1%").arg(highPercentage, 0, 'f', 1));
        connect(highSlice, &QPieSlice::hovered, this, &teamwindow::onPieSliceHovered);
    }

    for (QPieSlice *slice : budgetSeries->slices()) {
        slice->setLabelVisible(true);
        slice->setLabelPosition(QPieSlice::LabelOutside);
        slice->setLabelColor(QColor("#E0E0E0"));
        slice->setBorderColor(QColor("#2D3748"));
        slice->setBorderWidth(2);
    }

    QChart *chart = new QChart();
    chart->addSeries(budgetSeries);
    chart->setTitle("Team Budget Intervals");
    chart->setTitleBrush(QBrush(QColor("#34C759")));
    chart->setTitleFont(QFont("Montserrat", 16, QFont::Bold));
    chart->setBackgroundBrush(QBrush(QColor("#1A2526")));
    chart->setPlotAreaBackgroundBrush(QBrush(QColor("#1A2526")));
    chart->setPlotAreaBackgroundVisible(true);
    chart->setTheme(QChart::ChartThemeDark);
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignRight);
    chart->legend()->setLabelColor(QColor("#E0E0E0"));
    chart->legend()->setFont(QFont("Montserrat", 12));
    chart->setAnimationOptions(QChart::SeriesAnimations);

    chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setFixedSize(600, 450);
    chartView->setStyleSheet("background-color: #1A2526; border: 2px solid #2D3748; border-radius: 15px;");

    QVBoxLayout *mainLayout = new QVBoxLayout(ui->widget_2);
    QHBoxLayout *chartLayout = new QHBoxLayout();
    chartLayout->addStretch(5);
    chartLayout->addWidget(chartView);
    chartLayout->addStretch(1);

    mainLayout->addSpacing(280);
    mainLayout->addLayout(chartLayout);
    mainLayout->setContentsMargins(10, 0, 10, 10);
    mainLayout->setSpacing(5);
    ui->widget_2->setLayout(mainLayout);
}

void teamwindow::updateBudgetPieChart()
{
    if (!budgetSeries) return;

    budgetSeries->clear();

    QSqlQuery query("SELECT BUDG FROM HOTSTUFF.EQUIPE");
    int lowBudgetCount = 0;
    int midBudgetCount = 0;
    int highBudgetCount = 0;
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

void teamwindow::onPieSliceHovered(bool state)
{
    QPieSlice *slice = qobject_cast<QPieSlice *>(sender());
    if (slice) {
        if (state) {
            slice->setExploded(true);
            slice->setExplodeDistanceFactor(0.15);
            slice->setLabelFont(QFont("Montserrat", 14, QFont::Bold));
            slice->setColor(slice->color().lighter(120));
        } else {
            slice->setExploded(false);
            slice->setExplodeDistanceFactor(0.0);
            slice->setLabelFont(QFont("Montserrat", 12));
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

void teamwindow::populateTodoList()
{
    QList<ToDoItem> todoItems;
    QSqlQuery query("SELECT t.IDTODO, t.IDTEAM, e.TEAM_NAME, t.TODO, t.STATS, t.DATETODO "
                    "FROM HOTSTUFF.TODO t "
                    "JOIN HOTSTUFF.EQUIPE e ON t.IDTEAM = e.ID_TEAM "
                    "ORDER BY t.DATETODO DESC");

    while (query.next()) {
        ToDoItem item;
        item.idTodo = query.value(0).toInt();
        item.idTeam = query.value(1).toInt();
        item.teamName = query.value(2).toString();
        item.todo = query.value(3).toString();
        item.status = query.value(4).toString();
        item.dateTodo = query.value(5).toDateTime();
        todoItems << item;
    }

    todoModel->setItems(todoItems);
}

void teamwindow::refreshTodoList()
{
    populateTodoList();
}

void teamwindow::on_userbutton_cliceked()
{
    QStackedWidget *stackedWidget = qobject_cast<QStackedWidget*>(parentWidget());
    if (stackedWidget) {
        // Assuming the player window is at index 2 in the stacked widget
        stackedWidget->setCurrentIndex(0);
    }
}

void teamwindow::on_pushButton_2_clicked()
{
    FormAdd *formAdd = new FormAdd(this);
    connect(formAdd, &FormAdd::teamAdded, this, [=]() {
        updateBudgetPieChart();
    });
    formAdd->show();
}

void teamwindow::on_pushButton_3_clicked()
{
    ChatDialog *chatDialog = new ChatDialog(this);
    chatDialog->setModal(false);
    chatDialog->show();
}

void teamwindow::on_pushButton_4_clicked()
{
    Tableau *tableau = new Tableau(this);
    tableau->exec();
}

void teamwindow::on_pushButton_5_clicked()
{
    Tableau *tableau = new Tableau(this);
    tableau->exec();
}

void teamwindow::on_pushButton_6_clicked()
{
    Tableau *tableau = new Tableau(this);
    tableau->exec();
}

void teamwindow::on_pushButton_7_clicked()
{
    TodoDialog *todoDialog = new TodoDialog(this);
    connect(todoDialog, &TodoDialog::todoAdded, this, &teamwindow::refreshTodoList);
    todoDialog->exec();
}

void teamwindow::on_pushButton_8_clicked()
{
    // Get the selected item
    QModelIndexList selectedIndexes = todoListView->selectionModel()->selectedIndexes();
    if (selectedIndexes.isEmpty()) {
        QMessageBox::warning(this, "No Selection", "Please select a to-do item to delete.");
        return;
    }

    // Since single selection is enabled, there should be only one selected index
    QModelIndex index = selectedIndexes.first();
    ToDoItem item = index.data(Qt::DisplayRole).value<ToDoItem>();

    // Confirm deletion
    QMessageBox::StandardButton reply = QMessageBox::question(
        this,
        "Confirm Deletion",
        QString("Are you sure you want to delete the to-do item '%1' for team '%2'?").arg(item.todo).arg(item.teamName),
        QMessageBox::Yes | QMessageBox::No
        );

    if (reply == QMessageBox::Yes) {
        // Delete from the database
        QSqlQuery query;
        query.prepare("DELETE FROM HOTSTUFF.TODO WHERE IDTODO = :idtodo");
        query.bindValue(":idtodo", item.idTodo);

        if (query.exec()) {
            QMessageBox::information(this, "Success", "To-do item deleted successfully!");
            refreshTodoList(); // Refresh the list after deletion
        } else {
            QMessageBox::critical(this, "Error", "Failed to delete to-do item: " + query.lastError().text());
            qDebug() << "SQL Error:" << query.lastError().text();
        }
    }
}

void teamwindow::on_toolButton_clicked()
{
    FormAdd *formAdd = new FormAdd(this);
    formAdd->exec();
}

void teamwindow::on_resetButton_clicked()
{
    updateBudgetPieChart();
}

void teamwindow::handleLogoutButtonClicked()
{
    qDebug() << "Logout button clicked.";
    // Clear the session to log out the user
    SessionManager::instance().clearSession();

    // Update the photo label to indicate no user
    ui->currentUserPhotoLabel->setText("No User");
    ui->dashboard_9->setText("User name"); // Reset username label
    ui->dashboard_8->setText("Role");      // Reset role label

    // Try to get the parent MainWindow
    QWidget *parent = parentWidget();
    MainWindow *mainWindow = qobject_cast<MainWindow*>(parent);
    if (mainWindow) {
        // Clear the email and password fields in MainWindow
        QLineEdit *emailField = mainWindow->findChild<QLineEdit*>("lineEdit");
        QLineEdit *passwordField = mainWindow->findChild<QLineEdit*>("lineEdit_2");
        if (emailField && passwordField) {
            emailField->clear();
            passwordField->clear();
        } else {
            qDebug() << "Failed to find email or password fields in MainWindow.";
        }
        mainWindow->show();
    } else {
        // Fallback: Create a new MainWindow
        qDebug() << "No parent MainWindow found, creating a new one.";
        MainWindow *loginWindow = new MainWindow();
        loginWindow->show();
    }

    // Close all parent windows up the chain (including stacked widgets)
    QWidget *w = this;
    while (w) {
        QWidget *parent = w->parentWidget();
        w->close();
        w = parent;
    }
}

void teamwindow::on_playerButton_clicked() {
    QStackedWidget *stackedWidget = qobject_cast<QStackedWidget*>(parentWidget());
    if (stackedWidget) {
            // Replace 2 with the correct index for your competition window if needed
            stackedWidget->setCurrentIndex(2);
    }
}
