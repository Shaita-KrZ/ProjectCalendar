#include "projetmanager.h"

ProjetManager::ProjetManager(){}

ProjetManager::~ProjetManager(){}

ProjetManager * ProjetManager::instance=0;

ProjetManager & ProjetManager::getInstance(){
    if(instance==0){
        instance=new ProjetManager;
    }
    return *instance;
}

void ProjetManager::libererInstance(){
    if(instance!=0)delete instance;
    instance=0;
}

void ProjetManager::creerProjet(const QString & t,unsigned int nbPrec){
    Projet *P=new Projet(t,nbPrec);
    projets[t]=P;
}

void ProjetManager::modifierNomProjet(QString & projet, const QString & nouveauT){
    //Le projet existe deja
    if(projets.find(nouveauT)!=projets.end()){
        throw CalendarException("Le titre est deja pris par un autre projet");
    }
    projets[projet]->setTitre(nouveauT);
}

void ProjetManager::supprimerProjet(const QString & t){
    if(projets.find(t)!=projets.end()){
        projets.erase(t);
    }
    else throw CalendarException("Le projet n\'existe pas");
}

Projet & ProjetManager::getProjet(const QString& t){
    if(projets.find(t)!=projets.end()){
        map<QString, Projet*>::const_iterator it;
        it=projets.find(t);
        Projet *P=it->second;
        return *P;
    }
    else throw CalendarException("Le projet n\'existe pas");
}


