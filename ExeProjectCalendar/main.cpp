#include <QApplication>
#include "exception.h"
#include <QPushButton>
#include "projetmanager.h"
#include "activitetraditionnelle.h"
#include "programmation.h"
#include <QDate>
#include "gestionprojets.h"
#include "fenagenda.h"

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
        qDebug()<<it->first;
    }
    */
    //PM.save("projetsavetest.xml","Projet 1");
    /*
    TacheManager T=P.getTaches();
    Tache *T1;
    T1=T.getTache("T3");
    TacheComposite *tComposite=dynamic_cast<TacheComposite*>(T1);
    //Duree d=T.getTache("T3")->tachesCompo["T3b"]->getDuree();*/
    /*
    ActiviteTraditionnelle * act = new ActiviteTraditionnelle("titre", Duree(1,32));
    Programmation prog(QDate(2015,1,2),QTime(15,30),act);
    QPushButton button(prog.getLundi().toString());
    button.show();*/

    //Gestionprojets fenetre(10);
    //fenetre.show();
    Semaine s(prog.getLundi());
    //button.show();
    FenAgenda f(s);
    f.show();
    return app.exec();
}

