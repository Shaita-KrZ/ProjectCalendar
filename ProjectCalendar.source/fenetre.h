#ifndef FENETRE
#define FENETRE
#include "agenda.h"
#include "projets.h"

//page d'accueil
class accueil: public QWidget{
    Q_OBJECT
private:
    //interface graphique de l'agenda : agenda.h
    agenda *a;
    //interface graphique pour gérer un projet
    projetediteur *proj;

    QVBoxLayout *layout,*vbox1;
    //onglets page d'accueil
    QTabWidget *onglets;
    QLabel *label;
    QPushButton *quitter;
    //onglet 1 : presentation de l'application
    QWidget *presentation;
    //onglet 2 : emploi du temps
    QWidget *empTemps;
    //onglet 3 : gestion de projet
    QWidget *projet;
public:
    explicit accueil(QWidget *parent=0);
signals:
public slots:
};

#endif // FENETRE

