#include "ExtendedTest.h"
#include "ShortTest.h"

#include "SortedMap.h"

#include <iostream>
using namespace std;


int main() {
	testAll();
	cout << "Short test done!" << endl;
	testAllExtended();
	cout << "That's all!" << endl;
	//testOperation();
	cout << "Operation test done!" << endl;
	system("pause");
	return 0;
}


