#include "SMIterator.h"
#include "SortedMap.h"
#include <exception>
#include <stdexcept>
#include <iostream>
#include <utility>

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

void SMIterator::collectElements() {
	size = 0;
	for (int i = 0; i < map.capacity; i++){
		SortedMap::Node* node = map.hashTable[i];
		while(node != nullptr) {
			if(size == capacity) {
				resize();
			}

			elements[size++] = node->elem;
			node = node->next;
		}
	}
	quickSort(0, size - 1);
}

SMIterator::SMIterator(const SortedMap& m) : map(m), elements(new TElem[10]), capacity(10), size(0), current(0){
	collectElements();
}

void SMIterator::first(){
	current = 0;
}

void SMIterator::next(){
	if (current >= size) {
		throw std::out_of_range("Iterator out of range");
	}
	current++;
}

bool SMIterator::valid() const{
	return current < size && current >= 0;
}

TElem SMIterator::getCurrent() const{
	if (!valid()) {
		throw std::out_of_range("Iterator out of range");
	}
	return elements[current];
}


