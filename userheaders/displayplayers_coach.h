#ifndef DISPLAYPLAYERS_COACH_H
#define DISPLAYPLAYERS_COACH_H

#include <QMainWindow>
#include <QSqlQuery>
#include <QJsonObject>

namespace Ui {
class displayplayers_coach;
}

class displayplayers_coach : public QMainWindow
{
    Q_OBJECT

public:
    explicit displayplayers_coach(QWidget *parent = nullptr);
    ~displayplayers_coach();
    
private slots:
    void loadPlayers(); // Load players for the coach's team
    void on_comboBoxTri_currentIndexChanged(int index); // Handle sorting
    void on_tableWidget_itemSelectionChanged(); // Handle table selection
    void refreshPlayerDetails(); // Display selected player details
    void onSearchTextChanged(const QString &text); // Handle search text change
    void onGenerateReportClicked();
    void displayReport(const QString &reportText);

private:
    // Stub functions (to be implemented as needed)
    QPixmap generateQRCode(const QString &text);
    void exportPlayerToPDF(int playerId);
    QJsonObject collectPlayerData(int playerId);
    QString generateReport(const QJsonObject &data);
    bool validateTableSelection(); // Add this declaration

    Ui::displayplayers_coach *ui;
    int currentDisplayedPlayerId = -1; // Track selected player
};

#endif // DISPLAYPLAYERS_COACH_H