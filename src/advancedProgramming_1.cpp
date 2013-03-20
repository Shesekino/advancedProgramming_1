//============================================================================
// Name        : advancedProgramming_1.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "memPage_t.h"
#include "memPool_t.h"
using namespace std;

int main() {

	// testing memPage
	memPage_t myObj(16);

	cout << "current position is: " << myObj.getCurrentPosition() << endl;
	myObj.write("amir", 4);
	cout << "current position is: " << myObj.getCurrentPosition() << endl;

	cout << "rewinding..." << flush;
	myObj.setCurrentPosition(0);
	cout << "current position is: " << myObj.getCurrentPosition() << endl;

	char Stuff[16];
	int readChars = myObj.read(Stuff, 6);
	cout << "read things: " << Stuff << " total of " << readChars << endl;

	cout << "attempting to set current position to 5..." << flush;
	myObj.setCurrentPosition(5);
	cout << "current position is: " << myObj.getCurrentPosition() << endl;

	// following commented code doesn't work because we disabled copy-c'tor and assignment operator
	//memPage_t mySecondObj = myObj;
	//memPage_t mySecondObj(16);
	//mySecondObj = myObj;

	// testing memPool
	memPool_t pool3(2 ,1);
	char Stuff2[16];
	int derp = pool3.read(Stuff, 4);
	cout << "pool 3 read : " << derp << " chars, content is : " << Stuff2 << endl;
	int herp = pool3.write("amiramiramir", 13);
	cout << "pool 3 wrote : " << herp << " chars " << endl;
	pool3.setCurrentPosition(0);
	derp = pool3.read(Stuff2, 13);
	cout << "pool 3 read : " << derp << " chars, content is : " << Stuff2 << endl;
	cout << "actual size is  : " << pool3.getActualSize() << endl;
	cout << "page num is  : " << pool3.getNumberOfPages() << endl;

	// testing int write/read
	memPool_t pool4(3, 4);
	int k = 10;

	pool4.write(&k, sizeof(int));
	int j = 0;

	cout << "j is : " << j << endl;
	pool4.setCurrentPosition(0);
	pool4.read(&j, sizeof(int));
	cout << "j is : " << j << endl;

	return 0;
}
