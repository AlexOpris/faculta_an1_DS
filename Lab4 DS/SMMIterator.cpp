#include "SMMIterator.h"
#include "SortedMultiMap.h"

SMMIterator::SMMIterator(const SortedMultiMap& d) : map(d){
    this->cap = 10;
    this->it = new Elems[this->cap];
    this->pos = 0;
}
//Theta(1)

void SMMIterator::first(){
    this->pos = 0;
}
//Theta(1)

void SMMIterator::next(){
    if (this->pos < this->cap - 1)
        this->pos++;
    else
        throw exception();
}
//Theta(1)

bool SMMIterator::valid() const{
    if (this->pos < this->cap)
        return true;
    else
        return false;
}
//Theta(1)

TElem SMMIterator::getCurrent() const{
    TElem elem;
    elem.first = this->it[this->pos].k;
    elem.second = this->it[this->pos].v[0];
    return elem;
}
//Theta(1)
