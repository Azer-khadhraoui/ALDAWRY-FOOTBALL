#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QMessageBox>
#include "joueur.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    
    // Charger les équipes disponibles dans le combobox
    loadTeams();
    
    connect(ui->button1, &QPushButton::clicked, this, &MainWindow::on_button1_clicked);
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
    QByteArray img_joueur; // Vous devez ajouter un moyen de récupérer l'image
    
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
    } else {
        QMessageBox::critical(this, "Erreur", "Impossible d'ajouter le joueur dans la base de données.");
    }
}