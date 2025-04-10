#ifndef STATSWIDGET_H
#define STATSWIDGET_H

#include <QWidget>
#include <QPainter>

class UserWindow; // forward declare

class statsWidget : public QWidget {
public:
    explicit statsWidget(UserWindow *parent = nullptr);
protected:
    void paintEvent(QPaintEvent *event) override;
private:
    UserWindow *userWindow;
};

#endif // STATSWIDGET_H
