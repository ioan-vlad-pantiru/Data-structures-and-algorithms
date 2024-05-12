#include "SMIterator.h"
#include "SortedMap.h"
#include <exception>

using namespace std;

void SMIterator::resize() {
	TElem* newElements = new TElem[capacity * 2];
	for (int i = 0; i < size; i++){
		newElements[i] = elements[i];
	}
	delete[] elements;
	elements = newElements;
	capacity *= 2;
}

int SMIterator::partition(int low, int high) {
	TElem pivot = elements[high];
	int i = (low - 1);

	for(int j = low; j <= high -1; j++){
		if(map.rel(pivot.first, elements[j].first)) {
			i++;
			std::swap(elements[i], elements[j]);
		}
	}
	std::swap(elements[i+1], elements[high]);
	return (i + 1);
}

void SMIterator::quickSort(int low, int high) {
	if (low < high) {
		int pi = partition(low, high);

		quickSort(low, pi - 1);
		quickSort(pi + 1, high);
	}
}

void SMIterator::collectElements()

void SMIterator::sortElemets() {
	
}

SMIterator::SMIterator(const SortedMap& m) : map(m), elements(new TElem[10]), capacity(10), size(0), current(0){
	
}

void SMIterator::first(){
	//TODO - Implementation
}

void SMIterator::next(){
	//TODO - Implementation
}

bool SMIterator::valid() const{
	//TODO - Implementation
	return false;
}

TElem SMIterator::getCurrent() const{
	//TODO - Implementation
	return NULL_TPAIR;
}


