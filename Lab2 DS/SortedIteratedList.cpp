#include "ListIterator.h"
#include "SortedIteratedList.h"
#include <iostream>
using namespace std;
#include <exception>



SortedIteratedList::SortedIteratedList(Relation r) {
	
	this->rel = r;
	this->length = 0;
	this->head = nullptr;
	this->tail = nullptr;

}
//Theta(1)

int SortedIteratedList::size() const {
	return this->length;
}
//Theta(1)

bool SortedIteratedList::isEmpty() const {
	if (this->length == 0)
		return true;
	return false;
}
//Theta(1)

ListIterator SortedIteratedList::first() const {
	ListIterator it(*this);
	it.first();
	return it;
}
//Theta(1)

TComp SortedIteratedList::getElement(ListIterator poz) const {
	if (poz.valid() == true)
		return poz.getCurrent();
	else
		throw exception();
}
//Theta(1)

TComp SortedIteratedList::remove(ListIterator& poz) {
	if (isEmpty() == true)
		throw exception();


	TComp deletedElem;
	Node* currentNode;
	currentNode = poz.current;
	Node* deletedNode = currentNode;
	
	poz.next();

	if (deletedNode == nullptr)
		return NULL_TCOMP;

	if (currentNode == this->head) 
	{ 
		if (currentNode == this->tail)
		{ 
			this->head = nullptr;
			this->tail = nullptr;
		}
		else 
		{
			this->head = this->head->next;
			this->head->prev = nullptr;
		}
	}
	else
		if (currentNode == this->tail) 
		{
			this->tail = this->tail->prev;
			this->tail->next = nullptr;
		}
		else 
		{
			currentNode->next->prev = currentNode->prev;
			currentNode->prev->next = currentNode->next;
			deletedNode->next = nullptr;
			deletedNode->prev = nullptr;
		}
	
	deletedElem = deletedNode->elem;
	delete deletedNode;
	this->length--;
	return deletedElem;
}
//Theta(1)

ListIterator SortedIteratedList::search(TComp e) const{
	
	ListIterator it(*this);
	
	while (it.valid()) {
		if (it.getCurrent() == e) 
			break;
		it.next();
	}
	return it;
}
//O(n)

void SortedIteratedList::add(TComp e) {
	Node* newNode = new Node;
	newNode->elem = e;

	if (this->length == 0) {
		this->head = newNode;
		this->tail = newNode;
		this->head->next = nullptr;
		this->head->prev = nullptr;
		this->length++;
		return;
	}
	else
	{
		if (rel(e, this->head->elem)) {
			newNode->prev = nullptr;
			newNode->next = this->head;
			this->head->prev = newNode;
			this->head = newNode;
		}
		else if (!rel(e, this->tail->elem)) {

			newNode->next = nullptr;
			newNode->prev = this->tail;
			this->tail->next = newNode;
			this->tail = newNode;
		}
		else {
			Node* currentNode = this->head;
			while (!rel(e, currentNode->elem)) {
				currentNode = currentNode->next;
			}
			currentNode->prev->next = newNode;
			newNode->prev = currentNode->prev;
			currentNode->prev = newNode;
			newNode->next = currentNode;
		}
	}
	this->length++;
}
//O(n)

SortedIteratedList::~SortedIteratedList() {
	while (this->head != nullptr) {
		Node* node = head->next;
		delete this->head;
		this->head = node;
	}
	this->tail = nullptr;
}
//Theta(1)