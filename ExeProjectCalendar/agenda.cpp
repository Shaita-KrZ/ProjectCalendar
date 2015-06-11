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
    stream.writeStartElement("evenement");
    multimap<const QDate,Programmation*>::iterator it;
    for(it=s->getEvenements().begin();it!=s->getEvenements().end();++it){
            Programmation *P=it->second;
            stream.writeStartElement("programmation");
            stream.writeTextElement("date",P->getDate().toString(Qt::ISODate));
            stream.writeTextElement("horaireDebut",P->getHoraireDebut().toString());
            Evenement *E=P->getEvent();
            stream.writeTextElement("titre",E->getTitre());
            QString str;
            str.setNum(E->getDuree().getDureeEnMinutes());
            stream.writeTextElement("duree",str);
            stream.writeEndElement();
        }
    stream.writeEndElement();
    stream.writeEndElement();
    stream.writeEndDocument();
    newfile.close();
}
