#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QMessageBox>
#include <QFileDialog>
#include <QFile>
#include <QPixmap>
#include "joueur.h"
#include "deletejoueur.h"
#include "modifyjoueur.h" // Ajoutez cet include en haut du fichier

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->button1, &QPushButton::clicked, this, &MainWindow::on_button1_clicked);
    connect(ui->toolButton, &QToolButton::clicked, this, &MainWindow::on_toolButtonImage_clicked);
    connect(ui->pushButton_3, &QPushButton::clicked, this, &MainWindow::on_buttonDelete_clicked); // Connexion du bouton supprimer
    loadTeams();

    // Définir les en-têtes de colonnes pour le tableau
    ui->tableWidget->setColumnCount(13); // 13 colonnes pour les attributs du joueur
    ui->tableWidget->setHorizontalHeaderLabels({
        "ID Joueur", "ID Équipe", "Prénom", "Nom", "Position", "Numéro", "Date de naissance",
        "Nationalité", "Buts", "Passes", "Blessé", "Carton Jaune", "Carton Rouge"
    });

    loadPlayers(); // Charger les joueurs au démarrage
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::loadTeams()
{
    // Vider le combobox et la map
    ui->comboBoxTeam->clear();
    teamMap.clear();
    
    // Charger toutes les équipes depuis la base de données
    QSqlQuery query("SELECT id_team, team_name FROM equipe ORDER BY team_name");
    
    while (query.next()) {
        int id = query.value(0).toInt();
        QString name = query.value(1).toString();
        
        // Ajouter au combobox et à la map
        ui->comboBoxTeam->addItem(name);
        teamMap[name] = id;
    }
    
    if (ui->comboBoxTeam->count() == 0) {
        // Aucune équipe trouvée
        QMessageBox::warning(this, "Attention", "Aucune équipe n'a été trouvée dans la base de données.");
    }
}

void MainWindow::loadPlayers()
{
    // Vider le tableau
    ui->tableWidget->clearContents();
    ui->tableWidget->setRowCount(0);

    // Exécuter la requête pour récupérer les joueurs
    QSqlQuery query("SELECT id_player, id_team, first_name, last_name, position, jersey_nb, date_of_birth, nationality, goals, assists, injured, yellow_card, red_card FROM joueur");

    // Parcourir les résultats de la requête
    int row = 0;
    while (query.next()) {
        // Ajouter une nouvelle ligne au tableau
        ui->tableWidget->insertRow(row);

        // Remplir chaque colonne avec les données de la requête
        ui->tableWidget->setItem(row, 0, new QTableWidgetItem(query.value(0).toString())); // id_player
        ui->tableWidget->setItem(row, 1, new QTableWidgetItem(query.value(1).toString())); // id_team
        ui->tableWidget->setItem(row, 2, new QTableWidgetItem(query.value(2).toString())); // first_name
        ui->tableWidget->setItem(row, 3, new QTableWidgetItem(query.value(3).toString())); // last_name
        ui->tableWidget->setItem(row, 4, new QTableWidgetItem(query.value(4).toString())); // position
        ui->tableWidget->setItem(row, 5, new QTableWidgetItem(query.value(5).toString())); // jersey_nb
        ui->tableWidget->setItem(row, 6, new QTableWidgetItem(query.value(6).toString())); // date_of_birth
        ui->tableWidget->setItem(row, 7, new QTableWidgetItem(query.value(7).toString())); // nationality
        ui->tableWidget->setItem(row, 8, new QTableWidgetItem(query.value(8).toString())); // goals
        ui->tableWidget->setItem(row, 9, new QTableWidgetItem(query.value(9).toString())); // assists
        ui->tableWidget->setItem(row, 10, new QTableWidgetItem(query.value(10).toString())); // injured
        ui->tableWidget->setItem(row, 11, new QTableWidgetItem(query.value(11).toString())); // yellow_card
        ui->tableWidget->setItem(row, 12, new QTableWidgetItem(query.value(12).toString())); // red_card

        row++;
    }

    // Optionnel : ajuster la taille des colonnes pour s'adapter au contenu
    ui->tableWidget->resizeColumnsToContents();
}

