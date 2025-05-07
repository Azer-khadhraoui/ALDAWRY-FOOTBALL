#ifndef ADDMATCH_H
#define ADDMATCH_H

#include <QDialog>
#include <QByteArray>
#include <QWidget>
#include "ui_addMatch.h"

namespace Ui {
class addMatch;
}

class addMatch : public QDialog{
    Q_OBJECT
public:
    explicit addMatch(QWidget *parent = nullptr);
    ~addMatch();
signals:
    void matchAdded();
private slots:
    void on_Confirm_clicked();
private:
    Ui::addMatch *ui;
    
};

#endif // ADDMATCH_H
