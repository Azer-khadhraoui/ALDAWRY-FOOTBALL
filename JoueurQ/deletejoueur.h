#ifndef DELETEJOUEUR_H
#define DELETEJOUEUR_H

#include <QDialog>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QLabel>

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
    QLineEdit *lineEdit;
    int joueurId;
};

#endif // DELETEJOUEUR_H
