#include "fenetreGestionProjet.h"

Gestionprojets::Gestionprojets(QWidget *parent):QWidget(parent)
{
    couche=new QGridLayout(this);
    titreProjetLine=new QLineEdit();
    listeProjets=new QVBoxLayout();
    presentation=new QLabel("Liste de vos projets");
    creeProjet=new QPushButton("Créer un projet vide");
    importerProjet=new QPushButton("Importer un Projet");
    supprimerProjet=new QPushButton("Supprimer un projet");
    titreProjet=new QLabel();
    couche->addWidget(presentation,0,1);
    couche->addWidget(creeProjet,1,0);
    couche->addWidget(importerProjet,2,0);
    couche->addWidget(supprimerProjet,3,0);
    couche->addLayout(listeProjets,1,1,3,1);
    QObject::connect(creeProjet,SIGNAL(clicked()),this,SLOT(creationProjet()));
    QObject::connect(supprimerProjet,SIGNAL(clicked()),this,SLOT(supprimeProjet()));
    QObject::connect(importerProjet,SIGNAL(clicked()),this,SLOT(chargerProjet()));
}

QPushButton* Gestionprojets::trouverBouton(const QString& titre){
    return boutonProjets[titre];
}

void Gestionprojets::addBouton(const QString& titre){
    QPushButton *B=new QPushButton(titre);
    boutonProjets[titre]=B;
    listeProjets->addWidget(B);
    QObject::connect(B,SIGNAL(clicked()),this,SLOT(ouvrirProjet()));
}

void Gestionprojets::supprimerBouton(const QString& titre){
    listeProjets->removeWidget(boutonProjets[titre]);
    delete boutonProjets[titre];
    boutonProjets.erase(titre);
}

void Gestionprojets::supprimeProjet(){
    ProjetManager &PM=ProjetManager::getInstance();
    bool ok;
    QString titreProjetSupp=QInputDialog::getText(this,"Projet a supprimer","Entrez le titre du projet a supprimer",QLineEdit::Normal, QString(),&ok);
    if(ok && !titreProjetSupp.isEmpty()){
        try{
            PM.getProjet(titreProjetSupp);
        }catch(CalendarException& e){QMessageBox::critical(this, "Supprimer un projet", e.getInfo());return;}
        supprimerBouton(titreProjetSupp);
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
        }catch(CalendarException &e){ QMessageBox::critical(this,"Projet",e.getInfo());return;}
        QPushButton *Proj=new QPushButton();
        map<QString,Projet *> projets=PM.getProjets();
        Projet *P=projets.rbegin()->second;
        Proj->setText(P->getTitre());
        addBouton(P->getTitre());
        //On connecte le bouton à l'ouverture du projet
        QMessageBox::information(this,"Projet","Vous avez bien ajouter le projet : "+P->getTitre());
    }
    else{
        QMessageBox::information(this,"Projet","Le projet n'a pas été chargé");
    }
}

