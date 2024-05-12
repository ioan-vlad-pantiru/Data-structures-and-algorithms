#include "Bag.h"
#include "BagIterator.h"
#include <iostream>
#include <exception>
#include <math.h>
using namespace std;

//symbolic constant that indicates a free location in the hash table
#define NIL -1

//function that gives the hashCode of an element
int hashCode(TElem e){
   return abs(e);
}

//the hash function
int Bag::h(TElem e, int i) {
	return (hashCode(e) % m + i) % m;
}


Bag::Bag() {
    m = MAX;
	for (int i = 0; i < m; i++) {
		e[i] = NIL;
	}

}

void Bag::add(TElem elem) {
		int i=0; //probe number
		bool gasit = false;
		do {
			int j = h(elem, i);
			if (e[j] == NIL) {
				e[j] = elem;
				gasit = true;
			}
			else i++;
		} while (i < m && !gasit);
		if (i == m) {
				//resize & rehash, but we assume that m is high-enough, so this is not needed
		}

}

BagIterator Bag::iterator() const{
	return BagIterator(*this);
}

Bag::~Bag() {
}