void ProjetManager::load(const QString& f){
    qDebug()<<"debut load\n";
    file=f;
    QFile fin(file);
    //On test si on peut ouvrir le fichier
    if (!fin.open(QIODevice::ReadOnly | QIODevice::Text)) {
        throw CalendarException("Erreur ouverture fichier tâches");
    }
    QXmlStreamReader xml(&fin);
    unsigned int nbPrec=10;
    QString identificateurCompo;
    QString titreProjet;
    Projet *pere;
    QString identificateur;
    QString titre;
    QDate disponibilite;
    QDate echeance;
    Duree duree;
    bool preemptive;
    bool typeTache=true;
    QDate echeanceProjet;
    //On commence a lire le fichier xml
    while(!xml.atEnd() && !xml.hasError()) {
        // Read next element.
        QXmlStreamReader::TokenType token = xml.readNext();
        //Le premier token vaudra 2 = StartDocument.
        // If token is just StartDocument, we'll go to next.
        if(token == QXmlStreamReader::StartDocument) continue;
        // If token is StartElement, we'll see if we can read it.
        if(token == QXmlStreamReader::StartElement){
            //Le premier token=projet
            // Si le token type est projet alors
            if(xml.name() == "projet"){
                while(!(xml.tokenType()==QXmlStreamReader::StartElement && xml.name()=="tacheManager")){
                    if(xml.tokenType() == QXmlStreamReader::StartElement){
                        if(xml.name() == "titre"){
                        xml.readNext(); titreProjet=xml.text().toString();
                        }
                        if(xml.name() == "echeance") {
                            xml.readNext(); echeanceProjet=QDate::fromString(xml.text().toString(),Qt::ISODate);
                            //qDebug()<<"echeanceProjet="<<echeanceProjet.toString()<<"\n";
                        }
                    }
                    xml.readNext();
                }
                pere=new Projet(titreProjet,nbPrec);
                pere->setEcheance(echeanceProjet);
                projets[titreProjet]=pere;
            }

            //Sortie de la bouche xml.name() == tacheManager
            if(xml.name()=="tacheManager") continue;
            if(xml.name()=="tache" && typeTache==true){
                QXmlStreamAttributes attributes = xml.attributes();
                // Let's check that Task has attribute.
                if(attributes.hasAttribute("type")){
                    QString val =attributes.value("type").toString();
                    typeTache=(val == "unit" ? true : false);
                    //qDebug()<<"type Tache="<<val<<"\n";
                }
            }
            //We're going to loop over the things because the order might change.
            //We'll continue the loop until we hit an EndElement named tache.
            if(typeTache){
            while(!(xml.tokenType()==QXmlStreamReader::EndElement && xml.name()=="tache")){
                 if(xml.tokenType() == QXmlStreamReader::StartElement){
                      if(xml.name() == "preemptive") {
                            QString val;
                            xml.readNext(); val=xml.text().toString();
                            preemptive=(val == "true" ? true : false);
                           }
                        // We've found identificteur.
                        if(xml.name() == "identificateur") {
                            xml.readNext(); identificateur=xml.text().toString();
                           }

                        // We've found titre.
                        if(xml.name() == "titre") {
                            xml.readNext(); titre=xml.text().toString();
                        }
                        // We've found disponibilite
                        if(xml.name() == "disponibilite") {
                            xml.readNext();
                            disponibilite=QDate::fromString(xml.text().toString(),Qt::ISODate);
                        }
                        // We've found echeance
                        if(xml.name() == "echeance") {
                            xml.readNext();
                            echeance=QDate::fromString(xml.text().toString(),Qt::ISODate);
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
                projets[titreProjet]->taches.addTache(identificateur,titre,disponibilite,echeance,pere,duree,preemptive);
            }
            if(!typeTache){
                while(!(xml.tokenType()==QXmlStreamReader::EndElement && xml.name()=="tachescompo")){
                    while(!((xml.tokenType()==QXmlStreamReader::EndElement && xml.name()=="tache") ||
                          (xml.tokenType()==QXmlStreamReader::StartElement && xml.name()=="tachescompo") ||
                            (xml.tokenType()==QXmlStreamReader::EndElement && xml.name()=="tachescompo"))){
                        if(xml.tokenType() == QXmlStreamReader::StartElement){
                            if(xml.name() == "preemptive") {
                                QString val;
                                xml.readNext(); val=xml.text().toString();
                                preemptive=(val == "true" ? true : false);
                                //qDebug()<<"preemptive="<<val<<"\n";
                            }
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
                    if(xml.name()=="tachescompo" && xml.tokenType()==QXmlStreamReader::StartElement){
                        identificateurCompo=identificateur;
                        typeTache=true;
                        pere->taches.addTache(identificateurCompo,titre,disponibilite,echeance,pere);
                        xml.readNext();
                    }
                    else if(xml.name()=="tache"){
                        //Ajout d'une tache UNITAIRE sur une tacheComposite
                        TacheUnitaire *tUnitaire=new TacheUnitaire(titre,identificateur,disponibilite,echeance,pere,preemptive,duree);
                        Tache* T=pere->taches.getTache(identificateurCompo);
                        TacheComposite *tComposite=dynamic_cast<TacheComposite*>(T);
                        tComposite->addTache(tUnitaire);
                        xml.readNext();
                    }
                }
            }
        }
    }
 // Error handling.
    if(xml.hasError()){
        throw CalendarException("Erreur lecteur fichier taches, parser xml");
    }
    // Removes any device() or data from the reader * and resets its internal state to the initial state.
    xml.clear();
    //qDebug()<<"fin load\n";
}


void  ProjetManager::save(const QString& f,const QString &titreProjet){
    file=f;
    QFile newfile( file);
    qDebug()<<"debut save";
    if (!newfile.open(QIODevice::WriteOnly | QIODevice::Text)){
        qDebug()<<"test";
        throw CalendarException(QString("erreur sauvegarde tâches : ouverture fichier xml"));
    }
    QXmlStreamWriter stream(&newfile);
    stream.setAutoFormatting(true);
    stream.writeStartDocument();
    stream.writeStartElement("projet");
    Projet P=getProjet(titreProjet);
    stream.writeTextElement("titre",P.getTitre());
    stream.writeTextElement("echeance",P.getEcheance().toString(Qt::ISODate));
    stream.writeStartElement("tacheManager");
    TacheManager tManager=P.getTaches();
    map<const QString, Tache*>lTaches=tManager.getTaches();
    map<const QString, Tache*>::const_iterator it;
    for(it=lTaches.begin();it!=lTaches.end();++it){
        if(it->second->estComposite()){
            TacheComposite *tComposite=dynamic_cast<TacheComposite*>(it->second);
            stream.writeStartElement("tache");
            stream.writeAttribute("type","compo");
            stream.writeTextElement("identificateur",tComposite->getID());
            stream.writeTextElement("titre",tComposite->getTitre());
            stream.writeTextElement("disponibilite",tComposite->getDisponibilite().toString(Qt::ISODate));
            stream.writeTextElement("echeance",tComposite->getEcheance().toString(Qt::ISODate));
            stream.writeStartElement("tachescompo");
            map<const QString, Tache*>::const_iterator itCompo;
            map<const QString, Tache*>lTachesCompo=tComposite->getTaches();
            for(itCompo=lTachesCompo.begin();itCompo!=lTachesCompo.end();++itCompo){
                TacheUnitaire *tUnitaire=dynamic_cast<TacheUnitaire*>(itCompo->second);
                stream.writeStartElement("tache");
                stream.writeAttribute("type","unit");
                stream.writeTextElement("preemptive",(tUnitaire->isPreemptive()?"true":"false"));
                stream.writeTextElement("identificateur",tUnitaire->getID());
                stream.writeTextElement("titre",tUnitaire->getTitre());
                stream.writeTextElement("disponibilite",tUnitaire->getDisponibilite().toString(Qt::ISODate));
                stream.writeTextElement("echeance",tUnitaire->getEcheance().toString(Qt::ISODate));
                QString str;
                str.setNum(tUnitaire->getDuree().getDureeEnMinutes());
                stream.writeTextElement("duree",str);
                stream.writeEndElement();
            }
            stream.writeEndElement();
            stream.writeEndElement();
        }
        else{
            TacheUnitaire *tUnitaire=dynamic_cast<TacheUnitaire*>(it->second);
            stream.writeStartElement("tache");
            stream.writeAttribute("type","unit");
            stream.writeTextElement("preemptive",(tUnitaire->isPreemptive()?"true":"false"));
            stream.writeTextElement("identificateur",tUnitaire->getID());
            stream.writeTextElement("titre",tUnitaire->getTitre());
            stream.writeTextElement("disponibilite",tUnitaire->getDisponibilite().toString(Qt::ISODate));
            stream.writeTextElement("echeance",tUnitaire->getEcheance().toString(Qt::ISODate));
            QString str;
            str.setNum(tUnitaire->getDuree().getDureeEnMinutes());
            stream.writeTextElement("duree",str);
            stream.writeEndElement();
        }
    }
    stream.writeEndElement();
    stream.writeEndElement();
    stream.writeEndDocument();
    newfile.close();
}

