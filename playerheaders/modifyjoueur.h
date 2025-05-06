#ifndef MODIFYJOUEUR_H
#define MODIFYJOUEUR_H

#include <QDialog>
#include <QLineEdit>
#include <QComboBox>
#include <QSpinBox>
#include <QPushButton>
#include <QLabel>
#include <QDateEdit>
#include <QMap>

class ModifyJoueur : public QDialog
{
    Q_OBJECT

public:
    explicit ModifyJoueur(QWidget *parent = nullptr);
    ~ModifyJoueur();
    void setJoueurId(int id); // Pour définir l'ID du joueur à modifier

private slots:
    void acceptDialog();
    void loadJoueurData(); // Pour charger les données du joueur
    void selectImage();    // Pour sélectionner une nouvelle image
    void onStatusChanged(int index); // Ajoutez ce slot

private:
    void loadTeamsIntoComboBox();  // Charger la liste des équipes
    
    int joueurId;
    QByteArray imageData;  
    QMap<int, QString> teamMap;  // Mapping des ID des équipes et leurs noms
    
    QLabel *labelId;
    QLineEdit *lineEditId;
    QPushButton *buttonLoad;
    
    QComboBox *comboBoxTeam;
    QLineEdit *lineEditFirstName;
    QLineEdit *lineEditLastName;
    QComboBox *comboBoxPosition;
    QSpinBox *spinBoxJerseyNb;
    QDateEdit *dateEditBirth;
    QLineEdit *lineEditNationality;
    
    QSpinBox *spinBoxGoals;
    QSpinBox *spinBoxAssists;
    QComboBox *comboBoxInjured;
    QSpinBox *spinBoxYellowCard;
    QSpinBox *spinBoxRedCard;
    QComboBox *comboBoxStatus;
    
    QLabel *labelImage;
    QPushButton *buttonSelectImage;
    
    QPushButton *pushButtonModifier;
    QPushButton *pushButtonAnnuler;
};

#endif // MODIFYJOUEUR_H
