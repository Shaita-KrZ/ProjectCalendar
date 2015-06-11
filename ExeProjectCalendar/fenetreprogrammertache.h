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
    Projet * proj;
    Tache * t1;
    Tache * t2;
    Q_OBJECT

public:
    explicit FenetreProgrammerTache(FenAgenda * f, QWidget *parent = 0);
    ~FenetreProgrammerTache();


private slots:
    void on_inProjet_activated(const QString &arg1);

    void on_inTache_activated(const QString &arg1);

    void on_inTache2_activated(const QString &arg1);

    void on_bOK_accepted();

private:
    Ui::FenetreProgrammerTache *ui;
};

#endif // FENETREPROGRAMMERTACHE_H