void Gestionprojets::ouvrirProjet(){
    QObject *emetteur =sender();
    QPushButton *emetteurCasted=qobject_cast<QPushButton*>(emetteur);
    unsigned int j=0;
     //On recherche dans la liste des boutons le bouton sur lequel on a appuyé
     map<QString,QPushButton*>::iterator itB=boutonProjets.begin();
     QString titreP;
     while(itB->second!=emetteurCasted)++itB;
     titreP=itB->first;
     ProjetManager &PM=ProjetManager::getInstance();
     map<QString,Projet*> projets=PM.getProjets();
     map<QString,Projet*>::iterator iter=projets.begin();
     while(iter->first!=titreP){
         ++iter;
     }
     Projet *P=iter->second;
     TacheManager T=P->getTaches();
     Fenetreprojet= new QWidget();
     QGridLayout *grid=new QGridLayout(Fenetreprojet);
     titreProj=P->getTitre();
     titreProjet=new QLabel(P->getTitre());

     QLabel *echeanceProjet=new QLabel(P->getEcheance().toString());
     QPushButton *modifierProjet=new QPushButton("Modifier le titre du projet");
     QPushButton *ajouterTache=new QPushButton("Ajouter une tache");
     QObject::connect(ajouterTache,SIGNAL(clicked()),this,SLOT(ajouterTache()));
     QObject::connect(modifierProjet,SIGNAL(clicked()),this,SLOT(modifierTitreProjet()));
     grid->addWidget(titreProjet,0,0,1,1);
     grid->addWidget(echeanceProjet,1,0,1,1);
     grid->addWidget(modifierProjet,2,0,1,1);
     grid->addWidget(ajouterTache,3,0,1,1);
     QLabel **identificateurTache=new QLabel*[T.getTaches().size()];
     QLabel **caracteristiqueTache=new QLabel*[T.getTaches().size()];
     QLabel **caracteristiqueTacheUnitaireComposee;
     unsigned int k=0,nbTu=0;
     j=0;
     map<QString, Tache*> taches=T.getTaches();
     map<QString, Tache*>::iterator it;
     for(it=taches.begin();it!=taches.end();++it){
         QPushButton *B=new QPushButton();
         identificateurTache[k]=new QLabel("Identificateur Tache "+QString::number(k+1)+" : "+it->first);
         B->setText("Modifier la tache : "+it->first);
         boutonModifTache[it->first]=B;
         QObject::connect(boutonModifTache[it->first],SIGNAL(clicked()),this,SLOT(modifierTache()));
         grid->addWidget(identificateurTache[k],2+10*j,1,2,3);
         grid->addWidget(B,2+10*j,4,2,3);
         Tache *t=it->second;
         if(t->estComposite()){
             TacheComposite *tCompo=dynamic_cast<TacheComposite*>(t);
             map<QString,Tache*>taches=tCompo->getTaches();
             map<QString,Tache*>::const_iterator it;
             caracteristiqueTache[k]=new QLabel("     Titre : "+t->getTitre()+"\n     "+"Disponibilite : "+t->getDisponibilite().toString()+"\n     "+
                                                "Echenace : "+t->getEcheance().toString()+"     Duree :"+QString::number(t->getDuree().getDureeEnMinutes())+" minutes");
             grid->addWidget(caracteristiqueTache[k],4+10*j,2,6,6);
             caracteristiqueTacheUnitaireComposee=new QLabel*[taches.size()];
             for(it=taches.begin();it!=taches.end();++it){
                QString preemptive=(it->second->isPreemptive() == true? "true" : "false");
                caracteristiqueTacheUnitaireComposee[nbTu]=new QLabel("     Identificateur : "+it->first+"\n     "+"Preemptive : "+preemptive+"\n     "+"Titre : "+it->second->getTitre()+
                                                                "\n     "+"Disponibilite : "+it->second->getDisponibilite().toString()+"\n     "+
                                                                 "Echenace : "+it->second->getEcheance().toString()+"     Duree :"+QString::number(it->second->getDuree().getDureeEnMinutes())+" minutes");

                j++;
                grid->addWidget(caracteristiqueTacheUnitaireComposee[nbTu],2+10*j,4,6,6);
                nbTu++;
             }
         }
         else{
            QString preemptive=(t->isPreemptive() == true? "true" : "false");
            caracteristiqueTache[k]=new QLabel("     Preemptive : "+ preemptive +"\n     "+"Titre : "+t->getTitre()+"\n     "+"Disponibilite : "+t->getDisponibilite().toString()+"\n     "+
                                            "Echenace : "+t->getEcheance().toString()+"Duree :"+QString::number(t->getDuree().getDureeEnMinutes())+" minutes");

            grid->addWidget(caracteristiqueTache[k],4+10*j,2,6,6);
         }
         j++;
         k++;
     }
     Fenetreprojet->show();
}

void Gestionprojets::creationProjet(){
    fenetreCreeProjet=new QWidget();
    QVBoxLayout *couche1=new QVBoxLayout(fenetreCreeProjet);
    QLabel *titreProjetLabel=new QLabel("Entrez le titre du projet");
    QLabel *echeanceProjetLabel=new QLabel("Entrez la date d'échenace du projet");
    echeanceProjetLine=new QDateTimeEdit(QDate::currentDate());
    echeanceProjetLine->setMinimumDate(QDate::currentDate().addDays(-365));
    echeanceProjetLine->setMaximumDate(QDate::currentDate().addDays(365));
    echeanceProjetLine->setDisplayFormat("dd.mm.yyyy");
    QPushButton *valider=new QPushButton("OK");
    QPushButton *annuler=new QPushButton("Annuler");
    QHBoxLayout *couche2=new QHBoxLayout();
    couche2->addWidget(valider);
    couche2->addWidget(annuler);
    couche1->addWidget(titreProjetLabel);
    couche1->addWidget(titreProjetLine);
    couche1->addWidget(echeanceProjetLabel);
    couche1->addWidget(echeanceProjetLine);
    couche1->addLayout(couche2);
    QObject::connect(valider,SIGNAL(clicked()),this,SLOT(validerProjet()));
    QObject::connect(annuler,SIGNAL(clicked()),this,SLOT(annulerProjet()));
    fenetreCreeProjet->show();
}

