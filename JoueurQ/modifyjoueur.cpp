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
    setWindowTitle("Modify Player");
    setMinimumWidth(400);
    
    // Create main layout
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    
    // Player ID section (read-only)
    QHBoxLayout *idLayout = new QHBoxLayout();
    labelId = new QLabel("Player ID:", this);
    lineEditId = new QLineEdit(this);
    lineEditId->setReadOnly(true); // Make ID field read-only
    lineEditId->setStyleSheet("background-color: #f0f0f0;"); // Grey background to indicate read-only
    buttonLoad = new QPushButton("Load", this);
    idLayout->addWidget(labelId);
    idLayout->addWidget(lineEditId);
    idLayout->addWidget(buttonLoad);
    mainLayout->addLayout(idLayout);
    
    // Hide the load button since we're setting the ID directly
    buttonLoad->setVisible(false);
    
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
    
    // Automatically load the player data when ID is set
    loadJoueurData();
}

void ModifyJoueur::loadJoueurData()
{
    // No need to validate ID since it's set directly and read-only
    if (joueurId <= 0) {
        QMessageBox::warning(this, "Error", "Invalid player ID.");
        return;
    }
    
    // Query player data
    QSqlQuery query;
    query.prepare("SELECT * FROM joueur WHERE id_player = :id");
    query.bindValue(":id", joueurId);
    
    if (query.exec() && query.next()) {
        // Get player values from database
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
        int status = query.value("status").toInt();
        QByteArray img = query.value("img_joueur").toByteArray();
        
        // Fill form fields with data
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
        
        QMessageBox::information(this, "Success", "Player data loaded successfully.");
    } else {
        QMessageBox::warning(this, "Error", "Could not find player with ID: " + QString::number(joueurId));
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
        QMessageBox::warning(this, "Error", "No player loaded for modification.");
        return;
    }
    
    // Get values from controls
    int id_team = comboBoxTeam->currentData().toInt();
    QString first_name = lineEditFirstName->text().trimmed();
    QString last_name = lineEditLastName->text().trimmed();
    QString position = comboBoxPosition->currentText().trimmed();
    int jersey_nb = spinBoxJerseyNb->value();
    QDate date_of_birth = dateEditBirth->date();
    QString nationality = lineEditNationality->text().trimmed();
    
    int goals = spinBoxGoals->value();
    int assists = spinBoxAssists->value();
    int injured = comboBoxInjured->currentIndex();
    int yellowCard = spinBoxYellowCard->value();
    int redCard = spinBoxRedCard->value();
    int status = comboBoxStatus->currentIndex();
    
    // Field validation
    
    // Check for empty required fields
    if (first_name.isEmpty() || last_name.isEmpty() || nationality.isEmpty()) {
        QMessageBox::warning(this, "Error", "Please fill all required fields (First Name, Last Name, Nationality).");
        return;
    }
    
    // Validate name format
    QRegularExpression nameRegex("^[A-Za-z\\s'-]+$");
    if (!nameRegex.match(first_name).hasMatch()) {
        QMessageBox::warning(this, "Error", "First name contains invalid characters. Only letters, spaces, hyphens and apostrophes are allowed.");
        lineEditFirstName->setFocus();
        return;
    }
    
    if (!nameRegex.match(last_name).hasMatch()) {
        QMessageBox::warning(this, "Error", "Last name contains invalid characters. Only letters, spaces, hyphens and apostrophes are allowed.");
        lineEditLastName->setFocus();
        return;
    }
    
    if (!nameRegex.match(nationality).hasMatch()) {
        QMessageBox::warning(this, "Error", "Nationality contains invalid characters. Only letters, spaces, hyphens and apostrophes are allowed.");
        lineEditNationality->setFocus();
        return;
    }
    
    // Validate date of birth
    QDate currentDate = QDate::currentDate();
    QDate minDate = currentDate.addYears(-50); // No players older than 50
    QDate maxDate = currentDate.addYears(-16); // No players younger than 16
    
    if (date_of_birth > maxDate || date_of_birth < minDate) {
        QMessageBox::warning(this, "Error", "Invalid date of birth. Player must be between 16 and 50 years old.");
        dateEditBirth->setFocus();
        return;
    }
    
    // Validate statistics
    if (goals < 0 || assists < 0 || yellowCard < 0 || redCard < 0) {
        QMessageBox::warning(this, "Error", "Statistics cannot have negative values.");
        return;
    }
    
    // Confirm modification
    QMessageBox::StandardButton confirmation;
    confirmation = QMessageBox::question(this, "Confirm Modification", 
        "Are you sure you want to update player with ID: " + QString::number(joueurId) + "?",
        QMessageBox::Yes | QMessageBox::No);
        
    if (confirmation == QMessageBox::No) {
        return;
    }
    
    // Attempt to modify player
    if (joueur::modifier(joueurId, id_team, first_name, last_name, position, jersey_nb, 
                        date_of_birth, nationality, goals, assists, injured, 
                        yellowCard, redCard, status, imageData)) {
        QMessageBox::information(this, "Success", "Player information has been updated successfully.");
        accept();
    } else {
        QMessageBox::critical(this, "Error", "Could not update player information.");
    }
}
