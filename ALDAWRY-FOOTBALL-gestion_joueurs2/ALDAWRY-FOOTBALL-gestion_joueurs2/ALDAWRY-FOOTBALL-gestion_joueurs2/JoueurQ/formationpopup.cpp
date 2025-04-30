#include "formationpopup.h"
#include <QDebug>
#include <QSqlError>
#include <QPainterPath>
#include <QApplication>

FormationPopup::FormationPopup(const QString &competitionName, QWidget *parent)
    : QDialog(parent), competitionName(competitionName)
{
    setWindowTitle("Formation - " + competitionName);
    setMinimumSize(800, 600);

    // Définir les coordonnées pour différentes formations
    // 4-3-3
    formationPositions["4-3-3"] = {
        QPointF(400, 500),  // GK
        QPointF(200, 400),  // LB
        QPointF(300, 400),  // CB
        QPointF(500, 400),  // CB
        QPointF(600, 400),  // RB
        QPointF(200, 250),  // LM
        QPointF(400, 250),  // CM
        QPointF(600, 250),  // RM
        QPointF(200, 100),  // LW
        QPointF(400, 100),  // ST
        QPointF(600, 100)   // RW
    };

    // 4-4-2
    formationPositions["4-4-2"] = {
        QPointF(400, 500),  // GK
        QPointF(200, 400),  // LB
        QPointF(300, 400),  // CB
        QPointF(500, 400),  // CB
        QPointF(600, 400),  // RB
        QPointF(150, 250),  // LM
        QPointF(300, 250),  // CM
        QPointF(500, 250),  // CM
        QPointF(650, 250),  // RM
        QPointF(300, 100),  // ST
        QPointF(500, 100)   // ST
    };

    // 3-5-2
    formationPositions["3-5-2"] = {
        QPointF(400, 500),  // GK
        QPointF(250, 400),  // CB
        QPointF(400, 400),  // CB
        QPointF(550, 400),  // CB
        QPointF(100, 300),  // LWB
        QPointF(250, 250),  // CM
        QPointF(400, 250),  // CM
        QPointF(550, 250),  // CM
        QPointF(700, 300),  // RWB
        QPointF(300, 100),  // ST
        QPointF(500, 100)   // ST
    };

    // 5-3-2
    formationPositions["5-3-2"] = {
        QPointF(400, 500),  // GK
        QPointF(100, 350),  // LWB
        QPointF(250, 400),  // CB
        QPointF(400, 400),  // CB
        QPointF(550, 400),  // CB
        QPointF(700, 350),  // RWB
        QPointF(250, 250),  // CM
        QPointF(400, 250),  // CM
        QPointF(550, 250),  // CM
        QPointF(300, 100),  // ST
        QPointF(500, 100)   // ST
    };

    setupUI();
}

FormationPopup::~FormationPopup()
{
}

void FormationPopup::setupUI()
{
    // Layout principal
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    // Titre
    QLabel *titleLabel = new QLabel("Team Formation - " + competitionName);
    titleLabel->setStyleSheet("font-size: 18px; font-weight: bold; color: #2c3e50; margin-bottom: 10px;");
    titleLabel->setAlignment(Qt::AlignCenter);

    // Contrôles en haut
    QHBoxLayout *controlsLayout = new QHBoxLayout();

    QLabel *formationLabel = new QLabel("Formation:");
    formationLabel->setStyleSheet("font-weight: bold;");

    formationCombo = new QComboBox();
    formationCombo->addItem("4-3-3");
    formationCombo->addItem("4-4-2");
    formationCombo->addItem("3-5-2");
    formationCombo->addItem("5-3-2");
    formationCombo->setStyleSheet(
        "QComboBox {"
        "   background-color: white;"
        "   border: 1px solid #bdc3c7;"
        "   border-radius: 3px;"
        "   padding: 5px;"
        "   min-width: 100px;"
        "}"
        );

    connect(formationCombo, &QComboBox::currentTextChanged, this, &FormationPopup::onFormationChanged);

    QPushButton *closeButton = new QPushButton("Close");
    closeButton->setStyleSheet(
        "QPushButton {"
        "   background-color: #e74c3c;"
        "   color: white;"
        "   border: none;"
        "   border-radius: 3px;"
        "   padding: 5px 15px;"
        "   font-weight: bold;"
        "}"
        "QPushButton:hover {"
        "   background-color: #c0392b;"
        "}"
        );

    connect(closeButton, &QPushButton::clicked, this, &QDialog::accept);

    controlsLayout->addWidget(formationLabel);
    controlsLayout->addWidget(formationCombo);
    controlsLayout->addStretch();
    controlsLayout->addWidget(closeButton);

    // Créer la scène et la vue
    scene = new QGraphicsScene(this);
    scene->setSceneRect(0, 0, 800, 600);

    view = new QGraphicsView(scene);
    view->setRenderHint(QPainter::Antialiasing);
    view->setBackgroundBrush(QBrush(QColor(0, 128, 0)));
    view->setMinimumHeight(500);

    // Ajouter les widgets au layout principal
    mainLayout->addWidget(titleLabel);
    mainLayout->addLayout(controlsLayout);
    mainLayout->addWidget(view, 1);

    // Charger la formation par défaut
    loadFormation(formationCombo->currentText());
}

