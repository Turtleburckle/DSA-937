#include "SMIterator.h"
#include "SortedMap.h"
#include <exception>


#include <iostream>

using namespace std;

SMIterator::SMIterator(const SortedMap& m) : map(m){
	this->currentPosition = 1;
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
	if (this->currentPosition <= this->map.size()) {
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


