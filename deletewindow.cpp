#include "deletewindow.h"
#include "ui_deletewindow.h"
#include "competition.h"
#include <QMessageBox>
deletewindow::deletewindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::deletewindow)
{
    ui->setupUi(this);
}

deletewindow::~deletewindow()
{
    delete ui;
}

void deletewindow::on_deleteButton_clicked()
{
    int id = ui->lineEdit->text().toInt();
    competition c;
    competition existingCompetition = c.get_competition(id);
    if (!c.exist_competition(id)) {
        QMessageBox::warning(this, "Error", "Competition ID does not exist");
        return;
    }
    if(c.delete_competition(id)) {
        QMessageBox::information(this, "Success", "Competition deleted successfully");
    } else {
        QMessageBox::warning(this, "Error", "Failed to delete competition");
    }
    this->close();
}

