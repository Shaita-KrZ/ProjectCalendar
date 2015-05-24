#ifndef ACTIVITETRADITIONNELLE_H
#define ACTIVITETRADITIONNELLE_H
#include "evenement.h"
#include "duree.h"
#include "iterator.h"

/*!
 * \class Activite Traditionnelle
 * \brief Represente un evenement quelconque (qui ne fait pas partie d'un projet)
 *      Par exemple un RDV ou un repas de famille
 */
class ActiviteTraditionnelle : public Evenement
{
private:
    Duree duree;
public:

    /*!
     * \brief
     * \return duree de l'activite
     */
    virtual Duree getDuree() const;

    /*!
     * \brief modifie la duree de l'activite
     * \param d : duree a modifier
     */
    void setDuree(Duree d) {duree = d;}
    /*!
     * \brief Constructeur
     * \param t : titre de l'activite
     * \param d : duree de l'activite
     */
    ActiviteTraditionnelle(QString titre, Duree d):Evenement(titre), duree(d){}

};

#endif // ACTIVITETRADITIONNELLE_H
