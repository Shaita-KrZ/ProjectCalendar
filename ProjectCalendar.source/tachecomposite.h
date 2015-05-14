#ifndef TACHECOMPOSITE_H
#define TACHECOMPOSITE_H

#include "tache.h"
#include <map>


/*!
 * \class TacheComposite
 * \brief Tache composée de plusieurs autres taches (unitaires ou composées)
 */
class TacheComposite : public Tache
{
private:
    map<QString, Tache> tachesCompo;

public:
    /*!
     * \brief Construit une tache composite vide
     * \param titre
     * \param id
     * \param dispo
     * \param ech
     * \param pere
     */
    TacheComposite(const QString titre, const QString id, const QDate dispo, const QDate ech, const Projet* pere);

    ~TacheComposite();

    /*!
     * \brief ajoute une tache dans la liste des taches
     * \param t : tache à ajouter
     * \throw CalendarException si la disponibilité de t est < à la disponibilite de self
     * \throw CalendarException si l'échéance de t est > à l'échéance de self
     * \throw CalendarException si une tache du même identifiant existe déjà
     */
    void addTache(Tache & t);

    /*!
     * \brief Supprime la tache d'identifiant t de la liste
     *      aucun effet si la tache n'existe pas
     * \param id : identifiant de la tache à supprimer
     */
    void delTache(const QString & id);

    /*!
     * \brief getDuree est la somme des duree des taches qui composent la tacheComposite
     * \return la duree totale de la tache
     */
    virtual const Duree & getDuree() const;

    /*!
     * \brief Vérifie si toutes les taches qui composent la tache composite sont programmées
     * \return true si toutes les taches sont programmées, false sinon
     */
    virtual bool isScheduled () const;


};

#endif // TACHECOMPOSITE_H
