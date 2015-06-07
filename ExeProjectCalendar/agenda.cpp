#include "agenda.h"

using namespace std;

Agenda * Agenda::instance=0;

Agenda & Agenda::getInstance(){
    if(instance==0){
        instance=new Agenda();
    }
    return *instance;
}

void Agenda::libererInstance(){
    if(instance!=0)delete instance;
    instance=0;
}

/*
 * \brief Cree et ajoute une semaine dans l'agenda; aucun effet si la semaine existe deja
 * \param lundi
 * \throw CalendarException si la date en parametre ne correspond pas a un lundi
 */
void Agenda::creerSemaine(const QDate &lundi)
{
    if(lundi.dayOfWeek()!=1)
        throw CalendarException("Erreur : La date en parametre ne correspond pas a un lundi");
    Semaine *s = new Semaine(lundi);
    pair<map<const QDate, Semaine*>::iterator,bool> ret = semaines.insert(pair<const QDate, Semaine*>(lundi, s));
}

void Agenda::addProgrammation(Programmation *p)
{
    Semaine * sem = new Semaine(p->getLundi());
    pair<map<const QDate, Semaine*>::iterator,bool> ret = semaines.insert(pair<const QDate, Semaine*>(sem->getLundi(), sem));
    Semaine * semaineProg = this->getSemaines().find(p->getLundi())->second;
    try{
        semaineProg->addProgrammation(p);
    }
    catch(CalendarException &e){
        throw e;
    }

}

Agenda::~Agenda(){
    for (map<const QDate, Semaine*>::iterator it=semaines.begin(); it!=semaines.end(); ++it){
        delete it->second;
    }
}
