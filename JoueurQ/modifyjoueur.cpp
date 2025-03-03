#include "modifyjoueur.h"
#include "joueur.h"
#include <QMessageBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QLabel>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QFileDialog>
#include <QPixmap>
#include <QBuffer>

ModifyJoueur::ModifyJoueur(QWidget *parent) :
    QDialog(parent),
    joueurId(0)
{
    setWindowTitle("Modifier un joueur");
    setMinimumWidth(400);
    
    // Créer l'interface manuellement
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    
    // Section pour entrer l'ID et charger les données
    QHBoxLayout *idLayout = new QHBoxLayout();
    labelId = new QLabel("ID du joueur à modifier:", this);
    lineEditId = new QLineEdit(this);
    buttonLoad = new QPushButton("Charger", this);
    idLayout->addWidget(labelId);
    idLayout->addWidget(lineEditId);
    idLayout->addWidget(buttonLoad);
    mainLayout->addLayout(idLayout);
    
    // Formulaire principal pour tous les attributs
    QFormLayout *formLayout = new QFormLayout();
    
    // Chargement des équipes
    comboBoxTeam = new QComboBox(this);
    loadTeamsIntoComboBox();
    formLayout->addRow("Équipe:", comboBoxTeam);
    
    // Informations personnelles
    lineEditFirstName = new QLineEdit(this);
    formLayout->addRow("Prénom:", lineEditFirstName);
    
    lineEditLastName = new QLineEdit(this);
    formLayout->addRow("Nom:", lineEditLastName);
    
    comboBoxPosition = new QComboBox(this);
    comboBoxPosition->addItems({"Gardien", "Défenseur", "Milieu", "Attaquant"});
    formLayout->addRow("Position:", comboBoxPosition);
    
    spinBoxJerseyNb = new QSpinBox(this);
    spinBoxJerseyNb->setRange(1, 99);
    formLayout->addRow("Numéro de maillot:", spinBoxJerseyNb);
    
    dateEditBirth = new QDateEdit(this);
    dateEditBirth->setCalendarPopup(true);
    dateEditBirth->setDisplayFormat("dd/MM/yyyy");
    formLayout->addRow("Date de naissance:", dateEditBirth);
    
    lineEditNationality = new QLineEdit(this);
    formLayout->addRow("Nationalité:", lineEditNationality);
    
    // Statistiques
    spinBoxGoals = new QSpinBox(this);
    spinBoxGoals->setRange(0, 999);
    formLayout->addRow("Buts:", spinBoxGoals);
    
    spinBoxAssists = new QSpinBox(this);
    spinBoxAssists->setRange(0, 999);
    formLayout->addRow("Passes décisives:", spinBoxAssists);
    
    comboBoxInjured = new QComboBox(this);
    comboBoxInjured->addItem("Non blessé", 0);
    comboBoxInjured->addItem("Blessé", 1);
    formLayout->addRow("État de blessure:", comboBoxInjured);
    
    spinBoxYellowCard = new QSpinBox(this);
    spinBoxYellowCard->setRange(0, 99);
    formLayout->addRow("Cartons jaunes:", spinBoxYellowCard);
    
    spinBoxRedCard = new QSpinBox(this);
    spinBoxRedCard->setRange(0, 99);
    formLayout->addRow("Cartons rouges:", spinBoxRedCard);
    
    comboBoxStatus = new QComboBox(this);
    comboBoxStatus->addItem("Actif", 0);
    comboBoxStatus->addItem("Blessé", 1);
    comboBoxStatus->addItem("Suspendu", 2);
    comboBoxStatus->addItem("Transféré", 3);
    formLayout->addRow("Statut:", comboBoxStatus);
    
    // Section pour l'image
    QHBoxLayout *imageLayout = new QHBoxLayout();
    labelImage = new QLabel(this);
    labelImage->setMinimumSize(100, 120);
    labelImage->setMaximumSize(100, 120);
    labelImage->setScaledContents(true);
    labelImage->setFrameShape(QFrame::Box);
    
    buttonSelectImage = new QPushButton("Sélectionner une image", this);
    imageLayout->addWidget(labelImage);
    imageLayout->addWidget(buttonSelectImage);
    formLayout->addRow("Image:", imageLayout);
    
    mainLayout->addLayout(formLayout);
    
    // Boutons
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    pushButtonModifier = new QPushButton("Modifier", this);
    pushButtonAnnuler = new QPushButton("Annuler", this);
    buttonLayout->addWidget(pushButtonModifier);
    buttonLayout->addWidget(pushButtonAnnuler);
    mainLayout->addLayout(buttonLayout);
    
    // Connexions
    connect(buttonLoad, &QPushButton::clicked, this, &ModifyJoueur::loadJoueurData);
    connect(pushButtonModifier, &QPushButton::clicked, this, &ModifyJoueur::acceptDialog);
    connect(pushButtonAnnuler, &QPushButton::clicked, this, &QDialog::reject);
    connect(buttonSelectImage, &QPushButton::clicked, this, &ModifyJoueur::selectImage);
}

ModifyJoueur::~ModifyJoueur()
{
   
}

void ModifyJoueur::loadTeamsIntoComboBox()
{
    
    comboBoxTeam->clear();
    teamMap.clear();
    
    
    QSqlQuery query("SELECT id_team, team_name FROM equipe ORDER BY team_name");
    
    while (query.next()) {
        int id = query.value(0).toInt();
        QString name = query.value(1).toString();
        
        // Ajouter au combobox et à la map
        comboBoxTeam->addItem(name, id);
        teamMap[id] = name;
    }
}

