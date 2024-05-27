#pragma once
#include "SortedSet.h"

//DO NOT CHANGE THIS PART
class SortedSetIterator
{
	friend class SortedSet;
private:
	const SortedSet& set;
    int currentNode;
    TComp* nodes;
	int numberOfNodes;

    SortedSetIterator(const SortedSet& s);

	void inorder(int root);

public:
	void first();
	void next();
	TElem getCurrent();
	bool valid() const;

	void jumpForward(int k);

	~SortedSetIterator();	
};

