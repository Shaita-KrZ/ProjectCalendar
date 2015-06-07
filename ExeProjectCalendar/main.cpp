#include <QApplication>
#include "exception.h"
#include <QPushButton>
#include "projetmanager.h"
#include "activitetraditionnelle.h"
#include "programmation.h"
#include <QDate>
#include "fenetrePrincipal.h"
#include "projetmanager.h"
#include "agenda.h"

using namespace std;
#include "fenetreGestionProjet.h"
#include "fenetrePrincipal.h"

int main(int argc, char *argv[]){

    QApplication app(argc, argv);
/*
    QString chemin = QFileDialog::getOpenFileName(fenetre, "Charger un projet", QString(), "Fichiers (*.xml)");
    PM.load(chemin);
    Projet P=PM.getProjet("Projet 1");
    TacheManager TM=P.getTaches();
    map<QString,Tache*>taches=TM.getTaches();
    map<QString,Tache*>::iterator it;
    for(it=taches.begin();it!=taches.end();++it){
    }
    */
    //PM.save("projetsavetest.xml","Projet 1");
    /*
    TacheManager T=P.getTaches();
    Tache *T1;
    T1=T.getTache("T3");
    TacheComposite *tComposite=dynamic_cast<TacheComposite*>(T1);
    //Duree d=T.getTache("T3")->tachesCompo["T3b"]->getDuree();*/
    Agenda & agenda = Agenda::getInstance();QDate lundiCourant = QDate::currentDate().addDays(-QDate::currentDate().dayOfWeek()+1);
    agenda.creerSemaine(lundiCourant);
    ActiviteTraditionnelle * act1 = new ActiviteTraditionnelle("RDV Médecin", Duree(1,32));
    ActiviteTraditionnelle * act2 = new ActiviteTraditionnelle("Courses a faire", Duree(6,0));
    ActiviteTraditionnelle * act3 = new ActiviteTraditionnelle("Chercher les enfants à l'escalade", Duree(0,20));
    //Programmation prog(QDate(2015,1,2),QTime(15,30),act);


   /* ActiviteTraditionnelle * act = new ActiviteTraditionnelle("titre", Duree(1,32));
    Programmation prog(QDate(2015,1,2),QTime(15,30),act);
    //QPushButton button(prog.getLundi().toString());
    //button.show();*/
    Programmation * prog1 = new Programmation(lundiCourant,QTime(15,30),act1);
    Programmation * prog2 = new Programmation(lundiCourant,QTime(8,00),act2);
    Programmation * prog3 = new Programmation(lundiCourant,QTime(18,30),act3);
    //Gestionprojets fenetre(10);
    //fenetre.show();
    //Semaine s(prog.getLundi());
    //Semaine s(QDate(2015,06,01));
    //button.show();
    /*try{
        agenda.getSemaines().at(prog->getLundi())->addProgrammation(prog);
    }
    catch(CalendarException &e){
        QMessageBox::warning(0,"Erreur",e.getInfo());
    }*/
    agenda.addProgrammation(prog1);
    agenda.addProgrammation(prog2);
    agenda.addProgrammation(prog3);
    TacheUnitaire * t = new TacheUnitaire("TacheUnitaire", "id1", QDate(2015,06,02), QDate(2015,06,22),0,true,Duree(2,15));
    Programmation * tProg = new Programmation(QDate(2015,06,02),QTime(8,0),t);
    agenda.addProgrammation(tProg);
    Semaine * premiereSemaine = agenda.getSemaines().begin()->second;
    //agenda.getSemaines().insert(pair<const QDate, Programmation*>(prog->getLundi(),prog));//   at(prog->getLundi())->addProgrammation(prog);

    FenAgenda f(premiereSemaine);
    f.show();
    return app.exec();
}

