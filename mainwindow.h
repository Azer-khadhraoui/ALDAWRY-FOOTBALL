#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QByteArray>
#include <QTableWidgetItem>
#include "team.h"
#include "modifyTeam.h"
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QMediaPlayer>
#include <QVideoWidget>
#include "chatdialog.h"
#include "tododialog.h"
#include <QListView>
#include <QAbstractListModel>
#include <QStyledItemDelegate>
#include <QPainter>
#include <QDateTime>

// Struct to hold To-Do item data
struct ToDoItem {
    int idTodo;
    int idTeam;
    QString teamName;
    QString todo;
    QString status;
    QDateTime dateTodo;
};

// Custom model for To-Do items
class ToDoModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit ToDoModel(QObject *parent = nullptr) : QAbstractListModel(parent) {}

    int rowCount(const QModelIndex &parent = QModelIndex()) const override {
        return parent.isValid() ? 0 : items.size();
    }

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override {
        if (!index.isValid() || index.row() >= items.size()) return QVariant();
        const ToDoItem &item = items[index.row()];
        if (role == Qt::DisplayRole || role == Qt::EditRole) {
            return QVariant::fromValue(item);
        }
        return QVariant();
    }

    void setItems(const QList<ToDoItem> &newItems) {
        beginResetModel();
        items = newItems;
        endResetModel();
    }

private:
    QList<ToDoItem> items;
};

// Custom delegate for rendering To-Do items
class ToDoDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit ToDoDelegate(QObject *parent = nullptr) : QStyledItemDelegate(parent) {}

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override {
        if (!index.isValid()) return;

        ToDoItem item = index.data(Qt::DisplayRole).value<ToDoItem>();

        painter->save();
        QRect rect = option.rect;
        QRect contentRect = rect.adjusted(10, 5, -10, -5);

        // Background and hover effect
        if (option.state & QStyle::State_Selected) {
            painter->fillRect(rect, QColor("#34C759"));
        } else if (option.state & QStyle::State_MouseOver) {
            painter->fillRect(rect, QColor("#2D3748"));
        } else {
            painter->fillRect(rect, QColor("#1A2526"));
        }

        // Draw border
        painter->setPen(QPen(QColor("#2D3748"), 1));
        painter->drawRect(rect.adjusted(0, 0, -1, -1));

        // Status indicator
        QRect statusRect(contentRect.left(), contentRect.top(), 20, 20);
        if (item.status.toLower() == "pending") {
            painter->setBrush(QColor("#FFA500")); // Orange for Pending
        } else if (item.status.toLower() == "completed") {
            painter->setBrush(QColor("#34C759")); // Green for Completed
        } else {
            painter->setBrush(QColor("#808080")); // Gray for others
        }
        painter->drawEllipse(statusRect);

        // Text layout
        int textX = contentRect.left() + 30;
        int textY = contentRect.top();
        QFont titleFont("Montserrat", 12, QFont::Bold);
        QFont detailFont("Montserrat", 10);

        painter->setPen(QColor("#E0E0E0"));

        // Team and To-Do
        painter->setFont(titleFont);
        QString teamTodoText = QString("%1: %2").arg(item.teamName).arg(item.todo);
        painter->drawText(textX, textY, teamTodoText);
        textY += 20;

        // Details
        painter->setFont(detailFont);
        QString idText = QString("ID: %1 | Team ID: %2").arg(item.idTodo).arg(item.idTeam);
        painter->drawText(textX, textY, idText);
        textY += 15;
        painter->drawText(textX, textY, QString("Status: %1 | Date: %2").arg(item.status).arg(item.dateTodo.toString("yyyy-MM-dd HH:mm:ss")));

        painter->restore();
    }

    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override {
        return QSize(option.rect.width(), 70); // Fixed height for each item
    }
};

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_toolButton_clicked();
    void on_resetButton_clicked();
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_5_clicked();
    void on_pushButton_6_clicked();
    void on_pushButton_7_clicked();
    void on_pushButton_8_clicked(); // New slot for delete button
    void onPieSliceHovered(bool state);
    void refreshTodoList();

private:
    Ui::MainWindow *ui;
    QByteArray teamLogo;

    void setupBudgetPieChart();
    void updateBudgetPieChart();
    void populateTodoList();

    QPieSeries *budgetSeries;
    QChartView *chartView;

    QMediaPlayer *mediaPlayer;
    QVideoWidget *videoWidget;

    QListView *todoListView;
    ToDoModel *todoModel;
    ToDoDelegate *todoDelegate;
};

#endif // MAINWINDOW_H
