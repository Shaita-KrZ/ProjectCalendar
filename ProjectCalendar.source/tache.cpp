#include "tache.h"

Tache::Tache(QString t, QString id, QDate dispo, QDate ech, Projet *pere):titre(t),identificateur(id),disponibilite(dispo),echeance(ech),projetPere(pere)
{}

