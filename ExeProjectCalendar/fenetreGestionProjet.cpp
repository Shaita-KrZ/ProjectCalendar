#include "fenetreGestionProjet.h"

/* ********************* INTERFACE GESTION DE PROJETS ********************** */

/* ********************* CONSTRUCTEUR ************************* */


Gestionprojets::Gestionprojets(QWidget *parent):QWidget(parent){
    m_bool=false;
    m_titreProj="";
    m_couche=new QVBoxLayout(this);
    m_fenetreProjet=new QWidget();
    /* *********** COUCHE 1 ******************* */
    m_presentation=new QLabel("Bienvenue sur l'interface de gestion de projets.");
    m_creeProjet=new QPushButton("Créer un projet vide");
    m_importerProjet=new QPushButton("Importer un Projet");
    m_supprimerProjet=new QPushButton("Supprimer un projet");
    m_couche->addWidget(m_presentation);
    m_couche->addWidget(m_creeProjet);
    m_couche->addWidget(m_importerProjet);
    m_couche->addWidget(m_supprimerProjet);
    m_listeProj=new QLabel("                    Liste de vos projets");
    m_couche->addWidget(m_listeProj);

    /* *********** SIGNAUX/SLOTS******************* */

    QObject::connect(m_creeProjet,SIGNAL(clicked()),this,SLOT(creationProjet()));
    QObject::connect(m_supprimerProjet,SIGNAL(clicked()),this,SLOT(supprimeProjet()));
    QObject::connect(m_importerProjet,SIGNAL(clicked()),this,SLOT(chargerProjet()));

    /* *********** WIDGET GLOBALESAS ******************* */
    m_titreProjet=new QLabel();
    //m_titreProjetLine=new QLineEdit();
}

/* ********************* FIN CONSTRUCTEUR ************************* */

/* ********************* FONCTIONS PUBLIQUES POUR LA GESTION DYNAMIQUE DES BOUTONS ********************** */

QPushButton* Gestionprojets::trouverBouton(const QString& titre){
    return m_boutonProjets[titre];
}
void Gestionprojets::ajouterBouton(const QString& titre){
    QPushButton *B=new QPushButton(titre);
    m_boutonProjets[titre]=B;
    m_couche->addWidget(B);
    QObject::connect(B,SIGNAL(clicked()),this,SLOT(ouvrirProjet()));
}

void Gestionprojets::supprimerBouton(const QString& titre){
    m_couche->removeWidget(m_boutonProjets[titre]);
    delete m_boutonProjets[titre];
    m_boutonProjets.erase(titre);
}

/* ********************* FIN FONCTIONS PUBLIQUES POUR LA GESTION DYNAMIQUE DES BOUTONS ********************** */

/* ********************* SUPPRIMER UN PROJET ********************** */

void Gestionprojets::supprimeProjet(){
    ProjetManager &PM=ProjetManager::getInstance();
    bool ok;
    QString titreProjetSupp=QInputDialog::getText(this,"Supprimer un projet","Entrez le titre du projet à supprimer : ",QLineEdit::Normal, QString(),&ok);
    if(ok && !titreProjetSupp.isEmpty()){
        //On test si le est présent, si il ne l'est pas getProj envoi un throw ("Le projet n'existe pas")
        try{
            PM.getProjet(titreProjetSupp);
        }catch(CalendarException& e){QMessageBox::critical(this, "Supprimer un projet", e.getInfo());return;}
        if(m_titreProj==titreProjetSupp)m_fenetreProjet->close();
        //On supprime le bouton
        supprimerBouton(titreProjetSupp);
        //On supprime le projet
        PM.supprimerProjet(titreProjetSupp);
    }
    else {
        QMessageBox::critical(this, "Supprimer un projet", "Vous n'avez pas entré un projet");
    }
}

/* ********************* FIN SUPPRIMER UN PROJET ********************** */

/* ********************* CHARGER UN PROJET (LOAD) ********************** */

void Gestionprojets::chargerProjet(){
    //On ouvre un une fenetre pour ouvrir le fichier xml à charger
    QString chemin = QFileDialog::getOpenFileName(this, "Charger un projet", QString(), "Fichiers (*.xml)");
    ProjetManager &PM=ProjetManager::getInstance();
    QString titre;
    if(!chemin.isEmpty()){
        //On charge le projet
        try{
            //load va envoyer un throw pour indiquer si le projet exiset déjà ou si y'a un probleme de lecture du fichier xml
            //load va lire le projet et l'ajouter dans le ProjetManager
            titre=PM.load(chemin);
        }catch(CalendarException &e){ QMessageBox::critical(this,"Projet",e.getInfo());return;}
        //On crée un nouveau bouton pour le nouveau projet
        QPushButton *boutonProj=new QPushButton();
        map<QString,Projet *> projets=PM.getProjets();
        //On récupère le titre du projet pour l'affecter au bouton
        map<QString,Projet*>::iterator it=projets.begin();
        while(it->first!=titre)++it;
        Projet *P=it->second;
        boutonProj->setText(P->getTitre());
        //On ajoute le bouton a la liste des boutons
        ajouterBouton(P->getTitre());
        //On connecte le bouton à l'ouverture du projet
        QMessageBox::information(this,"Projet","Vous avez bien ajouter le projet : "+P->getTitre());
    }
    else{
        QMessageBox::information(this,"Projet","Le projet n'a pas été chargé");
    }
}

