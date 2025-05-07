#ifndef COACH_H
#define COACH_H

#include <QMainWindow>
#include <QStandardItemModel>
#include <QSqlQuery>
#include "ui_coach.h"
#include "../todolistview.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class CoachWindow;
}
QT_END_NAMESPACE

class CoachWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit CoachWindow(QWidget *parent = nullptr);
    ~CoachWindow();

private slots:
    void on_viewplayer_clicked();
    void on_MatchesButton_clicked();
    void on_add_todo_clicked();
    void on_delete_todo_clicked();
    void on_todoItemClicked(const QModelIndex &index);
    void logout();
    void on_aboutButton_clicked();

private:
    void loadTodoList();
    void updateTodoList();
    int getCoachTeamId();

    Ui::CoachWindow *ui;
    QStandardItemModel *pendingModel;
    QStandardItemModel *doingModel;
    QStandardItemModel *doneModel;
    TodoListView *pendingListView;
    TodoListView *doingListView;
    TodoListView *doneListView;
};

#endif // COACH_H
