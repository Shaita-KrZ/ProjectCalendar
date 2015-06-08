#include "fenetreactivitetrad.h"
#include "ui_fenetreactivitetrad.h"


FenetreActiviteTrad::FenetreActiviteTrad(FenAgenda *f, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FenetreActiviteTrad),
    fenAg(f)
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
    try{
        a.addProgrammation(prog);
    }
    catch(CalendarException &e){
        QMessageBox::critical(this,"Ajout Activite",e.getInfo());
        this->close();
    }
    fenAg->actualiserItems();
}
