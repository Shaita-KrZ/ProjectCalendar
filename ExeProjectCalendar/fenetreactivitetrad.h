#ifndef FENETREACTIVITETRAD_H
#define FENETREACTIVITETRAD_H

#include <QDialog>
#include "duree.h"
#include "programmation.h"
#include "activitetraditionnelle.h"
#include "fenetrePrincipal.h"

namespace Ui {
class FenetreActiviteTrad;
}

class FenetreActiviteTrad : public QDialog
{
    Q_OBJECT
    FenAgenda * fenAg;

public:
    explicit FenetreActiviteTrad(FenAgenda * f, QWidget *parent = 0);
    ~FenetreActiviteTrad();

private slots:
    void on_bOKcancel_accepted();

private:
    Ui::FenetreActiviteTrad *ui;
};

#endif // FENETREACTIVITETRAD_H
