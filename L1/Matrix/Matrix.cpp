#include "Matrix.h"
#include <exception>
using namespace std;


Matrix::Matrix(int nrLines, int nrCols) {
	this->nrLin = nrLines;
	this->nrCol = nrCols;

	this->capacity = nrLines * nrCols;

	this->e = new tuple<int, int, TElem>[capacity];

	this->size = 0;
}


int Matrix::nrLines() const {
	//O(1)

	return this->nrLin;
}


int Matrix::nrColumns() const {
	//O(1)
	return this->nrCol;
}


TElem Matrix::element(int i, int j) const {
	//O(n)

	if(i < 0 || i >= this->nrLin || j < 0 || j >= this->nrCol)
		throw std::exception();	
	
	for (int k = 0; k < this->size; k++) {
		if (get<0>(this->e[k]) == i && get<1>(this->e[k]) == j)
			return get<2>(this->e[k]);
	}
	return NULL_TELEM;
}

TElem Matrix::modify(int i, int j, TElem e) {
	//O(n)

	if(i < 0 || i >= this->nrLin || j < 0 || j >= this->nrCol)
		throw std::exception();	
	
	TElem old;
	for (int k = 0; k < this->size; k++) {
		if (get<0>(this->e[k]) == i && get<1>(this->e[k]) == j) {
			old = get<2>(this->e[k]);
			if(e != NULL_TELEM){
				this->e[k] = make_tuple(i, j, e);
			}
			if(e == NULL_TELEM) {
				for (int l = k; l < this->size - 1; l++) {
					this->e[l] = this->e[l + 1];
				}
				this->size--;
			}
			return old;
			
		}
		if (get<0>(this->e[k]) > i || (get<0>(this->e[k]) == i && get<1>(this->e[k]) > j)) {
			for (int l = this->size; l > k; l--) {
				this->e[l] = this->e[l - 1];
			}
			this->e[k] = make_tuple(i, j, e);
			this->size++;
			return NULL_TELEM;
		}
	}
	this->e[this->size] = make_tuple(i, j, e);
	this->size++;
	return NULL_TELEM;
}


