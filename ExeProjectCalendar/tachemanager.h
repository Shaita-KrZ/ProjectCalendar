#ifndef TACHEMANAGER_H
#define TACHEMANAGER_H
#include <tache.h>
#include <qDebug>

/*!
 * \class TacheManager
 * \brief Objet qui manipule la liste des taches d'un projet
 */
class TacheManager
{
private:
    map<QString, Tache*> taches;
public:

    /*!
     * \brief Constructeur
     */
    TacheManager();

    /*!
     * \brief Detruit l'objet ainsi que toutes les taches qui le composent
     */
    ~TacheManager();

    /*!
     * \brief Construit une tache et l'ajoute dans la liste, à condition qu'une tache du même id
     *      n'existe pas déjà
     * \param id
     * \param t
     * \param disp
     * \param ech
     * \param d
     * \param p
     */
    void addTache(const QString id, const QString t, const QDate disp, const QDate ech, Projet *pp,const Duree d, const bool p);
    void addTache(const QString id, const QString t, const QDate disp,const QDate ech,Projet *p);

    /*!
     * \brief Cherche une tache
     * \param id : identifiant de la tache recherchée
     * \return la Tache recherchée, NULL si inexistante
     */
    Tache* getTache(const QString id) const;

    /*!
     * \brief Supprime une tache
     * \param id : identifiant de la tache à supprimer
     */
    void delTache(const QString id);
    /*!
     * \brief getTaches
     * \return la liste des taches de tacheManager
     */
    map<QString, Tache*> getTaches() const{
        return taches;
    }
};

#endif // TACHEMANAGER_H
