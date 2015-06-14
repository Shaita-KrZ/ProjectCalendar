#include "agenda.h"

using namespace std;

Agenda * Agenda::instance=0;

Agenda & Agenda::getInstance(){
    if(instance==0){
        instance=new Agenda();
    }
    return *instance;
}

void Agenda::libererInstance(){
    if(instance!=0)delete instance;
    instance=0;
}

/*
 * \brief Cree et ajoute une semaine dans l'agenda; aucun effet si la semaine existe deja
 * \param lundi
 * \throw CalendarException si la date en parametre ne correspond pas a un lundi
 */
void Agenda::creerSemaine(const QDate &lundi)
{
    if(lundi.dayOfWeek()!=1)
        throw CalendarException("Erreur : La date en parametre ne correspond pas a un lundi");
    Semaine *s = new Semaine(lundi);
    pair<map<const QDate, Semaine*>::iterator,bool> ret = semaines.insert(pair<const QDate, Semaine*>(lundi, s));
}

void Agenda::addProgrammation(Programmation *p)
{
    Semaine * sem = new Semaine(p->getLundi());
    pair<map<const QDate, Semaine*>::iterator,bool> ret = semaines.insert(pair<const QDate, Semaine*>(sem->getLundi(), sem));
    Semaine * semaineProg = this->getSemaines().find(p->getLundi())->second;
    try{
        semaineProg->addProgrammation(p);
    }
    catch(CalendarException &e){
        throw e;
    }

}

Agenda::~Agenda(){
    for (map<const QDate, Semaine*>::iterator it=semaines.begin(); it!=semaines.end(); ++it){
        delete it->second;
    }
}

void Agenda::save(const QString& f,const QDate lundi){
    file=f;
    Semaine *s=semaines[lundi];
    QFile newfile( file);
    qDebug()<<"debut save";
    if (!newfile.open(QIODevice::WriteOnly | QIODevice::Text)){
        throw CalendarException(QString("erreur sauvegarde tâches : ouverture fichier xml"));
    }

    QXmlStreamWriter stream(&newfile);
    stream.setAutoFormatting(true);
    stream.writeStartDocument();
    stream.writeStartElement("semaine");
    stream.writeTextElement("dateLundi",s->getLundi().toString(Qt::ISODate));
    stream.writeStartElement("evenements");
    multimap<const QDate,Programmation*>::iterator it;
    for(it=s->getEvenements().begin();it!=s->getEvenements().end();++it){
            Programmation *P=it->second;
            stream.writeStartElement("programmation");
            stream.writeTextElement("date",P->getDate().toString(Qt::ISODate));
            stream.writeTextElement("horaireDebut",P->getHoraireDebut().toString("hh:mm"));
            Evenement *E=P->getEvent();
            stream.writeTextElement("titre",E->getTitre());
            QString str;
            str.setNum(E->getDuree().getDureeEnMinutes());
            stream.writeTextElement("duree",str);
            stream.writeEndElement();
        }
  qDebug()<<"fin sav4e";
    stream.writeEndElement();
    stream.writeEndElement();
    stream.writeEndDocument();
    newfile.close();
    qDebug()<<"fin save";
}


void Agenda::load(const QString& f){
    qDebug()<<"debut load\n";
    file=f;
    QFile fin(file);
    //On test si on peut ouvrir le fichier
    if (!fin.open(QIODevice::ReadOnly | QIODevice::Text)) {
        throw CalendarException("Erreur ouverture fichier tâches");
    }
    QXmlStreamReader xml(&fin);
    QDate dateLundi;
    QDate date;
    QTime horaire;
    QString titre;
    Duree duree;
    //On commence a lire le fichier xml
    while(!xml.atEnd() && !xml.hasError()) {
        // Read next element.
        QXmlStreamReader::TokenType token = xml.readNext();
        //Le premier token vaudra 2 = StartDocument.
        // If token is just StartDocument, we'll go to next.
        if(token == QXmlStreamReader::StartDocument) continue;
        // If token is StartElement, we'll see if we can read it.
        if(token == QXmlStreamReader::StartElement){
            if(xml.name()=="projet")throw CalendarException("Veuillez importer une semaine !");
            if(xml.name() == "semaine"){
                while(!(xml.tokenType()==QXmlStreamReader::StartElement && xml.name()=="evenements")){
                    if(xml.tokenType() == QXmlStreamReader::StartElement){
                        if(xml.name() == "dateLundi"){
                        xml.readNext(); dateLundi=QDate::fromString(xml.text().toString(),Qt::ISODate);
                        }
                    }
                    xml.readNext();
                }
                creerSemaine(dateLundi);
            }
            if(xml.name()=="evenements") continue;
            //We're going to loop over the things because the order might change.
            //We'll continue the loop until we hit an EndElement named tache.
            if(xml.name()=="programmation"){
                while(!(xml.tokenType()==QXmlStreamReader::EndElement && xml.name()=="programmation")){
                     if(xml.tokenType() == QXmlStreamReader::StartElement){
                          if(xml.name() == "date") {
                               xml.readNext(); date=QDate::fromString(xml.text().toString(),Qt::ISODate);
                               }
                            // We've found horaireDebut.
                            if(xml.name() == "horaireDebut") {
                                xml.readNext(); horaire=QTime::fromString(xml.text().toString(),"hh:mm");
                               }

                            // We've found titre.
                            if(xml.name() == "titre") {
                                xml.readNext(); titre=xml.text().toString();
                            }
                            // We've found duree
                            if(xml.name() == "duree") {
                                xml.readNext();
                                duree.setDuree(xml.text().toString().toUInt());
                            }
                        }
                        // ...and next...
                        xml.readNext();
                    }
                    ActiviteTraditionnelle *event=new ActiviteTraditionnelle(titre,duree);
                    Programmation *p=new Programmation(date,horaire,event);
                    addProgrammation(p);
                }
        }
    }
 // Error handling.
    if(xml.hasError()){
        throw CalendarException("Erreur lecteur fichier semaines, parser xml");
    }
    // Removes any device() or data from the reader * and resets its internal state to the initial state.
    xml.clear();
    qDebug()<<"fin load\n";
    return;
}
