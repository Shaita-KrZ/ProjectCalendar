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

    // Teste si la programmation respecte les conditions de précéédences
    // Renvoie true si elle les respecte, false sinon
    bool testPrecedences(Programmation *p) const;
public:
    /*!
     * \brief Constructeur de la classe
     * \param l : Date du lundi de la semaine
     */
    Semaine(QDate l):lundi(l){}



    virtual ~Semaine(){}

    /*!
     * \brief Ajoute une programmation dans la semaine
     *      si l'evenement est une tache, la rend programmée
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

    /*!
     * \brief Genere une chaine de caracteres correspondant aux programmations pour le jour en entree
     *      La chaine est compose des activites du jour en parametre dans leur ordre chronologique
     * \param jour : lundi à dimanche - 1 à 7
     * \return QString correspondant aux programmations du jour en parametre
     */
    QString jourToString(int jour) const;

    /*!
     * \brief Donne le nombre de programmations de semaines
     * \return
     */
    size_t nombreEvent() const {return evenements.size();}
};

#endif // SEMAINE_H
