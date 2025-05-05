#ifndef USERWINDOW_H
#define USERWINDOW_H

#include <QMainWindow>
#include <QSortFilterProxyModel>
#include "User.h"
#include "statswidget.h"
#include "mainwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class UserWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit UserWindow(MainWindow *parent = nullptr);
    ~UserWindow();

private slots:
    void on_button1_clicked();
    void on_pushButton_3_clicked();
    void on_tabWidget_currentChanged(int index);
    void on_pushButton_2_clicked();
    void on_searchButton_clicked();
    void on_pdfButton_clicked();
    void on_statButton_clicked();
    void populateModifyFields(const QModelIndex &index);
    void on_pushButton_clicked();
    void on_searchTextChanged(const QString &text);
    void on_uploadPhotoButton_clicked(); // New slot for photo upload
    void on_modifyUploadPhotoButton_clicked(); // New slot for modify photo upload

private:
    Ui::MainWindow *ui;
    int selectedEmployeeId = 0;
    QSortFilterProxyModel *proxyModel;
    statsWidget* statsView = nullptr;
    MainWindow *mainWindowParent;
    QByteArray selectedEmployeePhoto; // Store the photo temporarily
    QByteArray newEmployeePhoto; // Store photo for adding a new employee

    void refreshEmployeeTable();
    void clearModifyFields();
    bool validatePhoneNumber(const QString& mobileNumber);
    bool validateAge(const QDate& dob);
    void collectStatistics();

    QMap<QString, int> ageCategories;
    QMap<QString, int> roleCount;
    QMap<QString, QMap<QString, int>> roleByAge;
    int totalEmployees = 0;

    friend class statsWidget;
};

#endif // USERWINDOW_H
