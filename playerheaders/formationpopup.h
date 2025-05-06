#ifndef FORMATIONPOPUP_H
#define FORMATIONPOPUP_H

#include <QDialog>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsEllipseItem>
#include <QGraphicsTextItem>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QSqlQuery>
#include <QComboBox>
#include <QMap>
#include <QPixmap>
#include <QPainter>
#include <QGraphicsDropShadowEffect>

class FormationPopup : public QDialog
{
    Q_OBJECT

public:
    explicit FormationPopup(const QString &competitionName, QWidget *parent = nullptr);
    ~FormationPopup();

    void loadFormation(const QString &formation);
    void setupUI();

private slots:
    void onFormationChanged(const QString &formation);

private:
    QString competitionName;
    QGraphicsScene *scene;
    QGraphicsView *view;
    QComboBox *formationCombo;
    QMap<QString, QList<QPointF>> formationPositions;
     void drawPitch();

    void createPlayerNode(const QPointF &pos, const QString &position, int playerId,
                          const QString &playerName, const QByteArray &imageData);
    QPixmap createPlayerAvatar(const QByteArray &imageData, const QString &initials);
    void clearFormation();
    void getBestPlayersForFormation(const QString &formation);
};

#endif // FORMATIONPOPUP_H
