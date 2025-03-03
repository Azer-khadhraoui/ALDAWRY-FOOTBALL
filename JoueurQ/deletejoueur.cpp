#include "deletejoueur.h"
#include "joueur.h"
#include <QMessageBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>

DeleteJoueur::DeleteJoueur(QWidget *parent) :
    QDialog(parent),
    joueurId(0)
{
    setWindowTitle("Supprimer un joueur");
    setMinimumWidth(300);
    
    // Créer l'interface manuellement
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    
    QLabel *label = new QLabel("ID du joueur à supprimer:", this);
    mainLayout->addWidget(label);
    
    lineEditId = new QLineEdit(this);
    mainLayout->addWidget(lineEditId);
    
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    pushButtonSupprimer = new QPushButton("Supprimer", this);
    pushButtonAnnuler = new QPushButton("Annuler", this);
    buttonLayout->addWidget(pushButtonSupprimer);
    buttonLayout->addWidget(pushButtonAnnuler);
    
    mainLayout->addLayout(buttonLayout);
    
    // Connexions
    connect(pushButtonSupprimer, &QPushButton::clicked, this, &DeleteJoueur::acceptDialog);
    connect(pushButtonAnnuler, &QPushButton::clicked, this, &QDialog::reject);
}

DeleteJoueur::~DeleteJoueur()
{
    // Les widgets sont automatiquement détruits car ils ont this comme parent
}

int DeleteJoueur::getJoueurId() const
{
    return joueurId;
}

void DeleteJoueur::acceptDialog()
{
    bool ok;
    joueurId = lineEditId->text().toInt(&ok);
    
    if (!ok || joueurId <= 0) {
        QMessageBox::warning(this, "Erreur", "Veuillez entrer un ID valide (nombre entier positif).");
        return;
    }
    
    // Utiliser la méthode statique de la classe joueur pour supprimer
    if (joueur::supprimer(joueurId)) {
        QMessageBox::information(this, "Succès", "Le joueur a été supprimé avec succès.");
        accept(); // Fermer la boîte de dialogue avec succès
    } else {
        QMessageBox::warning(this, "Erreur", "Impossible de supprimer le joueur. Vérifiez l'ID et réessayez.");
    }
}
