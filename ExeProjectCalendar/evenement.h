#ifndef EVENEMENT_H
#define EVENEMENT_H
#include "duree.h"

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
};

#endif // EVENEMENT_H