void Gestionprojets::validerProjet(){

    ProjetManager &PM=ProjetManager::getInstance();
    QString titreProjet=titreProjetLine->text();
    QDate echeanceProjet=echeanceProjetLine->date();
    try{
        PM.projetExistdeja(titreProjetLine->text());
    }catch(CalendarException &e){ QMessageBox::critical(this, "Creation du projet", e.getInfo()); return;}
    PM.creerProjet(titreProjet,echeanceProjet);
    addBouton(titreProjet);
    QMessageBox::information(this,"Creation projet","Le projet a été ajouté");
    titreProjetLine->setText("");
    fenetreCreeProjet->close();
}

void Gestionprojets::annulerProjet(){
     QMessageBox::critical(this, "Creation du projet", "Le projet n'a pas été créé");
}



void Gestionprojets::modifierTitreProjet(){
    fenetreTitreProjet=new QWidget();
    QVBoxLayout *couche=new QVBoxLayout(fenetreTitreProjet);
    QLabel *titreProjetLabel=new QLabel("Entrez le titre du projet");
    QPushButton *valider=new QPushButton("OK");
    QPushButton *annuler=new QPushButton("Annuler");
    QHBoxLayout *couche1=new QHBoxLayout();
    couche1->addWidget(valider);
    couche1->addWidget(annuler);
    couche->addWidget(titreProjetLabel);
    couche->addWidget(titreProjetLine);
    couche->addLayout(couche1);
    QObject::connect(valider,SIGNAL(clicked()),this,SLOT(validerTitreProjet()));
    QObject::connect(annuler,SIGNAL(clicked()),this,SLOT(annulerTitreProjet()));
    fenetreTitreProjet->show();
}

void Gestionprojets::validerTitreProjet(){
    ProjetManager &PM=ProjetManager::getInstance();
    try{
        PM.projetExistdeja(titreProjetLine->text());
    }catch(CalendarException &e){ QMessageBox::critical(this, "Modifier le titre du projet", e.getInfo());return;}
    PM.modifierNomProjet(titreProj,titreProjetLine->text());
    QMessageBox::information(this,"Creation projet","Le titre du projet a bien été ajouté été ajouté");
    titreProjet->setText(titreProjetLine->text());
    supprimerBouton(titreProj);
    addBouton(titreProjetLine->text());
    titreProjetLine->setText("");
    fenetreTitreProjet->close();
}

void Gestionprojets::annulerTitreProjet(){
    QMessageBox::critical(this, "Modifier le titre du projet", "Le titre du projet n'a pas été modifié");
    fenetreTitreProjet->close();
}

