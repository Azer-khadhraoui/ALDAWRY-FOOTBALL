#include "mainwindow.h"
#include "./ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow),
    mainwindow_id(-1)
{
    ui->setupUi(this);
    Connection conn;
    bool test = conn.createconnect();
    
}



MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_3_clicked()
{
    AddCompetitionWindow a;
    if (a.exec() == QDialog::Accepted) {
    }
   
}




void MainWindow::on_pushButton_4_clicked()
{
    statistics s;
    if (s.exec() == QDialog::Accepted) {
    }
    
}






void MainWindow::on_pushButton_6_clicked()
{
    TableauDialog t;
    if (t.exec() == QDialog::Accepted) {
    }
}

