#ifndef ACTIVITETRADITIONNELLE_H
#define ACTIVITETRADITIONNELLE_H
#include "evenement.h"
#include "duree.h"
#include "iterator.h"

/*!
 * \brief Represente un evenement quelconque (qui ne fait pas partie d'un projet)
 *      Par exemple un RDV
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

    virtual bool estTache() const{ return false;}

    /*!
     * \brief Renvoie faux car l'objet n'est pas une tache
     * \return false
     */
    virtual bool isScheduled()const{return false;}

    /*!
     * \brief Renvoie un pointeur null puisque l'evenement n'est pas une tache
     * \return 0
     */
    virtual Projet* getPere()const {return 0;}

    /*!
     * \brief renvoie une chaine vide car l'objet n'est pas une tache
     * \return ""
     */
   virtual QString getID() const{return "";}

    virtual void setScheduled(){
        throw CalendarException("Erreur : l'evenement n'est pas une tache unitaire");
    }

    virtual void setNonScheduled(){
        throw CalendarException("Erreur : l'evenement n'est pas une tache unitaire");
    }
};

#endif // ACTIVITETRADITIONNELLE_H
