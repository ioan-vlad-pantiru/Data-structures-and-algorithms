#include <exception>
#include "BagIterator.h"
#include "Bag.h"

void BagIterator::move() {
	while ((current < bag.m) && bag.e[current] == -1)
		current++;
}

//constructor BagIterator
BagIterator::BagIterator(const Bag& col) :
		bag(col) {
	current = 0;
	move();
}

void BagIterator::first() {
	current = 0;
	move();
}

void BagIterator::next() {
	if (!valid()){
		throw std::exception();
	}
	current++;
	move();
}

bool BagIterator::valid() const {
	return (current < bag.m);
}

TElem BagIterator::getCurrent() const {
	if (!valid()){
			throw std::exception();
	}
	return bag.e[current];
}
