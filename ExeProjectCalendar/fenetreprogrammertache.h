#ifndef FENETREPROGRAMMERTACHE_H
#define FENETREPROGRAMMERTACHE_H

#include <QDialog>
#include "fenetrePrincipal.h"
#include "projetmanager.h"

namespace Ui {
class FenetreProgrammerTache;
}

class FenetreProgrammerTache : public QDialog
{
    FenAgenda * fenAg;
    Q_OBJECT

public:
    explicit FenetreProgrammerTache(FenAgenda * f, QWidget *parent = 0);
    ~FenetreProgrammerTache();


private:
    Ui::FenetreProgrammerTache *ui;
};

#endif // FENETREPROGRAMMERTACHE_H
