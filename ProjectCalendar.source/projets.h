#ifndef PROJETS
#define PROJETS
#include <QtWidgets>
#include "calendar.h"

//Interface graphique gestion de projet
class projetediteur:public QWidget{
    Q_OBJECT
private:
    QGridLayout *couche;
    QVBoxLayout *couche1;
    //ajouter un projet
    QPushButton *ajouterprojet;
    QPushButton **boutonProjets;
    unsigned int nbProjetsMax;
    unsigned int nbProjets;
public:
    explicit projetediteur(unsigned int nb,QWidget *parent=0);
    void addBouton(QPushButton *B);
    QPushButton* operator[](unsigned int i){return boutonProjets[i];}
signals:
public slots:
    void chargerProjet();
    void ouvrirProjet();
};

#endif // PROJETS

