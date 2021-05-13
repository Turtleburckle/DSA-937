#include "MultiMap.h"
#include "MultiMapIterator.h"
#include <exception>
#include <iostream>

using namespace std;


void MultiMap::resize()
{
	int newCapacity = this->capacity * 2;
	TElem* newElements = new TElem[newCapacity];
	int* newNext = new int[newCapacity];
	for (int index = 0; index < this->capacity; index++) {
		newElements[index] = this->elements[index];
		newNext[index] = this->next[index];
	}
	for (int index = this->capacity - 1 ; index < newCapacity; index++) {
		newNext[index] = index + 1;
	}
	
	this->capacity = newCapacity;
	this->elements = newElements;
	this->next = newNext;
}

MultiMap::MultiMap() {
	// Best / Worst / Average Case : Θ(n) - n the capacity
	this->capacity = 3;
	this->length = 0;
	this->head = -1;
	this->nextFree = 0;
	this->elements = new TElem[this->capacity];
	this->next = new int[this->capacity];
	for (int index = 0; index < this->capacity; index++) {
		this->next[index] = index + 1;
	}
}


void MultiMap::add(TKey c, TValue v) {
	// Best Case : Θ(1) - if the array is empty or if there is only one element.
	// Worst Case: Θ(n) - otherwise, because we need to find the end.
	// Average Case: O(n)
	
	if (this->length + 1 == this->capacity) { this->resize(); }
	if (this->head == -1 || this->length == 0) { // this means that the multi map is empty
		this->head = this->nextFree;
		this->nextFree = this->next[this->nextFree];
		this->next[this->head] = -1;
		this->elements[this->head].first = c;
		this->elements[this->head].second = v;
		this->length++;
	}
	else if (this->next[this->head] == -1) { // in this case it means that there is only one element
		int currentPosition = this->nextFree;
		this->nextFree = this->next[this->nextFree];
		this->next[this->head] = currentPosition;
		this->elements[currentPosition].first = c;
		this->elements[currentPosition].second = v;
		this->next[currentPosition] = -1;
		this->length++;
	}
	else {
		int currentPosition = this->nextFree; //S1
		
		this->nextFree = this->next[this->nextFree]; //S2
		
		int last = this->head;
		while (this->next[last] != -1) {
			last = this->next[last];
		} // S3
		
		this->next[last] = currentPosition; //S4
		
		this->next[currentPosition] = -1; //S5
		
		this->elements[currentPosition].first = c; 
		this->elements[currentPosition].second = v; //S6

		this->length++; //S7
	}
}


bool MultiMap::remove(TKey c, TValue v) {
	// Best Case : Θ(1) - when the entry that we want to remove is the first one (the head)/if the size of the map is 0 or 1
	// Worst Case: Θ(n) - if the entry that we search for doesn't exist or is the last one.
	// Average Case : O(n) 
	if (this->head == -1 || this->length == 0) {
		return false;
	}
	else if (this->length == 1) {
		if (this->elements[this->head].first == c && this->elements[this->head].second == v) {
			this->next[this->head] = this->nextFree;
			this->nextFree = this->head;
			this->head = -1;
			this->length--;
			return true;
		}
		else {
			return false;
		}
	}
	else if (this->elements[this->head].first == c && this->elements[this->head].second == v) {
		int nextHead = this->next[this->head];
		this->next[this->head] = this->nextFree;
		this->nextFree = this->head;
		this->head = nextHead;
		this->length--;
		return true;
	}
	else {
		int last= this->head;

		while (this->next[last] != -1) {
			int currentPosition = this->next[last];
			if (this->elements[currentPosition].first == c && this->elements[currentPosition].second == v) {
				this->next[last] = this->next[currentPosition];
				this->next[currentPosition] = this->nextFree;
				this->nextFree = currentPosition;
				this->length--;
				return true;
			}
			else { last = currentPosition; }
		}
		return false;
	}
	return false;
}


vector<TValue> MultiMap::search(TKey c) const {
	// Best/ Worst/ Average Case : Θ(n) - because there could be more than one entry with the same key and we have to search until the end. 
	vector<TValue> result;
	int currentPosition = this->head;
	while (currentPosition != -1) {
		if (this->elements[currentPosition].first == c) {
			result.push_back(this->elements[currentPosition].second);
		}
		currentPosition = this->next[currentPosition];
	}
	return result;
}


int MultiMap::size() const {
	// Best/ Worst/ Average Case: Θ(1) - because we store the value.
	return this->length;

}


bool MultiMap::isEmpty() const {
	// Best/ Worst/ Average Case : Θ(1) - because we know the number of entries.
	return this->length == 0;
}

vector<TValue> MultiMap::valueBag() const
{	// Best/ Worst/ Average Case: Θ(1) - if there are no entries;
	// Worst Case: Θ(n) - otherwise;
	// Average Case : O(n)
	vector<TValue> result;
	if (this->length == 0) {
		return result;
	}
	else if (this->length == 1) {
		result.push_back(this->elements[this->head].second);
		return result;
	}
	int currentPosition = this->head;
	while (currentPosition != -1) {
		result.push_back(this->elements[currentPosition].second);
		currentPosition = this->next[currentPosition];
	}
	return result;
}

MultiMapIterator MultiMap::iterator() const {
	return MultiMapIterator(*this);
}


MultiMap::~MultiMap() {
	//Best/ Worst/ Average Case : Θ(1)
	delete[] this->elements;
	delete[] this->next;
}

