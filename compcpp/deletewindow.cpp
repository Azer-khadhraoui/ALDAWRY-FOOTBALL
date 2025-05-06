#include "../compheaders/deletewindow.h"
#include "ui_deletewindow.h"
#include "../compheaders/competition.h"
#include <QMessageBox>
deletewindow::deletewindow(QWidget *parent, int id):
    QDialog(parent), 
    ui(new Ui::deletewindow),
    m_id(id)
{
    ui->setupUi(this);
}

deletewindow::~deletewindow()
{
    delete ui;
}

void deletewindow::on_deleteButton_clicked()
{
    competition c;
    competition existingCompetition = c.get_competition(m_id);
    if (!c.exist_competition(m_id)) {
        QMessageBox::warning(this, "Error", "Competition ID does not exist");
        return;
    }
    if(c.delete_competition(m_id)) {
        QMessageBox::information(this, "Success", "Competition deleted successfully");
    } else {
        QMessageBox::warning(this, "Error", "Failed to delete competition");
    }
    this->close();
}


void deletewindow::on_pushButton_clicked()
{
    this->close();
}

