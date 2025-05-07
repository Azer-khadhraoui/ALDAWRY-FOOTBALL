#ifndef TODOLISTVIEW_H
#define TODOLISTVIEW_H

#include <QListView>
#include <QDragEnterEvent>
#include <QDropEvent>

class TodoListView : public QListView {
    Q_OBJECT
public:
    explicit TodoListView(QWidget *parent = nullptr);

protected:
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dragMoveEvent(QDragMoveEvent *event) override;
    void dropEvent(QDropEvent *event) override;
};

#endif // TODOLISTVIEW_H
