#include "fenetreprogrammer.h"
#include "ui_fenetreprogrammer.h"
#include "fenetreactivitetrad.h"

FenetreProgrammer::FenetreProgrammer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FenetreProgrammer)
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
    FenetreActiviteTrad * fAT = new FenetreActiviteTrad();
    fAT->show();
    this->close();
}
