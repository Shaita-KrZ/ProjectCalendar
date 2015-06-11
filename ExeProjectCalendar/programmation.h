#ifndef PROGRAMMATION_H
#define PROGRAMMATION_H
#include "tache.h"

/*!
 * \brief Classe qui associe un Evenement a une date et une horaire
 */
class Programmation
{
private:
    QDate date;
    QTime horaireDebut;
    Evenement * event;
public:
    /*!
     * \brief Constructeur de l'objet Programmation
     */
    Programmation(QDate d, QTime hd, Evenement * e):
        date(d), horaireDebut(hd), event(e){}

    virtual ~Programmation(){delete event;}

    QDate getDate() const{ return date;}

    /*!
     * \brief Permet d'acceder a l'horaire de debut
     * \return
     */
    QTime getHoraireDebut() const {return horaireDebut;}

    /*!
     * \brief Permet d'acceder a l'evement programmé
     * \return un pointeur sur l'attribut en evenement
     */
    Evenement * getEvent() const {return event;}

    /*!
     * \brief recupere la date du lundi de la semaine correspondant a la programmation
     * \return date du lundi correspondant a la date de l'evenement
     */
    QDate getLundi() const;

    /*!
     * \brief Compare deux programmations
     * \param p : Programmation a comparer avec self
     * \return true si les programmations sont les memes, false sinon
     */
    bool operator==(const Programmation & p) const {return (event==p.getEvent() && date==p.getDate() && horaireDebut==p.getHoraireDebut());}

    /*!
     * \brief Retourne une chaine contenant le titre de l'envenement, son horaire debut et son horaire de fin.
     * \return
     */
    QString toString() const;
};

/*!
 * \brief compare les dates des deux programmations
 * \param p1
 * \param p2
 * \return true si p1 se passe avant p2
 */
bool operator<(Programmation const & p1, Programmation const & p2);

/*!
 * \brief compare les dates des deux programmations (pointeur)
 * \param p1
 * \param p2
 * \return true si p1 se passe avant p2
 */
bool compareProg(const Programmation * const &p1, const Programmation * const &p2);


#endif // PROGRAMMATION_H
