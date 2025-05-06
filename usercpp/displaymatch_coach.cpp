#include "../userheaders/displaymatch_coach.h"
#include "ui_displaymatch_coach.h"

displaymatch_coach::displaymatch_coach(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::displaymatch_coach)
{
    ui->setupUi(this);
}

displaymatch_coach::~displaymatch_coach()
{
    delete ui;
}
