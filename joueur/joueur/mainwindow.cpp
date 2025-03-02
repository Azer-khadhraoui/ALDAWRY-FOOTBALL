#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->button1, &QPushButton::clicked, this, &MainWindow::on_button1_clicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_button1_clicked()
{
    // Récupérer les informations du joueur depuis les champs de saisie
   
    int id_team = ui->lineEdit_6->text().toInt();
    QString first_name = ui->lineEdit_3->text();
    QString last_name = ui->lineEdit_6->text();
    QString position = ui->lineEdit_5->text();
    int jersey_nb = ui->lineEdit_8->text().toInt();
    QDate date_of_birth = ui->dateEdit->date();
    QString nationality = ui->lineEdit_9->text();
 
    QByteArray img_joueur; // Vous devez ajouter un moyen de récupérer l'image

    // Créer un objet joueur avec les informations récupérées
    joueur newPlayer(id_player, id_team, first_name, last_name, position, jersey_nb, date_of_birth, nationality, goals, assists, injured, yellow_card, red_card, status, img_joueur);

    // Ajouter le joueur dans la base de données
    if (newPlayer.ajouterDansBD()) {
        qDebug() << "Le joueur a été ajouté avec succès.";
    } else {
        qDebug() << "Erreur lors de l'ajout du joueur.";
    }
}
