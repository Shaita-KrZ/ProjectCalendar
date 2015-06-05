#include <QApplication>
#include "exception.h"
#include <QPushButton>
#include "projetmanager.h"
#include "activitetraditionnelle.h"
#include "programmation.h"
#include <QDate>
#include "fenagenda.h"

int main(int argc, char *argv[]){
    ProjetManager PM=ProjetManager::getInstance();

    //PM.load("projet.xml");
    QApplication app(argc, argv);
    //PM.save("projetsavetest.xml","Projet 1");
    /*
    TacheManager T=P.getTaches();
    Tache *T1;

    T1=T.getTache("T3");
    TacheComposite *tComposite=dynamic_cast<TacheComposite*>(T1);
    //Duree d=T.getTache("T3")->tachesCompo["T3b"]->getDuree();*/
    ActiviteTraditionnelle * act = new ActiviteTraditionnelle("titre", Duree(1,32));
    Programmation prog(QDate(2015,1,2),QTime(15,30),act);
    QPushButton button(prog.getLundi().toString());
    Semaine s(prog.getLundi());
    //button.show();
    FenAgenda f(s);
    f.show();
    return app.exec();
}

