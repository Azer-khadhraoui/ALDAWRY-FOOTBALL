#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "addcompetitionwindow.h"
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlDatabase>
#include <QDebug>
#include <QMessageBox>
#include "deletewindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableView->setModel(c.show_competitions());
    // Populate table view using the connection from main.cpp
    updateTableView();
}

MainWindow::~MainWindow()
{
    delete ui;
    // No need to close the database here; it’s managed by Qt’s default connection
}

void MainWindow::updateTableView()
{
    QSqlQueryModel *model = c.show_competitions();
    if (!model) {
        qDebug() << "Failed to retrieve competitions model";
        return;
    }




    ui->tableView->setModel(model);
    ui->tableView->resizeColumnsToContents();
    qDebug() << "Table view updated";
}

void MainWindow::on_pushButton_3_clicked()
{
    AddCompetitionWindow a;
    if (a.exec() == QDialog::Accepted) {
        updateTableView(); // Refresh table after adding
    }
}

void MainWindow::on_pushButton_clicked()
{
    deletewindow d;
    if (d.exec() == QDialog::Accepted) {
        updateTableView(); // Refresh table after deleting
    }
}

