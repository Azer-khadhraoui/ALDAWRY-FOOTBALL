#ifndef TABLEAU_H
#define TABLEAU_H

#include <QDialog>
#include "ui_tableau.h" // Include the generated UI header

class Tableau : public QDialog
{
    Q_OBJECT

public:
    explicit Tableau(QWidget *parent = nullptr);
    ~Tableau();

    void loadTeams(); // Function to load teams into the table

private slots:
    void on_searchBar_textChanged(const QString &text); // Slot for search functionality
    void on_downloadButton_clicked();                  // Slot for downloading PDF
    void on_deleteButton_clicked();                    // Slot for deleting a team
    void on_modifyButton_clicked();                    // Slot for modifying a team
    void updateTeamInTable(const QString &teamName, const QString &homeStadium, int budget, const QString &teamABV);

private:
    Ui::Tableau *ui;
};

#endif // TABLEAU_H
