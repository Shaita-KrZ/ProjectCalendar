#include "fenetrePrincipal.h"
#include "ui_fenetrePrincipal.h"
#include "fenetreprogrammer.h"

FenAgenda::FenAgenda(Semaine * s, QWidget *parent) :
    sem(s),
    QWidget(parent),
    ui(new Ui::FenAgenda)
{
    ui->setupUi(this);
    QObject::connect(ui->bGoProjets,SIGNAL(clicked()),this,SLOT(gestionProjet()));
    this->actualiserItems();
}

void FenAgenda::actualiserItems()
{
    ui->labelSemaine->setText("Semaine du " + sem->getLundi().toString("dd/MM/yyyy") + " au " + sem->getLundi().addDays(6).toString("dd/MM/yyyy"));
    ui->tSemaine->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);

    // Inititialisation du semainier
    ui->tSemaine->setItem(1,-1,new QTableWidgetItem(this->sem->jourToString(1)));
    ui->tSemaine->setItem(1,0,new QTableWidgetItem(this->sem->jourToString(2)));
    ui->tSemaine->setItem(1,1,new QTableWidgetItem(this->sem->jourToString(3)));
    ui->tSemaine->setItem(1,2,new QTableWidgetItem(this->sem->jourToString(4)));
    ui->tSemaine->setItem(1,3,new QTableWidgetItem(this->sem->jourToString(5)));
    ui->tSemaine->setItem(1,4,new QTableWidgetItem(this->sem->jourToString(6)));
    ui->tSemaine->setItem(1,5,new QTableWidgetItem(this->sem->jourToString(7)));
    ui->tSemaine->resizeColumnsToContents();
}

void FenAgenda::goSemaine(const QDate &dateLundi)
{
    Agenda & a = Agenda::getInstance();
    try{
        a.creerSemaine(dateLundi);
    }
    catch (CalendarException &e){
        QMessageBox::critical(this, "Semaine Suivante", e.getInfo());
    }
    Semaine * semSuivante = a.getSemaines().at(dateLundi);
    sem=semSuivante;
}

FenAgenda::~FenAgenda()
{
    delete ui;
}


void FenAgenda::on_bSemaineSuiv_clicked()
{
    QDate dateNewSem = sem->getLundi().addDays(7);
    this->goSemaine(dateNewSem);
    this->actualiserItems();
}
//ouvrir l'interface de mon projet
void FenAgenda::gestionProjet(){
    this->close();
    gestionproj.show();
}

void FenAgenda::programmerEvenement()
{
    FenetreProgrammer * f = new FenetreProgrammer();
    f->show();
}


void FenAgenda::on_bSemainePrec_clicked()
{
    QDate dateNewSem = sem->getLundi().addDays(-7);
    this->goSemaine(dateNewSem);
    this->actualiserItems();
}


void FenAgenda::on_bProgrammer_clicked()
{
    programmerEvenement();
}
