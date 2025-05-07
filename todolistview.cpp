#include "todolistview.h"
#include <QStandardItemModel>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QMimeData>

TodoListView::TodoListView(QWidget *parent) : QListView(parent) {
    setDragEnabled(true);
    setAcceptDrops(true);
    setDropIndicatorShown(true);
    setDefaultDropAction(Qt::MoveAction);
    setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setStyleSheet(R"(
        QListView {
            background-color: #1F2633;
            border: 1px solid #4A4E58;
            border-radius: 8px;
            padding: 10px;
            margin: 5px;
        }
        QListView::item {
            background-color: #2A3244;
            border: 1px solid #4A4E58;
            border-radius: 6px;
            padding: 12px;
            margin: 8px 5px;
            color: #FFFFFF;
            font: 12pt "Segoe UI";
        }
        QListView::item:hover {
            background-color: #3A4659;
            border: 1px solid #F5A623;
        }
        QListView::item:selected {
            background-color: #D8A353;
            color: #1A2633;
        }
        QScrollBar:vertical {
            border: none;
            background: #2A3244;
            width: 8px;
            margin: 0px;
            border-radius: 4px;
        }
        QScrollBar::handle:vertical {
            background: #F5A623;
            border-radius: 4px;
        }
        QScrollBar::add-line:vertical, QScrollBar::sub-line:vertical {
            background: none;
        }
        QScrollBar::add-page:vertical, QScrollBar::sub-page:vertical {
            background: none;
        }
    )");
}

void TodoListView::dragEnterEvent(QDragEnterEvent *event) {
    if (event->mimeData()->hasFormat("application/x-idtodo")) {
        event->acceptProposedAction();
    } else {
        event->ignore();
    }
}

void TodoListView::dragMoveEvent(QDragMoveEvent *event) {
    if (event->mimeData()->hasFormat("application/x-idtodo")) {
        event->acceptProposedAction();
    } else {
        event->ignore();
    }
}

void TodoListView::dropEvent(QDropEvent *event) {
    if (!event->mimeData()->hasFormat("application/x-idtodo")) {
        qDebug() << "Drop ignored: Invalid mime data format";
        event->ignore();
        return;
    }

    QByteArray idData = event->mimeData()->data("application/x-idtodo");
    if (idData.isEmpty()) {
        qDebug() << "Drop ignored: Empty IDTODO data";
        event->ignore();
        return;
    }
    int idTodo = idData.toInt();

    QString newStatus = property("status").toString();
    if (newStatus.isEmpty() || !QStringList({"Pending", "Doing", "Done"}).contains(newStatus)) {
        qDebug() << "Drop ignored: Invalid status" << newStatus;
        event->ignore();
        return;
    }

    QSqlQuery query;
    query.prepare("UPDATE HOTSTUFF.TODO SET STATS = :stats WHERE IDTODO = :idtodo");
    query.bindValue(":stats", newStatus);
    query.bindValue(":idtodo", idTodo);
    if (!query.exec()) {
        qDebug() << "Failed to update task status on drop:" << query.lastError().text();
        event->ignore();
        return;
    }

    event->acceptProposedAction();
    emit model()->dataChanged(QModelIndex(), QModelIndex());
}
