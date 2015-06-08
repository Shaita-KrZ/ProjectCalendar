#include "fenetreprogrammer.h"
#include "ui_fenetreprogrammer.h"
#include "fenetreactivitetrad.h"

FenetreProgrammer::FenetreProgrammer(FenAgenda *f, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FenetreProgrammer),
    fenAg(f)
{
    ui->setupUi(this);
}

FenetreProgrammer::~FenetreProgrammer()
{
    delete ui;
}

void FenetreProgrammer::on_bOKCancel_rejected()
{
    this->close();
}

void FenetreProgrammer::on_bActiviteTraditionnelle_clicked()
{
    FenetreActiviteTrad * fAT = new FenetreActiviteTrad(fenAg);
    fAT->show();
    this->close();
}
