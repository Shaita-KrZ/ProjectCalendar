#ifndef PRECEDENCEMANAGER_H
#define PRECEDENCEMANAGER_H
#include "precedence.h"
#include "iterator.h"
#include <vector>


/*!
 * \brief Manipule les differentes precedences du projet
 */
class PrecedenceManager
{
private:
    Precedence **tabPrec;
    unsigned int nb;
    unsigned int nbMax;
public:

    /*!
     * \brief Constructeur de la classe
     */
    explicit PrecedenceManager();

    ~PrecedenceManager();

    /*!
     * \brief Verifie s'il existe une precedences entre deux classes
     * \param idP tache predecesseur
     * \param idS tache successeur
     * \return true s'il existe une precedence, false sinon
     */
    bool isPrecedence(Tache* prec, Tache *succ) const;

    /*!
     * \brief Crée une precedence et l'ajoute dans sa propre liste de precedences
     * \param p tache predecesseur
     * \param s tache successeur
     */
    void ajouterPrecedence(Tache * p,Tache * s);

    /*!
     * \brief Derivation generique d'iterateur en iterateur de precedences
     */
    class pmIterator:public iterateur<Precedence>
    {
    private:
        friend class PrecedenceManager;
        pmIterator(Precedence **c):iterateur(c){}
    public:
    };

    /*!
     * \brief Recupere le premier element de self
     * \return iterateur sur la premiere Precedence de self
     */
    pmIterator begin() const{return pmIterator(tabPrec);}

    /*!
     * \brief Recupere le dernier element de self
     * \return iterateur sur la derniere Precedence de self
     */
    pmIterator end() const{return pmIterator(tabPrec+nb);}

};

#endif // PRECEDENCEMANAGER_H
