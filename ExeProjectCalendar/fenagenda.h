#ifndef FENAGENDA_H
#define FENAGENDA_H

#include <QWidget>
#include "semaine.h"
#include <iostream>

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

private:
    Ui::FenAgenda *ui;
};

#endif // FENAGENDA_H
