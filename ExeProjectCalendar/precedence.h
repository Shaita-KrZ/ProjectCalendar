#ifndef PRECEDENCE_H
#define PRECEDENCE_H
#include "tache.h"

/*!
 * \brief Classe permettant de creer des liens de precedences entre les taches
 */
class Precedence
{
private:
    const Tache * pred;
    const Tache * succ;
public:
    /*!
     * \brief Constructeur de la classe
     * \param p Tache predecesseur
     * \param s Tache successeur
     */
    Precedence(const Tache *p,const Tache *s);

    ~Precedence();

    /*!
     * \brief getPredecesseur
     * \return pointeur vers la tache predecesseur
     */
    const Tache * getPredecesseur() const{ return pred; }

    /*!
     * \brief getSuccesseur
     * \return pointeur vers la tache successeur
     */
    const Tache * getSuccesseur() const{ return succ;}
};

#endif // PRECEDENCE_H
