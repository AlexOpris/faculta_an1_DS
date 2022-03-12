#include "ListIterator.h"
#include "SortedIteratedList.h"
#include <exception>

using namespace std;

ListIterator::ListIterator(const SortedIteratedList& list) : list(list){
	this->current = this->list.head;
}
//Theta(1)

void ListIterator::first(){
	this->current = this->list.head;
}
//Theta(1)

void ListIterator::next(){
	if (!valid())
		throw exception();
	else
		this->current = this->current->next;
}
//Theta(1)

bool ListIterator::valid() const{
	if (this->current != nullptr)
		return true;
	return false;
}
//Theta(1)

TComp ListIterator::getCurrent() const{
	
	if (!valid())
		throw exception();

	return this->current->elem;
}
//Theta(1)


