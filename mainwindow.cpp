#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "userwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_sign_in_clicked() {
    // Directly open UserWindow (which loads user.ui)
    UserWindow *userWindow = new UserWindow(this);
    userWindow->show();
    this->hide(); // Hide the sign-in window
}
