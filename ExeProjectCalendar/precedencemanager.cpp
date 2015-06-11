#include "precedencemanager.h"

PrecedenceManager::PrecedenceManager():nb(0),nbMax(10),tabPrec(new Precedence*[nbMax])
{
    for(unsigned int i=0;i<nbMax;i++){
        tabPrec[i]=0;
    }
}

PrecedenceManager::~PrecedenceManager()
{
    delete[] tabPrec;
}

bool PrecedenceManager::isPrecedence(Tache *prec, Tache *succ) const{
    pmIterator it=begin();
    Precedence* p=it.getCurrent();
    while(it!=end() && (prec!=p->getPredecesseur() || succ!=p->getSuccesseur())){
        ++it;
        p=it.getCurrent();
    }
    if(it==end()){
        return false;
    }
    else return true;
}



void PrecedenceManager::ajouterPrecedence(Tache * p,Tache * s){

    if(p->getEcheance()>s->getEcheance()){
        throw CalendarException("La tache qui précède se termine après la tache qui succède");
    }
    Precedence *P=new Precedence(p,s);
    if(nb==nbMax){
        Precedence **newtab=new Precedence*[nb+10];
        for(unsigned int i=0;i<nb;i++)newtab[i]=tabPrec[i];
        nbMax+=10;
        Precedence **oldtab=tabPrec;
        tabPrec=newtab;
        delete[] oldtab;
    }
    tabPrec[nb++]=P;
}
