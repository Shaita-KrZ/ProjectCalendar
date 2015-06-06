#include "fenagenda.h"
#include "ui_fenagenda.h"

FenAgenda::FenAgenda(Semaine s, QWidget *parent) :
    sem(s),
    QWidget(parent),
    ui(new Ui::FenAgenda)
{
    ui->setupUi(this);

    ui->labelSemaine->setText("Semaine du " + sem.getLundi().toString("dd/MM/yyyy") + " au " + sem.getLundi().addDays(6).toString("dd/MM/yyyy"));
}

FenAgenda::~FenAgenda()
{
    delete ui;
}
