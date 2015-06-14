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
    QDate lundiCourant = QDate::currentDate().addDays(-QDate::currentDate().dayOfWeek()+1);
    agenda.creerSemaine(lundiCourant);
    Semaine * semaineCourante = agenda.getSemaines().at(lundiCourant);
    FenAgenda f(semaineCourante);
    f.show();
    return app.exec();
}
