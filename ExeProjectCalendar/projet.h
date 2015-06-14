#ifndef PROJET_H
#define PROJET_H
#include "tachemanager.h"
#include "precedencemanager.h"
#include <QXmlStreamReader>
#include <QXmlStreamWriter>
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
    /*!
     * \brief Constructeur de la classe
     *      Construit un projet vide
     * \param t : titre du projet
     */
    Projet(const QString & t);
    ~Projet();

    /*!
     * \brief modifie l'echeance du projet
     * \param e : nouvel echeance
     */
    void setEcheance(const QDate & e);

    /*!
     * \brief getEcheance
     * \return echeance du projet
     */
    QDate getEcheance() const{return echeance;}


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
     * \brief getTaches
     * \return la liste de taches sous forme de TacheManager
     */
    TacheManager getTaches(){return taches;}

    /*!
     * \brief getPrecedences
     * \return la liste de precedences sous forme de PrecedenceManager
     */
    PrecedenceManager& getPrecedences(){return precedences;}
};

#endif // PROJET_H
