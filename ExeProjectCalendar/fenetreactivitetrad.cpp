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
    QTime duree0(0,0);
    if(t==""){
        QMessageBox::critical(this,"Ajout Activite","Le titre de l'activite traditionnelle ne peut pas être nul");
        return;
    }
    if(timAct==duree0){
        QMessageBox::critical(this,"Ajout Activite","La duree de l'activite traditionnelle ne peut pas être nulle");
        return;
    }
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
        return;
    }
    QMessageBox::information(this, "Programmation tache", "Ajout de l'activite' : \n " + prog->toString() + "\n le " + prog->getDate().toString("dd/MM/yyyy"));
    fenAg->actualiserItems();
}
