#pragma once
#include "SortedBag.h"
#include <stack>

using namespace std;

class SortedBag;

class SortedBagIterator
{
	friend class SortedBag;

private:
	const SortedBag& bag;
	SortedBagIterator(const SortedBag& b);
	BSTNode* currentNode;
	stack <BSTNode*> stack;

public:
	TComp getCurrent();
	bool valid();
	void next();
	void first();
};

