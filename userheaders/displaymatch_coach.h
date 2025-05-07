#ifndef DISPLAYMATCH_COACH_H
#define DISPLAYMATCH_COACH_H

#include <QDialog>
#include <QByteArray>
#include <QComboBox>


namespace Ui {
class displaymatch_coach;
}

class displaymatch_coach : public QDialog
{
    Q_OBJECT

public:
    explicit displaymatch_coach(QWidget *parent = nullptr);
    ~displaymatch_coach();
private slots:
    void loadcoachmatches(int idteam);
    void loadCurrentCoachMatches();
    void on_headers_Clicked_coach(int logicalIndex);
    void on_search_textChanged_coach(const QString &text);
    void on_menurequest(const QPoint &pos);
    void on_setLineupTriggered();
    void setupLineupWidget(int matchId, int teamId, const QString& lineup);
    void updateAvailablePlayers();

private:
    Ui::displaymatch_coach *ui;
    bool updating = false; // Moved to class scope
    QVector<QPair<QComboBox*, QString>> positionBoxes; // Store the dynamic comboboxes and their positions
    bool ascendingOrder; // Variable to track the sorting order
    QList<std::tuple<int, QString, int>> allGoalkeepers; // id, name, status
    QList<std::tuple<int, QString, int>> allDefenders;
    QList<std::tuple<int, QString, int>> allMidfielders;
    QList<std::tuple<int, QString, int>> allForwards;
};

#endif // DISPLAYMATCH_COACH_H
