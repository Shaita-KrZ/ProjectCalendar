#include "tache.h"
#include <typeinfo>
using namespace std;

//methode tache
Tache::Tache(QString t, QString id, QDate dispo, QDate ech, Projet *pere):titre(t),identificateur(id),disponibilite(dispo),echeance(ech),projetPere(pere)
{}

Tache::~Tache(){}
bool Tache::estComposite() const{
    QDate d1(0,0,0);
    QDate d2(0,0,0);
    TacheComposite *tc=new TacheComposite(0,0,d1,d2,0);
    if(typeid(*this)==typeid(*tc)) return true;
    else return false;
}

//methode tache unitaire
TacheUnitaire::TacheUnitaire(const QString titre, const QString id, const QDate dispo, const QDate ech, Projet *pere, const bool preem, const Duree dur):
    Tache(titre,id,dispo,ech,pere),preemptive(preem),duree(dur),scheduled(false){}
TacheUnitaire::~TacheUnitaire(){}

//methode tache composite
TacheComposite::TacheComposite(const QString titre, const QString id, const QDate dispo, const QDate ech, Projet *pere):
    Tache(titre,id,dispo,ech,pere){}
TacheComposite::~TacheComposite(){}

void TacheComposite::addTache(Tache& t){
    if(t.getDisponibilite()<disponibilite){
            throw CalendarException("La disponibilite de la tache ne peut pas être inferieur a sa tache composite");
        }
    if(t.getEcheance()>echeance){
            throw CalendarException("L\'echeance de la tache ne peut pas être superieur a sa tache composite");
        }
    map<QString, Tache>::const_iterator exist(tachesCompo.find(t.getID()));
    tachesCompo.erase(exist);
    tachesCompo[t.getID()]=t;
}

