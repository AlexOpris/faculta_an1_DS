#include "SortedBagIterator.h"
#include "SortedBag.h"
#include <exception>

using namespace std;

SortedBagIterator::SortedBagIterator(const SortedBag& b) : bag(b), currentNode(nullptr), stack{ std::stack<BSTNode*>{} } {
	this->first();
}
//Theta(1)

TComp SortedBagIterator::getCurrent() {

	if (!this->valid())
		throw exception();
	return this->currentNode->info;
}
//Theta(1)

bool SortedBagIterator::valid() {

	if (this->currentNode != NULL)
		return true;
	else
		return false;
}
//Theta(1)

void SortedBagIterator::next() {
	if (!valid())
		throw exception();

	BSTNode* node = stack.top();
	stack.pop();
	if (node->right != nullptr) {
		node = node->right;
		while (node != NULL) {
			this->stack.push(node);
			node = node->left;
		}
	}

	if (this->stack.empty() == false) {
		this->currentNode = this->stack.top();
	}
	else {
		this->currentNode = NULL;
	}
}
//Theta(1)

void SortedBagIterator::first() {

	this->currentNode = this->bag.root;
	
	this->stack = std::stack<BSTNode*>{};
	
	while (this->currentNode != NULL)
	{
		this->stack.push(this->currentNode);
		this->currentNode = this->currentNode->left;
	}

	if (this->stack.empty() == false) {
		this->currentNode = stack.top();
	}
	else {
		this->currentNode = NULL;
	}
}
//Best case: Theta(1)
//Worst case: Theta(log2n)
//Overall complexity: O(log2n)

