#ifndef GESTIONPROJETS_H
#define GESTIONPROJETS_H
#include <QWidget>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include "projetmanager.h"
#include <QFileDialog>
#include <QInputDialog>

class Gestionprojets : public QWidget
{
    Q_OBJECT

public:
    explicit Gestionprojets(unsigned int nb,QWidget *parent = 0);
    void addBouton(QPushButton *B);
    void supprimerBouton(unsigned int i);
private:
    QGridLayout *couche;
    QLabel *presentation;
    QPushButton *supprimerProjet;
    QPushButton *creeProjet;
    QPushButton *importerProjet;
    QVBoxLayout *listeProjets;
    QPushButton **boutonProjets;
    unsigned int nbProjetsMax;
    unsigned int nbProjets;
public slots:
    void chargerProjet();
    void ouvrirProjet();
    void supprimeProjet();
};

#endif // GESTIONPROJETS_H
