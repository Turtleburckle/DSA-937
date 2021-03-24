#pragma once
#include "SortedMap.h"

//DO NOT CHANGE THIS PART
class SMIterator{
	friend class SortedMap;
private:
	const SortedMap& map;
	SMIterator(const SortedMap& mapionar);
	//TODO - Representation
	int currentPosition;
	bool validation;

public:
	void first();
	void next();
	bool valid() const;
    TElem getCurrent() const;

	//moves the current element from the iterator k steps backward, or makes the iterator invalid if there are less than k elements left until the beginning of the SortedMap.
	//throws an exception if the iterator is invalid or if k is negative or zero
	void jumpBackward(int k);
};

