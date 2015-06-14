#include "semaine.h"
#include <iostream>
#include <list>

using namespace std;

bool Semaine::testChevauche(Programmation *p) const
{
    QDate dateP;
    QTime heureDebutP;
    QTime heureFinP;
    QDate dateProg = p->getDate();
    QTime heureDebutProg = p->getHoraireDebut();
    QTime heureFinProg = heureDebutProg.addSecs(p->getEvent()->getDuree().getDureeEnMinutes()*60);
    bool jourSuivantP; int testJourP;
    int testJourProg = heureDebutProg.hour() + p->getEvent()->getDuree().getDureeEnHeures();
    bool jourSuivantProg = testJourProg>24;
    for(multimap<const QDate, Programmation*>::const_iterator it=evenements.begin(); it!=evenements.end(); ++it){
        dateP = it->second->getDate();
        heureDebutP = it->second->getHoraireDebut();
        heureFinP = heureDebutP.addSecs(it->second->getEvent()->getDuree().getDureeEnMinutes()*60);
        testJourP = heureDebutP.hour() + it->second->getEvent()->getDuree().getDureeEnHeures();
        jourSuivantP = (testJourP > 24);

        if (dateP == dateProg)
        {
            if (!jourSuivantProg){
                if(((heureDebutProg > heureDebutP) && (heureDebutProg < heureFinP)) || ((heureFinProg > heureDebutP) && (heureFinProg < heureFinP)))
                    return false;
            }
            else{
                if(jourSuivantP){
                    if(((heureDebutProg > heureDebutP) && (heureDebutProg < heureFinP)) || ((heureFinProg > heureDebutP) && (heureFinProg < heureFinP)))
                        return false;
                }
                else{
                    if((heureDebutProg > heureDebutP) && (heureDebutProg < heureFinP))
                        return false;
                }
            }
        }
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
//    if (p->getEvent()->estTache() && !testPrecedences(p))
//        throw CalendarException("Erreur : les contraintes de precedences rendent impossible la programmation");
    // Si aucune de ces exceptions n'est declenchee, on peut alors inserer la programmation dans la semaine.
    const QDate d = p->getDate();
    this->evenements.insert(pair<const QDate, Programmation*>(d,p));
    if (p->getEvent()->estTache()){
        p->getEvent()->setScheduled();
    }
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


QString Semaine::jourToString(int jour) const{
    QDate dateJour = getLundi().addDays(jour-1);
    list<Programmation*> lProgs;
    for(multimap<const QDate, Programmation*>::const_iterator it=evenements.begin(); it!=evenements.end(); ++it){
        if (it->first == dateJour)
            lProgs.push_back(it->second);
    }
    QString str;
    lProgs.sort(compareProg);
    Programmation * prog;
    for (list<Programmation*>::iterator it=lProgs.begin(); it != lProgs.end(); ++it){
        str += "[";
        prog = *it;
        str +=prog->toString();
        str += "] ";
    }
    //str =
    return str;
}
