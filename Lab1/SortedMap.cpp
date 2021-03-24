#include "SMIterator.h"
#include "SortedMap.h"
#include <exception>
#include <iostream>
using namespace std;

void SortedMap::resize()
{
	int newCapacity = this->capacity * 2;
	TElem* newElements = new TElem[newCapacity];
	for (int index = 1; index < this->capacity; index++) {
		newElements[index] = this->elements[index];
	}
	delete[] this->elements;
	this->elements = newElements;
	this->capacity = newCapacity;
	}


SortedMap::SortedMap(Relation r) {
	this->r = r;
	this->capacity = 2;
	this->length = 0;
	this->elements = new TElem[this->capacity];
}

TValue SortedMap::add(TKey k, TValue v){
	//Best Case: Θ(1) - if the array is empty
	//Worst Case: Θ(n) - otherwise
	//Averge Case: O(n)
	if (this->isEmpty()) {
		this->elements[1].first = k;
		this->elements[1].second= v;
		this->length++;
		return NULL_TVALUE;
	}
	else if (this->search(k) != NULL_TVALUE){
		for (int index = 1; index <= this->length; index++) {
			if (this->elements[index].first == k) {
				TValue replacedValue = this->elements[index].second;
				this->elements[index].second = v;
				return replacedValue;
			}
		}
	}
	else{
		bool added = false;
		TKey copyKey = k;
		TValue copyValue = v;
		for (int index = 1; index <= this->length; index++) {
			if (!added) {
				if (!this->r(this->elements[index].first, k)) {
					copyKey = this->elements[index].first;
					copyValue = this->elements[index].second;
					this->elements[index].first = k;
					this->elements[index].second = v;
					added = true;
				}
			}
			else {
				k = this->elements[index].first;
				v = this->elements[index].second;
				this->elements[index].first = copyKey;
				this->elements[index].second = copyValue;
				copyKey = k;
				copyValue = v;
			}
		}
		if (this->length + 1 == this->capacity) { this->resize(); }
		this->length++;
		this->elements[length].first = copyKey;
		this->elements[length].second = copyValue;
		return NULL_TVALUE;
	}
	
}

TValue SortedMap::search(TKey k) const {
	//Best Case: Θ(1) - if the element we search is on the first position or if the map is empty
	//Worst Case: Θ(n) - if the element that we search is on the last position
	//Averge Case: O(n)
	if (!this->isEmpty()) {
		for (int index = 1; index <= this->length; index++) {
			if (this->elements[index].first == k) { return this->elements[index].second; }
		}
	}
	return NULL_TVALUE;
}

TValue SortedMap::remove(TKey k) {
	// Θ(n)
	if (this->search(k) != NULL_TVALUE) {
		TValue valueRemoved = NULL_TVALUE;
		bool removed = false;
		for (int index = 1; index <= this->length; index++) {
			if (!removed) {
				if (this->elements[index].first == k) {
					valueRemoved = this->elements[index].second;
					removed = true;
				}
			}
			else {
				this->elements[index - 1].first = this->elements[index].first;
				this->elements[index - 1].second = this->elements[index].second;
			}
		}
		this->elements[this->length] = NULL_TPAIR;
		this->length--;
		return valueRemoved;
	}
	return NULL_TVALUE;
}

int SortedMap::size() const {
	// Θ(1)
	return this->length;
}

bool SortedMap::isEmpty() const {
	// Θ(1)
	if (this->length > 0) {
		return false;
	}
	return true;
}

SMIterator SortedMap::iterator() const {
	return SMIterator(*this);
}

SortedMap::~SortedMap() {
	//TODO - Implementation
	delete[] this->elements;
}
