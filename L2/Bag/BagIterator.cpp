#include <exception>
#include "BagIterator.h"

using namespace std;


BagIterator::BagIterator(const Bag& c): bag(c), currentFrequency(0)
{
	current = c.head;
	if (current != nullptr) {
        currentFrequency = current->getFrequency();
    }
}

void BagIterator::first() {
	current = bag.head;
    if (current != nullptr) {
        currentFrequency = current->getFrequency();
    }
}


void BagIterator::next() {
	if (!valid()) {
        throw exception();
    }
    if (currentFrequency > 1) {
        currentFrequency--;
    } else {
        current = current->getNext();
        if (current != nullptr) {
            currentFrequency = current->getFrequency();
        }
    }
}


bool BagIterator::valid() const {
	return (this->current!=nullptr);
}



TElem BagIterator::getCurrent() const
{
	if (!valid()) {
        throw exception();
    }
    return current->getValue();
}
