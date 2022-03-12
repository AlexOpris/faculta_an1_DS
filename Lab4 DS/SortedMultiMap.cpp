#include "SMMIterator.h"
#include "SortedMultiMap.h"
#include <iostream>
#include <vector>
#include <exception>
using namespace std;

//using a hashtable with open addressing and double hashing in which unique keys are stored 
//with a dynamic array of the associated values.In the constructor of the  iterator  create  
//a  sorted  array  of  (key,  dynamic  array  of  values)  pairs  and  use  it  for iterating.

int SortedMultiMap::hash_function1(TKey k) const
{
	return k % this->cap;
}
//Theta(1)

int SortedMultiMap::hash_function2(TKey k) const
{
	return 1 + (k % (this->cap - 1));
}
//Theta(1)

SortedMultiMap::SortedMultiMap(Relation r) {
	this->rel = r;
	this->len = 0;
	this->cap = 20;
	this->elems = new TElem*[this->cap];
	for (int i = 0; i < this->cap; i++)
		this->elems[i] = NULL;
	
}
//Theta(1)

void SortedMultiMap::add(TKey c, TValue v) {
	int index = this->hash_function1(c);
	
	if (this->elems[index] != NULL)
	{
		int index2 = this->hash_function2(c);
		int i = 1;
		while (1)
		{
			int newIndex = (index + i * index2) % this->cap;

			if (this->elems[newIndex] == NULL)
			{
				this->elems[newIndex]->first = c;
				this->elems[newIndex]->second = v;
				break;
			}
			i++;
		}
	}
	else
	{
		this->elems[index]->first = c;
		this->elems[index]->second = v;
	}

	this->len++;
}
//Best case: Theta(1)
//Worst case: Theta(n)
//Overall complexity: O(n)

vector<TValue> SortedMultiMap::search(TKey c) const {
	vector<TValue> v;
	
	int index1 = this->hash_function1(c);
	int index2 = this->hash_function2(c);
	int i = 0;
	while (this->elems[(index1 + i * index2) % this->cap]->first != c && i < this->cap) {
		i++;
	}
	for (int j = 0; j < this->cap; j++)
	{
		if (this->elems[j]->first == i)
			v.push_back(this->elems[i]->second);
	}
	return v;
}
//Best case: Theta(1)
//Worst case: Theta(n)
//Overall complexity: O(n)

bool SortedMultiMap::remove(TKey c, TValue v) {
	
	int hashIndex = this->hash_function1(c);

	while (this->elems[hashIndex] != NULL)
	{
		if (this->elems[hashIndex]->first == c)
		{
			TElem* del = this->elems[hashIndex];
			TElem* deleted = new TElem;
			deleted->first = -1;
			deleted->second = -1;
			
			this->elems[hashIndex] = deleted;

			this->len--;
			return true;
		}
		hashIndex++;
		hashIndex %= this->cap;
	}
	return false;
}
//Best case: Theta(1)
//Worst case: Theta(n)
//Overall complexity: O(n)

int SortedMultiMap::size() const {
	return this->len;
}
//Theta(1)

bool SortedMultiMap::isEmpty() const {
	if (this->len == 0)
		return true;
	return false;
}
//Theta(1)

SMMIterator SortedMultiMap::iterator() const {
	return SMMIterator(*this);
}
//Theta(1)

SortedMultiMap::~SortedMultiMap() {
	delete[] this->elems;
}
//Theta(1)

void SortedMultiMap::resize()
{
	int newSize = 2 * this->cap;
	TElem* newTable = new TElem[newSize];
	for (int i = 0; i < newSize; i++) {
		newTable[i] = NULL_TELEM;
	}
	for (int i = 0; i < newSize; i++) {
		if (this->elems[i] != NULL) {
			int index = this->hash_function1(this->elems[i]->first);
			int i = 1;
			while (newTable[index].first != 0) {
				index = (index + (i * i)) % newSize;
			}
			newTable[index].first = this->elems[i]->first;
			newTable[index].second = this->elems[i]->second;
		}
	}
	delete[] newTable;
}