void Gestionprojets::modifierTache(){
     fenetreModifTache=new QWidget();
     QVBoxLayout *couche=new QVBoxLayout(fenetreModifTache);
     QObject *emetteur =sender();
     QPushButton *emetteurCasted=qobject_cast<QPushButton*>(emetteur);
     //On recherche dans la liste des boutons le bouton sur lequel on a appuyé
     map<QString,QPushButton*>::iterator itB=boutonModifTache.begin();
     while(itB->second!=emetteurCasted)++itB;
     ProjetManager &PM=ProjetManager::getInstance();
     map<QString,Projet*> projets=PM.getProjets();
     Projet *P=projets[titreProj];
     TacheManager TM=P->getTaches();
     map<QString,Tache*>taches=TM.getTaches();
     TacheaModif=taches[itB->first];
     QHBoxLayout *couche0=new QHBoxLayout();
     QLabel *idTache=new QLabel("Modifier la tache : "+TacheaModif->getID());
     couche0->addWidget(idTache);
     couche->addLayout(couche0);
     QHBoxLayout *couche1=new QHBoxLayout();
     QLabel *titreTacheLabel=new QLabel("Titre : ");
     titreTacheLine=new QLineEdit(TacheaModif->getTitre());
     preemptive=new QCheckBox("Preemptive");//utiliser signal stateChanged
     couche1->addWidget(titreTacheLabel);
     couche1->addWidget(titreTacheLine);
     couche1->addWidget(preemptive);
     couche->addLayout(couche1);

     QHBoxLayout *couche2=new QHBoxLayout();
     QLabel *dateDispoTacheLabel=new QLabel("Disponibilite :");
     dateDispoTacheLine=new QDateTimeEdit(TacheaModif->getDisponibilite());
     dateDispoTacheLine->setMinimumDate(QDate::currentDate().addDays(-365));
     dateDispoTacheLine->setMaximumDate(QDate::currentDate().addDays(365));
     dateDispoTacheLine->setDisplayFormat("dd.mm.yyyy");
     QLabel *dateEcheTacheLabel=new QLabel("Echeance :");
     dateEcheTacheLine=new QDateTimeEdit(TacheaModif->getEcheance());
     dateEcheTacheLine->setMinimumDate(QDate::currentDate().addDays(-365));
     dateEcheTacheLine->setMaximumDate(QDate::currentDate().addDays(365));
     dateEcheTacheLine->setDisplayFormat("dd.mm.yyyy");
     couche2->addWidget(dateDispoTacheLabel);
     couche2->addWidget(dateDispoTacheLine);
     couche2->addWidget(dateEcheTacheLabel);
     couche2->addWidget(dateEcheTacheLine);
     couche->addLayout(couche2);
     if(TacheaModif->estComposite()){
            QPushButton *ajouterTache=new QPushButton("Ajouter une tache");
            QObject::connect(ajouterTache,SIGNAL(clicked()),this,SLOT(ajouterTache()));
            couche0->addWidget(ajouterTache);
            TacheComposite *tc=dynamic_cast<TacheComposite*>(TacheaModif);
            map<QString,Tache*>taches=tc->getTaches();
            map<QString,Tache*>::iterator it;
            unsigned int i=0;

            titreTacheCompoLine=new QLineEdit*[taches.size()];
            dateDispoTacheCompoLine=new QDateTimeEdit*[taches.size()];
            dateEcheTacheCompoLine=new QDateTimeEdit*[taches.size()];
            dureeTacheCompoLine=new QSpinBox*[taches.size()];
            preemptiveCompo=new QCheckBox*[taches.size()];
            QLabel **idTacheCompo=new QLabel*[taches.size()];
            QLabel **dateDispoTacheCompoLabel=new QLabel*[taches.size()];
            QHBoxLayout **coucheCompo1=new QHBoxLayout*[taches.size()];
            QHBoxLayout **coucheCompo2=new QHBoxLayout*[taches.size()];
            QHBoxLayout **coucheCompo3=new QHBoxLayout*[taches.size()];

            QVBoxLayout **coucheCompo=new QVBoxLayout*[taches.size()];
            QLabel **dateEcheTacheCompoLabel=new QLabel*[taches.size()];
            QLabel **titreTacheCompoLabel=new QLabel*[taches.size()];
            QLabel **dureeTacheCompoLabel=new QLabel*[taches.size()];

            for(it=taches.begin();it!=taches.end();++it){

                idTacheCompo[i]=new QLabel("\n\nModifier la tache : "+it->second->getID());
                coucheCompo[i]=new QVBoxLayout();
                coucheCompo[i]->addWidget(idTacheCompo[i]);
                titreTacheCompoLabel[i]=new QLabel("Titre : ");
                titreTacheCompoLine[i]=new QLineEdit(it->second->getTitre());
                preemptiveCompo[i]=new QCheckBox("Preemptive");//utiliser signal stateChanged
                coucheCompo1[i]=new QHBoxLayout();
                coucheCompo1[i]->addWidget(titreTacheCompoLabel[i]);
                coucheCompo1[i]->addWidget(titreTacheCompoLine[i]);
                coucheCompo1[i]->addWidget(preemptiveCompo[i]);
                coucheCompo[i]->addLayout(coucheCompo1[i]);
                dateDispoTacheCompoLabel[i]=new QLabel("Disponibilite :");
                dateDispoTacheCompoLine[i]=new QDateTimeEdit(it->second->getDisponibilite());
                dateDispoTacheCompoLine[i]->setMinimumDate(QDate::currentDate().addDays(-365));
                dateDispoTacheCompoLine[i]->setMaximumDate(QDate::currentDate().addDays(365));
                dateDispoTacheCompoLine[i]->setDisplayFormat("dd.mm.yyyy");
                dateEcheTacheCompoLabel[i]=new QLabel("Echeance :");
                dateEcheTacheCompoLine[i]=new QDateTimeEdit(it->second->getEcheance());
                dateEcheTacheCompoLine[i]->setMinimumDate(QDate::currentDate().addDays(-365));
                dateEcheTacheCompoLine[i]->setMaximumDate(QDate::currentDate().addDays(365));
                dateEcheTacheCompoLine[i]->setDisplayFormat("dd.mm.yyyy");
                coucheCompo2[i]=new QHBoxLayout();
                coucheCompo2[i]->addWidget(dateDispoTacheCompoLabel[i]);
                coucheCompo2[i]->addWidget(dateDispoTacheCompoLine[i]);
                coucheCompo2[i]->addWidget(dateEcheTacheCompoLabel[i]);
                coucheCompo2[i]->addWidget(dateEcheTacheCompoLine[i]);
                coucheCompo[i]->addLayout(coucheCompo2[i]);
                dureeTacheCompoLabel[i]=new QLabel("Duree (en minutes) :");
                dureeTacheCompoLine[i]=new QSpinBox();
                dureeTacheCompoLine[i]->setSingleStep(5);
                dureeTacheCompoLine[i]->setMaximum(1000);
                dureeTacheCompoLine[i]->setMinimum(0);
                dureeTacheCompoLine[i]->setValue(it->second->getDuree().getDureeEnMinutes());
                coucheCompo3[i]=new QHBoxLayout();
                coucheCompo3[i]->addWidget(dureeTacheCompoLabel[i]);
                coucheCompo3[i]->addWidget(dureeTacheCompoLine[i]);
                coucheCompo[i]->addLayout(coucheCompo3[i]);
                couche->addLayout(coucheCompo[i]);
                i++;

        }


     }
     else{
            QHBoxLayout *couche3=new QHBoxLayout();
            QLabel *dureeTacheLabel=new QLabel("Duree (en minutes) :");
            dureeTacheLine=new QSpinBox();
            dureeTacheLine->setSingleStep(5);
            dureeTacheLine->setMaximum(1000);
            dureeTacheLine->setMinimum(0);
            dureeTacheLine->setValue(TacheaModif->getDuree().getDureeEnMinutes());
            couche3->addWidget(dureeTacheLabel);
            couche3->addWidget(dureeTacheLine);
            couche->addLayout(couche3);
     }

     QHBoxLayout *couche4=new QHBoxLayout();
     QPushButton *valider=new QPushButton("OK");
     QPushButton *annuler=new QPushButton("Annuler");
     couche4->addWidget(valider);
     couche4->addWidget(annuler);
     couche->addLayout(couche4);
     QObject::connect(valider,SIGNAL(clicked()),this,SLOT(validermodifTache()));
     QObject::connect(annuler,SIGNAL(clicked()),this,SLOT(annulermodifTache()));
     fenetreModifTache->show();
}

