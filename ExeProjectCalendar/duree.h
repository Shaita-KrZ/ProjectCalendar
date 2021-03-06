#ifndef DUREE_H
#define DUREE_H
#include <QTextStream>
#include "exception.h"


//Class duree
/*!
 * \class Duree
 * \brief Represente une duree
 */
class Duree{
public:
    Duree(unsigned int h, unsigned int m):nb_minutes(h*60+m) {if (m>59) throw CalendarException("erreur: initialisation duree invalide");}
    Duree(unsigned int m=0):nb_minutes(m) {}
    /*!
     * \brief modifie la duree
     * \param minutes
     * \return Retourne rien
     */
    void setDuree(unsigned int minutes) { nb_minutes=minutes; }
    void setDuree(unsigned int heures, unsigned int minutes) { if (heures==0 && minutes>59) throw CalendarException("erreur: initialisation duree invalide"); nb_minutes=heures*60+minutes; }
    unsigned int getDureeEnMinutes() const { return nb_minutes; } //<!Retourne la duree en minutes
    double getDureeEnHeures() const { return double(nb_minutes)/60; } //<!Retourne la duree en heures
    unsigned int getMinute() const { return nb_minutes%60; }
    unsigned int getHeure() const { return nb_minutes/60; }
    void afficher(QTextStream& f) const; //<!Affiche la duree sous le format hhHmm
    Duree& operator+=(const Duree& d);
private:
    unsigned int nb_minutes;

};

QTextStream& operator<<(QTextStream& f, const Duree & d);
QTextStream& operator>>(QTextStream&, Duree&); //lecture format hhHmm

#endif // DUREE_H

