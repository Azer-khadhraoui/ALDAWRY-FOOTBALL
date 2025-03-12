#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QByteArray>
#include <QTableWidgetItem>
#include "team.h"
#include "modifyTeam.h"  // Updated include

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_toolButton_clicked();
    void on_addButtonclicked();
    void on_deleteButton_clicked();
    void on_resetButton_clicked();
    void on_searchBar_textChanged(const QString &text);
    void on_tableWidget_sectionClicked(int logicalIndex);
    void on_modifyButton_clicked();
    void on_downloadButton_clicked();  // New slot declaration

private:
    Ui::MainWindow *ui;
    QByteArray teamLogo;

    void loadTeams();
};

#endif // MAINWINDOW_H