void FormationPopup::onFormationChanged(const QString &formation)
{
    loadFormation(formation);
}

void FormationPopup::loadFormation(const QString &formation)
{
    clearFormation();

    // Dessiner le terrain
    drawPitch();

    // Obtenir les meilleurs joueurs pour cette formation
    getBestPlayersForFormation(formation);
}

void FormationPopup::drawPitch()
{
    QPen whitePen(Qt::white, 2);

    // Rectangle principal du terrain
    scene->addRect(50, 50, 700, 500, whitePen);

    // Cercle central
    scene->addEllipse(350, 250, 100, 100, whitePen);
    scene->addEllipse(395, 295, 10, 10, whitePen, QBrush(Qt::white));

    // Ligne médiane
    scene->addLine(50, 300, 750, 300, whitePen);

    // Surface de réparation (haute)
    scene->addRect(250, 50, 300, 100, whitePen);
    scene->addRect(300, 50, 200, 50, whitePen);
    scene->addEllipse(395, 120, 10, 10, whitePen, QBrush(Qt::white));

    // Surface de réparation (basse)
    scene->addRect(250, 450, 300, 100, whitePen);
    scene->addRect(300, 500, 200, 50, whitePen);
    scene->addEllipse(395, 470, 10, 10, whitePen, QBrush(Qt::white));

    // Points de corner
    scene->addEllipse(50, 50, 5, 5, whitePen, QBrush(Qt::white));
    scene->addEllipse(745, 50, 5, 5, whitePen, QBrush(Qt::white));
    scene->addEllipse(50, 545, 5, 5, whitePen, QBrush(Qt::white));
    scene->addEllipse(745, 545, 5, 5, whitePen, QBrush(Qt::white));
}

void FormationPopup::clearFormation()
{
    scene->clear();
}

