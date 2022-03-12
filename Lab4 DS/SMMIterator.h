#pragma once

#include "SortedMultiMap.h"

struct Elems {
	TKey k;
	TValue* v;
};

class SMMIterator{
	friend class SortedMultiMap;
private:
	//DO NOT CHANGE THIS PART
	const SortedMultiMap& map;
	SMMIterator(const SortedMultiMap& map);

	Elems* it;
	int pos;
	int cap;

	
public:
	void first();
	void next();
	bool valid() const;
   	TElem getCurrent() const;
};