#include "programmation.h"


QDate Programmation::getLundi() const{
    QDate jourLundi=getDate().addDays(-(getDate().dayOfWeek()-1));
    return jourLundi;
}
