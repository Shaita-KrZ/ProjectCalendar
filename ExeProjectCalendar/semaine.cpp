#include "semaine.h"
#include <iostream>

using namespace std;

bool Semaine::testChevauche(Programmation *p) const
{
    QDate dateP;
    QTime heureDebutP;
    QTime heureFinP;
    QDate dateProg = p->getDate();
    QTime heureDebutProg = p->getHoraireDebut();
    QTime heureFinProg = heureDebutProg.addSecs(p->getEvent()->getDuree().getDureeEnMinutes()*60);
    /*pair <multimap<const QDate,Programmation*>::const_iterator, multimap<const QDate,Programmation*>::const_iterator> ret;
    ret = evenements.equal_range(p->getDate());
    for (multimap<const QDate,Programmation*>::iterator it=ret.first; it!=ret.second; ++it){*/
    for(multimap<const QDate, Programmation*>::const_iterator it=evenements.begin(); it!=evenements.end(); ++it){
        dateP = it->second->getDate();
        heureDebutP = it->second->getHoraireDebut();
        heureFinP = heureDebutP.addSecs(it->second->getEvent()->getDuree().getDureeEnMinutes()*60);
        if((dateP == dateProg) && (((heureDebutProg > heureDebutP) && (heureDebutProg < heureFinP)) || ((heureFinProg > heureDebutP) && (heureFinProg < heureFinP))))
            return false;
    }
    return true;
}

// Teste si la programmation respecte les conditions de précédences
// il faut que les taches predecesseurs aient deja ete programmees
// Renvoie true si elle les respecte, false sinon
bool Semaine::testPrecedences(Programmation *p) const{
    QString idProg = p->getEvent()->getID();
    Projet * proj = p->getEvent()->getPere();
    PrecedenceManager pm = proj->getPrecedences();
    Tache * tProg = proj->getTaches().getTache(idProg); // CHOPER LA TACHE
    PrecedenceManager precProg = pm.getTachesPred(tProg);
    for (PrecedenceManager::pmIterator it = precProg.begin(); it!= precProg.end(); ++it){
        if (!it.getCurrent().getPredecesseur()->isScheduled())
            return false;
    }
    return true;
}

/*
 * \brief Ajoute une programmation dans la semaine
 * \param p : programmation a ajouter dans la semaine
 * \throw CalendarException si la programmation se chevauche avec une autre deja existante
 *      si la tache est deja programme,
 *      si les taches de precedences ne sont pas programmees avant,
 *      si la date de la programmation ne correspond pas a la semaine
 */
void Semaine::addProgrammation(Programmation * p){
    // Traitement des erreurs :
    // On essaie de rentrer la programmation dans la mauvaise semaine
    if (p->getLundi()!=getLundi())
        throw CalendarException("Erreur : Mauvaise semaine");
    // On essaie de programmer une tache deja programmee
    if (p->getEvent()->estTache() && p->getEvent()->isScheduled())
        throw CalendarException("Erreur : Tache deja programmee");
    // On essaie de rentrer une programmation qui se chevauche avec une autre deja existante
    if (!testChevauche(p))
        throw CalendarException("Erreur : la programmation rentre en conflit avec un autre evenement deja programme");
    // On vérifie les compatibilités de precedences
    if (!testPrecedences(p))
        throw CalendarException("Erreur : les contraintes de precedences rendent impossible la programmation");
    // Si aucune de ces exceptions n'est declenchee, on peut alors inserer la programmation dans la semaine.
    const QDate d = p->getDate();
    this->evenements.insert(pair<const QDate, Programmation*>(d,p));
}

void Semaine::delProgrammation(Programmation *p)
{
    bool trouve = false;
    for (multimap<const QDate, Programmation*>::iterator it=evenements.begin(); it!=evenements.end() && trouve==false; ++it){
        if(it->second == p){
            evenements.erase(it);
            trouve = true;
        }
    }
    if (!trouve)
        throw CalendarException("Erreur : la programmation en parametre n'existe pas dans la semaine");
}

