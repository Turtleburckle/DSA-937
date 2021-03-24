#include <assert.h>

#include "SortedMap.h"
#include "SMIterator.h"
#include "ShortTest.h"
#include <exception>

#include <iostream>
using namespace std;

bool relatie1(TKey cheie1, TKey cheie2) {
	if (cheie1 <= cheie2) {
		return true;
	}
	else {
		return false;
	}
}

void testAll(){
	SortedMap sm(relatie1);
	assert(sm.size() == 0);
	assert(sm.isEmpty());
    sm.add(1,2);
    assert(sm.size() == 1);
    assert(!sm.isEmpty());
    assert(sm.search(1)!=NULL_TVALUE);
    TValue v =sm.add(1,3);
    assert(v == 2);
    assert(sm.search(1) == 3);
    SMIterator it = sm.iterator();
    it.first();
    while (it.valid()){
    	TElem e = it.getCurrent();
    	assert(e.second != NULL_TVALUE);
    	it.next();
    }
    assert(sm.remove(1) == 3);
    assert(sm.isEmpty());


    // TEST FOR NEW OPERATION
    sm.add(1, 2);
    sm.add(2, 3);
    sm.add(5, 2);
    sm.add(6, 2);
    sm.add(3, 2);
    sm.add(4, 2);
    //   |1|    |2|     |3|     |4|     |5|     |6|
    // [(1,2); (2,3);  (3,2);  (4,2);  (5,2);  (6,2)]
    it.first();
    it.next(); // second
    it.next(); // third
    it.next(); //fourth
    it.next(); //fifth
    it.jumpBackward(2);
    assert(it.getCurrent().first == 3);
    it.jumpBackward(10);
    assert(it.valid()==false);
    try {
        it.jumpBackward(-1);
        assert(false);
    }
    catch (exception&) { assert(true); }
}

