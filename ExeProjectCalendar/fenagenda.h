#ifndef FENAGENDA_H
#define FENAGENDA_H

#include <QWidget>
#include "semaine.h"
#include <iostream>
#include "agenda.h"

namespace Ui {
class FenAgenda;
}

class FenAgenda : public QWidget
{
    Q_OBJECT
    Semaine sem;

public:
    explicit FenAgenda(Semaine s, QWidget *parent = 0);
    ~FenAgenda();

private slots:
    void on_bSemaineSuiv_clicked();

private:
    Ui::FenAgenda *ui;
};

#endif // FENAGENDA_H
