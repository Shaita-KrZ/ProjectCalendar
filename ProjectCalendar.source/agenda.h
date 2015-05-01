#ifndef EMPLOIDUTEMPS
#define EMPLOIDUTEMPS
#include <QtWidgets>

//ce sera l'interface graphique de l'emploi du temps
//A faire
class agenda: public QWidget{
    Q_OBJECT
public:
    explicit agenda(QWidget *parent=0);
private:
    QPushButton *buttontest;
};

#endif // EMPLOIDUTEMPS

