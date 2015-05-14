#ifndef CALENDAR_H
#define CALENDAR_H
#include <QtWidgets>

using namespace std;

/*!
 * \exception CalendarException
 * \brief declenche une exception
 */
class CalendarException{
public:
    CalendarException(const QString& message):info(message){}
    QString getInfo() const { return info; }
private:
    QString info;
};

//Class duree
/*!
 * \class Duree
 * \brief representer une duree
 */
class Duree{
public:
    Duree(unsigned int h, unsigned int m):nb_minutes(h*60+m) {if (m>59) throw CalendarException("erreur: initialisation duree invalide");}
    Duree(unsigned int m=0):nb_minutes(m) {}
    /*!
     * \brief modifie la duree
     * \param minutes : test
     * \return Retourne rien
     */
    void setDuree(unsigned int minutes) { nb_minutes=minutes; }
    void setDuree(unsigned int heures, unsigned int minutes) { if (heures==0 && minutes>59) throw CalendarException("erreur: initialisation duree invalide"); nb_minutes=heures*60+minutes; }
    unsigned int getDureeEnMinutes() const { return nb_minutes; } //<!Retourne la duree en minutes
    double getDureeEnHeures() const { return double(nb_minutes)/60; } //<!Retourne la duree en heures
    unsigned int getMinute() const { return nb_minutes%60; }
    unsigned int getHeure() const { return nb_minutes/60; }
    void afficher(QTextStream& f) const; //<!Affiche la duree sous le format hhHmm
private:
    unsigned int nb_minutes;
};

QTextStream& operator<<(QTextStream& f, const Duree & d);
QTextStream& operator>>(QTextStream&, Duree&); //lecture format hhHmm

//Classe Tache
class Tache{
public:
    QString getId() const { return identificateur; }
    void setId(const QString& str);
    QString getTitre() const { return titre; }
    void setTitre(const QString& str) { titre=str; }
    Duree getDuree() const { return duree; }
    void setDuree(const Duree& d) { duree=d; }
    QDate getDateDisponibilite() const {  return disponibilite; }
    QDate getDateEcheance() const {  return echeance; }
    void setDatesDisponibiliteEcheance(const QDate& disp, const QDate& e) {
        if (e<disp) throw CalendarException("erreur Tâche : date echéance < date disponibilité");
        disponibilite=disp; echeance=e;
    }
    bool isPreemptive() const { return preemptive; }
    void setPreemptive() { preemptive=true; }
    void setNonPreemptive() { preemptive=false; }
private:
    QString identificateur;
    QString titre;
    Duree duree;
    bool preemptive;
    QDate disponibilite;
    QDate echeance;
    Tache **sousTaches;
    Tache **Tacheprec;
    Tache(const QString& id, const QString& t, const Duree& dur, const QDate& dispo, const QDate& deadline, bool preempt=false):
            identificateur(id),titre(t),duree(dur),disponibilite(dispo),echeance(deadline),preemptive(preempt),sousTaches(0),Tacheprec(0){}
    Tache(const Tache& t);
    Tache& operator=(const Tache&);
    friend class Projet;
};

QTextStream& operator<<(QTextStream& f, const Tache& t);

class Projet{
public:
    //Charger un projet a partir d'un fichier xml
    void load(const QString& f);
    QString file;
    //constructeur/destructeur
    Projet():taches(0),nbT(0),nbTMax(0),titreProjet(""){}
    ~Projet();
    //Ajouter une tache
    void addItem(Tache* t);
    //Trouver une tache a partir de son ID
    Tache* trouverTache(const QString& id) const;
    //Ajouter une tache a partir de ses caracteristiques
    Tache& ajouterTache(const QString& id, const QString& t, const Duree& dur, const QDate& dispo, const QDate& deadline, bool preempt=false);


    QString getTitreProjet() const { return titreProjet; }
    void setTitreProjet(const QString& str) { titreProjet=str; }

    //Parcourir les taches du projet
    class iterateur{
    friend class Projet;
    private:
        Tache **current;
        iterateur(Tache **c):current(c){}
    public:
        iterateur():current(0){}
        iterateur& operator++(){current++; return *this;}
        Tache* operator*(){return *current;}
        bool operator!=(const iterateur &it){return current!=it.current;}
    };
    iterateur begin()const{return iterateur(taches);}
    iterateur end()const{return iterateur(taches+nbT);}
private:
    Tache ** taches;
    QString titreProjet;
    unsigned int nbT;
    unsigned int nbTMax;
};

class ProjetManager{
private:
    static ProjetManager *Instance;
    Projet **projets;
    unsigned int nb;
    unsigned int nbMax;
    //design pattern singleton
    ProjetManager(unsigned int n):nb(0),nbMax(n), projets(new Projet*[n]){}
    ~ProjetManager(){}
    ProjetManager(const ProjetManager &P);
    ProjetManager& operator=(const ProjetManager &P);
public:
    Projet* operator[](unsigned int i){return projets[i];}
    void ajouterProjet(Projet *P);
    static ProjetManager& getInstance();
    static void libererInstance();
};
#endif // CALENDAR_H

