#ifndef TACHEUNITAIRE_H
#define TACHEUNITAIRE_H

#include "tache.h"


class TacheUnitaire : public Tache
{
private:
    bool preemptive;
    Duree duree;
    bool scheduled;
public:
    /*!
     * \brief Constructeur de la tache unitaire, scheduled est à false initialement
     * \param titre
     * \param id
     * \param dispo
     * \param ech
     * \param pere
     * \param preem
     * \param dur
     */
    TacheUnitaire(const QString titre, const QString id, const QDate dispo, const QDate ech, const Projet* pere,
                  const bool preem, const Duree dur);

    virtual ~TacheUnitaire();

    /*!
     * \brief getDuree
     * \return durée de la tache unitaire
     */
    virtual Duree getDuree() const;

    /*!
     * \brief modifie la durée de la tache
     * \param d : nouvelle durée
     */
    void setDuree(Duree d);

    /*!
     * \brief rend la tache preemptive, aucun effet si elle l'est déjà
     */
    void setPreemptive();

    /*!
     * \brief rend la tache non preemptive, aucun effet si elle l'est déjà
     */
    void setNonPreemptive();

    /*!
     * \brief Vérifie si la tache est déjà programmée
     * \return true si la tache est programmée, false sinon
     */
    virtual bool isScheduled() const;

    /*!
     * \brief place l'attribut scheduled à true, aucun effet si il l'est déjà
     */
    void setScheduled();

    /*!
     * \brief place l'attribut scheduled à false, aucun effet si il l'est déjà
     */
    void setNonScheduled();
};

#endif // TACHEUNITAIRE_H
