#include "SMIterator.h"
#include "SortedMap.h"
#include <exception>


#include <iostream>

using namespace std;

SMIterator::SMIterator(const SortedMap& m) : map(m){
	this->currentPosition = 1;
	this->validation = true;
}

void SMIterator::first(){
	// Θ(1)
	this->currentPosition = 1;
}

void SMIterator::next(){
	// Θ(1)
	if (this->valid()) {
		this->currentPosition++;
	}
	else { throw exception(); }
}

bool SMIterator::valid() const{
	// Θ(1)
	if (this->currentPosition <= this->map.size() && this->validation) {
		return true;
	}
	else {
		return false;
	}
}

TElem SMIterator::getCurrent() const{
	// Θ(1)
	if (this->valid()) {
		return this->map.elements[this->currentPosition];
	}
	else { throw exception(); }
	return NULL_TPAIR;
}

void SMIterator::jumpBackward(int k) {
	// Θ(1)
	if (k <= 0) { throw exception("Invalid k!");}
	else if (this->currentPosition - k < 1) { this->validation = false; }
	else { this->currentPosition -= k; }
}