void FormationPopup::getBestPlayersForFormation(const QString &formation)
{
    // Positions standard pour cette formation
    if (!formationPositions.contains(formation)) {
        qDebug() << "Formation non reconnue:" << formation;
        return;
    }

    QList<QPointF> positions = formationPositions[formation];
    QStringList positionLabels;

    // Déterminer les positions basées sur la formation
    if (formation == "4-3-3") {
        positionLabels = {"GK", "LB", "CB", "CB", "RB", "LM", "CM", "RM", "LW", "ST", "RW"};
    } else if (formation == "4-4-2") {
        positionLabels = {"GK", "LB", "CB", "CB", "RB", "LM", "CM", "CM", "RM", "ST", "ST"};
    } else if (formation == "3-5-2") {
        positionLabels = {"GK", "CB", "CB", "CB", "LWB", "CM", "CM", "CM", "RWB", "ST", "ST"};
    } else if (formation == "5-3-2") {
        positionLabels = {"GK", "LWB", "CB", "CB", "CB", "RWB", "CM", "CM", "CM", "ST", "ST"};
    }

    // Structure pour stocker les joueurs
    struct PlayerInfo {
        int id;
        QString firstName;
        QString lastName;
        QString position; // Position réelle du joueur
        QByteArray imageData;
        int score; // Score basé sur les buts et passes
    };

    // Récupérer tous les joueurs de la compétition
    QList<PlayerInfo> allPlayers;

    QSqlQuery query;
    query.prepare(
        "SELECT j.id_player, j.first_name, j.last_name, j.position, "
        "j.goals, j.assists, j.img_joueur "
        "FROM joueur j "
        "JOIN equipe e ON j.id_team = e.id_team "
        "JOIN participation p ON e.id_team = p.id_team "
        "JOIN competition c ON p.id_competition = c.id_competition "
        "WHERE c.comp_name = :competition_name "
        "ORDER BY (j.goals * 2 + j.assists) DESC"
        );
    query.bindValue(":competition_name", competitionName);

    if (!query.exec()) {
        qDebug() << "Erreur lors de la récupération des joueurs:" << query.lastError().text();
        return;
    }

    while (query.next()) {
        PlayerInfo player;
        player.id = query.value("id_player").toInt();
        player.firstName = query.value("first_name").toString();
        player.lastName = query.value("last_name").toString();
        player.position = query.value("position").toString();
        player.imageData = query.value("img_joueur").toByteArray();
        int goals = query.value("goals").toInt();
        int assists = query.value("assists").toInt();
        player.score = goals * 2 + assists;

        allPlayers.append(player);
    }

    // Correspondance des positions du jeu avec celles de la formation
    QMap<QString, QStringList> eligiblePositions;
    eligiblePositions["GK"] = QStringList({"Goalkeeper"});
    eligiblePositions["LB"] = QStringList({"Defender", "Left Back"});
    eligiblePositions["CB"] = QStringList({"Defender", "Center Back"});
    eligiblePositions["RB"] = QStringList({"Defender", "Right Back"});
    eligiblePositions["LWB"] = QStringList({"Defender", "Left Back", "Left Midfielder"});
    eligiblePositions["RWB"] = QStringList({"Defender", "Right Back", "Right Midfielder"});
    eligiblePositions["LM"] = QStringList({"Midfielder", "Left Midfielder"});
    eligiblePositions["CM"] = QStringList({"Midfielder", "Central Midfielder"});
    eligiblePositions["RM"] = QStringList({"Midfielder", "Right Midfielder"});
    eligiblePositions["LW"] = QStringList({"Forward", "Left Winger"});
    eligiblePositions["ST"] = QStringList({"Forward", "Striker"});
    eligiblePositions["RW"] = QStringList({"Forward", "Right Winger"});

    // Sélection des joueurs pour chaque position
    QSet<int> usedPlayerIds;

    for (int i = 0; i < positionLabels.size() && i < positions.size(); ++i) {
        QString posLabel = positionLabels[i];
        QPointF pos = positions[i];

        // Chercher le meilleur joueur disponible pour cette position
        PlayerInfo *bestPlayer = nullptr;
        int bestScore = -1;

        for (int j = 0; j < allPlayers.size(); ++j) {
            PlayerInfo &player = allPlayers[j];

            // Ignorer les joueurs déjà utilisés
            if (usedPlayerIds.contains(player.id)) {
                continue;
            }

            // Vérifier si le joueur peut jouer à cette position
            bool canPlay = false;
            for (const QString &eligiblePos : eligiblePositions[posLabel]) {
                if (player.position.contains(eligiblePos, Qt::CaseInsensitive)) {
                    canPlay = true;
                    break;
                }
            }

            // Si spécial pour GK: les gardiens doivent être gardiens, et les non-gardiens ne peuvent pas être GK
            if (posLabel == "GK") {
                canPlay = player.position.contains("Goalkeeper", Qt::CaseInsensitive);
            } else if (player.position.contains("Goalkeeper", Qt::CaseInsensitive)) {
                canPlay = false;
            }

            if (canPlay && (bestPlayer == nullptr || player.score > bestScore)) {
                bestPlayer = &player;
                bestScore = player.score;
            }
        }

        if (bestPlayer) {
            // Créer un nœud pour ce joueur
            QString playerName = bestPlayer->firstName + " " + bestPlayer->lastName;
            createPlayerNode(pos, posLabel, bestPlayer->id, playerName, bestPlayer->imageData);
            usedPlayerIds.insert(bestPlayer->id);
        } else {
            // Pas de joueur disponible pour cette position
            createPlayerNode(pos, posLabel, -1, "No player", QByteArray());
        }
    }
}

