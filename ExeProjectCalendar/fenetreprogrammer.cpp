#include "fenetreprogrammer.h"
#include "ui_fenetreprogrammer.h"
#include "fenetreactivitetrad.h"
#include "fenetreprogrammertache.h"

FenetreProgrammer::FenetreProgrammer(FenAgenda *f, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FenetreProgrammer),
    fenAg(f)
{
    ui->setupUi(this);
}

FenetreProgrammer::~FenetreProgrammer()
{
    delete ui;
}

void FenetreProgrammer::on_bOKCancel_rejected()
{
    this->close();
}

void FenetreProgrammer::on_bActiviteTraditionnelle_clicked()
{
    FenetreActiviteTrad * fAT = new FenetreActiviteTrad(fenAg);
    fAT->show();
    this->close();
}

void FenetreProgrammer::on_bTache_clicked()
{
    ProjetManager & pm = ProjetManager::getInstance();
    if(pm.getProjets().empty()){
        QMessageBox::critical(this, "Programmation d'une Tache", "Erreur : Aucun projet enregistré");
    }
    else{
        FenetreProgrammerTache * fPT = new FenetreProgrammerTache(fenAg);
        fPT->show();
        this->close();
    }
}
