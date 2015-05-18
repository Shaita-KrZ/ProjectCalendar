#ifndef TACHE_H
#define TACHE_H
#include "duree.h"
#include "projet.h"
#include "exception.h"
#include<map>

/*!
 * \class Tache
 * \brief Classe abstraite representant une tache d'un projet
 */
class Tache{
protected:
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
    Tache(){}
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
     * \brief getDisponibilite
     * \return disponibilite de la tache
     */
    QDate getDisponibilite(){
        return disponibilite;
    }
    /*!
     * \brief getEcheance
     * \return echeance de la tache
     */
    QDate getEcheance(){
        return echeance;
    }

    /*!
     * \brief verifie le type de la tache
     * \return true si la tache est composite, false sinon
     */
    bool estComposite() const;
};


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
    TacheComposite(const QString titre, const QString id, const QDate dispo, const QDate ech, Projet* pere);
    virtual ~TacheComposite();

    /*!
     * \brief ajoute une tache dans la liste des taches
     * \param t : tache à ajouter
     * \throw CalendarException si la disponibilité de t est < à la disponibilite de self
     * \throw CalendarException si l'échéance de t est > à l'échéance de self
     * \throw CalendarException si une tache du même identifiant existe déjà
     */
    virtual void addTache(Tache & t);

    /*!
     * \brief Supprime la tache d'identifiant t de la liste
     *      aucun effet si la tache n'existe pas
     * \param id : identifiant de la tache à supprimer
     */
    void delTache(const QString & id);

};


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
    TacheUnitaire(const QString titre, const QString id, const QDate dispo, const QDate ech, Projet* pere,
                  const bool preem, const Duree dur);
    virtual ~TacheUnitaire();

    /*!
     * \brief getDuree
     * \return durée de la tache unitaire
     */
    const Duree& getDuree() const{
        return duree;
    }
    /*!
     * \brief modifie la durée de la tache
     * \param d : nouvelle durée
     */
    void setDuree(Duree d){
        duree=d;
    }

    /*!
     * \brief rend la tache preemptive, aucun effet si elle l'est déjà
     */
    void setPreemptive(){preemptive=true;}

    /*!
     * \brief rend la tache non preemptive, aucun effet si elle l'est déjà
     */
    void setNonPreemptive(){preemptive=false;}


    /*!
     * \brief place l'attribut scheduled à true, aucun effet si il l'est déjà
     */
    void setScheduled(){
        if(scheduled!=true)
            scheduled=true;
    }

    /*!
     * \brief place l'attribut scheduled à false, aucun effet si il l'est déjà
     */
    void setNonScheduled(){
        if(scheduled!=false)
            scheduled=false;
    }
    /*!
      *\brief permet de savoir si la tache est programmé
      */
    bool isScheduled()const{
        if(scheduled==true)return true;
        else return false;
    }
};

#endif
