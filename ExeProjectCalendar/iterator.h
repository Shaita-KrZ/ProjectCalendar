#ifndef ITERATOR_H
#define ITERATOR_H

/*!
 *  \brief Classe d'iterateur generique
 */
template<class X>
class iterateur{
protected:
    friend class agregateur;
    X **x;
    iterateur(X **x1):x(x1){}
public:
    /*!
     * \brief Compare l'iterateur avec un autre
     * \param it : iterateur a comparer avec self
     * \return true si les deux iterateurs sont differents, false sinon
     */
    virtual bool operator!=(const iterateur& it){
        return x!=it.x;
    }

    /*!
     * \brief incremente l'operateur pour aller a l'element suivant de l'agregateur
     */
    virtual void operator++(){ ++x;}

    /*!
     * \brief permet d'acceder a l'element pointe par l'iterateur
     * \return element courant
     */
    virtual X* getCurrent(){return *x;}

    /*!
     * \brief Compare l'iterateur avec un autre
     * \param it : iterateur a comparer avec self
     * \return true si les deux iterateurs sont les memes, false sinon
     */
    virtual bool operator==(const iterateur& it){
        return x==it.x;
    }
};

#endif // ITERATOR_H

