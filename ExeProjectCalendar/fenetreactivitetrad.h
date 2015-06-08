#ifndef FENETREACTIVITETRAD_H
#define FENETREACTIVITETRAD_H

#include <QDialog>

namespace Ui {
class FenetreActiviteTrad;
}

class FenetreActiviteTrad : public QDialog
{
    Q_OBJECT

public:
    explicit FenetreActiviteTrad(QWidget *parent = 0);
    ~FenetreActiviteTrad();

private slots:
    void on_bOKcancel_accepted();

private:
    Ui::FenetreActiviteTrad *ui;
};

#endif // FENETREACTIVITETRAD_H
