#include "ListIterator.h"
#include "IndexedList.h"
#include <exception>

using namespace std;

ListIterator::ListIterator(const IndexedList& list) : list(list){
   //TODO - Implementation
    this->currentNode = list.head;
}

void ListIterator::first(){
    //TODO - Implementation
    this->currentNode = list.head;
}

void ListIterator::next(){
    //TODO - Implementation
    if (this->valid()) { this->currentNode = this->currentNode->nextNode; }
    else { throw exception(); }
}

bool ListIterator::valid() const{
    //TODO - Implementation
    if (this->currentNode == NULL) { return false; }
	return true;
}

TElem ListIterator::getCurrent() const{
   //TODO - Implementation
    if (this->valid()) { return this->currentNode->data; }
    else { throw exception(); }
}