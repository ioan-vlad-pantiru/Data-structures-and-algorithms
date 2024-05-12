#include "SortedBag.h"
#include "SortedBagIterator.h"
#include <iostream>


SortedBag::SortedBag(Relation r): relation(r), capacity(2), sizeOfBag(0), firstEmpty(0), head(-1){
	next = new int[capacity];
	elements = new std::pair<TComp, int>[capacity];
	
	for(int i = 0; i < capacity-1 ; i++){
		next[i] = i + 1;
	}

	next[capacity-1] = -1;
	
}

void SortedBag::resize(){
	int newCapacity = capacity * 2;
	std::pair<TComp, int>* newElemnts = new std::pair<TComp, int>[newCapacity];
	int* newNext = new int[newCapacity];
	
	for(int i = 0; i < capacity; i++){
		newElemnts[i] = elements[i];
		newNext[i] = next[i];
	}

	for (int i = capacity; i < newCapacity -1; i++){
		newNext[i] = i + 1;
	}

	newNext[newCapacity - 1] = -1;

	firstEmpty = capacity;
	capacity = newCapacity;

	delete[] elements;
	delete[] next;

	elements = newElemnts;
	next = newNext;

}



void SortedBag::add(TComp e) {
    if (firstEmpty == -1) {
        resize();  // Ensure there's space for the new element
    }

    int currentNode = head;
    int prevNode = -1;

    while (currentNode != -1 && relation(elements[currentNode].first, e)) {
        if (elements[currentNode].first == e) {
            elements[currentNode].second++;
            sizeOfBag++;  // Increment total number of elements, not distinct
            return;  // Exit after incrementing the frequency
        }
        prevNode = currentNode;
        currentNode = next[currentNode];
    }

    // Insert new element
    int newNode = firstEmpty;
    firstEmpty = next[firstEmpty];
    elements[newNode] = {e, 1};  // Initialize the new node with the element and frequency of 1

    if (prevNode == -1) {
        head = newNode;  // Insertion at the head if there was no previous node
    } else {
        next[prevNode] = newNode;  // Link the previous node to the new node
    }
	next[newNode] = currentNode;
    sizeOfBag++;
}



bool SortedBag::remove(TComp e) {
	int currentNode = head;
	int prevNode = -1;
	
	while(currentNode != -1 && elements[currentNode].first != e){
		prevNode = currentNode;
		currentNode = next[currentNode];
	}

	if(currentNode == -1){
		return false;
	}

	elements[currentNode].second--;
	int frequency = elements[currentNode].second;
	if(frequency == 0){
		if(prevNode == -1){
			head = next[currentNode];
		} else {
			next[prevNode] = next[currentNode];
		}
		next[currentNode] = firstEmpty;
		firstEmpty = currentNode;
	}

	sizeOfBag--;

	return true;

}


bool SortedBag::search(TComp elem) const {
    int currentNode = head;

    while (currentNode != -1) {
        if (elements[currentNode].first == elem) {
            return true;
        }
        if (!relation(elements[currentNode].first, elem)) {
            break;
        }
        currentNode = next[currentNode];
    }

    return false;
}



int SortedBag::nrOccurrences(TComp elem) const {
	if(head == -1)
		return 0;

	int currentNode = head;

	while(currentNode != -1){
		if(elements[currentNode].first == elem){
			return elements[currentNode].second;
		}

		if(!relation(elements[currentNode].first, elem) && !relation(elem, elements[currentNode].first))
			break;

		currentNode = next[currentNode];
	}

	return 0;
}



int SortedBag::size() const {
	return sizeOfBag;
}


bool SortedBag::isEmpty() const {
	return sizeOfBag == 0;
}

int SortedBag::removeOccurrences(int nr, TComp e){
	int currentNode = head;
	int prevNode = -1;
	int removed = 0;

	if(nr < 0){
		throw std::exception();
	}

	while(currentNode != -1 && removed < nr){
		if(elements[currentNode].first == e){
			elements[currentNode].second--;
			removed++;
			if(elements[currentNode].second == 0){
				if(prevNode == -1){
					head = next[currentNode];
				} else {
					next[prevNode] = next[currentNode];
				}
				next[currentNode] = firstEmpty;
				firstEmpty = currentNode;
			}
		}

		if(elements[currentNode].first != e || elements[currentNode].second == 0){
			prevNode = currentNode;
			currentNode = next[currentNode];
		}
	}

	sizeOfBag -= removed;

	return removed;
}


SortedBagIterator SortedBag::iterator() const {
	return SortedBagIterator(*this);
}


SortedBag::~SortedBag() {
	delete[] elements;
	delete[] next;
}
