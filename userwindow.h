#ifndef USERWINDOW_H
#define USERWINDOW_H

#include <QMainWindow>
#include "User.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class UserWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit UserWindow(QWidget *parent = nullptr);
    ~UserWindow();

private slots:
    void on_button1_clicked();      // Add
    void on_pushButton_3_clicked(); // Delete
    void on_pushButton_4_clicked(); // Modify
    void on_tabWidget_currentChanged(int index); // Refresh display tab
    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;
    int selectedEmployeeId = 0;
    void populateModifyFields(const QModelIndex &index);
    void refreshEmployeeTable();
    void clearModifyFields();
    void on_searchButton_clicked(); // New slot for search

};

#endif // USERWINDOW_H
