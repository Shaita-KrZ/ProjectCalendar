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
    void addBouton(const QString& titre);
    void supprimerBouton(const QString &titre);
    QPushButton* trouverBouton(const QString& titre);
private:
    QGridLayout *couche;
    QLabel *presentation;
    QPushButton *supprimerProjet;
    QPushButton *creeProjet;
    QPushButton *importerProjet;
    QVBoxLayout *listeProjets;
    map<QString,QPushButton*>boutonProjets;
    map<QString,QPushButton*>boutonModifTache;
    QLineEdit* titreProjetLine;
    QDateTimeEdit *echeanceProjetLine;
    QWidget *fenetreCreeProjet;
    QWidget *fenetreTitreProjet;
    QLabel *titreProjet;
    QString titreProj;
    QWidget *fenetreModifTache;
    QDateTimeEdit *dateDispoTacheLine;
    QDateTimeEdit *dateEcheTacheLine;
    QSpinBox *dureeTacheLine;
    QLineEdit *titreTacheLine;
    QCheckBox *preemptive;
    QLineEdit **titreTacheCompoLine;
    QDateTimeEdit **dateDispoTacheCompoLine;
    QDateTimeEdit **dateEcheTacheCompoLine;
    QSpinBox **dureeTacheCompoLine;
    QCheckBox **preemptiveCompo;
    Tache *TacheaModif;
    QWidget *Fenetreprojet;

public slots:
    void chargerProjet();
    void ouvrirProjet();
    void supprimeProjet();
    void creationProjet();
    void validerProjet();
    void annulerProjet();
    void modifierTitreProjet();
    void validerTitreProjet();
    void annulerTitreProjet();
    void modifierTache();
    void validermodifTache();
    void annulermodifTache();
    void ajouterTache();
};


#endif // GESTIONPROJETS_H
