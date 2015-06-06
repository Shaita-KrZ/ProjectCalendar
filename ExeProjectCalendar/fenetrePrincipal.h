#ifndef FENAGENDA_H
#define FENAGENDA_H

#include <QWidget>
#include "semaine.h"
#include <iostream>
#include "fenetreGestionProjet.h"

namespace Ui {
class FenAgenda;
}

class FenAgenda : public QWidget
{
    Q_OBJECT
    Semaine sem;
    Gestionprojets gestionproj;

public:
    explicit FenAgenda(Semaine s, QWidget *parent = 0);
    ~FenAgenda();

private:
    Ui::FenAgenda *ui;
public slots:
    void gestionProjet();
};

#endif // FENAGENDA_H
