#include "SortedBag.h"
#include "SortedBagIterator.h"
#include "exception"

using namespace std;

SortedBag::SortedBag(Relation r) {
	this->nrElements = 0;
	this->capacity = 100;
	this->elements = new TElem[capacity];
	this->relation = r;
}

SortedBag::~SortedBag() {
	delete[] this->elements;
}
//Theta(1)

void SortedBag::sort()
{
	int i, k=1;
	TComp a;
	while (k == 1)
	{
		k = 0;
		for (int i = 0; i < this->nrElements - 1; i++)
			if (this->relation(this->elements[i], this->elements[i + 1]) == false)
			{
				a = this->elements[i];
				this->elements[i] = this->elements[i + 1];
				this->elements[i + 1] = a;
				k = 1;
			}
	}
}

void SortedBag::add(TComp e) {
	if (this->nrElements == this->capacity)
	{
		int newCapacity = this->capacity * 2;
		TComp* arr = new int[newCapacity];
		for (int i = 0; i < this->nrElements; i++)
			arr[i] = this->elements[i];

		this->capacity = newCapacity;
		this->elements = arr;
		delete[] arr;
	}
	if (this->nrElements == 0)
	{
		this->elements[0] = e;
		this->nrElements++;
	}
	else {
		this->elements[this->nrElements] = e;
		this->nrElements++;
		sort();
	}
}
//Best case: theta(1), worst case: theta(n^2),overall: O(n^2)


bool SortedBag::remove(TComp e) {
	int k = 0;
	for (int i = 1; i <= this->nrElements; i++)
	{
		if (this->elements[i] == e)
		{
			for (int j = i; j < nrElements; j++)
				this->elements[j] = this->elements[j + 1];
			nrElements--;
			k = 1;
		}
		if (k == 1)
		{
			return true;
			break;
		}
	}
	return false;
}
//Best case: theta(1), worst case: theta(n),overall: O(n)


bool SortedBag::search(TComp elem) const {
	for (int i = 1; i <= this->nrElements; i++)
		if (this->elements[i] == elem)
			return true;
	return false;
}
//Best case: theta(1), worst case: theta(n),overall: O(n)

int SortedBag::nrOccurrences(TComp elem) const {
	int nr = 0;
	for (int i = 0; i < this->nrElements; i++)
		if (this->elements[i] == elem)
			nr++;
	return nr;
}
//Theta(n)


int SortedBag::size() const {
	return this->nrElements;
}
//Theta(1)

bool SortedBag::isEmpty() const {
	if (this->nrElements == 0)
		return true;
	return false;
}
//Theta(1)

SortedBagIterator SortedBag::iterator() const {
	return SortedBagIterator(*this);
}
//Theta(1)


int SortedBag::removeAll()
{
	int nrRemoved = 0;
	int i;
	for(i = 0; i < this->nrElements; i++)
		if (this->nrOccurrences(this->elements[i]) > 1)
		{
			int a = this->nrOccurrences(this->elements[i]);
			nrRemoved = nrRemoved + this->nrOccurrences(this->elements[i]);
			for (int k = 1; k <= a; k++)
			{
				for (int j = i; j < this->nrElements - 1; j++)
					this->elements[j] = this->elements[j + 1];
				this->nrElements--;
			}
		}
	return nrRemoved;
}