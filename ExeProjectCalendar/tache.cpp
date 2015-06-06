#include "tache.h"
#include <typeinfo>
using namespace std;

//methode tache
Tache::Tache(QString t, QString id, QDate dispo, QDate ech, Projet *p)
    :Evenement(t),identificateur(id),disponibilite(dispo),echeance(ech),pere(p){}
Tache::~Tache(){}

//methode tache unitaire
TacheUnitaire::TacheUnitaire(const QString titre, const QString id, const QDate dispo, const QDate ech, Projet *p, const bool preem, const Duree dur):
    Tache(titre,id,dispo,ech,p),preemptive(preem),duree(dur),scheduled(false){}
TacheUnitaire::~TacheUnitaire(){}
bool TacheUnitaire::estComposite() const{
    return false;
}

Duree TacheUnitaire::getDuree() const{
    return duree;
}



//methode tache composite
TacheComposite::TacheComposite(QString t, QString id, QDate dispo, QDate ech, Projet *p)
    :Tache(t,id,dispo,ech,p){}
TacheComposite::~TacheComposite(){}

void TacheComposite::addTache(Tache* t){
    if(t->getDisponibilite()<disponibilite){
            throw CalendarException("La disponibilite de la tache ne peut pas être inferieur a sa tache composite");
        }
    if(t->getEcheance()>echeance){
            throw CalendarException("L\'echeance de la tache ne peut pas être superieur a sa tache composite");
        }
    if(tachesCompo.find(t->getID())!=tachesCompo.end()){
            throw CalendarException("La tache existe deja");
    }
    tachesCompo[t->getID()]=t;
}

void TacheComposite::delTache(const QString& id){
    if(tachesCompo.find(id)!=tachesCompo.end()){
            tachesCompo.erase(id);
    }
    else throw CalendarException("La tache n\'existe pas");
}

bool TacheComposite::estComposite() const{
    return true;
}

Duree TacheComposite::getDuree() const{
    Duree d;
    map<QString, Tache*>::const_iterator it;
    for(it=tachesCompo.begin();it!=tachesCompo.end();++it){
        d+=it->second->getDuree();
    }
    return d;
}


