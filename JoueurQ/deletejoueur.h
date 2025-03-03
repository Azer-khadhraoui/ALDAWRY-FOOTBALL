#ifndef DELETEJOUEUR_H
#define DELETEJOUEUR_H

#include <QDialog>
#include <QLineEdit>
#include <QPushButton>

// Nous n'utiliserons plus la déclaration forward de Ui::Delete_Joueur_2
// Nous allons créer l'interface manuellement

class DeleteJoueur : public QDialog
{
    Q_OBJECT

public:
    explicit DeleteJoueur(QWidget *parent = nullptr);
    ~DeleteJoueur();
    int getJoueurId() const;

private slots:
    void acceptDialog();

private:
    QLineEdit *lineEditId;
    QPushButton *pushButtonSupprimer;
    QPushButton *pushButtonAnnuler;
    int joueurId;
};

#endif // DELETEJOUEUR_H
