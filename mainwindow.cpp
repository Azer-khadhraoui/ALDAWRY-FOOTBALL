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
#include "formadd.h"
#include "chatdialog.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSpacerItem>
#include "tableau.h"
#include "tododialog.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setMinimumSize(1000, 700);

    if (!QSqlDatabase::database().isOpen()) {
        qDebug() << "Database connection failed to open in MainWindow!";
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

    // Populate the list initially
    populateTodoList();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupBudgetPieChart()
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
        connect(lowSlice, &QPieSlice::hovered, this, &MainWindow::onPieSliceHovered);

        double midPercentage = (midBudgetCount * 100.0) / totalTeams;
        QPieSlice *midSlice = budgetSeries->append("Mid Budget", midBudgetCount);
        midSlice->setColor(colors[1]);
        midSlice->setLabel(QString("Mid Budget\n%1%").arg(midPercentage, 0, 'f', 1));
        connect(midSlice, &QPieSlice::hovered, this, &MainWindow::onPieSliceHovered);

        double highPercentage = (highBudgetCount * 100.0) / totalTeams;
        QPieSlice *highSlice = budgetSeries->append("High Budget", highBudgetCount);
        highSlice->setColor(colors[2]);
        highSlice->setLabel(QString("High Budget\n%1%").arg(highPercentage, 0, 'f', 1));
        connect(highSlice, &QPieSlice::hovered, this, &MainWindow::onPieSliceHovered);
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

void MainWindow::updateBudgetPieChart()
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

void MainWindow::onPieSliceHovered(bool state)
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

void MainWindow::populateTodoList()
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

void MainWindow::refreshTodoList()
{
    populateTodoList();
}

void MainWindow::on_pushButton_clicked()
{
    ChatDialog *chatDialog = new ChatDialog(this);
    chatDialog->setModal(false);
    chatDialog->show();
}

void MainWindow::on_pushButton_2_clicked()
{
    FormAdd *formAdd = new FormAdd(this);
    connect(formAdd, &FormAdd::teamAdded, this, [=]() {
        updateBudgetPieChart();
    });
    formAdd->show();
}

void MainWindow::on_pushButton_3_clicked()
{
    ChatDialog *chatDialog = new ChatDialog(this);
    chatDialog->setModal(false);
    chatDialog->show();
}

void MainWindow::on_pushButton_4_clicked()
{
    Tableau *tableau = new Tableau(this);
    tableau->exec();
}

void MainWindow::on_pushButton_5_clicked()
{
    Tableau *tableau = new Tableau(this);
    tableau->exec();
}

void MainWindow::on_pushButton_6_clicked()
{
    Tableau *tableau = new Tableau(this);
    tableau->exec();
}

void MainWindow::on_pushButton_7_clicked()
{
    TodoDialog *todoDialog = new TodoDialog(this);
    connect(todoDialog, &TodoDialog::todoAdded, this, &MainWindow::refreshTodoList);
    todoDialog->exec();
}

void MainWindow::on_pushButton_8_clicked()
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

void MainWindow::on_toolButton_clicked()
{
    FormAdd *formAdd = new FormAdd(this);
    formAdd->exec();
}

void MainWindow::on_resetButton_clicked()
{
    updateBudgetPieChart();
}
