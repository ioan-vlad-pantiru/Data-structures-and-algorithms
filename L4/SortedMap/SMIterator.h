#pragma once
#include "SortedMap.h"

//DO NOT CHANGE THIS PART
class SMIterator{
	friend class SortedMap;
private:
	const SortedMap& map;
	TElem* elements;
	int capacity;
	int size;
	int current;
	SMIterator(const SortedMap& mapionar);

	void resize();
	int partition(int, int);
	void quickSort(int, int);
	void sortElemets();
	void collectElements();

public:
	void first();
	void next();
	bool valid() const;
    TElem getCurrent() const;
};