void ModifyJoueur::setJoueurId(int id)
{
    joueurId = id;
    lineEditId->setText(QString::number(id));
    loadJoueurData();
}

void ModifyJoueur::loadJoueurData()
{
    bool ok;
    int id = lineEditId->text().toInt(&ok);
    
    if (!ok || id <= 0) {
        QMessageBox::warning(this, "Erreur", "Veuillez entrer un ID valide.");
        return;
    }
    
    joueurId = id;
    
    QSqlQuery query;
    query.prepare("SELECT * FROM joueur WHERE id_player = :id");
    query.bindValue(":id", joueurId);
    
    if (query.exec() && query.next()) {
        
        int id_team = query.value("id_team").toInt();
        QString first_name = query.value("first_name").toString();
        QString last_name = query.value("last_name").toString();
        QString position = query.value("position").toString();
        int jersey_nb = query.value("jersey_nb").toInt();
        QDate date_of_birth = query.value("date_of_birth").toDate();
        QString nationality = query.value("nationality").toString();
        int goals = query.value("goals").toInt();
        int assists = query.value("assists").toInt();
        int injured = query.value("injured").toInt();
        int yellowCard = query.value("yellow_card").toInt();
        int redCard = query.value("red_card").toInt();
        int status = query.value("status").toInt(); // Changé en int
        QByteArray img = query.value("img_joueur").toByteArray();
        
        
        int teamIndex = comboBoxTeam->findData(id_team);
        if (teamIndex >= 0) {
            comboBoxTeam->setCurrentIndex(teamIndex);
        }
        
        lineEditFirstName->setText(first_name);
        lineEditLastName->setText(last_name);
        
        int posIndex = comboBoxPosition->findText(position);
        if (posIndex >= 0) {
            comboBoxPosition->setCurrentIndex(posIndex);
        }
        
        spinBoxJerseyNb->setValue(jersey_nb);
        dateEditBirth->setDate(date_of_birth);
        lineEditNationality->setText(nationality);
        
        spinBoxGoals->setValue(goals);
        spinBoxAssists->setValue(assists);
        comboBoxInjured->setCurrentIndex(injured);
        spinBoxYellowCard->setValue(yellowCard);
        spinBoxRedCard->setValue(redCard);
        
        comboBoxStatus->setCurrentIndex(status); // Utilisez directement l'index
        
        // Afficher l'image si elle existe
        imageData = img;
        if (!imageData.isEmpty()) {
            QPixmap pixmap;
            pixmap.loadFromData(imageData);
            labelImage->setPixmap(pixmap);
        } else {
            labelImage->clear();
            labelImage->setText("Aucune image");
        }
        
        QMessageBox::information(this, "Succès", "Données du joueur chargées avec succès.");
    } else {
        QMessageBox::warning(this, "Erreur", "Impossible de trouver le joueur avec l'ID spécifié.");
    }
}

void ModifyJoueur::selectImage()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Sélectionner une image", "", "Images (*.png *.jpg *.jpeg)");
    if (!fileName.isEmpty()) {
        QPixmap pixmap(fileName);
        
        if (!pixmap.isNull()) {
            // Afficher l'image
            labelImage->setPixmap(pixmap.scaled(100, 120, Qt::KeepAspectRatio));
            
            // Convertir en QByteArray pour stockage
            QByteArray byteArray;
            QBuffer buffer(&byteArray);
            buffer.open(QIODevice::WriteOnly);
            pixmap.save(&buffer, "JPG");
            imageData = byteArray;
        } else {
            QMessageBox::warning(this, "Erreur", "Impossible de charger l'image sélectionnée.");
        }
    }
}

void ModifyJoueur::acceptDialog()
{
    if (joueurId <= 0) {
        QMessageBox::warning(this, "Erreur", "Veuillez d'abord charger les données d'un joueur.");
        return;
    }
    
    // Récupérer toutes les valeurs des contrôles
    int id_team = comboBoxTeam->currentData().toInt();
    QString first_name = lineEditFirstName->text();
    QString last_name = lineEditLastName->text();
    QString position = comboBoxPosition->currentText();
    int jersey_nb = spinBoxJerseyNb->value();
    QDate date_of_birth = dateEditBirth->date();
    QString nationality = lineEditNationality->text();
    
    int goals = spinBoxGoals->value();
    int assists = spinBoxAssists->value();
    int injured = comboBoxInjured->currentIndex();
    int yellowCard = spinBoxYellowCard->value();
    int redCard = spinBoxRedCard->value();
    int status = comboBoxStatus->currentData().toInt();
    
    // Validation des champs obligatoires
    if (first_name.isEmpty() || last_name.isEmpty() || position.isEmpty() || nationality.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Veuillez remplir tous les champs obligatoires.");
        return;
    }
    
    // Appeler la méthode de modification
    if (joueur::modifier(joueurId, id_team, first_name, last_name, position, jersey_nb, 
                        date_of_birth, nationality, goals, assists, injured, 
                        yellowCard, redCard, status, imageData)) {
        QMessageBox::information(this, "Succès", "Informations du joueur mises à jour avec succès.");
        accept();
    } else {
        QMessageBox::critical(this, "Erreur", "Impossible de mettre à jour les informations du joueur.");
    }
}
