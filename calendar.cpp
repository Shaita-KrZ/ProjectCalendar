#include "calendar.h"

//methode Duree
void Duree::afficher(QTextStream& f) const {
    f.setPadChar('0');
    f.setFieldWidth(2);
    f<<nb_minutes/60;
    f.setFieldWidth(0);
    f<<"H";
    f.setFieldWidth(2);
    f<<nb_minutes%60;
    f.setFieldWidth(0);
    f.setPadChar(' ');
}
QTextStream& operator<<(QTextStream& f, const Duree & d){ d.afficher(f); return f; }
QTextStream& operator>>(QTextStream& flot, Duree& duree){
    unsigned int h,m;
    bool ok=true;
    flot>>h;
    if (flot.status()!=QTextStream::Ok) ok=false;
    if(flot.read(1)=="H") {
        flot>>m;
        if (flot.status()!=QTextStream::Ok) ok=false;
    }
    else {
        ok=false;
    }
    if (ok) duree=Duree(h,m);
    return flot;
}

//Methode tache
void Tache::setId(const QString& str){
  identificateur=str;
}

 QTextStream& operator<<(QTextStream& fout, const Tache& t){
     fout<<t.getId()<<"\n";
     fout<<t.getTitre()<<"\n";
     fout<<t.getDuree()<<"\n";
     fout<<t.getDateDisponibilite().toString()<<"\n";
     fout<<t.getDateEcheance().toString()<<"\n";
     return fout;
 }

 //methode projet

 Projet::~Projet(){
     delete[]taches;
 }
 void Projet::addItem(Tache* t){
     if (nbT==nbTMax){
         Tache** newtab=new Tache*[nbTMax+10];
         for(unsigned int i=0; i<nbT; i++) newtab[i]=taches[i];
         // ou memcpy(newtab,taches,nb*sizeof(Tache*));
         nbTMax+=10;
         Tache** old=taches;
         taches=newtab;
         delete[] old;
     }
     taches[nbT]=t;
     nbT++;
 }

 Tache* Projet::trouverTache(const QString& id)const{
     for(unsigned int i=0; i<nbT; i++)
         if (id==taches[i]->getId()) return taches[i];
     return 0;
 }
 Tache& Projet::ajouterTache(const QString& id, const QString& t, const Duree& dur, const QDate& dispo, const QDate& deadline, bool preempt){
     if (trouverTache(id)) throw CalendarException("erreur, TacheManager, tache deja existante");
     Tache* newt=new Tache(id,t,dur,dispo,deadline,preempt);
     addItem(newt);
     return *newt;
 }

 void Projet::load(const QString& f){
     //qDebug()<<"debut load\n";
     file=f;
     QFile fin(file);
     // If we can't open it, let's show an error message.
     if (!fin.open(QIODevice::ReadOnly | QIODevice::Text)) {
         throw CalendarException("Erreur ouverture fichier tâches");
     }
     // QXmlStreamReader takes any QIODevice.
     QXmlStreamReader xml(&fin);
     //qDebug()<<"debut fichier\n";
     // We'll parse the XML until we reach end of it.
     while(!xml.atEnd() && !xml.hasError()) {
         // Read next element.
         QXmlStreamReader::TokenType token = xml.readNext();
         // If token is just StartDocument, we'll go to next.
         if(token == QXmlStreamReader::StartDocument) continue;
         // If token is StartElement, we'll see if we can read it.
         if(token == QXmlStreamReader::StartElement) {
             // If it's named taches, we'll go to the next.
             if(xml.name() == "taches") continue;
             // If it's named tache, we'll dig the information from there.
             if(xml.name() == "tache") {
                 qDebug()<<"new tache\n";
                 QString identificateur;
                 QString titre;
                 QDate disponibilite;
                 QDate echeance;
                 Duree duree;
                 bool preemptive;

                 QXmlStreamAttributes attributes = xml.attributes();
                 /* Let's check that Task has attribute. */
                 if(attributes.hasAttribute("preemptive")) {
                     QString val =attributes.value("preemptive").toString();
                     preemptive=(val == "true" ? true : false);
                 }
                 //qDebug()<<"preemptive="<<preemptive<<"\n";

                 xml.readNext();
                 //We're going to loop over the things because the order might change.
                 //We'll continue the loop until we hit an EndElement named tache.


                 while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "tache")) {
                     if(xml.tokenType() == QXmlStreamReader::StartElement) {
                         // We've found identificteur.
                         if(xml.name() == "identificateur") {
                             xml.readNext(); identificateur=xml.text().toString();
                             //qDebug()<<"id="<<identificateur<<"\n";
                         }

                         // We've found titre.
                         if(xml.name() == "titre") {
                             xml.readNext(); titre=xml.text().toString();
                             //qDebug()<<"titre="<<titre<<"\n";
                         }
                         // We've found disponibilite
                         if(xml.name() == "disponibilite") {
                             xml.readNext();
                             disponibilite=QDate::fromString(xml.text().toString(),Qt::ISODate);
                             //qDebug()<<"disp="<<disponibilite.toString()<<"\n";
                         }
                         // We've found echeance
                         if(xml.name() == "echeance") {
                             xml.readNext();
                             echeance=QDate::fromString(xml.text().toString(),Qt::ISODate);
                             //qDebug()<<"echeance="<<echeance.toString()<<"\n";
                         }
                         // We've found duree
                         if(xml.name() == "duree") {
                             xml.readNext();
                             duree.setDuree(xml.text().toString().toUInt());
                             //qDebug()<<"duree="<<duree.getDureeEnMinutes()<<"\n";
                         }
                     }
                     // ...and next...
                     xml.readNext();
                 }
                 //qDebug()<<"ajout tache "<<identificateur<<"\n";
                 ajouterTache(identificateur,titre,duree,disponibilite,echeance,preemptive);

             }
         }
     }
     // Error handling.
     if(xml.hasError()) {
         throw CalendarException("Erreur lecteur fichier taches, parser xml");
     }
     // Removes any device() or data from the reader * and resets its internal state to the initial state.
     xml.clear();
     //qDebug()<<"fin load\n";
 }

 //Methode projetManager


ProjetManager *ProjetManager::Instance=0;
ProjetManager& ProjetManager::getInstance(){
     if(Instance==0){
            Instance=new ProjetManager(10);
     }
     return *Instance;
}

void ProjetManager::libererInstance(){
        if(Instance!=0)
            delete Instance;
        Instance=0;
 }
void ProjetManager::ajouterProjet(Projet *P){
    if (nb==nbMax){
        Projet** newtab=new Projet*[nbMax+10];
        for(unsigned int i=0; i<nb; i++) newtab[i]=projets[i];
        nbMax+=10;
        Projet** old=projets;
        projets=newtab;
        delete[] old;
    }
    projets[nb]=P;
    nb++;
}
