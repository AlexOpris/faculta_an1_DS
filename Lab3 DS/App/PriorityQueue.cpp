#include "PriorityQueue.h"
#include <exception>
using namespace std;


PriorityQueue::PriorityQueue(Relation r) {

	this->rel = r;
	this->cap = 100;
	this->elem = new Element[this->cap];
	this->next = new int[this->cap];
	this->firstEmpty = 0;
	this->head = -1;
	this->length = 0;
}
//Theta(1)

void PriorityQueue::push(TElem e, TPriority p) {
	
	if (this->firstEmpty == -1)
	{
		Element* newElems = new Element[this->cap * 2];
		int* newNext = new int[this->cap * 2];
		for (int i = 0; i < this->cap; i++)
		{
			newElems[i] = this->elem[i];
			newNext[i] = this->next[i];
		}
		for (int i = this->cap; i < this->cap * 2; i++) {
			newNext[i] = i + 1;
			newNext[this->cap * 2  - 1] = -1;
		}
		this->elem = newElems;
		this->next = newNext;
		this->firstEmpty = this->cap;
		this->cap = this->cap * 2;
	}
	if (this->rel(p, this->elem[this->head].second) == true)
	{
		int newPos = this->firstEmpty;
		this->elem[newPos].first = e;
		this->firstEmpty = this->next[this->firstEmpty];
		this->next[newPos] = this->head;
		this->head = newPos;
		this->elem[newPos].second = p;
	}
	else
		for (int i = 0; i < this->cap; i++)
		{
			if (this->rel(p, this->elem[i].second) == true)
			{
				int pozCurrent = 1;
				int nodCurrent = this->head;
				while (nodCurrent != -1 && pozCurrent < i - 1)
				{
					pozCurrent++;
					nodCurrent = this->next[nodCurrent];
				}
				if (nodCurrent != -1)
				{
					int newElem = this->firstEmpty;
					this->firstEmpty = this->next[this->firstEmpty];
					this->elem[newElem].first = e;
					this->elem[newElem].second = p;
					this->next[newElem] = this->next[nodCurrent];
					this->next[nodCurrent] = newElem;
				}
				break;
			}
		}
	this->length++;
}
//Best case: Theta(1); Worst case: Theta(n); Average case: O(n)

Element PriorityQueue::pop() {
	if (isEmpty() == true)
		throw exception();
	else
	{
		Element removed = this->elem[this->head];
		int nodC = this->head;
		int prevNode = -1;
		int n;
		while (nodC != -1)
		{
			if (rel(removed.second, this->elem[this->next[nodC]].second))
			{
				removed = this->elem[this->next[nodC]];
				n = this->next[nodC];
				prevNode = nodC;
			}
			nodC = this->next[nodC];
		}
		if (n == this->head)
			this->head = this->next[this->head];
		else
			this->next[prevNode] = this->next[n];
		this->next[n] = this->firstEmpty;
		this->firstEmpty = n;
		return removed;
	}
	this->length--;
}
//Theta(n)

//throws exception if the queue is empty
Element PriorityQueue::top() const {
	if (isEmpty() == true)
		throw exception();
	else
	{
		Element max_pr;

		if (this->head != -1)
		{
			max_pr.first = this->elem[this->head].first;
			max_pr.second = this->elem[this->head].second;
			if (this->length > 1) {
				for (int i = 0; i <= this->cap; i++)
				{
					if (this->rel(max_pr.second, this->elem[i].second) == true)
					{
						max_pr.first = this->elem[this->head].first;
						max_pr.second = this->elem[this->head].second;
					}
				}
			}
		}
		return max_pr;
	}
}
//Theta(n)

bool PriorityQueue::isEmpty() const {
	if (this->length == 0)
		return true;
	return false;
}
//Theta(1)

PriorityQueue::~PriorityQueue() {
	delete[] this->elem;
	delete[] this->next;
};
//Theta(1)
