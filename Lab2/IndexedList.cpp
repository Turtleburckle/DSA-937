#include <exception>
#include <iostream>
#include "IndexedList.h"
#include "ListIterator.h"
using namespace std;
IndexedList::IndexedList() {
	this->head = NULL;
	this->tail = NULL;
	this->length = 0;
}

int IndexedList::size() const {
    // Best | Worst | Average case = Θ(1)
	return this->length;
}


bool IndexedList::isEmpty() const {
    // Best | Worst | Average case = Θ(1)
	return this->length == 0;
}

TElem IndexedList::getElement(int pos) const {
    // Best case = Θ(1) - if it's the first or the last
    // Worst case = Θ(n) - if it's the one before the tail.
    // Average case = O(n)
    if (pos < 0 || pos >=  this->length){throw exception();}
    else if (pos == 0){return this->head->data;}
    else if (pos == this->length-1){return  this->tail->data;}
    int currentPosition = 1;
    Node* currentNode = this->head->nextNode;
    while (currentPosition < pos){
        currentNode = currentNode->nextNode;
        currentPosition++;
    }
    return currentNode->data;
}

TElem IndexedList::setElement(int pos, TElem e) {
    // Best case = Θ(1) - if it's the first/last or the position is invalid
    // Worst case = Θ(n) - if it's the one before the tail
    // Average case = O(n)
    if (pos < 0 || pos >= this->length){throw exception();}
    else if (pos == 0){
        TElem oldData = this->head->data;
        this->head->data = e;
        return oldData;
    } else if (pos == this->length - 1){
        TElem oldData = this->tail->data;
        this->tail->data = e;
        return oldData;
    }
    int currentPosition = 1;
    Node* currentNode = this->head->nextNode;
    while (currentPosition < pos){
        currentNode = currentNode->nextNode;
        currentPosition++;
    }
    TElem oldData = currentNode->data;
    currentNode->data = e;
    return oldData;
}

void IndexedList::addToEnd(TElem e) {
    // Best | Worst | Average = Θ(1)
    Node* newNode = new Node();
    newNode->data = e;
    if (this->length == 0) {
        newNode->previousNode = NULL;
        newNode->nextNode = NULL;
        this->head = newNode;
        this->tail = newNode;
    }
    else if (this->length == 1) {
        this->head->nextNode = newNode;
        newNode->previousNode = this->head;
        newNode->nextNode = NULL;
        this->tail = newNode;
    } 
    else{
        newNode->previousNode = this->tail;
        newNode->nextNode = NULL;
        this->tail->nextNode = newNode;
        this->tail = newNode;
    }
    this->length++;
}

void IndexedList::addToPosition(int pos, TElem e) {
    // Best case = Θ(1) - if the position we want to add the element is the first or the last
    // Worst case = Θ(n) - if we want to add it before the tail
    // Average case = O(n)

    if (pos < 0 || pos > this->length) { throw exception(); }
    else if (this->length == 0) {
        Node* newNode = new Node();
        newNode->data = e;
        newNode->nextNode = NULL;
        newNode->previousNode = NULL;
        this->head = newNode;
        this->tail = newNode;
        this->length++;
    }
    else if (this->length == 1) {
        Node* newNode = new Node();
        newNode->data = e;
        if (pos == 0) {
            newNode->nextNode = this->tail;
            newNode->previousNode = NULL;
            this->head = newNode;
            this->tail->previousNode = newNode;
        }
        else if (pos == 1) {
            newNode->nextNode = NULL;
            newNode->previousNode = this->head;
            this->tail = newNode;
        }
        this->length++;
    }
    else if (this->length == 2) {
        Node* newNode = new Node();
        newNode->data = e;
        newNode->nextNode = this->tail;
        newNode->previousNode = this->head;
        this->head->nextNode = newNode;
        this->tail->previousNode = newNode;
        this->length++;
    }
    else {
        Node* newNode = new Node();
        newNode->data = e;
        if (pos == 0) {
            newNode->nextNode = this->head;
            newNode->previousNode = NULL;
            this->head->previousNode = newNode;
            this->head = newNode;
        }
        else if (pos == this->length) {
            newNode->previousNode = this->tail;
            newNode->nextNode = NULL;
            this->tail->nextNode = newNode;
            this->tail = newNode;
        }
        else {
            int currentPosition = 1;
            Node* currentNode = this->head->nextNode;
            while (currentPosition < pos) {
                currentNode = currentNode->nextNode;
                currentPosition++;
            }
            newNode->nextNode = currentNode;
            newNode->previousNode = currentNode->previousNode;
            currentNode->previousNode->nextNode = newNode;
            currentNode->previousNode = newNode;
        }
    
        this->length++;
    }
}

TElem IndexedList::remove(int pos) {
    // Best case = Θ(1) - if it's the first or the last
    // Worst case = Θ(n) - if it's the one before the tail
    // Average case = O(n)

    if (pos < 0 || pos >= this->length) { throw exception(); }
    else if (pos == 0) {
        TElem removedValue = this->head->data;
        if (this->head->nextNode != NULL) {
            this->head->nextNode->previousNode = NULL;
            this->head = this->head->nextNode;
        }
        else if (this->length == 1) {
            this->head = NULL;
            this->tail = NULL;
        }
        this->length--;
        return removedValue;
    }
    else if (pos == this->length - 1) {
        TElem removedValue = this->tail->data;
        this->tail->previousNode->nextNode = NULL;
        this->tail = this->tail->previousNode;
        this->length--;
        return removedValue;
    }
    else {
        int currentPossition = 1;
        Node* currentNode = this->head->nextNode;
        while (currentPossition < pos) {
            currentNode = currentNode->nextNode;
            currentPossition++;
        }
        int removedValue = currentNode->data;
        currentNode->nextNode->previousNode = currentNode->previousNode;
        currentNode->previousNode->nextNode = currentNode->nextNode;
        this->length--;
        return removedValue;
    }
}

int IndexedList::search(TElem e) const {
    // Best case = Θ(1) - if it's the first or the last.
    // Worst case = Θ(n) - if it's before the tail
    // Average case = O(n)
    if (this->head->data == e) { return 0; }
    else if (this->tail->data == e) { return this->length - 1; }
    else {
        int currentPosition = 1;
        Node* currentNode = this->head->nextNode;
        while (currentNode != this->tail) {
            if (currentNode->data == e) { return currentPosition; }
            else {
                currentNode = currentNode->nextNode;
                currentPosition++;
            }
        }
    }
	return -1;
}

int IndexedList::lastIndexOf(TElem elem) const
{   // Best case = Θ(1) - the element that we search for is the last
    // Worst case = Θ(n) - the elemenet is the head
    // Average case = O(n)

    if (this->tail->data == elem) { return this->length - 1; }
    else {
        int currentPosition = this->length - 2;
        Node* currentNode = this->tail->previousNode;
        while (currentPosition != -1) {
            if (currentNode->data == elem) { return currentPosition; }
            else {
                currentPosition--;
            }
        }
    }
    return -1;
}

ListIterator IndexedList::iterator() const {
    return ListIterator(*this);        
}

IndexedList::~IndexedList() {
	//TODO - Implementation
}