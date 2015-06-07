#ifndef PROJET_H
#define PROJET_H
#include "tachemanager.h"
#include "precedencemanager.h"
#include <QXmlStreamReader>
#include <QFile>
#include <QTextCodec>
#include <QDebug>
#include <QMessageBox>

/*!
 * \brief The Projet class
 */
class Projet
{
private:
    QString titre;
    TacheManager taches;
    PrecedenceManager precedences;
    QDate echeance;
    friend class ProjetManager;
public:
    // Modifie la date d'echeance du projet avec le parametre e
    void setEcheance(const QDate & e);
    /*!
     * \brief Constructeur de la classe
     *      Construit un projet vide
     * \param t : titre du projet
     */
    Projet(const QString & t);
    ~Projet();

    /*!
     * \brief getTitre
     * \return titre du projet
     */
    QString getTitre() const{return titre;}

    /*!
     * \brief Modifie le titre du projet
     * \param t : nouveau titre
     */
    void setTitre(const QString & t){titre=t;}

    /*!
     * \brief getEcheance
     * \return echeance du projet
     */
    QDate getEcheance() const{return echeance;}
    /*!
     * \brief getTaches
     * \return la liste de taches sous forme de TacheManager
     */
    const TacheManager& getTaches()const{return taches;}

    /*!
     * \brief getPrecedences
     * \return la liste de precedences sous forme de PrecedenceManager
     */
    PrecedenceManager getPrecedences()const{return precedences;}
};

#endif // PROJET_H
