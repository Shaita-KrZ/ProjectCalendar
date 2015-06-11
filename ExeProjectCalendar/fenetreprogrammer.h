#ifndef FENETREPROGRAMMER_H
#define FENETREPROGRAMMER_H

#include <QWidget>
#include "fenetrePrincipal.h"

namespace Ui {
class FenetreProgrammer;
}

class FenetreProgrammer : public QWidget
{
    Q_OBJECT
    FenAgenda * fenAg;

public:
    explicit FenetreProgrammer(FenAgenda * f, QWidget *parent = 0);
    ~FenetreProgrammer();

private slots:
    void on_bOKCancel_rejected();

    void on_bActiviteTraditionnelle_clicked();

    void on_bTache_clicked();

private:
    Ui::FenetreProgrammer *ui;
};

#endif // FENETREPROGRAMMER_H
