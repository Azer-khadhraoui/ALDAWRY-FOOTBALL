#include "../userheaders/lineup.h"
#include "ui_lineup.h"

lineup::lineup(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::lineup)
{
    ui->setupUi(this);
}

lineup::~lineup()
{
    delete ui;
}
