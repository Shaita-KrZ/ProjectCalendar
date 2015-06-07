#ifndef GESTIONPROJETS_H
#define GESTIONPROJETS_H
#include <QWidget>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include "projetmanager.h"
#include <QFileDialog>
#include <QInputDialog>
#include <QDateTimeEdit>
#include <QSpinBox>
#include <QCheckBox>



class Gestionprojets : public QWidget
{
    Q_OBJECT

public:
    explicit Gestionprojets(QWidget *parent = 0);
    void ajouterBouton(const QString& titre);
    void supprimerBouton(const QString &titre);
    QPushButton* trouverBouton(const QString& titre);
private:
    /* ****** WIDGET Constructeur ******* */
    bool m_bool;
    QVBoxLayout *m_couche;
    QLabel *m_presentation;
    QPushButton *m_supprimerProjet;
    QPushButton *m_creeProjet;
    QPushButton *m_importerProjet;
    QLabel *m_listeProj;
    /* ****** FIN WIDGET Constructeur ******* */

    /* ****** WIDGET OUVRIR PROJET ******* */
    QWidget *m_fenetreProjet;
    QLabel *m_titreProjet;
    QString m_titreProj;
    map<QString,QPushButton*>m_boutonProjets;
    map<QString,QPushButton*>m_boutonModifTache;
    /* ****** FIN WIDGET OUVRIR PROJET ******* */

    /* ****** WIDGET CREER PROJET ******* */
    QWidget *m_fenetreCreeProjet;
    QLineEdit* m_titreProjetLine;
    QDateTimeEdit *m_echeanceProjetLine;
    /* ****** FIN WIDGET CREER PROJET ******* */

    /* ****** WIDGET MODIFIER TACHE ******* */
    //Ces variables vont permettent de récupérer les caracteristiques entrés par l'utilisateur
    QWidget *m_fenetreModifTache;
    Tache *m_tacheModif;
    QLineEdit *m_titreTacheLine;
    QCheckBox *m_preempTache;
    QDateTimeEdit *m_dateDispoTacheLine;
    QDateTimeEdit *m_dateEcheTacheLine;
    QSpinBox *m_dureeTacheLine;
    QLineEdit **m_titreTacheCompoLine;
    QDateTimeEdit **m_dateDispoTacheCompoLine;
    QDateTimeEdit **m_dateEcheTacheCompoLine;
    QSpinBox **m_dureeTacheCompoLine;
    QCheckBox **m_preemptiveCompo;

    /* ****** FIN WIDGET MODIFIER TACHE ******* */

    /* ***** WIDGET  AJOUTER UNE TACHE ***** */
    QWidget *m_fenetreAjoutTache;
    QLineEdit *m_idTacheLine;
    Projet *m_projetModif;
    QCheckBox *m_isTacheCompo;
    QWidget *m_fenetreModifTacheCompo;
    /* ***** FIN WIDGET  AJOUTER UNE TACHE ***** */
public slots:
    void chargerProjet();
    void ouvrirProjet();
    void supprimeProjet();
    void creationProjet();
    void validerCreationProjet();
    void annulerCreationProjet();

    void modifierTitreProjet();

    void modifierTache();
    void validermodifTache();
    void annulermodifTache();
    void ajouterTache();
    void validerajoutTache();
    void annulerajoutTache();
    void afficherDuree(int state);
    void ajouterTacheCompo();
    void validerajoutTacheCompo();
    void annulerajoutTacheCompo();
};


#endif // GESTIONPROJETS_H
