#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "addcompetitionwindow.h"
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlDatabase>
#include <QDebug>
#include <QMessageBox>
#include "deletewindow.h"
#include "connection.h"
#include "updateform.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Connection conn;
    bool test = conn.createconnect();
    ui->test->setModel(c.show_competitions());

    connect(ui->lineEdit, &QLineEdit::textChanged, this, &MainWindow::on_searchTextChanged);
    connect(ui->comboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), [=](int index) {
        if (index == 0) {
            ui->test->setModel(c.show_competitions());
        } else if (index == 1) {
            ui->test->setModel(c.show_competitions_by_date());
        } else if (index == 2) {
            ui->test->setModel(c.show_competitions_by_nb_teams());
        }
    });
    connect(ui->comboBox_2, QOverload<int>::of(&QComboBox::currentIndexChanged), [=](int index) {
        if (index == 0) {
            ui->test->setModel(c.show_competitions());
        } else if (index == 1) {
            ui->test->setModel(c.show_competitions_by_type("League"));
        } else if (index == 2) {
            ui->test->setModel(c.show_competitions_by_type("Tournament"));
        }
    });
}

void MainWindow::on_searchTextChanged(const QString &search)
{
    if (search.isEmpty()) {
        qDebug() << "Search field is empty.";
        ui->test->setModel(c.show_competitions());
    } else {
        qDebug() << "Search field is not empty.";
        ui->test->setModel(c.show_competitions_by_name(search));
    }
}

MainWindow::~MainWindow()
{
    delete ui;
    // No need to close the database here; it’s managed by Qt’s default connection
}



void MainWindow::on_pushButton_3_clicked()
{
    AddCompetitionWindow a;
    if (a.exec() == QDialog::Accepted) {
    }
    ui->test->setModel(c.show_competitions());
}

void MainWindow::on_pushButton_clicked()
{
    deletewindow d;
    if (d.exec() == QDialog::Accepted) {
    }
    ui->test->setModel(c.show_competitions());
}


void MainWindow::on_pushButton_2_clicked()
{
    updateform u;
    if (u.exec() == QDialog::Accepted) {
    }
    ui->test->setModel(c.show_competitions());
}

