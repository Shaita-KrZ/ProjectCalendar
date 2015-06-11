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
#include "fenetreprogrammer.h"

using namespace std;
#include "fenetreGestionProjet.h"
#include "fenetrePrincipal.h"

int main(int argc, char *argv[]){

    QApplication app(argc, argv);
    Agenda & agenda = Agenda::getInstance();
    try{
        QDate lundiCourant = QDate::currentDate().addDays(-QDate::currentDate().dayOfWeek()+1);
        agenda.creerSemaine(lundiCourant);
    }
    catch (CalendarException & e){
    }

    ActiviteTraditionnelle * act = new ActiviteTraditionnelle("titre", Duree(1,32));
    Programmation prog(QDate(2015,1,2),QTime(15,30),act);
    Semaine s(prog.getLundi());

    Semaine premiereSemaine = agenda.getSemaines().begin()->first;

    Agenda & agenda = Agenda::getInstance();
    QDate lundiCourant = QDate::currentDate().addDays(-QDate::currentDate().dayOfWeek()+1);
    agenda.creerSemaine(lundiCourant);
    ProjetManager & pm = ProjetManager::getInstance();
    pm.load("C:/Users/Alex/Dropbox/Cours/UTC/LO21/Projet Calendar/ProjetCalendar UML/exempleProjetSansPrecedence.xml");
    pm.load("D:/Alex/Bureau/othersp/ExeProjectCalendar/projet3.xml");
    pm.load("D:/Alex/Bureau/othersp/ExeProjectCalendar/projet.xml");
    pm.load("D:/Alex/Bureau/othersp/ExeProjectCalendar/projet2.xml");
    ActiviteTraditionnelle * act1 = new ActiviteTraditionnelle("RDV Médecin", Duree(1,32));
    ActiviteTraditionnelle * act2 = new ActiviteTraditionnelle("Courses a faire", Duree(6,0));
    ActiviteTraditionnelle * act3 = new ActiviteTraditionnelle("Chercher les enfants à l'escalade", Duree(0,20));

    Programmation * prog1 = new Programmation(lundiCourant,QTime(15,30),act1);
    Programmation * prog2 = new Programmation(lundiCourant,QTime(8,00),act2);
    Programmation * prog3 = new Programmation(lundiCourant,QTime(18,30),act3);

    agenda.addProgrammation(prog1);
    agenda.addProgrammation(prog2);
    agenda.addProgrammation(prog3);
    TacheUnitaire * t = new TacheUnitaire("TacheUnitaire", "id1", QDate(2015,06,02), QDate(2015,06,22),0,true,Duree(2,15));
    Programmation * tProg = new Programmation(QDate(2015,06,02),QTime(8,0),t);
    agenda.addProgrammation(tProg);
    Semaine * semaineCourante = agenda.getSemaines().at(lundiCourant);
    FenAgenda f(semaineCourante);
    f.show();
    return app.exec();
}

