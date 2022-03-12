#pragma once
#include "SortedIteratedList.h"

//DO NOT CHANGE THIS PART
class ListIterator{
	friend class SortedIteratedList;
private:
	const SortedIteratedList& list;
	ListIterator(const SortedIteratedList& list);

	SortedIteratedList::Node* current;

public:
	void first();
	void next();
	bool valid() const;
    TComp getCurrent() const;
};


