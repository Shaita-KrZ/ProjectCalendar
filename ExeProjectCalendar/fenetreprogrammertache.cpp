#include "fenetreprogrammertache.h"
#include "ui_fenetreprogrammertache.h"


FenetreProgrammerTache::FenetreProgrammerTache(FenAgenda *f, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FenetreProgrammerTache),
    fenAg(f)
{
    ui->setupUi(this);

    /*** ON CACHE LES CHAMPS DE TACHE TANT QUE LE PROJET N'EST PAS SELECTIONNE ***/
    ui->inTache->hide();
    ui->inTache2->hide();
    ui->lTache->hide();

    /*** ON INITIALISE LA COMBO_BOX DE SELECTION DE PROJETS ***/
    ProjetManager & pm = ProjetManager::getInstance();
    map<QString, Projet*> projets = pm.getProjets();
        for (map<QString, Projet*>::const_iterator it = projets.begin(); it!=projets.end(); ++it){
            ui->inProjet->addItem(it->first);
        }
}

FenetreProgrammerTache::~FenetreProgrammerTache()
{
    delete ui;
}

