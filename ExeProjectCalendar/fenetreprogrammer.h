#ifndef FENETREPROGRAMMER_H
#define FENETREPROGRAMMER_H

#include <QWidget>

namespace Ui {
class FenetreProgrammer;
}

class FenetreProgrammer : public QWidget
{
    Q_OBJECT

public:
    explicit FenetreProgrammer(QWidget *parent = 0);
    ~FenetreProgrammer();

private slots:
    void on_bOKCancel_rejected();

    void on_bActiviteTraditionnelle_clicked();

private:
    Ui::FenetreProgrammer *ui;
};

#endif // FENETREPROGRAMMER_H
