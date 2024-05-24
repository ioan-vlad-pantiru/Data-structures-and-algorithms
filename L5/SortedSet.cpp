#include "SortedSet.h"
#include "SortedSetIterator.h"

const int INITIAL_CAPACITY = 10;

SortedSet::SortedSet(Relation r) : relation(r), capacity(INITIAL_CAPACITY), root(-1), firstFree(0), numberOfElements(0) {
	nodes = new Node[capacity];
	initializeNodes();
}

void SortedSet::resize() {
	int newCapacity = 2 * capacity;
    Node* newNodes = new Node[newCapacity];
    for (int i = 0; i < capacity; ++i) {
        newNodes[i] = nodes[i];
    }
    for (int i = capacity; i < newCapacity; ++i) {
        newNodes[i].left = i + 1;
        newNodes[i].right = -1;
    }
    newNodes[newCapacity - 1].left = -1;
    firstFree = capacity;
    capacity = newCapacity;
    delete[] nodes;
    nodes = newNodes;
}

void SortedSet::initializeNodes() {
    for (int i = 0; i < capacity; ++i) {
        nodes[i].left = i + 1;
        nodes[i].right = -1;
    }
    nodes[capacity - 1].left = -1;
}

int SortedSet::allocateNode() {
    if (firstFree == -1) {
        resize();
    }
    int newNode = firstFree;
    firstFree = nodes[firstFree].left;
    return newNode;
}

void SortedSet::deallocateNode(int index) {
    nodes[index].left = firstFree;
    nodes[index].right = -1;
    firstFree = index;
}


bool SortedSet::add(TComp elem) {
	if(root == -1) {
		int newNode = allocateNode();
		nodes[newNode].data = elem;
		nodes[newNode].left = -1;
		nodes[newNode].right = -1;
		root = newNode;
		numberOfElements++;
		return true;
	}

	int currentNode = root;
	int parentNode = -1;
	while(currentNode != -1) {
		if (nodes[currentNode].data == elem) {
            return false;
        }
        parentNode = currentNode;
        if (relation(elem, nodes[currentNode].data)) {
            currentNode = nodes[currentNode].left;
        } else {
            currentNode = nodes[currentNode].right;
        }
	}

	int newNode = allocateNode();
    nodes[newNode].data = elem;
    nodes[newNode].left = -1;
    nodes[newNode].right = -1;
    if (relation(elem, nodes[parentNode].data)) {
        nodes[parentNode].left = newNode;
    } else {
        nodes[parentNode].right = newNode;
    }
    numberOfElements++;
    return true;
}


bool SortedSet::remove(TComp elem) {
	int currentNode = root;
    int parentNode = -1;
    bool isLeftChild = false;

    while (currentNode != -1 && nodes[currentNode].data != elem) {
        parentNode = currentNode;
        if (relation(elem, nodes[currentNode].data)) {
            isLeftChild = true;
            currentNode = nodes[currentNode].left;
        } else {
            isLeftChild = false;
            currentNode = nodes[currentNode].right;
        }
    }

    if (currentNode == -1) {
        return false;
    }

    // Node with only one child or no child
    if (nodes[currentNode].left == -1) {
        if (currentNode == root) {
            root = nodes[currentNode].right;
        } else if (isLeftChild) {
            nodes[parentNode].left = nodes[currentNode].right;
        } else {
            nodes[parentNode].right = nodes[currentNode].right;
        }
    } else if (nodes[currentNode].right == -1) {
        if (currentNode == root) {
            root = nodes[currentNode].left;
        } else if (isLeftChild) {
            nodes[parentNode].left = nodes[currentNode].left;
        } else {
            nodes[parentNode].right = nodes[currentNode].left;
        }
    } else {
        // Node with two children: Get the inorder successor (smallest in the right subtree)
        int successorParent = currentNode;
        int successor = nodes[currentNode].right;
        while (nodes[successor].left != -1) {
            successorParent = successor;
            successor = nodes[successor].left;
        }

        // Copy the successor's value to the current node
        nodes[currentNode].data = nodes[successor].data;

        // Delete the successor
        if (successorParent != currentNode) {
            nodes[successorParent].left = nodes[successor].right;
        } else {
            nodes[successorParent].right = nodes[successor].right;
        }

        currentNode = successor;
    }

    deallocateNode(currentNode);
    numberOfElements--;
    return true;
}


bool SortedSet::search(TComp elem) const {
	int currentNode = root;
	while (currentNode != -1) {
		if (nodes[currentNode].data == elem) {
			return true;
		} else if (relation(elem, nodes[currentNode].data)) {
			currentNode = nodes[currentNode].left;
		} else {
			currentNode = nodes[currentNode].right;
		}
	}
	return false;
}


int SortedSet::size() const {
	return numberOfElements;
}



bool SortedSet::isEmpty() const {
	return numberOfElements == 0;
}

SortedSetIterator SortedSet::iterator() const {
	return SortedSetIterator(*this);
}


SortedSet::~SortedSet() {
	delete[] nodes;
}


