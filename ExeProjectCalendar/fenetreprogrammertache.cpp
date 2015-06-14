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
    ui->bOK->setEnabled(false);

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


void FenetreProgrammerTache::on_inProjet_activated(const QString &arg1)
{
    ui->lTache->show();
    ui->inTache->clear();
    ui->inTache->show();
    ui->inTache2->hide();
    ui->bOK->setEnabled(false);
    ProjetManager & pm = ProjetManager::getInstance();
    Projet *p = pm.getProjetPoint(arg1);
    proj = p;
    map<QString, Tache*> taches = p->getTaches().getTaches();
    for (map<QString, Tache*>::const_iterator it = taches.begin(); it!=taches.end(); ++it){
        ui->inTache->addItem(it->first);
    }
}

void FenetreProgrammerTache::on_inTache_activated(const QString &arg1)
{
    t1 = proj->getTaches().getTache(arg1);
    if (!t1->estComposite()){
        ui->inTache2->hide();
        ui->bOK->setEnabled(true);
        t2 = t1;
    }
    else{
        ui->bOK->setEnabled(false);
        ui->inTache2->clear();
        ui->inTache2->show();
        map<QString, Tache*> taches = t1->getTaches();
        for (map<QString, Tache*>::const_iterator it = taches.begin(); it!=taches.end(); ++it){
            ui->inTache2->addItem(it->first);
        }
    }
}

void FenetreProgrammerTache::on_inTache2_activated(const QString &arg1)
{
    map<QString, Tache*> taches = t1->getTaches();
    t2 = taches.at(arg1);
    if (!t2->estComposite())
        ui->bOK->setEnabled(true);
}

void FenetreProgrammerTache::on_bOK_accepted()
{
    Agenda & a = Agenda::getInstance();
    QDate d = ui->inDateHeure->date();
    QTime hd = ui->inDateHeure->time();
    Programmation * p = new Programmation(d, hd, t2);
    try{
        a.addProgrammation(p);
    }
    catch(CalendarException &e){
        QMessageBox::critical(this,"Programmation tache",e.getInfo());
        this->close();
        return;
    }
    QMessageBox::information(this, "Programmation tache", "Ajout de la tache : \n " + p->toString() + "\n le " + p->getDate().toString("dd/MM/yyyy"));
    fenAg->actualiserItems();
    // Gestion des précédences & Preemptive?
    this->close();
}
