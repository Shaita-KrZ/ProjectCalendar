#include "semaine.h"

void Semaine::addProgrammation(Programmation * p){
    if (p->getLundi()!=getLundi()){
        throw CalendarException("Erreur : Mauvaise semaine");
    }
    if (p->getEvent()->estTache())
        throw CalendarException(p->getEvent()->isShe)
}

