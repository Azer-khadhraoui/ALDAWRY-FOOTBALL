#ifndef DISPLAYMATCH_H
#define DISPLAYMATCH_H

#include <QDialog>
#include <QByteArray>
#include <Qwidget>


namespace Ui {
class displayMatch;
}

class displayMatch : public QDialog{
    Q_OBJECT
public:
    explicit displayMatch(QWidget *parent = nullptr);
    ~displayMatch();
    void setupMatchTable();
private slots:
    void on_Delete_clicked();
    void on_Modify_clicked();
    void filterMatches(const QString &text);
    void on_headerClicked(int logicalIndex);
    void on_pdf_clicked();
    void on_matchDoubleClicked(const QModelIndex &index);
private:
    Ui::displayMatch *ui;
    bool ascendingOrder;
};

#endif // DISPLAYMATCH_H
