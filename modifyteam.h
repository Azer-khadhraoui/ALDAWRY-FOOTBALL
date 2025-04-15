#ifndef MODIFYTEAM_H
#define MODIFYTEAM_H

#include <QDialog>
#include <QByteArray>
#include <QSqlQuery>

namespace Ui {
class modifyTeam;
}

class ModifyTeam : public QDialog
{
    Q_OBJECT

public:
    explicit ModifyTeam(QWidget *parent = nullptr);
    ~ModifyTeam();

    void setTeamData(const QString &teamName, const QString &homeStadium, int budget, const QString &teamABV, const QByteArray &teamLogo);

signals:
    void teamModified(const QString &teamName, const QString &homeStadium, int budget, const QString &teamABV);

private slots:
    void on_button1_2_clicked();
    void on_toolButton_2_clicked();
    void on_confirmButton_clicked();

private:
    Ui::modifyTeam *ui;
    QByteArray teamLogo;
    QString originalTeamName;  // Store the original team name

    bool updateTeamInDatabase();
};

#endif // MODIFYTEAM_H
