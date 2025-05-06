#ifndef LINEUP_H
#define LINEUP_H

#include <QWidget>

namespace Ui {
class lineup;
}

class lineup : public QWidget
{
    Q_OBJECT

public:
    explicit lineup(QWidget *parent = nullptr);
    ~lineup();

private:
    Ui::lineup *ui;
};

#endif // LINEUP_H
