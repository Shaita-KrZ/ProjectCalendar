#include "fenetreactivitetrad.h"
#include "ui_fenetreactivitetrad.h"
#include "duree.h"
#include "programmation.h"
#include "activitetraditionnelle.h"
#include "fenetrePrincipal.h"

FenetreActiviteTrad::FenetreActiviteTrad(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FenetreActiviteTrad)
{
    ui->setupUi(this);
}

FenetreActiviteTrad::~FenetreActiviteTrad()
{
    delete ui;
}

void FenetreActiviteTrad::on_bOKcancel_accepted()
{
    QString t = this->ui->inTitre->text();
    QTime timAct = this->ui->inDuree->time();
    Duree d(timAct.hour(), timAct.minute());
    ActiviteTraditionnelle * at = new ActiviteTraditionnelle(t, d);
    QDate datProg = this->ui->inDateTimeProg->date();
    QTime timProg = this->ui->inDateTimeProg->time();
    Programmation * prog = new Programmation(datProg, timProg, at);
    Agenda & a = Agenda::getInstance();
    a.addProgrammation(prog);
}
