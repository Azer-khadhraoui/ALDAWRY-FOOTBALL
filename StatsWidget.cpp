#include "statswidget.h"
#include "userwindow.h"

statsWidget::statsWidget(UserWindow *parent)
    : QWidget(parent), userWindow(parent) {}

void statsWidget::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);
    QPainter painter(this);
    userWindow->drawStatistics(painter);
}