/* ********************* FIN CHARGER UN PROJET (LOAD) ********************** */

/* ********************* OUVRIR UN PROJET ********************** */
//Dans l'ouverture d'un projet, on va récupérer :
//Le titre du projet que l'on ouvre : m_titreProj
//Le label avec le titre du projet (pour le modifier) : m_titreProjet
//La fenêtre d'ouverture de projet : m_fenetreProjet
//La liste des boutons permettant de modifier une tache : m_boutonModifTache
//La liste des boutons permettant d'ouvrir un projet : m_boutonProjets

void Gestionprojets::ouvrirProjet(){
    m_fenetreProjet->close();
    unsigned int j=0,k=0,nbTu=0;
    //j va servir pour l'affichage dynamique des informations
    //k va servir à incrémenter les widgets dynamiquement
    //nbTu va servir pour l'affichage dynamique des taches d'une tache Composte
    QString titreP;
    //sender() permet de récuperer le bouton sur lequel on a appuyer
    QObject *emetteur =sender();
    QPushButton *emetteurCasted=qobject_cast<QPushButton*>(emetteur);
     //On recherche dans la liste des boutons le bouton sur lequel on a appuyé
     map<QString,QPushButton*>::iterator itB=m_boutonProjets.begin();
     //Tant que le bouton est différent de celui sur lequel on a appuyé on incrémente
     while(itB->second!=emetteurCasted)++itB;
     //On récupère le titre du projet
     titreP=itB->first;
     ProjetManager &PM=ProjetManager::getInstance();
     map<QString,Projet*> projets=PM.getProjets();
     // On recherche dans la liste des projets le projet correspondant au bouton
     map<QString,Projet*>::iterator iter=projets.begin();
     while(iter->first!=titreP){
         ++iter;
     }
     // On récupère le projet correspondant
     Projet *P=iter->second;
     TacheManager T=P->getTaches();
     QPushButton *ajoutPrecedence=new QPushButton("Ajouter une precedence");
     QPushButton *sauvegarderProjet=new QPushButton("Sauevgarder le projet");
     QObject::connect(sauvegarderProjet,SIGNAL(clicked()),this,SLOT(sauvegarderProjet()));
     QLabel *listePrecedence=new QLabel("Liste des precedences :");
     QObject::connect(ajoutPrecedence,SIGNAL(clicked()),this,SLOT(ajouterPrecedence()));
     QLabel **precedence=new QLabel*[T.getTaches().size()];
     m_fenetreProjet= new QWidget();
     QGridLayout *grid=new QGridLayout(m_fenetreProjet);
     PrecedenceManager &precedenceM=P->getPrecedences();
     unsigned int iP=0;
     for(PrecedenceManager::pmIterator itP=precedenceM.begin();itP!=precedenceM.end();++itP){
        Precedence *prec=itP.getCurrent();
         const Tache *succ=prec->getSuccesseur();
         const Tache *pred=prec->getPredecesseur();

         precedence[iP]=new QLabel("La tache "+pred->getID()+" précède la tache "+succ->getID());
         grid->addWidget(precedence[iP],8+iP,0,1,1);
         iP++;
     }

     m_titreProj=P->getTitre(); //titreProj va permet de récupérer le titre du projet pour le modifier
     m_titreProjet=new QLabel(P->getTitre());
     QLabel *echeanceProjet=new QLabel(P->getEcheance().toString());
     QPushButton *modifierProjet=new QPushButton("Modifier le titre du projet");
     QPushButton *ajouterTache=new QPushButton("Ajouter une tache");
     QObject::connect(ajouterTache,SIGNAL(clicked()),this,SLOT(ajouterTache()));
     QObject::connect(modifierProjet,SIGNAL(clicked()),this,SLOT(modifierTitreProjet()));
     grid->addWidget(m_titreProjet,0,0,1,1);
     grid->addWidget(echeanceProjet,1,0,1,1);
     grid->addWidget(modifierProjet,2,0,1,1);
     grid->addWidget(ajouterTache,3,0,1,1);
     grid->addWidget(sauvegarderProjet,4,0,1,1);
     grid->addWidget(ajoutPrecedence,5,0,1,1);
     grid->addWidget(listePrecedence,6,0,1,1);
     QLabel **identificateurTache=new QLabel*[T.getTaches().size()];
     QLabel **caracteristiqueTache=new QLabel*[T.getTaches().size()];
     QLabel **caracteristiqueTacheUnitaireComposee;
     //On récupere les taches du projet
     map<QString, Tache*> taches=T.getTaches();
     map<QString, Tache*>::iterator it;

     for(it=taches.begin();it!=taches.end();++it){
         //On crée un bouton pour modifier la tache
         QPushButton *B=new QPushButton("Modifier la tache : "+it->first);
         identificateurTache[k]=new QLabel("Identificateur Tache "+QString::number(k+1)+" : "+it->first);
         m_boutonModifTache[it->first]=B;
         QObject::connect(m_boutonModifTache[it->first],SIGNAL(clicked()),this,SLOT(modifierTache()));
         grid->addWidget(identificateurTache[k],2+10*j,1,2,3);
         grid->addWidget(B,2+10*j,4,2,3);
         //On récupère la tache
         Tache *t=it->second;
         if(t->estComposite()){

             TacheComposite *tCompo=dynamic_cast<TacheComposite*>(t);
             map<QString,Tache*>taches=tCompo->getTaches();
             map<QString,Tache*>::const_iterator it;
             caracteristiqueTache[k]=new QLabel("     Titre : "+t->getTitre()+"\n     "+"Disponibilite : "+t->getDisponibilite().toString()+"\n     "+
                                                "Echenace : "+t->getEcheance().toString()+"     Duree :"+QString::number(t->getDuree().getDureeEnMinutes())+" minutes");
             grid->addWidget(caracteristiqueTache[k],4+10*j,2,6,6);
             caracteristiqueTacheUnitaireComposee=new QLabel*[taches.size()];
             //On affiche les taches de la tache composite
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
     m_fenetreProjet->show();
}

/* ********************* FIN OUVRIR UN PROJET ********************** */

/* ********************* CREER UN PROJET ********************** */

void Gestionprojets::creationProjet(){
    //Nouvelle fenêtre avec un formulaire permettant de créer un projet
    //On créer un projet de base avec un nom et une date d'échéance
    m_fenetreCreeProjet=new QWidget();
    m_titreProjetLine=new QLineEdit();
    QVBoxLayout *couche1=new QVBoxLayout(m_fenetreCreeProjet);
    QLabel *titreProjetLabel=new QLabel("Entrez le titre du projet");
    QLabel *echeanceProjetLabel=new QLabel("Entrez la date d'échenace du projet");
    m_echeanceProjetLine=new QDateTimeEdit(QDate::currentDate());
    m_echeanceProjetLine->setMinimumDate(QDate::currentDate().addDays(-365));
    m_echeanceProjetLine->setMaximumDate(QDate::currentDate().addDays(365));
    m_echeanceProjetLine->setDisplayFormat("dd.mm.yyyy");
    QPushButton *valider=new QPushButton("OK");
    QPushButton *annuler=new QPushButton("Annuler");
    QHBoxLayout *couche2=new QHBoxLayout();
    couche2->addWidget(valider);
    couche2->addWidget(annuler);
    couche1->addWidget(titreProjetLabel);
    couche1->addWidget(m_titreProjetLine);
    couche1->addWidget(echeanceProjetLabel);
    couche1->addWidget(m_echeanceProjetLine);
    couche1->addLayout(couche2);
    QObject::connect(valider,SIGNAL(clicked()),this,SLOT(validerCreationProjet()));
    QObject::connect(annuler,SIGNAL(clicked()),this,SLOT(annulerCreationProjet()));
    m_fenetreCreeProjet->show();
}

void Gestionprojets::validerCreationProjet(){
    ProjetManager &PM=ProjetManager::getInstance();
    //On récupère le titre entré par l'utilisateur
    QString titreProjet=m_titreProjetLine->text();
    //On récupère la date
    QDate echeanceProjet=m_echeanceProjetLine->date();
    try{
        //Si le projet exist déjà on envoi un message d'erreur
        PM.projetExistdeja(titreProjet);
        PM.creerProjet(titreProjet,echeanceProjet);
    }catch(CalendarException &e){ QMessageBox::critical(this, "Creation d'un' projet", e.getInfo()); return;}
    //On ajoute un bouton avec le nouveau projet
    ajouterBouton(titreProjet);
    m_fenetreCreeProjet->close();
    QMessageBox::information(this,"Creation d'un projet","Le projet a été ajouté");
}

void Gestionprojets::annulerCreationProjet(){
    m_fenetreCreeProjet->close();
     QMessageBox::critical(this, "Creation d'un projet", "Le projet n'a pas été créé");
}

/* ********************* FIN CREER UN PROJET ********************** */

/* ********************* MODIFIER CREER UN PROJET ********************** */

void Gestionprojets::modifierTitreProjet(){
    ProjetManager &PM=ProjetManager::getInstance();
    bool ok;
    QString nouveauTitreProjet=QInputDialog::getText(this,"Modifier le titre d'un projet","Entrez le nouveau titre du projet",QLineEdit::Normal,QString(),&ok);
    if(ok && !nouveauTitreProjet.isEmpty()){
        try{
            PM.projetExistdeja(nouveauTitreProjet);
        }catch(CalendarException &e){ QMessageBox::critical(this, "Modifier le titre du projet", e.getInfo());return;}
        //m_titreProj dans ouvrirProjet va récupérer le titre du projet que l'on veut modifier
        PM.modifierNomProjet(m_titreProj,nouveauTitreProjet);
        m_fenetreProjet->close();
        QMessageBox::information(this,"Creation projet","Le titre du projet a bien été ajouté été ajouté");
        //On change la valeur du label m_titreProjet dans ouvrirProjet
        m_titreProjet->setText(nouveauTitreProjet);
        //On supprime l'ancien bouton avec l'ancien titre
        supprimerBouton(m_titreProj);
        //On ajoute un nouveau bouton avec le nouveau titre
        ajouterBouton(nouveauTitreProjet);
    }
    else{
        QMessageBox::critical(this, "Modifier le titre du projet", "Le titre du projet n'a pas été modifié");
    }
}

/* ********************* FIN MODIFIER UN PROJET ********************** */

/* ********************* MODIFIER UNE TACHE ********************** */

void Gestionprojets::modifierTache(){
     m_fenetreModifTache=new QWidget();
     QVBoxLayout *couche=new QVBoxLayout(m_fenetreModifTache);
     //On récupère le bouton sur lequel on a appuyé
     QObject *emetteur =sender();
     QPushButton *emetteurCasted=qobject_cast<QPushButton*>(emetteur);
     //On recherche dans la liste des boutons modifier tache le bouton sur lequel on a appuyé
     map<QString,QPushButton*>::iterator itB=m_boutonModifTache.begin();
     while(itB->second!=emetteurCasted)++itB;

     ProjetManager &PM=ProjetManager::getInstance();
     map<QString,Projet*> projets=PM.getProjets();
     //On récupère le projet avec le titre du projet récupéré par m_titreProj (dans ouverture projet)
     Projet *P=projets[m_titreProj];
     TacheManager TM=P->getTaches();
     map<QString,Tache*>taches=TM.getTaches();

     //On récupère la tache à modifier grâce à la clé du bouton correspondant
     m_tacheModif=taches[itB->first];

     //On crée le formulaire pour modifier la tache
     QHBoxLayout *couche0=new QHBoxLayout();
     QLabel *idTache=new QLabel("Modifier la tache : "+m_tacheModif->getID());

     couche0->addWidget(idTache);
     couche->addLayout(couche0);
     QHBoxLayout *couche1=new QHBoxLayout();
     QLabel *titreTacheLabel=new QLabel("Titre : ");
     m_titreTacheLine=new QLineEdit(m_tacheModif->getTitre());

     couche1->addWidget(titreTacheLabel);
     couche1->addWidget(m_titreTacheLine);

     couche->addLayout(couche1);

     QHBoxLayout *couche2=new QHBoxLayout();
     QLabel *dateDispoTacheLabel=new QLabel("Disponibilite :");
     m_dateDispoTacheLine=new QDateTimeEdit(m_tacheModif->getDisponibilite());
     m_dateDispoTacheLine->setMinimumDate(QDate::currentDate().addDays(-365));
     m_dateDispoTacheLine->setMaximumDate(QDate::currentDate().addDays(365));
     m_dateDispoTacheLine->setDisplayFormat("dd.mm.yyyy");
     QLabel *dateEcheTacheLabel=new QLabel("Echeance :");
     m_dateEcheTacheLine=new QDateTimeEdit(m_tacheModif->getEcheance());
     m_dateEcheTacheLine->setMinimumDate(QDate::currentDate().addDays(-365));
     m_dateEcheTacheLine->setMaximumDate(QDate::currentDate().addDays(365));
     m_dateEcheTacheLine->setDisplayFormat("dd.mm.yyyy");
     couche2->addWidget(dateDispoTacheLabel);
     couche2->addWidget(m_dateDispoTacheLine);
     couche2->addWidget(dateEcheTacheLabel);
     couche2->addWidget(m_dateEcheTacheLine);
     couche->addLayout(couche2);

     //Si la tache est composite, on parcourt ses taches pour pouvoir les modifier aussi
     if(m_tacheModif->estComposite()){
            //On créé un bouton pour permettre d'ajouter une tache à la tache composite
            QPushButton *ajouterTache=new QPushButton("Ajouter une tache");
            QObject::connect(ajouterTache,SIGNAL(clicked()),this,SLOT(ajouterTacheCompo()));
            couche0->addWidget(ajouterTache);
            TacheComposite *tc=dynamic_cast<TacheComposite*>(m_tacheModif);
            map<QString,Tache*>taches=tc->getTaches();
            map<QString,Tache*>::iterator it;
            unsigned int i=0;

            m_titreTacheCompoLine=new QLineEdit*[taches.size()];
            m_dateDispoTacheCompoLine=new QDateTimeEdit*[taches.size()];
            m_dateEcheTacheCompoLine=new QDateTimeEdit*[taches.size()];
            m_dureeTacheCompoLine=new QSpinBox*[taches.size()];
            m_preemptiveCompo=new QCheckBox*[taches.size()];
            QLabel **idTacheCompo=new QLabel*[taches.size()];
            QLabel **dateDispoTacheCompoLabel=new QLabel*[taches.size()];
            QHBoxLayout **coucheCompo1=new QHBoxLayout*[taches.size()];
            QHBoxLayout **coucheCompo2=new QHBoxLayout*[taches.size()];
            QHBoxLayout **coucheCompo3=new QHBoxLayout*[taches.size()];
            QVBoxLayout **coucheCompo=new QVBoxLayout*[taches.size()];
            QLabel **dateEcheTacheCompoLabel=new QLabel*[taches.size()];
            QLabel **titreTacheCompoLabel=new QLabel*[taches.size()];
            QLabel **dureeTacheCompoLabel=new QLabel*[taches.size()];
            //On parcourt les taches et on ajoute leurs caracteristique dynamiquement
            for(it=taches.begin();it!=taches.end();++it){
                idTacheCompo[i]=new QLabel("\n\nModifier la tache : "+it->second->getID());
                coucheCompo[i]=new QVBoxLayout();
                coucheCompo[i]->addWidget(idTacheCompo[i]);
                titreTacheCompoLabel[i]=new QLabel("Titre : ");
                m_titreTacheCompoLine[i]=new QLineEdit(it->second->getTitre());
                m_preemptiveCompo[i]=new QCheckBox("Preemptive");//utiliser signal stateChanged
                coucheCompo1[i]=new QHBoxLayout();
                coucheCompo1[i]->addWidget(titreTacheCompoLabel[i]);
                coucheCompo1[i]->addWidget(m_titreTacheCompoLine[i]);
                coucheCompo1[i]->addWidget(m_preemptiveCompo[i]);
                coucheCompo[i]->addLayout(coucheCompo1[i]);
                dateDispoTacheCompoLabel[i]=new QLabel("Disponibilite :");
                m_dateDispoTacheCompoLine[i]=new QDateTimeEdit(it->second->getDisponibilite());
                m_dateDispoTacheCompoLine[i]->setMinimumDate(QDate::currentDate().addDays(-365));
                m_dateDispoTacheCompoLine[i]->setMaximumDate(QDate::currentDate().addDays(365));
                m_dateDispoTacheCompoLine[i]->setDisplayFormat("dd.mm.yyyy");
                dateEcheTacheCompoLabel[i]=new QLabel("Echeance :");
                m_dateEcheTacheCompoLine[i]=new QDateTimeEdit(it->second->getEcheance());
                m_dateEcheTacheCompoLine[i]->setMinimumDate(QDate::currentDate().addDays(-365));
                m_dateEcheTacheCompoLine[i]->setMaximumDate(QDate::currentDate().addDays(365));
                m_dateEcheTacheCompoLine[i]->setDisplayFormat("dd.mm.yyyy");
                coucheCompo2[i]=new QHBoxLayout();
                coucheCompo2[i]->addWidget(dateDispoTacheCompoLabel[i]);
                coucheCompo2[i]->addWidget(m_dateDispoTacheCompoLine[i]);
                coucheCompo2[i]->addWidget(dateEcheTacheCompoLabel[i]);
                coucheCompo2[i]->addWidget(m_dateEcheTacheCompoLine[i]);
                coucheCompo[i]->addLayout(coucheCompo2[i]);
                dureeTacheCompoLabel[i]=new QLabel("Duree (en minutes) :");
                m_dureeTacheCompoLine[i]=new QSpinBox();
                m_dureeTacheCompoLine[i]->setSingleStep(5);
                m_dureeTacheCompoLine[i]->setMaximum(1000);
                m_dureeTacheCompoLine[i]->setMinimum(0);
                m_dureeTacheCompoLine[i]->setValue(it->second->getDuree().getDureeEnMinutes());
                coucheCompo3[i]=new QHBoxLayout();
                coucheCompo3[i]->addWidget(dureeTacheCompoLabel[i]);
                coucheCompo3[i]->addWidget(m_dureeTacheCompoLine[i]);
                coucheCompo[i]->addLayout(coucheCompo3[i]);
                couche->addLayout(coucheCompo[i]);
                i++;
        }
     }
     //Si tache unitaire, on ajoute le champ durée
     else{
            QHBoxLayout *couche3=new QHBoxLayout();
            QLabel *dureeTacheLabel=new QLabel("Duree (en minutes) :");
            m_dureeTacheLine=new QSpinBox();
            m_dureeTacheLine->setSingleStep(5);
            m_dureeTacheLine->setMaximum(1000);
            m_dureeTacheLine->setMinimum(0);
            m_dureeTacheLine->setValue(m_tacheModif->getDuree().getDureeEnMinutes());
            couche3->addWidget(dureeTacheLabel);
            couche3->addWidget(m_dureeTacheLine);
            couche->addLayout(couche3);
            m_preempTache=new QCheckBox("Preemptive");
            couche1->addWidget(m_preempTache);
     }
     QHBoxLayout *couche4=new QHBoxLayout();
     QPushButton *valider=new QPushButton("OK");
     QPushButton *annuler=new QPushButton("Annuler");
     couche4->addWidget(valider);
     couche4->addWidget(annuler);
     couche->addLayout(couche4);
     QObject::connect(valider,SIGNAL(clicked()),this,SLOT(validermodifTache()));
     QObject::connect(annuler,SIGNAL(clicked()),this,SLOT(annulermodifTache()));
     //Lorsque l'on ouvre la fenêtre pour modifier une tâche, on ferme la fenetre du projet
     m_fenetreModifTache->show();
     m_fenetreProjet->close();
}

void Gestionprojets::validermodifTache(){
    ProjetManager &PM=ProjetManager::getInstance();
    map<QString,Projet*>projets=PM.getProjets();
    Projet *P=projets[m_titreProj];
    TacheManager TM=P->getTaches();
    //On récupère la liste des taches du projet pour ajouter latache modifié
    map<QString,Tache*>taches=TM.getTaches();
    taches.erase(m_tacheModif->getID());
    m_tacheModif->setTitre(m_titreTacheLine->text());
    m_tacheModif->setDispo(m_dateDispoTacheLine->date());
    m_tacheModif->setEche(m_dateEcheTacheLine->date());
    if(m_tacheModif->estComposite()){
        TacheComposite *Tc=dynamic_cast<TacheComposite*>(m_tacheModif);
        map<QString,Tache*>taches=Tc->getTaches();
        map<QString,Tache*>::iterator it;
        unsigned int i=0;
        for(it=taches.begin();it!=taches.end();++it){
            TacheUnitaire *Tu=dynamic_cast<TacheUnitaire*>(it->second);
            Tu->setTitre(m_titreTacheCompoLine[i]->text());
            Tu->setDispo(m_dateDispoTacheCompoLine[i]->date());
            Tu->setEche(m_dateEcheTacheCompoLine[i]->date());
            unsigned int duree=m_dureeTacheCompoLine[i]->value();
            Duree d(duree);
            Tu->setDuree(d);
            i++;
        }
    }
    else {
        TacheUnitaire *Tu=dynamic_cast<TacheUnitaire*>(m_tacheModif);
        unsigned int duree=m_dureeTacheLine->value();
        Duree d(duree);
        Tu->setDuree(d);
    }
    //On ajoute la tache modifié
    taches[m_tacheModif->getID()]=m_tacheModif;
    m_fenetreModifTache->close();
    QMessageBox::information(this,"Creation projet","Le titre du projet a bien été ajouté été ajouté");
}

void Gestionprojets::annulermodifTache(){
    m_fenetreModifTache->close();
    m_fenetreProjet->show();
    QMessageBox::critical(this, "Modifier une tache", "La tache n'a pas été modifié");
}

/* ********************* FIN MODIFIER UNE TACHE ********************** */

/* ********************* AJOUTER UNE TACHE ********************** */

void Gestionprojets::ajouterTache(){
    ProjetManager &PM=ProjetManager::getInstance();
    map<QString,Projet*> projets=PM.getProjets();
    m_projetModif=projets[m_titreProj];
    m_fenetreAjoutTache=new QWidget();
    QVBoxLayout *coucheAjoutTache=new QVBoxLayout(m_fenetreAjoutTache);
    QHBoxLayout *couche5=new QHBoxLayout();
    QHBoxLayout *couche0=new QHBoxLayout();
    QLabel *idTache=new QLabel("Ajouter une tache");
    m_isTacheCompo=new QCheckBox("Tache composite");
    couche5->addWidget(idTache);
    couche5->addWidget(m_isTacheCompo);
    //Lorsque l'on coche ou on décoche la case, un signal est envoyé pour desactiver le champ duree ou pas
    QObject::connect(m_isTacheCompo,SIGNAL(stateChanged(int)),this,SLOT(afficherDuree(int)));
    coucheAjoutTache->addLayout(couche5);
    QLabel *IDTacheLabel=new QLabel("ID : ");
    m_idTacheLine=new QLineEdit();
    couche0->addWidget(IDTacheLabel);
    couche0->addWidget(m_idTacheLine);
    coucheAjoutTache->addLayout(couche0);
    QHBoxLayout *couche1=new QHBoxLayout();
    QLabel *titreTacheLabel=new QLabel("Titre : ");
    m_titreTacheLine=new QLineEdit();
    m_preempTache=new QCheckBox("Preemptive");//utiliser signal stateChanged
    couche1->addWidget(titreTacheLabel);
    couche1->addWidget(m_titreTacheLine);
    couche1->addWidget(m_preempTache);
    coucheAjoutTache->addLayout(couche1);
    QHBoxLayout *couche2=new QHBoxLayout();
    QLabel *dateDispoTacheLabel=new QLabel("Disponibilite :");
    m_dateDispoTacheLine=new QDateTimeEdit(QDate::currentDate());
    m_dateDispoTacheLine->setMinimumDate(QDate::currentDate().addDays(-365));
    m_dateDispoTacheLine->setMaximumDate(QDate::currentDate().addDays(365));
    m_dateDispoTacheLine->setDisplayFormat("dd.mm.yyyy");
    QLabel *dateEcheTacheLabel=new QLabel("Echeance :");
    m_dateEcheTacheLine=new QDateTimeEdit(QDate::currentDate());
    m_dateEcheTacheLine->setMinimumDate(QDate::currentDate().addDays(-365));
    m_dateEcheTacheLine->setMaximumDate(QDate::currentDate().addDays(365));
    m_dateEcheTacheLine->setDisplayFormat("dd.mm.yyyy");
    couche2->addWidget(dateDispoTacheLabel);
    couche2->addWidget(m_dateDispoTacheLine);
    couche2->addWidget(dateEcheTacheLabel);
    couche2->addWidget(m_dateEcheTacheLine);
    coucheAjoutTache->addLayout(couche2);

    QHBoxLayout *couche3=new QHBoxLayout();
    QLabel *dureeTacheLabel=new QLabel("Duree (en minutes) :");
    m_dureeTacheLine=new QSpinBox();
    m_dureeTacheLine->setSingleStep(5);
    m_dureeTacheLine->setMaximum(1000);
    m_dureeTacheLine->setMinimum(0);
    m_dureeTacheLine->setValue(90);
    couche3->addWidget(dureeTacheLabel);
    couche3->addWidget(m_dureeTacheLine);
    coucheAjoutTache->addLayout(couche3);
    QHBoxLayout *couche4=new QHBoxLayout();
    QPushButton *valider=new QPushButton("OK");
    QPushButton *annuler=new QPushButton("Annuler");
    couche4->addWidget(valider);
    couche4->addWidget(annuler);
    coucheAjoutTache->addLayout(couche4);
    QObject::connect(valider,SIGNAL(clicked()),this,SLOT(validerajoutTache()));
    QObject::connect(annuler,SIGNAL(clicked()),this,SLOT(annulerajoutTache()));
    m_fenetreAjoutTache->show();
}

void Gestionprojets::afficherDuree(int state){
    if(state==Qt::Checked){
        m_dureeTacheLine->setDisabled(true);
        m_preempTache->setDisabled(true);
        m_bool=true;
    }
    else {
        m_dureeTacheLine->setDisabled(false);
        m_preempTache->setDisabled(false);
        m_bool=false;
    }
}

void Gestionprojets::validerajoutTache(){
    m_fenetreProjet->close();
    TacheManager &TM=m_projetModif->getTaches();
    unsigned int duree=m_dureeTacheLine->value();
    Duree dureeTache(duree);
    bool preemp=m_preempTache->isChecked();
    try{
        if(m_bool==true){
            TM.addTache(m_idTacheLine->text(),m_titreTacheLine->text(),m_dateDispoTacheLine->date(),m_dateEcheTacheLine->date(),m_projetModif);
        }
        else{
            TM.addTache(m_idTacheLine->text(),m_titreTacheLine->text(),m_dateDispoTacheLine->date(),m_dateEcheTacheLine->date(),m_projetModif,
            dureeTache,preemp);
        }
    }catch(CalendarException e){QMessageBox::critical(this, "Ajouter une tache",e.getInfo());m_fenetreAjoutTache->close();m_bool=false;return;}
    m_bool=false;
    m_fenetreAjoutTache->close();
    QMessageBox::information(this,"Ajout Tache","La tache a bien été ajouté");
}

void Gestionprojets::annulerajoutTache(){
    m_fenetreAjoutTache->close();
    QMessageBox::critical(this, "Ajouter une tache", "La tache n'a pas été ajouté");
}

void Gestionprojets::ajouterTacheCompo(){
    ProjetManager &PM=ProjetManager::getInstance();
    map<QString,Projet*> projets=PM.getProjets();
    m_projetModif=projets[m_titreProj];
    m_fenetreModifTacheCompo=new QWidget();
    QVBoxLayout *coucheAjoutTache=new QVBoxLayout(m_fenetreModifTacheCompo);
    QHBoxLayout *couche0=new QHBoxLayout();
    QLabel *idTache=new QLabel("Ajouter une tache");
    coucheAjoutTache->addWidget(idTache);
    QLabel *IDTacheLabel=new QLabel("ID : ");
    m_idTacheLine=new QLineEdit();
    couche0->addWidget(IDTacheLabel);
    couche0->addWidget(m_idTacheLine);
    coucheAjoutTache->addLayout(couche0);
    QHBoxLayout *couche1=new QHBoxLayout();
    QLabel *titreTacheLabel=new QLabel("Titre : ");
    m_titreTacheLine=new QLineEdit();
    m_preempTache=new QCheckBox("Preemptive");
    couche1->addWidget(titreTacheLabel);
    couche1->addWidget(m_titreTacheLine);
    couche1->addWidget(m_preempTache);
    coucheAjoutTache->addLayout(couche1);
    QHBoxLayout *couche2=new QHBoxLayout();
    QLabel *dateDispoTacheLabel=new QLabel("Disponibilite :");
    m_dateDispoTacheLine=new QDateTimeEdit(QDate::currentDate());
    m_dateDispoTacheLine->setMinimumDate(QDate::currentDate().addDays(-365));
    m_dateDispoTacheLine->setMaximumDate(QDate::currentDate().addDays(365));
    m_dateDispoTacheLine->setDisplayFormat("dd.mm.yyyy");
    QLabel *dateEcheTacheLabel=new QLabel("Echeance :");
    m_dateEcheTacheLine=new QDateTimeEdit(QDate::currentDate());
    m_dateEcheTacheLine->setMinimumDate(QDate::currentDate().addDays(-365));
    m_dateEcheTacheLine->setMaximumDate(QDate::currentDate().addDays(365));
    m_dateEcheTacheLine->setDisplayFormat("dd.mm.yyyy");
    couche2->addWidget(dateDispoTacheLabel);
    couche2->addWidget(m_dateDispoTacheLine);
    couche2->addWidget(dateEcheTacheLabel);
    couche2->addWidget(m_dateEcheTacheLine);
    coucheAjoutTache->addLayout(couche2);
    QHBoxLayout *couche3=new QHBoxLayout();
    QLabel *dureeTacheLabel=new QLabel("Duree (en minutes) :");
    m_dureeTacheLine=new QSpinBox();
    m_dureeTacheLine->setSingleStep(5);
    m_dureeTacheLine->setMaximum(1000);
    m_dureeTacheLine->setMinimum(0);
    m_dureeTacheLine->setValue(90);
    couche3->addWidget(dureeTacheLabel);
    couche3->addWidget(m_dureeTacheLine);
    coucheAjoutTache->addLayout(couche3);
    QHBoxLayout *couche4=new QHBoxLayout();
    QPushButton *valider=new QPushButton("OK");
    QPushButton *annuler=new QPushButton("Annuler");
    couche4->addWidget(valider);
    couche4->addWidget(annuler);
    coucheAjoutTache->addLayout(couche4);
    QObject::connect(valider,SIGNAL(clicked()),this,SLOT(validerajoutTacheCompo()));
    QObject::connect(annuler,SIGNAL(clicked()),this,SLOT(annulerajoutTacheCompo()));
    m_fenetreModifTacheCompo->show();
    m_fenetreModifTache->close();
}

void Gestionprojets::validerajoutTacheCompo(){
    unsigned int duree=m_dureeTacheLine->value();
    Duree dureeTache(duree);
    bool preemp=m_preempTache->isChecked();
    if(m_idTacheLine->text()==""){
        m_fenetreModifTacheCompo->close();
        QMessageBox::critical(this, "Modifier une tache", "Vous n'avez pas entré d'identifiant");
        return;
    }
    TacheUnitaire *Tu=new TacheUnitaire(m_titreTacheLine->text(),m_idTacheLine->text(),m_dateDispoTacheLine->date(),
                                        m_dateEcheTacheLine->date(),m_projetModif,preemp,dureeTache);
    TacheComposite *Tc=dynamic_cast<TacheComposite*>(m_tacheModif);
    map<QString,Tache*>&taches=Tc->getTaches();
    taches[m_idTacheLine->text()]=Tu;
    m_fenetreModifTacheCompo->close();
    QMessageBox::information(this,"Creation projet","Le titre du projet a bien été ajouté été ajouté");
}

void Gestionprojets::annulerajoutTacheCompo(){
    m_fenetreModifTacheCompo->close();
    m_fenetreProjet->show();
    QMessageBox::critical(this, "Modifier une tache", "La tache n'a pas été modifié");
}

void Gestionprojets::ajouterPrecedence(){
    m_fenetrePrecedence=new QWidget();
    QVBoxLayout *couche=new QVBoxLayout(m_fenetrePrecedence);
    QLabel *ajoutPrec=new QLabel("Indiquer la tache precedence");
    QLabel *ajoutSucc=new QLabel("Indiquer la tache suivante");
    couche->addWidget(ajoutPrec);
    m_ajouterPrecLine=new QLineEdit();
    couche->addWidget(m_ajouterPrecLine);
    m_ajouterSuccLine=new QLineEdit();
    couche->addWidget(ajoutSucc);
    couche->addWidget(m_ajouterSuccLine);
    QHBoxLayout *couche1=new QHBoxLayout();
    QPushButton *valider=new QPushButton("OK");
    QPushButton *annuler=new QPushButton("Annuler");
    QObject::connect(valider,SIGNAL(clicked()),this,SLOT(validerajouterPrec()));
    QObject::connect(annuler,SIGNAL(clicked()),this,SLOT(annulerajouterPrec()));
    couche1->addWidget(valider);
    couche1->addWidget(annuler);
    couche->addLayout(couche1);
    m_fenetrePrecedence->show();
    m_fenetreProjet->close();
}

void Gestionprojets::validerajouterPrec(){
    ProjetManager& PM=ProjetManager::getInstance();
    //comment faire pour que getProjet ne soit pas une référence tout en modiifant le projet?
    Projet &P=PM.getProjet(m_titreProj);
    PrecedenceManager& precM=P.getPrecedences();
    TacheManager &tacheM=P.getTaches();
    try{
        const Tache *T1=tacheM.getTache(m_ajouterPrecLine->text());
        const Tache *T2=tacheM.getTache(m_ajouterSuccLine->text());
        precM.ajouterPrecedence(T1,T2);
    }catch(CalendarException &e){ QMessageBox::critical(this,"Ajouter une precedence",e.getInfo());return;}
    QMessageBox::information(this,"Ajouter une precedence","La tache a bien été ajouté");
    m_fenetrePrecedence->close();
}

void Gestionprojets::annulerajouterPrec(){
    m_fenetrePrecedence->close();
    QMessageBox::critical(this, "Ajouter une precedence", "Vous n'avez pas ajouté de precedence");
}

void Gestionprojets::sauvegarderProjet(){
    ProjetManager& PM=ProjetManager::getInstance();
    QString chemin = QFileDialog::getOpenFileName(m_fenetreProjet, "Sauvegarder un projet", QString(), "Fichiers (*.xml)");
    try{
        qDebug()<<m_titreProj;
        PM.save(chemin,m_titreProj);
        qDebug()<<"test";
    }catch(CalendarException &e){QMessageBox::critical(this,"Ajouter une precedence",e.getInfo());return;}
    QMessageBox::information(this,"Sauevgarder un projet","Le projet a bien été ajouté");
}
