#include "SMIterator.h"
#include "SortedMap.h"
#include <exception>
using namespace std;

SortedMap::SortedMap(Relation r) : rel(r), capacity(INITIAL_CAPACITY), _size(0){
	hashTable = new Node*[capacity] {};
}

TValue SortedMap::add(TKey k, TValue v) {
	int index = hash(k);
	Node* current = hashTable[index];
	Node* prev = nullptr;
}

TValue SortedMap::search(TKey k) const {
	//TODO - Implementation
	return NULL_TVALUE;
}

TValue SortedMap::remove(TKey k) {
	//TODO - Implementation
	return NULL_TVALUE;
}

int SortedMap::size() const {
	//TODO - Implementation
	return 0;
}

bool SortedMap::isEmpty() const {
	//TODO - Implementation
	return false;
}

SMIterator SortedMap::iterator() const {
	return SMIterator(*this);
}

SortedMap::~SortedMap() {
	//TODO - Implementation
}
