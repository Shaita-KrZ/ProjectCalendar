#ifndef FENAGENDA_H
#define FENAGENDA_H

#include <QWidget>
#include "semaine.h"
#include <iostream>
#include "agenda.h"
#include "fenetreGestionProjet.h"

namespace Ui {
class FenAgenda;
}

class FenAgenda : public QWidget
{
    Q_OBJECT
    Semaine * sem;
    Gestionprojets gestionproj;

public:
    explicit FenAgenda(Semaine *s, QWidget *parent = 0);
    void actualiserItems();
    void goSemaine(const QDate & dateLundi);
    ~FenAgenda();

private slots:
    void on_bSemaineSuiv_clicked();

    void on_bSemainePrec_clicked();

private:
    Ui::FenAgenda *ui;
public slots:
    void gestionProjet();
};

#endif // FENAGENDA_H
