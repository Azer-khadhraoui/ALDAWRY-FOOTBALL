#ifndef DISPLAYMATCH_COACH_H
#define DISPLAYMATCH_COACH_H

#include <QWidget>

namespace Ui {
class displaymatch_coach;
}

class displaymatch_coach : public QWidget
{
    Q_OBJECT

public:
    explicit displaymatch_coach(QWidget *parent = nullptr);
    ~displaymatch_coach();

private:
    Ui::displaymatch_coach *ui;
};

#endif // DISPLAYMATCH_COACH_H