void MainWindow::on_toolButtonImage_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Sélectionner une image", "", "Images (*.png *.jpg *.jpeg *.bmp)");
    if (!fileName.isEmpty()) {
        QFile file(fileName);
        if (file.open(QIODevice::ReadOnly)) {
            img_joueur = file.readAll();
            file.close();
            QPixmap pixmap;
            pixmap.loadFromData(img_joueur);
            ui->label_2->setPixmap(pixmap.scaled(ui->label_2->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
            QMessageBox::information(this, "Succès", "Image chargée avec succès.");
        } else {
            QMessageBox::critical(this, "Erreur", "Impossible de lire le fichier image.");
        }
    }
}

void MainWindow::on_button1_clicked()
{
    // Vérifier si une équipe est sélectionnée
    if (ui->comboBoxTeam->currentIndex() < 0) {
        QMessageBox::warning(this, "Erreur", "Veuillez sélectionner une équipe.");
        return;
    }
    
    // Récupérer l'ID de l'équipe sélectionnée
    QString teamName = ui->comboBoxTeam->currentText();
    int id_team = teamMap[teamName];
    
    // Récupérer les autres informations du joueur
    QString first_name = ui->lineEdit_3->text();
    QString last_name = ui->lineEdit_4->text();
    QString position = ui->lineEdit_5->text();
    
    // Vérifier que le numéro de maillot est un nombre valide
    bool ok;
    int jersey_nb = ui->lineEdit_8->text().toInt(&ok);
    if (!ok || jersey_nb <= 0) {
        QMessageBox::warning(this, "Erreur", "Le numéro de maillot doit être un nombre positif.");
        return;
    }
    
    QDate date_of_birth = ui->dateEdit->date();
    QString nationality = ui->lineEdit_9->text();
    
    // Validation des champs
    if (first_name.isEmpty() || last_name.isEmpty() || position.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Veuillez remplir tous les champs obligatoires.");
        return;
    }
    
    // Créer et ajouter le joueur
    joueur newPlayer(id_team, first_name, last_name, position, jersey_nb, date_of_birth, nationality, img_joueur);
    
    if (newPlayer.ajouterDansBD()) {
        QMessageBox::information(this, "Succès", "Le joueur a été ajouté avec succès.");
        // Nettoyer les champs de saisie
        ui->lineEdit_3->clear();
        ui->lineEdit_4->clear();
        ui->lineEdit_5->clear();
        ui->lineEdit_8->clear();
        ui->lineEdit_9->clear();
        img_joueur.clear(); // Réinitialiser l'image
        ui->label_2->clear(); // Réinitialiser l'affichage de l'image

        // Mettre à jour le tableau des joueurs
        loadPlayers();
    } else {
        QMessageBox::critical(this, "Erreur", "Impossible d'ajouter le joueur dans la base de données.");
    }
}

void MainWindow::on_buttonDelete_clicked()
{
    DeleteJoueur deleteDialog(this);
    
    if (deleteDialog.exec() == QDialog::Accepted) {
        // Le joueur a été supprimé avec succès dans la boîte de dialogue
        // Vous pouvez donc simplement mettre à jour votre interface
        loadPlayers(); // Pour rafraîchir la liste des joueurs
    }
}

void MainWindow::on_buttonModify_clicked()
{
    ModifyJoueur modifyDialog(this);
    
    // Si l'utilisateur a sélectionné un joueur dans le tableau, préchargez son ID
    QModelIndexList selection = ui->tableWidget->selectionModel()->selectedRows();
    if (!selection.isEmpty()) {
        int row = selection.first().row();
        int joueurId = ui->tableWidget->item(row, 0)->text().toInt(); // La colonne 0 contient l'ID
        modifyDialog.setJoueurId(joueurId);
    }
    
    if (modifyDialog.exec() == QDialog::Accepted) {
        // Recharger la liste des joueurs pour afficher les modifications
        loadPlayers();
    }
}