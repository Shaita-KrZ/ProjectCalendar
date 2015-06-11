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
    FenAgenda f(premiereSemaine);
    f.show();
    return app.exec();
}

