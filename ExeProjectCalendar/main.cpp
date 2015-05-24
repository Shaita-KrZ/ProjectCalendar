#include <QApplication>
#include "exception.h"
#include <QPushButton>
#include "projetmanager.h"

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
    QPushButton button("test");
    button.show();
    return app.exec();
}

