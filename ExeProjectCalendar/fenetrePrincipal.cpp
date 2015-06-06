#include "fenetrePrincipal.h"
#include "ui_fenetrePrincipal.h"

FenAgenda::FenAgenda(Semaine s, QWidget *parent) :
    sem(s),
    QWidget(parent),
    ui(new Ui::FenAgenda),
    gestionproj(10)
{
    ui->setupUi(this);

    QObject::connect(ui->bGoProjets,SIGNAL(clicked()),this,SLOT(gestionProjet()));
    ui->labelSemaine->setText("Semaine du " + sem.getLundi().toString("dd/MM/yyyy") + " au " + sem.getLundi().addDays(6).toString("dd/MM/yyyy"));
}

FenAgenda::~FenAgenda()
{
    delete ui;
}

//ouvrir l'interface de mon projet
void FenAgenda::gestionProjet(){
    gestionproj.show();
}
