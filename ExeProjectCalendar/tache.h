#ifndef TACHE_H
#define TACHE_H
#include <QDate>
#include <QString>
#include "evenement.h"
#include <map>
using namespace std;

class Projet;

/*!
 * \class Tache
 * \brief Classe abstraite representant une tache d'un projet
 */
class Tache: public Evenement{
protected:
    QString identificateur;
    QDate disponibilite;
    QDate echeance;
    Projet *pere;
public:
    /*!
     * \brief Constructeur d'une tache
     * \param t
     * \param id
     * \param dispo
     * \param ech
     * \param pere
     */
    Tache(QString t, QString id, QDate dispo, QDate ech, Projet *p);
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

    void setDispo(const QDate& d){disponibilite=d;}

    /*!
     * \brief getDisponibilite
     * \return disponibilite de la tache
     */
    QDate getDisponibilite(){
        return disponibilite;
    }

    void setEche(const QDate& e){echeance=e;}
    /*!
     * \brief getEcheance
     * \return echeance de la tache
     */
    QDate getEcheance(){
        return echeance;
    }
    /*!
     * \brief getDuree
     * \return Duree d'une tache
     */
    virtual Duree getDuree() const=0;


    /*!
     * \brief verifie le type de la tache
     * \return true si la tache est composite, false sinon
     */
    virtual bool estComposite() const=0;

    /*!
     * \brief Verifie que l'objet est une tache
     * \return true
     */
    virtual bool estTache() const{ return true;}

    /*!
     * \brief Verifie si la tache est programmee
     * \return true si la tache est programmee, false sinon
     */
    virtual bool isScheduled()const=0;

    /*!
     * \brief Permet d'acceder au projet pere de la tache
     * \return pointeur vers le projet pere de la tache
     */
    virtual Projet* getPere()const {return pere;}

    /*!
     * \brief verifie si la tache est preemptive
     * \return retourne la valeur de preemptive
     */
    virtual bool isPreemptive()const=0;

    /*!
     * \brief accède à la liste des taches composantes si self est composite
     * \return map des taches composantes
     * \throw CalendarException si la tache n'est pas composite
     */
    virtual map<QString, Tache*> getTaches() const = 0;

    /*!
     * \brief place l'attribut scheduled à true, aucun effet si il l'est déjà
     * \throw CalendarException si la tache n'est pas unitaire
     */
    virtual void setScheduled()=0;

    /*!
     * \brief place l'attribut scheduled à false, aucun effet si il l'est déjà
     * \throw CalendarException si la tache n'est pas unitaire
     */
    virtual void setNonScheduled()=0;
};


class TacheComposite : public Tache
{
private:
    map<QString, Tache*> tachesCompo;
public:
    /*!
     * \brief Construit une tache composite vide
     * \param titre
     * \param id
     * \param dispo
     * \param ech
     * \param pere
     */
    TacheComposite(QString t, QString id, QDate dispo, QDate ech, Projet *p);
    virtual ~TacheComposite();

    /*!
     * \brief ajoute une tache dans la liste des taches
     * \param t : tache à ajouter
     * \throw CalendarException si la disponibilité de t est < à la disponibilite de self
     * \throw CalendarException si l'échéance de t est > à l'échéance de self
     * \throw CalendarException si une tache du même identifiant existe déjà
     */
    virtual void addTache(Tache* t);

    /*!
     * \brief Supprime la tache d'identifiant t de la liste
     *      aucun effet si la tache n'existe pas
     * \param id : identifiant de la tache à supprimer
     */
    void delTache(const QString & id);

    /*!
     * \brief vérifie si la tache est composite
     * \return true
     */
    virtual bool estComposite() const;

    /*!
     * \brief Somme des durees tes taches qui la compose
     * \return duree totale de la tache composite
     */
    virtual Duree getDuree() const;

    /*!
     * \brief getTaches
     * \return liste des taches composées
     */
    virtual map<QString, Tache*> getTaches() const{return tachesCompo;}

    /*!
     * \brief Verifie si la tache a ete programmee
     * \return true si toutes les taches composantes sont programmees, false sinon
     */
    virtual bool isScheduled()const{
        for(map<const QString, Tache*>::const_iterator it=tachesCompo.begin(); it!=tachesCompo.end(); ++it){
            if (!it->second->isScheduled())
                return false;
        }
        return true;
    }

    /*!
     * \brief verifie si la tache est preemptive
     * \return false
     */
    virtual bool isPreemptive()const{
        return false;
    }

    /*!
     * \brief place l'attribut scheduled à true, aucun effet si il l'est déjà
     * \throw CalendarException si la tache n'est pas unitaire
     */
    virtual void setScheduled(){
        throw CalendarException("Erreur : la tache n'est pas unitaire");
    }

    /*!
     * \brief place l'attribut scheduled à false, aucun effet si il l'est déjà
     * \throw CalendarException si la tache n'est pas unitaire
     */
    virtual void setNonScheduled(){
        throw CalendarException("Erreur : la tache n'est pas unitaire");
    }
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
    TacheUnitaire(const QString titre, const QString id, const QDate dispo, const QDate ech, Projet *p,
                  const bool preem, const Duree dur);
    virtual ~TacheUnitaire();
    /*!
     * \brief verifie si la tache est preemptive
     * \return retourne la valeur de preemptive
     */
    virtual bool isPreemptive()const{ return preemptive;}
    /*!
     * \brief getDuree
     * \return durée de la tache unitaire
     */
    virtual Duree getDuree() const;
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
    virtual void setScheduled(){
        if(scheduled!=true)
            scheduled=true;
    }

    /*!
     * \brief place l'attribut scheduled à false, aucun effet si il l'est déjà
     */
    virtual void setNonScheduled(){
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

    /*!
     * \brief Verifie si la tache est compos
     * \return
     */
    virtual bool estComposite() const;

    /*!
     * \brief accède à la liste des taches composantes si self est composite
     * \return map des taches composantes
     * \throw CalendarException si la tache n'est pas composite
     */
    virtual map<QString, Tache*> getTaches() const{throw CalendarException("Erreur : La tache n'est pas composite");}

};

#endif
