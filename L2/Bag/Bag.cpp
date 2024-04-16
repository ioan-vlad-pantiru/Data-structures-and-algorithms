#include "Bag.h"
#include "BagIterator.h"
#include <exception>
#include <iostream>
using namespace std;


Bag::Bag() : head(nullptr), tail(nullptr), numElements(0) {}


void Bag::add(TElem elem) {
    //Complexity: O(n)
	PNod current = head;
    while (current != nullptr) {
        if (current->value == elem) {
            current->frequency += 1;
			numElements++;
            return;
        }
        current = current->next;
    }
    // Element not found, create a new node
    PNod newNode = new Node(elem, 1, tail, nullptr);
    if (tail != nullptr) {
        tail->next = newNode;
    } else {
        // Bag was empty
        head = newNode;
    }
    tail = newNode;
    numElements++;
}


bool Bag::remove(TElem elem) {
    //Complexity: O(n)
    PNod current = head;
    while (current != nullptr) {
        if (current->value == elem) {
            current->frequency -= 1;
			numElements--;
            if (current->frequency == 0) {
                if (current == head) { head = current->next; }
                if (current == tail) { tail = current->prev; }
                if (current->prev != nullptr) { current->prev->next = current->next; }
                if (current->next != nullptr) { current->next->prev = current->prev; }
                delete current;
            }
            return true;
        }
        current = current->next;
    }
    return false;
}



bool Bag::search(TElem elem) const {
    //Complexity: O(n)
	PNod current = head;
	while(current != nullptr){
		if(current->value == elem){
			return true;
		}
		current = current->getNext();
	}
	return false;
}

int Bag::nrOccurrences(TElem elem) const {
    //Complexity: O(n)
	int count = 0;
	PNod current = head;
	while(current != nullptr){
		if(current->value == elem){
			return current->frequency;
		}
		current = current->getNext();
	}
	return 0;
}


int Bag::size() const {
    //Complexity: Theta(1)
	return numElements;
}


bool Bag::isEmpty() const {
    //Complexity: Theta(1)
	return head == nullptr;
}

int Bag::removeOccurences(int nr, TElem elem) {
    //Complexity: O(n)
    if (nr <= 0) {
        throw std::exception();
    }

    PNod current = head;
    int removed = 0; // To track the number of removed occurrences

    while (current != nullptr) {
        if (current->value == elem) {
            if (current->frequency <= nr) {
                nr -= current->frequency;
                removed += current->frequency;
                numElements -= current->frequency;

                PNod toDelete = current;

                if (current->prev) current->prev->next = current->next;
                if (current->next) current->next->prev = current->prev;
                if (current == head) head = current->next;
                if (current == tail) tail = current->prev;
                
                current = current->next;
                delete toDelete;
            } else {
                current->frequency -= nr;
                numElements -= nr;
                removed += nr;
                break;
            }
        } else {
            current = current->next;
        }
    }

    return removed;
}


BagIterator Bag::iterator() const {
	return BagIterator(*this);
}


Bag::~Bag() {
	while(head != nullptr){
		PNod current = head;
		head = head->next;
		delete current;
	}
	head = tail = nullptr;
	numElements = 0;
}

