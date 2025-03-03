#include "deletejoueur.h"
#include <QMessageBox>
#include <QDialogButtonBox>

DeleteJoueur::DeleteJoueur(QWidget *parent) :
    QDialog(parent),
    joueurId(0)
{
    setWindowTitle("Supprimer un joueur");
    resize(300, 150);

    QVBoxLayout *layout = new QVBoxLayout(this);
    
    QLabel *label = new QLabel("Entrez l'ID du joueur à supprimer:", this);
    layout->addWidget(label);
    
    lineEdit = new QLineEdit(this);
    layout->addWidget(lineEdit);
    
    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
    connect(buttonBox, &QDialogButtonBox::accepted, this, &DeleteJoueur::acceptDialog);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
    layout->addWidget(buttonBox);
    
    setLayout(layout);
}

DeleteJoueur::~DeleteJoueur()
{
    // Les widgets sont détruits automatiquement car ils ont this comme parent
}

int DeleteJoueur::getJoueurId() const
{
    return joueurId;
}

void DeleteJoueur::acceptDialog()
{
    bool ok;
    joueurId = lineEdit->text().toInt(&ok);
    
    if (!ok || joueurId <= 0) {
        QMessageBox::warning(this, "Erreur", "Veuillez entrer un ID valide (nombre entier positif).");
        return;
    }
    
    accept();
}
