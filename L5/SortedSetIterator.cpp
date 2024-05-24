#include "SortedSetIterator.h"
#include <exception>
#include <iostream>

SortedSetIterator::SortedSetIterator(const SortedSet& s) : set(s), currentNode(0), numberOfNodes(0) {
    nodes = new TComp[s.size()];

    inorder(s.root);
}

void SortedSetIterator::inorder(int node) {
    if (node == -1) {
        return;
    }

    inorder(set.nodes[node].left);
    nodes[numberOfNodes++] = set.nodes[node].data;
    inorder(set.nodes[node].right);
}

void SortedSetIterator::first() {
    currentNode = 0;
}

void SortedSetIterator::next() {
    if (!valid()) {
        throw std::exception();
    }

    currentNode += 1;
}

TElem SortedSetIterator::getCurrent() {
    if (!valid()) {
        throw std::exception();
    }
    return this->nodes[currentNode];
}

bool SortedSetIterator::valid() const {
    return currentNode < numberOfNodes;
}

SortedSetIterator::~SortedSetIterator() {
    delete[] nodes;
}
