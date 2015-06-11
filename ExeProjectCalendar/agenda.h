#ifndef AGENDA_H
#define AGENDA_H

#include "semaine.h"

/*!
 * \brief Agenda - implemente singleton
 */
class Agenda
{
private:
    static Agenda* instance;
    map<const QDate, Semaine*> semaines;
    QString file;
    Agenda(){}
    ~Agenda();
public:
    /*!
     * \brief Cree l'agenda s'il n'existe pas encore, le retourne dans tous les cas
     * \return l'instance unique d'agenda
     */
    static Agenda & getInstance();

    /*!
     * \brief Detruit l'agenda. Aucun effet si l'agenda n'existe pas.
     */
    static void libererInstance();

    /*!
     * \brief Cree et ajoute une semaine dans l'agenda; aucun effet si la semaine existe deja
     * \param lundi
     * \throw CalendarException si la date en parametre ne correspond pas a un lundi
     */
    void creerSemaine(const QDate & lundi);

    /*!
     * \brief Permet d'acceder a la map des semaines
     * \return semaines
     */
    map<const QDate, Semaine*> getSemaines(){return semaines;}

    /*!
     * \brief Ajoute la programmation p dans la semaine correspondante de l'agenda
     * \param p : programmation a ajouter
     * \throw CalendarException si la programmation ne peut pas être ajoutee
     */
    void addProgrammation(Programmation * p);

    /*!
     * \brief Exporte la semaine dans un fichier XML
     * \param f : chemin du fichier dans lequel sauvegarder
     */
    void save(const QString& f,const QDate lundi);
};

#endif // AGENDA_H
