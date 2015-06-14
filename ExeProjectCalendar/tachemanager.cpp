#include "tachemanager.h"

TacheManager::TacheManager(){}

TacheManager::~TacheManager(){}

//Ajout d'une tache unitaire
void TacheManager::addTache(const QString id, const QString t, const QDate disp, const QDate ech, Projet *pp,const Duree d, const bool p){
    TacheUnitaire *tu=new TacheUnitaire(t,id,disp,ech,pp,p,d);

    if(id==""){
        throw CalendarException("Vous n'avez pas entré d'identifiant");
    }
    if(taches.find(id)!=taches.end()){
            throw CalendarException("La tache existe deja");
    }
    else taches[id]=tu;
}

//Ajout d'une tache composite
void TacheManager::addTache(const QString id, const QString t, const QDate disp,const QDate ech,Projet *p){
    TacheComposite *tc=new TacheComposite(t,id,disp,ech,p);
    if(id==""){
        throw CalendarException("Vous n'avez pas entré d'identifiant");
    }
    if(taches.find(id)!=taches.end()){
            throw CalendarException("La tache existe deja");
    }
    else taches[id]=tc;
}

Tache* TacheManager::getTache(const QString id) const{
    map<const QString, Tache*>::const_iterator it;
    if(taches.find(id)==taches.end()){
        throw CalendarException("La tache n'existe pas");
    }
    it=taches.find(id);
    return it->second;
}

void TacheManager::delTache(const QString id){
    if(taches.find(id)!=taches.end()){
            taches.erase(id);
    }
    else throw CalendarException("La tache n'existe pas");
}


