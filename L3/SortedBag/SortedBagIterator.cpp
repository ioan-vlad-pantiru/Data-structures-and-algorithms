#include "SortedBagIterator.h"
#include "SortedBag.h"
#include <exception>

using namespace std;

SortedBagIterator::SortedBagIterator(const SortedBag& b) : bag(b){
	current = b.head;
	if( current != -1)
		currentFrequency = b.elements[current].second;
	frequencyIndex = 0;
}

TComp SortedBagIterator::getCurrent() {
	if(!valid())
		throw std::exception();
	return this->bag.elements[current].first;
}

bool SortedBagIterator::valid() {
	return current != -1;
}

void SortedBagIterator::next() {
	if(!valid())
		throw std::exception();
	if(frequencyIndex < currentFrequency - 1)
		frequencyIndex++;
	else{
		current = bag.next[current];
		if(current != -1)
			currentFrequency = bag.elements[current].second;
			frequencyIndex = 0;
	}
	
}

void SortedBagIterator::first() {
	current = bag.head;
	if(current != -1){
		currentFrequency = bag.elements[current].second;
		frequencyIndex = 0;
	}
}

