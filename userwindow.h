#ifndef USERWINDOW_H
#define USERWINDOW_H

#include <QMainWindow>
#include <QSortFilterProxyModel>
#include <QPainter>
#include <QMap>
#include "User.h"
#include "statswidget.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE



// 🔽 Now define UserWindow below
class UserWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit UserWindow(QWidget *parent = nullptr);
    ~UserWindow();
    void drawStatistics(QPainter &painter);


private slots:
    void on_button1_clicked();
    void on_pushButton_3_clicked();
    void on_tabWidget_currentChanged(int index);
    void on_pushButton_2_clicked();
    void on_searchButton_clicked();
    void on_pdfButton_clicked();
    void on_statButton_clicked();
    void populateModifyFields(const QModelIndex &index);


private:
    Ui::MainWindow *ui;
    int selectedEmployeeId = 0;
    QSortFilterProxyModel *proxyModel;
    statsWidget* statsView = nullptr; // ✅ Now this is valid

    void refreshEmployeeTable();
    void clearModifyFields();
    void showStatistics();
    void generateStatisticsPDF(const QString &filePath);

    bool validatePhoneNumber(const QString& mobileNumber);
    bool validateAge(const QDate& dob);

    QMap<QString, int> ageCategories;
    QMap<QString, int> roleCount;
    QMap<QString, QMap<QString, int>> roleByAge;
    int totalEmployees = 0;

    void paintEvent(QPaintEvent *event) override;  // Declare paintEvent
    void on_searchTextChanged(const QString &text); // New slot for dynamic search


    void collectStatistics();


    friend class StatsWidget;

};

#endif // USERWINDOW_H
