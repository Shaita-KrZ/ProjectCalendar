#ifndef TACHE_H
#define TACHE_H

#include "evenement.h"
#include "duree.h"

/*!
 * \class Tache
 * \brief Classe abstraite representant une tache d'un projet
 */

class Tache : public Evenement
{
private:
    QString identificateur;
    QDate disponibilite;
    QDate echeance;
    Projet* projetPere;
    QString titre;
public:
    /*!
     * \brief Constructeur d'une tache
     * \param t
     * \param id
     * \param dispo
     * \param ech
     * \param pere
     */
    Tache(QString t, QString id, QDate dispo, QDate ech, Projet* pere);
    virtual ~Tache();

    /*!
     * \brief getID
     * \return identifiant de la tache
     */
    QString getID() const{return identificateur;}

    /*!
     * \brief modifie l'identificateur de la tache
     * \param id : nouvel identificateur
     */
    void setID(const QString id){identificateur=id;}

    /*!
     * \brief méthode virtuelle pure qui retourne la durée de la tache
     * \return duree de la tache
     */
    virtual const Duree & getDuree() const=0;

    /*!
     * \brief verifie le type de la tache
     * \return true si la tache est composite, false sinon
     */
    bool estComposite() const;


    /*!
     * \brief test si la tache est déjà programmée
     * \return true si la tache est déjà programmée, false sinon
     */
    virtual bool isScheduled() const =0;
};

#endif // TACHE_H
