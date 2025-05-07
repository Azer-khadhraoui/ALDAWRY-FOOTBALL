#ifndef VIEWMATCH_H
#define VIEWMATCH_H

#include <QDialog>
#include <QByteArray>

namespace Ui {
class viewMatch;
}

class viewMatch : public QDialog
{
    Q_OBJECT
public:
    explicit viewMatch(QWidget *parent = nullptr);
    ~viewMatch();
private slots:
    void viewmatchlist();
    void on_search_textChanged(const QString &text);
    void on_headers_Clicked(int logicalIndex);
    void on_allmatchesContextMenuRequested(const QPoint &pos);
    void on_showFullLineupTriggered();
private:
    Ui::viewMatch *ui;
    bool ascendingOrder; // Variable to track the sorting order
};

#endif // VIEWMATCH_H
