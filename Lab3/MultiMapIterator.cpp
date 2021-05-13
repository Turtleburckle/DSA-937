#include "MultiMapIterator.h"
#include "MultiMap.h"


MultiMapIterator::MultiMapIterator(const MultiMap& c): col(c) {
	//Best / Worst / Average Case : Θ(1)
	this->currentPosition = this->col.head;
}

TElem MultiMapIterator::getCurrent() const{
	// Best/ Worst/ Average Case : Θ(1)
	if (this->valid()) { return this->col.elements[this->currentPosition]; }
	else { throw exception(); }
	
}

bool MultiMapIterator::valid() const {
	// Best/ Worst/ Average Case : Θ(1)
	return !(this->currentPosition == -1);
}

void MultiMapIterator::next() {
	// Best/ Worst/ Average Case : Θ(1)
	if (!this->valid()) { throw exception(); }
	this->currentPosition = this->col.next[this->currentPosition];
}

void MultiMapIterator::first() {
	// Best/ Worst/ Average Case : Θ(1)
	this->currentPosition = this->col.head;
}

