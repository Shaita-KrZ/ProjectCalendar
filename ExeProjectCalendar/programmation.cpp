#include "programmation.h"


const QDate & Programmation::getLundi() const{
    QDate jourLundi = getDate().addDays(-(getDate().dayOfWeek()-1));
    return jourLundi;
}
