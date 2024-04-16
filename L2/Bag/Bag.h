#pragma once
//DO NOT INCLUDE BAGITERATOR


//DO NOT CHANGE THIS PART
#define NULL_TELEM -111111;
typedef int TElem;
class BagIterator; 

class Node;

typedef Node *PNod;


class Node{
	private:
		TElem value;
		int frequency;
		PNod next;
		PNod prev;
		
	public:
		friend class Bag;
		Node(TElem value, int frequency, PNod prev, PNod next) : value(value), frequency(frequency), prev(prev), next(next) {};
		TElem getValue() { return value; }
		PNod getNext() { return next; }
		PNod getPrev() { return prev; }
		int getFrequency() { return frequency; }
};

class Bag {

private:
	PNod head;
	PNod tail;
	int numElements;

	

	//DO NOT CHANGE THIS PART
	friend class BagIterator;
public:
	//constructor
	Bag();

	//removes nr occurrences of elem from the Bag
	int removeOccurences(int nr, TElem elem);

	//adds an element to the bag
	void add(TElem e);

	//removes one occurrence of an element from a bag
	//returns true if an element was removed, false otherwise (if e was not part of the bag)
	bool remove(TElem e);

	//checks if an element appearch is the bag
	bool search(TElem e) const;

	//returns the number of occurrences for an element in the bag
	int nrOccurrences(TElem e) const;

	//returns the number of elements from the bag
	int size() const;

	//returns an iterator for this bag
	BagIterator iterator() const;

	//checks if the bag is empty
	bool isEmpty() const;

	//destructor
	~Bag();
};