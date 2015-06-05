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
    PrecedenceManager(unsigned int n);

    ~PrecedenceManager();

    /*!
     * \brief Verifie s'il existe une precedences entre deux classes
     * \param idP tache predecesseur
     * \param idS tache successeur
     * \return true s'il existe une precedence, false sinon
     */
    bool isPrecedence(Tache* prec, Tache *succ) const;

    /*!
     * \brief Recupere toutes les taches d'un meme successeur
     * \param succ la tache dont on cherche les predecesseurs
     * \return les taches ainsi recuperres dans un autre Precedence Manager
     */
    PrecedenceManager & getTachesPred (const Tache * succ) const;

    /*!
     * \brief Crée une precedence et l'ajoute dans sa propre liste de precedences
     * \param p tache predecesseur
     * \param s tache successeur
     */
    void ajouterPrecedence(const Tache * p,const Tache * s);

    class pmIterator:public iterateur<Precedence>{
    private:
        friend class PrecedenceManager;
        pmIterator(Precedence **c):iterateur(c){}
    public:
    };
    pmIterator begin() const{return pmIterator(tabPrec);}
    pmIterator end() const{return pmIterator(tabPrec+nb);}
    /*
     PrecedenceManager PM;
     for(PM::pmIterator it=PM.begin();it!=PM.end();++it){
            cout << *it.getSucc().getId(); <<endl;
        }
     */
};

#endif // PRECEDENCEMANAGER_H
