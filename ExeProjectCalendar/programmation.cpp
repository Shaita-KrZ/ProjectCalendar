#include "programmation.h"


QDate Programmation::getLundi() const{
    QDate jourLundi=getDate().addDays(-(getDate().dayOfWeek()-1));
    return jourLundi;
}

QString Programmation::toString() const {
    QString str;
    str = this->getEvent()->getTitre();
    str += "  -> de ";
    str += this->getHoraireDebut().toString();
    str += " à ";
    QTime horaireFin = this->getHoraireDebut().addSecs(this->getEvent()->getDuree().getDureeEnMinutes()*60);
    str += horaireFin.toString();
    return str;
}


bool operator<(Programmation const &p1, Programmation const &p2){
    return(p1.getDate()<p2.getDate() || (p1.getDate()==p2.getDate() && p1.getHoraireDebut() < p2.getHoraireDebut()));
}


bool compareProg(const Programmation * const & p1, const Programmation * const & p2)
{
    return(p1->getDate()<p2->getDate() || (p1->getDate()==p2->getDate() && p1->getHoraireDebut() < p2->getHoraireDebut()));
}
