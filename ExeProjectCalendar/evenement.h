#ifndef EVENEMENT_H
#define EVENEMENT_H
#include "duree.h"
class Projet;
/*!
 * \class Evenement
 * \brief Classe abstraite representant un evenement a programmer dans l'agenda
 */
class Evenement
{
private:
    QString titre;
public:
    /*!
     * \brief Constructeur de la classe
     * \param t : titre de l'evenement
     */
    Evenement(const QString & t):titre(t){}

    /*!
     * \brief getDuree
     * \return duree de l'evenement
     */
    virtual Duree getDuree() const=0;
    /*!
     * \brief getTitre
     * \return titre de l'evenement
     */
    QString getTitre() const {return titre;}

    /*!
     * \brief modifie le titre de l'evenement
     * \param[in] t : nouveau titre
     * \param[in, out] self : objet a modifier
     *
     */
    void setTitre(const QString t){titre = t;}

    virtual ~Evenement(){}

    /*!
     * \brief Verifie si l'evenement est une tache ou une activite traditionnelle
     * \return true si l'evenement est une tache, false sinon
     */
    virtual bool estTache() const=0;

    /*!
     * \brief Verifie si la tache est programmee
     * \return true si la tache est programmee, false sinon
     */
    virtual bool isScheduled()const=0;

    /*!
     * \brief Permet d'acceder au projet pere si l'evenement est une tache
     * \return pointeur vers le projet pere de la tache
     */
    virtual Projet* getPere()const=0;

    /*!
     * \brief Compare deux evenements
     * \param Evenement a comparer avec self
     * \return true si les titres sont les memes
     */
    virtual bool operator==(const Evenement & e) const{
        return (titre == e.titre);
    }

    /*!
     * \brief Si l'objet est de type tache renvoie son ID, sinon renvoie une chaine vide.
     * \return identifiant de la tache
     */
   virtual QString getID() const=0;
};

#endif // EVENEMENT_H