void Gestionprojets::validermodifTache(){
    Fenetreprojet->close();
    ProjetManager &PM=ProjetManager::getInstance();
    map<QString,Projet*> projets=PM.getProjets();
    Projet *P=projets[titreProj];
    TacheManager TM=P->getTaches();
    map<QString,Tache*>taches=TM.getTaches();
    TacheaModif->setTitre(titreTacheLine->text());
    TacheaModif->setDispo(dateDispoTacheLine->date());
    TacheaModif->setEche(dateEcheTacheLine->date());
    qDebug()<<titreTacheLine->text();
    if(TacheaModif->estComposite()){
        TacheComposite *Tc=dynamic_cast<TacheComposite*>(TacheaModif);
        map<QString,Tache*>taches=Tc->getTaches();
        map<QString,Tache*>::iterator it;
        unsigned int i=0;
        for(it=taches.begin();it!=taches.end();++it){
            TacheUnitaire *Tu=dynamic_cast<TacheUnitaire*>(it->second);
            Tu->setTitre(titreTacheCompoLine[i]->text());
            Tu->setDispo(dateDispoTacheCompoLine[i]->date());
            Tu->setEche(dateEcheTacheCompoLine[i]->date());
            unsigned int duree=dureeTacheCompoLine[i]->value();
            Duree d(duree);
            Tu->setDuree(d);
            i++;
        }

    }
    else {
        TacheUnitaire *Tu=dynamic_cast<TacheUnitaire*>(TacheaModif);
        unsigned int duree=dureeTacheLine->value();
        Duree d(duree);
        Tu->setDuree(d);
    }
    taches[TacheaModif->getID()]=TacheaModif;
    fenetreModifTache->close();
    QMessageBox::information(this,"Creation projet","Le titre du projet a bien été ajouté été ajouté");
}



void Gestionprojets::annulermodifTache(){
    fenetreModifTache->close();
    QMessageBox::critical(this, "Modifier une tache", "La tache n'a pas été modifié");

}

void Gestionprojets::ajouterTache(){
    QWidget *fenetreAjouterTache=new QWidget();
    QPushButton *B=new QPushButton("test",fenetreAjouterTache);
    fenetreAjouterTache->show();
}


//RESTE A FAIRE DEMAIN
/*
Ajout une tache pour une tacheCompo
Ajout une tache pour un projet
Gérer le checkbox dans modifTache
*/

//RESTE A FAIRE PLUS TARD
/*
Lire les precedences dans load
Gérer les précédences
ExportSemaine
*/
