#include "SortedBag.h"
#include "SortedBagIterator.h"

SortedBag::SortedBag(Relation r) {
	this->rel = r;
	this->nrNodes = 0;
	this->root = nullptr;
}
//Theta(1)

void SortedBag::add(TComp e) {
	if(this->root!=nullptr)
		recursive_add(this->root, e);
	else
	{
		this->root = new BSTNode;
		this->root->info = e;
		this->root->left = nullptr;
		this->root->right = nullptr;
	}
	this->nrNodes++;
}
//Best case: Theta(1)
//Worst case: Theta(log2n)
//Overall complexity: O(log2n)

void SortedBag::recursive_add(BSTNode* n, TComp e)
{

	if (rel(n->info, e))
	{
		if (n->left != nullptr)
			recursive_add(n->left, e);
		else {
			n->left = new BSTNode;
			n->info = e;
			n->left->right = nullptr;
			n->left->left = nullptr;
		}
	}
	else
	{
		if (n->right != nullptr)
			recursive_add(n->right, e);
		else {
			n->right = new BSTNode;
			n->info = e;
			n->right->left = nullptr;
			n->right->right = nullptr;
		}
	}
}


bool SortedBag::remove(TComp e) {
	if (recursive_remove(this->root, e) == nullptr)
		return false;
	else
		return true;
}
//Best case: Theta(1)
//Worst case: Theta(log2n)
//Overall complexity: O(log2n)

BSTNode* SortedBag::recursive_remove(BSTNode* n, TComp e)
{
	{
		if (this->root == nullptr)
			return this->root;

		if (this->rel(this->root->info, e)) {
			this->root->left = recursive_remove(this->root->left, e);
			return this->root;
		}
		else{
			this->root->right = recursive_remove(this->root->right, e);
			return this->root;
		}

		if (this->root->left == nullptr) {
			BSTNode* node = this->root->right;
			delete this->root;
			return node;
		}
		else if (this->root->right == nullptr) {
			BSTNode* node = this->root->left;
			delete this->root;
			return node;
		}
		else {
			BSTNode* succParent = this->root;
			BSTNode* succ = this->root->right;
			while (succ->left != nullptr) {
				succParent = succ;
				succ = succ->left;
			}
			if (succParent != this->root)
				succParent->left = succ->right;
			else
				succParent->right = succ->right;

			this->root->info = succ->info;

			delete succ;
			return this->root;
		}
	}
}


bool SortedBag::search(TComp elem) const {
	if (this->root == nullptr)
		return false;
	else
		return recursive_search(this->root, elem);
}
//Best case: Theta(1)
//Worst case: Theta(log2n)
//Overall complexity: O(log2n)

bool SortedBag::recursive_search(BSTNode* n, TComp e) const
{
	bool res;

	if (n == nullptr)
		return false;

	if (n->info == e)
		return true;

	else if (rel(n->info, e))
		res = recursive_search(n->left, e);
	else
		res = recursive_search(n->right, e);

	return res;
}


int SortedBag::nrOccurrences(TComp elem) const {
	
	int nrOcc = 0;
	BSTNode* current = this->root;

	while (current != nullptr) { 
		if (current->info == elem) 
			nrOcc++;
		if (this->rel(elem, current->info)) 
			current = current->left;
		else
			current = current->right; 
	}
	return nrOcc;
}
//Theta(log2n)


int SortedBag::size() const {
	return this->nrNodes;
}
//Theta(1)

bool SortedBag::isEmpty() const {
	if (this->nrNodes == 0)
		return true;
	return false;
}
//Theta(1)

SortedBagIterator SortedBag::iterator() const {
	return SortedBagIterator(*this);
}
//Theta(1)

SortedBag::~SortedBag() {
}
//Theta(1)