#ifndef ITERATOR_H
#define ITERATOR_H


template<class X>
class iterateur{
protected:
    friend class agregateur;
    X **x;
    iterateur(X **x1):x(x1){}
public:
    virtual bool operator!=(const iterateur& it){
        return x!=it.x;
    }
    virtual void operator++(){ ++x;}
    virtual X* getCurrent(){return *x;}
    virtual bool operator==(const iterateur& it){
        return x==it.x;
    }
};

#endif // ITERATOR_H

