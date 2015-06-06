#include "projet.h"


Projet::~Projet()
{

}

Projet::Projet(const QString &t):titre(t){

}

// Modifie la date d'echeance du projet avec le parametre e
void Projet::setEcheance(const QDate & e){
    echeance=e;
}
