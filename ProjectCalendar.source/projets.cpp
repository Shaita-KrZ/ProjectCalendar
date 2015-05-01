#include "projets.h"
#include "calendar.h"

//constructeur graphique permettant la gestion de projet
projetediteur::projetediteur(unsigned int nb, QWidget *parent):QWidget(parent),nbProjets(0),nbProjetsMax(nb),boutonProjets(new QPushButton*[nb]){
    couche1=new QVBoxLayout();
    ajouterprojet=new QPushButton("Ajouter un projet");
    couche=new QGridLayout(parent);
    couche->addLayout(couche1,0,0);
    couche->addWidget(ajouterprojet,0,1);
    QObject::connect(ajouterprojet,SIGNAL(clicked()),this,SLOT(chargerProjet()));
}

void projetediteur::addBouton(QPushButton *B){
    if (nbProjets==nbProjetsMax){
        QPushButton** newtab=new QPushButton*[nbProjetsMax+10];
        for(unsigned int i=0; i<nbProjets; i++) newtab[i]=boutonProjets[i];
        nbProjetsMax+=10;
        QPushButton** old=boutonProjets;
        boutonProjets=newtab;
        delete[] old;
    }
    boutonProjets[nbProjets++]=B;
    couche1->addWidget(B);
}


//slot appelé lorsque l'on appuie sur le bouton Ajouter un projet
void projetediteur::chargerProjet(){
     //charger le fichier contenant les taches du projet
     QString chemin = QFileDialog::getOpenFileName(this, "Charger un projet", QString(), "Fichiers (*.xml)");
     //ouvrir une nouvelle fenetre pour entrez le nom du projet
     if(!chemin.isEmpty()){
         bool ok=false;
         QString identificateur=QInputDialog::getText(this,"Projet","Entrez le nom du projet :", QLineEdit::Normal,QString(),&ok);
         if(ok && !identificateur.isEmpty()){
             ProjetManager& PM=ProjetManager::getInstance();
             //On crée un projet (pointeur pour que la variable reste)
             Projet *p=new Projet;
             //Ce projet va lire toute ses taches à partir du fichier .xml
             p->load(chemin);
             //On donne un titre au projet
             p->setTitreProjet(identificateur);
             //On ajoute ce projet à la liste des projets
             PM.ajouterProjet(p);
             //On crée un nouveau bouton contenant le projet
             QPushButton *Proj=new QPushButton();
             Proj->setText(identificateur);
             addBouton(Proj);
             //On connecte le bouton à l'ouverture du projet
             QObject::connect(Proj,SIGNAL(clicked()),this,SLOT(ouvrirProjet()));
             QMessageBox::information(this,"Projet","Vous avez bien ajouter le projet : "+identificateur);
          }
          else{
             QMessageBox::information(this,"Projet","Le projet n'a pas été chargé");
           }
     }
     else{
         QMessageBox::information(this,"Projet","Le projet n'a pas été chargé");
     }
}

//slot permettant d'ouvrir le projet correspondant
void projetediteur::ouvrirProjet(){
    //recuperation du bouton sur lequel on a appuyer qui doit correspondre au projet
    QObject *emetteur =sender();
    QPushButton *emetteurCasted  = qobject_cast<QPushButton*>(emetteur);
    unsigned int i=0;
    //On recherche dans la liste des boutons le bouton sur lequel on a appuyé
    while(boutonProjets[i]!=emetteurCasted)i++;
    //On récupère l'instance ProjetManager contenant la liste des projets chargé
    ProjetManager& PM=ProjetManager::getInstance();
    //Projet récupéré
    Projet *Pr=PM[i];
    //On affiche toutes les taches dans une nouvelle fenetre
    QWidget *Fenetreprojet= new QWidget();
    QVBoxLayout *layout=new QVBoxLayout(Fenetreprojet);
    for(Projet::iterateur it=Pr->begin();it!=Pr->end();++it){
        Tache *t=*it;
        QLabel *l=new QLabel(t->getId());
        layout->addWidget(l);
    }
    Fenetreprojet->show();
}
