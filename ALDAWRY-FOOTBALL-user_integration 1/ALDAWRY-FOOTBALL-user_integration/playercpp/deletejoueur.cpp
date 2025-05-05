#include "../playerheaders/deletejoueur.h"
#include "../playerheaders/joueur.h"
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
    // Validate player ID
    bool ok;
    QString idText = lineEditId->text().trimmed();
    
    // Check if empty
    if (idText.isEmpty()) {
        QMessageBox::warning(this, "Error", "Please enter a player ID.");
        lineEditId->setFocus();
        return;
    }
    
    joueurId = idText.toInt(&ok);
    
    // Check if valid integer
    if (!ok) {
        QMessageBox::warning(this, "Error", "Player ID must be a number.");
        lineEditId->clear();
        lineEditId->setFocus();
        return;
    }
    
    // Check if positive
    if (joueurId <= 0) {
        QMessageBox::warning(this, "Error", "Player ID must be a positive number.");
        lineEditId->clear();
        lineEditId->setFocus();
        return;
    }
    
    // Confirm deletion
    QMessageBox::StandardButton confirmation;
    confirmation = QMessageBox::question(this, "Confirm Deletion", 
        "Are you sure you want to delete player with ID: " + QString::number(joueurId) + "?",
        QMessageBox::Yes | QMessageBox::No);
        
    if (confirmation == QMessageBox::No) {
        return;
    }
    
    // Attempt to delete player
    if (joueur::supprimer(joueurId)) {
        QMessageBox::information(this, "Success", "Player has been successfully deleted.");
        accept();
    } else {
        QMessageBox::warning(this, "Error", "Could not delete player. Please check the ID and try again.");
    }
}
