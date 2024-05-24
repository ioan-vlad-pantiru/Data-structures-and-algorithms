#include "SMIterator.h"
#include "SortedMap.h"
#include <exception>
using namespace std;

void SortedMap::resize() {
	int oldCapacity = capacity;
	capacity *= 2;
	Node** newTable = new Node*[capacity] {};

	for(int i = 0; i < oldCapacity; i++){
		Node* current = hashTable[i];
		while(current != nullptr) {
			int newIndex = std::abs(current->elem.first) % capacity;
			Node* next = current->next;
			current->next = newTable[newIndex];
			newTable[newIndex] = current;
			current = next;
		}
	}
	delete[] hashTable;
	hashTable = newTable;
}

SortedMap::SortedMap(Relation r) : rel(r), capacity(INITIAL_CAPACITY), _size(0){
	hashTable = new Node*[capacity] {};
}

TValue SortedMap::add(TKey k, TValue v) {
	//O(n)
	if (_size > capacity * 0.75){
		resize();
	}

	int index = hash(k);
	Node* current = hashTable[index];
	Node* prev = nullptr;

	while(current != nullptr && current->elem.first != k) {
		prev = current;
		current = current->next;
	}

	if(current != nullptr) {
		TValue oldVal = current->elem.second;
		current->elem.second = v;
		return oldVal;
	}

	Node* newNode = new Node(k, v);
	if (prev == nullptr){
		hashTable[index] = newNode;
	} else {
		prev->next = newNode;
	}
	_size++;
	return NULL_TVALUE;
}

TValue SortedMap::search(TKey k) const {
	//O(n)
	int index = hash(k);
	Node* current = hashTable[index];

	while (current != nullptr) {
		if (current->elem.first == k){
			return current->elem.second;
		}
		current = current->next;
	}

	return NULL_TVALUE;
}

TValue SortedMap::remove(TKey k) {
	//O(n)
	int index = hash(k);
	Node* current = hashTable[index];
	Node* prev = nullptr;

	while(current != nullptr && current->elem.first != k) {
		prev = current;
		current = current->next;
	}

	if (current == nullptr) {
		return NULL_TVALUE;
	}

	TValue retVal = current->elem.second;
	if (prev == nullptr) {
		hashTable[index] = current->next;
	} else {
		prev->next = current->next;
	}

	delete current;
	_size--;

	return retVal;
}

int SortedMap::size() const {
	//O(1)
	return _size;
}

bool SortedMap::isEmpty() const {
	//O(1)
	return _size == 0;
}

int SortedMap::getValueRange() const {
	//Best case: O(1)
	//Worst case: O(n)
	//Average case: O(n)
    if (_size == 0) {
        return -1;
    }

    bool isInitialized = false;
    TValue minValue, maxValue;

    for (int i = 0; i < capacity; i++) {
        Node* current = hashTable[i];
        while (current != nullptr) {
            if (!isInitialized) {
                minValue = maxValue = current->elem.second;
                isInitialized = true;
            } else {
                if (current->elem.second < minValue) {
                    minValue = current->elem.second;
                }
                if (current->elem.second > maxValue) {
                    maxValue = current->elem.second;
                }
            }
            current = current->next;
        }
    }

    return maxValue - minValue;
}

SMIterator SortedMap::iterator() const {
	return SMIterator(*this);
}

SortedMap::~SortedMap() {
	for(int i = 0; i < capacity; i++){
		Node* current = hashTable[i];
		while (current != nullptr){
			Node* toDelete = current;
			current = current->next;
			delete toDelete;
		}
	}
	delete[] hashTable;
}
