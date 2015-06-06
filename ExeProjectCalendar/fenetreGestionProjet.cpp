#include "fenetreGestionProjet.h"



Gestionprojets::Gestionprojets(unsigned int nb,QWidget *parent):QWidget(parent),nbProjets(0),nbProjetsMax(nb),boutonProjets(new QPushButton*[nb])
{
    couche=new QGridLayout(this);
    listeProjets=new QVBoxLayout();
    presentation=new QLabel("Liste de vos projets");
    creeProjet=new QPushButton("Créer un projet vide");
    importerProjet=new QPushButton("Importer un Projet");
    supprimerProjet=new QPushButton("Supprimer un projet");
    couche->addWidget(presentation,0,1);
    couche->addWidget(creeProjet,1,0);
    couche->addWidget(importerProjet,2,0);
    couche->addWidget(supprimerProjet,3,0);
    couche->addLayout(listeProjets,1,1,3,1);
    //QObject::connect(creeProjet,SIGNAL(clicked()),this,SLOT(creeProjet()));
    QObject::connect(supprimerProjet,SIGNAL(clicked()),this,SLOT(supprimeProjet()));
    QObject::connect(importerProjet,SIGNAL(clicked()),this,SLOT(chargerProjet()));
}

void Gestionprojets::addBouton(QPushButton *B){
    if (nbProjets==nbProjetsMax){
        QPushButton** newtab=new QPushButton*[nbProjetsMax+10];
        for(unsigned int i=0; i<nbProjets; i++) newtab[i]=boutonProjets[i];
        nbProjetsMax+=10;
        QPushButton** old=boutonProjets;
        boutonProjets=newtab;
        delete[] old;
    }
    boutonProjets[nbProjets++]=B;
    listeProjets->addWidget(B);
}

void Gestionprojets::supprimeProjet(){
    ProjetManager &PM=ProjetManager::getInstance();
    unsigned int i=0,j;
    bool ok;
    QString titreProjetSupp=QInputDialog::getText(this,"Projet a supprimer","Entrez le titre du projet a supprimer",QLineEdit::Normal, QString(),&ok);
    if(ok && !titreProjetSupp.isEmpty()){
        try{
            PM.getProjet(titreProjetSupp);
        }catch(CalendarException& e){QMessageBox::critical(this, "Supprimer un projet", e.getInfo());return;}
        map<QString,Projet*> projets=PM.getProjets();
        map<QString,Projet*>::iterator it=projets.begin();
        while(it->first!=titreProjetSupp){
            ++it;
            i++;
        }
        qDebug()<<QString::number(i);
        listeProjets->removeWidget(boutonProjets[i]);
        QPushButton *temp=boutonProjets[i];
        while(i<nbProjets-1){
            j=i;
            j++;
            boutonProjets[i]=boutonProjets[j];
            i++;
        }
        boutonProjets[nbProjets-1]=temp;
        delete boutonProjets[nbProjets-1];
        nbProjets--;
        PM.supprimerProjet(titreProjetSupp);
    }
    else {
        QMessageBox::critical(this, "Supprimer un projet", "Vous n'avez pas entrer de projet");
    }
}

void Gestionprojets::chargerProjet(){
    QString chemin = QFileDialog::getOpenFileName(this, "Charger un projet", QString(), "Fichiers (*.xml)");
    ProjetManager &PM=ProjetManager::getInstance();
    if(!chemin.isEmpty()){
        //On charge le projet
        try{
            PM.load(chemin);
        }catch(CalendarException &e){ qDebug()<<e.getInfo();return;}
        QPushButton *Proj=new QPushButton();
        map<QString,Projet *> projets=PM.getProjets();
        Projet *P=projets.rbegin()->second;
        qDebug()<<P->getTitre();
        Proj->setText(P->getTitre());
        addBouton(Proj);
        //On connecte le bouton à l'ouverture du projet
        QObject::connect(Proj,SIGNAL(clicked()),this,SLOT(ouvrirProjet()));
        QMessageBox::information(this,"Projet","Vous avez bien ajouter le projet : "+P->getTitre());
    }
    else{
        QMessageBox::information(this,"Projet","Le projet n'a pas été chargé");
    }
}

void Gestionprojets::ouvrirProjet(){
    QObject *emetteur =sender();
    QPushButton *emetteurCasted=qobject_cast<QPushButton*>(emetteur);
    unsigned int i=0,j=0;
     //On recherche dans la liste des boutons le bouton sur lequel on a appuyé
     while(boutonProjets[i]!=emetteurCasted)i++;

     ProjetManager &PM=ProjetManager::getInstance();
     map<QString,Projet*> projets=PM.getProjets();
     map<QString,Projet*>::iterator iter=projets.begin();
     while(j!=i){
         j++;
         ++iter;
     }
     Projet *P=iter->second;
     TacheManager &T=P->getTaches();
     QWidget *Fenetreprojet= new QWidget();
     QGridLayout *grid=new QGridLayout(Fenetreprojet);
     QLabel *titreProjet=new QLabel(P->getTitre());
     QLabel *echeanceProjet=new QLabel(P->getEcheance().toString());
     QPushButton *modifierProjet=new QPushButton("Modifier le projet");
     grid->addWidget(titreProjet,0,0,1,1);
     grid->addWidget(echeanceProjet,1,0,1,1);
     grid->addWidget(modifierProjet,2,0,1,1);
     QLabel **identificateurTache=new QLabel*[T.getTaches().size()];
     QLabel **caracteristiqueTache=new QLabel*[T.getTaches().size()];

     int k=0;
     map<QString, Tache*> taches=T.getTaches();
     map<QString, Tache*>::iterator it;
     for(it=taches.begin();it!=taches.end();++it){
         identificateurTache[k]=new QLabel("Identificateur Tache "+QString::number(k)+" : "+it->first);
         Tache *t=it->second;
         caracteristiqueTache[k]=new QLabel("     Titre : "+t->getTitre()+"\n     "+"Echeance : "+t->getDisponibilite().toString()+
                                           "\n     "+"Duree :"+QString::number(t->getDuree().getDureeEnMinutes())+" minutes");
         k++;
     }
     for(k=0;k<T.getTaches().size();k++){
         grid->addWidget(identificateurTache[k],2+10*k,1,2,3);
         grid->addWidget(caracteristiqueTache[k],4+10*k,2,6,6);
     }
     Fenetreprojet->show();
}