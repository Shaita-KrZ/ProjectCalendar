#ifndef SEMAINE_H
#define SEMAINE_H


#include "projet.h"
#include "programmation.h"
#include <map>
#include "exception.h"

/*!
 * \brief The Semaine class
 */
class Semaine
{
private:
    QDate lundi;
    multimap<const QDate,Programmation*> evenements;

    // Teste si la programmation p se chevauche avec les programmations existantes
    // Renvoie true si la programmation ne se chevauche pas, false sinon
    bool testChevauche(Programmation *p) const;
public:
    /*!
     * \brief Constructeur de la classe
     * \param l : Date du lundi de la semaine
     */
    Semaine(QDate l):lundi(l){}

    virtual ~Semaine(){}

    /*!
     * \brief Ajoute une programmation dans la semaine
     * \param p : programmation a ajouter dans la semaine
     * \throw CalendarException si la programmation existe deja dans la semaine,
     *      si la tache est deja programme,
     *      si les taches de precedences ne sont pas programmees avant,
     *      si la date de la programmation ne correspond pas a la semaine
     */
    void addProgrammation(Programmation * p);

    /*!
     * \brief Supprime une programmation dans la semaine
     * \param p : Programmation a supprimer
     * \throw CalendarException si la programmation n'existe pas
     */
    void delProgrammation(Programmation * p);

    /*!
     * \brief renvoie le lundi de la semaine
     * \return lundi
     */
    const QDate getLundi() const{return lundi;}
};

#endif // SEMAINE_H