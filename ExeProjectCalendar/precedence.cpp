#include "precedence.h"

Precedence::Precedence(const Tache *p,const Tache *s):pred(p),succ(s){}

Precedence::~Precedence(){
    delete pred;
    delete succ;
}

