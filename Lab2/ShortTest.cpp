#include <assert.h>
#include <exception>
#include <iostream>

#include "ShortTest.h"
#include "IndexedList.h"
#include "ListIterator.h"

using namespace std;




void testAll() {
    IndexedList list = IndexedList();
    assert(list.isEmpty());
    list.addToEnd(1);
    assert(list.size() == 1);
    list.addToPosition(0,2);
    assert(list.size() == 2);
    ListIterator it = list.iterator();
    assert(it.valid());
    it.next();
    assert(it.getCurrent() == 1);
    it.first();
    assert(it.getCurrent() == 2);
    assert(list.search(1) == 1);
    assert(list.setElement(1,3) == 1);
    assert(list.getElement(1) == 3);
    assert(list.remove(0) == 2);
    assert(list.size() == 1);

    cout<<"Bonus Operation"<<endl;
    list.addToEnd(1);
    list.addToEnd(2);
    list.addToEnd(3);
    list.addToEnd(4);
    list.addToEnd(4);
    assert(list.lastIndexOf(4) == 5);
    assert(list.lastIndexOf(6) == -1);
}