void FormationPopup::createPlayerNode(const QPointF &pos, const QString &position, int playerId,
                                      const QString &playerName, const QByteArray &imageData)
{
    // Créer un groupe pour regrouper les éléments
    QGraphicsItemGroup *playerGroup = new QGraphicsItemGroup();
    scene->addItem(playerGroup);

    // Générer l'avatar du joueur
    QPixmap avatar;
    if (!imageData.isEmpty()) {
        avatar = createPlayerAvatar(imageData, "");
    } else {
        QString initials = position;
        if (playerId > 0) {
            QStringList parts = playerName.split(" ");
            if (parts.size() >= 2) {
                initials = QString(parts[0][0]) + QString(parts[1][0]);
            }
        }
        avatar = createPlayerAvatar(QByteArray(), initials);
    }

    // Créer un item d'image pour l'avatar
    QGraphicsPixmapItem *avatarItem = new QGraphicsPixmapItem(avatar);
    avatarItem->setPos(pos.x() - avatar.width() / 2, pos.y() - avatar.height() / 2);

    // Ajouter une ombre
    QGraphicsDropShadowEffect *shadowEffect = new QGraphicsDropShadowEffect();
    shadowEffect->setBlurRadius(10);
    shadowEffect->setColor(QColor(0, 0, 0, 150));
    shadowEffect->setOffset(3, 3);
    avatarItem->setGraphicsEffect(shadowEffect);

    playerGroup->addToGroup(avatarItem);

    // Ajouter le nom du joueur
    QGraphicsTextItem *nameItem = new QGraphicsTextItem(playerName);
    nameItem->setDefaultTextColor(Qt::white);
    nameItem->setFont(QFont("Arial", 9, QFont::Bold));

    // Centrer le texte sous l'avatar
    QRectF textRect = nameItem->boundingRect();
    nameItem->setPos(pos.x() - textRect.width() / 2, pos.y() + avatar.height() / 2 + 5);

    // Ajouter un fond au texte pour meilleure lisibilité
    QGraphicsRectItem *textBg = new QGraphicsRectItem(textRect);
    textBg->setPos(nameItem->pos());
    textBg->setBrush(QColor(0, 0, 0, 150));
    textBg->setPen(Qt::NoPen);

    // Ajouter les items au groupe dans le bon ordre
    playerGroup->addToGroup(textBg);
    playerGroup->addToGroup(nameItem);

    // Ajouter le badge de position
    QGraphicsEllipseItem *positionBadge = new QGraphicsEllipseItem(0, 0, 24, 24);
    positionBadge->setBrush(QColor(255, 204, 0));
    positionBadge->setPen(QPen(Qt::white, 1));
    positionBadge->setPos(pos.x() + avatar.width() / 2 - 12, pos.y() - avatar.height() / 2 - 10);

    QGraphicsTextItem *positionText = new QGraphicsTextItem(position);
    positionText->setDefaultTextColor(Qt::black);
    positionText->setFont(QFont("Arial", 7, QFont::Bold));

    // Centrer le texte dans le badge
    QRectF posTextRect = positionText->boundingRect();
    positionText->setPos(
        positionBadge->pos().x() + (24 - posTextRect.width()) / 2,
        positionBadge->pos().y() + (24 - posTextRect.height()) / 2
        );

    playerGroup->addToGroup(positionBadge);
    playerGroup->addToGroup(positionText);
}

QPixmap FormationPopup::createPlayerAvatar(const QByteArray &imageData, const QString &initials)
{
    QPixmap avatar(70, 70);
    avatar.fill(Qt::transparent);

    QPainter painter(&avatar);
    painter.setRenderHint(QPainter::Antialiasing);

    // Dessiner le cercle de base
    painter.setPen(QPen(Qt::white, 2));
    painter.setBrush(QColor(52, 152, 219, 200));
    painter.drawEllipse(2, 2, 66, 66);

    if (!imageData.isEmpty()) {
        // Charger l'image du joueur
        QPixmap playerImage;
        if (playerImage.loadFromData(imageData)) {
            // Redimensionner et découper en cercle
            QPixmap scaledImage = playerImage.scaled(66, 66, Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);

            // Centrer l'image
            int x = (scaledImage.width() - 66) / 2;
            int y = (scaledImage.height() - 66) / 2;
            if (x < 0) x = 0;
            if (y < 0) y = 0;

            // Appliquer un masque circulaire
            QPainterPath path;
            path.addEllipse(2, 2, 66, 66);
            painter.setClipPath(path);
            painter.drawPixmap(2, 2, scaledImage, x, y, 66, 66);
        }
    } else {
        // Utiliser les initiales
        painter.setPen(Qt::white);
        painter.setFont(QFont("Arial", 20, QFont::Bold));
        painter.drawText(avatar.rect(), Qt::AlignCenter, initials);
    }

    painter.end();
    return avatar;
}
