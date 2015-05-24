#include "precedencemanager.h"

PrecedenceManager::PrecedenceManager(unsigned int n=0):nb(n),nbMax(n+10),tabPrec(new Precedence*[nb])
{
    for(unsigned int i=0;i<nb;i++){
        tabPrec[i]=0;
    }
}

PrecedenceManager::~PrecedenceManager()
{
    delete[] tabPrec;
}

bool PrecedenceManager::isPrecedence(Tache *prec, Tache *succ) const{
    pmIterator it=begin();
    Precedence p=*it;
    while(it!=end() && (prec!=p.getPredecesseur() || succ!=p.getSuccesseur())){
        ++it;
        p=*it;
    }
    if(it==end()){
        return false;
    }
    else return true;
}

PrecedenceManager & PrecedenceManager::getTachesPred (const Tache *succ) const{
    PrecedenceManager *PM=new PrecedenceManager;
    pmIterator it=begin();
    Precedence p=*it;
    while(it!=end()){
        while(it!=end() && succ!=p.getSuccesseur()){
            ++it;
            p=*it;
        }
        if(it!=end()){
            PM->ajouterPrecedence(p.getPredecesseur(),succ);
        }
    }
    return *PM;
}

void PrecedenceManager::ajouterPrecedence(const Tache * p,const Tache * s){
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
