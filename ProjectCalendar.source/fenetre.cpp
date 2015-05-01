#include "fenetre.h"

accueil::accueil(QWidget *parent):QWidget(parent){
    /*on crée le layout dynamique vertical avec comme
    parent (fenetre) l'objet lui meme(qui est un widget=fenetre) */
    layout=new QVBoxLayout(this);

    //module d'onglets
    onglets=new QTabWidget();
    //3fenetres
    presentation=new QWidget;
    empTemps=new QWidget;
    projet=new QWidget;

    //fenetre presentation
    label=new QLabel("Bienvenu sur ce projet. \n Vous pouvez gérer vos projets et consulter votre agenda.\n",presentation);
    quitter=new QPushButton("Quitter");
    //infobulle lorsque la souris passe sur le bouton
    quitter->setToolTip("Quittez l'application");
    //afficher une main au niveau du bouton
    quitter->setCursor(Qt::PointingHandCursor);
    vbox1=new QVBoxLayout();
    vbox1->addWidget(label);
    vbox1->addWidget(quitter);
    presentation->setLayout(vbox1);

    //fenetre agenda : afficher emploi du temps?
    a=new agenda(empTemps);

    //fenetre projets : afficher liste projets ? treeview?
    proj=new projetediteur(10,projet);

    //caracteristiques des onglets
    onglets->addTab(presentation,"Presentation");
    onglets->addTab(empTemps,"Agenda");
    onglets->addTab(projet,"Projets");
    layout->addWidget(onglets);

    //Les signaux
    QObject::connect(quitter,SIGNAL(clicked()),this,SLOT(close()));
}
