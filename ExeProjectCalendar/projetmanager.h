#ifndef PROJETMANAGER_H
#define PROJETMANAGER_H
#include <projet.h>

/*!
 * \brief The ProjetManager class
 *      La classe implemente le design pattern Singleton
 */
class ProjetManager
{
private:
    static ProjetManager * instance;
    map<QString, Projet*> projets;
    QString file;
    ProjetManager();
public:
    ~ProjetManager();
    /*!
     * \brief Recupere une reference vers le ProjetManager,
     *      Le cree s'il n'existe pas
     * \return reference vers le ProjetManager
     */
    static ProjetManager & getInstance();

    /*!
     * \brief Detruit l'instance du ProjetManager,
     *      Aucun effet si l'instance n'existe pas
     */
    static void libererInstance();

    /*!
     * \brief Cree un projet vide de titre t et l'ajoute a la liste de projets
     * \param t : titre du nouveau projet
     * \throw CalendarException si un projet du meme nom existe deja
     */
    void creerProjet(const QString & t,unsigned int nbPrec);

    /*!
     * \brief Modifie le titre du projet
     * \param projet : titre du projet a modifier
     * \param nouveauT : nouveau titre
     * \throw CalendarException si un projet de titre nouveauT existe deja
     */
    void modifierNomProjet(QString & projet, const QString & nouveauT);

    /*!
     * \brief Supprime un projet (ainsi que toutes ses taches)
     * \param t : titre du projet a supprimer
     * \throw CalendarException si le projet n'existe pas
     */
    void supprimerProjet(const QString & t);

    /*!
     * \brief Recupere une reference vers un projet
     * \param t : titre du projet a recuperer
     * \return reference vers le projet
     * \throw CalendarException si le projet n'existe pas
     */
    Projet & getProjet(const QString& t);

    /*!
     * \brief Importe un fichier XML
     * \param f : chemin du fichier a charger
     */
    void load(const QString& f);

    /*!
     * \brief Exporte le projet dans un fichier XML
     * \param f : chemin du fichier dans lequel sauvegarder
     */
    void  save(const QString& f,const QString& titreProjet);
    map<QString,Projet*> getProjets() const { return projets;}
};

#endif // PROJETMANAGER_H
