// displayuser.h
#ifndef DISPLAYUSER_H
#define DISPLAYUSER_H

#include <QDialog>
#include <QStandardItemModel>
#include <QList>
#include <QSortFilterProxyModel>
#include <QByteArray>
#include "ui_displayuser.h"
#include "user.h"

class DisplayUser : public QDialog {
    Q_OBJECT

public:
    explicit DisplayUser(const QString &role, QWidget *parent = nullptr);
    ~DisplayUser();

private slots:
    void on_pushButton_3_clicked();          // Delete button
    void on_pdfButton_clicked();             // Export to PDF button
    void on_ModifyUser_clicked();            // Modify button
    void on_searchTextChanged(const QString &text); // Dynamic search
    void on_tableRowClicked(const QModelIndex &index); // New slot for table row selection

private:
    void populateUserTable(const QString &role);
    void refreshUserTable();

    Ui::DisplayUser *ui;
    QStandardItemModel *model;
    QSortFilterProxyModel *proxyModel;
    int selectedUserId;
    QByteArray selectedUserPhoto;
};

#endif // DISPLAYUSER_H
